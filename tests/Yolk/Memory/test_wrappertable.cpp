#include <gtest/gtest.h>
#include "../../../src/Yolk/Memory/Memory/Tables/WrapperTable.h"
#include "../../../src/Yolk/Wrapper/WrapperGenerator.h"

TEST(Yolk_Test, Wrapper_Table_Add_Field)
{
    Yolk::Memory::MemoryManager manager;

    auto i1 = manager.AllocateMemory<int>(12);
    auto i2 = manager.AllocateMemory<float>(3.14);

    Yolk::Memory::WrapperTable wtable(manager);

    auto id1 = wtable.Add(i1);
    auto id2 = wtable.Add(i2);

    EXPECT_EQ(manager.ChangeAudience(i1.ID, 0), 2);
    EXPECT_EQ(manager.ChangeAudience(i2.ID, 0), 2);

    EXPECT_EQ(id1, 0);
    EXPECT_EQ(id2, 1);

    EXPECT_EQ(wtable.Size(), 2);
}
TEST(Yolk_Test, Wrapper_Table_Add_Field_2)
{
    Yolk::Memory::MemoryManager manager;
    auto i1 = manager.AllocateMemory<int>(12);
    auto i2 = manager.AllocateMemory<float>(3.14);

    Yolk::Memory::WrapperTable wtable(manager);

    auto id1 = wtable.Add(i1);
    auto id2 = wtable.Add(i2);

    std::cout << i1.ID << " - " << i2.ID << std::endl;
    std::cout << id1 << " - " << id2 << std::endl;

    EXPECT_EQ(manager.ChangeAudience(i1.ID, 0), 2);
    EXPECT_EQ(manager.ChangeAudience(i2.ID, 0), 2);

    wtable.Erase(id1);

    EXPECT_EQ(manager.ChangeAudience(i1.ID, 0), 1);
    EXPECT_EQ(manager.ChangeAudience(i2.ID, 0), 2);

    auto id3 = wtable.Add(manager.AllocateMemory<int>(18));

    EXPECT_EQ(wtable.Size(), 3);
    EXPECT_EQ(manager.ChangeAudience(i2.ID + 1, 0), 1);

    wtable.Erase(id3);
    EXPECT_EQ(manager.ChangeAudience(i2.ID + 1, 0), 0);
}
int test_wraptable(int x)
{
    return x + 3;
}
TEST(Yolk_Test, Wrapper_Table_Add_Method)
{
    Yolk::Memory::MemoryManager manager;
    std::function<int(int)> f = test_wraptable;
    auto i1 = Yolk::WrapperGenerator<int, int>::GenerateMethodWrapper(f, manager);
    auto i2 = Yolk::WrapperGenerator<int, int>::GenerateMethodWrapper(f, manager);

    Yolk::Memory::WrapperTable wtable(manager);

    auto id1 = wtable.Add(i1);
    wtable.Add(i2);

    EXPECT_EQ(manager.ChangeAudience(i1.ID, 0), 2);
    EXPECT_EQ(manager.ChangeAudience(i2.ID, 0), 2);

    wtable.Erase(id1);

    EXPECT_EQ(manager.ChangeAudience(i1.ID, 0), 1);
    EXPECT_EQ(manager.ChangeAudience(i2.ID, 0), 2);

    auto id3 = wtable.Add(manager.AllocateMemory<int>(18));

    EXPECT_EQ(wtable.Size(), 3);
    EXPECT_EQ(manager.ChangeAudience(i2.ID + 1, 0), 1);

    wtable.Erase(id3);
    EXPECT_EQ(manager.ChangeAudience(i2.ID + 1, 0), 0);
}
TEST(Yolk_Test, Wrapper_Table_Erase)
{
    Yolk::Memory::MemoryManager manager;
    Yolk::Memory::WrapperTable table(manager);

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
    EXPECT_EQ(table.Size(), 5);

    table.Erase(a);
    table.Erase(d);

    EXPECT_EQ(manager.Size(), 0);
    EXPECT_EQ(table.Size(), 5);
}
TEST(Yolk_Test, Wrapper_Table_Copy_Field)
{
    Yolk::Memory::MemoryManager manager;
    Yolk::Memory::WrapperTable table(manager);

    auto id = table.Add(manager.AllocateMemory<int>(121));
    auto cp = table.CopyField(id);

    EXPECT_EQ(manager.Size(), 1);
    EXPECT_EQ(manager.ChangeAudience(1, 0), 2);

    EXPECT_STREQ(cp.field->Print().c_str(), "121");
    EXPECT_EQ(cp.field->As<int>(), 121);

    table.Erase(id);
    EXPECT_EQ(manager.ChangeAudience(1, 0), 1);
}
TEST(Yolk_Test, Wrapper_Table_Copy_Method)
{
    Yolk::Memory::MemoryManager manager;
    Yolk::Memory::WrapperTable table(manager);
    std::function<int(int)> f = test_wraptable; // f(x) = x + 3;

    Yolk::MethodWrapper i1 = Yolk::WrapperGenerator<int, int>::GenerateMethodWrapper(f, manager);
    auto id = table.Add(i1);
    Yolk::MethodWrapper wrap = table.CopyMethod(id);

    Yolk::Wrapper p = manager.AllocateMemory<int>(-12);
    Yolk::ArgumentWrapper i = {p};

    auto o = wrap.Invoke(i);

    std::cout << o.Message << std::endl;
    EXPECT_TRUE(o.ok);
    EXPECT_EQ(o.output.field->As<int>(), -9);
}