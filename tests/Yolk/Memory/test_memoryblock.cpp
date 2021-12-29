
//#include "../../../src/Yolk/Yolk.h"
#include "../../../src/Yolk/Memory/Memory/NewMemoryBlock.h"
#include "../../../src/Yolk/Memory/Memory/Tables/NewWrapperTable.h"
#include "../../../src/Yolk/Wrapper/WrapperGenerator.h"
#include <gtest/gtest.h>
#include <vector>

TEST(Yolk_Test, MemoryBlock_RegisterFieldWrapper_Register)
{
    Yolk::Memory::MemoryManager manager;
    Yolk::Memory::WrapperTable wrapperTable(manager);
    Yolk::Memory::MemoryBlock block(manager, wrapperTable);

    auto F1 = manager.AllocateMemory<int>(12);

    auto t1 = block.RegisterWrapper("F1", F1);

    EXPECT_TRUE(t1.ok);

}
TEST(Yolk_Test, MemoryBlock_RegisterFieldWrapper_RegisterTwiceShouldFail)
{
    Yolk::Memory::MemoryManager manager;
    Yolk::Memory::WrapperTable wrapperTable(manager);
    Yolk::Memory::MemoryBlock block(manager, wrapperTable);

    auto F1 = manager.AllocateMemory<int>(12);
    auto t1 = block.RegisterWrapper("F1", F1);

    EXPECT_TRUE(t1.ok);

    auto t2 = block.RegisterWrapper("F1", F1);

    EXPECT_FALSE(t2.ok);
}
TEST(Yolk_Test, MemoryBlock_RegisterFieldWrapper_RegisterGetKey)
{

    Yolk::Memory::MemoryManager manager;
    Yolk::Memory::WrapperTable wrapperTable(manager);
    Yolk::Memory::MemoryBlock block(manager, wrapperTable);

    Yolk::Memory::WrapperKey key;

    auto F1 = manager.AllocateMemory<int>(12);
    auto output = block.RegisterWrapper("F1", F1);

    key = output.wrapperKey;

    EXPECT_EQ(key, 0);
}
TEST(Yolk_Test, MemoryBlock_RegisterFieldWrapper_GetWrapperKeyByName)
{
    Yolk::Memory::MemoryManager manager;
    Yolk::Memory::WrapperTable wrapperTable(manager);
    Yolk::Memory::MemoryBlock block(manager, wrapperTable);

    Yolk::Memory::WrapperKey key;

    auto F1 = manager.AllocateMemory<int>(12);
    auto output = block.RegisterWrapper("F1", F1, key);

    key = output.wrapperKey;

    Yolk::Memory::WrapperKey nkey = block.GetWrapperKeyByName("F1").key;

    EXPECT_EQ(key, nkey);
}
TEST(Yolk_Test, MemoryBlock_RegisterFieldWrapper_GetByKey)
{
    Yolk::Memory::MemoryManager manager;
    Yolk::Memory::WrapperTable wrapperTable(manager);
    Yolk::Memory::MemoryBlock block(manager, wrapperTable);

    Yolk::Wrapper F1 = manager.AllocateMemory<int>(12);
    block.RegisterWrapper("F1", F1);

    Yolk::Memory::WrapperKey nkey = block.GetWrapperKeyByName("F1").key;

    Yolk::Wrapper wrap = block.GetFieldWrapperByWrapperKey(nkey).wrapper;

    EXPECT_TRUE(wrap.field->Valid());
    EXPECT_STREQ(wrap.field->Print().c_str(), "12");
    EXPECT_STREQ(wrap.field->GetType().name(), "i");
}
TEST(Yolk_Test, MemoryBlock_RegisterFieldWrapper_GetByName)
{
    Yolk::Memory::MemoryManager manager;
    Yolk::Memory::WrapperTable wrapperTable(manager);
    Yolk::Memory::MemoryBlock block(manager, wrapperTable);
    
    Yolk::Wrapper F1 = manager.AllocateMemory<int>(12);
    block.RegisterWrapper("F1", F1);

    Yolk::Wrapper wrap = block.GetFieldWrapperByName("F1").wrapper;

    EXPECT_TRUE(wrap.field->Valid());
    EXPECT_STREQ(wrap.field->Print().c_str(), "12");
    EXPECT_STREQ(wrap.field->GetType().name(), "i");
}
TEST(Yolk_Test, MemoryBlock_Exists)
{
    Yolk::Memory::MemoryManager manager;
    Yolk::Memory::WrapperTable wrapperTable(manager);
    Yolk::Memory::MemoryBlock block(manager, wrapperTable);

    Yolk::Wrapper F1 = manager.AllocateMemory<int>(12);
    block.RegisterWrapper("F1", F1);

    auto t1 = block.GetWrapperKeyByName("F1").ok;
    auto t2 = block.GetWrapperKeyByName("F2").ok;
    
    EXPECT_TRUE(t1);
    EXPECT_FALSE(t2);
}
TEST(Yolk_Test, MemoryBlock_Delete_by_Name)
{
    Yolk::Memory::MemoryManager manager;
    Yolk::Memory::WrapperTable wrapperTable(manager);
    Yolk::Memory::MemoryBlock block(manager, wrapperTable);

    Yolk::Wrapper F1 = manager.AllocateMemory<int>(12); // 1 Audience
    block.RegisterWrapper("F1", F1); // 2 Audience

    auto t1 = block.GetWrapperKeyByName("F1").ok;
    auto t2 = block.GetWrapperKeyByName("F2").ok;
    
    EXPECT_TRUE(t1);
    EXPECT_FALSE(t2);

    block.DeleteByName("F1"); // 1 Audience    
    
    t1 = block.GetWrapperKeyByName("F1").ok;
    t2 = block.GetWrapperKeyByName("F2").ok;

    EXPECT_FALSE(t1);
    EXPECT_FALSE(t2);

    EXPECT_EQ(manager.ChangeAudience(1, 0), 1);
}
TEST(Yolk_Test, MemoryBlock_Delete_by_Tag)
{
    Yolk::Memory::MemoryManager manager;
    Yolk::Memory::WrapperTable wrapperTable(manager);
    Yolk::Memory::MemoryBlock block(manager, wrapperTable);

    Yolk::Wrapper F1 = manager.AllocateMemory<int>(12); // 1 Audience
    
    Yolk::Memory::WrapperKey kout;

    kout = block.RegisterWrapper("F1", F1).wrapperKey; // 2 Audience

    auto t1 = block.GetWrapperKeyByName("F1").ok;
    auto t2 = block.GetWrapperKeyByName("F2").ok;
    
    EXPECT_TRUE(t1);
    EXPECT_FALSE(t2);

    block.DeleteByWrapperKey(kout);// 1 Audience    
    
    t1 = block.GetWrapperKeyByName("F1").ok;
    t2 = block.GetWrapperKeyByName("F2").ok;

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
    Yolk::Memory::WrapperTable wrapperTable(manager);
    Yolk::Memory::MemoryBlock block(manager, wrapperTable);
    
    std::function<int(int)> f = memblock_func;

    auto m = Yolk::WrapperGenerator<int, int>::GenerateMethodWrapper(f, manager);

    block.RegisterWrapper("memblock_func", m);

    auto m2 = block.GetMethodWrapperByName("memblock_func").wrapper;

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
    Yolk::Memory::WrapperTable wrapperTable(manager);
    Yolk::Memory::MemoryBlock block(manager, wrapperTable);
    
    auto i1 = manager.AllocateMemory<int>(12);
    auto i2 = manager.AllocateMemory<int>(7);

    std::function<int(int, int)> f = memblock_sum;

    auto m = Yolk::WrapperGenerator<int, int, int>::GenerateMethodWrapper(f, manager);

    block.RegisterWrapper("hp", i1);
    block.RegisterWrapper("damage", i2);
    block.RegisterWrapper("deal_damage", m);

    Yolk::ArgumentWrapper i = {block.GetFieldWrapperByName("hp").wrapper, block.GetFieldWrapperByName("damage").wrapper};
    Yolk::MethodWrapper fun = block.GetMethodWrapperByName("deal_damage").wrapper;

    block.RegisterWrapper("new_hp", fun.Invoke(i).output);  //new_hp = deal_damage(hp, damage);

    EXPECT_EQ(block.GetFieldWrapperByName("new_hp").wrapper.field->As<int>(), 5);

}
int FunctionTest(int a, float b)
{
    int o = a + (int)b;
    return o;
}
void GoTest(Yolk::Memory::MemoryManager& manager, Yolk::Memory::MemoryBlock& memblock)
{
    // Initialize Registers
    Yolk::Wrapper REGA(manager.GenerateVoidWrapper());
    Yolk::Wrapper REGOUT(manager.GenerateVoidWrapper());
    Yolk::MethodWrapper MREG(manager.GenerateVoidWrapper());
    Yolk::ArgumentWrapper ARGREG;

    // var output = GetInfo(2, 3.14f);  <-- Command we are going to run.

    // It's Assembly form is:
    //mov REGA, 2
    //pushar REGA
    //mov REGA, 3.14
    //pushar REGA
    //movr "GetInfo"
    //CALLM
    //MOV REGA, REGOUT
    //NAMEL REGA, "output"
    
    
    // Let's GO!

    // mov REGA, 2
    REGA = manager.AllocateMemory<int>(2);
    // pushar REGA
    ARGREG << REGA;
    // mov REGA, 3.14f
    REGA = manager.AllocateMemory<float>(3.14f);
    // pushar REGA
    ARGREG << REGA;
    // movr "GetInfo"
    MREG = memblock.GetMethodWrapperByName("GetInfo").wrapper;
    // callm
    auto o = MREG.Invoke(ARGREG);
    REGOUT = o.output;
    // mov REGA, REGOUT
    REGA = REGOUT;
    // namel REGA, "output"
    memblock.RegisterWrapper("output", REGA);
}
TEST(Yolk_Test, MemoryBlock_Mini_Assembly)
{
    Yolk::Memory::MemoryManager manager;
    Yolk::Memory::WrapperTable wrapperTable(manager);
    Yolk::Memory::MemoryBlock memblock(manager, wrapperTable);

    auto m = Yolk::WrapperGenerator<int, int, float>::GenerateMethodWrapper(FunctionTest, manager);

    memblock.RegisterWrapper("GetInfo", m);
    GoTest(manager, memblock);

    EXPECT_EQ(manager.Size(), 2);
    auto w = memblock.GetFieldWrapperByName("output").wrapper;
    EXPECT_TRUE(w.field->Valid());
    EXPECT_EQ(w.field->As<int>(), 5);

    // Checking no leakage of memory

    EXPECT_EQ(manager.ChangeAudience(m.ID, 0), 2); // m and the one in MemBlock
    EXPECT_EQ(manager.ChangeAudience(w.ID, 0), 2); // w and the one in MemBlock
}
