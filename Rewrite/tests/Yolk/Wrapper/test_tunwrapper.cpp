#include <gtest/gtest.h>
#include "../../../src/Yolk/Core/Core.h"
#include <functional>

void TyA(int, int)
{
    return;   
}
TEST(Yolk_Test, Typed_Unwrapper_Test_A)
{
    Yolk::Memory::DynamicMemory manager;
    std::function<void(int, int)> f = TyA;

    auto i1 = manager.AllocateMemory<int>(1);
    auto i2 = manager.AllocateMemory<int>(1);

    Yolk::WrapperArgument p = {i1.wrapper,i2.wrapper};

    auto out = Yolk::ArgumentUnwrapper::Unwrap<void, int, int>::Run(manager, f, p);    
    EXPECT_TRUE(out.ok);
}

int TyB(int x, int y)
{
    return x + y;   
}
TEST(Yolk_Test, Typed_Unwrapper_Test_B)
{
    Yolk::Memory::DynamicMemory manager;
    std::function<int(int, int)> f = TyB;
    
    auto i1 = manager.AllocateMemory<int>(1);
    auto i2 = manager.AllocateMemory<int>(1);


    Yolk::WrapperArgument p = {i1.wrapper, i2.wrapper};

    auto o = Yolk::ArgumentUnwrapper::Unwrap<int, int, int>::Run(manager, f, p);
    EXPECT_TRUE(o.ok);
    EXPECT_EQ(o.wrapper.field->As<int>(), 2);
}



float TyC(float x, int y)
{
    return x - y;   
}
TEST(Yolk_Test, Typed_Unwrapper_Test_C)
{
    Yolk::Memory::DynamicMemory manager;
    std::function<float(float, int)> f = TyC;
    
    auto i1 = manager.AllocateMemory<float>(7.2);
    auto i2 = manager.AllocateMemory<int>(5);

    Yolk::WrapperArgument p = {i1.wrapper, i2.wrapper};

    auto m = Yolk::ArgumentUnwrapper::Unwrap<float, float, int>::Run(manager, f, p);

    EXPECT_TRUE(m.ok);
    EXPECT_FLOAT_EQ(m.wrapper.field->As<float>(), 2.2);
}

struct Helper
{
    int a;
};

Helper TyD(int x, int y)
{
    Helper o;
    if(x + y == 0)
        o.a = 5;
    else
        o.a = 6;
    return o;
}

TEST(Yolk_Test, Typed_Unwrapper_Test_D)
{
    Yolk::Memory::DynamicMemory manager;
    std::function<Helper(int, int)> f = TyD;
    
    auto i1 = manager.AllocateMemory<int>(-1);
    auto i2 = manager.AllocateMemory<int>(1);

    Yolk::WrapperArgument p = {i1.wrapper, i2.wrapper};

    auto m = Yolk::ArgumentUnwrapper::Unwrap<Helper, int, int>::Run(manager, f, p);

    EXPECT_TRUE(m.ok);
    EXPECT_EQ(m.wrapper.field->As<Helper>().a, 5);
}


TEST(Yolk_Test, Typed_Unwrapper_Test_E)
{
    Yolk::Memory::DynamicMemory manager;
    std::function<Helper(int, int)> f = TyD;
    
    auto i1 = manager.AllocateMemory<int>(-5);
    auto i2 = manager.AllocateMemory<int>(-7);

    Yolk::WrapperArgument p = {i1.wrapper, i2.wrapper};
    
    auto m = Yolk::ArgumentUnwrapper::Unwrap<Helper, int, int>::Run(manager, f, p);

    EXPECT_TRUE(m.ok);
    EXPECT_EQ(m.wrapper.field->As<Helper>().a, 6);
}
