#include "VM.h"
#include "OVO.h"
#include <stdexcept>
#include <string>

namespace Yolk {
    namespace VM {
       
        void AssertCondition(int condition, std::string message)
        {
            if(!condition)
            {
                throw VMException(message);
            }
        }
        
        const Instruction* Instruction::Select(const OPCode opcode)
        {
            switch(opcode)
            {
				case OPCode::MOV:
					const static Mov mov;
					return &mov;
				case OPCode::COPY:
					const static Copy copy;
					return &copy;
				case OPCode::CLONE:
					const static Clone clone;
					return &clone;
				case OPCode::NEW:
					const static New nnew;
					return &nnew;
				case OPCode::MOVM:
					const static Movm movm;
					return &movm;
				case OPCode::CALLM:
					const static Callm callm;
					return &callm;
				case OPCode::PUSHAR:
					const static Pushar pushar;
					return &pushar;
				case OPCode::POPAR:
					const static Popar popar;
					return &popar;
				case OPCode::CLRAR:
					const static Clrar clrar;
					return &clrar;
				case OPCode::PUSH:
					const static Push push;
					return &push;
				case OPCode::POP:
					const static Pop pop;
					return &pop;
				case OPCode::CLEAR:
					const static Clear clear;
					return &clear;
				case OPCode::CMP:
					const static Cmp cmp;
					return &cmp;
				case OPCode::CMPEQ:
					const static Cmpeq cmpeq;
					return &cmpeq;
				case OPCode::CMPNEQ:
					const static Cmpneq cmpneq;
					return &cmpneq;
				case OPCode::CMPLS:
					const static Cmpls cmpls;
					return &cmpls;
				case OPCode::CMPGT:
					const static Cmpgt cmpgt;
					return &cmpgt;
				case OPCode::CMPLSEQ:
					const static Cmplseq cmplseq;
					return &cmplseq;
				case OPCode::CMPGTEQ:
					const static Cmpgteq cmpgteq;
					return &cmpgteq;
				case OPCode::JNTRUE:
					const static Jntrue jntrue;
					return &jntrue;
				case OPCode::JNFALSE:
					const static Jnfalse jnfalse;
					return &jnfalse;
				case OPCode::JMP:
					const static Jmp jmp;
					return &jmp;
				case OPCode::CALL:
					const static Call call;
					return &call;
				case OPCode::RET:
					const static Ret ret;
					return &ret;
				case OPCode::ADD:
					const static Add add;
					return &add;
				case OPCode::SUB:
					const static Sub sub;
					return &sub;
				case OPCode::MUL:
					const static Mul mul;
					return &mul;
				case OPCode::DIV:
					const static Div div;
					return &div;
				case OPCode::MOD:
					const static Mod mod;
					return &mod;
				case OPCode::AND:
					const static And aand;
					return &aand;
				case OPCode::OR:
					const static Or oor;
					return &oor;
				case OPCode::CAST:
					const static Cast cast;
					return &cast;
				case OPCode::NAME:
					const static Name name;
					return &name;
				case OPCode::NAMEG:
					const static Nameg nameg;
					return &nameg;
				case OPCode::BRUP:
					const static Brup brup;
					return &brup;
				case OPCode::BRDW:
					const static Brdw brdw;
					return &brdw;
				case OPCode::BRHZ:
					const static Brhz brhz;
					return &brhz;
				case OPCode::RSBR:
					const static Rsbr rsbr;
					return &rsbr;
				case OPCode::ZERO:
					const static Zero zero;
					return &zero;
				case OPCode::HALT:
					const static Halt halt;
					return &halt;
                default:
                    const static Instruction generic;
                    return &generic;
            };
        }

        // Instruction Code Start:

		void Mov::Execute(VirtualMachine& machine, Ovo::Code::Arg& arg1, Ovo::Code::Arg& arg2) const
		{
			// Usage:         REGX, REGY  |   REGX, NAME
            // If Arg2 is a register, copies REGY onto REGX by reference. 
            // If Arg2 is a Name, searches in memory for a wrapper with that name and then copy it onto REGX by reference. 

            AssertCondition(arg1.type == ArgType::REGISTER, "Wrong argument for MOV instruction");
            Wrapper& regx = machine.SelectRegister(arg1.value);
            Wrapper regy = machine.GetMemory().GetVoidWrapper();
            switch(arg2.type)
            {
                case ArgType::REGISTER:
                    {
                        regy = machine.SelectRegister(arg2.value);
                        regx = regy;
                        break;
                    }
                case ArgType::NAME:
                    {
                        std::string text = machine.SelectText(arg2.value);
                        auto find = machine.GetInterface()->GetWrapper(text);  
                        regy = find.wrapper;
                        regx = regy;
                        break;
                    }
                default:
                    {
                        throw VMException("Wrong argument for MOV instruction");
                    }
            }


		}
		void Copy::Execute(VirtualMachine& machine, Ovo::Code::Arg& arg1, Ovo::Code::Arg& arg2) const
		{
			// Usage:        REGX, REGY  |   REGX, ELEMENTARY  |   REGX, NAME
            // Copies the value of a wrapper onto the other. This throws an exception if the two wrappers have different types. 
            // If Arg2 is a register, copies the value of REGY to the value of REGX.
            // If Arg2 is an Elementary type, copies the value of Arg2 to the value of REGX.
            // If Arg2 is a Name, searches in memory for a wrapper with that name and then copy its value to the value of REGX. 
            
            AssertCondition(arg1.type == ArgType::REGISTER, "Wrong argument for MOV instruction");
            Wrapper regx = machine.SelectRegister(arg1.value);
            switch(arg2.type)
            {
                case ArgType::REGISTER:
                    {
                        Wrapper regy = machine.SelectRegister(arg2.value);
                        regx.field->TrySET(*regy.field);
                        break;
                    }
                case ArgType::NAME:
                    {
                        std::string text = machine.SelectText(arg2.value);
                        auto find = machine.GetInterface()->GetWrapper(text);  
                        Wrapper regy = find.wrapper;
                        regx.field->TrySET(*regy.field);
                        break;
                    }
                case ArgType::INT32:
                    {
                        int32_t value = Bitcast<int32_t>(arg2.value);
                        regx.field->TrySET(value);
                        break;
                    }
                case ArgType::INT64:
                    {
                        int64_t value = Bitcast<int64_t>(arg2.value);
                        regx.field->TrySET(value);
                        break;
                    }
                case ArgType::UINT32:
                    {
                        uint32_t value = Bitcast<uint32_t>(arg2.value);
                        regx.field->TrySET(value);
                        break;
                    }
                case ArgType::UINT64:
                    {
                        uint64_t value = arg2.value;
                        regx.field->TrySET(value);
                        break;
                    }
                case ArgType::DOUBLE:
                    {
                        double value = Bitcast<double>(arg2.value);
                        regx.field->TrySET(value);
                        break;
                    }
                case ArgType::CHAR:
                    {
                        char value = Bitcast<char>(arg2.value);
                        regx.field->TrySET(value);
                        break;
                    }
                case ArgType::STRING:
                    {
                        std::string text = machine.SelectText(arg2.value);
                        regx.field->TrySET(text);
                        break;
                    }
                default:
                    {
                        throw VMException("Wrong argument for COPY instruction");
                    }
            }
		}
		void Clone::Execute(VirtualMachine& machine, Ovo::Code::Arg& arg1, Ovo::Code::Arg& arg2) const
		{
			// Usage:       REGX, REGY  |   REGX, NAME
            // If Arg2 is a register, clones REGY onto REGX.
            // If Arg2 is a Name, searches in memory for a wrapper with that name and then clones it onto REGX by value. 
            
            AssertCondition(arg1.type == ArgType::REGISTER, "Wrong argument for MOV instruction");
            Wrapper& regx = machine.SelectRegister(arg1.value);
            Wrapper regy = machine.GetMemory().GetVoidWrapper();
            switch(arg2.type)
            {
                case ArgType::REGISTER:
                    {
                        regy = machine.SelectRegister(arg2.value);
                        regx = machine.GetMemory().CreateCopy(regy);
                        break;
                    }
                case ArgType::NAME:
                    {
                        std::string text = machine.SelectText(arg2.value);
                        auto find = machine.GetInterface()->GetWrapper(text);  
                        regy = find.wrapper;
                        regx = machine.GetMemory().CreateCopy(regy);
                        break;
                    }
                default:
                    {
                        throw VMException("Wrong argument for CLONE instruction");
                    }
            }

		}
		void New::Execute(VirtualMachine& machine, Ovo::Code::Arg& arg1, Ovo::Code::Arg& arg2) const
		{
			// Usage:         REGX, ELEMENTARY
            // Allocates the elementary type onto memory and copies the wrapper to REGX.
            AssertCondition(arg1.type == ArgType::REGISTER, "Wrong argument for MOV instruction");
            AssertCondition(arg2.type == ArgType::ELEMENTARY, "Wrong argument for MOV instruction");
            
            Wrapper& regx = machine.SelectRegister(arg1.value);
            EType type = static_cast<EType>(arg2.value);

            switch(type)
            {
                case EType::INT32:
                    {
                        Wrapper w = machine.GetMemory().AllocateMemory<int32_t>();
                        regx = w;
                        break;
                    }
                case EType::INT64:
                    {
                        Wrapper w = machine.GetMemory().AllocateMemory<int64_t>();
                        regx = w;
                        break;
                    }
                case EType::UINT32:
                    {
                        Wrapper w = machine.GetMemory().AllocateMemory<uint32_t>();
                        regx = w;
                        break;
                    }
                case EType::UINT64:
                    {
                        Wrapper w = machine.GetMemory().AllocateMemory<uint64_t>();
                        regx = w;
                        break;
                    }
                case EType::FLOAT:
                    {
                        Wrapper w = machine.GetMemory().AllocateMemory<float>();
                        regx = w;
                        break;
                    }
                case EType::DOUBLE:
                    {
                        Wrapper w = machine.GetMemory().AllocateMemory<double>();
                        regx = w;
                        break;
                    }
                case EType::CHAR:
                    {
                        Wrapper w = machine.GetMemory().AllocateMemory<char>();
                        regx = w;
                        break;
                    }
                case EType::STRING:
                    {
                        Wrapper w = machine.GetMemory().AllocateMemory<std::string>();
                        regx = w;
                        break;
                    }
                default:
                    {
                        throw VMException("Wrong argument for NEW instruction");
                    }
            }

		}
		void Movm::Execute(VirtualMachine& machine, Ovo::Code::Arg& arg1, Ovo::Code::Arg& ) const
		{
			// Usage:        NAME
            // Searches in memory for a method wrapper with that name and then copy it onto the method register.
            AssertCondition(arg1.type == ArgType::NAME, "Wrong argument for MOV instruction");
            MethodWrapper& regm = machine.SelectMethodRegister();
            
            std::string text = machine.SelectText(arg1.value);
            auto find = machine.GetInterface()->GetMethodWrapper(text);  
            regm = find.wrapper;

		}
		void Callm::Execute(VirtualMachine& machine, Ovo::Code::Arg& , Ovo::Code::Arg& ) const
		{
			// Usage:  
            // Invokes the method wrapper in REGM
            Wrapper& regout = machine.SelectRegister(static_cast<uint64_t>(RegisterType::REGOUT));
            MethodWrapper regm = machine.SelectMethodRegister();
            WrapperArgument arguments = machine.SelectArgumentRegister();

            Wrapper out = regm.Invoke(arguments);
            
            regout = out;

		}
		void Pushar::Execute(VirtualMachine& machine, Ovo::Code::Arg& arg1, Ovo::Code::Arg& ) const
		{
			// Usage:      REGX
            // Pushes REGX onto the Argument stack
            
            AssertCondition(arg1.type == ArgType::REGISTER, "Wrong argument for Pushar instruction");
            Wrapper& regx = machine.SelectRegister(arg1.value);
            WrapperArgument& arguments = machine.SelectArgumentRegister();

            arguments.push_back(regx);

		}
		void Popar::Execute(VirtualMachine& machine, Ovo::Code::Arg& arg1, Ovo::Code::Arg& ) const
		{
			// Usage:    None   |   REGX
            // If Arg1 is None, pops the last element of the argument stack
            // If Arg1 is a register, pops the last element of the argument stack onto REGX
            WrapperArgument& arguments = machine.SelectArgumentRegister();
            switch(arg1.type)
            {
                case ArgType::REGISTER:
                    {
                        Wrapper& regx = machine.SelectRegister(arg1.value);
                        regx = arguments.back();
                        arguments.pop_back();
                        break;
                    }
                case ArgType::NONE:
                    {
                        arguments.pop_back();
                        break;
                    }
                default:
                    {
                        throw VMException("Wrong argument for POPAR instruction");
                    }
            }

		}
		void Clrar::Execute(VirtualMachine& machine, Ovo::Code::Arg& , Ovo::Code::Arg& ) const
		{
			// Usage:    
            // Clears the argument stack
            WrapperArgument& arguments = machine.SelectArgumentRegister();
            arguments.clear();
		}
		void Push::Execute(VirtualMachine& machine, Ovo::Code::Arg& arg1, Ovo::Code::Arg& ) const
		{
			// Usage:        REGX    
            // Pushes REGX into the Stack
            
            AssertCondition(arg1.type == ArgType::REGISTER, "Wrong argument for MOV instruction");
            Wrapper& regx = machine.SelectRegister(arg1.value);
            WrapperArgument& stack = machine.SelectStack();

            stack.push_back(regx);


		}
		void Pop::Execute(VirtualMachine& machine, Ovo::Code::Arg& arg1, Ovo::Code::Arg& ) const
		{
			// Usage:      NONE     |   REGX
            // If Arg1 is None, pops the last element of the stack
            // If Arg1 is a register, pops the last element of the stack onto REGX
            
            WrapperArgument& stack = machine.SelectStack();
            switch(arg1.type)
            {
                case ArgType::REGISTER:
                    {
                        Wrapper& regx = machine.SelectRegister(arg1.value);
                        regx = stack.back();
                        stack.pop_back();
                        break;
                    }
                case ArgType::NONE:
                    {
                        stack.pop_back();
                        break;
                    }
                default:
                    {
                        throw VMException("Wrong argument for POP instruction");
                    }
            }

		}
		void Clear::Execute(VirtualMachine& machine, Ovo::Code::Arg& , Ovo::Code::Arg& ) const
		{
			// Usage:    
            // Clears the stack
            WrapperArgument& stack = machine.SelectStack();
            stack.clear();
		}
		void Cmp::Execute(VirtualMachine& machine, Ovo::Code::Arg& arg1, Ovo::Code::Arg& ) const
		{
			// Usage:         REGX
            // Casts REGX to bool and check if it's valid.
            AssertCondition(arg1.type == ArgType::REGISTER, "Wrong argument for MOV instruction");
            Wrapper regx = machine.SelectRegister(arg1.value);
            bool& regcmp = machine.SelectCmpRegister();

            regcmp = regx.field->TryBOOL();
		}
		void Cmpeq::Execute(VirtualMachine& machine, Ovo::Code::Arg& arg1, Ovo::Code::Arg& arg2) const
		{
			// Usage:       REGX, REGY  |   REGX, ELEMENTARY    |   REGX, NAME   
            // if Arg2 is a register, compares REGX == REGY and set it's truth-value onto regcmp.
            // If Arg2 is an elementary value, compares RegX == value and set it's truth-value onto regcmp.
            // If Arg2 is a name, searches the memory for that wrapper, comapres RegX == Wrapper and set it's truth-value onto regcmp.
            
            AssertCondition(arg1.type == ArgType::REGISTER, "Wrong argument for MOV instruction");
            Wrapper regx = machine.SelectRegister(arg1.value);
            bool& regcmp = machine.SelectCmpRegister();
            
            switch(arg2.type)
            {
                case ArgType::REGISTER:
                    {
                        Wrapper regy = machine.SelectRegister(arg2.value);
                        regcmp = regx.field->TryEQ(*regy.field);
                        break;
                    }
                case ArgType::NAME:
                    {
                        std::string text = machine.SelectText(arg2.value);
                        auto find = machine.GetInterface()->GetWrapper(text);  
                        Wrapper regy = find.wrapper;
                        regcmp = regx.field->TryEQ(*regy.field);
                        break;
                    }
                case ArgType::INT32:
                    {
                        int32_t value = Bitcast<int32_t>(arg2.value);
                        regcmp = regx.field->TryEQ(value);
                        break;
                    }
                case ArgType::INT64:
                    {
                        int64_t value = Bitcast<int64_t>(arg2.value);
                        regcmp = regx.field->TryEQ(value);
                        break;
                    }
                case ArgType::UINT32:
                    {
                        uint32_t value = Bitcast<uint32_t>(arg2.value);
                        regcmp = regx.field->TryEQ(value);
                        break;
                    }
                case ArgType::UINT64:
                    {
                        uint64_t value = arg2.value;
                        regcmp = regx.field->TryEQ(value);
                        break;
                    }
                case ArgType::DOUBLE:
                    {
                        double value = Bitcast<double>(arg2.value);
                        regcmp = regx.field->TryEQ(value);
                        break;
                    }
                case ArgType::CHAR:
                    {
                        char value = Bitcast<char>(arg2.value);
                        regcmp = regx.field->TryEQ(value);
                        break;
                    }
                case ArgType::STRING:
                    {
                        std::string text = machine.SelectText(arg2.value);
                        regcmp = regx.field->TryEQ(text);
                        break;
                    }
                default:
                    {
                        throw VMException("Wrong argument for CMPEQ instruction");
                    }
            }

		}
		void Cmpneq::Execute(VirtualMachine& machine, Ovo::Code::Arg& arg1, Ovo::Code::Arg& arg2) const
		{
            // Usage:       REGX, REGY  |   REGX, ELEMENTARY    |   REGX, NAME   
            // if Arg2 is a register, compares REGX != REGY and set it's truth-value onto regcmp.
            // If Arg2 is an elementary value, compares RegX != value and set it's truth-value onto regcmp.
            // If Arg2 is a name, searches the memory for that wrapper, comapres RegX != Wrapper and set it's truth-value onto regcmp.
            AssertCondition(arg1.type == ArgType::REGISTER, "Wrong argument for MOV instruction");
            Wrapper regx = machine.SelectRegister(arg1.value);
            bool& regcmp = machine.SelectCmpRegister();
            
            switch(arg2.type)
            {
                case ArgType::REGISTER:
                    {
                        Wrapper regy = machine.SelectRegister(arg2.value);
                        regcmp = regx.field->TryNEQ(*regy.field);
                        break;
                    }
                case ArgType::NAME:
                    {
                        std::string text = machine.SelectText(arg2.value);
                        auto find = machine.GetInterface()->GetWrapper(text);  
                        Wrapper regy = find.wrapper;
                        regcmp = regx.field->TryNEQ(*regy.field);
                        break;
                    }
                case ArgType::INT32:
                    {
                        int32_t value = Bitcast<int32_t>(arg2.value);
                        regcmp = regx.field->TryNEQ(value);
                        break;
                    }
                case ArgType::INT64:
                    {
                        int64_t value = Bitcast<int64_t>(arg2.value);
                        regcmp = regx.field->TryNEQ(value);
                        break;
                    }
                case ArgType::UINT32:
                    {
                        uint32_t value = Bitcast<uint32_t>(arg2.value);
                        regcmp = regx.field->TryNEQ(value);
                        break;
                    }
                case ArgType::UINT64:
                    {
                        uint64_t value = arg2.value;
                        regcmp = regx.field->TryNEQ(value);
                        break;
                    }
                case ArgType::DOUBLE:
                    {
                        double value = Bitcast<double>(arg2.value);
                        regcmp = regx.field->TryNEQ(value);
                        break;
                    }
                case ArgType::CHAR:
                    {
                        char value = Bitcast<char>(arg2.value);
                        regcmp = regx.field->TryNEQ(value);
                        break;
                    }
                case ArgType::STRING:
                    {
                        std::string text = machine.SelectText(arg2.value);
                        regcmp = regx.field->TryNEQ(text);
                        break;
                    }
                default:
                    {
                        throw VMException("Wrong argument for CMPEQ instruction");
                    }
            }

		}
		void Cmpls::Execute(VirtualMachine& machine, Ovo::Code::Arg& arg1, Ovo::Code::Arg& arg2) const
		{
            // Usage:       REGX, REGY  |   REGX, ELEMENTARY    |   REGX, NAME   
            // if Arg2 is a register, compares REGX < REGY and set it's truth-value onto regcmp.
            // If Arg2 is an elementary value, compares RegX < value and set it's truth-value onto regcmp.
            // If Arg2 is a name, searches the memory for that wrapper, comapres RegX < Wrapper and set it's truth-value onto regcmp.
            //
            AssertCondition(arg1.type == ArgType::REGISTER, "Wrong argument for MOV instruction");
            Wrapper regx = machine.SelectRegister(arg1.value);
            bool& regcmp = machine.SelectCmpRegister();
            
            switch(arg2.type)
            {
                case ArgType::REGISTER:
                    {
                        Wrapper regy = machine.SelectRegister(arg2.value);
                        regcmp = regx.field->TryL(*regy.field);
                        break;
                    }
                case ArgType::NAME:
                    {
                        std::string text = machine.SelectText(arg2.value);
                        auto find = machine.GetInterface()->GetWrapper(text);  
                        Wrapper regy = find.wrapper;
                        regcmp = regx.field->TryL(*regy.field);
                        break;
                    }
                case ArgType::INT32:
                    {
                        int32_t value = Bitcast<int32_t>(arg2.value);
                        regcmp = regx.field->TryL(value);
                        break;
                    }
                case ArgType::INT64:
                    {
                        int64_t value = Bitcast<int64_t>(arg2.value);
                        regcmp = regx.field->TryL(value);
                        break;
                    }
                case ArgType::UINT32:
                    {
                        uint32_t value = Bitcast<uint32_t>(arg2.value);
                        regcmp = regx.field->TryL(value);
                        break;
                    }
                case ArgType::UINT64:
                    {
                        uint64_t value = arg2.value;
                        regcmp = regx.field->TryL(value);
                        break;
                    }
                case ArgType::DOUBLE:
                    {
                        double value = Bitcast<double>(arg2.value);
                        regcmp = regx.field->TryL(value);
                        break;
                    }
                case ArgType::CHAR:
                    {
                        char value = Bitcast<char>(arg2.value);
                        regcmp = regx.field->TryL(value);
                        break;
                    }
                case ArgType::STRING:
                    {
                        std::string text = machine.SelectText(arg2.value);
                        regcmp = regx.field->TryL(text);
                        break;
                    }
                default:
                    {
                        throw VMException("Wrong argument for CMPEQ instruction");
                    }
            }


		}
		void Cmpgt::Execute(VirtualMachine& machine, Ovo::Code::Arg& arg1, Ovo::Code::Arg& arg2) const
		{
            // Usage:       REGX, REGY  |   REGX, ELEMENTARY    |   REGX, NAME   
            // if Arg2 is a register, compares REGX > REGY and set it's truth-value onto regcmp.
            // If Arg2 is an elementary value, compares RegX > value and set it's truth-value onto regcmp.
            // If Arg2 is a name, searches the memory for that wrapper, comapres RegX > Wrapper and set it's truth-value onto regcmp.
            AssertCondition(arg1.type == ArgType::REGISTER, "Wrong argument for MOV instruction");
            Wrapper regx = machine.SelectRegister(arg1.value);
            bool& regcmp = machine.SelectCmpRegister();
            
            switch(arg2.type)
            {
                case ArgType::REGISTER:
                    {
                        Wrapper regy = machine.SelectRegister(arg2.value);
                        regcmp = regx.field->TryG(*regy.field);
                        break;
                    }
                case ArgType::NAME:
                    {
                        std::string text = machine.SelectText(arg2.value);
                        auto find = machine.GetInterface()->GetWrapper(text);  
                        Wrapper regy = find.wrapper;
                        regcmp = regx.field->TryG(*regy.field);
                        break;
                    }
                case ArgType::INT32:
                    {
                        int32_t value = Bitcast<int32_t>(arg2.value);
                        regcmp = regx.field->TryG(value);
                        break;
                    }
                case ArgType::INT64:
                    {
                        int64_t value = Bitcast<int64_t>(arg2.value);
                        regcmp = regx.field->TryG(value);
                        break;
                    }
                case ArgType::UINT32:
                    {
                        uint32_t value = Bitcast<uint32_t>(arg2.value);
                        regcmp = regx.field->TryG(value);
                        break;
                    }
                case ArgType::UINT64:
                    {
                        uint64_t value = arg2.value;
                        regcmp = regx.field->TryG(value);
                        break;
                    }
                case ArgType::DOUBLE:
                    {
                        double value = Bitcast<double>(arg2.value);
                        regcmp = regx.field->TryG(value);
                        break;
                    }
                case ArgType::CHAR:
                    {
                        char value = Bitcast<char>(arg2.value);
                        regcmp = regx.field->TryG(value);
                        break;
                    }
                case ArgType::STRING:
                    {
                        std::string text = machine.SelectText(arg2.value);
                        regcmp = regx.field->TryG(text);
                        break;
                    }
                default:
                    {
                        throw VMException("Wrong argument for CMPEQ instruction");
                    }
            }



		}
		void Cmplseq::Execute(VirtualMachine& machine, Ovo::Code::Arg& arg1, Ovo::Code::Arg& arg2) const
		{
            // Usage:       REGX, REGY  |   REGX, ELEMENTARY    |   REGX, NAME   
            // if Arg2 is a register, compares REGX <= REGY and set it's truth-value onto regcmp.
            // If Arg2 is an elementary value, compares RegX <= value and set it's truth-value onto regcmp.
            // If Arg2 is a name, searches the memory for that wrapper, comapres RegX <= Wrapper and set it's truth-value onto regcmp.
            AssertCondition(arg1.type == ArgType::REGISTER, "Wrong argument for MOV instruction");
            Wrapper regx = machine.SelectRegister(arg1.value);
            bool& regcmp = machine.SelectCmpRegister();
            
            switch(arg2.type)
            {
                case ArgType::REGISTER:
                    {
                        Wrapper regy = machine.SelectRegister(arg2.value);
                        regcmp = regx.field->TryLE(*regy.field);
                        break;
                    }
                case ArgType::NAME:
                    {
                        std::string text = machine.SelectText(arg2.value);
                        auto find = machine.GetInterface()->GetWrapper(text);  
                        Wrapper regy = find.wrapper;
                        regcmp = regx.field->TryLE(*regy.field);
                        break;
                    }
                case ArgType::INT32:
                    {
                        int32_t value = Bitcast<int32_t>(arg2.value);
                        regcmp = regx.field->TryLE(value);
                        break;
                    }
                case ArgType::INT64:
                    {
                        int64_t value = Bitcast<int64_t>(arg2.value);
                        regcmp = regx.field->TryLE(value);
                        break;
                    }
                case ArgType::UINT32:
                    {
                        uint32_t value = Bitcast<uint32_t>(arg2.value);
                        regcmp = regx.field->TryLE(value);
                        break;
                    }
                case ArgType::UINT64:
                    {
                        uint64_t value = arg2.value;
                        regcmp = regx.field->TryLE(value);
                        break;
                    }
                case ArgType::DOUBLE:
                    {
                        double value = Bitcast<double>(arg2.value);
                        regcmp = regx.field->TryLE(value);
                        break;
                    }
                case ArgType::CHAR:
                    {
                        char value = Bitcast<char>(arg2.value);
                        regcmp = regx.field->TryLE(value);
                        break;
                    }
                case ArgType::STRING:
                    {
                        std::string text = machine.SelectText(arg2.value);
                        regcmp = regx.field->TryLE(text);
                        break;
                    }
                default:
                    {
                        throw VMException("Wrong argument for CMPEQ instruction");
                    }
            }

		}
		void Cmpgteq::Execute(VirtualMachine& machine, Ovo::Code::Arg& arg1, Ovo::Code::Arg& arg2) const
		{
            // Usage:       REGX, REGY  |   REGX, ELEMENTARY    |   REGX, NAME   
            // if Arg2 is a register, compares REGX >= REGY and set it's truth-value onto regcmp.
            // If Arg2 is an elementary value, compares RegX >= value and set it's truth-value onto regcmp.
            // If Arg2 is a name, searches the memory for that wrapper, comapres RegX >= Wrapper and set it's truth-value onto regcmp.
            AssertCondition(arg1.type == ArgType::REGISTER, "Wrong argument for MOV instruction");
            Wrapper regx = machine.SelectRegister(arg1.value);
            bool& regcmp = machine.SelectCmpRegister();
            
            switch(arg2.type)
            {
                case ArgType::REGISTER:
                    {
                        Wrapper regy = machine.SelectRegister(arg2.value);
                        regcmp = regx.field->TryGE(*regy.field);
                        break;
                    }
                case ArgType::NAME:
                    {
                        std::string text = machine.SelectText(arg2.value);
                        auto find = machine.GetInterface()->GetWrapper(text);  
                        Wrapper regy = find.wrapper;
                        regcmp = regx.field->TryGE(*regy.field);
                        break;
                    }
                case ArgType::INT32:
                    {
                        int32_t value = Bitcast<int32_t>(arg2.value);
                        regcmp = regx.field->TryGE(value);
                        break;
                    }
                case ArgType::INT64:
                    {
                        int64_t value = Bitcast<int64_t>(arg2.value);
                        regcmp = regx.field->TryGE(value);
                        break;
                    }
                case ArgType::UINT32:
                    {
                        uint32_t value = Bitcast<uint32_t>(arg2.value);
                        regcmp = regx.field->TryGE(value);
                        break;
                    }
                case ArgType::UINT64:
                    {
                        uint64_t value = arg2.value;
                        regcmp = regx.field->TryGE(value);
                        break;
                    }
                case ArgType::DOUBLE:
                    {
                        double value = Bitcast<double>(arg2.value);
                        regcmp = regx.field->TryGE(value);
                        break;
                    }
                case ArgType::CHAR:
                    {
                        char value = Bitcast<char>(arg2.value);
                        regcmp = regx.field->TryGE(value);
                        break;
                    }
                case ArgType::STRING:
                    {
                        std::string text = machine.SelectText(arg2.value);
                        regcmp = regx.field->TryGE(text);
                        break;
                    }
                default:
                    {
                        throw VMException("Wrong argument for CMPEQ instruction");
                    }
            }

		}
		void Jntrue::Execute(VirtualMachine& machine, Ovo::Code::Arg& arg1, Ovo::Code::Arg& ) const
		{
			// Usage:      REGX        |   UINT
            // If Arg1 is a register, cast it's value to uint and jumps to that position if regcmp is true
            // If Arg1 is an uint, jump to that value if regcmp is true
            bool& regcmp = machine.SelectCmpRegister();
            
            if(regcmp)
            {
                switch(arg1.type)
                {
                    case ArgType::REGISTER:
                        {
                            Wrapper regx = machine.SelectRegister(arg1.value);
                            uint64_t position = regx.field->As<uint64_t>();
                            machine.Jump(position);
                            break;
                        }
                    case ArgType::UINT64:
                        {
                            uint64_t position = arg1.value;
                            machine.Jump(position);
                            break;
                        }
                    default:
                        {
                            throw VMException("Wrong argument for POPAR instruction");
                        }
                }
            }

		}
		void Jnfalse::Execute(VirtualMachine& machine, Ovo::Code::Arg& arg1, Ovo::Code::Arg& ) const
		{
			// Usage:     REGX        |   UINT
            // If Arg1 is a register, cast it's value to uint and jumps to that position if regcmp is false
            // If Arg1 is an uint, jump to that value if regcmp is false
            bool& regcmp = machine.SelectCmpRegister();
            
            if(!regcmp)
            {
                switch(arg1.type)
                {
                    case ArgType::REGISTER:
                        {
                            Wrapper regx = machine.SelectRegister(arg1.value);
                            uint64_t position = regx.field->As<uint64_t>();
                            machine.Jump(position);
                            break;
                        }
                    case ArgType::UINT64:
                        {
                            uint64_t position = arg1.value;
                            machine.Jump(position);
                            break;
                        }
                    default:
                        {
                            throw VMException("Wrong argument for POPAR instruction");
                        }
                }
            }
		}
		void Jmp::Execute(VirtualMachine& machine, Ovo::Code::Arg& arg1, Ovo::Code::Arg& ) const
		{
			// Usage:         REGX        |   UINT
            // If Arg1 is a register, cast it's value to uint and jumps to that position
            // If Arg1 is an uint, jump to that value
            switch(arg1.type)
                {
                    case ArgType::REGISTER:
                        {
                            Wrapper regx = machine.SelectRegister(arg1.value);
                            uint64_t position = regx.field->As<uint64_t>();
                            machine.Jump(position);
                            break;
                        }
                    case ArgType::UINT64:
                        {
                            uint64_t position = arg1.value;
                            machine.Jump(position);
                            break;
                        }
                    default:
                        {
                            throw VMException("Wrong argument for POPAR instruction");
                        }
                }
            
		}
		void Call::Execute(VirtualMachine& machine, Ovo::Code::Arg& arg1, Ovo::Code::Arg& ) const
		{
			// Usage:        REGX        |   UINT
            // Copies the position of ip onto the stack
            // If Arg1 is a register, cast it's value to uint and jumps to that position
            // If Arg1 is an uint, jump to that value
            
            uint64_t current_position = machine.GetPosition();
            Wrapper w = machine.GetMemory().AllocateMemory<uint64_t>(current_position);
            
            WrapperArgument& stack = machine.SelectStack();
            stack.push_back(w);

            switch(arg1.type)
                {
                    case ArgType::REGISTER:
                        {
                            Wrapper regx = machine.SelectRegister(arg1.value);
                            uint64_t position = regx.field->As<uint64_t>();
                            machine.Jump(position);
                            break;
                        }
                    case ArgType::UINT64:
                        {
                            uint64_t position = arg1.value;
                            machine.Jump(position);
                            break;
                        }
                    default:
                        {
                            throw VMException("Wrong argument for POPAR instruction");
                        }
                }
		}
		void Ret::Execute(VirtualMachine& machine, Ovo::Code::Arg& , Ovo::Code::Arg& ) const
		{
			// Usage: 
            // Pops the stack onto the position of ip.
            
            WrapperArgument& stack = machine.SelectStack();
            Wrapper w = stack.back();
            stack.pop_back();

            uint64_t jump_position = w.field->As<uint64_t>();
            machine.Jump(jump_position);
		}
		void Add::Execute(VirtualMachine& machine, Ovo::Code::Arg& arg1, Ovo::Code::Arg& arg2) const
		{
			// Usage:         REGX, REGY  |   REGX, ELEMENTARY    |   REGX, NAME
            // If Arg2 is a register, does REGX += REGY
            // If Arg2 is an elementary value, does REGX += value
            // If Arg2 is a name, search the memory for that wrapper and do REGX += Wrapper
            
            AssertCondition(arg1.type == ArgType::REGISTER, "Wrong argument for MOV instruction");
            Wrapper regx = machine.SelectRegister(arg1.value);
            
            switch(arg2.type)
            {
                case ArgType::REGISTER:
                    {
                        Wrapper regy = machine.SelectRegister(arg2.value);
                        regx.field->TryPLUS(*regy.field);
                        break;
                    }
                case ArgType::NAME:
                    {
                        std::string text = machine.SelectText(arg2.value);
                        auto find = machine.GetInterface()->GetWrapper(text);  
                        Wrapper regy = find.wrapper;
                        regx.field->TryPLUS(*regy.field);
                        break;
                    }
                case ArgType::INT32:
                    {
                        int32_t value = Bitcast<int32_t>(arg2.value);
                        regx.field->TryPLUS(value);
                        break;
                    }
                case ArgType::INT64:
                    {
                        int64_t value = Bitcast<int64_t>(arg2.value);
                        regx.field->TryPLUS(value);
                        break;
                    }
                case ArgType::UINT32:
                    {
                        uint32_t value = Bitcast<uint32_t>(arg2.value);
                        regx.field->TryPLUS(value);
                        break;
                    }
                case ArgType::UINT64:
                    {
                        uint64_t value = arg2.value;
                        regx.field->TryPLUS(value);
                        break;
                    }
                case ArgType::DOUBLE:
                    {
                        double value = Bitcast<double>(arg2.value);
                        regx.field->TryPLUS(value);
                        break;
                    }
                case ArgType::CHAR:
                    {
                        char value = Bitcast<char>(arg2.value);
                        regx.field->TryPLUS(value);
                        break;
                    }
                case ArgType::STRING:
                    {
                        std::string text = machine.SelectText(arg2.value);
                        regx.field->TryPLUS(text);
                        break;
                    }
                default:
                    {
                        throw VMException("Wrong argument for CMPEQ instruction");
                    }
            }

		}
		void Sub::Execute(VirtualMachine& machine, Ovo::Code::Arg& arg1, Ovo::Code::Arg& arg2) const
		{
			// Usage:         REGX, REGY  |   REGX, ELEMENTARY    |   REGX, NAME
            // If Arg2 is a register, does REGX -= REGY
            // If Arg2 is an elementary value, does REGX -= value
            // If Arg2 is a name, search the memory for that wrapper and do REGX -= Wrapper
            AssertCondition(arg1.type == ArgType::REGISTER, "Wrong argument for MOV instruction");
            Wrapper regx = machine.SelectRegister(arg1.value);
            
            switch(arg2.type)
            {
                case ArgType::REGISTER:
                    {
                        Wrapper regy = machine.SelectRegister(arg2.value);
                        regx.field->TrySUB(*regy.field);
                        break;
                    }
                case ArgType::NAME:
                    {
                        std::string text = machine.SelectText(arg2.value);
                        auto find = machine.GetInterface()->GetWrapper(text);  
                        Wrapper regy = find.wrapper;
                        regx.field->TrySUB(*regy.field);
                        break;
                    }
                case ArgType::INT32:
                    {
                        int32_t value = Bitcast<int32_t>(arg2.value);
                        regx.field->TrySUB(value);
                        break;
                    }
                case ArgType::INT64:
                    {
                        int64_t value = Bitcast<int64_t>(arg2.value);
                        regx.field->TrySUB(value);
                        break;
                    }
                case ArgType::UINT32:
                    {
                        uint32_t value = Bitcast<uint32_t>(arg2.value);
                        regx.field->TrySUB(value);
                        break;
                    }
                case ArgType::UINT64:
                    {
                        uint64_t value = arg2.value;
                        regx.field->TrySUB(value);
                        break;
                    }
                case ArgType::DOUBLE:
                    {
                        double value = Bitcast<double>(arg2.value);
                        regx.field->TrySUB(value);
                        break;
                    }
                case ArgType::CHAR:
                    {
                        char value = Bitcast<char>(arg2.value);
                        regx.field->TrySUB(value);
                        break;
                    }
                case ArgType::STRING:
                    {
                        std::string text = machine.SelectText(arg2.value);
                        regx.field->TrySUB(text);
                        break;
                    }
                default:
                    {
                        throw VMException("Wrong argument for CMPEQ instruction");
                    }
            }
		}
		void Mul::Execute(VirtualMachine& machine, Ovo::Code::Arg& arg1, Ovo::Code::Arg& arg2) const
		{
			// Usage:         REGX, REGY  |   REGX, ELEMENTARY    |   REGX, NAME
            // If Arg2 is a register, does REGX *= REGY
            // If Arg2 is an elementary value, does REGX *= value
            // If Arg2 is a name, search the memory for that wrapper and do REGX *= Wrapper
            //
            AssertCondition(arg1.type == ArgType::REGISTER, "Wrong argument for MOV instruction");
            Wrapper regx = machine.SelectRegister(arg1.value);
            
            switch(arg2.type)
            {
                case ArgType::REGISTER:
                    {
                        Wrapper regy = machine.SelectRegister(arg2.value);
                        regx.field->TryPROD(*regy.field);
                        break;
                    }
                case ArgType::NAME:
                    {
                        std::string text = machine.SelectText(arg2.value);
                        auto find = machine.GetInterface()->GetWrapper(text);  
                        Wrapper regy = find.wrapper;
                        regx.field->TryPROD(*regy.field);
                        break;
                    }
                case ArgType::INT32:
                    {
                        int32_t value = Bitcast<int32_t>(arg2.value);
                        regx.field->TryPROD(value);
                        break;
                    }
                case ArgType::INT64:
                    {
                        int64_t value = Bitcast<int64_t>(arg2.value);
                        regx.field->TryPROD(value);
                        break;
                    }
                case ArgType::UINT32:
                    {
                        uint32_t value = Bitcast<uint32_t>(arg2.value);
                        regx.field->TryPROD(value);
                        break;
                    }
                case ArgType::UINT64:
                    {
                        uint64_t value = arg2.value;
                        regx.field->TryPROD(value);
                        break;
                    }
                case ArgType::DOUBLE:
                    {
                        double value = Bitcast<double>(arg2.value);
                        regx.field->TryPROD(value);
                        break;
                    }
                case ArgType::CHAR:
                    {
                        char value = Bitcast<char>(arg2.value);
                        regx.field->TryPROD(value);
                        break;
                    }
                case ArgType::STRING:
                    {
                        std::string text = machine.SelectText(arg2.value);
                        regx.field->TryPROD(text);
                        break;
                    }
                default:
                    {
                        throw VMException("Wrong argument for CMPEQ instruction");
                    }
            }
		}
		void Div::Execute(VirtualMachine& machine, Ovo::Code::Arg& arg1, Ovo::Code::Arg& arg2) const
		{
			// Usage:         REGX, REGY  |   REGX, ELEMENTARY    |   REGX, NAME
            // If Arg2 is a register, does REGX /= REGY
            // If Arg2 is an elementary value, does REGX /= value
            // If Arg2 is a name, search the memory for that wrapper and do REGX /= Wrapper
            AssertCondition(arg1.type == ArgType::REGISTER, "Wrong argument for MOV instruction");
            Wrapper regx = machine.SelectRegister(arg1.value);
            
            switch(arg2.type)
            {
                case ArgType::REGISTER:
                    {
                        Wrapper regy = machine.SelectRegister(arg2.value);
                        regx.field->TryDIV(*regy.field);
                        break;
                    }
                case ArgType::NAME:
                    {
                        std::string text = machine.SelectText(arg2.value);
                        auto find = machine.GetInterface()->GetWrapper(text);  
                        Wrapper regy = find.wrapper;
                        regx.field->TryDIV(*regy.field);
                        break;
                    }
                case ArgType::INT32:
                    {
                        int32_t value = Bitcast<int32_t>(arg2.value);
                        regx.field->TryDIV(value);
                        break;
                    }
                case ArgType::INT64:
                    {
                        int64_t value = Bitcast<int64_t>(arg2.value);
                        regx.field->TryDIV(value);
                        break;
                    }
                case ArgType::UINT32:
                    {
                        uint32_t value = Bitcast<uint32_t>(arg2.value);
                        regx.field->TryDIV(value);
                        break;
                    }
                case ArgType::UINT64:
                    {
                        uint64_t value = arg2.value;
                        regx.field->TryDIV(value);
                        break;
                    }
                case ArgType::DOUBLE:
                    {
                        double value = Bitcast<double>(arg2.value);
                        regx.field->TryDIV(value);
                        break;
                    }
                case ArgType::CHAR:
                    {
                        char value = Bitcast<char>(arg2.value);
                        regx.field->TryDIV(value);
                        break;
                    }
                case ArgType::STRING:
                    {
                        std::string text = machine.SelectText(arg2.value);
                        regx.field->TryDIV(text);
                        break;
                    }
                default:
                    {
                        throw VMException("Wrong argument for CMPEQ instruction");
                    }
            }
		}
		void Mod::Execute(VirtualMachine& machine, Ovo::Code::Arg& arg1, Ovo::Code::Arg& arg2) const
		{
			// Usage:         REGX, REGY  |   REGX, ELEMENTARY    |   REGX, NAME
            // If Arg2 is a register, does REGX %= REGY
            // If Arg2 is an elementary value, does REGX %= value
            // If Arg2 is a name, search the memory for that wrapper and do REGX %= Wrapper
            AssertCondition(arg1.type == ArgType::REGISTER, "Wrong argument for MOV instruction");
            Wrapper regx = machine.SelectRegister(arg1.value);
            
            switch(arg2.type)
            {
                case ArgType::REGISTER:
                    {
                        Wrapper regy = machine.SelectRegister(arg2.value);
                        regx.field->TryMOD(*regy.field);
                        break;
                    }
                case ArgType::NAME:
                    {
                        std::string text = machine.SelectText(arg2.value);
                        auto find = machine.GetInterface()->GetWrapper(text);  
                        Wrapper regy = find.wrapper;
                        regx.field->TryMOD(*regy.field);
                        break;
                    }
                case ArgType::INT32:
                    {
                        int32_t value = Bitcast<int32_t>(arg2.value);
                        regx.field->TryMOD(value);
                        break;
                    }
                case ArgType::INT64:
                    {
                        int64_t value = Bitcast<int64_t>(arg2.value);
                        regx.field->TryMOD(value);
                        break;
                    }
                case ArgType::UINT32:
                    {
                        uint32_t value = Bitcast<uint32_t>(arg2.value);
                        regx.field->TryMOD(value);
                        break;
                    }
                case ArgType::UINT64:
                    {
                        uint64_t value = arg2.value;
                        regx.field->TryMOD(value);
                        break;
                    }
                case ArgType::DOUBLE:
                    {
                        double value = Bitcast<double>(arg2.value);
                        regx.field->TryMOD(value);
                        break;
                    }
                case ArgType::CHAR:
                    {
                        char value = Bitcast<char>(arg2.value);
                        regx.field->TryMOD(value);
                        break;
                    }
                case ArgType::STRING:
                    {
                        std::string text = machine.SelectText(arg2.value);
                        regx.field->TryMOD(text);
                        break;
                    }
                default:
                    {
                        throw VMException("Wrong argument for CMPEQ instruction");
                    }
            }
		}
		void And::Execute(VirtualMachine& machine, Ovo::Code::Arg& arg1, Ovo::Code::Arg& arg2) const
		{
			// Usage:         REGX, REGY  |   REGX, ELEMENTARY    |   REGX, NAME
            // If Arg2 is a register, does REGX &&= REGY
            // If Arg2 is an elementary value, does REGX &&= value
            // If Arg2 is a name, search the memory for that wrapper and do REGX &&= Wrapper
            AssertCondition(arg1.type == ArgType::REGISTER, "Wrong argument for MOV instruction");
            Wrapper regx = machine.SelectRegister(arg1.value);
            
            switch(arg2.type)
            {
                case ArgType::REGISTER:
                    {
                        Wrapper regy = machine.SelectRegister(arg2.value);
                        regx.field->TryAND(*regy.field);
                        break;
                    }
                case ArgType::NAME:
                    {
                        std::string text = machine.SelectText(arg2.value);
                        auto find = machine.GetInterface()->GetWrapper(text);  
                        Wrapper regy = find.wrapper;
                        regx.field->TryAND(*regy.field);
                        break;
                    }
                case ArgType::INT32:
                    {
                        int32_t value = Bitcast<int32_t>(arg2.value);
                        regx.field->TryAND(value);
                        break;
                    }
                case ArgType::INT64:
                    {
                        int64_t value = Bitcast<int64_t>(arg2.value);
                        regx.field->TryAND(value);
                        break;
                    }
                case ArgType::UINT32:
                    {
                        uint32_t value = Bitcast<uint32_t>(arg2.value);
                        regx.field->TryAND(value);
                        break;
                    }
                case ArgType::UINT64:
                    {
                        uint64_t value = arg2.value;
                        regx.field->TryAND(value);
                        break;
                    }
                case ArgType::DOUBLE:
                    {
                        double value = Bitcast<double>(arg2.value);
                        regx.field->TryAND(value);
                        break;
                    }
                case ArgType::CHAR:
                    {
                        char value = Bitcast<char>(arg2.value);
                        regx.field->TryAND(value);
                        break;
                    }
                case ArgType::STRING:
                    {
                        std::string text = machine.SelectText(arg2.value);
                        regx.field->TryAND(text);
                        break;
                    }
                default:
                    {
                        throw VMException("Wrong argument for CMPEQ instruction");
                    }
            }
		}
		void Or::Execute(VirtualMachine& machine, Ovo::Code::Arg& arg1, Ovo::Code::Arg& arg2) const
		{
			// Usage:          REGX, REGY  |   REGX, ELEMENTARY    |   REGX, NAME
            // If Arg2 is a register, does REGX ||= REGY
            // If Arg2 is an elementary value, does REGX ||= value
            // If Arg2 is a name, search the memory for that wrapper and do REGX ||= Wrapper
            AssertCondition(arg1.type == ArgType::REGISTER, "Wrong argument for MOV instruction");
            Wrapper regx = machine.SelectRegister(arg1.value);
            
            switch(arg2.type)
            {
                case ArgType::REGISTER:
                    {
                        Wrapper regy = machine.SelectRegister(arg2.value);
                        regx.field->TryOR(*regy.field);
                        break;
                    }
                case ArgType::NAME:
                    {
                        std::string text = machine.SelectText(arg2.value);
                        auto find = machine.GetInterface()->GetWrapper(text);  
                        Wrapper regy = find.wrapper;
                        regx.field->TryOR(*regy.field);
                        break;
                    }
                case ArgType::INT32:
                    {
                        int32_t value = Bitcast<int32_t>(arg2.value);
                        regx.field->TryOR(value);
                        break;
                    }
                case ArgType::INT64:
                    {
                        int64_t value = Bitcast<int64_t>(arg2.value);
                        regx.field->TryOR(value);
                        break;
                    }
                case ArgType::UINT32:
                    {
                        uint32_t value = Bitcast<uint32_t>(arg2.value);
                        regx.field->TryOR(value);
                        break;
                    }
                case ArgType::UINT64:
                    {
                        uint64_t value = arg2.value;
                        regx.field->TryOR(value);
                        break;
                    }
                case ArgType::DOUBLE:
                    {
                        double value = Bitcast<double>(arg2.value);
                        regx.field->TryOR(value);
                        break;
                    }
                case ArgType::CHAR:
                    {
                        char value = Bitcast<char>(arg2.value);
                        regx.field->TryOR(value);
                        break;
                    }
                case ArgType::STRING:
                    {
                        std::string text = machine.SelectText(arg2.value);
                        regx.field->TryOR(text);
                        break;
                    }
                default:
                    {
                        throw VMException("Wrong argument for CMPEQ instruction");
                    }
            }
		}
		void Cast::Execute(VirtualMachine& machine, Ovo::Code::Arg& arg1, Ovo::Code::Arg& arg2) const
		{
			// Usage:        REGX, REGY  |   REGX, TYPE          |   REGX, NAME
            // If Arg2 is a register, casts REGX to the type of REGY
            // If Arg2 is a type, casts REGX to that type
            // If Arg2 is a name, search the memory for that wrapper and casts REGX to the type of that wrapper
            
            AssertCondition(arg1.type == ArgType::REGISTER, "Wrong argument for MOV instruction");
            Wrapper& regx = machine.SelectRegister(arg1.value);
            switch(arg2.type)
            {
                case ArgType::REGISTER:
                    {
                        Wrapper regy = machine.SelectRegister(arg2.value);
                        regx.field->CastAs(*regy.field);
                        break;
                    }
                case ArgType::NAME:
                    {
                        std::string text = machine.SelectText(arg2.value);
                        auto find = machine.GetInterface()->GetWrapper(text);  
                        Wrapper regy = find.wrapper;
                        regx.field->CastAs(*regy.field);
                        break;
                    }
                case ArgType::ELEMENTARY:
                    {
                        EType type = static_cast<EType>(arg2.value);
                        switch(type)
                        {
                            case EType::INT32:
                                {
                                    regx.field->Cast<int32_t>();
                                    break;
                                }
                            case EType::INT64:
                                {
                                    regx.field->Cast<int64_t>();
                                    break;
                                }
                            case EType::UINT32:
                                {
                                    regx.field->Cast<uint32_t>();
                                    break;
                                }
                            case EType::UINT64:
                                {
                                    regx.field->Cast<uint64_t>();
                                    break;
                                }
                            case EType::FLOAT:
                                {
                                    regx.field->Cast<float>();
                                    break;
                                }
                            case EType::DOUBLE:
                                {
                                    regx.field->Cast<double>();
                                    break;
                                }
                            case EType::CHAR:
                                {
                                    regx.field->Cast<char>();
                                    break;
                                }
                            case EType::STRING:
                                {
                                    regx.field->Cast<std::string>();
                                    break;
                                }
                            default:
                                {
                                    throw VMException("Wrong argument for NEW instruction");
                                }
                            }
                        break;
                    }
                default:
                    {
                        throw VMException("Wrong argument for MOV instruction");
                    }
            }

		}
		void Name::Execute(VirtualMachine& machine, Ovo::Code::Arg& arg1, Ovo::Code::Arg& arg2) const
		{
			// Usage:        REGX, STRING 
            // Copies RegX to the memory under the name in Arg2
            AssertCondition(arg1.type == ArgType::REGISTER, "Wrong argument for MOV instruction");
            Wrapper regx = machine.SelectRegister(arg1.value);

            AssertCondition(arg2.type == ArgType::NAME, "Wrong argument for NAME instruction");
            std::string name = machine.SelectText(arg2.value);

            machine.GetInterface()->RegisterWrapper(regx, name, false);

		}
		void Nameg::Execute(VirtualMachine& machine, Ovo::Code::Arg& arg1, Ovo::Code::Arg& arg2) const
		{
			// Usage:       REGX, STRING
            // Copies RegX to the global memory under the name in Arg2
            AssertCondition(arg1.type == ArgType::REGISTER, "Wrong argument for MOV instruction");
            Wrapper regx = machine.SelectRegister(arg1.value);

            AssertCondition(arg2.type == ArgType::NAME, "Wrong argument for NAME instruction");
            std::string name = machine.SelectText(arg2.value);

            machine.GetInterface()->RegisterWrapper(regx, name, true);
		}
		void Brup::Execute(VirtualMachine& machine, Ovo::Code::Arg& , Ovo::Code::Arg& ) const
		{
			// Usage: 
            // Branches UP
            machine.GetInterface()->BranchUp();
		}
		void Brdw::Execute(VirtualMachine& machine, Ovo::Code::Arg& , Ovo::Code::Arg& ) const
		{
			// Usage:     
            // Branches DOWN
            machine.GetInterface()->BranchDown();
		}
		void Brhz::Execute(VirtualMachine& machine, Ovo::Code::Arg& arg1, Ovo::Code::Arg& ) const
		{
			// Usage:        STRING    
            // Branches horizontally to the memory under the name in Arg1
            AssertCondition(arg1.type == ArgType::NAME, "Wrong argument for NAME instruction");
            std::string name = machine.SelectText(arg1.value);

            auto find = machine.GetInterface()->GetMemoryPointer(name);
            Memory::MemoryInterface* interface = find.memory;

            machine.UpdateInterface(interface);
		}
		void Rsbr::Execute(VirtualMachine& machine, Ovo::Code::Arg& , Ovo::Code::Arg& ) const
		{
			// Usage: 
            // Resets Branching.
            machine.ResetInterface();
		}
		void Zero::Execute(VirtualMachine& , Ovo::Code::Arg& , Ovo::Code::Arg& ) const
		{
			// Usage:     
            // Does nothing.
		}
		void Halt::Execute(VirtualMachine& machine, Ovo::Code::Arg& , Ovo::Code::Arg& ) const
		{
			// Usage:     
            // Stops the machine.
            machine.Halt();
		}

        // Instruction Code End:

    }
}
