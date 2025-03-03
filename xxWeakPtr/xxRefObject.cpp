#include "xxRefObject.h"

xxRefObject::xxRefObject() = default;

xxRefObject::~xxRefObject()
{
    if(m_pProxy)
    {
        m_pProxy->reset();
        m_pProxy = nullptr;
    }
}

xxRefObject::xxRefObject(const xxRefObject& /*other*/)
{
    // 拷贝构造时不继承Proxy
}

xxRefObject& xxRefObject::operator=(const xxRefObject& /*other*/)
{
    // 赋值操作不转移Proxy
    return *this;
}

xxRefObject::ProxyRef* xxRefObject::getOrCreateProxy() const
{
    if(!m_pProxy)
    {
        m_pProxy = new ProxyRef(const_cast<xxRefObject*>(this));
    }
    return m_pProxy;
}
