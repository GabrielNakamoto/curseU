#pragma once

#include "common.h"

namespace ncurse {

template<typename T>
class Handle
{
private:

    std::unique_ptr<T,std::function<void (T*)> > resource;

public:

    Handle(T *ptr, std::function<void (T*)> releaseCallback) :
        resource(ptr, releaseCallback)
    {
        // TODO: handle nullptr
    }

    Handle(Handle&&) noexcept = default;
    Handle &operator=(Handle&&) noexcept = default;

    T* get() const noexcept
    {
        return resource.get();
    }

    T* operator->() const noexcept
    {
        return resource.get();
    }

    T& operator*() const noexcept
    {
        return *resource;
    }

};

}