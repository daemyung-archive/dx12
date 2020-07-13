//
// This file is part of the "dx12" project
// See "LICENSE" for license information.
//

#ifndef DX12_WRL_H_
#define DX12_WRL_H_

//----------------------------------------------------------------------------------------------------------------------

template <typename T>
class ComPtr {
public:
    ComPtr() = default;

    ComPtr(T* ptr)
    : ptr_(ptr) {
    }

    ComPtr(const ComPtr<T>& other)
    : ptr_(other.ptr_) {
        if (ptr_) {
            ptr_->AddRef();
        }
    }

    ~ComPtr() {
        if (ptr_) {
            ptr_->Release();
        }

        ptr_ = nullptr;
    }

    auto operator=(T* ptr) {
        if (ptr_) {
            ptr_->Release();
        }

        ptr_ = ptr;

        return *this;
    }

    auto operator=(const ComPtr<T>& other) {
        if (ptr_) {
            ptr_->Release();
        }

        ptr_ = other.ptr_;

        if (ptr_) {
            ptr_->AddRef();
        }

        return *this;
    }

    operator bool() const {
        return ptr_;
    }

    auto operator&() {
        auto count = 0;

        if (ptr_) {
            count = ptr_->Release();
        }

        if (!count) {
            ptr_ = nullptr;
        }

        return &ptr_;
    }

    auto operator->() const {
        return ptr_;
    }

    auto Reset() {
        auto count = 0;

        if (ptr_) {
            count = ptr_->Release();
        }

        if (!count) {
            ptr_ = nullptr;
        }

        return count;
    }

    auto Get() const {
        return ptr_;
    }

    auto GetAddressOf() {
        return &ptr_;
    }

private:
    T* ptr_ = { nullptr };
};

//----------------------------------------------------------------------------------------------------------------------

template <typename T, typename U>
inline bool operator==(const ComPtr<T>& lhs, const ComPtr<U>& rhs) {
    return lhs.Get() == rhs.Get();
}

//----------------------------------------------------------------------------------------------------------------------

template <typename T>
inline bool operator==(const ComPtr<T>& lhs, decltype(nullptr)) {
    return lhs.Get() == nullptr;
}

//----------------------------------------------------------------------------------------------------------------------

template <typename T>
inline bool operator==(decltype(__nullptr), const ComPtr<T>& rhs) {
    return nullptr == rhs.Get();
}

//----------------------------------------------------------------------------------------------------------------------

template <typename T, typename U>
inline bool operator!=(const ComPtr<T>& lhs, const ComPtr<U>& rhs) {
    return lhs.Get() != rhs.Get();
}

//----------------------------------------------------------------------------------------------------------------------

template <typename T>
inline bool operator!=(const ComPtr<T>& lhs, decltype(nullptr)) {
    return lhs.Get() != nullptr;
}

//----------------------------------------------------------------------------------------------------------------------

template <typename T>
inline bool operator!=(decltype(__nullptr), const ComPtr<T>& rhs) {
    return nullptr != rhs.Get();
}

//----------------------------------------------------------------------------------------------------------------------

#endif // DX12_WRL_H_
