
#include <gtest/gtest.h>
#include "../../../src/Yolk/Yolk.h"

TEST(Yolk_Test, Typed_Variable_Assignment)
{
    int a = 5;
    float b = 3.14;

    Yolk::TypedField x(a);
    Yolk::TypedField y = b;

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
    
    Yolk::TypedField x = a;
    Yolk::TypedField y = b;

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
	Yolk::TypedField y = f;

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

    Yolk::TypedField x = a;
    Yolk::TypedField y = b;

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

    Yolk::TypedField x = a;
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

    Yolk::TypedField x = a;
    Yolk::TypedField y = b;
    Yolk::TypedField z = c;

    EXPECT_TRUE(x.Compare(y));
    EXPECT_TRUE(x.Compare(1));
    EXPECT_TRUE(x.Compare(b));
    EXPECT_FALSE(x.Compare(z));
    EXPECT_FALSE(x.Compare(c));
    EXPECT_FALSE(x.Compare(0));

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

    EXPECT_TRUE(x.Compare(y));
    EXPECT_TRUE(x.Compare(b));
    EXPECT_TRUE(x.Compare(CompareB(0)));
    EXPECT_FALSE(x.Compare(z));
    EXPECT_FALSE(x.Compare(c));
    EXPECT_FALSE(x.Compare(CompareB(1)));

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

TEST(Yolk_Test, Typed_Variable_Create)
{
    Yolk::TypedField x;
    Yolk::TypedField::Create(5, x);

    EXPECT_EQ(x.As<int>(), 5);
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


    EXPECT_EQ(x.GetType(), typeid(int));
    EXPECT_EQ(y.GetType(), typeid(TypedStructure));
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
TEST(Yolk_Test, Typed_Variable_Stability_A)
{
    Yolk::TypedField x;
    Yolk::TypedField y(x);
    Yolk::TypedField z = x;

    z.Copy(x);
    y.Copy(3);
    z.Set(4);

    z.GetType();
    x.GetSize();

    x == y;
    
    y == 4.1;
    z.Compare(y);
    z.Compare(8);

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