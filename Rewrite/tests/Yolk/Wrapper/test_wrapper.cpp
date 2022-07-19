#include <gtest/gtest.h>
#include "../../../src/Yolk/Core/Core.h"

TEST(Yolk_Test, Wrapper_FromReference)
{
    Yolk::Memory::DynamicMemory manager;
    auto wrapperA = manager.AllocateMemory<int>(7);

    Yolk::Wrapper fromref(wrapperA);

    EXPECT_EQ(fromref.ID, wrapperA.ID);
    EXPECT_EQ(fromref.field->As<int>(), 7);
    EXPECT_EQ(manager.UpdateViewersCount(wrapperA.ID, 0), 2);
}

TEST(Yolk_Test, Wrapper_FromEquality)
{
    Yolk::Memory::DynamicMemory manager;

    auto a = manager.AllocateMemory<int>(12);
    auto b = manager.AllocateMemory<int>(17);

    Yolk::Wrapper wrapper(manager.GetVoidWrapper());
    EXPECT_TRUE(wrapper.field->IsNone());
    EXPECT_EQ(manager.ViewersCount(a.ID), 1);
    EXPECT_EQ(manager.ViewersCount(b.ID), 1);

    wrapper = a;
    EXPECT_EQ(wrapper.field->As<int>(), 12);
    EXPECT_EQ(manager.ViewersCount(a.ID), 2);
    EXPECT_EQ(manager.ViewersCount(b.ID), 1);
   
    wrapper = b;
    EXPECT_EQ(wrapper.field->As<int>(), 17);
    EXPECT_EQ(manager.ViewersCount(a.ID), 1);
    EXPECT_EQ(manager.ViewersCount(b.ID), 2);
}
