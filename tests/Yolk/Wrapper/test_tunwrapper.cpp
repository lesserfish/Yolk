#include <gtest/gtest.h>
#include "../../../src/Yolk/Yolk/Yolk.h"
#include <functional>

void TyA(int, int)
{
    return;   
}
TEST(Yolk_Test, Typed_Unwrapper_Test_A)
{
    Yolk::Memory::MemoryManager manager;
    std::function<void(int, int)> f = TyA;

    auto i1 = manager.AllocateMemory<int>(1);
    auto i2 = manager.AllocateMemory<int>(1);

    Yolk::ArgumentWrapper p = {i1,i2};

    auto o = manager.AllocateMemory<void>();

    Yolk::ArgumentUnwrapper::Unwrap<void, int, int>::Run(f, o, p);    
}


int TyB(int x, int y)
{
    return x + y;   
}
TEST(Yolk_Test, Typed_Unwrapper_Test_B)
{
    Yolk::Memory::MemoryManager manager;
    std::function<int(int, int)> f = TyB;
    
    auto i1 = manager.AllocateMemory<int>(1);
    auto i2 = manager.AllocateMemory<int>(1);


    Yolk::ArgumentWrapper p = {i1,i2};

    auto o = manager.AllocateMemory<int>();
    
    Yolk::ArgumentUnwrapper::Unwrap<int, int, int>::Run(f, o, p);

    EXPECT_EQ(o.field->As<int>(), 2);
}



float TyC(float x, int y)
{
    return x - y;   
}
TEST(Yolk_Test, Typed_Unwrapper_Test_C)
{
    Yolk::Memory::MemoryManager manager;
    std::function<float(float, int)> f = TyC;
    
    auto i1 = manager.AllocateMemory<float>(7.2);
    auto i2 = manager.AllocateMemory<int>(5);

    Yolk::ArgumentWrapper p = {i1, i2};

    auto o = manager.AllocateMemory<float>();

    auto m = Yolk::ArgumentUnwrapper::Unwrap<float, float, int>::Run(f, o, p);

    EXPECT_FLOAT_EQ(o.field->As<float>(), 2.2);
    EXPECT_TRUE(m.ok);
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
    Yolk::Memory::MemoryManager manager;
    std::function<Helper(int, int)> f = TyD;
    
    auto i1 = manager.AllocateMemory<int>(-1);
    auto i2 = manager.AllocateMemory<int>(1);

    Yolk::ArgumentWrapper p = {i1, i2};

    auto o = manager.AllocateMemory<Helper>();
    
    auto m = Yolk::ArgumentUnwrapper::Unwrap<Helper, int, int>::Run(f, o, p);

    EXPECT_EQ(o.field->As<Helper>().a, 5);
    EXPECT_TRUE(m.ok);
}


TEST(Yolk_Test, Typed_Unwrapper_Test_E)
{
    Yolk::Memory::MemoryManager manager;
    std::function<Helper(int, int)> f = TyD;
    
    auto i1 = manager.AllocateMemory<int>(-5);
    auto i2 = manager.AllocateMemory<int>(-7);

    Yolk::ArgumentWrapper p = {i1, i2};
    
    
    auto o = manager.AllocateMemory<Helper>();

    auto m = Yolk::ArgumentUnwrapper::Unwrap<Helper, int, int>::Run(f, o, p);

    EXPECT_EQ(o.field->As<Helper>().a, 6);
    EXPECT_TRUE(m.ok);
}
