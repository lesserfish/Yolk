#include <gtest/gtest.h>
#include "../../../src/Yolk/Core/Core.h"
#include <functional>

void  MTyA(int, int)
{
    return;   
}
TEST(Yolk_Test, Method_Wrapper_Test_A)
{
    Yolk::Memory::DynamicMemory manager;
    std::function<void(int, int)> f =  MTyA;

    auto i1 = manager.AllocateMemory<int>(1).wrapper;
    auto i2 = manager.AllocateMemory<int>(1).wrapper;

    Yolk::WrapperArgument p = {i1,i2};

    auto m = Yolk::WrapperGenerator<void, int, int>::GenerateMethodWrapper(manager, f);
    auto out = m.Invoke(p);
}


int  MTyB(int x, int y)
{
    return x + y;   
}
TEST(Yolk_Test, Method_Wrapper_Test_B)
{
    Yolk::Memory::DynamicMemory manager;
    std::function<int(int, int)> f =  MTyB;

    auto i1 = manager.AllocateMemory<int>(1).wrapper;
    auto i2 = manager.AllocateMemory<int>(1).wrapper;

    Yolk::WrapperArgument p = {i1,i2};

    auto m = Yolk::WrapperGenerator<int, int, int>::GenerateMethodWrapper(manager, f);
    auto out = m.Invoke(p);
    
    EXPECT_EQ(out.wrapper.field->As<int>(), 2);
}



float  MTyC(float x, int y)
{
    return x - y;   
}
TEST(Yolk_Test, Method_Wrapper_Test_C)
{
    Yolk::Memory::DynamicMemory manager;
    
    std::function<float(float, int)> f =  MTyC;
    
    auto i1 = manager.AllocateMemory<float>(7.2).wrapper;
    auto i2 = manager.AllocateMemory<int>(5).wrapper;
    Yolk::WrapperArgument p = {i1, i2};

    Yolk::MethodWrapper m = manager.AllocateMemory<std::function<float(float, int)>>(f).wrapper;
    m.InstantiateWrapper<float, float, int>(f);

    //auto wrapper = m.Invoke(p);

    //EXPECT_FLOAT_EQ(wrapper.wrapper.field->As<float>(), 2.2);
    //EXPECT_TRUE(wrapper.ok);
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
    Yolk::Memory::DynamicMemory manager;
    std::function<Helper(int, int)> f =  MTyD;
    
    auto i1 = manager.AllocateMemory<int>(-1).wrapper;
    auto i2 = manager.AllocateMemory<int>(1).wrapper;
    Yolk::WrapperArgument p = {i1, i2};

    auto m = Yolk::WrapperGenerator<Helper, int, int>::GenerateMethodWrapper(manager, f);
    auto out = m.Invoke(p);
    EXPECT_EQ(out.wrapper.field->As<Helper>().a, 5);
    EXPECT_TRUE(out.ok);
}


TEST(Yolk_Test, Method_Wrapper_Test_E)
{
    Yolk::Memory::DynamicMemory manager;
    std::function<Helper(int, int)> f =  MTyD;
    
    auto i1 = manager.AllocateMemory<int>(-5).wrapper;
    auto i2 = manager.AllocateMemory<int>(-7).wrapper;
    Yolk::WrapperArgument p = {i1, i2};
    
    auto m = Yolk::WrapperGenerator<Helper, int, int>::GenerateMethodWrapper(manager, f);
    auto out = m.Invoke(p); 
    EXPECT_EQ(out.wrapper.field->As<Helper>().a, 6);
    EXPECT_TRUE(out.ok);
}

void f(){}
void Func(Yolk::MethodWrapper& w1, Yolk::Memory::DynamicMemory &manager)
{
    auto func = std::function<void()>(f);
    auto o1 = Yolk::WrapperGenerator<void>::GenerateMethodWrapper(manager, func);

    EXPECT_TRUE(o1.IsValid());
    EXPECT_FALSE(w1.IsValid());
    w1 = o1;
    EXPECT_TRUE(w1.IsValid());
}
TEST(Yolk_Test, Method_Wrapper_Clone)
{
    Yolk::Memory::DynamicMemory manager;
    Yolk::TypedField::Pointer pointer = std::make_shared<Yolk::TypedField>();
    Yolk::MethodWrapper wrap(0, pointer, manager);

    Func(wrap, manager);

    EXPECT_TRUE(wrap.IsValid());
}
TEST(Yolk_Test, Method_Wrapper_By_Reference)
{
    Yolk::Memory::DynamicMemory manager;
    auto fa = Yolk::WrapperGenerator<int, int, int>::GenerateMethodWrapper(manager, MTyB);

    auto i1 = manager.AllocateMemory<int>(7).wrapper;
    auto i2 = manager.AllocateMemory<int>(5).wrapper;

    Yolk::WrapperArgument a;
    a << i1 << i2;

    Yolk::MethodWrapper m(fa);
    
    EXPECT_EQ(manager.ViewersCount(fa.ID), 2);
    auto out = m.Invoke(a);

    EXPECT_TRUE(out.ok);

    EXPECT_EQ(out.wrapper.field->As<int>(), 12);

}
TEST(Yolk_Test, Method_Wrapper_By_Equality)
{
    Yolk::Memory::DynamicMemory manager;
    auto fa = Yolk::WrapperGenerator<int, int, int>::GenerateMethodWrapper(manager, MTyB);
    auto fb = Yolk::WrapperGenerator<float, float, int>::GenerateMethodWrapper(manager, MTyC);

    auto i1 = manager.AllocateMemory<int>(7).wrapper;
    auto i2 = manager.AllocateMemory<int>(5).wrapper;
    auto f1 = manager.AllocateMemory<float>(3.12f).wrapper;

    Yolk::WrapperArgument a;
    a << i1 << i2;

    Yolk::MethodWrapper m = Yolk::MethodWrapper(manager.GetVoidWrapper());

    m = fa;
    auto out = m.Invoke(a);
    EXPECT_EQ(manager.ViewersCount(fa.ID), 2);
    EXPECT_EQ(manager.ViewersCount(fb.ID), 1);
    EXPECT_TRUE(out.ok);
    EXPECT_EQ(out.wrapper.field->As<int>(), 12);


    m = fb;
    a.clear();
    a << f1 << i1;
    out = m.Invoke(a);

    EXPECT_EQ(manager.ViewersCount(fa.ID), 1);
    EXPECT_EQ(manager.ViewersCount(fb.ID), 2);
    EXPECT_TRUE(out.ok);
    EXPECT_FLOAT_EQ(out.wrapper.field->As<float>(), -3.88);
}
