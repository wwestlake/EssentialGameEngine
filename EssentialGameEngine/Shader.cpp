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
#include "stdafx.h"
#include "Shader.h"

namespace Essential {


	Shader::Shader(wstring srcFile, string entryPoint, string profile, const D3D_SHADER_MACRO* defines)
	{
		*(&blob) = nullptr;

		UINT flags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
		flags |= D3DCOMPILE_DEBUG;
#endif	
		hr = D3DCompileFromFile(srcFile.c_str(), defines, D3D_COMPILE_STANDARD_FILE_INCLUDE,
			entryPoint.c_str(), profile.c_str(),
			flags, 0, &shaderBlob, &errorBlob);

		if (FAILED(hr))
		{
			if (errorBlob)
			{
				OutputDebugStringA((char*)errorBlob->GetBufferPointer());
				errorBlob->Release();
			}

			if (shaderBlob)
				shaderBlob->Release();

			return;
		}

		*blob = shaderBlob;

	}


	Shader::~Shader()
	{
		shaderBlob->Release();
	}


}