//
// This file is part of the "dx12" project
// See "LICENSE" for license information.
//

#ifndef DX12_D3D_COMPILER_H_
#define DX12_D3D_COMPILER_H_

#include <string>
#include <glslang/Public/ShaderLang.h>
#include "d3dcommon.h"

//----------------------------------------------------------------------------------------------------------------------

class D3DCompiler final {
public:
    D3DCompiler();

    ~D3DCompiler();

    ID3DBlob* Compile(const std::string& hlsl, ID3DBlob** error);

    void SetDefines(const D3D_SHADER_MACRO* defines);

    void SetEntryPoint(LPCSTR entry_point);

    void SetTarget(LPCSTR target);

    void SetFlags(UINT flags);

private:
    std::string preamble_;
    std::string entry_point_;
    EShLanguage language_;
    uint32_t flags_ = { 0 };


};

//----------------------------------------------------------------------------------------------------------------------

#endif // DX12_D3D_COMPILER_H_
