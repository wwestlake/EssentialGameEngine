// EssentialGameEngine.cpp : Defines the entry point for the console application.
//

#include "Application.h"
#include <windows.h>
#include <iostream>
#include "stdafx.h"

using namespace Essential;
using namespace std;

int main(int argc, char * argv[])
{
	cout << "Essential Game Engine" << endl;
	cout << "Copyright (C)2015, William W. Westlake" << endl;
	cout << "Release as open source under the GNU GPL Version 3" << endl;
	cout << "Source Code available on github" << endl;
	cout << "https://github.com/wwestlake/EssentialGameEngine" << endl;
	cout << "wwestlake@lagdaemon.com" << endl;

	Application* app = new Application();

	if (!app->Init()) return 1;

	return app->Run();

}