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

#pragma once

#if defined(ESSENTIAL_API_EXPORT)
#    define ESSENTIAL_API __declspec(dllexport)
#else
#    define ESSENTIAL_API __declspec(dllimport)
#endif

