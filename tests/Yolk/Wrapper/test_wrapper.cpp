#include <gtest/gtest.h>
#include "../../../src/Yolk/Yolk.h"

TEST(Yolk_Test, Wrapper_FromReference)
{
    Yolk::Memory::MemoryManager manager;
    auto wrapperA = manager.AllocateMemory<int>(7);

    Yolk::Wrapper fromref(wrapperA);

    EXPECT_EQ(fromref.ID, wrapperA.ID);
    EXPECT_EQ(fromref.field->As<int>(), 7);
    EXPECT_EQ(manager.ChangeAudience(wrapperA.ID, 0), 2);
}

TEST(Yolk_Test, Wrapper_FromEquality)
{
    Yolk::Memory::MemoryManager manager;

    auto a = manager.AllocateMemory<int>(12);
    auto b = manager.AllocateMemory<int>(17);

    Yolk::Wrapper wrapper(manager.GenerateVoidWrapper());
    EXPECT_FALSE(wrapper.field->Valid());
    EXPECT_EQ(manager.ChangeAudience(a.ID, 0), 1);
    EXPECT_EQ(manager.ChangeAudience(b.ID, 0), 1);

    wrapper = a;
    EXPECT_EQ(wrapper.field->As<int>(), 12);
    EXPECT_EQ(manager.ChangeAudience(a.ID, 0), 2);
    EXPECT_EQ(manager.ChangeAudience(b.ID, 0), 1);
   
    wrapper = b;
    EXPECT_EQ(wrapper.field->As<int>(), 17);
    EXPECT_EQ(manager.ChangeAudience(a.ID, 0), 1);
    EXPECT_EQ(manager.ChangeAudience(b.ID, 0), 2);
}
