
#include <gtest/gtest.h>
#include "../../../src/Yolk/Core/Core.h"

TEST(TypedField, Assignment)
{
    int a = 5;
    float b = 3.14;

    Yolk::TypedField x(a);
    Yolk::TypedField y(b);

    EXPECT_EQ(x.As<int>(), 5);
    EXPECT_FLOAT_EQ(y.As<float>(), 3.14);
}

struct Test_B
{
    Test_B(int x) : r(x){}
    int r;
};

TEST(TypedField, Assignment_B)
{
    int a = 5;
    Test_B b(7);
    
    Yolk::TypedField x(a);
    Yolk::TypedField y(b);

    x.Set(7);
    y.As<Test_B>().r = 3;

    EXPECT_EQ(a, 7);
    EXPECT_EQ(b.r, 3);
}

TEST(TypedField, Assignemnt_C)
{
    int a = 1;
    int b = 2;

    Yolk::TypedField x(a);
    Yolk::TypedField y(b);

    x.Set(b);

    EXPECT_EQ(a, 2);

    x.Set(7);

    // Set changes rvalue
    EXPECT_EQ(a, 7);
    // Set does not change lvalue
    EXPECT_EQ(b, 2);
}
TEST(TypedField, Typed_Variables_Const)
{
	const int a = 5;
	const float f = 3.14;

	Yolk::TypedField x(a);
	Yolk::TypedField y(f);

	EXPECT_EQ(x.As<int>(), 5);
	EXPECT_FLOAT_EQ(y.As<float>(), 3.14);
	EXPECT_FALSE(x.Copy(9));
}
TEST(TypedField, Copy_By_Function)
{
    int a = 1;
    int b = 2;

    Yolk::TypedField x(a);
    Yolk::TypedField y(b);

    x.Copy(y);

    // Copy copies the value
    EXPECT_EQ(a, 2);
    EXPECT_EQ(b, 2);
    EXPECT_EQ(x.As<int>(), a);
    EXPECT_EQ(y.As<int>(), b);

    a = 5;

    // Copy doesn not change the reference

    EXPECT_EQ(a, 5);
    EXPECT_EQ(b, 2);
    EXPECT_EQ(x.As<int>(), a);
    EXPECT_EQ(y.As<int>(), b);
}

TEST(TypedField, Copy_By_Other_Typed_Variable)
{
    int a = 2;
    int b = 5;

    Yolk::TypedField x(a);
    Yolk::TypedField y(b);

    x = y;

    EXPECT_EQ(a, 5);
}

struct Test_D
{
    Test_D() : a(0){}
    int a;
};
TEST(TypedField, Is_Method)
{
    int a = 4;
    Test_D b;

    Yolk::TypedField x(a);
    Yolk::TypedField y(b);

    EXPECT_TRUE(x.Is<int>());
    EXPECT_TRUE(y.Is<Test_D>());
    EXPECT_FALSE(x.Is<float>());
}

TEST(TypedField, Compare_A)
{
    int a = 1;
    int b = 1;
    int c = 0;

    Yolk::TypedField x(a);
    Yolk::TypedField y(b);
    Yolk::TypedField z(c);

    EXPECT_TRUE(x == y);
    EXPECT_TRUE(x == 1);
    EXPECT_TRUE(x == b);
    EXPECT_FALSE(x == z);
    EXPECT_FALSE(x == c);
    EXPECT_FALSE(x == 0);

}

struct CompareB
{
    CompareB(int x) : a(x){}
    int a;
    friend bool operator==(const CompareB& lhs, const CompareB& rhs)
    {
        return lhs.a == rhs.a;
    }
};


TEST(TypedField, Compare_BDemo)
{
    constexpr bool canCompare = requires(CompareB lhs, CompareB rhs){
        lhs == rhs;
    };
    EXPECT_TRUE(canCompare);
}
TEST(TypedField, Compare_B)
{
    CompareB a(0);
    CompareB b(0);
    CompareB c(1);

    Yolk::TypedField x(a);
    Yolk::TypedField y(b);
    Yolk::TypedField z(c);

    EXPECT_TRUE(x == y);
    EXPECT_TRUE(x == b);
    EXPECT_TRUE(x == CompareB(0));
    EXPECT_FALSE(x == z);
    EXPECT_FALSE(x == c);
    EXPECT_FALSE(x == CompareB(1));

}
TEST(TypedField, Bind)
{
    int a = 1;
    int b = 2;

    Yolk::TypedField x(a);

    x.Bind(b);
    x.Set(3);
    EXPECT_EQ(a, 1);
    EXPECT_EQ(b, 3);
    x.Bind(a);
    a = -1;
    EXPECT_EQ(x.As<int>(), -1);
    EXPECT_EQ(b, 3);
    x.Set(-7);
    EXPECT_EQ(a, -7);
    EXPECT_EQ(b, 3);
}
TEST(TypedField, EqualComparison)
{
    CompareB a(0);
    CompareB b(0);
    CompareB c(1);

    Yolk::TypedField x(a);
    Yolk::TypedField y(b);
    Yolk::TypedField z(c);

    EXPECT_TRUE(x == y);
    EXPECT_TRUE(x == b);
    EXPECT_TRUE(x == CompareB(0));
    EXPECT_FALSE(x == z);
    EXPECT_FALSE(x == c);
    EXPECT_FALSE(x == CompareB(1));

}

TEST(TypedField, Equal_Set)
{
    int a = 5;
    int b = 3;

    Yolk::TypedField x = a;  // x = a
    Yolk::TypedField y = b;  // y = b
    Yolk::TypedField z = y;  // z = b

    EXPECT_EQ(x.As<int>(), 5);
    EXPECT_EQ(y.As<int>(), 3);
    EXPECT_EQ(z.As<int>(), 3);

    x = 7;  // x = a = 7
    y = x;  // y = b = 7
    z = b; //  y = z = b = 7

    EXPECT_EQ(x.As<int>(), 7);
    EXPECT_EQ(y.As<int>(), 7);
    EXPECT_EQ(z.As<int>(), 7);    
    
    EXPECT_EQ(a, 7);
    EXPECT_EQ(b, 7);
}

struct TypedStructure
{
    int a;
};
TEST(TypedField, Type)
{
    int a = 5;
    TypedStructure b;

    Yolk::TypedField x = a;
    Yolk::TypedField y = b;


    EXPECT_EQ(x.Type(), typeid(int));
    EXPECT_EQ(y.Type(), typeid(TypedStructure));
}

TEST(TypedField, Sizeof)
{
    char c = 'x';
    Yolk::TypedField x = c;

    EXPECT_EQ(x.GetSize(), 1);
}
TEST(TypedField, SafeAs)
{
    int a = 5;
    Yolk::TypedField x(a);
    int b = 0;
    x.SafeAs<int>(b);
    EXPECT_EQ(b, 5);
}
TEST(TypedField, BindToTypedVariable)
{
    int xi = 5;
    int yi = 12;
    Yolk::TypedField x = xi;
    Yolk::TypedField y = yi;

    y.Bind(x);

    EXPECT_EQ(y.As<int>(), 5);

    y.Copy(121);

    EXPECT_EQ(xi, 121);
}
TEST(TypedField, Stability_A)
{
    Yolk::TypedField x;
    Yolk::TypedField y(x);
    Yolk::TypedField z(x);

    bool test = false;
    try {
        z.Copy(x);
        y.Copy(3);
        z.Set(4);
    } catch(const std::exception&) {
        test = true;
    }
    EXPECT_TRUE(test);

    z.Type();
    x.GetSize();

    x == y;
    
    y == 4.1;
    z == y;
    z == 8;

    int a;

    z.Is<int>();
    z.Free();
    x.Bind(a);
    y.Bind(z);

    int b;
    x.SafeAs<int>(b);
}
TEST(TypedField, Print_A)
{
    int a = 12;
    float f = 7.1;
    char c = 'c';
    Yolk::TypedField x(a);
    Yolk::TypedField y(f);
    Yolk::TypedField z(c);

    EXPECT_STREQ(x.Print().c_str(), "12");
    EXPECT_STREQ(y.Print().c_str(), "7.1");
    EXPECT_STREQ(z.Print().c_str(), "c");
}

struct TVPB
{
};
TEST(TypedField, Print_B)
{
    TVPB a;
    Yolk::TypedField x = a;
    EXPECT_STREQ(x.Print().c_str(), "[Unknown Object]");
}
TEST(TypedField, Comparison_){
    int a = 12;
    int b = 6;

    Yolk::TypedField xa(a);
    Yolk::TypedField xb(b);

    //EQ
    auto cmp = xa.TryEQ(xb);
    EXPECT_FALSE(cmp);
    cmp = xa.TryEQ(12);
    EXPECT_TRUE(cmp);
    //LE
    cmp = xa.TryLE(xb);
    EXPECT_FALSE(cmp);
    cmp = xb.TryLE(xa);
    EXPECT_TRUE(cmp);
    cmp = xa.TryLE(11);
    EXPECT_FALSE(cmp);
    cmp = xa.TryLE(14);
    EXPECT_TRUE(cmp);
    // L
    cmp = xa.TryL(xb);
    EXPECT_FALSE(cmp);
    cmp = xb.TryL(xa);
    EXPECT_TRUE(cmp);
    cmp = xa.TryL(11);
    EXPECT_FALSE(cmp);
    cmp = xa.TryL(12);
    EXPECT_FALSE(cmp);
    //GE
    cmp = xa.TryGE(xb);
    EXPECT_TRUE(cmp);
    cmp = xb.TryGE(xa);
    EXPECT_FALSE(cmp);
    cmp = xa.TryGE(11);
    EXPECT_TRUE(cmp);
    cmp = xa.TryGE(14);
    EXPECT_FALSE(cmp);
    // G
    cmp = xa.TryG(xb);
    EXPECT_TRUE(cmp);
    cmp = xb.TryG(xa);
    EXPECT_FALSE(cmp);
    cmp = xa.TryG(11);
    EXPECT_TRUE(cmp);
    cmp = xa.TryG(12);
    EXPECT_FALSE(cmp);
    // NEQ
    cmp = xa.TryNEQ(xb);
    EXPECT_TRUE(cmp);
    cmp = xa.TryNEQ(12);
    EXPECT_FALSE(cmp);
}
TEST(TypedField, Operators){
    int a = 12;
    int b = 4;

    Yolk::TypedField xa(a);
    Yolk::TypedField xb(b);

    xa.TryPLUS(xb);
    EXPECT_EQ(xa.As<int>(), 16);
    xa.TryPLUS(-4);
    EXPECT_EQ(xa.As<int>(), 12);
    
    xa.TrySUB(xb);
    EXPECT_EQ(xa.As<int>(), 8);
    xa.TrySUB(-4);
    EXPECT_EQ(xa.As<int>(), 12);

    xa.TryPROD(xb);
    EXPECT_EQ(xa.As<int>(), 48);
    xa.TryDIV(4);
    EXPECT_EQ(xa.As<int>(), 12); 
    
    xa.TryDIV(xb);
    EXPECT_EQ(xa.As<int>(), 3);
    xa.TryPROD(4);
    EXPECT_EQ(xa.As<int>(), 12);

    xa.TryMOD(xb);
    EXPECT_EQ(xa.As<int>(), 12 % 4);
}
struct CompIntEQ {
    int value;
    bool operator==(int other){
        return value == other;
    }
    bool operator<=(int other){
        return value <= other;
    }
    bool operator<(int other){
        return value < other;
    }
    bool operator>=(int other){
        return value >= other;
    }
    bool operator>(int other){
        return value > other;
    }
    bool operator!=(int other){
        return value != other;
    }
};
TEST(TypedField, Comparison_Struct){
    auto x = CompIntEQ{12};
    Yolk::TypedField xr(x);

    auto cmp = xr.TryEQ(12);
    EXPECT_TRUE(cmp);
    cmp = xr.TryLE(15);
    EXPECT_TRUE(cmp);
    cmp = xr.TryGE(21);
    EXPECT_FALSE(cmp);
    cmp = xr.TryL(9);
    EXPECT_FALSE(cmp);
    cmp = xr.TryG(9);
    EXPECT_TRUE(cmp);
    cmp = xr.TryNEQ(12);
    EXPECT_FALSE(cmp);
}
struct ProdInt {
    int value;
    void operator=(int other){
        value = other;
    }
    bool operator==(int other){
        return value == other;
    }
    int operator+(int other){
        return value + other;
    }
    int operator-(int other){
        return value - other;
    }
    int operator*(int other){
        return value * other;
    }
    int operator/(int other){
        return value / other;
    }
    int operator%(int other){
        return value % other;
    }
};
TEST(TypedField, Arithmetic_Struct){
    ProdInt x{12};
    Yolk::TypedField xr(x);

    xr.TryPLUS(4);
    EXPECT_TRUE(xr.TryEQ(16));
    
    xr.TrySUB(8);
    EXPECT_TRUE(xr.TryEQ(8));

    xr.TryPROD(6);
    EXPECT_TRUE(xr.TryEQ(48));

    xr.TryDIV(2);
    EXPECT_TRUE(xr.TryEQ(24));

    xr.TryMOD(16);
    EXPECT_TRUE(xr.TryEQ(24 % 16));
}
TEST(TypedField, Comparison_DoubleInt){
    double x = 12;
    Yolk::TypedField xr(x);

    auto cmp = xr.TryEQ(12);
    EXPECT_TRUE(cmp);
    cmp = xr.TryLE(15);
    EXPECT_TRUE(cmp);
    cmp = xr.TryGE(21);
    EXPECT_FALSE(cmp);
    cmp = xr.TryL(9);
    EXPECT_FALSE(cmp);
    cmp = xr.TryG(9);
    EXPECT_TRUE(cmp);
    cmp = xr.TryNEQ(12);
    EXPECT_FALSE(cmp);
}
TEST(TypedField, Arithmetic_DoubleInt){
    double x = 12;
    Yolk::TypedField xr(x);

    xr.TryPLUS(4);
    EXPECT_FLOAT_EQ(x, 16.0);
    
    xr.TrySUB(8);
    EXPECT_FLOAT_EQ(x, 8.0);

    xr.TryPROD(6);
    EXPECT_FLOAT_EQ(x, 48.0);

    xr.TryDIV(2);
    EXPECT_FLOAT_EQ(x, 24.0);
}
struct Demo{};
TEST(TypedField, Stability_B){
    int x = 12;
    Demo y;
    
    Yolk::TypedField xr(x);
    Yolk::TypedField yr(y);

    bool test = false;
    try {
        xr.TryEQ(y);
    } catch(const std::exception&)
    {
        test = true;
    }
    EXPECT_TRUE(test);
    test = false;
    
    try{
        xr.TryLE(yr);
    } catch(const std::exception&)
    {
        test = true;
    }
    EXPECT_TRUE(test);
    test = false;
    
    try{
        xr.TryGE(yr);
    } catch(const std::exception&)
    {
        test = true;
    }
    EXPECT_TRUE(test);
    test = false;
    
    try{
        xr.TryPROD(yr);
    } catch(const std::exception&)
    {
        test = true;
    }
    EXPECT_TRUE(test);
    test = false;

    try{
        xr.TrySUB(yr);
    } catch(const std::exception&)
    {
        test = true;
    }
    EXPECT_TRUE(test);
    test = false;
    
    try{
        xr.TryPLUS(yr);
    } catch(const std::exception&)
    {
        test = true;
    }
    EXPECT_TRUE(test);
    test = false;
}
TEST(TypedField, CopyByValue_A){
    int x = 12;
    Yolk::TypedField xr = x;

    auto cpy = xr.CopyByValue();

    EXPECT_EQ(cpy.field->As<int>(), 12);

    xr = 13;
    *cpy.field = 25;

    EXPECT_EQ(xr.As<int>(), 13);
    EXPECT_EQ(cpy.field->As<int>(), 25);
}
struct cpyval {
    int a;
};
TEST(TypedField, CopyByValue_B){
    cpyval x {12};
    Yolk::TypedField xr = x;

    auto cpy = xr.CopyByValue();

    EXPECT_EQ(cpy.field->As<cpyval>().a, 12);

    x.a = 13;
    (*cpy.field).As<cpyval>().a = 25;

    EXPECT_EQ(xr.As<cpyval>().a, 13);
    EXPECT_EQ(cpy.field->As<cpyval>().a, 25);
}
TEST(TypedField, SET){
    int x = 12;
    float y = 5.0;

    Yolk::TypedField xr = x;
    Yolk::TypedField yr = y;

    yr.TrySET(xr);
    EXPECT_DOUBLE_EQ(yr.As<float>(), 12.0);
    int c = 3;
    yr.TrySET(c);

    EXPECT_DOUBLE_EQ(yr.As<float>(), 3.0f);


    bool ok = true;
    try {
        cpyval a;
        yr.TrySET(a);
    } catch(const Yolk::Exceptions::Exception& )
    {
        ok = false;
    }

    EXPECT_FALSE(ok);
}
TEST(TypedField, SET_B){
    double a = 1.13;
    double b = 1.11;

    Yolk::TypedField ar = a;
    Yolk::TypedField br = b;

    ar.TrySET(br);

    EXPECT_DOUBLE_EQ(ar.As<double>(), 1.11);
}
TEST(TypedField, TryBOOL){
    int i = 13;
    Yolk::TypedField ir = i;

    bool cmp = ir.TryBOOL();

    EXPECT_TRUE(cmp);

    i = 0;

    cmp = ir.TryBOOL();

    EXPECT_FALSE(cmp);
}
TEST(TypedField, Stability_C)
{
    Yolk::TypedField x;
    bool test = false;
    try{
        int y = x.As<int>();
        y = y;
    } catch(const Yolk::TFException&)
    {
        test = true;
    }
    EXPECT_TRUE(test);
}
