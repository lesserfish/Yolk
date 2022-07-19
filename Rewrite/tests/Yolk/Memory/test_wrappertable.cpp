#include <gtest/gtest.h>
#include "../../../src/Yolk/Memory/MemoryTable.h"
#include "../../../src/Yolk/Core/Core.h"

TEST(Yolk_Test, Wrapper_Table_Add_Field)
{
    Yolk::Memory::DynamicMemory manager;

    auto i1 = manager.AllocateMemory<int>(12);
    auto i2 = manager.AllocateMemory<float>(3.14);

    Yolk::Memory::MemoryTable wtable(manager);

    auto id1 = wtable.Add(i1);
    auto id2 = wtable.Add(i2);

    EXPECT_EQ(manager.ViewersCount(i1.ID), 2);
    EXPECT_EQ(manager.ViewersCount(i2.ID), 2);

    EXPECT_EQ(id1, 0);
    EXPECT_EQ(id2, 1);

    EXPECT_EQ(wtable.Size(), 2);
}
TEST(Yolk_Test, Wrapper_Table_Add_Field_2)
{
    Yolk::Memory::DynamicMemory manager;
    auto i1 = manager.AllocateMemory<int>(12);
    auto i2 = manager.AllocateMemory<float>(3.14);

    Yolk::Memory::MemoryTable wtable(manager);

    auto id1 = wtable.Add(i1);
    wtable.Add(i2);

    EXPECT_EQ(manager.ViewersCount(i1.ID), 2);
    EXPECT_EQ(manager.ViewersCount(i2.ID), 2);

    wtable.Erase(id1);

    EXPECT_EQ(manager.ViewersCount(i1.ID), 1);
    EXPECT_EQ(manager.ViewersCount(i2.ID), 2);

    auto id3 = wtable.Add(manager.AllocateMemory<int>(18));

    EXPECT_EQ(wtable.Size(), 2);
    EXPECT_EQ(manager.ViewersCount(i2.ID + 1), 1);

    wtable.Erase(id3);
    EXPECT_EQ(manager.ViewersCount(i2.ID + 1), 0);
}
int test_wraptable(int x)
{
    return x + 3;
}
TEST(Yolk_Test, Wrapper_Table_Add_Method)
{
    Yolk::Memory::DynamicMemory manager;
    std::function<int(int)> f = test_wraptable;
    auto i1 = Yolk::WrapperGenerator<int, int>::GenerateMethodWrapper(manager, f);
    auto i2 = Yolk::WrapperGenerator<int, int>::GenerateMethodWrapper(manager, f);

    Yolk::Memory::MemoryTable wtable(manager);

    auto id1 = wtable.Add(i1);
    wtable.Add(i2);

    EXPECT_EQ(manager.ViewersCount(i1.ID), 2);
    EXPECT_EQ(manager.ViewersCount(i2.ID), 2);

    wtable.Erase(id1);

    EXPECT_EQ(manager.ViewersCount(i1.ID), 1);
    EXPECT_EQ(manager.ViewersCount(i2.ID), 2);

    auto id3 = wtable.Add(manager.AllocateMemory<int>(18));

    EXPECT_EQ(wtable.Size(), 2);
    EXPECT_EQ(manager.ViewersCount(i2.ID + 1), 1);

    wtable.Erase(id3);
    EXPECT_EQ(manager.ViewersCount(i2.ID + 1), 0);
}
TEST(Yolk_Test, Wrapper_Table_Erase)
{
    Yolk::Memory::DynamicMemory manager;
    Yolk::Memory::MemoryTable table(manager);

    auto a = table.Add(manager.AllocateMemory<int>(1));
    auto b = table.Add(manager.AllocateMemory<int>(1));
    auto c = table.Add(manager.AllocateMemory<int>(1));
    auto d = table.Add(manager.AllocateMemory<int>(1));
    auto e = table.Add(manager.AllocateMemory<int>(1));

    EXPECT_EQ(a, 0);
    EXPECT_EQ(b, 1);
    EXPECT_EQ(c, 2);
    EXPECT_EQ(d, 3);
    EXPECT_EQ(e, 4);

    EXPECT_EQ(manager.Size(), 5);
    EXPECT_EQ(table.Size(), 5);

    table.Erase(b);

    table.Erase(c);
    table.Erase(e);

    EXPECT_EQ(manager.Size(), 2);
    EXPECT_EQ(table.Size(), 2);

    table.Erase(a);
    table.Erase(d);

    EXPECT_EQ(manager.Size(), 0);
    EXPECT_EQ(table.Size(), 0);
}
TEST(Yolk_Test, Wrapper_Table_Get_Field)
{
    Yolk::Memory::DynamicMemory manager;
    Yolk::Memory::MemoryTable table(manager);

    auto id = table.Add(manager.AllocateMemory<int>(121));
    auto cp = table.GetField(id).wrapper;

    EXPECT_EQ(manager.Size(), 1);
    EXPECT_EQ(manager.ViewersCount(1), 2);

    EXPECT_STREQ(cp.field->Print().c_str(), "121");
    EXPECT_EQ(cp.field->As<int>(), 121);

    table.Erase(id);
    EXPECT_EQ(manager.ViewersCount(1), 1);
}
TEST(Yolk_Test, Wrapper_Table_Get_Method)
{
    Yolk::Memory::DynamicMemory manager;
    Yolk::Memory::MemoryTable table(manager);
    std::function<int(int)> f = test_wraptable; // f(x) = x + 3;

    Yolk::MethodWrapper i1 = Yolk::WrapperGenerator<int, int>::GenerateMethodWrapper(manager, f);
    auto id = table.Add(i1);
    Yolk::MethodWrapper wrap = table.GetMethod(id).wrapper;

    Yolk::Wrapper p = manager.AllocateMemory<int>(-12);
    Yolk::WrapperArgument i = {p};

    auto o = wrap.Invoke(i);

    EXPECT_EQ(o.field->As<int>(), -9);
}
TEST(Yolk_Test, Wrapper_Table_Unset_Method)
{
    Yolk::Memory::DynamicMemory manager;
    Yolk::Memory::MemoryTable table(manager);
    Yolk::Memory::MemoryInterface* interface;

    auto key = table.Add(interface);

    auto out = table.GetMemory(key);
    EXPECT_EQ(out.memory, interface);

    table.UnsetMemoryPointer(interface);
    
    bool ok = true;
    try {
        table.GetMemory(key);
    } catch(const Yolk::Memory::MException&) 
    {
        ok = false;
    }
    EXPECT_FALSE(ok);
}
