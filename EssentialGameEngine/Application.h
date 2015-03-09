#pragma once

#include "Macros.h"
#include "Constants.h"
#include "Shader.h"
#include <Windows.h>
#include <d3d11.h>

#pragma comment (lib, "d3d11.lib")


namespace Essential {


	class ESSENTIAL_API Application
	{
	public:
		Application();
		Application(HINSTANCE hInstance);
		virtual ~Application();

		// access tests
		bool MatchHWND(HWND toTest)
		{
			return AppWnd == toTest;
		}

		// main application loop
		int Run();

		// framework methods
		virtual bool Init();
		virtual void Start();
		virtual void Update(float dt);
		virtual void Render(float dt);
		virtual LRESULT MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

		void LoadShader(LPCWSTR filename);

	protected:
		HWND AppWnd;
		HINSTANCE AppInstance;
		UINT ClientWidth;
		UINT ClientHeight;
		DWORD WindowStyle;
		WCHAR* AppTitle;
		float DeltaTime;
		float FPS;
		
		bool InitWindow();
		void Shutdown();
		bool OutErrorMessage(const char* message);
		void CalculateFPS(float dt);

		// DirectX
	protected:
		IDXGISwapChain *swapchain;             // the pointer to the swap chain interface
		ID3D11Device *dev;                     // the pointer to our Direct3D device interface
		ID3D11DeviceContext *devcon;           // the pointer to our Direct3D device context
		ID3D11RenderTargetView *backbuffer;    // the pointer to the back buffer
		void InitD3D();     // sets up and initializes Direct3D
		void CleanD3D();            // closes Direct3D and releases memory
		Shader* shader;
	};

}