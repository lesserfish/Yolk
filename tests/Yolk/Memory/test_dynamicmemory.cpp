#include "../../../src/Yolk/Core/Core.h"
#include <gtest/gtest.h>
#include <vector>

TEST(MemoryAllocator, Add)
{
    Yolk::Memory::MemoryAllocator manager;
    auto o = manager.AllocateMemory<int>();
    *(o.field) = 14;

    EXPECT_EQ(manager.Size(), 1);
    EXPECT_TRUE(manager.Exists(o.ID));
}
void RemoveTest_B(Yolk::Memory::MemoryAllocator &manager)
{
    EXPECT_EQ(manager.Size(), 1);
    auto o = manager.AllocateMemory<float>(1.1);
    EXPECT_EQ(manager.Size(), 2);
}
void RemoveTest_A(Yolk::Memory::MemoryAllocator &manager)
{
    EXPECT_EQ(manager.Size(), 0);
    auto o = manager.AllocateMemory<float>(3.14);
    EXPECT_EQ(manager.Size(), 1);
    RemoveTest_B(manager);
    EXPECT_EQ(manager.Size(), 1);
}
TEST(MemoryAllocator, Remove)
{
    Yolk::Memory::MemoryAllocator manager;
    RemoveTest_A(manager);
    EXPECT_EQ(manager.Size(), 0);
}
TEST(MemoryAllocator, Size)
{
    Yolk::Memory::MemoryAllocator manager;
    auto o = manager.AllocateMemory<int>();
    int id = o.ID;

    EXPECT_EQ(manager.UpdateViewersCount(id, 0), 1);
    Yolk::Wrapper copy_wrapper = o;
    EXPECT_EQ(manager.UpdateViewersCount(id, 0), 2);
    Yolk::Wrapper copy_of_copy_wrapper = copy_wrapper;
    EXPECT_EQ(manager.UpdateViewersCount(id, 0), 3);
}

void Copy_Test(Yolk::Wrapper, Yolk::Memory::MemoryAllocator& manager, int id)
{
    EXPECT_EQ(manager.UpdateViewersCount(id, 0), 4);
}
TEST(MemoryAllocator, Size_B)
{
    Yolk::Memory::MemoryAllocator manager;
    auto o = manager.AllocateMemory<int>();
    int id = o.ID;

    EXPECT_EQ(manager.UpdateViewersCount(id, 0), 1);
    Yolk::Wrapper copy_wrapper = o;
    EXPECT_EQ(manager.UpdateViewersCount(id, 0), 2);
    Yolk::Wrapper copy_of_copy_wrapper = copy_wrapper;
    EXPECT_EQ(manager.UpdateViewersCount(id, 0), 3);
    Copy_Test(copy_of_copy_wrapper, manager, id);
    EXPECT_EQ(manager.UpdateViewersCount(id, 0), 3);
}

TEST(MemoryAllocator, Vector_test)
{
    Yolk::Memory::MemoryAllocator manager;
    auto o = manager.AllocateMemory<int>();

    *(o.field) = 12;

    EXPECT_STREQ(o.field->Print().c_str(), "12");
    
    std::vector<Yolk::Wrapper> WrapperVec;
    WrapperVec.push_back(o);
    WrapperVec.push_back(o);
    WrapperVec.push_back(o);

    EXPECT_EQ(manager.UpdateViewersCount(o.ID, 0), 4);
    WrapperVec.pop_back();
    EXPECT_EQ(manager.UpdateViewersCount(o.ID, 0), 3);
    WrapperVec.pop_back();
    *(WrapperVec.at(0).field) = 15;
    EXPECT_EQ(manager.UpdateViewersCount(o.ID, 0), 2);
    WrapperVec.pop_back();
    EXPECT_EQ(manager.UpdateViewersCount(o.ID, 0), 1);
    EXPECT_STREQ(o.field->Print().c_str(), "15");
}

TEST(MemoryAllocator, LostMemory_Test)
{
    Yolk::Memory::MemoryAllocator manager;
    manager.AllocateMemory<int>(121);
    manager.AllocateMemory<int>(121);
    manager.AllocateMemory<int>(121);
    manager.AllocateMemory<int>(121);
    manager.AllocateMemory<int>(121);
    manager.AllocateMemory<int>(121);
    EXPECT_EQ(manager.Size(), 0); // Since no Wrapper was stored, the memory stack should be empty.
}

TEST(MemoryAllocator, CreateCopy_Dynamic)
{
    Yolk::Memory::MemoryAllocator manager;
    auto w = manager.AllocateMemory<int>(12);
    auto wcopy = manager.CreateCopy(w);

    EXPECT_EQ(manager.Size(), 2);
    EXPECT_EQ(wcopy.field->As<int>(), 12);

    wcopy.field->Copy(14);
    
    EXPECT_EQ(w.field->As<int>(), 12);
    EXPECT_EQ(wcopy.field->As<int>(), 14);
}
TEST(MemoryAllocator, CreateCopy_Static)
{
    Yolk::Memory::MemoryAllocator manager;
    int x = 12;
    auto w = manager.CreateWrapper(x);

    auto wcopy = manager.CreateCopy(w);

    EXPECT_EQ(manager.Size(), 1);
    EXPECT_EQ(wcopy.field->As<int>(), 12);

    wcopy.field->Copy(14);
    
    EXPECT_EQ(w.field->As<int>(), 12);
    EXPECT_EQ(wcopy.field->As<int>(), 14);
}
//TEST(MemoryAllocator, CopyByReference_NewEntry)
//{
//    Yolk::Memory::MemoryAllocator manager;
//    int x = 12;
//    auto w = manager.CreateWrapper(x);
//
//    auto wcopy = manager.CopyByReference(w, true);
//
//    EXPECT_EQ(manager.Size(), 2);
//    EXPECT_EQ(wcopy.field->As<int>(), 12);
//    
//    wcopy.field->Copy(14);
//    
//    EXPECT_EQ(w.field->As<int>(), 14);
//    EXPECT_EQ(wcopy.field->As<int>(), 14);
//}
//TEST(MemoryAllocator, CopyByReference_NoNewEntry)
//{
//    Yolk::Memory::MemoryAllocator manager;
//    int x = 12;
//    auto w = manager.CreateWrapper(x);
//
//    auto wcopy = manager.CopyByReference(w);
//
//    EXPECT_EQ(manager.Size(), 1);
//    EXPECT_EQ(wcopy.field->As<int>(), 12);
//    
//    wcopy.field->Copy(14);
//    
//    EXPECT_EQ(w.field->As<int>(), 14);
//    EXPECT_EQ(wcopy.field->As<int>(), 14);
//}

TEST(MemoryAllocator, Delete)
{
    Yolk::Memory::MemoryAllocator manager;

    Yolk::Wrapper a = manager.AllocateMemory<int>(5);
    Yolk::Wrapper b = manager.AllocateMemory<int>(7);

    int ID = b.ID;

    EXPECT_EQ(manager.UpdateViewersCount(ID, 0), 1);

    b = a;

    EXPECT_EQ(manager.UpdateViewersCount(ID, 0), 0);

}
