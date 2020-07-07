//
// This file is part of the "dx12" project
// See "LICENSE" for license information.
//

#ifndef DX12_GLUE_GUARD
#define DX12_GLUE_GUARD

#include <cstddef>
#include <cstdint>
#include <cwchar>
#include <objc/objc.h>

//----------------------------------------------------------------------------------------------------------------------

#define __RPCNDR_H_VERSION__

using RPC_IF_HANDLE = void*;

//----------------------------------------------------------------------------------------------------------------------

#define COM_NO_WINDOWS_H

//----------------------------------------------------------------------------------------------------------------------

#define D3D12_IGNORE_SDK_LAYERS

//----------------------------------------------------------------------------------------------------------------------

using BYTE     = uint8_t;
using UCHAR    = uint8_t;
using WCHAR    = wchar_t;
using UINT8    = uint8_t;
using INT8     = int8_t;
using USHORT   = uint16_t;
using UINT16   = uint16_t;
using UINT     = uint32_t;
using UINT32   = uint32_t;
using INT      = int32_t;
using ULONG    = uint64_t;
using UINT64   = uint64_t;
using LONG     = int64_t;
using LONGLONG = int64_t;
using SIZE_T   = size_t;
using FLOAT    = float;
using HRESULT  = int64_t;
using DWORD    = uint32_t;
using LPVOID   = void*;
using LPCVOID  = const void*;
using LONG_PTR = uint64_t;
using LPCSTR   = const char*;
using LPCWSTR  = const wchar_t*;

//----------------------------------------------------------------------------------------------------------------------

union LARGE_INTEGER {
    struct {
#if BIGENDIAN
        LONG HighPart;
        DWORD LowPart;
#else
        DWORD LowPart;
        LONG HighPart;
#endif
    };
    struct {
#if BIGENDIAN
        LONG HighPart;
        DWORD LowPart;
#else
        DWORD LowPart;
        LONG HighPart;
#endif
    } u;
    LONGLONG QuadPart;
};

//----------------------------------------------------------------------------------------------------------------------

using HANDLE  = void*;
using HMODULE = HANDLE;
using HDC     = HANDLE;
using HWND    = HANDLE;

#define DECLARE_HANDLE(name) struct name##__ { int unused; }; typedef struct name##__ *name

//----------------------------------------------------------------------------------------------------------------------

struct GUID {
    ULONG  Data1;
    USHORT Data2;
    USHORT Data3;
    UCHAR  Data4[8];
};

using REFGUID = const GUID&;
using IID     = GUID;
using REFIID  = const IID&;
using UUID    = GUID;

//----------------------------------------------------------------------------------------------------------------------

struct LUID
{
    DWORD LowPart;
    DWORD HighPart;
};

//----------------------------------------------------------------------------------------------------------------------

struct SECURITY_ATTRIBUTES {
    DWORD nLength;
    LPVOID lpSecurityDescriptor;
    BOOL bInheritHandle;
};

//----------------------------------------------------------------------------------------------------------------------

struct RECT {
    LONG left;
    LONG top;
    LONG right;
    LONG bottom;
};

//----------------------------------------------------------------------------------------------------------------------

#define EXTERN_C extern "C"
#define WINAPI
#define FAR

//----------------------------------------------------------------------------------------------------------------------

#define DECLSPEC_NOVTABLE
#define DECLSPEC_SELECTANY __attribute__((weak))
#define DECLSPEC_UUID(x)

//----------------------------------------------------------------------------------------------------------------------

#define STDMETHODCALLTYPE

//----------------------------------------------------------------------------------------------------------------------

#define DEFINE_ENUM_FLAG_OPERATORS(ENUMTYPE) \
extern "C++" { \
    inline ENUMTYPE operator |(ENUMTYPE a, ENUMTYPE b) { return ENUMTYPE(((int)a)|((int)b)); } \
    inline ENUMTYPE operator |=(ENUMTYPE& a, ENUMTYPE b) { return (ENUMTYPE &)(((int &)a) |= ((int)b)); } \
    inline ENUMTYPE operator &(ENUMTYPE a, ENUMTYPE b) { return ENUMTYPE(((int)a)&((int)b)); } \
    inline ENUMTYPE operator &=(ENUMTYPE& a, ENUMTYPE b) { return (ENUMTYPE &)(((int &)a) &= ((int)b)); } \
    inline ENUMTYPE operator ~(ENUMTYPE a) { return (ENUMTYPE)(~((int)a)); } \
    inline ENUMTYPE operator ^(ENUMTYPE a, ENUMTYPE b) { return ENUMTYPE(((int)a)^((int)b)); } \
    inline ENUMTYPE operator ^=(ENUMTYPE& a, ENUMTYPE b) { return (ENUMTYPE &)(((int &)a) ^= ((int)b)); } \
}

//----------------------------------------------------------------------------------------------------------------------

#define COM_DECLSPEC_NOTHROW

#define __STRUCT__ struct
#define interface __STRUCT__
#define STDMETHOD(method)        virtual COM_DECLSPEC_NOTHROW HRESULT STDMETHODCALLTYPE method
#define STDMETHOD_(type,method)  virtual COM_DECLSPEC_NOTHROW type STDMETHODCALLTYPE method
#define STDMETHODV(method)       virtual COM_DECLSPEC_NOTHROW HRESULT STDMETHODVCALLTYPE method
#define STDMETHODV_(type,method) virtual COM_DECLSPEC_NOTHROW type STDMETHODVCALLTYPE method
#define PURE                    = 0
#define THIS_
#define THIS                    void
#define DECLARE_INTERFACE(iface)                      interface DECLSPEC_NOVTABLE iface
#define DECLARE_INTERFACE_(iface, baseiface)          interface DECLSPEC_NOVTABLE iface : public baseiface
#define DECLARE_INTERFACE_IID(iface, iid)             interface DECLSPEC_UUID(iid) DECLSPEC_NOVTABLE iface
#define DECLARE_INTERFACE_IID_(iface, baseiface, iid) interface DECLSPEC_UUID(iid) DECLSPEC_NOVTABLE iface : public baseiface

#define IFACEMETHOD(method)        __override STDMETHOD(method)
#define IFACEMETHOD_(type,method)  __override STDMETHOD_(type,method)
#define IFACEMETHODV(method)       __override STDMETHODV(method)
#define IFACEMETHODV_(type,method) __override STDMETHODV_(type,method)

//----------------------------------------------------------------------------------------------------------------------

#define DEFINE_GUID(name, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8) \
    EXTERN_C const GUID DECLSPEC_SELECTANY name = { l, w1, w2, { b1, b2,  b3,  b4,  b5,  b6,  b7,  b8 } }

//----------------------------------------------------------------------------------------------------------------------

#define MIDL_INTERFACE(x) struct

//----------------------------------------------------------------------------------------------------------------------

#define __uuidof(x) UUID()

//----------------------------------------------------------------------------------------------------------------------

DEFINE_GUID(IID_IUnknown, 0x00000000, 0x0000, 0x0000, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46);

MIDL_INTERFACE("00000000-0000-0000-C000-000000000046")
IUnknown
{
    virtual HRESULT STDMETHODCALLTYPE QueryInterface(
        REFIID riid,
        void **ppvObject) = 0;

    virtual ULONG STDMETHODCALLTYPE AddRef( void) = 0;

    virtual ULONG STDMETHODCALLTYPE Release( void) = 0;

    template<class Q>
    HRESULT
    STDMETHODCALLTYPE
    QueryInterface(Q** pp)
    {
        return QueryInterface(__uuidof(Q), (void **)pp);
    }
};

//----------------------------------------------------------------------------------------------------------------------

#define __in_ecount(n)
#define __in_ecount_opt(n)
#define __in_ecount_opt(n)

//----------------------------------------------------------------------------------------------------------------------

#define _Always_(a)
#define _In_
#define _In_z_
#define _In_reads_(s)
#define _In_reads_bytes_(s)
#define _In_reads_opt_(s)
#define _In_reads_bytes_opt_(s)
#define _In_opt_
#define _In_range_(l,h)
#define _Out_
#define _Out_opt_
#define _Out_writes_(s)
#define _Out_writes_bytes_(s)
#define _Out_writes_opt_(s)
#define _Out_writes_bytes_opt_(s)
#define _Out_writes_to_opt_(s,c)
#define _Outptr_opt_result_bytebuffer_(s)
#define _Inout_
#define _Inout_opt_
#define _Inout_updates_bytes_(s)
#define _Field_size_full_(s)
#define _Field_size_bytes_full_(s)
#define _Field_size_bytes_full_opt_(s)
#define _COM_Outptr_
#define _COM_Outptr_opt_
#define _COM_Outptr_opt_result_maybenull_

//----------------------------------------------------------------------------------------------------------------------

#endif // DX12_GLUE_GUARD
