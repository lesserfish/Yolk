#include "YVM.h"
#include <chrono>

namespace Yolk
{
    namespace VM
    {
        YVM::YVM(Memory::MemoryManager &_manager, Memory::WrapperTable &_wrapperTable) : manager(_manager),
                                                                                         wrapperTable(_wrapperTable),
                                                                                         opHandler(manager),
                                                                                         rega(manager.GenerateVoidWrapper()),
                                                                                         regb(manager.GenerateVoidWrapper()),
                                                                                         regc(manager.GenerateVoidWrapper()),
                                                                                         regd(manager.GenerateVoidWrapper()),
                                                                                         regout(manager.GenerateVoidWrapper()),
                                                                                         mreg(manager.GenerateVoidWrapper()),
                                                                                         cmpreg(false),
                                                                                         argreg(),
                                                                                         instructionPointer({})
        {
        }

        // API

        void YVM::SetUp(OVO _ovo, Memory::SymbolTable& _symTable)
        {
            ovo = _ovo;
            symTable = &_symTable;
            instructionPointer = ovo.InstructionSet.begin();
        }
        void YVM::SetSymTable(Memory::SymbolTable& _symTable)
        {
            symTable = &_symTable;
        }
        void YVM::SetOvo(OVO _ovo)
        {
            ovo = _ovo;
            instructionPointer = ovo.InstructionSet.begin();
        }
        void YVM::Tick()
        {
            if(instructionPointer == ovo.InstructionSet.end())
                return;
            clock++;

            auto current_instruction = instructionPointer;
            instructionPointer++;

            HandleInstruction(*current_instruction);
        }
        void YVM::Run()
        {
            Running = true;
            status = Status::RUNNING;
            Message = "Started!";
            clock = 0;

            JumpToInstruction(0);

            while(Running)
            {
                clock++;
                
                auto current_instruction = instructionPointer;
                instructionPointer++;

                HandleInstruction(*current_instruction);

                if(instructionPointer == ovo.InstructionSet.end() && Running)
                {
                    Running = false;
                    instructionPointer = ovo.InstructionSet.end();
                    status = Status::HALTED;
                    Message = "Instruction pointer left valid scope!";
                    break;
                }

            }
            return;
        }
        void YVM::Run(OVO _ovo, Memory::SymbolTable& _symTable)
        {
            ovo = _ovo;
            symTable = &_symTable;
            workingSymTable = &_symTable;
            instructionPointer = ovo.InstructionSet.begin();

            Running = true;
            status = Status::RUNNING;
            Message = "Started!";
            clock = 0;

//            std::chrono::steady_clock Clock;

            JumpToInstruction(0);

            while(Running)
            {
                clock++;

                auto current_instruction = instructionPointer;
                instructionPointer++;
            
                HandleInstruction(*current_instruction);

                if(instructionPointer == ovo.InstructionSet.end() && Running)
                {
                    Running = false;
                    instructionPointer = ovo.InstructionSet.end();
                    status = Status::HALTED;
                    Message = "Instruction pointer left valid scope!";
                    break;
                }
            }

            //Debug();
            return;
        }

        Operator& YVM::GetOpHandler()
        {
            return opHandler;
        }
        YVM::Status YVM::GetStatus() const
        {
            return status;
        }
        std::string YVM::GetMessage() const
        {
            return Message;
        }
        unsigned long int YVM::GetException() const
        {
            return exceptionStatus;
        }
        unsigned long int YVM::GetClock() const
        {
            return clock;
        }
        // Helper Functions
        void YVM::HandleInstruction(OVO::Instruction instruction)
        {
            const int exception_shift = 0x0;
            switch(instruction.instruction)
            {
                case OVO::Instruction::INSTRUCTION::MOV: 
                {
                    return I_MOV(instruction.arg1, instruction.arg2);
                }
                case OVO::Instruction::INSTRUCTION::CLONE: 
                {
                    return I_CLONE(instruction.arg1, instruction.arg2);
                }
                case OVO::Instruction::INSTRUCTION::NEW:
                {
                    return I_NEW(instruction.arg1, instruction.arg2);
                }
                case OVO::Instruction::INSTRUCTION::MOVM: 
                {
                    return I_MOVM(instruction.arg1);
                } 
                case OVO::Instruction::INSTRUCTION::CALLM: 
                {
                    return I_CALLM();
                }
                case OVO::Instruction::INSTRUCTION::PUSHAR: 
                {
                    return I_PUSHAR(instruction.arg1);
                }
                case OVO::Instruction::INSTRUCTION::POPAR: 
                {
                    return I_POPAR(instruction.arg1);
                }
                case OVO::Instruction::INSTRUCTION::CLRAR: 
                {
                    return I_CLRAR();
                }
                case OVO::Instruction::INSTRUCTION::PUSH: 
                {
                    return I_PUSH(instruction.arg1);
                }
                case OVO::Instruction::INSTRUCTION::POP: 
                {
                    return I_POP(instruction.arg1);
                }
                case OVO::Instruction::INSTRUCTION::CLEAR: 
                {
                    return I_CLEAR();
                }
                case OVO::Instruction::INSTRUCTION::CMP: 
                {
                    return I_CMP(instruction.arg1);
                }
                case OVO::Instruction::INSTRUCTION::CMPEQ: 
                {
                    return I_CMPEQ(instruction.arg1, instruction.arg2);
                }
                case OVO::Instruction::INSTRUCTION::CMPNEQ: 
                {
                    return I_CMPNEQ(instruction.arg1, instruction.arg2);
                }
                case OVO::Instruction::INSTRUCTION::CMPLS: 
                {
                    return I_CMPLS(instruction.arg1, instruction.arg2);
                } 
                case OVO::Instruction::INSTRUCTION::CMPGT: 
                {
                    return I_CMPGT(instruction.arg1, instruction.arg2);
                } 
                case OVO::Instruction::INSTRUCTION::CMPLSEQ: 
                {
                    return I_CMPLSEQ(instruction.arg1, instruction.arg2);
                }
                case OVO::Instruction::INSTRUCTION::CMPGTEQ: 
                {
                    return I_CMPGTEQ(instruction.arg1, instruction.arg2);
                }
                case OVO::Instruction::INSTRUCTION::JNTRUE: 
                {
                    return I_JNTRUE(instruction.arg1);
                }
                case OVO::Instruction::INSTRUCTION::JNFALSE: 
                {
                    return I_JNFALSE(instruction.arg1);
                }
                case OVO::Instruction::INSTRUCTION::JMP: 
                {
                    return I_JMP(instruction.arg1);
                }
                case OVO::Instruction::INSTRUCTION::CALL: 
                {
                    return I_CALL(instruction.arg1);
                }
                case OVO::Instruction::INSTRUCTION::RET: 
                {
                    return I_RET();
                }
                case OVO::Instruction::INSTRUCTION::ADD: 
                {
                    return I_ADD(instruction.arg1, instruction.arg2);
                }
                case OVO::Instruction::INSTRUCTION::SUB: 
                {
                    return I_SUB(instruction.arg1, instruction.arg2);
                } 
                case OVO::Instruction::INSTRUCTION::MUL: 
                {
                    return I_MUL(instruction.arg1, instruction.arg2);
                }
                case OVO::Instruction::INSTRUCTION::DIV: 
                {
                    return I_DIV(instruction.arg1, instruction.arg2);
                }
                case OVO::Instruction::INSTRUCTION::MOD: 
                {
                    return I_MOD(instruction.arg1, instruction.arg2);
                }
                case OVO::Instruction::INSTRUCTION::AND: 
                {
                    return I_AND(instruction.arg1, instruction.arg2);
                }
                case OVO::Instruction::INSTRUCTION::OR: 
                {
                    return I_OR(instruction.arg1, instruction.arg2);
                }
                case OVO::Instruction::INSTRUCTION::CAST: 
                {
                    return I_CAST(instruction.arg1, instruction.arg2);
                }
                case OVO::Instruction::INSTRUCTION::COPY: 
                {
                    return I_COPY(instruction.arg1, instruction.arg2);
                }
                case OVO::Instruction::INSTRUCTION::NAMEL: 
                {
                    return I_NAMEL(instruction.arg1, instruction.arg2);
                }
                case OVO::Instruction::INSTRUCTION::NAMEG: 
                {
                    return I_NAMEG(instruction.arg1, instruction.arg2);
                }
                case OVO::Instruction::INSTRUCTION::BRUP: 
                {
                    return I_BRUP();
                }
                case OVO::Instruction::INSTRUCTION::BRDW:
                {
                    return I_BRDW();
                }
                case OVO::Instruction::INSTRUCTION::BRHZ: 
                {
                    return I_BRHR(instruction.arg1);
                }
                case OVO::Instruction::INSTRUCTION::RSBR:
                {
                    return I_RSBR();
                }
                case OVO::Instruction::INSTRUCTION::ZERO: 
                {
                    return I_ZERO();
                }
                case OVO::Instruction::INSTRUCTION::HALT: 
                {
                    return I_HALT();
                }
                default:
                    return ThrowException(exception_shift + 0x1, "Unknown instruction!");
            }
        }
        bool YVM::SelectRegister(OVO::Instruction::CHUNK chunk, Wrapper *&ref)
        {
            switch (chunk)
            {
            case 0x0:
                ref = &rega;
                return true;
            case 0x1:
                ref = &regb;
                return true;
            case 0x2:
                ref = &regc;
                return true;
            case 0x3:
                ref = &regd;
                return true;
            case 0x4:
                ref = &regout;
                return true;
            default:
                return false;
            }
        }
        bool YVM::ValidInstruction(OVO::Usize position)
        {
            if(position >= ovo.InstructionSet.size()){
                return false;
            }

            return true;
        }
        void YVM::JumpToInstruction(OVO::Usize position)
        {
            if(!ValidInstruction(position))
            {
                Running = false;
                instructionPointer = ovo.InstructionSet.end();
                status = Status::HALTED;
                Message = "Instruction pointer left valid scope!";
                return;
            }
            instructionPointer = ovo.InstructionSet.begin() + position;
        }
        OVO::Usize YVM::CurrentInstruction()
        {
            OVO::Usize position = instructionPointer - ovo.InstructionSet.begin();
            return position;
        }
        void YVM::ThrowException(int exception_status, std::string _Message)
        {
            std::string exception =  "Exception Thrown (" + std::to_string(exception_status) + "): " + _Message + ".";
            Running = false;
            status = Status::ERROR;
            exceptionStatus = exception_status;
            Message = exception;
        }
        YVM::DataOutput YVM::RetrieveData(OVO::Instruction::CHUNK position)
        {
            DataOutput out;

            if(position >= ovo.DataSet.size())
            {
                return DataOutput {OVO::Data(), false};
            }
            out.ok = true;
            out.data = ovo.DataSet.at(position);
            return out;
        }
        void YVM::PrintOVO()
        {
            for(auto i : ovo.InstructionSet)
            {
                PrintInstruction(i);
            }
        }
        void YVM::PrintInstruction(OVO::Instruction instruction)
        {

        std::string out = GetInstructionName(instruction.instruction) + "  " + 
                            GetValue(instruction.arg1.mode, instruction.arg1.value) +  " , " +
                            GetValue(instruction.arg2.mode, instruction.arg2.value);  

            std::cout << "\t\t" << out << std::endl;   
        }
        std::string YVM::GetInstructionName(OVO::Instruction::INSTRUCTION i)
        {
            switch(i)
            {
                case OVO::Instruction::INSTRUCTION::MOV: 
                {
                    return "I_MOV";
                }
                case OVO::Instruction::INSTRUCTION::CLONE: 
                {
                    return "I_CLONE";
                }
                case OVO::Instruction::INSTRUCTION::MOVM: 
                {
                    return "I_MOVM";
                } 
                case OVO::Instruction::INSTRUCTION::CALLM: 
                {
                    return "I_CALLM";
                }
                case OVO::Instruction::INSTRUCTION::PUSHAR: 
                {
                    return "I_PUSHAR";
                }
                case OVO::Instruction::INSTRUCTION::POPAR: 
                {
                    return "I_POPAR";
                }
                case OVO::Instruction::INSTRUCTION::CLRAR: 
                {
                    return "I_CLRAR";
                }
                case OVO::Instruction::INSTRUCTION::PUSH: 
                {
                    return "I_PUSH";
                }
                case OVO::Instruction::INSTRUCTION::POP: 
                {
                    return "I_POP";
                }
                case OVO::Instruction::INSTRUCTION::CLEAR: 
                {
                    return "I_CLEAR";
                }
                case OVO::Instruction::INSTRUCTION::CMP: 
                {
                    return "I_CMP";
                }
                case OVO::Instruction::INSTRUCTION::CMPEQ: 
                {
                    return "I_CMPEQ";
                }
                case OVO::Instruction::INSTRUCTION::CMPNEQ: 
                {
                    return "I_CMPNEQ";
                }
                case OVO::Instruction::INSTRUCTION::CMPLS: 
                {
                    return "I_CMPLS";
                } 
                case OVO::Instruction::INSTRUCTION::CMPGT: 
                {
                    return "I_CMPGT";
                } 
                case OVO::Instruction::INSTRUCTION::CMPLSEQ: 
                {
                    return "I_CMPLSEQ";
                }
                case OVO::Instruction::INSTRUCTION::CMPGTEQ: 
                {
                    return "I_CMPGTEQ";
                }
                case OVO::Instruction::INSTRUCTION::JNTRUE: 
                {
                    return "I_JNTRUE";
                }
                case OVO::Instruction::INSTRUCTION::JNFALSE: 
                {
                    return "I_JNFALSE";
                }
                case OVO::Instruction::INSTRUCTION::JMP: 
                {
                    return "I_JMP";
                }
                case OVO::Instruction::INSTRUCTION::CALL: 
                {
                    return "I_CALL";
                }
                case OVO::Instruction::INSTRUCTION::RET: 
                {
                    return "I_RET";
                }
                case OVO::Instruction::INSTRUCTION::ADD: 
                {
                    return "I_ADD";
                }
                case OVO::Instruction::INSTRUCTION::SUB: 
                {
                    return "I_SUB";
                } 
                case OVO::Instruction::INSTRUCTION::MUL: 
                {
                    return "I_MUL";
                }
                case OVO::Instruction::INSTRUCTION::DIV: 
                {
                    return "I_DIV";
                }
                case OVO::Instruction::INSTRUCTION::MOD: 
                {
                    return "I_MOD";
                }
                case OVO::Instruction::INSTRUCTION::AND: 
                {
                    return "I_AND";
                }
                case OVO::Instruction::INSTRUCTION::OR: 
                {
                    return "I_OR";
                }
                case OVO::Instruction::INSTRUCTION::CAST: 
                {
                    return "I_CAST";
                }
                case OVO::Instruction::INSTRUCTION::COPY: 
                {
                    return "I_COPY";
                }
                case OVO::Instruction::INSTRUCTION::NAMEL: 
                {
                    return "I_NAMEL";
                }
                case OVO::Instruction::INSTRUCTION::NAMEG: 
                {
                    return "I_NAMEG";
                }
                case OVO::Instruction::INSTRUCTION::BRUP: 
                {
                    return "I_BRUP";
                }
                case OVO::Instruction::INSTRUCTION::BRDW:
                {
                    return "I_BRDW";
                }
                case OVO::Instruction::INSTRUCTION::BRHZ: 
                {
                    return "I_BRHR";
                }
                case OVO::Instruction::INSTRUCTION::RSBR:
                {
                    return "I_RSBR";
                }
                case OVO::Instruction::INSTRUCTION::ZERO: 
                {
                    return "I_ZERO";
                }
                case OVO::Instruction::INSTRUCTION::HALT: 
                {
                    return "I_HALT";
                }
                case OVO::Instruction::INSTRUCTION::NEW:
                {
                    return "I_NEW";
                }
                default:
                {
                    return "UNKNOWN";
                }
                }
        }
        std::string YVM::GetValue(OVO::Instruction::ARG::MODE s, OVO::Instruction::CHUNK chunk)
        {
                switch(s)
                {
                    case OVO::Instruction::ARG::MODE::SYMBOL:
                    {
                        return std::to_string(chunk);
                    }
                    case OVO::Instruction::ARG::MODE::REG:
                    {
                        return std::to_string(chunk);
                    }
                    case OVO::Instruction::ARG::MODE::DATA:
                    {
                        auto d = RetrieveData(chunk);
                        if(!d.ok)
                            return "[None]";
                        Wrapper w = OVO::Data::ToWrapper(d.data, manager);
                        return w.field->Print();
                    }
                    default:
                    {
                        return "";
                    }
                }
        }
        void YVM::Debug()
        {
            std::cout << "REGA: " << rega.field->Print() << std::endl;
            std::cout << "REGB: " << regb.field->Print() << std::endl;
            std::cout << "REGC: " << regc.field->Print() << std::endl;
            std::cout << "REGD: " << regd.field->Print() << std::endl;
            std::cout << "MREG: ";
            std::cout << mreg.GetOutType().name() << "( ";
            for (auto i : mreg.GetInType())
                std::cout << i.name() << " ";
            std::cout << ")\n";
            std::cout << "ARGREG: [";
            for (auto i : argreg)
                std::cout << i.field->Print() << " ";
            std::cout << "]\n";
            std::cout << "CMPREG: " << (cmpreg ? "TRUE" : "FALSE") << std::endl;
        }

        // API Functions

        // Instructions

        void YVM::I_MOV(OVO::Instruction::ARG arg1, OVO::Instruction::ARG arg2)
        {
            // Usage
            // 1. MOV REGX, REGY
            // 2. MOV REX, data   where data contains an std::string with the name of a variable
            const int exception_shift = 1;

            Wrapper *regx;

            if (arg1.mode != OVO::Instruction::ARG::MODE::REG)
                return ThrowException(exception_shift + 0, "MOV arguments do not fit standard!");

            bool selection = SelectRegister(arg1.value, regx);
            if (!selection)
                return ThrowException(exception_shift + 1, "MOV arguments do not fit standard! Current value is: " + std::to_string(arg1.value) + ".");

            switch (arg2.mode)
            {
            case OVO::Instruction::ARG::MODE::REG:
            {
                Wrapper *regy;

                selection = SelectRegister(arg2.value, regy);
                if (!selection)
                    return ThrowException(exception_shift + 2, "MOV arguments do not find standard!");

                *regx = *regy;

                return;
            }
            case OVO::Instruction::ARG::MODE::DATA:
            {
                auto result = RetrieveData(arg2.value);
                if (!result.ok)
                    return ThrowException(exception_shift + 3, "DATA could not be found!");
                OVO::Data data = result.data;
                if (data.mode != OVO::Data::Mode::STRING)
                    return ThrowException(exception_shift + 4, "MOV arguments do not fit standard!");

                std::string wrapperName = data.ToWrapper(data, manager).field->As<std::string>();

                auto symbol_result = workingSymTable->Get(Yolk::Memory::SymbolKey(wrapperName));

                if (!symbol_result.ok)
                    return ThrowException(exception_shift + 5, "Could not find variable named \"" + wrapperName + "\".");

                auto wrapper_info = wrapperTable.GetInfo(symbol_result.value.key);

                if (!wrapper_info.alive)
                    return ThrowException(exception_shift + 6, "Could not find variable named \"" + wrapperName + "\". It has already been deleted.");
                if (wrapper_info.wrapperType != WrapperType::FieldWrapper)
                    return ThrowException(exception_shift + 7, "Wrapper named \"" + wrapperName + "\" is a not field!");

                *regx = wrapperTable.CopyField(symbol_result.value.key);

                return;
            }
            default:
            {
                return ThrowException(exception_shift + 8, "MOV arguments do not fit standard!");
            }
            }
        }
        void YVM::I_COPY(OVO::Instruction::ARG arg1, OVO::Instruction::ARG arg2)
        {
            // Usage:
            // 1. COPY REGX, REGY
            // 2. COPY REGX, data  where data contains an elementary value
            // 3- COPY REGX, symbol where symbol contains the index of an elementary type

            const int exception_shift = 9;

            Wrapper *regx;

            if (arg1.mode != OVO::Instruction::ARG::MODE::REG)
                return ThrowException(exception_shift + 0, "MOV arguments do not fit standard!");

            bool selection = SelectRegister(arg1.value, regx);
            if (!selection)
                return ThrowException(exception_shift + 1, "MOV arguments do not fit standard! Current value is: " + std::to_string(arg1.value) + ".");

            switch (arg2.mode)
            {
            case OVO::Instruction::ARG::MODE::REG:
            {
                Wrapper *regy;

                selection = SelectRegister(arg2.value, regy);
                if (!selection)
                    return ThrowException(exception_shift + 2, "MOV arguments do not find standard!");

                bool copy_result = regx->field->Copy(*(regy->field));
                if (!copy_result)
                    return ThrowException(exception_shift + 3, "Failed to copy content onto register.");
                return;
            }
            case OVO::Instruction::ARG::MODE::DATA:
            {
                auto result = RetrieveData(arg2.value);
                if (!result.ok)
                    return ThrowException(exception_shift + 4, "DATA could not be found!");
                OVO::Data data = result.data;

                Wrapper tmp = OVO::Data::ToWrapper(data, manager);

                bool copy_result = regx->field->Copy(*(tmp.field));

                if (copy_result)
                    return;

                bool cast_result = false;

                Wrapper cast = opHandler.EvaluateCast(tmp, regx->field->GetType());

                if(!cast_result)    
                    ThrowException(exception_shift + 5, "Failed to copy content onto register.");

                copy_result = regx->field->Copy(*(cast.field));

                if(!copy_result)
                    ThrowException(exception_shift + 6, "Failed to copy content onto register.");
               
                return;
            }
            case OVO::Instruction::ARG::MODE::SYMBOL:
            {
                switch (arg2.value)
                {
                case 0x00:
                    *regx = manager.GenerateVoidWrapper();
                    return;
                case 0x01:
                    *regx = manager.AllocateMemory<int>(0);
                    return;
                case 0x02:
                    *regx = manager.AllocateMemory<unsigned int>(0);
                    return;
                case 0x03:
                    *regx = manager.AllocateMemory<long>(0);
                    return;
                case 0x04:
                    *regx = manager.AllocateMemory<unsigned long>(0);
                    return;
                case 0x05:
                    *regx = manager.AllocateMemory<float>(0);
                    return;
                case 0x06:
                    *regx = manager.AllocateMemory<double>(0);
                    return;
                case 0x07:
                    *regx = manager.AllocateMemory<bool>(0);
                    return;
                case 0x08:
                    *regx = manager.AllocateMemory<char>(0);
                    return;
                case 0x09:
                    *regx = manager.AllocateMemory<unsigned char>(0);
                    return;
                case 0x0A:
                    *regx = manager.AllocateMemory<std::string>("");
                    return;
                default:
                    return ThrowException(exception_shift + 3, "MOV arguments do not fit standard!");
                }
            }
            default:
            {
                return ThrowException(exception_shift + 7, "MOV arguments do not fit standard!");
            }
            }
        }
        void YVM::I_CLONE(OVO::Instruction::ARG arg1, OVO::Instruction::ARG arg2)
        {
            // Usage:
            // CLONE REGX, REGY
            // CLONE REGX, data where data contains an elementary value
            // CLONE REGX, symbol where symbol contains the type of an elementary value

            const int exception_shift = 18;
            Wrapper *regx;

            if (arg1.mode != OVO::Instruction::ARG::MODE::REG)
                return ThrowException(exception_shift + 0, "MOV arguments do not fit standard!");

            bool selection = SelectRegister(arg1.value, regx);
            if (!selection)
                return ThrowException(exception_shift + 1, "MOV arguments do not fit standard! Current value is: " + std::to_string(arg1.value) + ".");

            switch (arg2.mode)
            {
            case OVO::Instruction::ARG::MODE::REG:
            {
                Wrapper *regy;

                selection = SelectRegister(arg2.value, regy);
                
                if (!selection)
                    return ThrowException(exception_shift + 2, "MOV arguments do not fit standard! Current value is: " + std::to_string(arg1.value) + ".");
                
                auto copy_result = manager.CopyByValue(*regy);

                if(copy_result.status == -1)
                    return ThrowException(exception_shift + 3, "Failed copy by value! Not a field");
                if(copy_result.status == -2)
                    return ThrowException(exception_shift + 4, "Failed copy by value! Not in memory!");
                
                *regx = copy_result.wrapper;
                return;

            }
            case OVO::Instruction::ARG::MODE::DATA:
            {
                auto result = RetrieveData(arg2.value);
                if (!result.ok)
                    return ThrowException(exception_shift + 5, "DATA could not be found!");
                OVO::Data data = result.data;

                auto wrapper = data.ToWrapper(data, manager);

                auto copy_result = manager.CopyByValue(wrapper);

                if(copy_result.status == -1)
                    return ThrowException(exception_shift + 6, "Failed copy by value! Not a field");
                if(copy_result.status == -2)
                    return ThrowException(exception_shift + 7, "Failed copy by value! Not in memory!");
                
                *regx = copy_result.wrapper;
                return;
            }
            case OVO::Instruction::ARG::MODE::SYMBOL:
            {
                switch (arg2.value)
                {
                case 0x00:
                    *regx = manager.GenerateVoidWrapper();
                    return;
                case 0x01:
                    *regx = manager.AllocateMemory<int>(0);
                    return;
                case 0x02:
                    *regx = manager.AllocateMemory<unsigned int>(0);
                    return;
                case 0x03:
                    *regx = manager.AllocateMemory<long>(0);
                    return;
                case 0x04:
                    *regx = manager.AllocateMemory<unsigned long>(0);
                    return;
                case 0x05:
                    *regx = manager.AllocateMemory<float>(0);
                    return;
                case 0x06:
                    *regx = manager.AllocateMemory<double>(0);
                    return;
                case 0x07:
                    *regx = manager.AllocateMemory<bool>(0);
                    return;
                case 0x08:
                    *regx = manager.AllocateMemory<char>(0);
                    return;
                case 0x09:
                    *regx = manager.AllocateMemory<unsigned char>(0);
                    return;
                case 0x0A:
                    *regx = manager.AllocateMemory<std::string>("");
                    return;
                default:
                    return ThrowException(exception_shift + 3, "MOV arguments do not fit standard!");
                }
            }
            default:
            {
                return ThrowException(exception_shift + 8, "MOV arguments do not fit standard!");
            }
            }
        }
        void YVM::I_NEW(OVO::Instruction::ARG arg1, OVO::Instruction::ARG arg2)
        {
            // Usage:
            // NEW REGX, symbol where symbol represents the index of an elementary type
            const int exception_shift = 27;

            Wrapper *regx;

            if (arg1.mode != OVO::Instruction::ARG::MODE::REG)
                return ThrowException(exception_shift + 0, "MOV arguments do not fit standard!");

            bool selection = SelectRegister(arg1.value, regx);
            if (!selection)
                return ThrowException(exception_shift + 1, "MOV arguments do not fit standard! Current value is: " + std::to_string(arg1.value) + ".");
            
            
            if(arg2.mode != OVO::Instruction::ARG::MODE::SYMBOL)
                return ThrowException(exception_shift + 2, "New Arguments do not fit standard!");
            
            switch (arg2.value)
            {
            case 0x00:
                *regx = manager.GenerateVoidWrapper();
                return;
            case 0x01:
                *regx = manager.AllocateMemory<int>(0);
                return;
            case 0x02:
                *regx = manager.AllocateMemory<unsigned int>(0);
                return;
            case 0x03:
                *regx = manager.AllocateMemory<long>(0);
                return;
            case 0x04:
                *regx = manager.AllocateMemory<unsigned long>(0);
                return;
            case 0x05:
                *regx = manager.AllocateMemory<float>(0);
                return;
            case 0x06:
                *regx = manager.AllocateMemory<double>(0);
                return;
            case 0x07:
                *regx = manager.AllocateMemory<bool>(0);
                return;
            case 0x08:
                *regx = manager.AllocateMemory<char>(0);
                return;
            case 0x09:
                *regx = manager.AllocateMemory<unsigned char>(0);
                return;
            case 0x0A:
                *regx = manager.AllocateMemory<std::string>("");
                return;
            default:
                return ThrowException(exception_shift + 3, "MOV arguments do not fit standard!");
            }
        }
        void YVM::I_MOVM(OVO::Instruction::ARG arg1)
        {
            // Usage:
            // MOVM data, where data contains the std::string of a method
            const int exception_shift = 0xAA;
            if (arg1.mode != OVO::Instruction::ARG::MODE::DATA)
                return ThrowException(exception_shift + 4, "MOVM arguments do not fit standard!");

            auto result = RetrieveData(arg1.value);

            if (!result.ok)
                return ThrowException(exception_shift + 5, "DATA could not be found!");

            std::string method_name = OVO::Data::ToWrapper(result.data, manager).field->As<std::string>();

            auto symbol_result = workingSymTable->Get(Yolk::Memory::SymbolKey(method_name));

            if (!symbol_result.ok)
                return ThrowException(exception_shift + 6, "Could not find method named \"" + method_name + "\".");

            auto wrapper_info = wrapperTable.GetInfo(symbol_result.value.key);

            if (!wrapper_info.alive)
                return ThrowException(exception_shift + 7, "Could not find method named \"" + method_name + "\". It has already been deleted.");
            if (wrapper_info.wrapperType != WrapperType::MethodWrapper)
                return ThrowException(exception_shift + 8, "Wrapper named \"" + method_name + "\" is not a method.");

            MethodWrapper func = wrapperTable.CopyMethod(symbol_result.value.key);

            mreg = func;

            return;
        }
        void YVM::I_CALLM()
        {
            // Usage:
            // CALLM
            const int exception_shift = 36;
            
            if (!mreg.IsValid())
                return ThrowException(exception_shift + 0, "Method register is not valid.");

            auto result = mreg.Invoke(argreg);

            if (!result.ok)
                return ThrowException(exception_shift + 1, "Failed to invoke method: " + result.Message);

            regout = result.output;
        }
        void YVM::I_PUSHAR(OVO::Instruction::ARG arg1)
        {
            // Usage:
            // PUSHAR REGX
            const int exception_shift = 2;
            Wrapper *regx;

            if (arg1.mode != OVO::Instruction::ARG::MODE::REG)
                return ThrowException(exception_shift + 3, "MOV arguments do not fit standard!");

            bool selection = SelectRegister(arg1.value, regx);
            if (!selection)
                return ThrowException(exception_shift + 4, "MOV arguments do not fit standard! Current value is: " + std::to_string(arg1.value) + ".");

            argreg.push_back(*regx);
        }
        void YVM::I_POPAR(OVO::Instruction::ARG arg1)
        {
            // Usage:
            // 1. POPAR REGX
            // 2. POPAR
            const int exception_shift = 41;
            if (arg1.mode == OVO::Instruction::ARG::MODE::REG)
            {
                Wrapper *regx;

                bool selection = SelectRegister(arg1.value, regx);
                if (!selection)
                    return ThrowException(exception_shift + 0, "MOV arguments do not fit standard!");

                if (argreg.size() == 0)
                {
                    *regx = manager.GenerateVoidWrapper();
                    return;
                }

                Wrapper wrapper = argreg.at(argreg.size() - 1);
                *regx = wrapper;

                argreg.pop_back();
                return;
            }
            else if (arg1.mode == OVO::Instruction::ARG::MODE::NONE)
            {
                if (argreg.size() == 0)
                    return;
                argreg.pop_back();
                return;
            }
        }
        void YVM::I_CLRAR()
        {
            // Usage:
            // CLRAR
            argreg.clear();
            return;
        }
        void YVM::I_PUSH(OVO::Instruction::ARG arg1)
        {
            // Usage:
            // PUSH REGX
            const int exception_shift = 43;
            Wrapper *regx;

            if (arg1.mode != OVO::Instruction::ARG::MODE::REG)
                return ThrowException(exception_shift + 0, "MOV arguments do not fit standard!");

            bool selection = SelectRegister(arg1.value, regx);
            if (!selection)
                return ThrowException(exception_shift + 1, "MOV arguments do not fit standard! Current value is: " + std::to_string(arg1.value) + ".");

            stack.push_back(*regx);
        }
        void YVM::I_POP(OVO::Instruction::ARG arg1)
        {
            // Usage:
            // 1. POP REGX
            // 2. POP
            const int exception_shift = 45;
            if (arg1.mode == OVO::Instruction::ARG::MODE::REG)
            {
                Wrapper *regx;

                bool selection = SelectRegister(arg1.value, regx);
                if (!selection)
                    return ThrowException(exception_shift + 0, "MOV arguments do not fit standard!");

                if (stack.size() == 0)
                {
                    *regx = manager.GenerateVoidWrapper();
                    return;
                }

                Wrapper wrapper = stack.at(stack.size() - 1);
                *regx = wrapper;

                stack.pop_back();
                return;
            }
            else if (arg1.mode == OVO::Instruction::ARG::MODE::NONE)
            {
                if (stack.size() == 0)
                    return;
                stack.pop_back();
                return;
            }
        }
        void YVM::I_CLEAR()
        {
            // Usage:
            // CLEAR

            stack.clear();
            return;
        }
        void YVM::I_CMP(OVO::Instruction::ARG arg1)
        {
            // Usage:
            // CMP REGX

            const int exception_shift = 46;
            Wrapper *regx;

            if (arg1.mode != OVO::Instruction::ARG::MODE::REG)
                return ThrowException(exception_shift + 0, "MOV arguments do not fit standard!");

            bool selection = SelectRegister(arg1.value, regx);
            if (!selection)
                return ThrowException(exception_shift + 1, "MOV arguments do not fit standard!");

            if (!regx->field->Valid())
                return ThrowException(exception_shift + 2, "Wrapper is not valid!");

            // Todo: More checks in here. Not everything can be cast as bool.
            // Ideally, one can create a method in the Typed Field where it returns an error if the type can not be cast to bool.
            cmpreg = regx->field->As<bool>();
            return;
        }
        void YVM::I_CMPEQ(OVO::Instruction::ARG arg1, OVO::Instruction::ARG arg2)
        {
            // Usage:
            // 1. CMPEQ REGX, REGY
            // 2. CMPEQ REGX, data where data contains an elementary value
            const int exception_shift = 49;

            Wrapper *regx;

            /*if (arg1.mode != OVO::Instruction::ARG::MODE::REG)
                return ThrowException(exception_shift + 0, "MOV arguments do not fit standard!");*/

            bool selection = SelectRegister(arg1.value, regx);
            if (!selection)
                return ThrowException(exception_shift + 1, "MOV arguments do not fit standard! Current value is: " + std::to_string(arg1.value) + ".");

            switch (arg2.mode)
            {
            case OVO::Instruction::ARG::MODE::REG:
            {
                Wrapper *regy;

                selection = SelectRegister(arg2.value, regy);
                if (!selection)
                    return ThrowException(exception_shift + 2, "MOV arguments do not find standard!");

                if (regy->field->GetType() == regx->field->GetType())
                {
                    cmpreg = regy->field->Compare(*(regx->field));
                    return;
                }
                bool can_evaluate = false;
                Wrapper cmp_result = opHandler.EvaluateEquality(*regx, *regy, can_evaluate);

                if (!can_evaluate)
                    return ThrowException(exception_shift + 3, "Operator == is not defined for types: " + std::string(regx->field->GetType().name()) + " and " + std::string(regy->field->GetType().name()) + ".");

                cmpreg = cmp_result.field->As<bool>();
                return;
            }
            case OVO::Instruction::ARG::MODE::DATA:
            {
                auto result = RetrieveData(arg2.value);
                if (!result.ok)
                    return ThrowException(exception_shift + 4, "DATA could not be found!");
                
                OVO::Data data = result.data;
                Wrapper tmp = OVO::Data::ToWrapper(data, manager);


                if (tmp.field->GetType() == regx->field->GetType())
                {
                    cmpreg = tmp.field->Compare(*(regx->field));
                    return;
                }
                bool can_evaluate = false;
                Wrapper cmp_result = opHandler.EvaluateEquality(*regx, tmp, can_evaluate);

                if (!can_evaluate)
                    return ThrowException(exception_shift + 5, "Operator == is not defined for types: " + std::string(regx->field->GetType().name()) + " and " + std::string(tmp.field->GetType().name()) + ".");

                cmpreg = cmp_result.field->As<bool>();
                return;
            }
            default:
            {
                return ThrowException(exception_shift + 6, "MOV arguments do not fit standard!");
            }
            }
        }
        void YVM::I_CMPNEQ(OVO::Instruction::ARG arg1, OVO::Instruction::ARG arg2)
        {
            // Usage:
            // CMPNEQ REGX, REGY
            // CMPNEQ REGX, data where data contains an elementary type
            const int exception_shift = 56;

            Wrapper *regx;

            /*if (arg1.mode != OVO::Instruction::ARG::MODE::REG)
                return ThrowException(exception_shift + 0, "MOV arguments do not fit standard!");*/

            bool selection = SelectRegister(arg1.value, regx);
            if (!selection)
                return ThrowException(exception_shift + 1, "MOV arguments do not fit standard! Current value is: " + std::to_string(arg1.value) + ".");

            switch (arg2.mode)
            {
            case OVO::Instruction::ARG::MODE::REG:
            {
                Wrapper *regy;

                selection = SelectRegister(arg2.value, regy);
                if (!selection)
                    return ThrowException(exception_shift + 2, "MOV arguments do not find standard!");

                if (regy->field->GetType() == regx->field->GetType())
                {
                    cmpreg = !regy->field->Compare(*(regx->field));
                    return;
                }
                bool can_evaluate = false;
                Wrapper cmp_result = opHandler.EvaluateEquality(*regx, *regy, can_evaluate);

                if (!can_evaluate)
                    return ThrowException(exception_shift + 3, "Operator = is not defined for types: " + std::string(regx->field->GetType().name()) + " and " + std::string(regy->field->GetType().name()) + ".");

                cmpreg = !cmp_result.field->As<bool>();
                return;
            }
            case OVO::Instruction::ARG::MODE::DATA:
            {
                auto result = RetrieveData(arg2.value);
                if (!result.ok)
                    return ThrowException(exception_shift + 4, "DATA could not be found!");

                OVO::Data data = result.data;
                Wrapper tmp = OVO::Data::ToWrapper(data, manager);

                if (tmp.field->GetType() == regx->field->GetType())
                {
                    cmpreg = !tmp.field->Compare(*(regx->field));
                    return;
                }
                bool can_evaluate = false;
                Wrapper cmp_result = opHandler.EvaluateEquality(*regx, tmp, can_evaluate);

                if (!can_evaluate)
                    return ThrowException(exception_shift + 5, "Operator = is not defined for types: " + std::string(regx->field->GetType().name()) + " and " + std::string(tmp.field->GetType().name()) + ".");

                cmpreg = !cmp_result.field->As<bool>();
                return;
            }
            default:
            {
                return ThrowException(exception_shift + 6, "MOV arguments do not fit standard!");
            }
            }
        }
        void YVM::I_CMPLS(OVO::Instruction::ARG arg1, OVO::Instruction::ARG arg2)
        {
            // Usage:
            // CMPLS REGX, REGY
            // CMPLS REGX, data where data contains an elementary value
            const int exception_shift = 63;

            Wrapper *regx;

            if (arg1.mode != OVO::Instruction::ARG::MODE::REG)
                return ThrowException(exception_shift + 0, "MOV arguments do not fit standard!");

            bool selection = SelectRegister(arg1.value, regx);
            if (!selection)
                return ThrowException(exception_shift + 1, "MOV arguments do not fit standard! Current value is: " + std::to_string(arg1.value) + ".");

            switch (arg2.mode)
            {
            case OVO::Instruction::ARG::MODE::REG:
            {
                Wrapper *regy;

                selection = SelectRegister(arg2.value, regy);
                if (!selection)
                    return ThrowException(exception_shift + 2, "MOV arguments do not find standard!");

                if(regx->field->GetType() == regy->field->GetType())
                {
                    cmpreg = regx->field->CompareLess(*regy->field);
                    return;
                }

                bool can_evaluate = false;
                Wrapper cmp_result = opHandler.EvaluateLessThan(*regx, *regy, can_evaluate);

                if (!can_evaluate)
                    return ThrowException(exception_shift + 3, "Operator < is not defined for types: " + std::string(regx->field->GetType().name()) + " and " + std::string(regy->field->GetType().name()) + ".");

                cmpreg = cmp_result.field->As<bool>();
                return;
            }
            case OVO::Instruction::ARG::MODE::DATA:
            {
                auto result = RetrieveData(arg2.value);
                if (!result.ok)
                    return ThrowException(exception_shift + 0x4, "DATA could not be found!");
                OVO::Data data = result.data;
                Wrapper tmp = OVO::Data::ToWrapper(data, manager);

                if(regx->field->GetType() == tmp.field->GetType())
                {
                    cmpreg = regx->field->CompareLess(*tmp.field);
                    return;
                }
                bool can_evaluate = false;
                Wrapper cmp_result = opHandler.EvaluateLessThan(*regx, tmp, can_evaluate);

                if (!can_evaluate)
                    return ThrowException(exception_shift + 0x05, "Operator < is not defined for types: " + std::string(regx->field->GetType().name()) + " and " + std::string(tmp.field->GetType().name()) + ".");

                cmpreg = cmp_result.field->As<bool>();
                return;
            }
            default:
            {
                return ThrowException(exception_shift + 0x9, "MOV arguments do not fit standard!");
            }
            }
        }
        void YVM::I_CMPGT(OVO::Instruction::ARG arg1, OVO::Instruction::ARG arg2)
        {
            // Usage:
            // CMPGT REGX, REGX
            // CMPGT REGX, data where data contains an elementary value
            const int exception_shift = 0x0;

            Wrapper *regx;

            if (arg1.mode != OVO::Instruction::ARG::MODE::REG)
                return ThrowException(exception_shift + 0x1, "MOV arguments do not fit standard!");

            bool selection = SelectRegister(arg1.value, regx);
            if (!selection)
                return ThrowException(exception_shift + 0x2, "MOV arguments do not fit standard! Current value is: " + std::to_string(arg1.value) + ".");

            switch (arg2.mode)
            {
            case OVO::Instruction::ARG::MODE::REG:
            {
                Wrapper *regy;

                selection = SelectRegister(arg2.value, regy);
                if (!selection)
                    return ThrowException(exception_shift + 0x3, "MOV arguments do not find standard!");



                if(regx->field->GetType() == regy->field->GetType())
                {
                    cmpreg = regx->field->CompareGreater(*regy->field);
                    return;
                }
                bool can_evaluate = false;
                Wrapper cmp_result = opHandler.EvaluateGreaterThan(*regx, *regy, can_evaluate);

                if (!can_evaluate)
                    return ThrowException(exception_shift + 0x05, "Operator > is not defined for types: " + std::string(regx->field->GetType().name()) + " and " + std::string(regy->field->GetType().name()) + ".");

                cmpreg = cmp_result.field->As<bool>();
                return;
            }
            case OVO::Instruction::ARG::MODE::DATA:
            {
                auto result = RetrieveData(arg2.value);
                if (!result.ok)
                    return ThrowException(exception_shift + 0x4, "DATA could not be found!");
                OVO::Data data = result.data;
                Wrapper tmp = OVO::Data::ToWrapper(data, manager);


                if(regx->field->GetType() == tmp.field->GetType())
                {
                    cmpreg = regx->field->CompareGreater(*tmp.field);
                    return;
                }

                bool can_evaluate = false;
                Wrapper cmp_result = opHandler.EvaluateGreaterThan(*regx, tmp, can_evaluate);

                if (!can_evaluate)
                    return ThrowException(exception_shift + 0x05, "Operator > is not defined for types: " + std::string(regx->field->GetType().name()) + " and " + std::string(tmp.field->GetType().name()) + ".");

                cmpreg = cmp_result.field->As<bool>();
                return;
            }
            default:
            {
                return ThrowException(exception_shift + 0x9, "MOV arguments do not fit standard!");
            }
            }
        }
        void YVM::I_CMPLSEQ(OVO::Instruction::ARG arg1, OVO::Instruction::ARG arg2)
        {
            // Usage:
            // CMPLSEQ REGX, REGY
            // CMPLSEQ REGX, data where data contains an elementary value
            const int exception_shift = 0x0;

            Wrapper *regx;

            if (arg1.mode != OVO::Instruction::ARG::MODE::REG)
                return ThrowException(exception_shift + 0x1, "MOV arguments do not fit standard!");

            bool selection = SelectRegister(arg1.value, regx);
            if (!selection)
                return ThrowException(exception_shift + 0x2, "MOV arguments do not fit standard! Current value is: " + std::to_string(arg1.value) + ".");

            switch (arg2.mode)
            {
            case OVO::Instruction::ARG::MODE::REG:
            {
                Wrapper *regy;

                selection = SelectRegister(arg2.value, regy);
                if (!selection)
                    return ThrowException(exception_shift + 0x3, "MOV arguments do not find standard!");


                if(regx->field->GetType() == regy->field->GetType())
                {
                    cmpreg = regx->field->CompareLessEqual(*regy->field);
                    return;
                }
                bool can_evaluate = false;
                Wrapper cmp_result = opHandler.EvaluateLessOrEqualThan(*regx, *regy, can_evaluate);

                if (!can_evaluate)
                    return ThrowException(exception_shift + 0x05, "Operator <= is not defined for types: " + std::string(regx->field->GetType().name()) + " and " + std::string(regy->field->GetType().name()) + ".");

                cmpreg = cmp_result.field->As<bool>();
                return;
            }
            case OVO::Instruction::ARG::MODE::DATA:
            {
                auto result = RetrieveData(arg2.value);
                if (!result.ok)
                    return ThrowException(exception_shift + 0x4, "DATA could not be found!");
                OVO::Data data = result.data;
                Wrapper tmp = OVO::Data::ToWrapper(data, manager);

                if(regx->field->GetType() == tmp.field->GetType())
                {
                    cmpreg = regx->field->CompareLessEqual(*tmp.field);
                    return;
                }
                bool can_evaluate = false;
                Wrapper cmp_result = opHandler.EvaluateLessOrEqualThan(*regx, tmp, can_evaluate);

                if (!can_evaluate)
                    return ThrowException(exception_shift + 0x05, "Operator <= is not defined for types: " + std::string(regx->field->GetType().name()) + " and " + std::string(tmp.field->GetType().name()) + ".");

                cmpreg = cmp_result.field->As<bool>();
                return;
            }
            default:
            {
                return ThrowException(exception_shift + 0x9, "MOV arguments do not fit standard!");
            }
            }
        }
        void YVM::I_CMPGTEQ(OVO::Instruction::ARG arg1, OVO::Instruction::ARG arg2)
        {
            // Usage:
            // CMPGTEQ REGX, REGY
            // CMPGTEQ REGX, data where data contains an elementary type
            const int exception_shift = 0x0;

            Wrapper *regx;

            if (arg1.mode != OVO::Instruction::ARG::MODE::REG)
                return ThrowException(exception_shift + 0x1, "MOV arguments do not fit standard!");

            bool selection = SelectRegister(arg1.value, regx);
            if (!selection)
                return ThrowException(exception_shift + 0x2, "MOV arguments do not fit standard! Current value is: " + std::to_string(arg1.value) + ".");

            switch (arg2.mode)
            {
            case OVO::Instruction::ARG::MODE::REG:
            {
                Wrapper *regy;

                selection = SelectRegister(arg2.value, regy);
                if (!selection)
                    return ThrowException(exception_shift + 0x3, "MOV arguments do not find standard!");

                if(regx->field->GetType() == regy->field->GetType())
                {
                    cmpreg = regx->field->CompareGreaterEqual(*regy->field);
                    return;
                }

                bool can_evaluate = false;
                Wrapper cmp_result = opHandler.EvaluateGreaterOrEqualThan(*regx, *regy, can_evaluate);

                if (!can_evaluate)
                    return ThrowException(exception_shift + 0x05, "Operator >= is not defined for types: " + std::string(regx->field->GetType().name()) + " and " + std::string(regy->field->GetType().name()) + ".");

                cmpreg = cmp_result.field->As<bool>();
                return;
            }
            case OVO::Instruction::ARG::MODE::DATA:
            {
                auto result = RetrieveData(arg2.value);
                if (!result.ok)
                    return ThrowException(exception_shift + 0x4, "DATA could not be found!");
                OVO::Data data = result.data;
                Wrapper tmp = OVO::Data::ToWrapper(data, manager);

                if(regx->field->GetType() == tmp.field->GetType())
                {
                    cmpreg = regx->field->CompareGreaterEqual(*tmp.field);
                    return;
                }

                bool can_evaluate = false;
                Wrapper cmp_result = opHandler.EvaluateGreaterOrEqualThan(*regx, tmp, can_evaluate);

                if (!can_evaluate)
                    return ThrowException(exception_shift + 0x05, "Operator >= is not defined for types: " + std::string(regx->field->GetType().name()) + " and " + std::string(tmp.field->GetType().name()) + ".");

                cmpreg = cmp_result.field->As<bool>();
                return;
            }
            default:
            {
                return ThrowException(exception_shift + 0x9, "MOV arguments do not fit standard!");
            }
            }
        }
        void YVM::I_JNTRUE(OVO::Instruction::ARG arg1)
        {
            // Usage:
            // JNTRUE REGX
            // JNTRUE data where data contains the position of the jump
            // JNTRUE symbol where symbol contains the value for the jump
            const int exception_shift = 0x00;
            if (cmpreg)
            {
                switch (arg1.mode)
                {
                case OVO::Instruction::ARG::MODE::REG:
                {
                    Wrapper *regx;

                    bool selection = SelectRegister(arg1.value, regx);
                    if (!selection)
                        return ThrowException(exception_shift + 0x3, "MOV arguments do not find standard!");

                    if (!regx->field->Valid())
                        return ThrowException(exception_shift + 0x4, "Register is void!");

                    if (regx->field->GetType() == typeid(unsigned long int))
                    {
                        unsigned long int position = regx->field->As<unsigned long int>();
                        JumpToInstruction(position);
                        return;
                    }
                    bool cast_result = false;

                    Wrapper wrap = opHandler.EvaluateCast(*regx, typeid(unsigned long int));

                    if (!cast_result)
                        return ThrowException(exception_shift + 0x5, "Can't convert register to unsigned long int.");

                    unsigned long int position = wrap.field->As<unsigned long int>();
                    JumpToInstruction(position);
                    return;
                }
                case OVO::Instruction::ARG::MODE::DATA:
                {
                    auto result = RetrieveData(arg1.value);
                    if (!result.ok)
                        return ThrowException(exception_shift + 0x4, "DATA could not be found!");
                    OVO::Data data = result.data;

                    Wrapper tmp = OVO::Data::ToWrapper(data, manager);

                    if (!tmp.field->Valid())
                        return ThrowException(exception_shift + 0x4, "Register is void!");

                    if (tmp.field->GetType() == typeid(unsigned long int))
                    {
                        unsigned long int position = tmp.field->As<unsigned long int>();
                        JumpToInstruction(position);
                        return;
                    }
                    bool cast_result = false;

                    Wrapper wrap = opHandler.EvaluateCast(tmp, typeid(unsigned long int));

                    if (!cast_result)
                        return ThrowException(exception_shift + 0x5, "Can't convert register to unsigned long int.");

                    unsigned long int position = wrap.field->As<unsigned long int>();

                    JumpToInstruction(position);
                    return;
                }
                case OVO::Instruction::ARG::MODE::SYMBOL:
                {
                    unsigned long int position = arg1.value;

                    JumpToInstruction(position);

                    return;
                }
                default:
                {
                    return ThrowException(exception_shift + 0x9, "MOV arguments do not fit standard!");
                }
                }
            }
        }
        void YVM::I_JNFALSE(OVO::Instruction::ARG arg1)
        {
            // Usage:
            // JNFALSE REGX
            // JNFALSE data where data contains the position of the jump
            // JNFALSE symbol where symbol contains the value for the jump
            const int exception_shift = 0x00;
            if (!cmpreg)
            {
                switch (arg1.mode)
                {
                case OVO::Instruction::ARG::MODE::REG:
                {
                    Wrapper *regx;

                    bool selection = SelectRegister(arg1.value, regx);
                    if (!selection)
                        return ThrowException(exception_shift + 0x3, "MOV arguments do not find standard!");

                    if (!regx->field->Valid())
                        return ThrowException(exception_shift + 0x4, "Register is void!");

                    if (regx->field->GetType() == typeid(unsigned long int))
                    {
                        unsigned long int position = regx->field->As<unsigned long int>();
                        JumpToInstruction(position);
                        return;
                    }
                    bool cast_result = false;

                    Wrapper wrap = opHandler.EvaluateCast(*regx, typeid(unsigned long int));

                    if (!cast_result)
                        return ThrowException(exception_shift + 0x5, "Can't convert register to unsigned long int.");

                    unsigned long int position = wrap.field->As<unsigned long int>();
                    JumpToInstruction(position);
                    return;
                }
                case OVO::Instruction::ARG::MODE::DATA:
                {
                    auto result = RetrieveData(arg1.value);
                    if (!result.ok)
                        return ThrowException(exception_shift + 0x4, "DATA could not be found!");
                    OVO::Data data = result.data;

                    Wrapper tmp = OVO::Data::ToWrapper(data, manager);

                    if (!tmp.field->Valid())
                        return ThrowException(exception_shift + 0x4, "Register is void!");

                    if (tmp.field->GetType() == typeid(unsigned long int))
                    {
                        unsigned long int position = tmp.field->As<unsigned long int>();
                        JumpToInstruction(position);
                        return;
                    }
                    bool cast_result = false;

                    Wrapper wrap = opHandler.EvaluateCast(tmp, typeid(unsigned long int));

                    if (!cast_result)
                        return ThrowException(exception_shift + 0x5, "Can't convert register to unsigned long int.");

                    unsigned long int position = wrap.field->As<unsigned long int>();
                    JumpToInstruction(position);
                    return;
                }
                case OVO::Instruction::ARG::MODE::SYMBOL:
                {
                    unsigned long int position = arg1.value;

                    JumpToInstruction(position);

                    return;
                }
                default:
                {
                    return ThrowException(exception_shift + 0x9, "MOV arguments do not fit standard!");
                }
                }
            }
        }
        void YVM::I_JMP(OVO::Instruction::ARG arg1)
        {
            // Usage:
            // JMP REGX
            // JMP data where data contains the position of the jump
            // JMP symbol where symbol contains the value for the jump
            const int exception_shift = 0x00;
            switch (arg1.mode)
            {
            case OVO::Instruction::ARG::MODE::REG:
            {
                Wrapper *regx;

                bool selection = SelectRegister(arg1.value, regx);
                if (!selection)
                    return ThrowException(exception_shift + 0x3, "MOV arguments do not find standard!");

                if (!regx->field->Valid())
                    return ThrowException(exception_shift + 0x4, "Register is void!");

                if (regx->field->GetType() == typeid(unsigned long int))
                {
                    unsigned long int position = regx->field->As<unsigned long int>();
                    JumpToInstruction(position);
                    return;
                }
                bool cast_result = false;

                Wrapper wrap = opHandler.EvaluateCast(*regx, typeid(unsigned long int));

                if (!cast_result)
                    return ThrowException(exception_shift + 0x5, "Can't convert register to unsigned long int.");

                unsigned long int position = wrap.field->As<unsigned long int>();
                JumpToInstruction(position);
                return;
            }
            case OVO::Instruction::ARG::MODE::DATA:
            {
                auto result = RetrieveData(arg1.value);
                if (!result.ok)
                    return ThrowException(exception_shift + 0x4, "DATA could not be found!");
                OVO::Data data = result.data;

                Wrapper tmp = OVO::Data::ToWrapper(data, manager);

                if (!tmp.field->Valid())
                    return ThrowException(exception_shift + 0x4, "Register is void!");

                if (tmp.field->GetType() == typeid(unsigned long int))
                {
                    unsigned long int position = tmp.field->As<unsigned long int>();
                    JumpToInstruction(position);
                    return;
                }
                bool cast_result = false;

                Wrapper wrap = opHandler.EvaluateCast(tmp, typeid(unsigned long int));

                if (!cast_result)
                    return ThrowException(exception_shift + 0x5, "Can't convert register to unsigned long int.");

                unsigned long int position = wrap.field->As<unsigned long int>();
                JumpToInstruction(position);
                return;
            }
            case OVO::Instruction::ARG::MODE::SYMBOL:
            {
                unsigned long int position = arg1.value;

                JumpToInstruction(position);

                return;
            }
            default:
            {
                return ThrowException(exception_shift + 0x9, "MOV arguments do not fit standard!");
            }
            }
        }
        void YVM::I_CALL(OVO::Instruction::ARG arg1)
        {
            // Usage:
            // CALL REGX
            // CALL data where data contains the position of the jump
            // CALL symbol where symbol contains the value for the jump
            const int exception_shift = 0x00;

            auto current_instruction = manager.AllocateMemory<unsigned long int>(CurrentInstruction());

            switch (arg1.mode)
            {
            case OVO::Instruction::ARG::MODE::REG:
            {
                Wrapper *regx;

                bool selection = SelectRegister(arg1.value, regx);
                if (!selection)
                    return ThrowException(exception_shift + 0x3, "MOV arguments do not find standard!");

                if (!regx->field->Valid())
                    return ThrowException(exception_shift + 0x4, "Register is void!");

                if (regx->field->GetType() == typeid(unsigned long int))
                {
                    unsigned long int position = regx->field->As<unsigned long int>();
                    
                    stack.push_back(current_instruction);
                    JumpToInstruction(position);
                    return;
                }
                bool cast_result = false;

                Wrapper wrap = opHandler.EvaluateCast(*regx, typeid(unsigned long int));

                if (!cast_result)
                    return ThrowException(exception_shift + 0x5, "Can't convert register to unsigned long int.");

                unsigned long int position = wrap.field->As<unsigned long int>();
                
                stack.push_back(current_instruction);
                JumpToInstruction(position);
                return;
            }
            case OVO::Instruction::ARG::MODE::DATA:
            {
                auto result = RetrieveData(arg1.value);
                if (!result.ok)
                    return ThrowException(exception_shift + 0x4, "DATA could not be found!");
                OVO::Data data = result.data;

                Wrapper tmp = OVO::Data::ToWrapper(data, manager);

                if (!tmp.field->Valid())
                    return ThrowException(exception_shift + 0x4, "Register is void!");

                if (tmp.field->GetType() == typeid(unsigned long int))
                {
                    unsigned long int position = tmp.field->As<unsigned long int>();
                    
                    stack.push_back(current_instruction);
                    JumpToInstruction(position);
                    return;
                }
                bool cast_result = false;

                Wrapper wrap = opHandler.EvaluateCast(tmp, typeid(unsigned long int));

                if (!cast_result)
                    return ThrowException(exception_shift + 0x5, "Can't convert register to unsigned long int.");

                unsigned long int position = wrap.field->As<unsigned long int>();
                
                stack.push_back(current_instruction);
                JumpToInstruction(position);
                return;
            }
            case OVO::Instruction::ARG::MODE::SYMBOL:
            {
                unsigned long int position = arg1.value;

                stack.push_back(current_instruction);
                JumpToInstruction(position);

                return;
            }
            default:
            {
                return ThrowException(exception_shift + 0x9, "MOV arguments do not fit standard!");
            }
            }
        }
        void YVM::I_RET()
        {
            // Usage:
            // RET

            const int exception_shift = 0x00;
            if(stack.size() == 0)
                return ThrowException(exception_shift + 0x1, "Stack is Empty. Can't return.");

            auto previous_instruction = stack.at(stack.size() - 1);
            stack.pop_back();

            if(!previous_instruction.field->Valid())
                return ThrowException(exception_shift + 0x01, "Can't return to a void position");
            
            if(previous_instruction.field->GetType() == typeid(unsigned long int))
            {
                unsigned long int position = previous_instruction.field->As<unsigned long int>();
                JumpToInstruction(position);
                return;
            }

            bool cast_result = false;

            Wrapper wrap = opHandler.EvaluateCast(previous_instruction, typeid(unsigned long int));

            if(!cast_result)
                return ThrowException(exception_shift + 0x02, "Failed to get return address from top of stack.");

            unsigned long int position = wrap.field->As<unsigned long int>();


            JumpToInstruction(position);


        }
        void YVM::I_ADD(OVO::Instruction::ARG arg1, OVO::Instruction::ARG arg2)
        {
            // Usage:
            // ADD REGX, REGY
            const int exception_shift = 0x0;

            Wrapper *regx;

            /*if (arg1.mode != OVO::Instruction::ARG::MODE::REG)
                return ThrowException(exception_shift + 0x1, "MOV arguments do not fit standard!");*/

            bool selection = SelectRegister(arg1.value, regx);
            if (!selection)
                return ThrowException(exception_shift + 0x2, "MOV arguments do not fit standard! Current value is: " + std::to_string(arg1.value) + ".");

            Wrapper *regy;

            /*if (arg2.mode != OVO::Instruction::ARG::MODE::REG)
                return ThrowException(exception_shift + 0x1, "MOV arguments do not fit standard!");*/

            selection = SelectRegister(arg2.value, regy);
            if (!selection)
                return ThrowException(exception_shift + 0x2, "MOV arguments do not fit standard! Current value is: " + std::to_string(arg1.value) + ".");

            bool can_add = regx->field->TryAdd(*(regy->field));

            if(can_add)
                return;

            Wrapper tmp = opHandler.EvaluateAdd(*regx, *regy, can_add);

            if (!can_add)
                return ThrowException(exception_shift + 0x05, "Operator + is not defined for types: " + std::string(regx->field->GetType().name()) + " and " + std::string(regy->field->GetType().name()) + ".");

            regx->field->Set(*tmp.field); // Todo: Is this correct? Should we copy the value of the sum to regx? Or copy it as a new wrapper?
        }
        void YVM::I_SUB(OVO::Instruction::ARG arg1, OVO::Instruction::ARG arg2)
        {
            // Usage:
            // SUB REGX, REGY
            const int exception_shift = 0x0;

            Wrapper *regx;

            if (arg1.mode != OVO::Instruction::ARG::MODE::REG)
                return ThrowException(exception_shift + 0x1, "MOV arguments do not fit standard!");

            bool selection = SelectRegister(arg1.value, regx);
            if (!selection)
                return ThrowException(exception_shift + 0x2, "MOV arguments do not fit standard! Current value is: " + std::to_string(arg1.value) + ".");

            Wrapper *regy;

            if (arg2.mode != OVO::Instruction::ARG::MODE::REG)
                return ThrowException(exception_shift + 0x1, "MOV arguments do not fit standard!");

            selection = SelectRegister(arg2.value, regy);
            if (!selection)
                return ThrowException(exception_shift + 0x2, "MOV arguments do not fit standard! Current value is: " + std::to_string(arg1.value) + ".");

            bool can_sub = regx->field->TrySub(*(regy->field));

            if(can_sub)
                return;

            Wrapper tmp = opHandler.EvaluateSubtract(*regx, *regy, can_sub);

            if (!can_sub)
                return ThrowException(exception_shift + 0x05, "Operator - is not defined for types: " + std::string(regx->field->GetType().name()) + " and " + std::string(regy->field->GetType().name()) + ".");

            regx->field->Set(*tmp.field); // Todo: Is this correct? Should we copy the value of the sum to regx? Or copy it as a new wrapper?
        }
        void YVM::I_MUL(OVO::Instruction::ARG arg1, OVO::Instruction::ARG arg2)
        {
            // Usage:
            // MUL REGX, REGY
            const int exception_shift = 0x0;

            Wrapper *regx;

            if (arg1.mode != OVO::Instruction::ARG::MODE::REG)
                return ThrowException(exception_shift + 0x1, "MOV arguments do not fit standard!");

            bool selection = SelectRegister(arg1.value, regx);
            if (!selection)
                return ThrowException(exception_shift + 0x2, "MOV arguments do not fit standard! Current value is: " + std::to_string(arg1.value) + ".");

            Wrapper *regy;

            if (arg2.mode != OVO::Instruction::ARG::MODE::REG)
                return ThrowException(exception_shift + 0x1, "MOV arguments do not fit standard!");

            selection = SelectRegister(arg2.value, regy);
            if (!selection)
                return ThrowException(exception_shift + 0x2, "MOV arguments do not fit standard! Current value is: " + std::to_string(arg1.value) + ".");

            bool can_mul = regx->field->TryMul(*(regy->field));

            if(can_mul)
                return;

            Wrapper tmp = opHandler.EvaluateMultiply(*regx, *regy, can_mul);

            if (!can_mul)
                return ThrowException(exception_shift + 0x05, "Operator * is not defined for types: " + std::string(regx->field->GetType().name()) + " and " + std::string(regy->field->GetType().name()) + ".");

            regx->field->Set(*tmp.field); // Todo: Is this correct? Should we copy the value of the sum to regx? Or copy it as a new wrapper?
        }
        void YVM::I_DIV(OVO::Instruction::ARG arg1, OVO::Instruction::ARG arg2)
        {
            // Usage
            // DIV REGX, REGY
            const int exception_shift = 0x0;

            Wrapper *regx;

            if (arg1.mode != OVO::Instruction::ARG::MODE::REG)
                return ThrowException(exception_shift + 0x1, "MOV arguments do not fit standard!");

            bool selection = SelectRegister(arg1.value, regx);
            if (!selection)
                return ThrowException(exception_shift + 0x2, "MOV arguments do not fit standard! Current value is: " + std::to_string(arg1.value) + ".");

            Wrapper *regy;

            if (arg2.mode != OVO::Instruction::ARG::MODE::REG)
                return ThrowException(exception_shift + 0x1, "MOV arguments do not fit standard!");

            selection = SelectRegister(arg2.value, regy);
            if (!selection)
                return ThrowException(exception_shift + 0x2, "MOV arguments do not fit standard! Current value is: " + std::to_string(arg1.value) + ".");

            bool can_div = regx->field->TryDiv(*regy->field);

            Wrapper tmp = opHandler.EvaluateDivide(*regx, *regy, can_div);

            if (!can_div)
                return ThrowException(exception_shift + 0x05, "Operator / is not defined for types: " + std::string(regx->field->GetType().name()) + " and " + std::string(regy->field->GetType().name()) + ".");

            regx->field->Set(*tmp.field); // Todo: Is this correct? Should we copy the value of the sum to regx? Or copy it as a new wrapper?
        }
        void YVM::I_MOD(OVO::Instruction::ARG arg1, OVO::Instruction::ARG arg2)
        {
            // Usage:
            // MOD REGX, REGY
            const int exception_shift = 0x0;

            Wrapper *regx;

            if (arg1.mode != OVO::Instruction::ARG::MODE::REG)
                return ThrowException(exception_shift + 0x1, "MOV arguments do not fit standard!");

            bool selection = SelectRegister(arg1.value, regx);
            if (!selection)
                return ThrowException(exception_shift + 0x2, "MOV arguments do not fit standard! Current value is: " + std::to_string(arg1.value) + ".");

            Wrapper *regy;

            if (arg2.mode != OVO::Instruction::ARG::MODE::REG)
                return ThrowException(exception_shift + 0x1, "MOV arguments do not fit standard!");

            selection = SelectRegister(arg2.value, regy);
            if (!selection)
                return ThrowException(exception_shift + 0x2, "MOV arguments do not fit standard! Current value is: " + std::to_string(arg1.value) + ".");

            bool can_mod = regx->field->TryMod(*regy->field);

            Wrapper tmp = opHandler.EvaluateModulo(*regx, *regy, can_mod);

            if (!can_mod)
                return ThrowException(exception_shift + 0x05, "Operator % is not defined for types: " + std::string(regx->field->GetType().name()) + " and " + std::string(regy->field->GetType().name()) + ".");

            regx->field->Set(*tmp.field); // Todo: Is this correct? Should we copy the value of the sum to regx? Or copy it as a new wrapper?
        }
        void YVM::I_AND(OVO::Instruction::ARG arg1, OVO::Instruction::ARG arg2)
        {
            // Usage:
            // AND REGX, REGY
            const int exception_shift = 0x0;

            Wrapper *regx;

            if (arg1.mode != OVO::Instruction::ARG::MODE::REG)
                return ThrowException(exception_shift + 0x1, "MOV arguments do not fit standard!");

            bool selection = SelectRegister(arg1.value, regx);
            if (!selection)
                return ThrowException(exception_shift + 0x2, "MOV arguments do not fit standard! Current value is: " + std::to_string(arg1.value) + ".");

            Wrapper *regy;

            if (arg2.mode != OVO::Instruction::ARG::MODE::REG)
                return ThrowException(exception_shift + 0x1, "MOV arguments do not fit standard!");

            selection = SelectRegister(arg2.value, regy);
            if (!selection)
                return ThrowException(exception_shift + 0x2, "MOV arguments do not fit standard! Current value is: " + std::to_string(arg1.value) + ".");

            bool can_and = regx->field->TryAnd(*regy->field);

            Wrapper tmp = opHandler.EvaluateAnd(*regx, *regy, can_and);

            if (!can_and)
                return ThrowException(exception_shift + 0x05, "Operator & is not defined for types: " + std::string(regx->field->GetType().name()) + " and " + std::string(regy->field->GetType().name()) + ".");

            regx->field->Set(*tmp.field); // Todo: Is this correct? Should we copy the value of the sum to regx? Or copy it as a new wrapper?
        }
        void YVM::I_OR(OVO::Instruction::ARG arg1, OVO::Instruction::ARG arg2)
        {
            // Usage:
            // OR REGX, REGY
            const int exception_shift = 0x0;

            Wrapper *regx;

            if (arg1.mode != OVO::Instruction::ARG::MODE::REG)
                return ThrowException(exception_shift + 0x1, "MOV arguments do not fit standard!");

            bool selection = SelectRegister(arg1.value, regx);
            if (!selection)
                return ThrowException(exception_shift + 0x2, "MOV arguments do not fit standard! Current value is: " + std::to_string(arg1.value) + ".");

            Wrapper *regy;

            if (arg2.mode != OVO::Instruction::ARG::MODE::REG)
                return ThrowException(exception_shift + 0x1, "MOV arguments do not fit standard!");

            selection = SelectRegister(arg2.value, regy);
            if (!selection)
                return ThrowException(exception_shift + 0x2, "MOV arguments do not fit standard! Current value is: " + std::to_string(arg1.value) + ".");

            bool can_or = regx->field->TryOr(*regy->field);

            Wrapper tmp = opHandler.EvaluateOr(*regx, *regy, can_or);

            if (!can_or)
                return ThrowException(exception_shift + 0x05, "Operator & is not defined for types: " + std::string(regx->field->GetType().name()) + " and " + std::string(regy->field->GetType().name()) + ".");

            regx->field->Set(tmp.field); // Todo: Is this correct? Should we copy the value of the sum to regx? Or copy it as a new wrapper?
        }
        void YVM::I_CAST(OVO::Instruction::ARG arg1, OVO::Instruction::ARG arg2)
        {
            // Usage:
            // CAST REGX, REGY
            // CAST REGX, symbol where symbol contains the index of an elementary type
            // CAST REGX, data where data contains the string 
            const int exception_shift = 0x9;
            Wrapper *regx;

            if (arg1.mode != OVO::Instruction::ARG::MODE::REG)
                return ThrowException(exception_shift + 0x01, "MOV arguments do not fit standard!");

            bool selection = SelectRegister(arg1.value, regx);
            if (!selection)
                return ThrowException(exception_shift + 0x02, "MOV arguments do not fit standard! Current value is: " + std::to_string(arg1.value) + ".");

            if (!regx->field->Valid())
                return ThrowException(exception_shift + 0x02, "Cannot cast from void!");
            switch (arg2.mode)
            {
            case OVO::Instruction::ARG::MODE::REG:
            {

                Wrapper *regy;

                bool selection = SelectRegister(arg2.value, regy);
                if (!selection)
                    return ThrowException(exception_shift + 0x02, "MOV arguments do not fit standard! Current value is: " + std::to_string(arg1.value) + ".");

                if (!regy->field->Valid())
                    return ThrowException(exception_shift + 0x02, "Cannot cast to void!");
                
                bool cast_result = false;
                Wrapper wrapper = opHandler.EvaluateCast(*regx, regy->field->GetType(), cast_result);

                if (!cast_result)
                    return ThrowException(exception_shift + 0x04, "Cannot cast between the two types");
                
                *regx = wrapper;
                return;
            }
            case OVO::Instruction::ARG::MODE::SYMBOL:
            {
                switch (arg2.value)
                {
                case 0x00:
                {
                    return ThrowException(exception_shift + 0x03, "Cannot cast to void!");
                }
                case 0x01:
                {
                    bool cast_result = false;
                    Wrapper wrapper = opHandler.EvaluateCast(*regx, typeid(int), cast_result);
                    if (!cast_result)
                        return ThrowException(exception_shift + 0x04, "Cannot cast between the two types");
                    *regx = wrapper;
                    return;
                }
                case 0x02:
                {
                    bool cast_result = false;
                    Wrapper wrapper = opHandler.EvaluateCast(*regx, typeid(unsigned int), cast_result);
                    if (!cast_result)
                        return ThrowException(exception_shift + 0x04, "Cannot cast between the two types");
                    *regx = wrapper;
                    return;
                }
                case 0x03:
                {
                    bool cast_result = false;
                    Wrapper wrapper = opHandler.EvaluateCast(*regx, typeid(long), cast_result);
                    if (!cast_result)
                        return ThrowException(exception_shift + 0x04, "Cannot cast between the two types");
                    *regx = wrapper;
                    return;
                }
                case 0x04:
                {
                    bool cast_result = false;
                    Wrapper wrapper = opHandler.EvaluateCast(*regx, typeid(unsigned long), cast_result);
                    if (!cast_result)
                        return ThrowException(exception_shift + 0x04, "Cannot cast between the two types");
                    *regx = wrapper;
                    return;
                }
                case 0x05:
                {
                    bool cast_result = false;
                    Wrapper wrapper = opHandler.EvaluateCast(*regx, typeid(float), cast_result);
                    if (!cast_result)
                        return ThrowException(exception_shift + 0x04, "Cannot cast between the two types");
                    *regx = wrapper;
                    return;
                }
                case 0x06:
                {
                    bool cast_result = false;
                    Wrapper wrapper = opHandler.EvaluateCast(*regx, typeid(double), cast_result);
                    if (!cast_result)
                        return ThrowException(exception_shift + 0x04, "Cannot cast between the two types");
                    *regx = wrapper;
                    return;
                }
                case 0x07:
                {
                    bool cast_result = false;
                    Wrapper wrapper = opHandler.EvaluateCast(*regx, typeid(bool), cast_result);
                    if (!cast_result)
                        return ThrowException(exception_shift + 0x04, "Cannot cast between the two types");
                    *regx = wrapper;
                    return;
                }
                case 0x08:
                {
                    bool cast_result = false;
                    Wrapper wrapper = opHandler.EvaluateCast(*regx, typeid(char), cast_result);
                    if (!cast_result)
                        return ThrowException(exception_shift + 0x04, "Cannot cast between the two types");
                    *regx = wrapper;
                    return;
                }
                case 0x09:
                {
                    bool cast_result = false;
                    Wrapper wrapper = opHandler.EvaluateCast(*regx, typeid(unsigned char), cast_result);
                    if (!cast_result)
                        return ThrowException(exception_shift + 0x04, "Cannot cast between the two types");
                    *regx = wrapper;
                    return;
                    ;
                }
                case 0x0A:
                {
                    bool cast_result = false;
                    Wrapper wrapper = opHandler.EvaluateCast(*regx, typeid(std::string), cast_result);
                    if (!cast_result)
                        return ThrowException(exception_shift + 0x04, "Cannot cast between the two types");
                    *regx = wrapper;
                    return;
                }
                default:
                {
                    return ThrowException(exception_shift + 0x03, "MOV arguments do not fit standard!");
                }
                }
            }
            default:
            {
                return ThrowException(exception_shift + 0x0B, "MOV arguments do not fit standard!");
            }
            }
        }
        void YVM::I_RECAST(OVO::Instruction::ARG arg1, OVO::Instruction::ARG arg2)
        {
            const int exception_shift = 0x9;
            Wrapper *regx;

            if (arg1.mode != OVO::Instruction::ARG::MODE::REG)
                return ThrowException(exception_shift + 0x01, "MOV arguments do not fit standard!");

            bool selection = SelectRegister(arg1.value, regx);
            if (!selection)
                return ThrowException(exception_shift + 0x02, "MOV arguments do not fit standard! Current value is: " + std::to_string(arg1.value) + ".");

            if (!regx->field->Valid())
                return ThrowException(exception_shift + 0x02, "Cannot cast from void!");
            switch (arg2.mode)
            {
            case OVO::Instruction::ARG::MODE::REG:
            {
                Wrapper *regy;

                bool selection = SelectRegister(arg2.value, regy);
                if (!selection)
                    return ThrowException(exception_shift + 0x02, "MOV arguments do not fit standard! Current value is: " + std::to_string(arg1.value) + ".");

                if (!regy->field->Valid())
                    return ThrowException(exception_shift + 0x02, "Cannot cast to void!");
                
                regx->field->CastAs(*(regy->field));                
                return;
            }
            case OVO::Instruction::ARG::MODE::SYMBOL:
            {
                switch (arg2.value)
                {
                case 0x00:
                    return ThrowException(exception_shift + 0x03, "Cannot cast to void!");
                case 0x01:
                    regx->field->Cast<int>();
                    return;
                case 0x02:
                    regx->field->Cast<unsigned int>();
                    return;
                case 0x03:
                    regx->field->Cast<long>();
                    return;
                case 0x04:
                    regx->field->Cast<unsigned long>();
                    return;
                case 0x05:
                    regx->field->Cast<float>();
                    return;
                case 0x06:
                    regx->field->Cast<double>();
                    return;
                case 0x07:
                    regx->field->Cast<bool>();
                    return;
                case 0x08:
                    regx->field->Cast<char>();
                    return;
                case 0x09:
                    regx->field->Cast<unsigned char>();
                    return;
                case 0x0A:
                    regx->field->Cast<std::string>();
                    return;
                default:
                    return ThrowException(exception_shift + 0x03, "MOV arguments do not fit standard!");
                }
            }
            default:
            {
                return ThrowException(exception_shift + 0x0B, "MOV arguments do not fit standard!");
            }
            }
        }
        void YVM::I_NAMEL(OVO::Instruction::ARG arg1, OVO::Instruction::ARG arg2)
        {
            // Usage:
            // NAMEL regx, data where data contains the std::string of a name
            const int exception_shift = 0x9;
            Wrapper *regx;

            if (arg1.mode != OVO::Instruction::ARG::MODE::REG)
                return ThrowException(exception_shift + 0x01, "MOV arguments do not fit standard!");

            bool selection = SelectRegister(arg1.value, regx);
            if (!selection)
                return ThrowException(exception_shift + 0x02, "MOV arguments do not fit standard! Current value is: " + std::to_string(arg1.value) + ".");

            if (arg2.mode != OVO::Instruction::ARG::MODE::DATA)
                return ThrowException(exception_shift + 0x02, "NAMEL arguments do not fit standard!");

            auto result = RetrieveData(arg2.value);
            if (!result.ok)
                return ThrowException(exception_shift + 0x04, "DATA could not be found!");

            OVO::Data data = result.data;
            if (data.mode != OVO::Data::Mode::STRING)
                return ThrowException(exception_shift + 0x05, "MOV arguments do not fit standard!");

            std::string wrapperName = data.ToWrapper(data, manager).field->As<std::string>();

            auto reg_out = wrapperTable.Add(*regx);
            bool check = workingSymTable->Add(Memory::SymbolKey(wrapperName), Memory::SymbolValue(reg_out));

            if (!check)
            {
                wrapperTable.Erase(reg_out);
                return ThrowException(exception_shift + 0x06, "Failed to register the wrapper. That name is already in use.");
            }

            return;
        }
        void YVM::I_NAMEG(OVO::Instruction::ARG arg1, OVO::Instruction::ARG arg2)
        {
            // Usage:
            // NAMEG regx, data where data contains the std::string of a name
            const int exception_shift = 0x9;
            Wrapper *regx;

            if (arg1.mode != OVO::Instruction::ARG::MODE::REG)
                return ThrowException(exception_shift + 0x01, "MOV arguments do not fit standard!");

            bool selection = SelectRegister(arg1.value, regx);
            if (!selection)
                return ThrowException(exception_shift + 0x02, "MOV arguments do not fit standard! Current value is: " + std::to_string(arg1.value) + ".");

            if (arg2.mode != OVO::Instruction::ARG::MODE::DATA)
                return ThrowException(exception_shift + 0x02, "NAMEL arguments do not fit standard!");

            auto result = RetrieveData(arg2.value);
            if (!result.ok)
                return ThrowException(exception_shift + 0x04, "DATA could not be found!");

            OVO::Data data = result.data;
            if (data.mode != OVO::Data::Mode::STRING)
                return ThrowException(exception_shift + 0x05, "MOV arguments do not fit standard!");

            std::string wrapperName = data.ToWrapper(data, manager).field->As<std::string>();

            auto reg_out = wrapperTable.Add(*regx);
            bool check = workingSymTable->GlobalAdd(Memory::SymbolKey(wrapperName), Memory::SymbolValue(reg_out));

            if (!check)
            {
                wrapperTable.Erase(reg_out);
                return ThrowException(exception_shift + 0x06, "Failed to register the wrapper. That name is already in use.");
            }

            return;
        }
        void YVM::I_BRUP()
        {
            // Usage:
            // BRUP
            auto wrapper_list = workingSymTable->BranchUp();

            for (auto wrapper : wrapper_list)
            {
                wrapperTable.Erase(wrapper.second.key);
            }
        }
        void YVM::I_BRDW()
        {
            // Usage:
            // BRDW
            workingSymTable->BranchDown();
        }
        void YVM::I_BRHR(OVO::Instruction::ARG arg1)
        {
            // Usage:
            // BRHR data where data consist of a std::string with the name of a friend
            const int exception_shift = 0x0;
            if (arg1.mode != OVO::Instruction::ARG::MODE::DATA)
                return ThrowException(exception_shift + 0x02, "NAMEL arguments do not fit standard!");

            auto result = RetrieveData(arg1.value);
            if (!result.ok)
                return ThrowException(exception_shift + 0x04, "DATA could not be found!");

            OVO::Data data = result.data;
            if (data.mode != OVO::Data::Mode::STRING)
                return ThrowException(exception_shift + 0x05, "MOV arguments do not fit standard!");

            std::string friendName = data.ToWrapper(data, manager).field->As<std::string>();

            auto friend_result = workingSymTable->GetFriend(friendName);

            if (!friend_result.ok)
                return ThrowException(exception_shift + 0x06, "Could not find Object " + friendName + ".");

            workingSymTable = friend_result.result;
        }
        void YVM::I_RSBR()
        {
            // Usage:
            // RSBR
            workingSymTable = symTable;
        }
        void YVM::I_ZERO()
        {
            // Usage:
            // ZERO
            return;
        }
        void YVM::I_HALT()
        {
            // Usage:
            // HALT
            Running = false;
            status = Status::HALTED;
            Message = "Received Halt instruction!";
        }
    }
}