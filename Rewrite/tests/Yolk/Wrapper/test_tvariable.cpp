
#include <gtest/gtest.h>
#include "../../../src/Yolk/Wrapper/TypedField.h"

TEST(Yolk_Test, Typed_Variable_Assignment)
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

TEST(Yolk_Test, Typed_Variable_Assignment_B)
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

TEST(Yolk_Test, Typed_Variable_Assignemnt_C)
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
TEST(Yolk_Test, Typed_Variables_Const)
{
	const int a = 5;
	const float f = 3.14;

	Yolk::TypedField x(a);
	Yolk::TypedField y(f);

	EXPECT_EQ(x.As<int>(), 5);
	EXPECT_FLOAT_EQ(y.As<float>(), 3.14);
	EXPECT_FALSE(x.Copy(9));
}
TEST(Yolk_Test, Typed_Variable_Copy_By_Function)
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

TEST(Yolk_Test, Typed_Variable_Copy_By_Other_Typed_Variable)
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
TEST(Yolk_Test, Typed_Variable_Is_Method)
{
    int a = 4;
    Test_D b;

    Yolk::TypedField x(a);
    Yolk::TypedField y(b);

    EXPECT_TRUE(x.Is<int>());
    EXPECT_TRUE(y.Is<Test_D>());
    EXPECT_FALSE(x.Is<float>());
}

TEST(Yolk_Test, Typed_Variable_Compare_A)
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
};

TEST(Yolk_Test, Typed_Variable_Compare_B)
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
TEST(Yolk_Test, Typed_Variable_Bind)
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
TEST(Yolk_Test, Typed_Variable_EqualComparison)
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

TEST(Yolk_Test, Typed_Variable_Equal_Set)
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
TEST(Yolk_Test, Typed_Variable_Type)
{
    int a = 5;
    TypedStructure b;

    Yolk::TypedField x = a;
    Yolk::TypedField y = b;


    EXPECT_EQ(x.Type(), typeid(int));
    EXPECT_EQ(y.Type(), typeid(TypedStructure));
}

TEST(Yolk_Test, Typed_Variable_Sizeof)
{
    char c = 'x';
    Yolk::TypedField x = c;

    EXPECT_EQ(x.GetSize(), 1);
}
TEST(Yolk_Test, Typed_Variable_SafeAs)
{
    int a = 5;
    Yolk::TypedField x(a);
    int b = 0;
    x.SafeAs<int>(b);
    EXPECT_EQ(b, 5);
}
TEST(Yolk_Test, Typed_Variable_BindToTypedVariable)
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
TEST(Yolk_Test, Typed_Variable_Stability_A)
{
    Yolk::TypedField x;
    Yolk::TypedField y(x);
    Yolk::TypedField z(x);

    z.Copy(x);
    y.Copy(3);
    z.Set(4);

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
TEST(Yolk_Test, Typed_Variable_Print_A)
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
TEST(Yolk_Test, Typed_Variable_Print_B)
{
    TVPB a;
    Yolk::TypedField x = a;
    EXPECT_STREQ(x.Print().c_str(), "[Unknown Object]");
}
TEST(Yolk_Test, Typed_Variable_Comparison_){
    int a = 12;
    int b = 6;

    Yolk::TypedField xa(a);
    Yolk::TypedField xb(b);

    //EQ
    auto cmp = xa.TryEQ(xb);
    EXPECT_TRUE(cmp.ok);
    EXPECT_FALSE(cmp.value);
    cmp = xa.TryEQ(12);
    EXPECT_TRUE(cmp.ok);
    EXPECT_TRUE(cmp.value);
    //LE
    cmp = xa.TryLE(xb);
    EXPECT_TRUE(cmp.ok);
    EXPECT_FALSE(cmp.value);
    cmp = xb.TryLE(xa);
    EXPECT_TRUE(cmp.ok);
    EXPECT_TRUE(cmp.value);
    cmp = xa.TryLE(11);
    EXPECT_TRUE(cmp.ok);
    EXPECT_FALSE(cmp.value);
    cmp = xa.TryLE(14);
    EXPECT_TRUE(cmp.ok);
    EXPECT_TRUE(cmp.value);
    // L
    cmp = xa.TryL(xb);
    EXPECT_TRUE(cmp.ok);
    EXPECT_FALSE(cmp.value);
    cmp = xb.TryL(xa);
    EXPECT_TRUE(cmp.ok);
    EXPECT_TRUE(cmp.value);
    cmp = xa.TryL(11);
    EXPECT_TRUE(cmp.ok);
    EXPECT_FALSE(cmp.value);
    cmp = xa.TryL(12);
    EXPECT_TRUE(cmp.ok);
    EXPECT_FALSE(cmp.value);
    //GE
    cmp = xa.TryGE(xb);
    EXPECT_TRUE(cmp.ok);
    EXPECT_TRUE(cmp.value);
    cmp = xb.TryGE(xa);
    EXPECT_TRUE(cmp.ok);
    EXPECT_FALSE(cmp.value);
    cmp = xa.TryGE(11);
    EXPECT_TRUE(cmp.ok);
    EXPECT_TRUE(cmp.value);
    cmp = xa.TryGE(14);
    EXPECT_TRUE(cmp.ok);
    EXPECT_FALSE(cmp.value);
    // G
    cmp = xa.TryG(xb);
    EXPECT_TRUE(cmp.ok);
    EXPECT_TRUE(cmp.value);
    cmp = xb.TryG(xa);
    EXPECT_TRUE(cmp.ok);
    EXPECT_FALSE(cmp.value);
    cmp = xa.TryG(11);
    EXPECT_TRUE(cmp.ok);
    EXPECT_TRUE(cmp.value);
    cmp = xa.TryG(12);
    EXPECT_TRUE(cmp.ok);
    EXPECT_FALSE(cmp.value);
    // NEQ
    cmp = xa.TryNEQ(xb);
    EXPECT_TRUE(cmp.ok);
    EXPECT_TRUE(cmp.value);
    cmp = xa.TryNEQ(12);
    EXPECT_TRUE(cmp.ok);
    EXPECT_FALSE(cmp.value);
}
TEST(Yolk_Test, Typed_Variable_Operators){
    int a = 12;
    int b = 4;

    Yolk::TypedField xa(a);
    Yolk::TypedField xb(b);

    EXPECT_TRUE(xa.TryPLUS(xb));
    EXPECT_EQ(xa.As<int>(), 16);
    EXPECT_TRUE(xa.TryPLUS(-4));
    EXPECT_EQ(xa.As<int>(), 12);
    
    EXPECT_TRUE(xa.TrySUB(xb));
    EXPECT_EQ(xa.As<int>(), 8);
    EXPECT_TRUE(xa.TrySUB(-4));
    EXPECT_EQ(xa.As<int>(), 12);

    EXPECT_TRUE(xa.TryPROD(xb));
    EXPECT_EQ(xa.As<int>(), 48);
    EXPECT_TRUE(xa.TryDIV(4));
    EXPECT_EQ(xa.As<int>(), 12); 
    
    EXPECT_TRUE(xa.TryDIV(xb));
    EXPECT_EQ(xa.As<int>(), 3);
    EXPECT_TRUE(xa.TryPROD(4));
    EXPECT_EQ(xa.As<int>(), 12);

    EXPECT_TRUE(xa.TryMOD(xb));
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
TEST(Yolk_Test, Typed_Variable_Comparison_Struct){
    auto x = CompIntEQ{12};
    Yolk::TypedField xr(x);

    auto cmp = xr.TryEQ(12);
    EXPECT_TRUE(cmp.ok);
    EXPECT_TRUE(cmp.value);
    cmp = xr.TryLE(15);
    EXPECT_TRUE(cmp.ok);
    EXPECT_TRUE(cmp.value);
    cmp = xr.TryGE(21);
    EXPECT_TRUE(cmp.ok);
    EXPECT_FALSE(cmp.value);
    cmp = xr.TryL(9);
    EXPECT_TRUE(cmp.ok);
    EXPECT_FALSE(cmp.value);
    cmp = xr.TryG(9);
    EXPECT_TRUE(cmp.ok);
    EXPECT_TRUE(cmp.value);
    cmp = xr.TryNEQ(12);
    EXPECT_TRUE(cmp.ok);
    EXPECT_FALSE(cmp.value);
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
TEST(Yolk_Test, Typed_Variable_Arithmetic_Struct){
    ProdInt x{12};
    Yolk::TypedField xr(x);

    EXPECT_TRUE(xr.TryPLUS(4));
    EXPECT_TRUE(xr.TryEQ(16).value);
    
    EXPECT_TRUE(xr.TrySUB(8));
    EXPECT_TRUE(xr.TryEQ(8).value);

    EXPECT_TRUE(xr.TryPROD(6));
    EXPECT_TRUE(xr.TryEQ(48).value);

    EXPECT_TRUE(xr.TryDIV(2));
    EXPECT_TRUE(xr.TryEQ(24).value);

    EXPECT_TRUE(xr.TryMOD(16));
    EXPECT_TRUE(xr.TryEQ(24 % 16).value);
}
TEST(Yolk_Test, Typed_Variable_Comparison_DoubleInt){
    double x = 12;
    Yolk::TypedField xr(x);

    auto cmp = xr.TryEQ(12);
    EXPECT_TRUE(cmp.ok);
    EXPECT_TRUE(cmp.value);
    cmp = xr.TryLE(15);
    EXPECT_TRUE(cmp.ok);
    EXPECT_TRUE(cmp.value);
    cmp = xr.TryGE(21);
    EXPECT_TRUE(cmp.ok);
    EXPECT_FALSE(cmp.value);
    cmp = xr.TryL(9);
    EXPECT_TRUE(cmp.ok);
    EXPECT_FALSE(cmp.value);
    cmp = xr.TryG(9);
    EXPECT_TRUE(cmp.ok);
    EXPECT_TRUE(cmp.value);
    cmp = xr.TryNEQ(12);
    EXPECT_TRUE(cmp.ok);
    EXPECT_FALSE(cmp.value);
}
TEST(Yolk_Test, Typed_Variable_Arithmetic_DoubleInt){
    double x = 12;
    Yolk::TypedField xr(x);

    EXPECT_TRUE(xr.TryPLUS(4));
    EXPECT_FLOAT_EQ(x, 16.0);
    
    EXPECT_TRUE(xr.TrySUB(8));
    EXPECT_FLOAT_EQ(x, 8.0);

    EXPECT_TRUE(xr.TryPROD(6));
    EXPECT_FLOAT_EQ(x, 48.0);

    EXPECT_TRUE(xr.TryDIV(2));
    EXPECT_FLOAT_EQ(x, 24.0);
}
struct Demo{
    int x = 1;
};
TEST(Yolk_Test, Typed_Variable_Stability_B){
    int x = 12;
    Demo y;
    
    Yolk::TypedField xr(x);
    Yolk::TypedField yr(y);

    auto check = xr.TryEQ(y);
    EXPECT_FALSE(check.ok);
    check = xr.TryLE(yr);
    EXPECT_FALSE(check.ok);
    check = xr.TryGE(yr);
    EXPECT_FALSE(check.ok);
    bool check2 = xr.TryPROD(yr);
    EXPECT_FALSE(check2);
    check2 = xr.TrySUB(yr);
    EXPECT_FALSE(check2);
    check2 = xr.TryPLUS(yr);
    EXPECT_FALSE(check2);
}