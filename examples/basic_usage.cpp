#include <iostream>
#include <memory>
#include <xxWeakPtr/xxRefObject.h>
#include <xxWeakPtr/xxWeakPtr.h>

class MyObject : public xxRefObject {
public:
    MyObject(const char* name) : name_(name) {
        std::cout << "MyObject constructed: " << name_ << std::endl;
    }
    
    ~MyObject() {
        std::cout << "MyObject destroyed: " << name_ << std::endl;
    }
    
    void doSomething() {
        std::cout << "MyObject " << name_ << " doing something" << std::endl;
    }

private:
    const char* name_;
};

int main() {
    xxWeakPtr<MyObject> weakPtr;
    
    {
        auto obj = std::make_unique<MyObject>("test");
        weakPtr = obj.get();
        
        if (auto ptr = weakPtr.get()) {
            ptr->doSomething();
        }
    }
    
    if (weakPtr.expired()) {
        std::cout << "Weak pointer is expired" << std::endl;
    }
    
    return 0;
} 