//
// This file is part of the "dx12" project
// See "LICENSE" for license information.
//

#include "unknown.h"

#include <cassert>

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE Unknown::QueryInterface(
    REFIID riid,
    void **ppvObject) {
    assert(false && "Not implement!!!");
    return S_OK;
}

//----------------------------------------------------------------------------------------------------------------------

ULONG STDMETHODCALLTYPE Unknown::AddRef( void) {
    return ++count_;
}

//----------------------------------------------------------------------------------------------------------------------

ULONG STDMETHODCALLTYPE Unknown::Release( void) {
    return --count_;
}

//----------------------------------------------------------------------------------------------------------------------
