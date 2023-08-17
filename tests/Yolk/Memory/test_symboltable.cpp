#include <gtest/gtest.h>
#include "../../../src/Yolk/Memory/Memory.h"

TEST(SymbolTableInterface, Basic)
{

    Yolk::Memory::SymbolTableInterface systable;

    Yolk::Memory::SymbolKey key("Name");
    Yolk::Memory::SymbolValue value(12, Yolk::Memory::SymbolValue::Type::Wrapper);

    systable.Add(key, value);

    auto t1 = systable.Get(key);

    EXPECT_EQ(t1.second, value);

    auto t2 = systable.Find(value);

    EXPECT_EQ(t2.key, key);

    auto t3 = systable.Exists(key);

    EXPECT_TRUE(t3);

    systable.Delete(key);

    auto t4 = systable.Exists(key);

    EXPECT_FALSE(t4);

    auto t5 = systable.GetLevel();

    EXPECT_EQ(t5, 0);

}
TEST(SymbolTableInterface, VerticalBranching)
{
    Yolk::Memory::SymbolTableInterface systable;

    Yolk::Memory::SymbolKey key("Name");
    Yolk::Memory::SymbolValue val(12, Yolk::Memory::SymbolValue::Type::Wrapper);
    systable.Add(key, val);
    
    Yolk::Memory::SymbolKey key2("Age");
    Yolk::Memory::SymbolValue val2(18, Yolk::Memory::SymbolValue::Type::Wrapper);
    systable.Add(key2, val2);
    
    systable.BranchDown();

    EXPECT_EQ(systable.GetLevel(), 1);

    auto t1 = systable.Get(key);

    EXPECT_EQ(t1.second, val);

    Yolk::Memory::SymbolKey key3("Remorse");
    Yolk::Memory::SymbolValue val3(18, Yolk::Memory::SymbolValue::Type::Wrapper);
    systable.Add(key3, val3);

    auto t2 = systable.Exists(key3);

    EXPECT_TRUE(t2);

    systable.BranchUp();

    auto t3 = systable.Exists(key3);

    EXPECT_FALSE(t3);

}
TEST(SymbolTableInterface, GlobalAddAndDelete)
{
    Yolk::Memory::SymbolTableInterface systable;
    systable.Add(Yolk::Memory::SymbolKey("Name"), Yolk::Memory::SymbolValue(12, Yolk::Memory::SymbolValue::Type::Wrapper));
    systable.BranchDown();
    systable.Add(Yolk::Memory::SymbolKey("Age"), Yolk::Memory::SymbolValue(27, Yolk::Memory::SymbolValue::Type::Wrapper));
    systable.GlobalAdd(Yolk::Memory::SymbolKey("GlobalAge"), Yolk::Memory::SymbolValue(33, Yolk::Memory::SymbolValue::Type::Wrapper));
    systable.GlobalDelete(Yolk::Memory::SymbolKey("Name"));

    EXPECT_FALSE(systable.Exists(Yolk::Memory::SymbolKey("Name")));
    EXPECT_TRUE(systable.Exists(Yolk::Memory::SymbolKey("Age")));
    EXPECT_TRUE(systable.Exists(Yolk::Memory::SymbolKey("GlobalAge")));

    systable.BranchUp();
    
    EXPECT_FALSE(systable.Exists(Yolk::Memory::SymbolKey("Name")));
    EXPECT_FALSE(systable.Exists(Yolk::Memory::SymbolKey("Age")));
    EXPECT_TRUE(systable.Exists(Yolk::Memory::SymbolKey("GlobalAge")));

}
TEST(SymbolTableInterface, BranchUp)
{
    Yolk::Memory::SymbolTableInterface systable;
    systable.Add(Yolk::Memory::SymbolKey("A"), Yolk::Memory::SymbolValue(12, Yolk::Memory::SymbolValue::Type::Wrapper));
    systable.Add(Yolk::Memory::SymbolKey("B"), Yolk::Memory::SymbolValue(17, Yolk::Memory::SymbolValue::Type::Wrapper));
    systable.Add(Yolk::Memory::SymbolKey("C"), Yolk::Memory::SymbolValue(22, Yolk::Memory::SymbolValue::Type::Wrapper));

    systable.BranchDown();
    systable.Add(Yolk::Memory::SymbolKey("A2"), Yolk::Memory::SymbolValue(15, Yolk::Memory::SymbolValue::Type::Wrapper));

    systable.BranchDown();
    systable.Add(Yolk::Memory::SymbolKey("A3"), Yolk::Memory::SymbolValue(5, Yolk::Memory::SymbolValue::Type::Wrapper));
    systable.Add(Yolk::Memory::SymbolKey("B3"), Yolk::Memory::SymbolValue(1, Yolk::Memory::SymbolValue::Type::Wrapper));

    auto t1 = systable.BranchUp();

    EXPECT_EQ(t1.size(), 2);
    EXPECT_EQ(t1.at(0).second.key, 5);
    EXPECT_EQ(t1.at(1).second.key, 1);

    auto t2 = systable.BranchUp();

    EXPECT_EQ(t2.size(), 1);

    EXPECT_EQ(t2.at(0).second.key, 15);
}
TEST(SymbolTableInterface, SymboLTable_GlobalAll)
{
    Yolk::Memory::SymbolTableInterface systable;
    systable.Add(Yolk::Memory::SymbolKey("A"), Yolk::Memory::SymbolValue(12, Yolk::Memory::SymbolValue::Type::Wrapper));
    systable.Add(Yolk::Memory::SymbolKey("B"), Yolk::Memory::SymbolValue(17, Yolk::Memory::SymbolValue::Type::Wrapper));
    systable.Add(Yolk::Memory::SymbolKey("C"), Yolk::Memory::SymbolValue(22, Yolk::Memory::SymbolValue::Type::Wrapper));
    systable.BranchDown();
    systable.Add(Yolk::Memory::SymbolKey("A2"), Yolk::Memory::SymbolValue(15, Yolk::Memory::SymbolValue::Type::Wrapper));
    systable.BranchDown();
    systable.Add(Yolk::Memory::SymbolKey("A3"), Yolk::Memory::SymbolValue(5, Yolk::Memory::SymbolValue::Type::Wrapper));
    systable.Add(Yolk::Memory::SymbolKey("B3"), Yolk::Memory::SymbolValue(1, Yolk::Memory::SymbolValue::Type::Wrapper));
    systable.GlobalAdd(Yolk::Memory::SymbolKey("A4"), Yolk::Memory::SymbolValue(10, Yolk::Memory::SymbolValue::Type::Wrapper));

    auto t1 = systable.BranchUp();
    auto t2 = systable.BranchUp();

    EXPECT_EQ(t1.size(), 2); // A3, B3
    EXPECT_EQ(t2.size(), 1); // A2

}
//TEST(SymbolTableInterface, Clone)
//{
//    Yolk::Memory::SymbolTableInterface systable;
//    systable.Add(Yolk::Memory::SymbolKey("A"), Yolk::Memory::SymbolValue(12, Yolk::Memory::SymbolValue::Type::Wrapper));
//    systable.Add(Yolk::Memory::SymbolKey("B"), Yolk::Memory::SymbolValue(17, Yolk::Memory::SymbolValue::Type::Wrapper));
//    systable.Add(Yolk::Memory::SymbolKey("C"), Yolk::Memory::SymbolValue(22, Yolk::Memory::SymbolValue::Type::Wrapper));
//    systable.BranchDown();
//    systable.Add(Yolk::Memory::SymbolKey("A2"), Yolk::Memory::SymbolValue(15, Yolk::Memory::SymbolValue::Type::Wrapper));
//    systable.BranchDown();
//    systable.Add(Yolk::Memory::SymbolKey("A3"), Yolk::Memory::SymbolValue(5, Yolk::Memory::SymbolValue::Type::Wrapper));
//    systable.Add(Yolk::Memory::SymbolKey("B3"), Yolk::Memory::SymbolValue(1, Yolk::Memory::SymbolValue::Type::Wrapper));
//
//    Yolk::Memory::SymbolTableInterface copytable;
//    Yolk::Memory::SymbolTableInterface::Clone(systable, copytable);
//
//    EXPECT_TRUE(copytable.Exists(Yolk::Memory::SymbolKey("A3")));
//    EXPECT_TRUE(copytable.Exists(Yolk::Memory::SymbolKey("B3")));
//    EXPECT_TRUE(copytable.Exists(Yolk::Memory::SymbolKey("A2")));
//    EXPECT_TRUE(copytable.Exists(Yolk::Memory::SymbolKey("A")));
//    EXPECT_TRUE(copytable.Exists(Yolk::Memory::SymbolKey("B")));
//    EXPECT_TRUE(copytable.Exists(Yolk::Memory::SymbolKey("C")));
//
//    copytable.BranchUp();
//    EXPECT_FALSE(copytable.Exists(Yolk::Memory::SymbolKey("A3")));
//    EXPECT_FALSE(copytable.Exists(Yolk::Memory::SymbolKey("B3")));
//    EXPECT_TRUE(copytable.Exists(Yolk::Memory::SymbolKey("A2")));
//    EXPECT_TRUE(copytable.Exists(Yolk::Memory::SymbolKey("A")));
//    EXPECT_TRUE(copytable.Exists(Yolk::Memory::SymbolKey("B")));
//    EXPECT_TRUE(copytable.Exists(Yolk::Memory::SymbolKey("C")));
//
//    copytable.BranchUp();
//
//    EXPECT_FALSE(copytable.Exists(Yolk::Memory::SymbolKey("A3")));
//    EXPECT_FALSE(copytable.Exists(Yolk::Memory::SymbolKey("B3")));
//    EXPECT_FALSE(copytable.Exists(Yolk::Memory::SymbolKey("A2")));
//    EXPECT_TRUE(copytable.Exists(Yolk::Memory::SymbolKey("A")));
//    EXPECT_TRUE(copytable.Exists(Yolk::Memory::SymbolKey("B")));
//    EXPECT_TRUE(copytable.Exists(Yolk::Memory::SymbolKey("C")));
//
//}
//
//TEST(SymbolTableInterface, Clear)
//{
//    std::cout << "A!\n";
//    Yolk::Memory::SymbolTableInterface systable;
//    systable.Add(Yolk::Memory::SymbolKey("A"), Yolk::Memory::SymbolValue(12, Yolk::Memory::SymbolValue::Type::Wrapper));
//    systable.Add(Yolk::Memory::SymbolKey("B"), Yolk::Memory::SymbolValue(17, Yolk::Memory::SymbolValue::Type::Wrapper));
//    systable.Add(Yolk::Memory::SymbolKey("C"), Yolk::Memory::SymbolValue(22, Yolk::Memory::SymbolValue::Type::Wrapper));
//    std::cout << "B!\n";
//    systable.BranchDown();
//    systable.Add(Yolk::Memory::SymbolKey("A2"), Yolk::Memory::SymbolValue(15, Yolk::Memory::SymbolValue::Type::Wrapper));
//    std::cout << "C!\n";
//    systable.BranchDown();
//    systable.Add(Yolk::Memory::SymbolKey("A3"), Yolk::Memory::SymbolValue(5, Yolk::Memory::SymbolValue::Type::Wrapper));
//    systable.Add(Yolk::Memory::SymbolKey("B3"), Yolk::Memory::SymbolValue(1, Yolk::Memory::SymbolValue::Type::Wrapper));
//
//    std::cout << "D!\n";
//    Yolk::Memory::SymbolTableInterface copytable(systable);
//    std::cout << "E!\n";
//    systable.ClearAll();
//
//    EXPECT_EQ(systable.GetLevel(), 0);
//
//    EXPECT_FALSE(systable.Exists(Yolk::Memory::SymbolKey("A3")));
//    EXPECT_FALSE(systable.Exists(Yolk::Memory::SymbolKey("B3")));
//    EXPECT_FALSE(systable.Exists(Yolk::Memory::SymbolKey("A2")));
//    EXPECT_FALSE(systable.Exists(Yolk::Memory::SymbolKey("A")));
//    EXPECT_FALSE(systable.Exists(Yolk::Memory::SymbolKey("B")));
//    EXPECT_FALSE(systable.Exists(Yolk::Memory::SymbolKey("C")));
//
//    std::cout << "F!\n";
//    systable = copytable;
//
//    EXPECT_TRUE(systable.Exists(Yolk::Memory::SymbolKey("A3")));
//    EXPECT_TRUE(systable.Exists(Yolk::Memory::SymbolKey("B3")));
//    EXPECT_TRUE(systable.Exists(Yolk::Memory::SymbolKey("A2")));
//    EXPECT_TRUE(systable.Exists(Yolk::Memory::SymbolKey("A")));
//    EXPECT_TRUE(systable.Exists(Yolk::Memory::SymbolKey("B")));
//    EXPECT_TRUE(systable.Exists(Yolk::Memory::SymbolKey("C")));
//
//    std::cout << "G!\n";
//    systable.BranchUp();
//    EXPECT_FALSE(systable.Exists(Yolk::Memory::SymbolKey("A3")));
//    EXPECT_FALSE(systable.Exists(Yolk::Memory::SymbolKey("B3")));
//    EXPECT_TRUE(systable.Exists(Yolk::Memory::SymbolKey("A2")));
//    EXPECT_TRUE(systable.Exists(Yolk::Memory::SymbolKey("A")));
//    EXPECT_TRUE(systable.Exists(Yolk::Memory::SymbolKey("B")));
//    EXPECT_TRUE(systable.Exists(Yolk::Memory::SymbolKey("C")));
//
//    std::cout << "H!\n";
//    systable.BranchUp();
//
//    EXPECT_FALSE(systable.Exists(Yolk::Memory::SymbolKey("A3")));
//    EXPECT_FALSE(systable.Exists(Yolk::Memory::SymbolKey("B3")));
//    EXPECT_FALSE(systable.Exists(Yolk::Memory::SymbolKey("A2")));
//    EXPECT_TRUE(systable.Exists(Yolk::Memory::SymbolKey("A")));
//    EXPECT_TRUE(systable.Exists(Yolk::Memory::SymbolKey("B")));
//    EXPECT_TRUE(systable.Exists(Yolk::Memory::SymbolKey("C")));
//}

//TEST(SymbolTableInterface, ClearChildren)
//{
//    Yolk::Memory::SymbolTableInterface systable;
//    systable.Add(Yolk::Memory::SymbolKey("A"), Yolk::Memory::SymbolValue(12, Yolk::Memory::SymbolValue::Type::Wrapper));
//    systable.Add(Yolk::Memory::SymbolKey("B"), Yolk::Memory::SymbolValue(17, Yolk::Memory::SymbolValue::Type::Wrapper));
//    systable.Add(Yolk::Memory::SymbolKey("C"), Yolk::Memory::SymbolValue(22, Yolk::Memory::SymbolValue::Type::Wrapper));
//    systable.BranchDown();
//    systable.Add(Yolk::Memory::SymbolKey("A2"), Yolk::Memory::SymbolValue(15, Yolk::Memory::SymbolValue::Type::Wrapper));
//    systable.BranchDown();
//    systable.Add(Yolk::Memory::SymbolKey("A3"), Yolk::Memory::SymbolValue(5, Yolk::Memory::SymbolValue::Type::Wrapper));
//    systable.Add(Yolk::Memory::SymbolKey("B3"), Yolk::Memory::SymbolValue(1, Yolk::Memory::SymbolValue::Type::Wrapper));
//
//    auto w = systable.ClearChildren();
//
//    EXPECT_EQ(w.size(), 3);
//}
//TEST(SymbolTableInterface, ClearAll)
//{
//    Yolk::Memory::SymbolTableInterface systable;
//    systable.Add(Yolk::Memory::SymbolKey("A"), Yolk::Memory::SymbolValue(12, Yolk::Memory::SymbolValue::Type::Wrapper));
//    systable.Add(Yolk::Memory::SymbolKey("B"), Yolk::Memory::SymbolValue(17, Yolk::Memory::SymbolValue::Type::Wrapper));
//    systable.Add(Yolk::Memory::SymbolKey("C"), Yolk::Memory::SymbolValue(22, Yolk::Memory::SymbolValue::Type::Wrapper));
//    systable.BranchDown();
//    systable.Add(Yolk::Memory::SymbolKey("A2"), Yolk::Memory::SymbolValue(15, Yolk::Memory::SymbolValue::Type::Wrapper));
//    systable.BranchDown();
//    systable.Add(Yolk::Memory::SymbolKey("A3"), Yolk::Memory::SymbolValue(5, Yolk::Memory::SymbolValue::Type::Wrapper));
//    systable.Add(Yolk::Memory::SymbolKey("B3"), Yolk::Memory::SymbolValue(1, Yolk::Memory::SymbolValue::Type::Wrapper));
//
//    auto w = systable.ClearAll();
//
//    EXPECT_EQ(w.size(), 6);
//}

