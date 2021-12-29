#include <gtest/gtest.h>
#include "../../../src/Yolk/Yolk.h"
//#include "../../../src/Yolk/Object/NewObject.h"
//#include "../../../src/Yolk/Environment/Environment.h"

class YK_God : public Yolk::Environment
{
    public:
    YK_God(){
        this->LogCallbackFunction = [](std::string in){std::cout << in << std::endl;};
    }
};

TEST(Yolk_Test, Object_Test_God)
{
    YK_God A1;
    EXPECT_STREQ(A1.GetLocalName().c_str(), "Environment");
}

class YKVec2 : public Yolk::Object
{
    public:
    YKVec2(std::string Name, Yolk::Object* father) : Object(Name, father), x(0), y(0) 
    {
        RegisterField(x, "x");
        RegisterField(y, "y");
    }
    
    Yolk::Memory::MemoryBlock& PublicGetMemoryBlock()
    {
        return GetMemoryBlock();
    }
    int x;
    int y;
};

class YKPlayer : public Yolk::Object
{
    public:
    YKPlayer(Yolk::Object *env) : Object("Player", env), Position("Position", this), Health(100)
    {
        RegisterField(Health, "Health");
    }
    Yolk::Memory::MemoryBlock& GetMemoryBlock()
    {
        return Object::GetMemoryBlock();
    }
    YKVec2 Position;
    int Health;

    void SetHealth(int newHealth)
    {
        GetMemoryBlock().GetFieldWrapperByName("Health").wrapper.field->Copy(newHealth);
    }

    int GetHealth()
    {
        return GetMemoryBlock().GetFieldWrapperByName("Health").wrapper.field->As<int>();
    }

    void SetPos(int x, int y)
    {
        auto p = GetMemoryBlock().GetSymbolTable().GetFriend("Position");
        EXPECT_TRUE(p.ok);
        auto xid = p.result->Get(Yolk::Memory::SymbolKey("x"));
        auto yid = p.result->Get(Yolk::Memory::SymbolKey("y"));
        EXPECT_TRUE(xid.ok);
        EXPECT_TRUE(yid.ok);
        auto t1 = GetWrapperTable().CopyField(xid.value.key).field->Copy(x);
        auto t2 = GetWrapperTable().CopyField(yid.value.key).field->Copy(y);

        EXPECT_TRUE(t1);
        EXPECT_TRUE(t2);
    }

    int GetPosX()
    {
        auto p = GetMemoryBlock().GetSymbolTable().GetFriend("Position");
        EXPECT_TRUE(p.ok);
        auto xid = p.result->Get(Yolk::Memory::SymbolKey("x"));
        EXPECT_TRUE(xid.ok);
        int w = GetWrapperTable().CopyField(xid.value.key).field->As<int>();
        return w;
    }

    int GetPosY()
    {
        auto p = GetMemoryBlock().GetSymbolTable().GetFriend("Position");
        EXPECT_TRUE(p.ok);
        auto xid = p.result->Get(Yolk::Memory::SymbolKey("y"));
        EXPECT_TRUE(xid.ok);
        int w = GetWrapperTable().CopyField(xid.value.key).field->As<int>();
        return w;
    }

};

TEST(Yolk_Test, Object_Test_Child)
{
    YK_God god;
    YKPlayer player(&god);

    int t1 = player.GetHealth();
    EXPECT_EQ(t1, 100);

    player.SetHealth(27);

    int t2 = player.GetHealth();

    EXPECT_EQ(t2, 27);

    int t3 = player.GetPosX();
    int t4 = player.GetPosY();

    EXPECT_EQ(t3, 0);
    EXPECT_EQ(t4, 0);

    player.SetPos(17, -7);
    
    int t5 = player.GetPosX();
    int t6 = player.GetPosY();

    EXPECT_EQ(t5, 17);
    EXPECT_EQ(t6, -7);
}


class MethodDemo : public Yolk::Object
{
    public:
    MethodDemo(Yolk::Object *father, int v) : Object("Method", father), value(v) {
        RegisterMethod<int, int, int>( Yolk::FunctionGenerator<int, int, int>::AsFunction([this](int x, int y){return this->Sum(x, y);}) , "Sum");
        RegisterField(value, "value");
    }

    void ChangeValue(int new_value)
    {
        GetMemoryBlock().GetFieldWrapperByName("value").wrapper.field->Copy(new_value);
    }
    int EvaluateSum(Yolk::Wrapper x, Yolk::Wrapper y)
    {
        auto p = Yolk::WrapperGenerator<>::GenerateArgumentWrapper(x, y);
        auto result = GetMemoryBlock().GetMethodWrapperByName("Sum").wrapper.Invoke(p);

        EXPECT_TRUE(result.ok);
        return result.output.field->As<int>();
    }

    int Sum(int x, int y)
    {
        return x + y + value;
    }

    int value;
};
TEST(Yolk_Test, Object_Method)
{
    YK_God god;
    MethodDemo m(&god, 7);

    auto w1 = Yolk::WrapperGenerator<int>::GenerateDynamicWrapper(14, god.GetMemoryManager());
    auto w2 = Yolk::WrapperGenerator<int>::GenerateDynamicWrapper(27, god.GetMemoryManager());

    int o = m.EvaluateSum(w1, w2);

    EXPECT_EQ(o, 14 + 27 + 7);

    m.ChangeValue(-14);

    int o2 = m.EvaluateSum(w1, w2);

    EXPECT_EQ(o2, 14 + 27 - 14);
}

TEST(Yolk_Test, Object_Memory_NotLeaking)
{
    YK_God god;
    god.GetMemoryManager().Debug();
    MethodDemo *m1 = new MethodDemo(&god, 1);  // Registers one one method and one field. 
    MethodDemo *m2 = new MethodDemo(&god, 1);  //
    MethodDemo *m3 = new MethodDemo(&god, 1);  //
    MethodDemo *m4 = new MethodDemo(&god, 1);  //
    MethodDemo *m5 = new MethodDemo(&god, 1);  //
    MethodDemo *m6 = new MethodDemo(&god, 1);  //
    MethodDemo *m7 = new MethodDemo(&god, 1);  // * 7

    EXPECT_EQ(god.GetMemoryManager().Size(), 7*2 );

    delete(m1);
    delete(m2);
    delete(m3);
    delete(m4);

    EXPECT_EQ(god.GetMemoryManager().Size(), 3*2);

    delete(m5);
    delete(m6);
    delete(m7);

    EXPECT_EQ(god.GetMemoryManager().Size(), 0);
}
class Friends_Object : public Yolk::Object
{
    public:
    Friends_Object(Yolk::Object& father, std::string Name) : Object(Name, &father){
        this->LogCallbackFunction = [](std::string in){std::cout << in << std::endl;};
    }
    void CreateFriend(Friends_Object& object)
    {
        RegisterObject(&object);
    }
    int GetFriendcount()
    {
        return GetObjectCount();
    }
};
TEST(Yolk_Test, Object_Register_Object)
{
    YK_God god;
    Friends_Object obj_a(god, "A");
    Friends_Object obj_b(god, "B");
    Friends_Object *obj_c = new Friends_Object(god, "C");

    obj_a.CreateFriend(obj_b);
    obj_a.CreateFriend(*obj_c);

    EXPECT_EQ(obj_a.GetFriendcount(), 2);

    obj_b.CreateFriend(*obj_c);

    delete(obj_c);

    EXPECT_EQ(obj_a.GetFriendcount(), 1);
    EXPECT_EQ(obj_b.GetFriendcount(), 0);

}