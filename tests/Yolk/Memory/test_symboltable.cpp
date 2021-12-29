#include <gtest/gtest.h>
#include "../../../src/Yolk/Memory/Memory/Tables/NewSymbolTable.h"

TEST(Yolk_Memory, SymbolTable_Basic)
{

    Yolk::Memory::SymbolTable systable;

    Yolk::Memory::SymbolKey key("Name");
    Yolk::Memory::SymbolValue value(12);

    systable.Add(key, value);

    auto t1 = systable.Get(key);

    EXPECT_TRUE(t1.ok);
    EXPECT_EQ(t1.value, value);

    auto t2 = systable.Find(value);

    EXPECT_TRUE(t2.ok);
    EXPECT_EQ(t2.key, key);

    auto t3 = systable.Exists(key);

    EXPECT_TRUE(t3);

    systable.Delete(key);

    auto t4 = systable.Exists(key);

    EXPECT_FALSE(t4);

    auto t5 = systable.GetLevel();

    EXPECT_EQ(t5, 0);

}

TEST(Yolk_Memory, SymbolTable_VerticalBranching)
{
    Yolk::Memory::SymbolTable systable;

    Yolk::Memory::SymbolKey key("Name");
    Yolk::Memory::SymbolValue val(12);
    systable.Add(key, val);
    
    Yolk::Memory::SymbolKey key2("Age");
    Yolk::Memory::SymbolValue val2(18);
    systable.Add(key2, val2);
    
    systable.BranchDown();

    EXPECT_EQ(systable.GetLevel(), 1);

    auto t1 = systable.Get(key);

    EXPECT_TRUE(t1.ok);
    EXPECT_EQ(t1.value, val);

    Yolk::Memory::SymbolKey key3("Remorse");
    Yolk::Memory::SymbolValue val3(18);
    systable.Add(key3, val3);

    auto t2 = systable.Exists(key3);

    EXPECT_TRUE(t2);

    systable.BranchUp();

    auto t3 = systable.Exists(key3);

    EXPECT_FALSE(t3);
}
TEST(Yolk_Memory, SymbolTable_GlobalAddAndDelete)
{
    Yolk::Memory::SymbolTable systable;
    systable.Add(Yolk::Memory::SymbolKey("Name"), Yolk::Memory::SymbolValue(12));
    systable.BranchDown();
    systable.Add(Yolk::Memory::SymbolKey("Age"), Yolk::Memory::SymbolValue(27));
    systable.GlobalAdd(Yolk::Memory::SymbolKey("GlobalAge"), Yolk::Memory::SymbolValue(33));
    systable.GlobalDelete(Yolk::Memory::SymbolKey("Name"));

    EXPECT_FALSE(systable.Exists(Yolk::Memory::SymbolKey("Name")));
    EXPECT_TRUE(systable.Exists(Yolk::Memory::SymbolKey("Age")));
    EXPECT_TRUE(systable.Exists(Yolk::Memory::SymbolKey("GlobalAge")));

    systable.BranchUp();
    
    EXPECT_FALSE(systable.Exists(Yolk::Memory::SymbolKey("Name")));
    EXPECT_FALSE(systable.Exists(Yolk::Memory::SymbolKey("Age")));
    EXPECT_TRUE(systable.Exists(Yolk::Memory::SymbolKey("GlobalAge")));

}
TEST(Yolk_Memory, SymbolTable_Clone)
{
    Yolk::Memory::SymbolTable systable;
    systable.Add(Yolk::Memory::SymbolKey("A"), Yolk::Memory::SymbolValue(12));
    systable.Add(Yolk::Memory::SymbolKey("B"), Yolk::Memory::SymbolValue(17));
    systable.Add(Yolk::Memory::SymbolKey("C"), Yolk::Memory::SymbolValue(22));
    systable.BranchDown();
    systable.Add(Yolk::Memory::SymbolKey("A2"), Yolk::Memory::SymbolValue(15));
    systable.BranchDown();
    systable.Add(Yolk::Memory::SymbolKey("A3"), Yolk::Memory::SymbolValue(5));
    systable.Add(Yolk::Memory::SymbolKey("B3"), Yolk::Memory::SymbolValue(1));

    Yolk::Memory::SymbolTable copytable;
    Yolk::Memory::SymbolTable::Clone(systable, copytable);

    EXPECT_TRUE(copytable.Exists(Yolk::Memory::SymbolKey("A3")));
    EXPECT_TRUE(copytable.Exists(Yolk::Memory::SymbolKey("B3")));
    EXPECT_TRUE(copytable.Exists(Yolk::Memory::SymbolKey("A2")));
    EXPECT_TRUE(copytable.Exists(Yolk::Memory::SymbolKey("A")));
    EXPECT_TRUE(copytable.Exists(Yolk::Memory::SymbolKey("B")));
    EXPECT_TRUE(copytable.Exists(Yolk::Memory::SymbolKey("C")));

    copytable.BranchUp();
    EXPECT_FALSE(copytable.Exists(Yolk::Memory::SymbolKey("A3")));
    EXPECT_FALSE(copytable.Exists(Yolk::Memory::SymbolKey("B3")));
    EXPECT_TRUE(copytable.Exists(Yolk::Memory::SymbolKey("A2")));
    EXPECT_TRUE(copytable.Exists(Yolk::Memory::SymbolKey("A")));
    EXPECT_TRUE(copytable.Exists(Yolk::Memory::SymbolKey("B")));
    EXPECT_TRUE(copytable.Exists(Yolk::Memory::SymbolKey("C")));

    copytable.BranchUp();

    EXPECT_FALSE(copytable.Exists(Yolk::Memory::SymbolKey("A3")));
    EXPECT_FALSE(copytable.Exists(Yolk::Memory::SymbolKey("B3")));
    EXPECT_FALSE(copytable.Exists(Yolk::Memory::SymbolKey("A2")));
    EXPECT_TRUE(copytable.Exists(Yolk::Memory::SymbolKey("A")));
    EXPECT_TRUE(copytable.Exists(Yolk::Memory::SymbolKey("B")));
    EXPECT_TRUE(copytable.Exists(Yolk::Memory::SymbolKey("C")));

}
TEST(Yolk_Memory, SymbolTable_Clear)
{
    std::cout << "A!\n";
    Yolk::Memory::SymbolTable systable;
    systable.Add(Yolk::Memory::SymbolKey("A"), Yolk::Memory::SymbolValue(12));
    systable.Add(Yolk::Memory::SymbolKey("B"), Yolk::Memory::SymbolValue(17));
    systable.Add(Yolk::Memory::SymbolKey("C"), Yolk::Memory::SymbolValue(22));
    std::cout << "B!\n";
    systable.BranchDown();
    systable.Add(Yolk::Memory::SymbolKey("A2"), Yolk::Memory::SymbolValue(15));
    std::cout << "C!\n";
    systable.BranchDown();
    systable.Add(Yolk::Memory::SymbolKey("A3"), Yolk::Memory::SymbolValue(5));
    systable.Add(Yolk::Memory::SymbolKey("B3"), Yolk::Memory::SymbolValue(1));

    std::cout << "D!\n";
    Yolk::Memory::SymbolTable copytable(systable);
    std::cout << "E!\n";
    systable.ClearAll();

    EXPECT_EQ(systable.GetLevel(), 0);

    EXPECT_FALSE(systable.Exists(Yolk::Memory::SymbolKey("A3")));
    EXPECT_FALSE(systable.Exists(Yolk::Memory::SymbolKey("B3")));
    EXPECT_FALSE(systable.Exists(Yolk::Memory::SymbolKey("A2")));
    EXPECT_FALSE(systable.Exists(Yolk::Memory::SymbolKey("A")));
    EXPECT_FALSE(systable.Exists(Yolk::Memory::SymbolKey("B")));
    EXPECT_FALSE(systable.Exists(Yolk::Memory::SymbolKey("C")));

    std::cout << "F!\n";
    systable = copytable;

    EXPECT_TRUE(systable.Exists(Yolk::Memory::SymbolKey("A3")));
    EXPECT_TRUE(systable.Exists(Yolk::Memory::SymbolKey("B3")));
    EXPECT_TRUE(systable.Exists(Yolk::Memory::SymbolKey("A2")));
    EXPECT_TRUE(systable.Exists(Yolk::Memory::SymbolKey("A")));
    EXPECT_TRUE(systable.Exists(Yolk::Memory::SymbolKey("B")));
    EXPECT_TRUE(systable.Exists(Yolk::Memory::SymbolKey("C")));

    std::cout << "G!\n";
    systable.BranchUp();
    EXPECT_FALSE(systable.Exists(Yolk::Memory::SymbolKey("A3")));
    EXPECT_FALSE(systable.Exists(Yolk::Memory::SymbolKey("B3")));
    EXPECT_TRUE(systable.Exists(Yolk::Memory::SymbolKey("A2")));
    EXPECT_TRUE(systable.Exists(Yolk::Memory::SymbolKey("A")));
    EXPECT_TRUE(systable.Exists(Yolk::Memory::SymbolKey("B")));
    EXPECT_TRUE(systable.Exists(Yolk::Memory::SymbolKey("C")));

    std::cout << "H!\n";
    systable.BranchUp();

    EXPECT_FALSE(systable.Exists(Yolk::Memory::SymbolKey("A3")));
    EXPECT_FALSE(systable.Exists(Yolk::Memory::SymbolKey("B3")));
    EXPECT_FALSE(systable.Exists(Yolk::Memory::SymbolKey("A2")));
    EXPECT_TRUE(systable.Exists(Yolk::Memory::SymbolKey("A")));
    EXPECT_TRUE(systable.Exists(Yolk::Memory::SymbolKey("B")));
    EXPECT_TRUE(systable.Exists(Yolk::Memory::SymbolKey("C")));
}