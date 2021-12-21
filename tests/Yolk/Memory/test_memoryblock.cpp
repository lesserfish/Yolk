
#include "../../../src/Yolk/Yolk/Yolk.h"
#include <gtest/gtest.h>
#include <vector>

TEST(Yolk_Test, MemoryBlock_RegisterFieldWrapper_Register)
{
    Yolk::Memory::MemoryManager manager;
    Yolk::Memory::MemoryBlock block(manager);

    auto F1 = manager.AllocateMemory<int>(12);

    auto t1 = block.RegisterWrapper("F1", F1);

    EXPECT_TRUE(t1);

}
TEST(Yolk_Test, MemoryBlock_RegisterFieldWrapper_RegisterTwiceShouldFail)
{
    Yolk::Memory::MemoryManager manager;
    Yolk::Memory::MemoryBlock block(manager);

    auto F1 = manager.AllocateMemory<int>(12);
    auto t1 = block.RegisterWrapper("F1", F1);

    EXPECT_TRUE(t1);

    auto t2 = block.RegisterWrapper("F1", F1);

    EXPECT_FALSE(t2);
}
TEST(Yolk_Test, MemoryBlock_RegisterFieldWrapper_RegisterGetKey)
{
    Yolk::Memory::MemoryManager manager;
    Yolk::Memory::MemoryBlock block(manager);


    Yolk::Memory::WrapperTable::Key key;

    auto F1 = manager.AllocateMemory<int>(12);
    block.RegisterWrapper("F1", F1, key);

    EXPECT_EQ(key, 0);
}
TEST(Yolk_Test, MemoryBlock_RegisterFieldWrapper_GetWrapperKeyByName)
{
    Yolk::Memory::MemoryManager manager;
    Yolk::Memory::MemoryBlock block(manager);


    Yolk::Memory::WrapperTable::Key key;

    auto F1 = manager.AllocateMemory<int>(12);
    block.RegisterWrapper("F1", F1, key);

    Yolk::Memory::WrapperTable::Key nkey = block.GetWrapperKeyByName("F1");

    EXPECT_EQ(key, nkey);
}
TEST(Yolk_Test, MemoryBlock_RegisterFieldWrapper_GetByKey)
{
    Yolk::Memory::MemoryManager manager;
    Yolk::Memory::MemoryBlock block(manager);

    Yolk::Wrapper F1 = manager.AllocateMemory<int>(12);
    block.RegisterWrapper("F1", F1);

    Yolk::Memory::WrapperTable::Key nkey = block.GetWrapperKeyByName("F1");

    Yolk::Wrapper wrap = block.GetFieldWrapperByWrapperKey(nkey);

    EXPECT_TRUE(wrap.field->Valid());
    EXPECT_STREQ(wrap.field->Print().c_str(), "12");
    EXPECT_STREQ(wrap.field->GetType().name(), "i");
}
TEST(Yolk_Test, MemoryBlock_RegisterFieldWrapper_GetByName)
{
    Yolk::Memory::MemoryManager manager;
    Yolk::Memory::MemoryBlock block(manager);

    Yolk::Wrapper F1 = manager.AllocateMemory<int>(12);
    block.RegisterWrapper("F1", F1);

    Yolk::Wrapper wrap = block.GetFieldWrapperByName("F1");

    EXPECT_TRUE(wrap.field->Valid());
    EXPECT_STREQ(wrap.field->Print().c_str(), "12");
    EXPECT_STREQ(wrap.field->GetType().name(), "i");
}
TEST(Yolk_Test, MemoryBlock_Exists)
{

    Yolk::Memory::MemoryManager manager;
    Yolk::Memory::MemoryBlock block(manager);

    Yolk::Wrapper F1 = manager.AllocateMemory<int>(12);
    block.RegisterWrapper("F1", F1);

    auto t1 = block.Exists("F1");
    auto t2 = block.Exists("F2");
    
    EXPECT_TRUE(t1);
    EXPECT_FALSE(t2);
}
TEST(Yolk_Test, MemoryBlock_Delete_by_Name)
{

    Yolk::Memory::MemoryManager manager;
    Yolk::Memory::MemoryBlock block(manager);

    Yolk::Wrapper F1 = manager.AllocateMemory<int>(12); // 1 Audience
    block.RegisterWrapper("F1", F1); // 2 Audience

    auto t1 = block.Exists("F1");
    auto t2 = block.Exists("F2");
    
    EXPECT_TRUE(t1);
    EXPECT_FALSE(t2);

    block.DeleteByName("F1"); // 1 Audience    
    
    t1 = block.Exists("F1");
    t2 = block.Exists("F2");

    EXPECT_FALSE(t1);
    EXPECT_FALSE(t2);

    EXPECT_EQ(manager.ChangeAudience(1, 0), 1);
}
TEST(Yolk_Test, MemoryBlock_Delete_by_Tag)
{

    Yolk::Memory::MemoryManager manager;
    Yolk::Memory::MemoryBlock block(manager);

    Yolk::Wrapper F1 = manager.AllocateMemory<int>(12); // 1 Audience
    
    Yolk::Memory::WrapperTable::Key kout;

    block.RegisterWrapper("F1", F1, kout); // 2 Audience

    auto t1 = block.Exists("F1");
    auto t2 = block.Exists("F2");
    
    EXPECT_TRUE(t1);
    EXPECT_FALSE(t2);

    block.DeleteByWrapperKey(kout);// 1 Audience    
    
    t1 = block.Exists("F1");
    t2 = block.Exists("F2");

    EXPECT_FALSE(t1);
    EXPECT_FALSE(t2);

    EXPECT_EQ(manager.ChangeAudience(1, 0), 1);
}

int memblock_func(int x)
{
    return x;
}
TEST(Yolk_Test, MemoryBlock_RegisterMethod)
{
    Yolk::Memory::MemoryManager manager;
    Yolk::Memory::MemoryBlock block(manager);
    
    std::function<int(int)> f = memblock_func;

    auto m = Yolk::WrapperGenerator<int, int>::GenerateMethodWrapper(f, manager);

    block.RegisterWrapper("memblock_func", m);

    auto m2 = block.GetMethodWrapperByName("memblock_func");

    auto input = manager.AllocateMemory<int>(18);
    Yolk::ArgumentWrapper p = {input};

    auto output = m2.Invoke(p);

    EXPECT_TRUE(output.ok);
    EXPECT_STREQ(output.output.field->Print().c_str(), "18");

}

int memblock_sum(int x, int y)
{
    return x - y;
}
TEST(Yolk_Test, MemoryBlock_Combination)
{
    Yolk::Memory::MemoryManager manager;
    Yolk::Memory::MemoryBlock block(manager);

    auto i1 = manager.AllocateMemory<int>(12);
    auto i2 = manager.AllocateMemory<int>(7);

    std::function<int(int, int)> f = memblock_sum;

    auto m = Yolk::WrapperGenerator<int, int, int>::GenerateMethodWrapper(f, manager);

    block.RegisterWrapper("hp", i1);
    block.RegisterWrapper("damage", i2);
    block.RegisterWrapper("deal_damage", m);

    Yolk::ArgumentWrapper i = {block.GetFieldWrapperByName("hp"), block.GetFieldWrapperByName("damage")};
    Yolk::MethodWrapper fun = block.GetMethodWrapperByName("deal_damage");

    block.RegisterWrapper("new_hp", fun.Invoke(i).output);  //new_hp = deal_damage(hp, damage);

    EXPECT_EQ(block.GetFieldWrapperByName("new_hp").field->As<int>(), 5);

}
