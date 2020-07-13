//
// This file is part of the "dx12" project
// See "LICENSE" for license information.
//

#ifndef DX12_D3D12_HELPER_H_
#define DX12_D3D12_HELPER_H_

#include "d3d12.h"

//----------------------------------------------------------------------------------------------------------------------

class D3D12Resource;

//----------------------------------------------------------------------------------------------------------------------

inline auto ToResource(D3D12_CPU_DESCRIPTOR_HANDLE handle) {
    return *reinterpret_cast<D3D12Resource**>(handle.ptr);
}

//----------------------------------------------------------------------------------------------------------------------

#endif // DX12_D3D12_HELPER_H_
