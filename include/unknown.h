//
// This file is part of the "dx12" project
// See "LICENSE" for license information.
//

#ifndef DX12_UNKNOWN_H_
#define DX12_UNKNOWN_H_

#include <atomic>

#include "glue.h"

//----------------------------------------------------------------------------------------------------------------------

class Unknown : public IUnknown {
public:
    virtual ~Unknown() = default;

    HRESULT STDMETHODCALLTYPE QueryInterface(
        REFIID riid,
        void **ppvObject) override;

    ULONG STDMETHODCALLTYPE AddRef( void) override;

    ULONG STDMETHODCALLTYPE Release( void) override;

private:
    std::atomic<uint64_t> count_ = { 0 };
};

//----------------------------------------------------------------------------------------------------------------------

#endif // DX12_UNKNOWN_H_
