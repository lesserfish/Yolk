#include "VM.h"
#include "OVO.h"
#include <stdexcept>
#include <string>

#ifndef Int64
#define Int64 int64_t
#endif

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

// TODO: Remove this.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

        // Instruction Code Start:

		void Mov::Execute(VirtualMachine& machine, Ovo::Code::Arg& arg1, Ovo::Code::Arg& arg2)
		{
			// Usage:         REGX, REGY  |   REGX, NAME
            // If Arg2 is a register, copies REGY onto REGX by reference. 
            // If Arg2 is a Name, searches in memory for a wrapper with that name and then copy it onto REGX by reference. 

            AssertCondition(arg1.type == ArgType::REGISTER, "Wrong argument for MOV instruction");
            Wrapper* regx = &machine.SelectRegister(arg1.value);
            Wrapper regy = machine.GetMemory().GetVoidWrapper();
            switch(arg2.type)
            {
                case ArgType::REGISTER:
                    {
                        regy = machine.SelectRegister(arg2.value);
                        break;
                    }
                case ArgType::NAME:
                    {
                        std::string text = machine.SelectText(arg2.value);
                        auto find = machine.GetInterface()->GetWrapper(text);  
                        regy = find.wrapper;
                        break;
                    }
                default:
                    {
                        throw VMException("Wrong argument for MOV instruction");
                    }
            }

            *regx = regy;

		}
		void Copy::Execute(VirtualMachine& machine, Ovo::Code::Arg& arg1, Ovo::Code::Arg& arg2)
		{
			// Usage:        REGX, REGY  |   REGX, ELEMENTARY  |   REGX, NAME
            // Copies the value of a wrapper onto the other. This throws an exception if the two wrappers have different types. 
            // If Arg2 is a register, copies the value of REGY to the value of REGX.
            // If Arg2 is an Elementary type, copies the value of Arg2 to the value of REGX.
            // If Arg2 is a Name, searches in memory for a wrapper with that name and then copy its value to the value of REGX. 
            
//            AssertCondition(arg1.type == ArgType::REGISTER, "Wrong argument for MOV instruction");
//            Wrapper regx = machine.SelectRegister(arg1.value);
//            Wrapper regy = machine.GetMemory().GetVoidWrapper();
//            switch(arg2.type)
//            {
//                case ArgType::REGISTER:
//                    {
//                        regy = machine.SelectRegister(arg2.value);
//                        break;
//                    }
//                case ArgType::NAME:
//                    {
//                        std::string text = machine.SelectText(arg2.value);
//                        auto find = machine.GetInterface()->GetWrapper(text);  
//                        regy = find.wrapper;
//                        break;
//                    }
//                case ArgType::INT32:
//                    {
//                        int32_t value = (int32_t)arg2.value;
//                        Wrapper newWrapper = machine.GetMemory().AllocateMemory<int32_t>();
//                        regy = newWrapper;
//                        break;
//                    }
//                case ArgType::INT64:
//                    {
//                        int64_t value = (int64_t)arg2.value;
//                        Wrapper newWrapper = machine.GetMemory().AllocateMemory<int64_t>();
//                        regy = newWrapper;
//                        break;
//                    }
//                case ArgType::UINT64:
//                    {
//                        break;
//                    }
//                case ArgType::DOUBLE:
//                    {
//                        break;
//                    }
//                case ArgType::CHAR:
//                    {
//                        break;
//                    }
//                case ArgType::STRING:
//                    {
//                        break;
//                    }
//                default:
//                    {
//                        throw VMException("Wrong argument for MOV instruction");
//                    }
//            }
//
//            regx.field->Copy(regy);
//
		}
		void Clone::Execute(VirtualMachine& machine, Ovo::Code::Arg& arg1, Ovo::Code::Arg& arg2)
		{
			// Usage:       REGX, REGY  |   REGX, NAME
            // If Arg2 is a register, clones REGY onto REGX.
            // If Arg2 is a Name, searches in memory for a wrapper with that name and then clones it onto REGX by value. 
		}
		void New::Execute(VirtualMachine& machine, Ovo::Code::Arg& arg1, Ovo::Code::Arg& arg2)
		{
			// Usage:         REGX, ELEMENTARY
            // Allocates the elementary type onto memory and copies the wrapper to REGX.
		}
		void Movm::Execute(VirtualMachine& machine, Ovo::Code::Arg& arg1, Ovo::Code::Arg& arg2)
		{
			// Usage:        NAME
            // Searched in memory for a method wrapper with that name and then copy it onto the method register.
		}
		void Callm::Execute(VirtualMachine& machine, Ovo::Code::Arg& arg1, Ovo::Code::Arg& arg2)
		{
			// Usage:  
            // Invokes the method wrapper in REGM
		}
		void Pushar::Execute(VirtualMachine& machine, Ovo::Code::Arg& arg1, Ovo::Code::Arg& arg2)
		{
			// Usage:      REGX
            // Pushes REGX onto the Argument stack
		}
		void Popar::Execute(VirtualMachine& machine, Ovo::Code::Arg& arg1, Ovo::Code::Arg& arg2)
		{
			// Usage:    None   |   REGX
            // If Arg1 is None, pops the last element of the argument stack
            // If Arg1 is a register, pops the last element of the argument stack onto REGX
		}
		void Clrar::Execute(VirtualMachine& machine, Ovo::Code::Arg& arg1, Ovo::Code::Arg& arg2)
		{
			// Usage:    
            // Clears the argument stack
		}
		void Push::Execute(VirtualMachine& machine, Ovo::Code::Arg& arg1, Ovo::Code::Arg& arg2)
		{
			// Usage:        REGX    
            // Pushes REGX into the Stack
		}
		void Pop::Execute(VirtualMachine& machine, Ovo::Code::Arg& arg1, Ovo::Code::Arg& arg2)
		{
			// Usage:      NONE     |   REGX
            // If Arg1 is None, pops the last element of the stack
            // If Arg1 is a register, pops the last element of the stack onto REGX
		}
		void Clear::Execute(VirtualMachine& machine, Ovo::Code::Arg& arg1, Ovo::Code::Arg& arg2)
		{
			// Usage:    
            // Clears the stack
		}
		void Cmp::Execute(VirtualMachine& machine, Ovo::Code::Arg& arg1, Ovo::Code::Arg& arg2)
		{
			// Usage:         REGX
            // Casts REGX to bool and check if it's valid.
		}
		void Cmpeq::Execute(VirtualMachine& machine, Ovo::Code::Arg& arg1, Ovo::Code::Arg& arg2)
		{
			// Usage:       REGX, REGY  |   REGX, ELEMENTARY    |   REGX, NAME   
            // if Arg2 is a register, compares REGX == REGY and set it's truth-value onto regcmp.
            // If Arg2 is an elementary value, compares RegX == value and set it's truth-value onto regcmp.
            // If Arg2 is a name, searches the memory for that wrapper, comapres RegX == Wrapper and set it's truth-value onto regcmp.
		}
		void Cmpneq::Execute(VirtualMachine& machine, Ovo::Code::Arg& arg1, Ovo::Code::Arg& arg2)
		{
            // Usage:       REGX, REGY  |   REGX, ELEMENTARY    |   REGX, NAME   
            // if Arg2 is a register, compares REGX != REGY and set it's truth-value onto regcmp.
            // If Arg2 is an elementary value, compares RegX != value and set it's truth-value onto regcmp.
            // If Arg2 is a name, searches the memory for that wrapper, comapres RegX != Wrapper and set it's truth-value onto regcmp.

		}
		void Cmpls::Execute(VirtualMachine& machine, Ovo::Code::Arg& arg1, Ovo::Code::Arg& arg2)
		{
            // Usage:       REGX, REGY  |   REGX, ELEMENTARY    |   REGX, NAME   
            // if Arg2 is a register, compares REGX < REGY and set it's truth-value onto regcmp.
            // If Arg2 is an elementary value, compares RegX < value and set it's truth-value onto regcmp.
            // If Arg2 is a name, searches the memory for that wrapper, comapres RegX < Wrapper and set it's truth-value onto regcmp.


		}
		void Cmpgt::Execute(VirtualMachine& machine, Ovo::Code::Arg& arg1, Ovo::Code::Arg& arg2)
		{
            // Usage:       REGX, REGY  |   REGX, ELEMENTARY    |   REGX, NAME   
            // if Arg2 is a register, compares REGX > REGY and set it's truth-value onto regcmp.
            // If Arg2 is an elementary value, compares RegX > value and set it's truth-value onto regcmp.
            // If Arg2 is a name, searches the memory for that wrapper, comapres RegX > Wrapper and set it's truth-value onto regcmp.


		}
		void Cmplseq::Execute(VirtualMachine& machine, Ovo::Code::Arg& arg1, Ovo::Code::Arg& arg2)
		{
            // Usage:       REGX, REGY  |   REGX, ELEMENTARY    |   REGX, NAME   
            // if Arg2 is a register, compares REGX <= REGY and set it's truth-value onto regcmp.
            // If Arg2 is an elementary value, compares RegX <= value and set it's truth-value onto regcmp.
            // If Arg2 is a name, searches the memory for that wrapper, comapres RegX <= Wrapper and set it's truth-value onto regcmp.
		}
		void Cmpgteq::Execute(VirtualMachine& machine, Ovo::Code::Arg& arg1, Ovo::Code::Arg& arg2)
		{
            // Usage:       REGX, REGY  |   REGX, ELEMENTARY    |   REGX, NAME   
            // if Arg2 is a register, compares REGX >= REGY and set it's truth-value onto regcmp.
            // If Arg2 is an elementary value, compares RegX >= value and set it's truth-value onto regcmp.
            // If Arg2 is a name, searches the memory for that wrapper, comapres RegX >= Wrapper and set it's truth-value onto regcmp.
		}
		void Jntrue::Execute(VirtualMachine& machine, Ovo::Code::Arg& arg1, Ovo::Code::Arg& arg2)
		{
			// Usage:      REGX        |   UINT
            // If Arg1 is a register, cast it's value to uint and jumps to that position if regcmp is true
            // If Arg1 is an uint, jump to that value if regcmp is true
		}
		void Jnfalse::Execute(VirtualMachine& machine, Ovo::Code::Arg& arg1, Ovo::Code::Arg& arg2)
		{
			// Usage:     REGX        |   UINT
            // If Arg1 is a register, cast it's value to uint and jumps to that position if regcmp is false
            // If Arg1 is an uint, jump to that value if regcmp is false
		}
		void Jmp::Execute(VirtualMachine& machine, Ovo::Code::Arg& arg1, Ovo::Code::Arg& arg2)
		{
			// Usage:         REGX        |   UINT
            // If Arg1 is a register, cast it's value to uint and jumps to that position
            // If Arg1 is an uint, jump to that value
		}
		void Call::Execute(VirtualMachine& machine, Ovo::Code::Arg& arg1, Ovo::Code::Arg& arg2)
		{
			// Usage:        REGX        |   UINT
            // Copies the position of ip onto the stack
            // If Arg1 is a register, cast it's value to uint and jumps to that position
            // If Arg1 is an uint, jump to that value
		}
		void Ret::Execute(VirtualMachine& machine, Ovo::Code::Arg& arg1, Ovo::Code::Arg& arg2)
		{
			// Usage: 
            // Pops the stack onto the position of ip.
		}
		void Add::Execute(VirtualMachine& machine, Ovo::Code::Arg& arg1, Ovo::Code::Arg& arg2)
		{
			// Usage:         REGX, REGY  |   REGX, ELEMENTARY    |   REGX, NAME
            // If Arg2 is a register, does REGX += REGY
            // If Arg2 is an elementary value, does REGX += value
            // If Arg2 is a name, search the memory for that wrapper and do REGX += Wrapper
		}
		void Sub::Execute(VirtualMachine& machine, Ovo::Code::Arg& arg1, Ovo::Code::Arg& arg2)
		{
			// Usage:         REGX, REGY  |   REGX, ELEMENTARY    |   REGX, NAME
            // If Arg2 is a register, does REGX -= REGY
            // If Arg2 is an elementary value, does REGX -= value
            // If Arg2 is a name, search the memory for that wrapper and do REGX -= Wrapper
		}
		void Mul::Execute(VirtualMachine& machine, Ovo::Code::Arg& arg1, Ovo::Code::Arg& arg2)
		{
			// Usage:         REGX, REGY  |   REGX, ELEMENTARY    |   REGX, NAME
            // If Arg2 is a register, does REGX *= REGY
            // If Arg2 is an elementary value, does REGX *= value
            // If Arg2 is a name, search the memory for that wrapper and do REGX *= Wrapper
		}
		void Div::Execute(VirtualMachine& machine, Ovo::Code::Arg& arg1, Ovo::Code::Arg& arg2)
		{
			// Usage:         REGX, REGY  |   REGX, ELEMENTARY    |   REGX, NAME
            // If Arg2 is a register, does REGX /= REGY
            // If Arg2 is an elementary value, does REGX /= value
            // If Arg2 is a name, search the memory for that wrapper and do REGX /= Wrapper
		}
		void Mod::Execute(VirtualMachine& machine, Ovo::Code::Arg& arg1, Ovo::Code::Arg& arg2)
		{
			// Usage:         REGX, REGY  |   REGX, ELEMENTARY    |   REGX, NAME
            // If Arg2 is a register, does REGX %= REGY
            // If Arg2 is an elementary value, does REGX %= value
            // If Arg2 is a name, search the memory for that wrapper and do REGX %= Wrapper
		}
		void And::Execute(VirtualMachine& machine, Ovo::Code::Arg& arg1, Ovo::Code::Arg& arg2)
		{
			// Usage:         REGX, REGY  |   REGX, ELEMENTARY    |   REGX, NAME
            // If Arg2 is a register, does REGX &&= REGY
            // If Arg2 is an elementary value, does REGX &&= value
            // If Arg2 is a name, search the memory for that wrapper and do REGX &&= Wrapper
		}
		void Or::Execute(VirtualMachine& machine, Ovo::Code::Arg& arg1, Ovo::Code::Arg& arg2)
		{
			// Usage:          REGX, REGY  |   REGX, ELEMENTARY    |   REGX, NAME
            // If Arg2 is a register, does REGX ||= REGY
            // If Arg2 is an elementary value, does REGX ||= value
            // If Arg2 is a name, search the memory for that wrapper and do REGX ||= Wrapper
		}
		void Cast::Execute(VirtualMachine& machine, Ovo::Code::Arg& arg1, Ovo::Code::Arg& arg2)
		{
			// Usage:        REGX, REGY  |   REGX, TYPE          |   REGX, NAME
            // If Arg2 is a register, casts REGX to the type of REGY
            // If Arg2 is a type, casts REGX to that type
            // If Arg2 is a name, search the memory for that wrapper and casts REGX to the type of that wrapper
		}
		void Name::Execute(VirtualMachine& machine, Ovo::Code::Arg& arg1, Ovo::Code::Arg& arg2)
		{
			// Usage:        REGX, STRING 
            // Copies RegX to the memory under the name in Arg2
		}
		void Nameg::Execute(VirtualMachine& machine, Ovo::Code::Arg& arg1, Ovo::Code::Arg& arg2)
		{
			// Usage:       REGX, STRING
            // Copies RegX to the global memory under the name in Arg2
		}
		void Brup::Execute(VirtualMachine& machine, Ovo::Code::Arg& arg1, Ovo::Code::Arg& arg2)
		{
			// Usage: 
            // Branches UP
		}
		void Brdw::Execute(VirtualMachine& machine, Ovo::Code::Arg& arg1, Ovo::Code::Arg& arg2)
		{
			// Usage:     
            // Branches DOWN
		}
		void Brhz::Execute(VirtualMachine& machine, Ovo::Code::Arg& arg1, Ovo::Code::Arg& arg2)
		{
			// Usage:        STRING    
            // Branches horizontally to the memory under the name in Arg1
		}
		void Rsbr::Execute(VirtualMachine& machine, Ovo::Code::Arg& arg1, Ovo::Code::Arg& arg2)
		{
			// Usage: 
            // Resets Branching.
		}
		void Zero::Execute(VirtualMachine& machine, Ovo::Code::Arg& arg1, Ovo::Code::Arg& arg2)
		{
			// Usage:     
            // Does nothing.
		}
		void Halt::Execute(VirtualMachine& machine, Ovo::Code::Arg& arg1, Ovo::Code::Arg& arg2)
		{
			// Usage:     
            // Stops the machine.
		}

        // Instruction Code End:

#pragma GCC diagnostic pop
    }
}
