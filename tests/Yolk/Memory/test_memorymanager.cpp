#include "../../../src/Yolk/Yolk.h"
#include <gtest/gtest.h>
#include <vector>

TEST(Yolk_Test, MemoryManager_Add)
{
    Yolk::Memory::MemoryManager manager;
    auto o = manager.AllocateMemory<int>();
    *(o.field) = 14;

    EXPECT_TRUE(manager.Exists(1));
}
void RemoveTest_B(Yolk::Memory::MemoryManager &manager)
{
    EXPECT_EQ(manager.Size(), 1);
    auto o = manager.AllocateMemory<float>();
    EXPECT_EQ(manager.Size(), 2);
}
void RemoveTest_A(Yolk::Memory::MemoryManager &manager)
{
    EXPECT_EQ(manager.Size(), 0);
    auto o = manager.AllocateMemory<float>();
    EXPECT_EQ(manager.Size(), 1);
    RemoveTest_B(manager);
    EXPECT_EQ(manager.Size(), 1);
}
TEST(Yolk_Test, MemoryManager_Remove)
{
    Yolk::Memory::MemoryManager manager;
    RemoveTest_A(manager);
    EXPECT_EQ(manager.Size(), 0);
}
TEST(Yolk_Test, MemoryManager_Size)
{
    Yolk::Memory::MemoryManager manager;
    auto o = manager.AllocateMemory<int>();
    int id = o.ID;

    EXPECT_EQ(manager.ChangeAudience(id, 0), 1);
    Yolk::Wrapper copy_wrapper = o;
    EXPECT_EQ(manager.ChangeAudience(id, 0), 2);
    Yolk::Wrapper copy_of_copy_wrapper = copy_wrapper;
    EXPECT_EQ(manager.ChangeAudience(id, 0), 3);
}

void Copy_Test(Yolk::Wrapper, Yolk::Memory::MemoryManager& manager, int id)
{
    EXPECT_EQ(manager.ChangeAudience(id, 0), 4);
}
TEST(Yolk_Test, MemoryManager_Size_B)
{
    Yolk::Memory::MemoryManager manager;
    auto o = manager.AllocateMemory<int>();
    int id = o.ID;

    EXPECT_EQ(manager.ChangeAudience(id, 0), 1);
    Yolk::Wrapper copy_wrapper = o;
    EXPECT_EQ(manager.ChangeAudience(id, 0), 2);
    Yolk::Wrapper copy_of_copy_wrapper = copy_wrapper;
    EXPECT_EQ(manager.ChangeAudience(id, 0), 3);
    Copy_Test(copy_of_copy_wrapper, manager, id);
    EXPECT_EQ(manager.ChangeAudience(id, 0), 3);
}

TEST(Yolk_Test, MemoryManager_Vector_test)
{
    Yolk::Memory::MemoryManager manager;
    auto o = manager.AllocateMemory<int>();

    *(o.field) = 12;

    EXPECT_STREQ(o.field->Print().c_str(), "12");
    std::vector<Yolk::Wrapper> WrapperVec;
    WrapperVec.push_back(o);
    WrapperVec.push_back(o);
    WrapperVec.push_back(o);

    EXPECT_EQ(manager.ChangeAudience(o.ID, 0), 4);
    WrapperVec.pop_back();
    EXPECT_EQ(manager.ChangeAudience(o.ID, 0), 3);
    WrapperVec.pop_back();
    *(WrapperVec.at(0).field) = 15;
    EXPECT_EQ(manager.ChangeAudience(o.ID, 0), 2);
    WrapperVec.pop_back();
    EXPECT_EQ(manager.ChangeAudience(o.ID, 0), 1);
    EXPECT_STREQ(o.field->Print().c_str(), "15");
}

TEST(Yolk_Test, MemoryManager_LostMemory_Test)
{
    Yolk::Memory::MemoryManager manager;
    manager.AllocateMemory<int>(121);
    manager.AllocateMemory<int>(121);
    manager.AllocateMemory<int>(121);
    manager.AllocateMemory<int>(121);
    manager.AllocateMemory<int>(121);
    manager.AllocateMemory<int>(121);
    EXPECT_EQ(manager.Size(), 0); // Since no Wrapper was stored, the memory stack should be empty.
}

TEST(Yolk_Test, MemoryManager_CopyByValue_Dynamic)
{
    Yolk::Memory::MemoryManager manager;
    auto w = manager.AllocateMemory<int>(12);
    auto wcopy = manager.CopyByValue(w);

    EXPECT_EQ(manager.Size(), 2);
    EXPECT_EQ(wcopy.field->As<int>(), 12);

    wcopy.field->Copy(14);
    
    EXPECT_EQ(w.field->As<int>(), 12);
    EXPECT_EQ(wcopy.field->As<int>(), 14);
}
TEST(Yolk_Test, MemoryManager_CopyByValue_Static)
{
    Yolk::Memory::MemoryManager manager;
    int x = 12;
    auto w = manager.RegisterStatic<int>(x);

    auto wcopy = manager.CopyByValue(w);

    EXPECT_EQ(manager.Size(), 2);
    EXPECT_EQ(wcopy.field->As<int>(), 12);

    wcopy.field->Copy(14);
    
    EXPECT_EQ(w.field->As<int>(), 12);
    EXPECT_EQ(wcopy.field->As<int>(), 14);
}
TEST(Yolk_Test, MemoryManager_CopyByReference_NewEntry)
{
    Yolk::Memory::MemoryManager manager;
    int x = 12;
    auto w = manager.RegisterStatic<int>(x);

    auto wcopy = manager.CopyByReference(w, true);

    EXPECT_EQ(manager.Size(), 2);
    EXPECT_EQ(wcopy.field->As<int>(), 12);
    
    wcopy.field->Copy(14);
    
    EXPECT_EQ(w.field->As<int>(), 14);
    EXPECT_EQ(wcopy.field->As<int>(), 14);
}
TEST(Yolk_Test, MemoryManager_CopyByReference_NoNewEntry)
{
    Yolk::Memory::MemoryManager manager;
    int x = 12;
    auto w = manager.RegisterStatic<int>(x);

    auto wcopy = manager.CopyByReference(w);

    EXPECT_EQ(manager.Size(), 1);
    EXPECT_EQ(wcopy.field->As<int>(), 12);
    
    wcopy.field->Copy(14);
    
    EXPECT_EQ(w.field->As<int>(), 14);
    EXPECT_EQ(wcopy.field->As<int>(), 14);
}