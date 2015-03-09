#include "stdafx.h"
#include "Application.h"
#include "Shader.h"
#include <iostream>
#include <d3dcompiler.h>

namespace Essential {


	namespace
	{
		Application* g_pGameWindow;
	}

	LRESULT CALLBACK MainWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		if (g_pGameWindow && g_pGameWindow->MatchHWND(hwnd))
			return g_pGameWindow->MsgProc(hwnd, msg, wParam, lParam);
		else
			return DefWindowProc(hwnd, msg, wParam, lParam);
	}



	Application::Application() : Application(GetModuleHandle(NULL))
	{
	}

	Application::Application(HINSTANCE hInstance)
	{
		g_pGameWindow = this;
		AppInstance = hInstance;
		AppWnd = NULL;
		ClientWidth = SCREEN_WIDTH;
		ClientHeight = SCREEN_HEIGHT;
		AppTitle = L"Essential Game Engine";
		WindowStyle = WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX;
	}

	Application::~Application()
	{
	}


	int Application::Run()
	{
		__int64 prevTime = 0;
		QueryPerformanceCounter((LARGE_INTEGER*)&prevTime);
		__int64 countsPerSecond = 0;
		QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSecond);
		float secondsPerCount = 1.0 / countsPerSecond;

		MSG msg = { 0 };
		Start();
		while (WM_QUIT != msg.message)
		{
			if (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
			{
				__int64 currentTime = 0;
				QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);
				DeltaTime = (currentTime - prevTime) * secondsPerCount;
				Update(DeltaTime);
				Render(DeltaTime);
				CalculateFPS(DeltaTime);
				prevTime = currentTime;
			}


		}

		Shutdown();

		return static_cast<int>(msg.wParam);
	}

	void Application::Start()
	{
		const D3D_SHADER_MACRO defines[] =
		{
			"EXAMPLE_DEFINE", "1",
			NULL, NULL
		};

	}


	bool Application::InitWindow()
	{
		WNDCLASSEX wcex;
		ZeroMemory(&wcex, sizeof(WNDCLASSEX));
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = 0;
		wcex.cbSize = sizeof(WNDCLASSEX);
		wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.hInstance = AppInstance;
		wcex.lpfnWndProc = MainWindowProc;
		wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
		//wcex.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
		wcex.lpszClassName = L"GAMEWINDOW";
		wcex.lpszMenuName = NULL;
		wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
		if (!RegisterClassEx(&wcex)) return OutErrorMessage("Failed to register window class");

		RECT r{ 0, 0, ClientWidth, ClientHeight };
		AdjustWindowRect(&r, WindowStyle, FALSE);
		int width = r.right - r.left;
		int height = r.bottom - r.top;
		int x = GetSystemMetrics(SM_CXSCREEN) / 2 - width / 2;
		int y = GetSystemMetrics(SM_CYSCREEN) / 2 - height / 2;

		AppWnd = CreateWindow(L"GAMEWINDOW", (LPWSTR)AppTitle, WindowStyle, x, y, width, height, NULL, NULL, AppInstance, NULL);
		if (!AppWnd) return OutErrorMessage("Failed to create game window");

		ShowWindow(AppWnd, SW_SHOW);

		return true;
	}


	bool Application::Init()
	{
		if (!InitWindow()) return false;
		InitD3D();

		return true;
	}



	void Application::Shutdown()
	{
		CleanD3D();
	}

	LRESULT Application::MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		switch (msg)
		{
		case WM_DESTROY:
			PostQuitMessage(0);
			break;

		default:
			return DefWindowProc(hwnd, msg, wParam, lParam);
		}
	}


	bool Application::OutErrorMessage(const char* message)
	{
		std::cout << message << std::endl;
		return false;
	}


	// DirectX

	void Application::InitD3D()     // sets up and initializes Direct3D
	{
		// create a struct to hold information about the swap chain
		DXGI_SWAP_CHAIN_DESC scd;

		// clear out the struct for use
		ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

		// fill the swap chain description struct
		scd.BufferCount = 1;                                    // one back buffer
		scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;     // use 32-bit color
		scd.BufferDesc.Width = SCREEN_WIDTH;
		scd.BufferDesc.Height = SCREEN_HEIGHT;
		scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;      // how swap chain is to be used
		scd.OutputWindow = AppWnd;                                // the window to be used
		scd.SampleDesc.Count = 4;                               // how many multisamples
		scd.Windowed = TRUE;                                    // windowed/full-screen mode
		scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

		// create a device, device context and swap chain using the information in the scd struct
		D3D11CreateDeviceAndSwapChain(NULL,
			D3D_DRIVER_TYPE_HARDWARE,
			NULL,
			NULL,
			NULL,
			NULL,
			D3D11_SDK_VERSION,
			&scd,
			&swapchain,
			&dev,
			NULL,
			&devcon);


		// get the address of the back buffer
		ID3D11Texture2D *pBackBuffer;
		swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

		// use the back buffer address to create the render target
		dev->CreateRenderTargetView(pBackBuffer, NULL, &backbuffer);
		pBackBuffer->Release();

		// set the render target as the back buffer
		devcon->OMSetRenderTargets(1, &backbuffer, NULL);


		// Set the viewport
		D3D11_VIEWPORT viewport;
		ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

		viewport.TopLeftX = 0;
		viewport.TopLeftY = 0;
		viewport.Width = SCREEN_WIDTH;
		viewport.Height = SCREEN_HEIGHT;

		devcon->RSSetViewports(1, &viewport);

	}

	void Application::CleanD3D()            // closes Direct3D and releases memory
	{
		swapchain->SetFullscreenState(FALSE, NULL);    // switch to windowed mode

		// close and release all existing COM objects
		swapchain->Release();
		dev->Release();
		devcon->Release();
	}

	void Application::Render(float dt)
	{
		float clearColor[4] = { 0.0f, 0.2f, 0.4f, 1.0f };
		// clear the back buffer to a deep blue
		devcon->ClearRenderTargetView(backbuffer, clearColor);



		// do 3D rendering on the back buffer here

		// switch the back buffer and the front buffer
		swapchain->Present(0, 0);

	}

	float elapsed = 0.0f;

	void Application::Update(float dt)
	{
		elapsed += dt;
		if (elapsed > 1.0f)
		{
			elapsed = 0.0f;
			std::cout << "FPS = " << FPS << ", DeltaTime = " << dt << std::endl;
		}
	}

	void Application::CalculateFPS(float dt)
	{
		static float elapsed = 0;
		static int frameCount = 0;

		elapsed += dt;
		frameCount++;

		if (elapsed >= 1.0f)
		{
			FPS = (float)frameCount;
			elapsed = 0.0f;
			frameCount = 0;
		}

	}


}




