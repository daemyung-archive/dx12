//
// This file is part of the "dx12" project
// See "LICENSE" for license information.
//

#include "d3dcompiler.h"

#include <fstream>

#include "d3d_blob.h"
#include "d3d_compiler.h"

//----------------------------------------------------------------------------------------------------------------------

using namespace std;

//----------------------------------------------------------------------------------------------------------------------

HRESULT WINAPI
D3DCompileFromFile(_In_ LPCWSTR pFileName,
                   _In_reads_opt_(_Inexpressible_(pDefines->Name != NULL)) CONST D3D_SHADER_MACRO* pDefines,
                   _In_opt_ ID3DInclude* pInclude,
                   _In_ LPCSTR pEntrypoint,
                   _In_ LPCSTR pTarget,
                   _In_ UINT Flags1,
                   _In_ UINT Flags2,
                   _Out_ ID3DBlob** ppCode,
                   _Always_(_Outptr_opt_result_maybenull_) ID3DBlob** ppErrorMsgs) {
    fstream fin(pFileName, ios::in | ios::binary);
    if (!fin.is_open()) {
        return D3D11_ERROR_FILE_NOT_FOUND;
    }

    const auto hlsl = string(istreambuf_iterator<char>(fin), istreambuf_iterator<char>());
    if (hlsl.empty()) {
        return E_FAIL;
    }

    D3DCompiler compiler;

    if (pDefines) {
        compiler.SetDefines(pDefines);
    }

    compiler.SetEntryPoint(pEntrypoint);
    compiler.SetTarget(pTarget);
    compiler.SetFlags(D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION);
    *ppCode = compiler.Compile(hlsl, ppErrorMsgs);

    return (*ppCode) ? S_OK : E_FAIL;
}

//----------------------------------------------------------------------------------------------------------------------
