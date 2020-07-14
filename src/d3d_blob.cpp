//
// This file is part of the "dx12" project
// See "LICENSE" for license information.
//

#include "d3d_blob.h"

//----------------------------------------------------------------------------------------------------------------------

D3DBlob::D3DBlob(const void* data, uint64_t size) {
    buffer_.resize(size);
    memcpy(buffer_.data(), data, size);
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT D3DBlob::STDMETHODCALLTYPE QueryInterface(
    REFIID riid,
    void **ppvObject) {
    return Unknown::QueryInterface(riid, ppvObject);
}

//----------------------------------------------------------------------------------------------------------------------

ULONG STDMETHODCALLTYPE D3DBlob::AddRef( void) {
    return Unknown::AddRef();
}

//----------------------------------------------------------------------------------------------------------------------

ULONG STDMETHODCALLTYPE D3DBlob::Release( void) {
    return Unknown::Release();
}

//----------------------------------------------------------------------------------------------------------------------

LPVOID STDMETHODCALLTYPE D3DBlob::GetBufferPointer( void) {
    return buffer_.data();
}

//----------------------------------------------------------------------------------------------------------------------

SIZE_T STDMETHODCALLTYPE D3DBlob::GetBufferSize( void) {
    return buffer_.size();
}

//----------------------------------------------------------------------------------------------------------------------
