#include <gtest/gtest.h>
#include "../../../src/Yolk/YolkVM/YVM.h"
#include "../../../src/Yolk/YolkVM/Elementary.h"
#include "../../../src/Yolk/Environment/Environment.h"

class YVM_Tester : public Yolk::Environment, public Yolk::VM::YVM
    {
        using Instruction = Yolk::VM::OVO::Instruction;
        using Arg = Yolk::VM::OVO::Instruction::ARG;
        using Data = Yolk::VM::OVO::Data;
        public:
        YVM_Tester() : YVM(MemoryManager, WrapperTable) 
        {
            Yolk::VM::Elementary::GenerateElementaryOperations(GetOpHandler());
            RegisterField(a, "a");
            RegisterField(b, "b");
            RegisterMethod(Yolk::FunctionGenerator<int, int, int>::AsFunction([this](int x, int y){return this->VMFuncA(x, y);}) , "VMfuncA");
            RegisterMethod(Yolk::FunctionGenerator<bool, int>::AsFunction([this](int x){return this->GreaterThanZero(x);}) , "GreaterThanZero");
        }

        void TEST_MOV()
        {
            Yolk::VM::OVO ovo;
            ovo.InstructionSet.push_back(Instruction{Instruction::INSTRUCTION::MOV, Arg{ Arg::MODE::REG, 0x0}, Arg { Arg::MODE::DATA, 0x0}}); // MOV REGA, a
            ovo.InstructionSet.push_back(Instruction{Instruction::INSTRUCTION::MOV, Arg{ Arg::MODE::REG, 0x1}, Arg { Arg::MODE::REG, 0x0}}); // MOV REGB, REGA
            ovo.DataSet.push_back(Data::GenerateData(std::string("a")));

            Run(ovo, memoryBlock.GetSymbolTable());

            EXPECT_EQ(GetStatus(), Status::HALTED);
            EXPECT_EQ(rega.field->As<int>(), 5);
            EXPECT_EQ(regb.field->As<int>(), 5);

        }
        void TEST_COPY()
        {
            Yolk::VM::OVO ovo;
            ovo.InstructionSet.push_back(Instruction{Instruction::INSTRUCTION::MOV, Arg{ Arg::MODE::REG, 0x0}, Arg { Arg::MODE::DATA, 0x0}}); // MOV REGA, a
            ovo.InstructionSet.push_back(Instruction{Instruction::INSTRUCTION::MOV, Arg{ Arg::MODE::REG, 0x1}, Arg { Arg::MODE::DATA, 0x1}}); // MOV REGB, b
            ovo.InstructionSet.push_back(Instruction{Instruction::INSTRUCTION::COPY, Arg{ Arg::MODE::REG, 0x0}, Arg { Arg::MODE::REG, 0x1}}); // COPY REGA, REGB
            ovo.InstructionSet.push_back(Instruction{Instruction::INSTRUCTION::COPY, Arg{ Arg::MODE::REG, 0x1}, Arg { Arg::MODE::DATA, 0x2}}); // COPY REGB, -17
            ovo.DataSet.push_back(Data::GenerateData(std::string("a")));
            ovo.DataSet.push_back(Data::GenerateData(std::string("b")));
            ovo.DataSet.push_back(Data::GenerateData(-17));

            Run(ovo, memoryBlock.GetSymbolTable());

            EXPECT_EQ(rega.field->As<int>(), 12);
            EXPECT_EQ(regb.field->As<int>(), -17);
            EXPECT_EQ(a, 12);
            EXPECT_EQ(b, -17);
        }

        void TEST_CLONE()
        {
            Yolk::VM::OVO ovo;
            ovo.InstructionSet.push_back(Instruction{Instruction::INSTRUCTION::MOV, Arg{ Arg::MODE::REG, 0x0}, Arg { Arg::MODE::DATA, 0x0}}); // MOV REGA, a
            ovo.InstructionSet.push_back(Instruction{Instruction::INSTRUCTION::CLONE, Arg{ Arg::MODE::REG, 0x1}, Arg { Arg::MODE::REG, 0x0}}); // CLONE REGB, REGA
            ovo.InstructionSet.push_back(Instruction{Instruction::INSTRUCTION::CLONE, Arg{ Arg::MODE::REG, 0x0}, Arg { Arg::MODE::DATA, 0x1}}); // CLONE REGA, 3.14f
            ovo.DataSet.push_back(Data::GenerateData(std::string("a")));
            ovo.DataSet.push_back(Data::GenerateData(3.14f));

            Run(ovo, memoryBlock.GetSymbolTable());

            EXPECT_EQ(GetClock(), 3);
            EXPECT_EQ(GetStatus(), Status::HALTED);
            EXPECT_EQ(regb.field->As<int>(), 5);
            EXPECT_FLOAT_EQ(rega.field->As<float>(), 3.14f);
            EXPECT_EQ(MemoryManager.Size(), 6); // a, b, VMFuncA, a clone, new float
        }

        void TEST_NEW()
        {

            Yolk::VM::OVO ovo;
            ovo.InstructionSet.push_back(Instruction{Instruction::INSTRUCTION::NEW, Arg{ Arg::MODE::REG, 0x0}, Arg { Arg::MODE::SYMBOL, 0x1}}); // NEW REGB, INT
            ovo.InstructionSet.push_back(Instruction{Instruction::INSTRUCTION::NEW, Arg{ Arg::MODE::REG, 0x1}, Arg { Arg::MODE::SYMBOL, 0x5}}); // NEW REGB, FLOAT

            Run(ovo, memoryBlock.GetSymbolTable());

            EXPECT_EQ(GetStatus(), Status::HALTED);
            EXPECT_EQ(rega.field->As<int>(), 0);
            EXPECT_FLOAT_EQ(regb.field->As<float>(), 0);
            EXPECT_EQ(rega.field->GetType(), typeid(int));
            EXPECT_EQ(regb.field->GetType(), typeid(float));
        }

        void TEST_METHOD_GENERAL()
        {

            Yolk::VM::OVO ovo;
            ovo.InstructionSet.push_back(Instruction{Instruction::INSTRUCTION::MOV, Arg{ Arg::MODE::REG, 0x0}, Arg { Arg::MODE::DATA, 0x0}}); // MOV REGA, "a"
            ovo.InstructionSet.push_back(Instruction{Instruction::INSTRUCTION::NEW, Arg{ Arg::MODE::REG, 0x1}, Arg { Arg::MODE::SYMBOL, 0x1}}); // NEW REGB, INT
            ovo.InstructionSet.push_back(Instruction{Instruction::INSTRUCTION::ADD, Arg{ Arg::MODE::REG, 0x1}, Arg { Arg::MODE::REG, 0x0}}); // ADD REGB, REGA
            ovo.InstructionSet.push_back(Instruction{Instruction::INSTRUCTION::ADD, Arg{ Arg::MODE::REG, 0x1}, Arg { Arg::MODE::REG, 0x1}}); // ADD REGB, REGB
            ovo.InstructionSet.push_back(Instruction{Instruction::INSTRUCTION::PUSHAR, Arg{ Arg::MODE::REG, 0x0}, Arg { Arg::MODE::NONE, 0x0}}); // PUSHAR REGA
            ovo.InstructionSet.push_back(Instruction{Instruction::INSTRUCTION::PUSHAR, Arg{ Arg::MODE::REG, 0x1}, Arg { Arg::MODE::NONE, 0x0}}); // PUSHAR REGB
            ovo.InstructionSet.push_back(Instruction{Instruction::INSTRUCTION::MOVM, Arg{ Arg::MODE::DATA, 0x1}, Arg { Arg::MODE::NONE, 0x0}}); // MOVM "VMFuncA"
            ovo.InstructionSet.push_back(Instruction{Instruction::INSTRUCTION::CALLM, Arg{ Arg::MODE::NONE, 0x0}, Arg { Arg::MODE::NONE, 0x0}}); // MOVM "VMFuncA"
            ovo.InstructionSet.push_back(Instruction{Instruction::INSTRUCTION::MOV, Arg{ Arg::MODE::REG, 0x2}, Arg { Arg::MODE::REG, 0x4}}); // MOV REGA, REGOUT


            ovo.DataSet.push_back(Data::GenerateData(std::string("a")));
            ovo.DataSet.push_back(Data::GenerateData(std::string("VMfuncA")));

            Run(ovo, memoryBlock.GetSymbolTable());

            std::cout << GetMessage() << std::endl;
            Debug();
            EXPECT_EQ(GetStatus(), Status::HALTED);
            EXPECT_EQ(rega.field->As<int>(), 5);
            EXPECT_EQ(regb.field->As<int>(), 10);
            EXPECT_EQ(regc.field->As<int>(), 15);

        }

        void TEST_PUSH_POP()
        {
            Yolk::VM::OVO ovo;
            ovo.InstructionSet.push_back(Instruction{Instruction::INSTRUCTION::CLONE, Arg{ Arg::MODE::REG, 0x0}, Arg { Arg::MODE::DATA, 0x0}}); // CLONE REGA, 3.21
            ovo.InstructionSet.push_back(Instruction{Instruction::INSTRUCTION::CLONE, Arg{ Arg::MODE::REG, 0x1}, Arg { Arg::MODE::DATA, 0x1}}); // CLONE REGB, 5.1
            ovo.InstructionSet.push_back(Instruction{Instruction::INSTRUCTION::CLONE, Arg{ Arg::MODE::REG, 0x2}, Arg { Arg::MODE::DATA, 0x2}}); // CLONE REGC, -2.1
            
            ovo.InstructionSet.push_back(Instruction{Instruction::INSTRUCTION::PUSH, Arg{ Arg::MODE::REG, 0x0}, Arg { Arg::MODE::NONE, 0x0}}); // PUSH REGA
            ovo.InstructionSet.push_back(Instruction{Instruction::INSTRUCTION::PUSH, Arg{ Arg::MODE::REG, 0x2}, Arg { Arg::MODE::NONE, 0x0}}); // PUSH REGC
            
            ovo.InstructionSet.push_back(Instruction{Instruction::INSTRUCTION::PUSHAR, Arg{ Arg::MODE::REG, 0x1}, Arg { Arg::MODE::NONE, 0x0}}); // PUSHAR REGB
            
            ovo.InstructionSet.push_back(Instruction{Instruction::INSTRUCTION::POP, Arg{ Arg::MODE::REG, 0x1}, Arg { Arg::MODE::NONE, 0x0}}); // POP REGB
            ovo.InstructionSet.push_back(Instruction{Instruction::INSTRUCTION::POP, Arg{ Arg::MODE::NONE, 0x0}, Arg { Arg::MODE::NONE, 0x0}}); // POP REGA
            ovo.InstructionSet.push_back(Instruction{Instruction::INSTRUCTION::POPAR, Arg{ Arg::MODE::REG, 0x2}, Arg { Arg::MODE::NONE, 0x0}}); // POPAR REGC
            
            ovo.InstructionSet.push_back(Instruction{Instruction::INSTRUCTION::ADD, Arg{ Arg::MODE::REG, 0x0}, Arg { Arg::MODE::REG, 0x1}}); // ADD REGA, REGB
            
            ovo.DataSet.push_back(Data::GenerateData(3.21f));
            ovo.DataSet.push_back(Data::GenerateData(5.1f));
            ovo.DataSet.push_back(Data::GenerateData(-2.1f));

            Run(ovo, memoryBlock.GetSymbolTable());

            std::cout << GetMessage() << std::endl;
            Debug();
            EXPECT_EQ(GetStatus(), Status::HALTED);
            EXPECT_FLOAT_EQ(rega.field->As<float>(), 1.11);
            EXPECT_FLOAT_EQ(regb.field->As<float>(), -2.1);
            EXPECT_FLOAT_EQ(regc.field->As<float>(), 5.1);
        }

        void TEST_COMPARE_EQ()
        {
            Yolk::VM::OVO ovo;
            ovo.InstructionSet.push_back(Instruction{Instruction::INSTRUCTION::MOV, Arg{ Arg::MODE::REG, 0x0}, Arg { Arg::MODE::DATA, 0x0}}); // 0. MOV REGA, "a"
            ovo.InstructionSet.push_back(Instruction{Instruction::INSTRUCTION::CMPEQ, Arg{ Arg::MODE::REG, 0x0}, Arg { Arg::MODE::DATA, 0x1}}); // 1. CMP REGA. 5.0f
            ovo.InstructionSet.push_back(Instruction{Instruction::INSTRUCTION::JNTRUE, Arg{ Arg::MODE::SYMBOL, 4}, Arg { Arg::MODE::NONE, 0x0}}); // 2. JNTRUE 4
            ovo.InstructionSet.push_back(Instruction{Instruction::INSTRUCTION::HALT, Arg{ Arg::MODE::NONE, 0x0}, Arg { Arg::MODE::NONE, 0x0}}); // 3. HALT
            ovo.InstructionSet.push_back(Instruction{Instruction::INSTRUCTION::NEW, Arg{ Arg::MODE::REG, 0x1}, Arg { Arg::MODE::SYMBOL, 0x1}}); // 4. NEW REGB, INT
            ovo.DataSet.push_back(Data::GenerateData(std::string("a")));
            ovo.DataSet.push_back(Data::GenerateData(5.0f));

            Run(ovo, memoryBlock.GetSymbolTable());
            Debug();
            EXPECT_EQ(regb.field->As<int>(), 0);
        }
        void TEST_COMPARE_NEQ()
        {
            Yolk::VM::OVO ovo;
            ovo.InstructionSet.push_back(Instruction{Instruction::INSTRUCTION::MOV, Arg{ Arg::MODE::REG, 0x0}, Arg { Arg::MODE::DATA, 0x0}}); // 0. MOV REGA, "a"
            ovo.InstructionSet.push_back(Instruction{Instruction::INSTRUCTION::CMPNEQ, Arg{ Arg::MODE::REG, 0x0}, Arg { Arg::MODE::DATA, 0x1}}); // 1. CMP REGA. 5.0f
            ovo.InstructionSet.push_back(Instruction{Instruction::INSTRUCTION::JNFALSE, Arg{ Arg::MODE::SYMBOL, 4}, Arg { Arg::MODE::NONE, 0x0}}); // 2. JNTRUE 4
            ovo.InstructionSet.push_back(Instruction{Instruction::INSTRUCTION::HALT, Arg{ Arg::MODE::NONE, 0x0}, Arg { Arg::MODE::NONE, 0x0}}); // 3. HALT
            ovo.InstructionSet.push_back(Instruction{Instruction::INSTRUCTION::NEW, Arg{ Arg::MODE::REG, 0x1}, Arg { Arg::MODE::SYMBOL, 0x1}}); // 4. NEW REGB, INT
            ovo.DataSet.push_back(Data::GenerateData(std::string("a")));
            ovo.DataSet.push_back(Data::GenerateData(5.0f));

            Run(ovo, memoryBlock.GetSymbolTable());
            Debug();
            EXPECT_EQ(regb.field->As<int>(), 0);
        }
        void TEST_COMPARE()
        {
            Yolk::VM::OVO ovo;
            ovo.InstructionSet.push_back(Instruction{Instruction::INSTRUCTION::CLONE, Arg{ Arg::MODE::REG, 0x0}, Arg { Arg::MODE::DATA, 0x0}}); // 0. MOV REGA, 1
            ovo.InstructionSet.push_back(Instruction{Instruction::INSTRUCTION::PUSHAR, Arg{ Arg::MODE::REG, 0x0}, Arg { Arg::MODE::NONE, 0x0}}); // 1. PUSHAR REGA
            ovo.InstructionSet.push_back(Instruction{Instruction::INSTRUCTION::MOVM, Arg{ Arg::MODE::DATA, 0x1}, Arg { Arg::MODE::NONE, 0x0}}); // 1. MOVM GreaterThanZero
            ovo.InstructionSet.push_back(Instruction{Instruction::INSTRUCTION::CALLM, Arg{ Arg::MODE::NONE, 0x0}, Arg { Arg::MODE::NONE, 0x0}}); // 1. MOVM GreaterThanZero
            ovo.InstructionSet.push_back(Instruction{Instruction::INSTRUCTION::MOV, Arg{ Arg::MODE::REG, 0x0}, Arg { Arg::MODE::REG, 0x4}}); // 1. MOV REGA, REGOUT
            ovo.InstructionSet.push_back(Instruction{Instruction::INSTRUCTION::CMP, Arg{ Arg::MODE::REG, 0x0}, Arg { Arg::MODE::NONE, 0x0}}); // 1. CMP
            ovo.DataSet.push_back(Data::GenerateData(1));
            ovo.DataSet.push_back(Data::GenerateData(std::string("GreaterThanZero")));

            Run(ovo, memoryBlock.GetSymbolTable());
            Debug();
            EXPECT_TRUE(cmpreg);
        }
        void TEST_CALL()
        {
            ovo.InstructionSet.push_back(Instruction{Instruction::INSTRUCTION::CALL, Arg{ Arg::MODE::SYMBOL, 0x2}, Arg { Arg::MODE::NONE, 0x0}}); // 0. CLONE REGA, INT
            ovo.InstructionSet.push_back(Instruction{Instruction::INSTRUCTION::HALT, Arg{ Arg::MODE::NONE, 0x0}, Arg { Arg::MODE::NONE, 0x0}}); // 1. CLONE REGA, INT
            ovo.InstructionSet.push_back(Instruction{Instruction::INSTRUCTION::NEW, Arg{ Arg::MODE::REG, 0x0}, Arg { Arg::MODE::SYMBOL, 0x1}}); // 2. CLONE REGA, INT
            ovo.InstructionSet.push_back(Instruction{Instruction::INSTRUCTION::RET, Arg{ Arg::MODE::NONE, 0x0}, Arg { Arg::MODE::NONE, 0x0}}); // 3. CLONE REGA, INT
            ovo.InstructionSet.push_back(Instruction{Instruction::INSTRUCTION::NEW, Arg{ Arg::MODE::REG, 0x1}, Arg { Arg::MODE::SYMBOL, 0x5}}); // 4. CLONE REGA, INT
            
            Run(ovo, memoryBlock.GetSymbolTable());
            EXPECT_EQ(GetStatus(), Status::HALTED);
            EXPECT_EQ(rega.field->GetType(), typeid(int));
            EXPECT_NE(regb.field->GetType(), typeid(float));
            EXPECT_EQ(GetClock(), 4); // 0->2->3->1
        }
        void TEST_NAME()
        {
            ovo.InstructionSet.push_back(Instruction{Instruction::INSTRUCTION::NEW, Arg{ Arg::MODE::REG, 0x0}, Arg { Arg::MODE::SYMBOL, 0x1}}); // 0. NEW REGA, INT
            ovo.InstructionSet.push_back(Instruction{Instruction::INSTRUCTION::NAMEL, Arg{ Arg::MODE::REG, 0x0}, Arg { Arg::MODE::DATA, 0x0}}); // 0. NEW REGA, INT
            ovo.InstructionSet.push_back(Instruction{Instruction::INSTRUCTION::MOV, Arg{ Arg::MODE::REG, 0x1}, Arg { Arg::MODE::DATA, 0x0}}); // MOV REGA, "a"
            ovo.DataSet.push_back(Data::GenerateData(std::string("mynewVariable")));


            Run(ovo, memoryBlock.GetSymbolTable());
            std::cout << GetMessage() << std::endl;
            std::cout << GetClock() << std::endl;
            Debug();
            EXPECT_STREQ(regb.field->GetType().name(), "i");

        }
        void TEST_CAST()
        {
            
            Yolk::VM::OVO ovo;
            ovo.InstructionSet.push_back(Instruction{Instruction::INSTRUCTION::MOV, Arg{ Arg::MODE::REG, 0x0}, Arg { Arg::MODE::DATA, 0x0}}); // MOV REGA, a
            ovo.InstructionSet.push_back(Instruction{Instruction::INSTRUCTION::NEW, Arg{ Arg::MODE::REG, 0x1}, Arg { Arg::MODE::SYMBOL, 0x5}}); // MOV REGA, a
            ovo.InstructionSet.push_back(Instruction{Instruction::INSTRUCTION::CAST, Arg{ Arg::MODE::REG, 0x0}, Arg { Arg::MODE::REG, 0x1}}); // MOV REGA, a
            ovo.DataSet.push_back(Data::GenerateData(std::string("a")));

            Run(ovo, memoryBlock.GetSymbolTable());

            EXPECT_EQ(GetStatus(), Status::HALTED);
            EXPECT_EQ(rega.field->GetType(), typeid(float));
            EXPECT_FLOAT_EQ(rega.field->As<float>(), 5.0f);
        }

        int a = 5;
        int b = 12;
        int VMFuncA(int x, int y)
        {
            return x + y;
        }
        bool GreaterThanZero(int x)
        {
            return (x > 0);   
        }
    };



TEST(Yolk_YVM, YVM_MOV)
{
    YVM_Tester yvmtester;
    yvmtester.TEST_MOV();
}
TEST(Yolk_YVM, YVM_COPY)
{
    YVM_Tester yvmtester;
    yvmtester.TEST_COPY();
}
TEST(Yolk_YVM, YVM_CLONE)
{
    YVM_Tester yvmtester;
    yvmtester.TEST_CLONE();
}
TEST(Yolk_YVM, YVM_NEW)
{
    YVM_Tester yvmtester;
    yvmtester.TEST_NEW();
}
TEST(Yolk_YVM, YVM_METHOD)
{
    YVM_Tester yvmtester;
    yvmtester.TEST_METHOD_GENERAL();
}
TEST(Yolk_YVM, YVM_PUSHPOP)
{
    YVM_Tester yvmtester;
    yvmtester.TEST_PUSH_POP();
}
TEST(Yolk_YVM, YVM_CMPEQ)
{
    YVM_Tester yvmtester;
    yvmtester.TEST_COMPARE_EQ();
}
TEST(Yolk_YVM, YVM_CMPNEQ)
{
    YVM_Tester yvmtester;
    yvmtester.TEST_COMPARE_NEQ();
}
TEST(Yolk_YVM, YVM_CMP)
{
    YVM_Tester yvmtester;
    yvmtester.TEST_COMPARE();
}
TEST(Yolk_YVM, YVM_CALL)
{
    YVM_Tester yvmtester;
    yvmtester.TEST_CALL();
}
TEST(Yolk_YVM, YVM_CAST)
{
    YVM_Tester yvmtester;
    yvmtester.TEST_CAST();
}
TEST(Yolk_YVM, YVM_NAME)
{
    YVM_Tester yvmtester;
    yvmtester.TEST_NAME();
}
