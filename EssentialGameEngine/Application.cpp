#include "stdafx.h"
#include "Application.h"
#include <iostream>

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
		ClientWidth = 800;
		ClientHeight = 600;
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
		while (WM_QUIT != msg.message)
		{
			if (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}

		Shutdown();

		return static_cast<int>(msg.wParam);
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
		wcex.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
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

		return true;
	}



	void Application::Shutdown()
	{
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

}




