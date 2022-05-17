#include <gtest/gtest.h>
#include "../../../src/Yolk/Yolk.h"

TEST(Yolk_Test, WrapperGenerator_Dynamic_Field)
{
    Yolk::Memory::MemoryManager manager;
    auto o = Yolk::WrapperGenerator<int>::GenerateDynamicWrapper(127, manager);

    EXPECT_TRUE(o.field->Valid());
    EXPECT_EQ(o.field->As<int>(), 127);
    EXPECT_EQ(manager.ChangeAudience(1, 0), 1);
}

TEST(Yolk_Test, WrapperGenerator__Static_Field)
{
    Yolk::Memory::MemoryManager manager;
    int x = 12;
    
    
    auto o = Yolk::WrapperGenerator<int>::GenerateStaticWrapper(x, manager);


    EXPECT_TRUE(o.field->Valid());
    EXPECT_EQ(o.field->As<int>(), 12);
    EXPECT_EQ(manager.ChangeAudience(1, 0), 1);

    *o.field = 15;
    EXPECT_EQ(x, 15);
}

TEST(Yolk_Test, WrapperGenerator__Method)
{
    Yolk::Memory::MemoryManager manager;
    auto o = Yolk::WrapperGenerator<int, int>::GenerateMethodWrapper([](int x){return x + 3;}, manager);

    auto i = Yolk::WrapperGenerator<int>::GenerateDynamicWrapper(19, manager);
    Yolk::ArgumentWrapper a = {i};

    auto result = o.Invoke(a);

    EXPECT_TRUE(result.ok);
    EXPECT_EQ(result.output.field->As<int>(), 22);
}

TEST(Yolk_Test, Wrapper_Generator_Argument)
{
    Yolk::Memory::MemoryManager manager;
    auto o = Yolk::WrapperGenerator<int, int, int>::GenerateMethodWrapper([](int x, int y){return x + y;}, manager);
    auto i1 = Yolk::WrapperGenerator<int>::GenerateDynamicWrapper(5, manager);
    auto i2 = Yolk::WrapperGenerator<int>::GenerateDynamicWrapper(-5, manager);

    auto i = Yolk::WrapperGenerator<>::GenerateArgumentWrapper(i1, i2);

    auto result = o.Invoke(i);    
    
    EXPECT_TRUE(result.ok);
    EXPECT_EQ(result.output.field->As<int>(), 0);

}