#pragma once

#include "../Core/Core.h"
#include <string>
#include <cstring>

namespace Yolk {
    namespace VM {
        class VirtualMachine;
        
        struct VMException : public Yolk::Exceptions::Exception
        {
            private:
                std::string message;
            public:
                VMException(std::string m = "VM exception thrown.") : Yolk::Exceptions::Exception(m), message(m) {}
            virtual const char* what() const throw() {
                return message.c_str();
            }
        };

        void AssertCondition(int, std::string message = "");

        template<typename T, typename F>
        inline T Bitcast(F& f)
        {
            T t;
            std::memcpy((void*)&t, (void*)&f, sizeof(T));
            return t;
        }
        template<typename T, typename F>
        inline T Bitcast(F&& ff)
        {
            T t;
            F f = ff;
            std::memcpy((void*)&t, (void*)&f, sizeof(T));
            return t;
        }
        struct Instruction {
            const static Instruction* Select(const OPCode op);
            virtual ~Instruction() {}
            virtual std::string to_string() const {return "NON-IMPLEMENTED INSTRUCTION";};
			virtual void Execute(VirtualMachine&, Ovo::Code::Arg& , Ovo::Code::Arg& ) const { throw VMException("Called non-implemented instruction.");}
        };
    	struct Mov final : public Instruction {
			inline std::string to_string() const {return "MOV";};
			void Execute(VirtualMachine&, Ovo::Code::Arg& arg1, Ovo::Code::Arg& arg2) const;
			// NEW METHODS...
		};
		struct Copy final : public Instruction {
			inline std::string to_string() const {return "COPY";};
			void Execute(VirtualMachine&, Ovo::Code::Arg& arg1, Ovo::Code::Arg& arg2) const;
			// NEW METHODS...
		};
		struct Clone final : public Instruction {
			inline std::string to_string() const {return "CLONE";};
			void Execute(VirtualMachine&, Ovo::Code::Arg& arg1, Ovo::Code::Arg& arg2) const;
			// NEW METHODS...
		};
		struct New final : public Instruction {
			inline std::string to_string() const {return "NEW";};
			void Execute(VirtualMachine&, Ovo::Code::Arg& arg1, Ovo::Code::Arg& arg2) const;
			// NEW METHODS...
		};
		struct Movm final : public Instruction {
			inline std::string to_string() const {return "MOVM";};
			void Execute(VirtualMachine&, Ovo::Code::Arg& arg1, Ovo::Code::Arg& arg2) const;
			// NEW METHODS...
		};
		struct Callm final : public Instruction {
			inline std::string to_string() const {return "CALLM";};
			void Execute(VirtualMachine&, Ovo::Code::Arg& arg1, Ovo::Code::Arg& arg2) const;
			// NEW METHODS...
		};
		struct Pushar final : public Instruction {
			inline std::string to_string() const {return "PUSHAR";};
			void Execute(VirtualMachine&, Ovo::Code::Arg& arg1, Ovo::Code::Arg& arg2) const;
			// NEW METHODS...
		};
		struct Popar final : public Instruction {
			inline std::string to_string() const {return "POPAR";};
			void Execute(VirtualMachine&, Ovo::Code::Arg& arg1, Ovo::Code::Arg& arg2) const;
			// NEW METHODS...
		};
		struct Clrar final : public Instruction {
			inline std::string to_string() const {return "CLRAR";};
			void Execute(VirtualMachine&, Ovo::Code::Arg& arg1, Ovo::Code::Arg& arg2) const;
			// NEW METHODS...
		};
		struct Push final : public Instruction {
			inline std::string to_string() const {return "PUSH";};
			void Execute(VirtualMachine&, Ovo::Code::Arg& arg1, Ovo::Code::Arg& arg2) const;
			// NEW METHODS...
		};
		struct Pop final : public Instruction {
			inline std::string to_string() const {return "POP";};
			void Execute(VirtualMachine&, Ovo::Code::Arg& arg1, Ovo::Code::Arg& arg2) const;
			// NEW METHODS...
		};
		struct Clear final : public Instruction {
			inline std::string to_string() const {return "CLEAR";};
			void Execute(VirtualMachine&, Ovo::Code::Arg& arg1, Ovo::Code::Arg& arg2) const;
			// NEW METHODS...
		};
		struct Cmp final : public Instruction {
			inline std::string to_string() const {return "CMP";};
			void Execute(VirtualMachine&, Ovo::Code::Arg& arg1, Ovo::Code::Arg& arg2) const;
			// NEW METHODS...
		};
		struct Cmpeq final : public Instruction {
			inline std::string to_string() const {return "CMPEQ";};
			void Execute(VirtualMachine&, Ovo::Code::Arg& arg1, Ovo::Code::Arg& arg2) const;
			// NEW METHODS...
		};
		struct Cmpneq final : public Instruction {
			inline std::string to_string() const {return "CMPNEQ";};
			void Execute(VirtualMachine&, Ovo::Code::Arg& arg1, Ovo::Code::Arg& arg2) const;
			// NEW METHODS...
		};
		struct Cmpls final : public Instruction {
			inline std::string to_string() const {return "CMPLS";};
			void Execute(VirtualMachine&, Ovo::Code::Arg& arg1, Ovo::Code::Arg& arg2) const;
			// NEW METHODS...
		};
		struct Cmpgt final : public Instruction {
			inline std::string to_string() const {return "CMPGT";};
			void Execute(VirtualMachine&, Ovo::Code::Arg& arg1, Ovo::Code::Arg& arg2) const;
			// NEW METHODS...
		};
		struct Cmplseq final : public Instruction {
			inline std::string to_string() const {return "CMPLSEQ";};
			void Execute(VirtualMachine&, Ovo::Code::Arg& arg1, Ovo::Code::Arg& arg2) const;
			// NEW METHODS...
		};
		struct Cmpgteq final : public Instruction {
			inline std::string to_string() const {return "CMPGTEQ";};
			void Execute(VirtualMachine&, Ovo::Code::Arg& arg1, Ovo::Code::Arg& arg2) const;
			// NEW METHODS...
		};
		struct Jntrue final : public Instruction {
			inline std::string to_string() const {return "JNTRUE";};
			void Execute(VirtualMachine&, Ovo::Code::Arg& arg1, Ovo::Code::Arg& arg2) const;
			// NEW METHODS...
		};
		struct Jnfalse final : public Instruction {
			inline std::string to_string() const {return "JNFALSE";};
			void Execute(VirtualMachine&, Ovo::Code::Arg& arg1, Ovo::Code::Arg& arg2) const;
			// NEW METHODS...
		};
		struct Jmp final : public Instruction {
			inline std::string to_string() const {return "JMP";};
			void Execute(VirtualMachine&, Ovo::Code::Arg& arg1, Ovo::Code::Arg& arg2) const;
			// NEW METHODS...
		};
		struct Call final : public Instruction {
			inline std::string to_string() const {return "CALL";};
			void Execute(VirtualMachine&, Ovo::Code::Arg& arg1, Ovo::Code::Arg& arg2) const;
			// NEW METHODS...
		};
		struct Ret final : public Instruction {
			inline std::string to_string() const {return "RET";};
			void Execute(VirtualMachine&, Ovo::Code::Arg& arg1, Ovo::Code::Arg& arg2) const;
			// NEW METHODS...
		};
		struct Add final : public Instruction {
			inline std::string to_string() const {return "ADD";};
			void Execute(VirtualMachine&, Ovo::Code::Arg& arg1, Ovo::Code::Arg& arg2) const;
			// NEW METHODS...
		};
		struct Sub final : public Instruction {
			inline std::string to_string() const {return "SUB";};
			void Execute(VirtualMachine&, Ovo::Code::Arg& arg1, Ovo::Code::Arg& arg2) const;
			// NEW METHODS...
		};
		struct Mul final : public Instruction {
			inline std::string to_string() const {return "MUL";};
			void Execute(VirtualMachine&, Ovo::Code::Arg& arg1, Ovo::Code::Arg& arg2) const;
			// NEW METHODS...
		};
		struct Div final : public Instruction {
			inline std::string to_string() const {return "DIV";};
			void Execute(VirtualMachine&, Ovo::Code::Arg& arg1, Ovo::Code::Arg& arg2) const;
			// NEW METHODS...
		};
		struct Mod final : public Instruction {
			inline std::string to_string() const {return "MOD";};
			void Execute(VirtualMachine&, Ovo::Code::Arg& arg1, Ovo::Code::Arg& arg2) const;
			// NEW METHODS...
		};
		struct And final : public Instruction {
			inline std::string to_string() const {return "AND";};
			void Execute(VirtualMachine&, Ovo::Code::Arg& arg1, Ovo::Code::Arg& arg2) const;
			// NEW METHODS...
		};
		struct Or final : public Instruction {
			inline std::string to_string() const {return "OR";};
			void Execute(VirtualMachine&, Ovo::Code::Arg& arg1, Ovo::Code::Arg& arg2) const;
			// NEW METHODS...
		};
		struct Cast final : public Instruction {
			inline std::string to_string() const {return "CAST";};
			void Execute(VirtualMachine&, Ovo::Code::Arg& arg1, Ovo::Code::Arg& arg2) const;
			// NEW METHODS...
		};
		struct Name final : public Instruction {
			inline std::string to_string() const {return "NAME";};
			void Execute(VirtualMachine&, Ovo::Code::Arg& arg1, Ovo::Code::Arg& arg2) const;
			// NEW METHODS...
		};
		struct Nameg final : public Instruction {
			inline std::string to_string() const {return "NAMEG";};
			void Execute(VirtualMachine&, Ovo::Code::Arg& arg1, Ovo::Code::Arg& arg2) const;
			// NEW METHODS...
		};
		struct Brup final : public Instruction {
			inline std::string to_string() const {return "BRUP";};
			void Execute(VirtualMachine&, Ovo::Code::Arg& arg1, Ovo::Code::Arg& arg2) const;
			// NEW METHODS...
		};
		struct Brdw final : public Instruction {
			inline std::string to_string() const {return "BRDW";};
			void Execute(VirtualMachine&, Ovo::Code::Arg& arg1, Ovo::Code::Arg& arg2) const;
			// NEW METHODS...
		};
		struct Brhz final : public Instruction {
			inline std::string to_string() const {return "BRHZ";};
			void Execute(VirtualMachine&, Ovo::Code::Arg& arg1, Ovo::Code::Arg& arg2) const;
			// NEW METHODS...
		};
		struct Rsbr final : public Instruction {
			inline std::string to_string() const {return "RSBR";};
			void Execute(VirtualMachine&, Ovo::Code::Arg& arg1, Ovo::Code::Arg& arg2) const;
			// NEW METHODS...
		};
		struct Zero final : public Instruction {
			inline std::string to_string() const {return "ZERO";};
			void Execute(VirtualMachine&, Ovo::Code::Arg& arg1, Ovo::Code::Arg& arg2) const;
			// NEW METHODS...
		};
		struct Halt final : public Instruction {
			inline std::string to_string() const {return "HALT";};
			void Execute(VirtualMachine&, Ovo::Code::Arg& arg1, Ovo::Code::Arg& arg2) const;
			// NEW METHODS...
		};
    }
}
