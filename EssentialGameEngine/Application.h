#pragma once

#include <Windows.h>

namespace Essential {


	class Application
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
		//virtual void Update(float dt) = 0;
		//virtual void Render(float dt) = 0;
		virtual LRESULT MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	protected:
		HWND AppWnd;
		HINSTANCE AppInstance;
		UINT ClientWidth;
		UINT ClientHeight;
		DWORD WindowStyle;
		WCHAR* AppTitle;
		float DeltaTime;

		
		bool InitWindow();
		void Shutdown();
		bool OutErrorMessage(const char* message);

	};

}