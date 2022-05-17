#include <gtest/gtest.h>
#include "../../../src/Yolk/YolkVM/OVO.h"

using Data = Yolk::VM::OVO::Data;

TEST(Yolk_Test, OVO_Data_INT)
{
    Yolk::Memory::MemoryManager manager;
    int x = 12;

    Data d(x);
    Yolk::Wrapper w = Data::ToWrapper(d, manager);

    EXPECT_EQ(w.field->As<int>(), 12);
    EXPECT_EQ(w.field->GetType(), typeid(int));

    Data d2 = Data::GenerateData<int>(121);
    Yolk::Wrapper w2 = Data::ToWrapper(d2, manager);
    EXPECT_EQ(w2.field->As<int>(), 121);
    EXPECT_EQ(w2.field->GetType(), typeid(int));

}
TEST(Yolk_Test, OVO_Data_UINT)
{

    Yolk::Memory::MemoryManager manager;
    unsigned int x = 12;

    Data d(x);
    Yolk::Wrapper w = Data::ToWrapper(d, manager);

    EXPECT_LE(w.field->As<unsigned int>(), 12);
    EXPECT_EQ(w.field->GetType(), typeid(unsigned int));

    Data d2 = Data::GenerateData<unsigned int>(121);
    Yolk::Wrapper w2 = Data::ToWrapper(d2, manager);
    EXPECT_EQ(w2.field->As<unsigned int>(), 121);
    EXPECT_EQ(w2.field->GetType(), typeid(unsigned int));

}
TEST(Yolk_Test, OVO_Data_LONG)
{

    Yolk::Memory::MemoryManager manager;
    long x = 12;

    Data d(x);
    Yolk::Wrapper w = Data::ToWrapper(d, manager);

    EXPECT_EQ(w.field->As<long>(), 12);
    EXPECT_EQ(w.field->GetType(), typeid(long));

    Data d2 = Data::GenerateData<long>(121);
    Yolk::Wrapper w2 = Data::ToWrapper(d2, manager);
    EXPECT_EQ(w2.field->As<long>(), 121);
    EXPECT_EQ(w2.field->GetType(), typeid(long));

}
TEST(Yolk_Test, OVO_Data_ULONG)
{

    Yolk::Memory::MemoryManager manager;
    unsigned long x = 12;

    Data d(x);
    Yolk::Wrapper w = Data::ToWrapper(d, manager);

    EXPECT_EQ(w.field->As<unsigned int>(), 12);
    EXPECT_EQ(w.field->GetType(), typeid(unsigned long));

    Data d2 = Data::GenerateData<unsigned long>(121);
    Yolk::Wrapper w2 = Data::ToWrapper(d2, manager);
    EXPECT_EQ(w2.field->As<unsigned long>(), 121);
    EXPECT_EQ(w2.field->GetType(), typeid(unsigned long));

}
TEST(Yolk_Test, OVO_Data_FLOAT)
{

    Yolk::Memory::MemoryManager manager;
    float x = 12.3f;

    Data d(x);
    Yolk::Wrapper w = Data::ToWrapper(d, manager);

    EXPECT_FLOAT_EQ(w.field->As<float>(), 12.3f);
    EXPECT_EQ(w.field->GetType(), typeid(float));

    Data d2 = Data::GenerateData<float>(121.1f);
    Yolk::Wrapper w2 = Data::ToWrapper(d2, manager);
    EXPECT_FLOAT_EQ(w2.field->As<float>(), 121.1f);
    EXPECT_EQ(w2.field->GetType(), typeid(float));

}
TEST(Yolk_Test, OVO_Data_DOUBLE)
{

    Yolk::Memory::MemoryManager manager;
    double x = 12.1;

    Data d(x);
    Yolk::Wrapper w = Data::ToWrapper(d, manager);

    EXPECT_DOUBLE_EQ(w.field->As<double>(), 12.1);
    EXPECT_EQ(w.field->GetType(), typeid(double));

    Data d2 = Data::GenerateData<double>(121.1);
    Yolk::Wrapper w2 = Data::ToWrapper(d2, manager);
    EXPECT_DOUBLE_EQ(w2.field->As<double>(), 121.1);
    EXPECT_EQ(w2.field->GetType(), typeid(double));

}
TEST(Yolk_Test, OVO_Data_BOOL)
{

    Yolk::Memory::MemoryManager manager;
    bool x = true;

    Data d(x);
    Yolk::Wrapper w = Data::ToWrapper(d, manager);

    EXPECT_TRUE(w.field->As<bool>());
    EXPECT_EQ(w.field->GetType(), typeid(bool));

    Data d2 = Data::GenerateData<bool>(false);
    Yolk::Wrapper w2 = Data::ToWrapper(d2, manager);
    EXPECT_FALSE(w2.field->As<bool>());
    EXPECT_EQ(w2.field->GetType(), typeid(bool));

}
TEST(Yolk_Test, OVO_Data_CHAR)
{

    Yolk::Memory::MemoryManager manager;
    char x = 'x';

    Data d(x);
    Yolk::Wrapper w = Data::ToWrapper(d, manager);

    EXPECT_EQ(w.field->As<char>(), 'x');
    EXPECT_EQ(w.field->GetType(), typeid(char));

    Data d2 = Data::GenerateData<char>('y');
    Yolk::Wrapper w2 = Data::ToWrapper(d2, manager);
    EXPECT_EQ(w2.field->As<char>(), 'y');
    EXPECT_EQ(w2.field->GetType(), typeid(char));

}
TEST(Yolk_Test, OVO_Data_UCHAR)
{

    Yolk::Memory::MemoryManager manager;
    unsigned char x = 12;

    Data d(x);
    Yolk::Wrapper w = Data::ToWrapper(d, manager);

    EXPECT_EQ(w.field->As<unsigned char>(), 12);
    EXPECT_EQ(w.field->GetType(), typeid(unsigned char));

    Data d2 = Data::GenerateData<unsigned char>(0xf0);
    Yolk::Wrapper w2 = Data::ToWrapper(d2, manager);
    EXPECT_EQ(w2.field->As<unsigned char>(), 0xf0);
    EXPECT_EQ(w2.field->GetType(), typeid(unsigned char));

}
TEST(Yolk_Test, OVO_Data_STRING)
{

    Yolk::Memory::MemoryManager manager;
    std::string x = "Hello John!";

    Data d(x);
    Yolk::Wrapper w = Data::ToWrapper(d, manager);

    EXPECT_STREQ(w.field->As<std::string>().c_str(), "Hello John!");
    EXPECT_EQ(w.field->GetType(), typeid(std::string));

    Data d2 = Data::GenerateData<std::string>("Hello William!");
    Yolk::Wrapper w2 = Data::ToWrapper(d2, manager);
    EXPECT_STREQ(w2.field->As<std::string>().c_str(), "Hello William!");
    EXPECT_EQ(w2.field->GetType(), typeid(std::string));

}
struct AStruct{};
TEST(Yolk_Test, OVO_Data_VOID)
{

    Yolk::Memory::MemoryManager manager;
    AStruct x;

    Data d(x);
    Yolk::Wrapper w = Data::ToWrapper(d, manager);

    EXPECT_EQ(d.mode, Data::Mode::VOID);
    EXPECT_FALSE(w.field->Valid());
}

TEST(Yolk_Test, OVO_Data_STR_INT)
{
    Yolk::Memory::MemoryManager manager;
    int x = 12;

    Data d(x);

    std::string str = Data::ToString(d);

    auto d2 = Data::FromString(str);

    EXPECT_EQ(d2.size, d.size);
    EXPECT_EQ(d2.mode, d.mode);

    Data::Usize size = sizeof(Data::Usize) + sizeof(Data::Mode) + d.size;
    Data::Usize strsize = str.length() * sizeof(Data::Byte) / sizeof(char);
    EXPECT_EQ(size, strsize);

    auto w = Data::ToWrapper(d2, manager);
    EXPECT_STREQ(w.field->Print().c_str(), "12");

}
TEST(Yolk_Test, OVO_DATA_STR_UINT)
{


    Yolk::Memory::MemoryManager manager;
    unsigned int x = 12;

    Data d(x);

    std::string str = Data::ToString(d);

    auto d2 = Data::FromString(str);

    EXPECT_EQ(d2.size, d.size);
    EXPECT_EQ(d2.mode, d.mode);

    Data::Usize size = sizeof(Data::Usize) + sizeof(Data::Mode) + d.size;
    Data::Usize strsize = str.length() * sizeof(Data::Byte) / sizeof(char);
    EXPECT_EQ(size, strsize);

    auto w = Data::ToWrapper(d2, manager);
    EXPECT_STREQ(w.field->Print().c_str(), "12");

}
TEST(Yolk_Test, OVO_DATA_STR_LONG)
{

    Yolk::Memory::MemoryManager manager;
    long x = 12;

    Data d(x);

    std::string str = Data::ToString(d);

    auto d2 = Data::FromString(str);

    EXPECT_EQ(d2.size, d.size);
    EXPECT_EQ(d2.mode, d.mode);

    Data::Usize size = sizeof(Data::Usize) + sizeof(Data::Mode) + d.size;
    Data::Usize strsize = str.length() * sizeof(Data::Byte) / sizeof(char);
    EXPECT_EQ(size, strsize);

    auto w = Data::ToWrapper(d2, manager);
    EXPECT_STREQ(w.field->Print().c_str(), "12");

}
TEST(Yolk_Test, OVO_DATA_STR_ULONG)
{

    Yolk::Memory::MemoryManager manager;
    unsigned long x = 12;

    Data d(x);

    std::string str = Data::ToString(d);

    auto d2 = Data::FromString(str);

    EXPECT_EQ(d2.size, d.size);
    EXPECT_EQ(d2.mode, d.mode);

    Data::Usize size = sizeof(Data::Usize) + sizeof(Data::Mode) + d.size;
    Data::Usize strsize = str.length() * sizeof(Data::Byte) / sizeof(char);
    EXPECT_EQ(size, strsize);

    auto w = Data::ToWrapper(d2, manager);
    EXPECT_STREQ(w.field->Print().c_str(), "12");

}
TEST(Yolk_Test, OVO_DATA_STR_FLOAT)
{

    Yolk::Memory::MemoryManager manager;
    float x = 12.1f;

    Data d(x);

    std::string str = Data::ToString(d);

    auto d2 = Data::FromString(str);

    EXPECT_EQ(d2.size, d.size);
    EXPECT_EQ(d2.mode, d.mode);

    Data::Usize size = sizeof(Data::Usize) + sizeof(Data::Mode) + d.size;
    Data::Usize strsize = str.length() * sizeof(Data::Byte) / sizeof(char);
    EXPECT_EQ(size, strsize);

    auto w = Data::ToWrapper(d2, manager);
    EXPECT_STREQ(w.field->Print().c_str(), "12.1");

}
TEST(Yolk_Test, OVO_DATA_STR_DOUBLE)
{

    Yolk::Memory::MemoryManager manager;
    double x = 12.3;

    Data d(x);

    std::string str = Data::ToString(d);

    auto d2 = Data::FromString(str);

    EXPECT_EQ(d2.size, d.size);
    EXPECT_EQ(d2.mode, d.mode);

    Data::Usize size = sizeof(Data::Usize) + sizeof(Data::Mode) + d.size;
    Data::Usize strsize = str.length() * sizeof(Data::Byte) / sizeof(char);
    EXPECT_EQ(size, strsize);

    auto w = Data::ToWrapper(d2, manager);
    EXPECT_STREQ(w.field->Print().c_str(), "12.3");

}
TEST(Yolk_Test, OVO_DATA_STR_BOOL)
{

    Yolk::Memory::MemoryManager manager;
    bool x = true;

    Data d(x);

    std::string str = Data::ToString(d);

    auto d2 = Data::FromString(str);

    EXPECT_EQ(d2.size, d.size);
    EXPECT_EQ(d2.mode, d.mode);

    Data::Usize size = sizeof(Data::Usize) + sizeof(Data::Mode) + d.size;
    Data::Usize strsize = str.length() * sizeof(Data::Byte) / sizeof(char);
    EXPECT_EQ(size, strsize);

    auto w = Data::ToWrapper(d2, manager);
    EXPECT_STREQ(w.field->Print().c_str(), "1");

}
TEST(Yolk_Test, OVO_DATA_STR_CHAR)
{

    Yolk::Memory::MemoryManager manager;
    char x = 't';

    Data d(x);

    std::string str = Data::ToString(d);

    auto d2 = Data::FromString(str);

    EXPECT_EQ(d2.size, d.size);
    EXPECT_EQ(d2.mode, d.mode);

    Data::Usize size = sizeof(Data::Usize) + sizeof(Data::Mode) + d.size;
    Data::Usize strsize = str.length() * sizeof(Data::Byte) / sizeof(char);
    EXPECT_EQ(size, strsize);

    auto w = Data::ToWrapper(d2, manager);
    EXPECT_STREQ(w.field->Print().c_str(), "t");

}
TEST(Yolk_Test, OVO_DATA_STR_UCHAR)
{

    Yolk::Memory::MemoryManager manager;
    unsigned char x = 'a';

    Data d(x);

    std::string str = Data::ToString(d);

    auto d2 = Data::FromString(str);

    EXPECT_EQ(d2.size, d.size);
    EXPECT_EQ(d2.mode, d.mode);

    Data::Usize size = sizeof(Data::Usize) + sizeof(Data::Mode) + d.size;
    Data::Usize strsize = str.length() * sizeof(Data::Byte) / sizeof(char);
    EXPECT_EQ(size, strsize);

    auto w = Data::ToWrapper(d2, manager);
    EXPECT_STREQ(w.field->Print().c_str(), "a");

}
TEST(Yolk_Test, OVO_DATA_STR_STRING)
{

    Yolk::Memory::MemoryManager manager;
    std::string x = "Aloha!";

    Data d(x);

    std::string str = Data::ToString(d);

    auto d2 = Data::FromString(str);

    EXPECT_EQ(d2.size, d.size);
    EXPECT_EQ(d2.mode, d.mode);

    Data::Usize size = sizeof(Data::Usize) + sizeof(Data::Mode) + d.size;
    Data::Usize strsize = str.length() * sizeof(Data::Byte) / sizeof(char);
    EXPECT_EQ(size, strsize);

    auto w = Data::ToWrapper(d2, manager);
    EXPECT_STREQ(w.field->Print().c_str(), "Aloha!");

}
TEST(Yolk_Test, OVO_DATA_STR_VOID)
{

    Yolk::Memory::MemoryManager manager;
    AStruct x;

    Data d(x);

    std::string str = Data::ToString(d);

    auto d2 = Data::FromString(str);

    EXPECT_EQ(d2.size, d.size);
    EXPECT_EQ(d2.mode, d.mode);

    Data::Usize size = sizeof(Data::Usize) + sizeof(Data::Mode) + d.size;
    Data::Usize strsize = str.length() * sizeof(Data::Byte) / sizeof(char);
    EXPECT_EQ(size, strsize);

    auto w = Data::ToWrapper(d2, manager);
    EXPECT_STREQ(w.field->Print().c_str(), "[None]");

}
