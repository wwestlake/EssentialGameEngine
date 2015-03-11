/*
* This file is part of Essential Game Engine.
*
* Essential Game Engine is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* Essential Game Engine is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
*
* wwestlake@laqgdaemon.com
*
* change notes:
---------------------------------------------------------------



*/



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