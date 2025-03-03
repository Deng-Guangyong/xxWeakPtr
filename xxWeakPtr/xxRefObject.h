/**

    @file      xxRefObject.h
    @brief     
    @details   ~
    @author    dgy
    @date      27.02.2025
    @copyright © xx, 2025. All right reserved.

**/

#ifndef XXREFOBJECT_H
#define XXREFOBJECT_H

#include "xxWeakPtrExport.h"

class XXWEAKPTR_API xxRefObject
{
public:
    xxRefObject();
    virtual ~xxRefObject();

    xxRefObject(const xxRefObject& other);
    xxRefObject& operator=(const xxRefObject& other);

private:
    template<class T> friend class xxWeakPtr;
    
    class ProxyRef
    {
    public:
        explicit ProxyRef(xxRefObject* pObject) : m_pObject(pObject), m_refCount(0) {}
        ~ProxyRef() { if(m_pObject) m_pObject->m_pProxy = nullptr; }
        
        xxRefObject* operator->() { return m_pObject; }
        const xxRefObject* operator->() const { return m_pObject; }
        
        xxRefObject& operator*() { return *m_pObject; }
        const xxRefObject& operator*() const { return *m_pObject; }
        
        xxRefObject* get() { return m_pObject; }
        const xxRefObject* get() const { return m_pObject; }
        
        void reset() { m_pObject = nullptr; }
        void ref() { m_refCount++; }
        void unRef() { if(--m_refCount == 0) delete this; }
        bool isValid() const { return m_pObject != nullptr; }

    private:
        friend class xxRefObject;
        xxRefObject* m_pObject;
        int m_refCount;
    };

    ProxyRef* getOrCreateProxy() const;

private:
    mutable ProxyRef* m_pProxy = nullptr;
};

#endif // XXREFOBJECT_H
