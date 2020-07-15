//
// This file is part of the "dx12" project
// See "LICENSE" for license information.
//

#include "d3d_compiler.h"

#include <vector>
#include <sstream>
#include <stdexcept>
#include <fmt/core.h>
#include <glslang/Include/ResourceLimits.h>
#include <SPIRV/GlslangToSpv.h>

#include "d3dcompiler.h"
#include "d3d_blob.h"

//----------------------------------------------------------------------------------------------------------------------

using namespace std;
using namespace fmt;
using namespace glslang;

//----------------------------------------------------------------------------------------------------------------------

constexpr TBuiltInResource kDefaultBuiltInResource = {
    /* .MaxLights = */ 32,
    /* .MaxClipPlanes = */ 6,
    /* .MaxTextureUnits = */ 32,
    /* .MaxTextureCoords = */ 32,
    /* .MaxVertexAttribs = */ 64,
    /* .MaxVertexUniformComponents = */ 4096,
    /* .MaxVaryingFloats = */ 64,
    /* .MaxVertexTextureImageUnits = */ 32,
    /* .MaxCombinedTextureImageUnits = */ 80,
    /* .MaxTextureImageUnits = */ 32,
    /* .MaxFragmentUniformComponents = */ 4096,
    /* .MaxDrawBuffers = */ 32,
    /* .MaxVertexUniformVectors = */ 128,
    /* .MaxVaryingVectors = */ 8,
    /* .MaxFragmentUniformVectors = */ 16,
    /* .MaxVertexOutputVectors = */ 16,
    /* .MaxFragmentInputVectors = */ 15,
    /* .MinProgramTexelOffset = */ -8,
    /* .MaxProgramTexelOffset = */ 7,
    /* .MaxClipDistances = */ 8,
    /* .MaxComputeWorkGroupCountX = */ 65535,
    /* .MaxComputeWorkGroupCountY = */ 65535,
    /* .MaxComputeWorkGroupCountZ = */ 65535,
    /* .MaxComputeWorkGroupSizeX = */ 1024,
    /* .MaxComputeWorkGroupSizeY = */ 1024,
    /* .MaxComputeWorkGroupSizeZ = */ 64,
    /* .MaxComputeUniformComponents = */ 1024,
    /* .MaxComputeTextureImageUnits = */ 16,
    /* .MaxComputeImageUniforms = */ 8,
    /* .MaxComputeAtomicCounters = */ 8,
    /* .MaxComputeAtomicCounterBuffers = */ 1,
    /* .MaxVaryingComponents = */ 60,
    /* .MaxVertexOutputComponents = */ 64,
    /* .MaxGeometryInputComponents = */ 64,
    /* .MaxGeometryOutputComponents = */ 128,
    /* .MaxFragmentInputComponents = */ 128,
    /* .MaxImageUnits = */ 8,
    /* .MaxCombinedImageUnitsAndFragmentOutputs = */ 8,
    /* .MaxCombinedShaderOutputResources = */ 8,
    /* .MaxImageSamples = */ 0,
    /* .MaxVertexImageUniforms = */ 0,
    /* .MaxTessControlImageUniforms = */ 0,
    /* .MaxTessEvaluationImageUniforms = */ 0,
    /* .MaxGeometryImageUniforms = */ 0,
    /* .MaxFragmentImageUniforms = */ 8,
    /* .MaxCombinedImageUniforms = */ 8,
    /* .MaxGeometryTextureImageUnits = */ 16,
    /* .MaxGeometryOutputVertices = */ 256,
    /* .MaxGeometryTotalOutputComponents = */ 1024,
    /* .MaxGeometryUniformComponents = */ 1024,
    /* .MaxGeometryVaryingComponents = */ 64,
    /* .MaxTessControlInputComponents = */ 128,
    /* .MaxTessControlOutputComponents = */ 128,
    /* .MaxTessControlTextureImageUnits = */ 16,
    /* .MaxTessControlUniformComponents = */ 1024,
    /* .MaxTessControlTotalOutputComponents = */ 4096,
    /* .MaxTessEvaluationInputComponents = */ 128,
    /* .MaxTessEvaluationOutputComponents = */ 128,
    /* .MaxTessEvaluationTextureImageUnits = */ 16,
    /* .MaxTessEvaluationUniformComponents = */ 1024,
    /* .MaxTessPatchComponents = */ 120,
    /* .MaxPatchVertices = */ 32,
    /* .MaxTessGenLevel = */ 64,
    /* .MaxViewports = */ 16,
    /* .MaxVertexAtomicCounters = */ 0,
    /* .MaxTessControlAtomicCounters = */ 0,
    /* .MaxTessEvaluationAtomicCounters = */ 0,
    /* .MaxGeometryAtomicCounters = */ 0,
    /* .MaxFragmentAtomicCounters = */ 8,
    /* .MaxCombinedAtomicCounters = */ 8,
    /* .MaxAtomicCounterBindings = */ 1,
    /* .MaxVertexAtomicCounterBuffers = */ 0,
    /* .MaxTessControlAtomicCounterBuffers = */ 0,
    /* .MaxTessEvaluationAtomicCounterBuffers = */ 0,
    /* .MaxGeometryAtomicCounterBuffers = */ 0,
    /* .MaxFragmentAtomicCounterBuffers = */ 1,
    /* .MaxCombinedAtomicCounterBuffers = */ 1,
    /* .MaxAtomicCounterBufferSize = */ 16384,
    /* .MaxTransformFeedbackBuffers = */ 4,
    /* .MaxTransformFeedbackInterleavedComponents = */ 64,
    /* .MaxCullDistances = */ 8,
    /* .MaxCombinedClipAndCullDistances = */ 8,
    /* .MaxSamples = */ 4,
    /* .maxMeshOutputVerticesNV = */ 256,
    /* .maxMeshOutputPrimitivesNV = */ 512,
    /* .maxMeshWorkGroupSizeX_NV = */ 32,
    /* .maxMeshWorkGroupSizeY_NV = */ 1,
    /* .maxMeshWorkGroupSizeZ_NV = */ 1,
    /* .maxTaskWorkGroupSizeX_NV = */ 32,
    /* .maxTaskWorkGroupSizeY_NV = */ 1,
    /* .maxTaskWorkGroupSizeZ_NV = */ 1,
    /* .maxMeshViewCountNV = */ 4,
    /* .limits = */ {
        /* .nonInductiveForLoops = */ 1,
        /* .whileLoops = */ 1,
        /* .doWhileLoops = */ 1,
        /* .generalUniformIndexing = */ 1,
        /* .generalAttributeMatrixVectorIndexing = */ 1,
        /* .generalVaryingIndexing = */ 1,
        /* .generalSamplerIndexing = */ 1,
        /* .generalVariableIndexing = */ 1,
        /* .generalConstantMatrixVectorIndexing = */ 1,
    }
};

//----------------------------------------------------------------------------------------------------------------------

D3DCompiler::D3DCompiler() {
    InitializeProcess();
}

//----------------------------------------------------------------------------------------------------------------------

D3DCompiler::~D3DCompiler() {
    FinalizeProcess();
}

//----------------------------------------------------------------------------------------------------------------------

ID3DBlob* D3DCompiler::Compile(const std::string& hlsl, ID3DBlob** error) {
    TShader shader(language_);
    shader.setEnvInput(EShSourceHlsl, language_, EShClientVulkan, 100);
    shader.setEnvClient(EShClientVulkan, EShTargetVulkan_1_0);
    shader.setEnvTarget(EShTargetSpv, EShTargetSpv_1_0);

    if (!entry_point_.empty()) {
        shader.setEntryPoint(entry_point_.c_str());
    }

    const char* const hlsls[] = { hlsl.c_str() };
    shader.setStrings(hlsls, 1);

    if (!shader.parse(&kDefaultBuiltInResource, 110, false, EShMsgDefault)) {
        if (error) {
            auto message = format("Fail to parse shader\n info : {}\n info debug : {}",
                shader.getInfoLog(), shader.getInfoDebugLog());
            *error = new D3DBlob(message.c_str(), message.size());
        }

        return nullptr;
    }

    TProgram program;
    program.addShader(&shader);

    if (!program.link(EShMsgDefault)) {
        if (error) {
            auto message = format("Fail to link program\n info : {}\n info debug : {}",
                program.getInfoLog(), program.getInfoDebugLog());
            *error = new D3DBlob(message.c_str(), message.size());
        }

        return nullptr;
    }

    if (!program.mapIO()) {
        if (error) {
            auto message = format("Fail to map IO\n info : {}\n info debug : {}",
                program.getInfoLog(), program.getInfoDebugLog());
            *error = new D3DBlob(message.c_str(), message.size());
        }

        return nullptr;
    }

    SpvOptions options;

    if (flags_ & D3DCOMPILE_DEBUG) {
        options.generateDebugInfo = true;
    } else {
        options.generateDebugInfo = false;
    }

    if (flags_ & D3DCOMPILE_SKIP_VALIDATION) {
        options.validate = false;
    } else {
        options.validate = true;
    }

    if (flags_ & D3DCOMPILE_SKIP_OPTIMIZATION) {
        options.disableOptimizer = true;
        options.optimizeSize = false;
    } else {
        options.disableOptimizer = false;
        options.optimizeSize = true;
    }

    vector<uint32_t> spirv;
    GlslangToSpv(*program.getIntermediate(language_), spirv, nullptr, &options);

    return new D3DBlob(spirv.data(), spirv.size() * sizeof(uint32_t));
}

//----------------------------------------------------------------------------------------------------------------------

void D3DCompiler::SetDefines(const D3D_SHADER_MACRO* defines) {
    if (!preamble_.empty()) {
        preamble_.clear();
    }

    stringstream ss;
    while (!defines->Name) {
        ss << "#define " << defines->Name;

        if (defines->Definition) {
            ss << ' ' << defines->Definition;
        }

        ss << '\n';
        ++defines;
    }

    preamble_.append(ss.str());
}

//----------------------------------------------------------------------------------------------------------------------

void D3DCompiler::SetEntryPoint(LPCSTR entry_point) {
    entry_point_ = entry_point;
}

//----------------------------------------------------------------------------------------------------------------------

void D3DCompiler::SetTarget(LPCSTR target) {
    if (!strncmp("vs", target, 2)) {
        language_ = EShLangVertex;
    } else if (!strncmp("ps", target, 2)) {
        language_ = EShLangFragment;
    }
    else {
        assert(false);
    }
}

//----------------------------------------------------------------------------------------------------------------------

void D3DCompiler::SetFlags(UINT flags) {
    flags_ = flags;
}

//----------------------------------------------------------------------------------------------------------------------
