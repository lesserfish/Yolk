#include <gtest/gtest.h>
#include "../../../src/Yolk/Core/Core.h"

TEST(Yolk_Test, WrapperGenerator_Dynamic_Field)
{
    Yolk::Memory::DynamicMemory manager;
    auto o = Yolk::WrapperGenerator<int>::GenerateDynamicWrapper(manager, 127);

    EXPECT_FALSE(o.field->IsNone());
    EXPECT_EQ(o.field->As<int>(), 127);
    EXPECT_EQ(manager.ViewersCount(o.ID), 1);
}

TEST(Yolk_Test, WrapperGenerator__Static_Field)
{
    Yolk::Memory::DynamicMemory manager;
    int x = 12;
    
    
    auto o = Yolk::WrapperGenerator<int>::GenerateStaticWrapper(manager, x);


    EXPECT_FALSE(o.field->IsNone());
    EXPECT_EQ(o.field->As<int>(), 12);

    *o.field = 15;
    EXPECT_EQ(x, 15);
}

TEST(Yolk_Test, WrapperGenerator__Method)
{
    Yolk::Memory::DynamicMemory manager;
    auto o = Yolk::WrapperGenerator<int, int>::GenerateMethodWrapper(manager, [](int x){return x + 3;});

    auto i = Yolk::WrapperGenerator<int>::GenerateDynamicWrapper(manager, 19);
    Yolk::WrapperArgument a = {i};

    auto result = o.Invoke(a);

    EXPECT_EQ(result.field->As<int>(), 22);
}

TEST(Yolk_Test, Wrapper_Generator_Argument)
{
    Yolk::Memory::DynamicMemory manager;
    auto o = Yolk::WrapperGenerator<int, int, int>::GenerateMethodWrapper(manager, [](int x, int y){return x + y;});
    auto i1 = Yolk::WrapperGenerator<int>::GenerateDynamicWrapper(manager, 5);
    auto i2 = Yolk::WrapperGenerator<int>::GenerateDynamicWrapper(manager, -5);

    auto i = Yolk::WrapperGenerator<>::GenerateWrapperArgument(i1, i2);

    auto result = o.Invoke(i);    
    
    EXPECT_EQ(result.field->As<int>(), 0);

}
