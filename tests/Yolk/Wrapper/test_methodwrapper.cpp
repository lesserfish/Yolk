#include <gtest/gtest.h>
#include "../../../src/Yolk/Yolk.h"
#include <functional>

void  MTyA(int, int)
{
    return;   
}
TEST(Yolk_Test, Method_Wrapper_Test_A)
{
    Yolk::Memory::MemoryManager manager;
    std::function<void(int, int)> f =  MTyA;

    auto i1 = manager.AllocateMemory<int>(1);
    auto i2 = manager.AllocateMemory<int>(1);

    Yolk::ArgumentWrapper p = {i1,i2};

    auto m = Yolk::WrapperGenerator<void, int, int>::GenerateMethodWrapper(f, manager);
    auto out = m.Invoke(p);
}


int  MTyB(int x, int y)
{
    return x + y;   
}
TEST(Yolk_Test, Method_Wrapper_Test_B)
{
    Yolk::Memory::MemoryManager manager;
    std::function<int(int, int)> f =  MTyB;

    auto i1 = manager.AllocateMemory<int>(1);
    auto i2 = manager.AllocateMemory<int>(1);

    Yolk::ArgumentWrapper p = {i1,i2};

    auto m = Yolk::WrapperGenerator<int, int, int>::GenerateMethodWrapper(f, manager);
    auto out = m.Invoke(p);
    
    EXPECT_EQ(out.output.field->As<int>(), 2);
}



float  MTyC(float x, int y)
{
    return x - y;   
}
TEST(Yolk_Test, Method_Wrapper_Test_C)
{
    Yolk::Memory::MemoryManager manager;
    
    std::function<float(float, int)> f =  MTyC;
    
    auto i1 = manager.AllocateMemory<float>(7.2);
    auto i2 = manager.AllocateMemory<int>(5);
    Yolk::ArgumentWrapper p = {i1, i2};

    Yolk::MethodWrapper m = manager.AllocateMemory<std::function<float(float, int)>>();
    m.InstantiateWrapper(f);

    auto output = m.Invoke(p);

    EXPECT_FLOAT_EQ(output.output.field->As<float>(), 2.2);
    EXPECT_TRUE(output.ok);
}

struct Helper
{
    int a;
};

Helper  MTyD(int x, int y)
{
    Helper o;
    if(x + y == 0)
        o.a = 5;
    else
        o.a = 6;
    return o;
}

TEST(Yolk_Test, Method_Wrapper_Test_D)
{
    Yolk::Memory::MemoryManager manager;
    std::function<Helper(int, int)> f =  MTyD;
    
    auto i1 = manager.AllocateMemory<int>(-1);
    auto i2 = manager.AllocateMemory<int>(1);
    Yolk::ArgumentWrapper p = {i1, i2};

    auto m = Yolk::WrapperGenerator<Helper, int, int>::GenerateMethodWrapper(f, manager);
    auto out = m.Invoke(p);
    EXPECT_EQ(out.output.field->As<Helper>().a, 5);
    EXPECT_TRUE(out.ok);
}


TEST(Yolk_Test, Method_Wrapper_Test_E)
{
    Yolk::Memory::MemoryManager manager;
    std::function<Helper(int, int)> f =  MTyD;
    
    auto i1 = manager.AllocateMemory<int>(-5);
    auto i2 = manager.AllocateMemory<int>(-7);
    Yolk::ArgumentWrapper p = {i1, i2};
    
    auto m = Yolk::WrapperGenerator<Helper, int, int>::GenerateMethodWrapper(f, manager);
    auto out = m.Invoke(p); 
    EXPECT_EQ(out.output.field->As<Helper>().a, 6);
    EXPECT_TRUE(out.ok);
}

void f(){}
void Func(Yolk::MethodWrapper& w1, Yolk::Memory::MemoryManager &manager)
{
    auto func = std::function<void()>(f);
    auto o1 = Yolk::WrapperGenerator<void>::GenerateMethodWrapper(func, manager);

    EXPECT_TRUE(o1.IsValid());
    EXPECT_FALSE(w1.IsValid());
    w1 = o1;
    EXPECT_TRUE(w1.IsValid());
}
TEST(Yolk_Test, Method_Wrapper_Clone)
{
    Yolk::Memory::MemoryManager manager;
    Yolk::TypedField::Pointer pointer = std::make_shared<Yolk::TypedField>();
    Yolk::MethodWrapper wrap(0, pointer, manager);

    Func(wrap, manager);

    EXPECT_TRUE(wrap.IsValid());
}