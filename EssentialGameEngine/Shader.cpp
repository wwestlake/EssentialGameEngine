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