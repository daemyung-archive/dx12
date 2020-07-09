//
// This file is part of the "dx12" project
// See "LICENSE" for license information.
//

#include "d3d12.h"

#include <cassert>

#include "d3d12_device.h"

//----------------------------------------------------------------------------------------------------------------------

HRESULT WINAPI D3D12CreateDevice(
    _In_opt_ IUnknown* pAdapter,
    D3D_FEATURE_LEVEL MinimumFeatureLevel,
    _In_ REFIID riid, // Expected: ID3D12Device
    _COM_Outptr_opt_ void** ppDevice)
{
    if (pAdapter) {
        assert(false && "Not implement!!!");
    } else {
        *ppDevice = new D3D12Device();
        assert(*ppDevice);
    }

    return S_OK;
}

//----------------------------------------------------------------------------------------------------------------------
