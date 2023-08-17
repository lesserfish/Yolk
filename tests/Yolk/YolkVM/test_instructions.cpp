#include <gtest/gtest.h>
#include "../../../src/Yolk/YolkVM/VM.h"

class InstructionTest : public Yolk::VM::VirtualMachine
{
    public:
        InstructionTest(Yolk::Memory::MemoryAllocator& memory, Yolk::Memory::MemoryInterface& interface) : 
            Yolk::VM::VirtualMachine(memory, &interface) 
		{
            auto aw = Yolk::WrapperGenerator<int>::GenerateStaticWrapper(memory, a);
            interface.Register(aw, "a");
            auto bw = Yolk::WrapperGenerator<int>::GenerateStaticWrapper(memory, b);
            interface.Register(bw, "b");
            auto cw = Yolk::WrapperGenerator<double>::GenerateStaticWrapper(memory, c);
            interface.Register(cw, "c");
            std::function<int(int)> func = [this](int input) {
                return this->Add(input);
            };
            auto funcw = Yolk::WrapperGenerator<int, int>::GenerateMethodWrapper(memory, func);
            interface.Register(funcw, "Add");
        }
        std::string SelectText(uint64_t input)
        {
            switch(input)
            {
                case 0: return "a";
                case 1: return "b";
                case 2: return "c";
                case 3: return "Add";
                case 4: return "Variable";
                default: return "";
            };
        }
		void MOV(){
			// Usage:         REGX, REGY  |   REGX, NAME
            // If Arg2 is a register, copies REGY onto REGX by reference. 
            // If Arg2 is a Name, searches in memory for a wrapper with that name and then copy it onto REGX by reference. 
            auto instruction = Yolk::VM::Instruction::Select(Yolk::VM::OPCode::MOV);
            auto arg1 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::REGISTER,
                                                static_cast<uint64_t>(Yolk::VM::RegisterType::REGA));
            auto arg2 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::NAME,
                                                0);
            Yolk::VM::VirtualMachine* machine = (static_cast<Yolk::VM::VirtualMachine *>(this));
            instruction->Execute(*machine, arg1, arg2);

            EXPECT_EQ(rega.field->As<int>(), a);
            
            arg1 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::REGISTER,
                                                static_cast<uint64_t>(Yolk::VM::RegisterType::REGB));
            arg2 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::REGISTER,
                                                static_cast<uint64_t>(Yolk::VM::RegisterType::REGA));

            instruction->Execute(*machine, arg1, arg2);

            EXPECT_EQ(regb.field->As<int>(), a);

		}
		void COPY(){
            // Usage:        REGX, REGY  |   REGX, ELEMENTARY  |   REGX, NAME
            // Copies the value of a wrapper onto the other. This throws an exception if the two wrappers have different types. 
            // If Arg2 is a register, copies the value of REGY to the value of REGX.
            // If Arg2 is an Elementary type, copies the value of Arg2 to the value of REGX.
            // If Arg2 is a Name, searches in memory for a wrapper with that name and then copy its value to the value of REGX. 
            
            Yolk::VM::VirtualMachine* machine = (static_cast<Yolk::VM::VirtualMachine *>(this));
            auto instruction = Yolk::VM::Instruction::Select(Yolk::VM::OPCode::MOV);
            
            // REGA = a (=3)
            auto arg1 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::REGISTER,
                                                static_cast<uint64_t>(Yolk::VM::RegisterType::REGA));
            auto arg2 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::NAME,
                                                0);
            instruction->Execute(*machine, arg1, arg2);

            // REGB = b (=5)
            arg1 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::REGISTER,
                                                static_cast<uint64_t>(Yolk::VM::RegisterType::REGB));
            arg2 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::NAME,
                                                1);
            instruction->Execute(*machine, arg1, arg2);


            // REGA <- REGB
            instruction = Yolk::VM::Instruction::Select(Yolk::VM::OPCode::COPY);
            
            arg1 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::REGISTER,
                                                static_cast<uint64_t>(Yolk::VM::RegisterType::REGA));
            arg2 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::REGISTER,
                                                static_cast<uint64_t>(Yolk::VM::RegisterType::REGB));

            instruction->Execute(*machine, arg1, arg2);
            
            EXPECT_EQ(a, 5);
            EXPECT_EQ(b, 5);

            // REGA <- 12
            int32_t val = 12;
            int64_t conv = (int64_t) val;
            uint64_t asuint = Yolk::VM::Bitcast<uint64_t>(conv);

            arg2 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::INT32,
                                                asuint);

            instruction->Execute(*machine, arg1, arg2);

            EXPECT_EQ(a, 12);
            
            // REGA <- 'B'
            arg2 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::NAME,
                                                1);

            instruction->Execute(*machine, arg1, arg2);

            EXPECT_EQ(a, b);

		}
		void CLONE(){
            // Usage:       REGX, REGY  |   REGX, NAME
            // If Arg2 is a register, clones REGY onto REGX.
            // If Arg2 is a Name, searches in memory for a wrapper with that name and then clones it onto REGX by value. 
            
            Yolk::VM::VirtualMachine* machine = (static_cast<Yolk::VM::VirtualMachine *>(this));
            auto instruction = Yolk::VM::Instruction::Select(Yolk::VM::OPCode::MOV);
            
            // REGA = a (=3)
            auto arg1 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::REGISTER,
                                                static_cast<uint64_t>(Yolk::VM::RegisterType::REGA));
            auto arg2 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::NAME,
                                                0);
            instruction->Execute(*machine, arg1, arg2);

            // REGB = b (=5)
            arg1 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::REGISTER,
                                                static_cast<uint64_t>(Yolk::VM::RegisterType::REGB));
            arg2 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::NAME,
                                                1);
            instruction->Execute(*machine, arg1, arg2);


            // REGC <- REGB Clone
            instruction = Yolk::VM::Instruction::Select(Yolk::VM::OPCode::CLONE);
            
            arg1 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::REGISTER,
                                                static_cast<uint64_t>(Yolk::VM::RegisterType::REGC));
            arg2 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::REGISTER,
                                                static_cast<uint64_t>(Yolk::VM::RegisterType::REGB));

            instruction->Execute(*machine, arg1, arg2);

            EXPECT_EQ(regc.field->As<int>(), b);

            b = 123;
            
            EXPECT_NE(regc.field->As<int>(), b);
            // REGD <- Clone 'a'

            arg1 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::REGISTER,
                                                static_cast<uint64_t>(Yolk::VM::RegisterType::REGD));
            arg2 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::NAME,
                                                0);

            instruction->Execute(*machine, arg1, arg2);

            EXPECT_EQ(regd.field->As<int>(), a);

		}
		void NEW(){
            // Usage:         REGX, ELEMENTARY
            // Allocates the elementary type onto memory and copies the wrapper to REGX.
            
            Yolk::VM::VirtualMachine* machine = (static_cast<Yolk::VM::VirtualMachine *>(this));
            auto instruction = Yolk::VM::Instruction::Select(Yolk::VM::OPCode::NEW);
            
            auto arg1 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::REGISTER,
                                                static_cast<uint64_t>(Yolk::VM::RegisterType::REGA));
            auto arg2 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::ELEMENTARY,
                                                static_cast<uint64_t>(Yolk::VM::EType::DOUBLE));
            instruction->Execute(*machine, arg1, arg2);

            EXPECT_EQ(rega.field->Type(), typeid(double));

		}
		void MOVM(){
            // Usage:        NAME
            // Searches in memory for a method wrapper with that name and then copy it onto the method register.
            Yolk::VM::VirtualMachine* machine = (static_cast<Yolk::VM::VirtualMachine *>(this));
            auto instruction = Yolk::VM::Instruction::Select(Yolk::VM::OPCode::MOVM);
            
            auto arg1 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::NAME,
                                                3);
            auto arg2 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::NONE, 0);
            instruction->Execute(*machine, arg1, arg2);
            EXPECT_TRUE(regm.IsValid());

		}
		void CALLM(){
            // Usage:  
            // Invokes the method wrapper in REGM
            Yolk::VM::VirtualMachine* machine = (static_cast<Yolk::VM::VirtualMachine *>(this));
            
            // REGC = INT
            auto instruction = Yolk::VM::Instruction::Select(Yolk::VM::OPCode::NEW);
            
            auto arg1 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::REGISTER,
                                                static_cast<uint64_t>(Yolk::VM::RegisterType::REGA));
            auto arg2 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::ELEMENTARY,
                                                static_cast<uint64_t>(Yolk::VM::EType::INT32));
            instruction->Execute(*machine, arg1, arg2);
            // REGC <- 122 
            int32_t value = 122;
            int64_t conv = value;
            uint64_t asuint = Yolk::VM::Bitcast<uint64_t>(conv);
            instruction = Yolk::VM::Instruction::Select(Yolk::VM::OPCode::COPY);

            arg2 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::INT32,
                                                asuint);

            instruction->Execute(*machine, arg1, arg2);
            
            //MOVM <- 'Add'

            instruction = Yolk::VM::Instruction::Select(Yolk::VM::OPCode::MOVM);
            
            arg1 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::NAME,
                                                3);
            arg2 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::NONE, 0);
            instruction->Execute(*machine, arg1, arg2);
            
            // PUSHAR

            instruction = Yolk::VM::Instruction::Select(Yolk::VM::OPCode::PUSHAR);
            arg1 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::REGISTER,
                                                static_cast<uint64_t>(Yolk::VM::RegisterType::REGA));
            arg2 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::NONE, 0);
            instruction->Execute(*machine, arg1, arg2);
            
            // CALLM

            arg1 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::NONE, 0);
            instruction = Yolk::VM::Instruction::Select(Yolk::VM::OPCode::CALLM);
            instruction->Execute(*machine, arg1, arg2);

            EXPECT_EQ(regout.field->As<int>(), a + b + value);


		}
		void PUSHAR(){
            // Already testes in CALLM

		}
		void POPAR(){
            //
		}
		void CLRAR(){
            // 
		}
		void PUSH(){
            //
		}
		void POP(){
            //
		}
		void CLEAR(){
            //
		}
		void CMP(){
            // Usage:         REGX
            // Casts REGX to bool and check if it's valid. 
            //
            a = 1;
            
            Yolk::VM::VirtualMachine* machine = (static_cast<Yolk::VM::VirtualMachine *>(this));
            auto instruction = Yolk::VM::Instruction::Select(Yolk::VM::OPCode::MOV);
            
            // REGA = a (=3)
            auto arg1 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::REGISTER,
                                                static_cast<uint64_t>(Yolk::VM::RegisterType::REGA));
            auto arg2 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::NAME,
                                                0);
            instruction->Execute(*machine, arg1, arg2);

            instruction = Yolk::VM::Instruction::Select(Yolk::VM::OPCode::CMP);

            instruction->Execute(*machine, arg1, arg2);

            EXPECT_TRUE(regcmp);

            a = 0;

            instruction->Execute(*machine, arg1, arg2);
            
            EXPECT_FALSE(regcmp);

		}
		void CMPEQ(){
            // Usage:       REGX, REGY  |   REGX, ELEMENTARY    |   REGX, NAME   
            // if Arg2 is a register, compares REGX == REGY and set it's truth-value onto regcmp.
            // If Arg2 is an elementary value, compares RegX == value and set it's truth-value onto regcmp.
            Yolk::VM::VirtualMachine* machine = (static_cast<Yolk::VM::VirtualMachine *>(this));
            auto instruction = Yolk::VM::Instruction::Select(Yolk::VM::OPCode::MOV);
            
            // REGA = a (=3)
            auto arg1 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::REGISTER,
                                                static_cast<uint64_t>(Yolk::VM::RegisterType::REGA));
            auto arg2 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::NAME,
                                                0);
            instruction->Execute(*machine, arg1, arg2);

            // REGB = b (=5)
            arg1 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::REGISTER,
                                                static_cast<uint64_t>(Yolk::VM::RegisterType::REGB));
            arg2 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::NAME,
                                                1);
            instruction->Execute(*machine, arg1, arg2);


            // REGA <- REGB
            instruction = Yolk::VM::Instruction::Select(Yolk::VM::OPCode::CMPEQ);
            
            arg1 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::REGISTER,
                                                static_cast<uint64_t>(Yolk::VM::RegisterType::REGA));
            arg2 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::REGISTER,
                                                static_cast<uint64_t>(Yolk::VM::RegisterType::REGB));
            a = 1;
            b = 1;
            regcmp = false;
            instruction->Execute(*machine, arg1, arg2);
            
            EXPECT_TRUE(regcmp);
            
            // REGA <- 12
            int32_t val = 12;
            int64_t conv = (int64_t) val;
            uint64_t asuint = Yolk::VM::Bitcast<uint64_t>(conv);

            arg2 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::INT32,
                                                asuint);

            instruction->Execute(*machine, arg1, arg2);

            EXPECT_FALSE(regcmp);
            
            // REGA <- 'B'
            arg2 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::NAME,
                                                1);

            instruction->Execute(*machine, arg1, arg2);

            EXPECT_TRUE(regcmp);
            
		}
		void CMPNEQ(){
            
            // Usage:       REGX, REGY  |   REGX, ELEMENTARY    |   REGX, NAME   
            // if Arg2 is a register, compares REGX != REGY and set it's truth-value onto regcmp.
            // If Arg2 is an elementary value, compares RegX != value and set it's truth-value onto regcmp.
            // If Arg2 is a name, searches the memory for that wrapper, comapres RegX != Wrapper and set it's truth-value onto regcmp.
            
            Yolk::VM::VirtualMachine* machine = (static_cast<Yolk::VM::VirtualMachine *>(this));
            auto instruction = Yolk::VM::Instruction::Select(Yolk::VM::OPCode::MOV);
            
            // REGA = a (=3)
            auto arg1 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::REGISTER,
                                                static_cast<uint64_t>(Yolk::VM::RegisterType::REGA));
            auto arg2 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::NAME,
                                                0);
            instruction->Execute(*machine, arg1, arg2);

            // REGB = b (=5)
            arg1 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::REGISTER,
                                                static_cast<uint64_t>(Yolk::VM::RegisterType::REGB));
            arg2 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::NAME,
                                                1);
            instruction->Execute(*machine, arg1, arg2);


            // REGA <- REGB
            instruction = Yolk::VM::Instruction::Select(Yolk::VM::OPCode::CMPNEQ);
            
            arg1 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::REGISTER,
                                                static_cast<uint64_t>(Yolk::VM::RegisterType::REGA));
            arg2 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::REGISTER,
                                                static_cast<uint64_t>(Yolk::VM::RegisterType::REGB));
            a = 1;
            b = 1;
            regcmp = false;
            instruction->Execute(*machine, arg1, arg2);
            
            EXPECT_FALSE(regcmp);
            
            // REGA <- 12
            int32_t val = 12;
            int64_t conv = (int64_t) val;
            uint64_t asuint = Yolk::VM::Bitcast<uint64_t>(conv);

            arg2 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::INT32,
                                                asuint);

            instruction->Execute(*machine, arg1, arg2);

            EXPECT_TRUE(regcmp);
            
            // REGA <- 'B'
            arg2 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::NAME,
                                                1);

            instruction->Execute(*machine, arg1, arg2);

            EXPECT_FALSE(regcmp);
            
		}
		void CMPLS(){
            // Usage:       REGX, REGY  |   REGX, ELEMENTARY    |   REGX, NAME   
            // if Arg2 is a register, compares REGX < REGY and set it's truth-value onto regcmp.
            // If Arg2 is an elementary value, compares RegX < value and set it's truth-value onto regcmp.
            // If Arg2 is a name, searches the memory for that wrapper, comapres RegX < Wrapper and set it's truth-value onto regcmp.
            
            Yolk::VM::VirtualMachine* machine = (static_cast<Yolk::VM::VirtualMachine *>(this));
            auto instruction = Yolk::VM::Instruction::Select(Yolk::VM::OPCode::MOV);
            
            // REGA = a (=3)
            auto arg1 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::REGISTER,
                                                static_cast<uint64_t>(Yolk::VM::RegisterType::REGA));
            auto arg2 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::NAME,
                                                0);
            instruction->Execute(*machine, arg1, arg2);

            // REGB = b (=5)
            arg1 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::REGISTER,
                                                static_cast<uint64_t>(Yolk::VM::RegisterType::REGB));
            arg2 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::NAME,
                                                1);
            instruction->Execute(*machine, arg1, arg2);


            // REGA <- REGB
            instruction = Yolk::VM::Instruction::Select(Yolk::VM::OPCode::CMPLS);
            
            arg1 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::REGISTER,
                                                static_cast<uint64_t>(Yolk::VM::RegisterType::REGA));
            arg2 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::REGISTER,
                                                static_cast<uint64_t>(Yolk::VM::RegisterType::REGB));
            a = 1;
            b = 3;
            regcmp = false;
            instruction->Execute(*machine, arg1, arg2);
            
            EXPECT_TRUE(regcmp);
            
            // REGA <- 12
            int32_t val = -1;
            int64_t conv = (int64_t) val;
            uint64_t asuint = Yolk::VM::Bitcast<uint64_t>(conv);

            arg2 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::INT32,
                                                asuint);

            instruction->Execute(*machine, arg1, arg2);

            EXPECT_FALSE(regcmp);
            
            // REGA <- 'B'
            arg2 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::NAME,
                                                1);

            instruction->Execute(*machine, arg1, arg2);

            EXPECT_TRUE(regcmp);
            
		}
		void CMPGT(){
            Yolk::VM::VirtualMachine* machine = (static_cast<Yolk::VM::VirtualMachine *>(this));
            auto instruction = Yolk::VM::Instruction::Select(Yolk::VM::OPCode::MOV);
            
            // REGA = a (=3)
            auto arg1 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::REGISTER,
                                                static_cast<uint64_t>(Yolk::VM::RegisterType::REGA));
            auto arg2 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::NAME,
                                                0);
            instruction->Execute(*machine, arg1, arg2);

            // REGB = b (=5)
            arg1 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::REGISTER,
                                                static_cast<uint64_t>(Yolk::VM::RegisterType::REGB));
            arg2 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::NAME,
                                                1);
            instruction->Execute(*machine, arg1, arg2);


            // REGA <- REGB
            instruction = Yolk::VM::Instruction::Select(Yolk::VM::OPCode::CMPGT);
            
            arg1 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::REGISTER,
                                                static_cast<uint64_t>(Yolk::VM::RegisterType::REGA));
            arg2 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::REGISTER,
                                                static_cast<uint64_t>(Yolk::VM::RegisterType::REGB));
            a = 1;
            b = 3;
            regcmp = false;
            instruction->Execute(*machine, arg1, arg2);
            
            EXPECT_FALSE(regcmp);
            
            // REGA <- 12
            int32_t val = -1;
            int64_t conv = (int64_t) val;
            uint64_t asuint = Yolk::VM::Bitcast<uint64_t>(conv);

            arg2 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::INT32,
                                                asuint);

            instruction->Execute(*machine, arg1, arg2);

            EXPECT_TRUE(regcmp);
            
            // REGA <- 'B'
            arg2 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::NAME,
                                                1);

            instruction->Execute(*machine, arg1, arg2);

            EXPECT_FALSE(regcmp);
		}
		void CMPLSEQ(){
            Yolk::VM::VirtualMachine* machine = (static_cast<Yolk::VM::VirtualMachine *>(this));
            auto instruction = Yolk::VM::Instruction::Select(Yolk::VM::OPCode::MOV);
            
            // REGA = a (=3)
            auto arg1 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::REGISTER,
                                                static_cast<uint64_t>(Yolk::VM::RegisterType::REGA));
            auto arg2 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::NAME,
                                                0);
            instruction->Execute(*machine, arg1, arg2);

            // REGB = b (=5)
            arg1 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::REGISTER,
                                                static_cast<uint64_t>(Yolk::VM::RegisterType::REGB));
            arg2 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::NAME,
                                                1);
            instruction->Execute(*machine, arg1, arg2);


            // REGA <- REGB
            instruction = Yolk::VM::Instruction::Select(Yolk::VM::OPCode::CMPLSEQ);
            
            arg1 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::REGISTER,
                                                static_cast<uint64_t>(Yolk::VM::RegisterType::REGA));
            arg2 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::REGISTER,
                                                static_cast<uint64_t>(Yolk::VM::RegisterType::REGB));
            a = 1;
            b = 1;
            regcmp = false;
            instruction->Execute(*machine, arg1, arg2);
            
            EXPECT_TRUE(regcmp);
            
            // REGA <- 12
            int32_t val = -1;
            int64_t conv = (int64_t) val;
            uint64_t asuint = Yolk::VM::Bitcast<uint64_t>(conv);

            arg2 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::INT32,
                                                asuint);

            instruction->Execute(*machine, arg1, arg2);

            EXPECT_FALSE(regcmp);
            
            // REGA <- 'B'
            arg2 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::NAME,
                                                1);

            instruction->Execute(*machine, arg1, arg2);

            EXPECT_TRUE(regcmp);
		}
		void CMPGTEQ(){
            Yolk::VM::VirtualMachine* machine = (static_cast<Yolk::VM::VirtualMachine *>(this));
            auto instruction = Yolk::VM::Instruction::Select(Yolk::VM::OPCode::MOV);
            
            // REGA = a (=3)
            auto arg1 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::REGISTER,
                                                static_cast<uint64_t>(Yolk::VM::RegisterType::REGA));
            auto arg2 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::NAME,
                                                0);
            instruction->Execute(*machine, arg1, arg2);

            // REGB = b (=5)
            arg1 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::REGISTER,
                                                static_cast<uint64_t>(Yolk::VM::RegisterType::REGB));
            arg2 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::NAME,
                                                1);
            instruction->Execute(*machine, arg1, arg2);


            // REGA <- REGB
            instruction = Yolk::VM::Instruction::Select(Yolk::VM::OPCode::CMPGTEQ);
            
            arg1 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::REGISTER,
                                                static_cast<uint64_t>(Yolk::VM::RegisterType::REGA));
            arg2 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::REGISTER,
                                                static_cast<uint64_t>(Yolk::VM::RegisterType::REGB));
            a = 1;
            b = 1;
            regcmp = false;
            instruction->Execute(*machine, arg1, arg2);
            
            EXPECT_TRUE(regcmp);
            
            // REGA <- 12
            int32_t val = -1;
            int64_t conv = (int64_t) val;
            uint64_t asuint = Yolk::VM::Bitcast<uint64_t>(conv);

            arg2 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::INT32,
                                                asuint);

            instruction->Execute(*machine, arg1, arg2);

            EXPECT_TRUE(regcmp);
            
            // REGA <- 'B'
            arg2 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::NAME,
                                                1);

            instruction->Execute(*machine, arg1, arg2);

            EXPECT_TRUE(regcmp);
		}
		void JNTRUE(){
            // Usage:      REGX        |   UINT
            // If Arg1 is a register, cast it's value to uint and jumps to that position if regcmp is true
            // If Arg1 is an uint, jump to that value if regcmp is true
            
            regcmp = true;

            Yolk::VM::VirtualMachine* machine = (static_cast<Yolk::VM::VirtualMachine *>(this));
            auto instruction = Yolk::VM::Instruction::Select(Yolk::VM::OPCode::JNTRUE);
            
            uint64_t position = 123;
            // REGA = a (=3)
            auto arg1 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::UINT64,
                                                position);
            auto arg2 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::NONE, 0);

            instruction->Execute(*machine, arg1, arg2);

            EXPECT_EQ(ip, 123);

		}
		void JNFALSE(){
            
            regcmp = false;

            Yolk::VM::VirtualMachine* machine = (static_cast<Yolk::VM::VirtualMachine *>(this));
            auto instruction = Yolk::VM::Instruction::Select(Yolk::VM::OPCode::JNFALSE);
            
            uint64_t position = 123;
            // REGA = a (=3)
            auto arg1 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::UINT64,
                                                position);
            auto arg2 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::NONE, 0);

            instruction->Execute(*machine, arg1, arg2);

            EXPECT_EQ(ip, 123);
		}
		void JMP(){
            Yolk::VM::VirtualMachine* machine = (static_cast<Yolk::VM::VirtualMachine *>(this));
            auto instruction = Yolk::VM::Instruction::Select(Yolk::VM::OPCode::JMP);
            
            uint64_t position = 123;
            // REGA = a (=3)
            auto arg1 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::UINT64,
                                                position);
            auto arg2 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::NONE, 0);

            instruction->Execute(*machine, arg1, arg2);

            EXPECT_EQ(ip, 123);

		}
		void CALL(){
            
            // Usage:        REGX        |   UINT
            // Copies the position of ip onto the stack
            // If Arg1 is a register, cast it's value to uint and jumps to that position
            // If Arg1 is an uint, jump to that value
            Yolk::VM::VirtualMachine* machine = (static_cast<Yolk::VM::VirtualMachine *>(this));
            auto instruction = Yolk::VM::Instruction::Select(Yolk::VM::OPCode::CALL);
            
            ip = 12;
            uint64_t position = 123;
            // REGA = a (=3)
            auto arg1 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::UINT64,
                                                position);
            auto arg2 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::NONE, 0);

            instruction->Execute(*machine, arg1, arg2);

            EXPECT_EQ(ip, 123);
            
            instruction = Yolk::VM::Instruction::Select(Yolk::VM::OPCode::RET);
            arg1 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::NONE, 0);
            arg2 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::NONE, 0);

            instruction->Execute(*machine, arg1, arg2);
            EXPECT_EQ(ip, 12);

		}
		void RET(){
            // TESTED IN CALL
		}
		void ADD(){
            Yolk::VM::VirtualMachine* machine = (static_cast<Yolk::VM::VirtualMachine *>(this));
            auto instruction = Yolk::VM::Instruction::Select(Yolk::VM::OPCode::MOV);
            
            // REGA = a (=3)
            auto arg1 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::REGISTER,
                                                static_cast<uint64_t>(Yolk::VM::RegisterType::REGA));
            auto arg2 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::NAME,
                                                0);
            instruction->Execute(*machine, arg1, arg2);

            // REGB = b (=5)
            arg1 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::REGISTER,
                                                static_cast<uint64_t>(Yolk::VM::RegisterType::REGB));
            arg2 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::NAME,
                                                1);
            instruction->Execute(*machine, arg1, arg2);


            // REGA <- REGB
            instruction = Yolk::VM::Instruction::Select(Yolk::VM::OPCode::ADD);
            
            arg1 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::REGISTER,
                                                static_cast<uint64_t>(Yolk::VM::RegisterType::REGA));
            arg2 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::REGISTER,
                                                static_cast<uint64_t>(Yolk::VM::RegisterType::REGB));

            instruction->Execute(*machine, arg1, arg2);
            
            EXPECT_EQ(a, 3 + 5);

            // REGA <- 12
            int32_t val = 12;
            int64_t conv = (int64_t) val;
            uint64_t asuint = Yolk::VM::Bitcast<uint64_t>(conv);

            arg2 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::INT32,
                                                asuint);

            instruction->Execute(*machine, arg1, arg2);

            EXPECT_EQ(a, 3 + 5 + 12);
            
            // REGA <- 'B'
            arg2 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::NAME,
                                                1);

            instruction->Execute(*machine, arg1, arg2);

            EXPECT_EQ(a, 3 + 5 + 12 + 5);

		}
		void SUB(){
            Yolk::VM::VirtualMachine* machine = (static_cast<Yolk::VM::VirtualMachine *>(this));
            auto instruction = Yolk::VM::Instruction::Select(Yolk::VM::OPCode::MOV);
            
            // REGA = a (=3)
            auto arg1 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::REGISTER,
                                                static_cast<uint64_t>(Yolk::VM::RegisterType::REGA));
            auto arg2 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::NAME,
                                                0);
            instruction->Execute(*machine, arg1, arg2);

            // REGB = b (=5)
            arg1 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::REGISTER,
                                                static_cast<uint64_t>(Yolk::VM::RegisterType::REGB));
            arg2 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::NAME,
                                                1);
            instruction->Execute(*machine, arg1, arg2);


            // REGA <- REGB
            instruction = Yolk::VM::Instruction::Select(Yolk::VM::OPCode::SUB);
            
            arg1 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::REGISTER,
                                                static_cast<uint64_t>(Yolk::VM::RegisterType::REGA));
            arg2 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::REGISTER,
                                                static_cast<uint64_t>(Yolk::VM::RegisterType::REGB));

            instruction->Execute(*machine, arg1, arg2);
            
            EXPECT_EQ(a, 3 - 5);

            // REGA <- 12
            int32_t val = 12;
            int64_t conv = (int64_t) val;
            uint64_t asuint = Yolk::VM::Bitcast<uint64_t>(conv);

            arg2 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::INT32,
                                                asuint);

            instruction->Execute(*machine, arg1, arg2);

            EXPECT_EQ(a, 3 - 5 - 12);
            
            // REGA <- 'B'
            arg2 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::NAME,
                                                1);

            instruction->Execute(*machine, arg1, arg2);

            EXPECT_EQ(a, 3 - 5 - 12 - 5);
		}
		void MUL(){
            Yolk::VM::VirtualMachine* machine = (static_cast<Yolk::VM::VirtualMachine *>(this));
            auto instruction = Yolk::VM::Instruction::Select(Yolk::VM::OPCode::MOV);
            
            // REGA = a (=3)
            auto arg1 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::REGISTER,
                                                static_cast<uint64_t>(Yolk::VM::RegisterType::REGA));
            auto arg2 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::NAME,
                                                0);
            instruction->Execute(*machine, arg1, arg2);

            // REGB = b (=5)
            arg1 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::REGISTER,
                                                static_cast<uint64_t>(Yolk::VM::RegisterType::REGB));
            arg2 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::NAME,
                                                1);
            instruction->Execute(*machine, arg1, arg2);


            // REGA <- REGB
            instruction = Yolk::VM::Instruction::Select(Yolk::VM::OPCode::MUL);
            
            arg1 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::REGISTER,
                                                static_cast<uint64_t>(Yolk::VM::RegisterType::REGA));
            arg2 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::REGISTER,
                                                static_cast<uint64_t>(Yolk::VM::RegisterType::REGB));

            instruction->Execute(*machine, arg1, arg2);
            
            EXPECT_EQ(a, 3 * 5);

            // REGA <- 12
            int32_t val = 12;
            int64_t conv = (int64_t) val;
            uint64_t asuint = Yolk::VM::Bitcast<uint64_t>(conv);

            arg2 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::INT32,
                                                asuint);

            instruction->Execute(*machine, arg1, arg2);

            EXPECT_EQ(a, 3 * 5 * 12);
            
            // REGA <- 'B'
            arg2 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::NAME,
                                                1);

            instruction->Execute(*machine, arg1, arg2);

            EXPECT_EQ(a, 3 * 5 * 12 * 5);
		}
		void DIV(){
            a = 250;
            Yolk::VM::VirtualMachine* machine = (static_cast<Yolk::VM::VirtualMachine *>(this));
            auto instruction = Yolk::VM::Instruction::Select(Yolk::VM::OPCode::MOV);
            
            // REGA = a (=3)
            auto arg1 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::REGISTER,
                                                static_cast<uint64_t>(Yolk::VM::RegisterType::REGA));
            auto arg2 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::NAME,
                                                0);
            instruction->Execute(*machine, arg1, arg2);

            // REGB = b (=5)
            arg1 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::REGISTER,
                                                static_cast<uint64_t>(Yolk::VM::RegisterType::REGB));
            arg2 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::NAME,
                                                1);
            instruction->Execute(*machine, arg1, arg2);


            // REGA <- REGB
            instruction = Yolk::VM::Instruction::Select(Yolk::VM::OPCode::DIV);
            
            arg1 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::REGISTER,
                                                static_cast<uint64_t>(Yolk::VM::RegisterType::REGA));
            arg2 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::REGISTER,
                                                static_cast<uint64_t>(Yolk::VM::RegisterType::REGB));

            instruction->Execute(*machine, arg1, arg2);
            
            EXPECT_EQ(a, 250 / 5);

            // REGA <- 12
            int32_t val = 10;
            int64_t conv = (int64_t) val;
            uint64_t asuint = Yolk::VM::Bitcast<uint64_t>(conv);

            arg2 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::INT32,
                                                asuint);

            instruction->Execute(*machine, arg1, arg2);

            EXPECT_EQ(a, (250 / 5) / 10);
            
            // REGA <- 'B'
            arg2 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::NAME,
                                                1);

            instruction->Execute(*machine, arg1, arg2);

            EXPECT_EQ(a, ((250 / 5) / 10) / 5);
		}
		void MOD(){
            a = 250;
            Yolk::VM::VirtualMachine* machine = (static_cast<Yolk::VM::VirtualMachine *>(this));
            auto instruction = Yolk::VM::Instruction::Select(Yolk::VM::OPCode::MOV);
            
            // REGA = a (=3)
            auto arg1 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::REGISTER,
                                                static_cast<uint64_t>(Yolk::VM::RegisterType::REGA));
            auto arg2 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::NAME,
                                                0);
            instruction->Execute(*machine, arg1, arg2);

            // REGB = b (=5)
            arg1 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::REGISTER,
                                                static_cast<uint64_t>(Yolk::VM::RegisterType::REGB));
            arg2 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::NAME,
                                                1);
            instruction->Execute(*machine, arg1, arg2);


            // REGA <- REGB
            instruction = Yolk::VM::Instruction::Select(Yolk::VM::OPCode::MOD);
            
            arg1 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::REGISTER,
                                                static_cast<uint64_t>(Yolk::VM::RegisterType::REGA));
            arg2 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::REGISTER,
                                                static_cast<uint64_t>(Yolk::VM::RegisterType::REGB));

            instruction->Execute(*machine, arg1, arg2);
            
            EXPECT_EQ(a, 250 % 5);

            // REGA <- 12
            a = 250;
            int32_t val = 10;
            int64_t conv = (int64_t) val;
            uint64_t asuint = Yolk::VM::Bitcast<uint64_t>(conv);

            arg2 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::INT32,
                                                asuint);

            instruction->Execute(*machine, arg1, arg2);

            EXPECT_EQ(a, 250 % 10);
            
            // REGA <- 'B'
            a = 250;
            arg2 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::NAME,
                                                1);

            instruction->Execute(*machine, arg1, arg2);

            EXPECT_EQ(a, 250 % 5);
		}
		void AND(){
            a = 250;
            Yolk::VM::VirtualMachine* machine = (static_cast<Yolk::VM::VirtualMachine *>(this));
            auto instruction = Yolk::VM::Instruction::Select(Yolk::VM::OPCode::MOV);
            
            // REGA = a (=3)
            auto arg1 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::REGISTER,
                                                static_cast<uint64_t>(Yolk::VM::RegisterType::REGA));
            auto arg2 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::NAME,
                                                0);
            instruction->Execute(*machine, arg1, arg2);

            // REGB = b (=5)
            arg1 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::REGISTER,
                                                static_cast<uint64_t>(Yolk::VM::RegisterType::REGB));
            arg2 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::NAME,
                                                1);
            instruction->Execute(*machine, arg1, arg2);


            // REGA <- REGB
            instruction = Yolk::VM::Instruction::Select(Yolk::VM::OPCode::AND);
            
            arg1 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::REGISTER,
                                                static_cast<uint64_t>(Yolk::VM::RegisterType::REGA));
            arg2 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::REGISTER,
                                                static_cast<uint64_t>(Yolk::VM::RegisterType::REGB));

            instruction->Execute(*machine, arg1, arg2);
            
            EXPECT_EQ(a, 250 && 5);

            // REGA <- 12
            a = 250;
            int32_t val = 10;
            int64_t conv = (int64_t) val;
            uint64_t asuint = Yolk::VM::Bitcast<uint64_t>(conv);

            arg2 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::INT32,
                                                asuint);

            instruction->Execute(*machine, arg1, arg2);

            EXPECT_EQ(a, 250 && 10);
            
            // REGA <- 'B'
            a = 250;
            arg2 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::NAME,
                                                1);

            instruction->Execute(*machine, arg1, arg2);

            EXPECT_EQ(a, 250 && 5);
		}
		void OR(){
            a = 250;
            Yolk::VM::VirtualMachine* machine = (static_cast<Yolk::VM::VirtualMachine *>(this));
            auto instruction = Yolk::VM::Instruction::Select(Yolk::VM::OPCode::MOV);
            
            // REGA = a (=3)
            auto arg1 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::REGISTER,
                                                static_cast<uint64_t>(Yolk::VM::RegisterType::REGA));
            auto arg2 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::NAME,
                                                0);
            instruction->Execute(*machine, arg1, arg2);

            // REGB = b (=5)
            arg1 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::REGISTER,
                                                static_cast<uint64_t>(Yolk::VM::RegisterType::REGB));
            arg2 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::NAME,
                                                1);
            instruction->Execute(*machine, arg1, arg2);


            // REGA <- REGB
            instruction = Yolk::VM::Instruction::Select(Yolk::VM::OPCode::OR);
            
            arg1 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::REGISTER,
                                                static_cast<uint64_t>(Yolk::VM::RegisterType::REGA));
            arg2 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::REGISTER,
                                                static_cast<uint64_t>(Yolk::VM::RegisterType::REGB));

            instruction->Execute(*machine, arg1, arg2);
            
            EXPECT_EQ(a, 250 || 5);

            // REGA <- 12
            a = 250;
            int32_t val = 10;
            int64_t conv = (int64_t) val;
            uint64_t asuint = Yolk::VM::Bitcast<uint64_t>(conv);

            arg2 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::INT32,
                                                asuint);

            instruction->Execute(*machine, arg1, arg2);

            EXPECT_EQ(a, 250 || 10);
            
            // REGA <- 'B'
            a = 250;
            arg2 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::NAME,
                                                1);

            instruction->Execute(*machine, arg1, arg2);

            EXPECT_EQ(a, 250 || 5);
		}
		void CAST(){
            Yolk::VM::VirtualMachine* machine = (static_cast<Yolk::VM::VirtualMachine *>(this));
            auto instruction = Yolk::VM::Instruction::Select(Yolk::VM::OPCode::MOV);
            
            // REGA = a (=3)
            auto arg1 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::REGISTER,
                                                static_cast<uint64_t>(Yolk::VM::RegisterType::REGA));
            auto arg2 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::NAME,
                                                0);
            instruction->Execute(*machine, arg1, arg2);

            // REGB = c (= DOUBLE)
            arg1 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::REGISTER,
                                                static_cast<uint64_t>(Yolk::VM::RegisterType::REGB));
            arg2 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::NAME,
                                                2);
            instruction->Execute(*machine, arg1, arg2);


            // REGA <- REGB
            instruction = Yolk::VM::Instruction::Select(Yolk::VM::OPCode::CAST);
            
            arg1 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::REGISTER,
                                                static_cast<uint64_t>(Yolk::VM::RegisterType::REGA));
            arg2 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::REGISTER,
                                                static_cast<uint64_t>(Yolk::VM::RegisterType::REGB));

            instruction->Execute(*machine, arg1, arg2);
            
            EXPECT_EQ(rega.field->Type(), typeid(double));

            // REGA <- 12

            arg2 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::ELEMENTARY,
                                               static_cast<uint64_t>(Yolk::VM::EType::INT32));

            instruction->Execute(*machine, arg1, arg2);

            EXPECT_EQ(rega.field->Type(), typeid(int));
            EXPECT_EQ(rega.field->As<int>(), 3);
            
            // REGA <- 'B'
            a = 250;
            arg2 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::NAME,
                                                2);

            instruction->Execute(*machine, arg1, arg2);

            EXPECT_EQ(rega.field->Type(), typeid(double));
		}
		void NAME(){
            // Usage:        REGX, STRING 
            // Copies RegX to the memory under the name in Arg2
            
            Yolk::VM::VirtualMachine* machine = (static_cast<Yolk::VM::VirtualMachine *>(this));
            auto instruction = Yolk::VM::Instruction::Select(Yolk::VM::OPCode::NEW);
            
            auto arg1 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::REGISTER,
                                                static_cast<uint64_t>(Yolk::VM::RegisterType::REGA));
            auto arg2 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::ELEMENTARY,
                                                static_cast<uint64_t>(Yolk::VM::EType::DOUBLE));
            instruction->Execute(*machine, arg1, arg2);
            
            instruction = Yolk::VM::Instruction::Select(Yolk::VM::OPCode::NAME);
            arg2 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::NAME, 4);
            instruction->Execute(*machine, arg1, arg2);

            auto w = GetInterface()->GetWrapper("Variable").wrapper;
            EXPECT_EQ(w.field->Type(), typeid(double));

		}
		void NAMEG(){
            // TODO
		}
		void BRUP(){
            // Tested in BRDW
		}
		void BRDW(){
            Yolk::VM::VirtualMachine* machine = (static_cast<Yolk::VM::VirtualMachine *>(this));
            auto instruction = Yolk::VM::Instruction::Select(Yolk::VM::OPCode::BRDW);
            auto arg1 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::NONE, 0);
            auto arg2 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::NONE, 0);
            instruction->Execute(*machine, arg1, arg2);

            instruction = Yolk::VM::Instruction::Select(Yolk::VM::OPCode::NEW);
            
            arg1 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::REGISTER,
                                                static_cast<uint64_t>(Yolk::VM::RegisterType::REGA));
            arg2 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::ELEMENTARY,
                                                static_cast<uint64_t>(Yolk::VM::EType::DOUBLE));
            instruction->Execute(*machine, arg1, arg2);
            
            instruction = Yolk::VM::Instruction::Select(Yolk::VM::OPCode::NAME);
            arg2 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::NAME, 4);
            instruction->Execute(*machine, arg1, arg2);

            EXPECT_TRUE(GetInterface()->Exists("Variable"));
            
            instruction = Yolk::VM::Instruction::Select(Yolk::VM::OPCode::BRUP);
            arg1 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::NONE, 0);
            arg2 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::NONE, 0);
            instruction->Execute(*machine, arg1, arg2);

            EXPECT_FALSE(GetInterface()->Exists("Variable"));

		}
		void BRHZ(){
            // TODO
		}
		void RSBR(){
            // Trivial
		}
		void ZERO(){
            // Does Nothing
		}
		void HALT(){
            
            Yolk::VM::VirtualMachine* machine = (static_cast<Yolk::VM::VirtualMachine *>(this));
            auto instruction = Yolk::VM::Instruction::Select(Yolk::VM::OPCode::HALT);
            
            auto arg1 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::NONE, 0);
            auto arg2 = Yolk::VM::Ovo::Code::Arg(Yolk::VM::ArgType::NONE, 0);
            instruction->Execute(*machine, arg1, arg2);
            
            EXPECT_EQ(status, Yolk::VM::Status::HALTED);

        }
    private:
        int a = 3;
        int b = 5;
        double c = 3.14;
        int Add(int tmp = 0)
        {
            return a + b + tmp;
        }
};
TEST(Instruction, MOV)
{
	//TOADD:MOV
	Yolk::Memory::MemoryAllocator memory;
	Yolk::Memory::MemoryInterface interface(memory);
	InstructionTest itest(memory, interface);
	itest.MOV();
}
TEST(Instruction, COPY)
{
	//TOADD:COPY
	Yolk::Memory::MemoryAllocator memory;
	Yolk::Memory::MemoryInterface interface(memory);
	InstructionTest itest(memory, interface);
	itest.COPY();
}
TEST(Instruction, CLONE)
{
	//TOADD:CLONE
	Yolk::Memory::MemoryAllocator memory;
	Yolk::Memory::MemoryInterface interface(memory);
	InstructionTest itest(memory, interface);
	itest.CLONE();
}
TEST(Instruction, NEW)
{
	//TOADD:NEW
	Yolk::Memory::MemoryAllocator memory;
	Yolk::Memory::MemoryInterface interface(memory);
	InstructionTest itest(memory, interface);
	itest.NEW();
}
TEST(Instruction, MOVM)
{
	//TOADD:MOVM
	Yolk::Memory::MemoryAllocator memory;
	Yolk::Memory::MemoryInterface interface(memory);
	InstructionTest itest(memory, interface);
	itest.MOVM();
}
TEST(Instruction, CALLM)
{
	//TOADD:CALLM
	Yolk::Memory::MemoryAllocator memory;
	Yolk::Memory::MemoryInterface interface(memory);
	InstructionTest itest(memory, interface);
	itest.CALLM();
}
TEST(Instruction, PUSHAR)
{
	//TOADD:PUSHAR
	Yolk::Memory::MemoryAllocator memory;
	Yolk::Memory::MemoryInterface interface(memory);
	InstructionTest itest(memory, interface);
	itest.PUSHAR();
}
TEST(Instruction, POPAR)
{
	//TOADD:POPAR
	Yolk::Memory::MemoryAllocator memory;
	Yolk::Memory::MemoryInterface interface(memory);
	InstructionTest itest(memory, interface);
	itest.POPAR();
}
TEST(Instruction, CLRAR)
{
	//TOADD:CLRAR
	Yolk::Memory::MemoryAllocator memory;
	Yolk::Memory::MemoryInterface interface(memory);
	InstructionTest itest(memory, interface);
	itest.CLRAR();
}
TEST(Instruction, PUSH)
{
	//TOADD:PUSH
	Yolk::Memory::MemoryAllocator memory;
	Yolk::Memory::MemoryInterface interface(memory);
	InstructionTest itest(memory, interface);
	itest.PUSH();
}
TEST(Instruction, POP)
{
	//TOADD:POP
	Yolk::Memory::MemoryAllocator memory;
	Yolk::Memory::MemoryInterface interface(memory);
	InstructionTest itest(memory, interface);
	itest.POP();
}
TEST(Instruction, CLEAR)
{
	//TOADD:CLEAR
	Yolk::Memory::MemoryAllocator memory;
	Yolk::Memory::MemoryInterface interface(memory);
	InstructionTest itest(memory, interface);
	itest.CLEAR();
}
TEST(Instruction, CMP)
{
	//TOADD:CMP
	Yolk::Memory::MemoryAllocator memory;
	Yolk::Memory::MemoryInterface interface(memory);
	InstructionTest itest(memory, interface);
	itest.CMP();
}
TEST(Instruction, CMPEQ)
{
	//TOADD:CMPEQ
	Yolk::Memory::MemoryAllocator memory;
	Yolk::Memory::MemoryInterface interface(memory);
	InstructionTest itest(memory, interface);
	itest.CMPEQ();
}
TEST(Instruction, CMPNEQ)
{
	//TOADD:CMPNEQ
	Yolk::Memory::MemoryAllocator memory;
	Yolk::Memory::MemoryInterface interface(memory);
	InstructionTest itest(memory, interface);
	itest.CMPNEQ();
}
TEST(Instruction, CMPLS)
{
	//TOADD:CMPLS
	Yolk::Memory::MemoryAllocator memory;
	Yolk::Memory::MemoryInterface interface(memory);
	InstructionTest itest(memory, interface);
	itest.CMPLS();
}
TEST(Instruction, CMPGT)
{
	//TOADD:CMPGT
	Yolk::Memory::MemoryAllocator memory;
	Yolk::Memory::MemoryInterface interface(memory);
	InstructionTest itest(memory, interface);
	itest.CMPGT();
}
TEST(Instruction, CMPLSEQ)
{
	//TOADD:CMPLSEQ
	Yolk::Memory::MemoryAllocator memory;
	Yolk::Memory::MemoryInterface interface(memory);
	InstructionTest itest(memory, interface);
	itest.CMPLSEQ();
}
TEST(Instruction, CMPGTEQ)
{
	//TOADD:CMPGTEQ
	Yolk::Memory::MemoryAllocator memory;
	Yolk::Memory::MemoryInterface interface(memory);
	InstructionTest itest(memory, interface);
	itest.CMPGTEQ();
}
TEST(Instruction, JNTRUE)
{
	//TOADD:JNTRUE
	Yolk::Memory::MemoryAllocator memory;
	Yolk::Memory::MemoryInterface interface(memory);
	InstructionTest itest(memory, interface);
	itest.JNTRUE();
}
TEST(Instruction, JNFALSE)
{
	//TOADD:JNFALSE
	Yolk::Memory::MemoryAllocator memory;
	Yolk::Memory::MemoryInterface interface(memory);
	InstructionTest itest(memory, interface);
	itest.JNFALSE();
}
TEST(Instruction, JMP)
{
	//TOADD:JMP
	Yolk::Memory::MemoryAllocator memory;
	Yolk::Memory::MemoryInterface interface(memory);
	InstructionTest itest(memory, interface);
	itest.JMP();
}
TEST(Instruction, CALL)
{
	//TOADD:CALL
	Yolk::Memory::MemoryAllocator memory;
	Yolk::Memory::MemoryInterface interface(memory);
	InstructionTest itest(memory, interface);
	itest.CALL();
}
TEST(Instruction, RET)
{
	//TOADD:RET
	Yolk::Memory::MemoryAllocator memory;
	Yolk::Memory::MemoryInterface interface(memory);
	InstructionTest itest(memory, interface);
	itest.RET();
}
TEST(Instruction, ADD)
{
	//TOADD:ADD
	Yolk::Memory::MemoryAllocator memory;
	Yolk::Memory::MemoryInterface interface(memory);
	InstructionTest itest(memory, interface);
	itest.ADD();
}
TEST(Instruction, SUB)
{
	//TOADD:SUB
	Yolk::Memory::MemoryAllocator memory;
	Yolk::Memory::MemoryInterface interface(memory);
	InstructionTest itest(memory, interface);
	itest.SUB();
}
TEST(Instruction, MUL)
{
	//TOADD:MUL
	Yolk::Memory::MemoryAllocator memory;
	Yolk::Memory::MemoryInterface interface(memory);
	InstructionTest itest(memory, interface);
	itest.MUL();
}
TEST(Instruction, DIV)
{
	//TOADD:DIV
	Yolk::Memory::MemoryAllocator memory;
	Yolk::Memory::MemoryInterface interface(memory);
	InstructionTest itest(memory, interface);
	itest.DIV();
}
TEST(Instruction, MOD)
{
	//TOADD:MOD
	Yolk::Memory::MemoryAllocator memory;
	Yolk::Memory::MemoryInterface interface(memory);
	InstructionTest itest(memory, interface);
	itest.MOD();
}
TEST(Instruction, AND)
{
	//TOADD:AND
	Yolk::Memory::MemoryAllocator memory;
	Yolk::Memory::MemoryInterface interface(memory);
	InstructionTest itest(memory, interface);
	itest.AND();
}
TEST(Instruction, OR)
{
	//TOADD:OR
	Yolk::Memory::MemoryAllocator memory;
	Yolk::Memory::MemoryInterface interface(memory);
	InstructionTest itest(memory, interface);
	itest.OR();
}
TEST(Instruction, CAST)
{
	//TOADD:CAST
	Yolk::Memory::MemoryAllocator memory;
	Yolk::Memory::MemoryInterface interface(memory);
	InstructionTest itest(memory, interface);
	itest.CAST();
}
TEST(Instruction, NAME)
{
	//TOADD:NAME
	Yolk::Memory::MemoryAllocator memory;
	Yolk::Memory::MemoryInterface interface(memory);
	InstructionTest itest(memory, interface);
	itest.NAME();
}
TEST(Instruction, NAMEG)
{
	//TOADD:NAMEG
	Yolk::Memory::MemoryAllocator memory;
	Yolk::Memory::MemoryInterface interface(memory);
	InstructionTest itest(memory, interface);
	itest.NAMEG();
}
TEST(Instruction, BRUP)
{
	//TOADD:BRUP
	Yolk::Memory::MemoryAllocator memory;
	Yolk::Memory::MemoryInterface interface(memory);
	InstructionTest itest(memory, interface);
	itest.BRUP();
}
TEST(Instruction, BRDW)
{
	//TOADD:BRDW
	Yolk::Memory::MemoryAllocator memory;
	Yolk::Memory::MemoryInterface interface(memory);
	InstructionTest itest(memory, interface);
	itest.BRDW();
}
TEST(Instruction, BRHZ)
{
	//TOADD:BRHZ
	Yolk::Memory::MemoryAllocator memory;
	Yolk::Memory::MemoryInterface interface(memory);
	InstructionTest itest(memory, interface);
	itest.BRHZ();
}
TEST(Instruction, RSBR)
{
	//TOADD:RSBR
	Yolk::Memory::MemoryAllocator memory;
	Yolk::Memory::MemoryInterface interface(memory);
	InstructionTest itest(memory, interface);
	itest.RSBR();
}
TEST(Instruction, ZERO)
{
	//TOADD:ZERO
	Yolk::Memory::MemoryAllocator memory;
	Yolk::Memory::MemoryInterface interface(memory);
	InstructionTest itest(memory, interface);
	itest.ZERO();
}
TEST(Instruction, HALT)
{
	//TOADD:HALT
	Yolk::Memory::MemoryAllocator memory;
	Yolk::Memory::MemoryInterface interface(memory);
	InstructionTest itest(memory, interface);
	itest.HALT();
}

