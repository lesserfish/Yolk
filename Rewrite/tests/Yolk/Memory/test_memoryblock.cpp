
//#include "../../../src/Yolk/Yolk.h"
#include "../../../src/Yolk/Memory/Memory.h"
#include <gtest/gtest.h>
#include <vector>

TEST(Yolk_Test, MemoryInterface_Register_Register)
{
    Yolk::Memory::DynamicMemory manager;
    Yolk::Memory::MemoryInterface block(manager);

    auto F1 = manager.AllocateMemory<int>(12);

    block.Register(F1, "F1");

}
TEST(Yolk_Test, MemoryInterface_Register_RegisterTwiceShouldFail)
{
    Yolk::Memory::DynamicMemory manager;
    Yolk::Memory::MemoryInterface block(manager);

    auto F1 = manager.AllocateMemory<int>(12);
    block.Register(F1, "F1");

    bool ok = true;
    try {
        block.Register(F1, "F1");
    }catch(const Yolk::Memory::MException& )
    {
        ok = false;
    }

    EXPECT_FALSE(ok);

}
TEST(Yolk_Test, MemoryInterface_Register)
{
    Yolk::Memory::DynamicMemory manager;
    Yolk::Memory::MemoryInterface block(manager);

    auto F1 = manager.AllocateMemory<int>(12);
    block.Register(F1, "F1");

    auto type = block.GetType("F1");

    EXPECT_EQ(type, Yolk::Memory::SymbolValue::Type::Wrapper);
}
TEST(Yolk_Test, MemoryInterface_Register_GetByName)
{
    Yolk::Memory::DynamicMemory manager;
    Yolk::Memory::MemoryInterface block(manager);
    
    Yolk::Wrapper F1 = manager.AllocateMemory<int>(12);
    block.Register(F1, "F1");

    Yolk::Wrapper wrap = block.GetWrapper("F1").wrapper;

    EXPECT_FALSE(wrap.field->IsNone());
    EXPECT_STREQ(wrap.field->Print().c_str(), "12");
    EXPECT_STREQ(wrap.field->Type().name(), "i");
}
TEST(Yolk_Test, MemoryInterface_Exists)
{
    Yolk::Memory::DynamicMemory manager;
    Yolk::Memory::MemoryInterface block(manager);

    Yolk::Wrapper F1 = manager.AllocateMemory<int>(12);
    block.Register(F1, "F1");
    bool ok1 = true;
    bool ok2 = true;
    try{
        block.GetWrapper("F1");
    }catch(const Yolk::Memory::MException& )
    {
        ok1 = false;
    }
     try{
        block.GetWrapper("F2");
    }catch(const Yolk::Memory::MException& )
    {
        ok2 = false;
    }
    
    EXPECT_TRUE(ok1);
    EXPECT_FALSE(ok2);
}
TEST(Yolk_Test, MemoryInterface_Delete_by_Name)
{
    Yolk::Memory::DynamicMemory manager;
    Yolk::Memory::MemoryInterface block(manager);

    Yolk::Wrapper F1 = manager.AllocateMemory<int>(12); // 1 Audience
    block.Register(F1, "F1"); // 2 Audience
    bool t1 = true;

    try {
        block.GetWrapper("F1");
    } catch(const Yolk::Memory::MException& )
    {
        t1 = false;
    }
    bool t2 = true;
    try {
        block.GetWrapper("F2");
    } catch(const Yolk::Memory::MException& )
    {
        t2 = false;
    }

    
    EXPECT_TRUE(t1);
    EXPECT_FALSE(t2);

    block.Delete("F1"); // 1 Audience    
    
    t1 = true;
    t2 = true;
    try {
        block.GetWrapper("F1");
    } catch(const Yolk::Memory::MException& )
    {
        t1 = false;
    }
    try {
        block.GetWrapper("F2");
    } catch(const Yolk::Memory::MException& )
    {
        t2 = false;
    }

    EXPECT_FALSE(t1);
    EXPECT_FALSE(t2);

    EXPECT_EQ(manager.ViewersCount(F1.ID), 1);
}

int memblock_func(int x)
{
    return x;
}
TEST(Yolk_Test, MemoryInterface_RegisterMethod)
{
    Yolk::Memory::DynamicMemory manager;
    Yolk::Memory::MemoryInterface block(manager);
    
    std::function<int(int)> f = memblock_func;

    auto m = Yolk::WrapperGenerator<int, int>::GenerateMethodWrapper(manager, f);

    block.Register(m, "memblock_func");

    auto m2 = block.GetMethodWrapper("memblock_func").wrapper;

    auto input = manager.AllocateMemory<int>(18);
    Yolk::WrapperArgument p = {input};

    auto output = m2.Invoke(p);

    EXPECT_STREQ(output.field->Print().c_str(), "18");

}
int memblock_sum(int x, int y)
{
    return x - y;
}
TEST(Yolk_Test, MemoryInterface_Combination)
{
    Yolk::Memory::DynamicMemory manager;
    Yolk::Memory::MemoryInterface block(manager);
    
    auto i1 = manager.AllocateMemory<int>(12);
    auto i2 = manager.AllocateMemory<int>(7);

    std::function<int(int, int)> f = memblock_sum;

    auto m = Yolk::WrapperGenerator<int, int, int>::GenerateMethodWrapper(manager, f);

    block.Register(i1, "hp");
    block.Register(i2, "damage");
    block.Register(m, "deal_damage");

    Yolk::WrapperArgument i = {block.GetWrapper("hp").wrapper, block.GetWrapper("damage").wrapper};
    auto funx = block.GetMethodWrapper("deal_damage").wrapper;
    
    auto fun = funx;
    auto out = fun.Invoke(i);  //new_hp = deal_damage(hp, damage, "new_hp");

    block.Register(out, "new_hp");
    
    EXPECT_EQ(block.GetWrapper("new_hp").wrapper.field->As<int>(), 5);

}
int FunctionTest(int a, float b)
{
    int o = a + (int)b;
    return o;
}
void GoTest(Yolk::Memory::DynamicMemory& manager, Yolk::Memory::MemoryInterface& memblock)
{
    // Initialize Registers
    Yolk::Wrapper REGA(manager.GetVoidWrapper());
    Yolk::Wrapper REGOUT(manager.GetVoidWrapper());
    Yolk::MethodWrapper MREG(manager.GetVoidWrapper());
    Yolk::WrapperArgument ARGREG;

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
    MREG = memblock.GetMethodWrapper("GetInfo").wrapper;
    // callm
    auto o = MREG.Invoke(ARGREG);
    REGOUT = o;
    // mov REGA, REGOUT
    REGA = REGOUT;
    // namel REGA, "output"
    memblock.Register(REGA, "output");
}
TEST(Yolk_Test, MemoryInterface_Mini_Assembly)
{
    Yolk::Memory::DynamicMemory manager;
    Yolk::Memory::MemoryInterface memblock(manager);

    auto m = Yolk::WrapperGenerator<int, int, float>::GenerateMethodWrapper(manager, FunctionTest);

    memblock.Register(m, "GetInfo");
    GoTest(manager, memblock);

    EXPECT_EQ(manager.Size(), 2);
    auto w = memblock.GetWrapper("output").wrapper;
    EXPECT_FALSE(w.field->IsNone());
    EXPECT_EQ(w.field->As<int>(), 5);

    // Checking no leakage of memory

    EXPECT_EQ(manager.ViewersCount(m.ID), 2); // m and the one in MemBlock
    EXPECT_EQ(manager.ViewersCount(w.ID), 2); // w and the one in MemBlock
}
TEST(Yolk_Test, MemoryInterface_Branch)
{
    Yolk::Memory::DynamicMemory manager;
    Yolk::Memory::MemoryInterface memblock(manager);
    auto i1 = manager.AllocateMemory<int>(12);
    
    memblock.Register(i1, "i1");
   
    memblock.BranchDown();

    auto type = memblock.GetType("i1");
    EXPECT_EQ(type, Yolk::Memory::SymbolValue::Type::Wrapper);
    
    auto i2 = manager.AllocateMemory<int>(7);
    memblock.Register(i2, "i2");
    
    type = memblock.GetType("i2");
    EXPECT_EQ(type, Yolk::Memory::SymbolValue::Type::Wrapper);

    memblock.BranchUp();
    bool ok = true;
    try{
        type = memblock.GetType("i2");
    } catch(const Yolk::Memory::MException& )
    {
        ok = false;
    }
    EXPECT_FALSE(ok);
    EXPECT_EQ(memblock.GetMemoryTable().Size(), 1);
}
