/**

    @file      xxWeakPtr.h
    @brief     
    @details   ~
    @author    dgy
    @date      27.02.2025
    @copyright © xx, 2025. All right reserved.

**/

#ifndef XXWEAKPTR_H
#define XXWEAKPTR_H

#include <type_traits>
#include "xxRefObject.h"

template<class T>
class xxWeakPtr
{
    static_assert(std::is_base_of_v<xxRefObject, T>, 
        "xxWeakPtr template parameter must inherit from xxRefObject");

public:
    xxWeakPtr() noexcept = default;

    explicit xxWeakPtr(T* pObj) 
    {
        if(pObj)     
        {
            m_pProxy = pObj->getOrCreateProxy();
            m_pProxy->ref();
        }
    }

    xxWeakPtr(const xxWeakPtr& other) noexcept : m_pProxy(other.m_pProxy)
    {
        if(m_pProxy) m_pProxy->ref();
    }

    xxWeakPtr(xxWeakPtr&& other) noexcept : m_pProxy(other.m_pProxy)
    {
        other.m_pProxy = nullptr;
    }

    ~xxWeakPtr()
    {
        if(m_pProxy) m_pProxy->unRef();
    }

    xxWeakPtr& operator=(const xxWeakPtr& other) noexcept
    {
        if(this != &other)
        {
            reset();
            m_pProxy = other.m_pProxy;
            if(m_pProxy) m_pProxy->ref();
        }
        return *this;
    }

    xxWeakPtr& operator=(xxWeakPtr&& other) noexcept
    {
        if(this != &other)
        {
            reset();
            m_pProxy = other.m_pProxy;
            other.m_pProxy = nullptr;
        }
        return *this;
    }

    xxWeakPtr& operator=(T* pObj) noexcept
    {
        reset();
        if(pObj)
        {
            m_pProxy = pObj->getOrCreateProxy();
            m_pProxy->ref();
        }
        return *this;
    }

    T* get() const noexcept
    {
        return m_pProxy && m_pProxy->isValid() ? 
            static_cast<T*>(m_pProxy->get()) : nullptr;
    }

    T* operator->() const noexcept {
        return get();
    }

    T& operator*() const {
        T* p = get();
        if (!p) throw std::runtime_error("Dereferencing expired weak pointer");
        return *p;
    }

    bool expired() const noexcept
    {
        return !m_pProxy || !m_pProxy->isValid();
    }

    void reset() noexcept
    {
        if(m_pProxy)
        {
            m_pProxy->unRef();
            m_pProxy = nullptr;
        }
    }

    explicit operator bool() const noexcept { return !expired(); }

private:
    xxRefObject::ProxyRef* m_pProxy = nullptr;
};

#endif // !XXWEAKPTR_H
