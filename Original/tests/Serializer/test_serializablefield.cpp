#include "../../src/Yolk/Serializable/Serializable.h"
#include <gtest/gtest.h>
#include <string>

class A_Class : public Yolk::Serializer::Serializable
{
    public:
    A_Class(int _a, unsigned long int _c, long double _d, std::string _e, std::vector<int> _f) :
        a(_a), c(_c), d(_d), e(_e), f(_f){}
    
    
    SerializableField(int, a);
    SerializableField(char, b) = 'd';
    unsigned long int c;
    long double d;
    SerializableField(std::string, e);
    std::vector<int> f;

    SerializeField(unsigned long int, c);
    SerializeField(long double, d);
    SerializeField(std::vector<int>, f);
};

TEST(Test_SerializableField, Serializable_Basic_A)
{
    A_Class A(3, 147, 12.8, "Hello buddy!", {3, 7, 9, 12});
    A_Class B(9, 121, 1.78, "My neighbour hates me!", {1, 1, 1});
    A.b = 'k';

    std::string A_As_String = A.Save();
    std::cout << A_As_String << std::endl;
    B.Load(A_As_String);

    EXPECT_EQ(B.a, 3);
    EXPECT_EQ(B.b, 'k');
    EXPECT_EQ(B.c, 147);
    EXPECT_DOUBLE_EQ(B.d, 12.8);
    EXPECT_STREQ(B.e.c_str(), "Hello buddy!");
    EXPECT_EQ(B.f[0], 3);
    EXPECT_EQ(B.f[1], 7);
    EXPECT_EQ(B.f[2], 9);
    EXPECT_EQ(B.f[3], 12);
}

class B_Class : public Yolk::Serializer::Serializable
{
    public:
    B_Class(int _a, unsigned long int _c, long double _d, std::string _e, std::vector<int> _f, bool _g, std::map<int, float> _h) :
        A(_a, _c, _d, _e, _f), g(_g), h(_h){}

    SerializableField(A_Class, A);
    bool g;
    std::map<int, float> h;

    SerializeField(bool, g);
    SerializeField((std::map<int, float>), h);
};

TEST(Test_SerializableField, Serializable_Basic_B)
{
    B_Class b1(2, 3, 4.0, "teste", {1, 5, 9}, true, {{1, 1.0}, {2, 2.0}});
    B_Class b2(3, 1, 1.0, "toste", {0, 1, 2}, false, {{3, 4.0}, {5, 6.0}});

    std::string input = b1.Save();
    b2.Load(input);

    EXPECT_EQ(b2.A.a, 2);
    EXPECT_EQ(b2.A.c, 3);
    EXPECT_DOUBLE_EQ(b2.A.d, 4.0);
    EXPECT_STREQ(b2.A.e.c_str(), "teste");
    EXPECT_EQ(b2.A.f[0], 1);
    EXPECT_EQ(b2.A.f[1], 5);
    EXPECT_EQ(b2.A.f[2], 9);
    EXPECT_TRUE(b2.g);
    EXPECT_FLOAT_EQ(b2.h[1], 1.0);
    EXPECT_FLOAT_EQ(b2.h[2], 2.0);

}

struct Custom
{  
    Custom(){}
    int value;
    std::string Save()
    {
        return std::to_string(value);
    }
    void Load(std::string input)
    {
        value = std::atoi(input.c_str());
    }
};

class C_Class : public Yolk::Serializer::Serializable
{
    public:
    C_Class(int _value)
    {
        c.value = _value;
    }
    SerializableField(Custom, c);
};

TEST(Test_SerializableField, Serializable_Basic_C)
{
    C_Class A(12);
    C_Class B(-5);

    std::string save = A.Save();
    B.Load(save);

    EXPECT_EQ(B.c.value, 12);
}

struct CustomB
{
    int value;
};
std::string LoadCustomB(CustomB a)
{
    return std::to_string(a.value);
}
void SaveCustomB(std::string input, CustomB& obj)
{
    obj.value = std::atoi(input.c_str());
}
class D_Class : public Yolk::Serializer::Serializable
{
    public:
    SerializableField_SD(CustomB, a, LoadCustomB, SaveCustomB);

};
TEST(Test_SerializableField, Serializable_Basic_D)
{
    D_Class a;
    a.a.value = 8;
    D_Class b;
    b.a.value = -7;

    std::string save = a.Save();
    b.Load(save);

    EXPECT_EQ(b.a.value, 8);
}

struct Vec3
{
    double x;
    double y;
    double z;
};
namespace Yolk
{
    namespace Serializer
    {
        template<>
        struct Serializer<Vec3>
        {
            static std::string Serialize(Vec3& object)
            {
                std::string out = std::to_string(object.x) + ";" + std::to_string(object.y) + ";" + std::to_string(object.z) + ";";
                return out;
            }
        };
        template<>
        struct Deserializer<Vec3>
        {
            static void Deserialize(std::string input, Vec3& object)
            {
                double x;
                double y;
                double z;
                int c = 0;
                std::string tmp = "";
                for(std::string::iterator it = input.begin(); it != input.end(); it++)
                {
                    if(*it == ';')
                    {
                        if(c == 0)
                            x = std::atof(tmp.c_str());
                        else if(c == 1)
                            y = std::atof(tmp.c_str());
                        else
                            z = std::atof(tmp.c_str());

                        c++;
                        tmp = "";
                    }
                    else
                    {
                        tmp += *it;
                    }
                }
                object.x = x;
                object.y = y;
                object.z = z;
            }
        };
    }   
}

class Demo : public Yolk::Serializer::Serializable
{
    public:
    Demo(double x, double y, double z) : Position()
    {
        Position.x = x;
        Position.y = y;
        Position.z = z;
    }

    Vec3 Position;
    SerializeField(Vec3, Position);
};

TEST(Test_SerializableField, SerializerOverload)
{
    Demo demo(7, 4.1, 3);
    std::string save = demo.Save();
    Demo demob(0, 0, 0);
    demob.Load(save);
    EXPECT_DOUBLE_EQ(demob.Position.x, 7);
    EXPECT_DOUBLE_EQ(demob.Position.y, 4.1);
    EXPECT_DOUBLE_EQ(demob.Position.z, 3);
}
