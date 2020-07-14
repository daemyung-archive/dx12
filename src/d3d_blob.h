//
// This file is part of the "dx12" project
// See "LICENSE" for license information.
//

#ifndef DX12_D3D_BLOB_H_
#define DX12_D3D_BLOB_H_

#include <cstdint>
#include <vector>

#include "d3dcommon.h"
#include "unknown.h"

//----------------------------------------------------------------------------------------------------------------------

class D3DBlob : public ID3DBlob, public Unknown {
public:
    D3DBlob(const void* data, uint64_t size);

    HRESULT STDMETHODCALLTYPE QueryInterface(
        REFIID riid,
        void **ppvObject) override;

    ULONG STDMETHODCALLTYPE AddRef( void) override;

    ULONG STDMETHODCALLTYPE Release( void) override;

    LPVOID STDMETHODCALLTYPE GetBufferPointer( void) override;

    SIZE_T STDMETHODCALLTYPE GetBufferSize( void) override;

private:
    std::vector<uint8_t> buffer_;
};

//----------------------------------------------------------------------------------------------------------------------

#endif // DX12_D3D_BLOB_H_
