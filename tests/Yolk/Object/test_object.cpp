#include <gtest/gtest.h>
#include "../../../src/Yolk/Yolk.h"

class YK_God : public Yolk::Environment
{
    public:
    YK_God(){}
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
        GetMemoryBlock().GetFieldWrapperByName("Health").field->Copy(newHealth);
    }

    int GetHealth()
    {
        return GetMemoryBlock().GetFieldWrapperByName("Health").field->As<int>();
    }

    void SetPos(int x, int y)
    {
        GetMemoryBlock().GetObjectWrapperByName("Environment::Player::Position").field->As<Object>().GetMemoryBlock().GetFieldWrapperByName("x").field->Copy(x);
        GetMemoryBlock().GetObjectWrapperByName("Environment::Player::Position").field->As<Object>().GetMemoryBlock().GetFieldWrapperByName("y").field->Copy(y);
    }

    int GetPosX()
    {
        return GetMemoryBlock().GetObjectWrapperByName("Environment::Player::Position").field->As<YKVec2>().PublicGetMemoryBlock().GetFieldWrapperByName("x").field->As<int>();
    }

    int GetPosY()
    {
        return GetMemoryBlock().GetObjectWrapperByName("Environment::Player::Position").field->As<YKVec2>().PublicGetMemoryBlock().GetFieldWrapperByName("y").field->As<int>();
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

class YKDemo : public Yolk::Object
{
    public:
    YKDemo(std::string Name, Yolk::Object* father, int v) : Object(Name, father), value(v) {
        RegisterField(value, "value");
    }

    int GetChildValue(std::string Name)
    {
        int o = GetMemoryBlock().GetObjectWrapperByName(Name).field->As<YKDemo>().value;
        return o;
    }
    int value;
};
TEST(Yolk_Test, Object_Adoption)
{
    YK_God god;
    YKDemo* a = new YKDemo("a", &god, 1);
    YKDemo* b = new YKDemo("b", a, 2);
    YKDemo* c = new YKDemo("c", b, 3);

    int v = a->GetChildValue("Environment::a::b");
    EXPECT_EQ(v, 2);
    int u = b->GetChildValue("Environment::a::b::c");
    EXPECT_EQ(u, 3);

    delete(b); // now c should be a child of a

    std::string new_loca_name = c->GetLocalName();

    EXPECT_EQ(new_loca_name, "c");

    int w = a->GetChildValue("Environment::a::c");

    EXPECT_EQ(w, 3);

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
        GetMemoryBlock().GetFieldWrapperByName("value").field->Copy(new_value);
    }
    int EvaluateSum(Yolk::Wrapper x, Yolk::Wrapper y)
    {
        auto p = Yolk::WrapperGenerator<>::GenerateArgumentWrapper(x, y);
        auto result = GetMemoryBlock().GetMethodWrapperByName("Sum").Invoke(p);

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
    MethodDemo *m1 = new MethodDemo(&god, 1);  // Registers one object, one method and one field. 
    MethodDemo *m2 = new MethodDemo(&god, 1);  //
    MethodDemo *m3 = new MethodDemo(&god, 1);  //
    MethodDemo *m4 = new MethodDemo(&god, 1);  //
    MethodDemo *m5 = new MethodDemo(&god, 1);  //
    MethodDemo *m6 = new MethodDemo(&god, 1);  //
    MethodDemo *m7 = new MethodDemo(&god, 1);  // * 7

    EXPECT_EQ(god.GetMemoryManager().Size(), 7 * 3);

    delete(m1);
    delete(m2);
    delete(m3);
    delete(m4);

    EXPECT_EQ(god.GetMemoryManager().Size(), 3*3);

    delete(m5);
    delete(m6);
    delete(m7);

    EXPECT_EQ(god.GetMemoryManager().Size(), 0);
}