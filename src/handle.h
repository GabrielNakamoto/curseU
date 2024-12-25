#pragma once


#include "common.h"

namespace crsu {

template<typename T>
class Handle
{
private:
    std::unique_ptr<T, std::function<void (T*)> > resource;

public:

    Handle(T *ptr, std::function<void (T*)> releaseCallback)
        :   resource(ptr, releaseCallback)
    {
        // TODO: handle nullptr
    }

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
