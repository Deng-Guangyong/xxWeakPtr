#include <gtest/gtest.h>
#include <memory>
#include <xxWeakPtr/xxWeakPtr.h>
#include <xxWeakPtr/xxRefObject.h>

class TestObject : public xxRefObject {
public:
    int value;
    TestObject(int v) : value(v) {}
};

TEST(WeakPtrTest, BasicUsage) {
    xxWeakPtr<TestObject> weakPtr;
    {
        auto obj = std::make_unique<TestObject>(42);
        weakPtr = obj.get();
        EXPECT_FALSE(weakPtr.expired());
        EXPECT_EQ(weakPtr.get()->value, 42);
        //EXPECT_EQ(weakPtr->value, 42);
    }
    EXPECT_TRUE(weakPtr.expired());
}

// 添加更多测试...
