#include <gtest/gtest.h>
#include "../../../src/Yolk/Core/Core.h"
#include <functional>

void  MTyA(int, int)
{
    return;   
}
TEST(MethodWrapper, Void_IntInt)
{
    Yolk::Memory::DynamicMemory manager;
    std::function<void(int, int)> f =  MTyA;

    auto i1 = manager.AllocateMemory<int>(1);
    auto i2 = manager.AllocateMemory<int>(1);

    Yolk::WrapperArgument p = {i1,i2};

    auto m = Yolk::WrapperGenerator<void, int, int>::GenerateMethodWrapper(manager, f);
    auto out = m.Invoke(p);
}


int  MTyB(int x, int y)
{
    return x + y;   
}
TEST(MethodWrapper, Int_IntInt)
{
    Yolk::Memory::DynamicMemory manager;
    std::function<int(int, int)> f =  MTyB;

    auto i1 = manager.AllocateMemory<int>(1);
    auto i2 = manager.AllocateMemory<int>(1);

    Yolk::WrapperArgument p = {i1,i2};

    auto m = Yolk::WrapperGenerator<int, int, int>::GenerateMethodWrapper(manager, f);
    auto out = m.Invoke(p);
    
    EXPECT_EQ(out.field->As<int>(), 2);
}



float  MTyC(float x, int y)
{
    return x - y;   
}
TEST(MethodWrapper, Float_FloatInt)
{
    Yolk::Memory::DynamicMemory manager;
    
    std::function<float(float, int)> f =  MTyC;
    
    auto i1 = manager.AllocateMemory<float>(7.2);
    auto i2 = manager.AllocateMemory<int>(5);
    Yolk::WrapperArgument p = {i1, i2};

    Yolk::MethodWrapper m = manager.AllocateMemory<std::function<float(float, int)>>(f);
    m.InstantiateWrapper<float, float, int>(f);

    auto wrapper = m.Invoke(p);

    EXPECT_FLOAT_EQ(wrapper.field->As<float>(), 2.2);
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

TEST(MethodWrapper, Struct_IntInt)
{
    Yolk::Memory::DynamicMemory manager;
    std::function<Helper(int, int)> f =  MTyD;
    
    auto i1 = manager.AllocateMemory<int>(-1);
    auto i2 = manager.AllocateMemory<int>(1);
    Yolk::WrapperArgument p = {i1, i2};

    auto m = Yolk::WrapperGenerator<Helper, int, int>::GenerateMethodWrapper(manager, f);
    auto out = m.Invoke(p);
    EXPECT_EQ(out.field->As<Helper>().a, 5);
}


TEST(MethodWrapper, Struct_IntInt2)
{
    Yolk::Memory::DynamicMemory manager;
    std::function<Helper(int, int)> f =  MTyD;
    
    auto i1 = manager.AllocateMemory<int>(-5);
    auto i2 = manager.AllocateMemory<int>(-7);
    Yolk::WrapperArgument p = {i1, i2};
    
    auto m = Yolk::WrapperGenerator<Helper, int, int>::GenerateMethodWrapper(manager, f);
    auto out = m.Invoke(p); 
    EXPECT_EQ(out.field->As<Helper>().a, 6);
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
TEST(MethodWrapper, Clone)
{
    Yolk::Memory::DynamicMemory manager;
    Yolk::TypedField::Pointer pointer = std::make_shared<Yolk::TypedField>();
    Yolk::MethodWrapper wrap(0, pointer, manager);

    Func(wrap, manager);

    EXPECT_TRUE(wrap.IsValid());
}
TEST(MethodWrapper, By_Reference)
{
    Yolk::Memory::DynamicMemory manager;
    auto fa = Yolk::WrapperGenerator<int, int, int>::GenerateMethodWrapper(manager, MTyB);

    auto i1 = manager.AllocateMemory<int>(7);
    auto i2 = manager.AllocateMemory<int>(5);

    Yolk::WrapperArgument a;
    a << i1 << i2;

    Yolk::MethodWrapper m(fa);
    
    EXPECT_EQ(manager.ViewersCount(fa.ID), 2);
    auto out = m.Invoke(a);


    EXPECT_EQ(out.field->As<int>(), 12);

}
TEST(MethodWrapper, By_Equality)
{
    Yolk::Memory::DynamicMemory manager;
    auto fa = Yolk::WrapperGenerator<int, int, int>::GenerateMethodWrapper(manager, MTyB);
    auto fb = Yolk::WrapperGenerator<float, float, int>::GenerateMethodWrapper(manager, MTyC);

    auto i1 = manager.AllocateMemory<int>(7);
    auto i2 = manager.AllocateMemory<int>(5);
    auto f1 = manager.AllocateMemory<float>(3.12f);

    Yolk::WrapperArgument a;
    a << i1 << i2;

    Yolk::MethodWrapper m = Yolk::MethodWrapper(manager.GetVoidWrapper());

    m = fa;
    auto out = m.Invoke(a);
    EXPECT_EQ(manager.ViewersCount(fa.ID), 2);
    EXPECT_EQ(manager.ViewersCount(fb.ID), 1);
    EXPECT_EQ(out.field->As<int>(), 12);


    m = fb;
    a.clear();
    a << f1 << i1;
    out = m.Invoke(a);

    EXPECT_EQ(manager.ViewersCount(fa.ID), 1);
    EXPECT_EQ(manager.ViewersCount(fb.ID), 2);
    EXPECT_FLOAT_EQ(out.field->As<float>(), -3.88);
}
