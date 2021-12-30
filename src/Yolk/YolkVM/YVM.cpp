/*#include "YVM.h"

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

        // Helper Functions

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
        bool YVM::ValidInstruction(OVO::Usize)
        {
            return true;
        }
        void YVM::JumpToInstruction(OVO::Usize)
        {
        }
        OVO::Usize YVM::CurrentInstruction()
        {
            return 0;
        }
        void YVM::ThrowException(int status, std::string Message)
        {
            std::cout << "ERROR (" + std::to_string(status) + "): " << Message << std::endl;
        }
        YVM::DataOutput YVM::RetrieveData(OVO::Instruction::CHUNK)
        {
            DataOutput out;
            out.ok = true;
            out.data = OVO::Data::GenerateData(std::string("myVariable"));
            return out;
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
            // Moves wrapper associated to arg2 onto arg1
            // Usage:
            //
            // MOV REGX, REGY; Where REGX and REGY are of type SYMBOL and whose value represent which register they represent.
            // MOV REGX, NAME; Where REGX is one of type SYMBOL and whose value represent which data is being target, and NAME is of type DATA and whose value is an integer to a position in the Data segment containing a string with the name of the wrapper to be moved onto the register.
            //

            const int exception_shift = 0x0;

            Wrapper *regx;

            if (arg1.mode != OVO::Instruction::ARG::MODE::SYMBOL)
                return ThrowException(exception_shift + 0x1, "MOV arguments do not fit standard!");

            bool selection = SelectRegister(arg1.value, regx);
            if (!selection)
                return ThrowException(exception_shift + 0x2, "MOV arguments do not fit standard! Current value is: " + std::to_string(arg1.value) + ".");

            switch (arg2.mode)
            {
            case OVO::Instruction::ARG::MODE::SYMBOL:
            {
                Wrapper *regy;

                selection = SelectRegister(arg2.value, regy);
                if (!selection)
                    return ThrowException(exception_shift + 0x3, "MOV arguments do not find standard!");

                *regx = *regy;

                return;
            }
            case OVO::Instruction::ARG::MODE::DATA:
            {
                auto result = RetrieveData(arg2.value);
                if (!result.ok)
                    return ThrowException(exception_shift + 0x4, "DATA could not be found!");
                OVO::Data data = result.data;
                if (data.mode != OVO::Data::Mode::STRING)
                    return ThrowException(exception_shift + 0x05, "MOV arguments do not fit standard!");

                std::string wrapperName = data.ToWrapper(data, manager).field->As<std::string>();

                auto symbol_result = workingSymTable->Get(Yolk::Memory::SymbolKey(wrapperName));

                if (!symbol_result.ok)
                    return ThrowException(exception_shift + 0x6, "Could not find variable named \"" + wrapperName + "\".");

                auto wrapper_info = wrapperTable.GetInfo(symbol_result.value.key);

                if (!wrapper_info.alive)
                    return ThrowException(exception_shift + 0x07, "Could not find variable named \"" + wrapperName + "\". It has already been deleted.");
                if (wrapper_info.wrapperType != WrapperType::FieldWrapper)
                    return ThrowException(exception_shift + 0x8, "Wrapper named \"" + wrapperName + "\" is a not field!");

                *regx = wrapperTable.CopyField(symbol_result.value.key);

                return;
            }
            default:
            {
                return ThrowException(exception_shift + 0x9, "MOV arguments do not fit standard!");
            }
            }
        }
        void YVM::I_COPY(OVO::Instruction::ARG arg1, OVO::Instruction::ARG arg2)
        {
            const int exception_shift = 0x0;

            Wrapper *regx;

            if (arg1.mode != OVO::Instruction::ARG::MODE::SYMBOL)
                return ThrowException(exception_shift + 0x1, "MOV arguments do not fit standard!");

            bool selection = SelectRegister(arg1.value, regx);
            if (!selection)
                return ThrowException(exception_shift + 0x2, "MOV arguments do not fit standard! Current value is: " + std::to_string(arg1.value) + ".");

            switch (arg2.mode)
            {
            case OVO::Instruction::ARG::MODE::SYMBOL:
            {
                Wrapper *regy;

                selection = SelectRegister(arg2.value, regy);
                if (!selection)
                    return ThrowException(exception_shift + 0x3, "MOV arguments do not find standard!");

                bool copy_result = regx->field->Copy(*(regy->field));
                if (!copy_result)
                    return ThrowException(exception_shift + 0x04, "Failed to copy content onto register.");
                return;
            }
            case OVO::Instruction::ARG::MODE::DATA:
            {
                auto result = RetrieveData(arg2.value);
                if (!result.ok)
                    return ThrowException(exception_shift + 0x4, "DATA could not be found!");
                OVO::Data data = result.data;

                Wrapper tmp = OVO::Data::ToWrapper(data, manager);

                bool copy_result = regx->field->Copy(*(tmp.field));

                if (!copy_result)
                    return ThrowException(exception_shift + 0x04, "Failed to copy content onto register.");
                return;
            }
            default:
            {
                return ThrowException(exception_shift + 0x9, "MOV arguments do not fit standard!");
            }
            }
        }
        void YVM::I_CLONE(OVO::Instruction::ARG arg1, OVO::Instruction::ARG arg2)
        {
            // Usage:
            //
            // CLONE REGX, TYPE;  Where REGX is of type SYMBOL and whose value represent which register is being target, and TYPE is of type SYMBOL and whose value represent which type is being target. Current types are: 0x0 VOID, 0x1 INT, 0x2 UINT, 0x3 LONG, 0x4 ULONG, 0x5 FLOAT, 0x6 DOUBLE, 0x7 BOOL, 0x8 CHAR, 0x9 UCHAR, 0xA STRING
            //
            // CLONE REGX, NAME; Where REGX is one of type SYMBOL and whose value represent which data is being target, and NAME is of type DATA and whose value is an integer to a position in the Data segment containing a string with the name of the wrapper to be moved onto the register.
            //
            //

            const int exception_shift = 0x9;
            Wrapper *regx;

            if (arg1.mode != OVO::Instruction::ARG::MODE::SYMBOL)
                return ThrowException(exception_shift + 0x01, "MOV arguments do not fit standard!");

            bool selection = SelectRegister(arg1.value, regx);
            if (!selection)
                return ThrowException(exception_shift + 0x02, "MOV arguments do not fit standard! Current value is: " + std::to_string(arg1.value) + ".");

            switch (arg2.mode)
            {
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
                    return ThrowException(exception_shift + 0x03, "MOV arguments do not fit standard!");
                }
            }
            case OVO::Instruction::ARG::MODE::DATA:
            {
                auto result = RetrieveData(arg2.value);
                if (!result.ok)
                    return ThrowException(exception_shift + 0x04, "DATA could not be found!");
                OVO::Data data = result.data;
                if (data.mode != OVO::Data::Mode::STRING)
                    return ThrowException(exception_shift + 0x05, "MOV arguments do not fit standard!");

                std::string wrapperName = data.ToWrapper(data, manager).field->As<std::string>();

                auto symbol_result = symTable->Get(Yolk::Memory::SymbolKey(wrapperName));

                if (!symbol_result.ok)
                    return ThrowException(exception_shift + 0x06, "Could not find variable named \"" + wrapperName + "\".");

                auto wrapper_info = wrapperTable.GetInfo(symbol_result.value.key);

                if (!wrapper_info.alive)
                    return ThrowException(exception_shift + 0x07, "Could not find variable named \"" + wrapperName + "\". It has already been deleted.");
                if (wrapper_info.wrapperType != WrapperType::FieldWrapper)
                    return ThrowException(exception_shift + 0x08, "Wrapper named \"" + wrapperName + "\" is not a field.");

                Wrapper original = wrapperTable.CopyField(symbol_result.value.key);

                auto cbv_out = manager.CopyByValue(original);

                if (cbv_out.status == -1)
                    return ThrowException(exception_shift + 0x09, "Attempted to copy a method wrapper by value!");
                else if (cbv_out.status == -2)
                    return ThrowException(exception_shift + 0x0A, "Could not find object in memory!");

                *regx = cbv_out.wrapper;

                return;
            }
            default:
            {
                return ThrowException(exception_shift + 0x0B, "MOV arguments do not fit standard!");
            }
            }
        }
        void YVM::I_MOVM(OVO::Instruction::ARG arg1)
        {
            const int exception_shift = 0xAA;
            if (arg1.mode != OVO::Instruction::ARG::MODE::DATA)
                return ThrowException(exception_shift + 0x1, "MOVM arguments do not fit standard!");

            auto result = RetrieveData(arg1.value);

            if (!result.ok)
                return ThrowException(exception_shift + 0x02, "DATA could not be found!");

            std::string method_name = OVO::Data::ToWrapper(result.data, manager).field->As<std::string>();

            auto symbol_result = workingSymTable->Get(Yolk::Memory::SymbolKey(method_name));

            if (!symbol_result.ok)
                return ThrowException(exception_shift + 0x03, "Could not find method named \"" + method_name + "\".");

            auto wrapper_info = wrapperTable.GetInfo(symbol_result.value.key);

            if (!wrapper_info.alive)
                return ThrowException(exception_shift + 0x03, "Could not find method named \"" + method_name + "\". It has already been deleted.");
            if (wrapper_info.wrapperType != WrapperType::MethodWrapper)
                return ThrowException(exception_shift + 0x04, "Wrapper named \"" + method_name + "\" is not a method.");

            MethodWrapper func = wrapperTable.CopyMethod(symbol_result.value.key);

            mreg = func;

            return;
        }
        void YVM::I_CALLM()
        {
            const int exception_shift = 0x00;
            if (!mreg.IsValid())
                return ThrowException(exception_shift + 0x01, "Method register is not valid.");

            auto result = mreg.Invoke(argreg);

            if (!result.ok)
                return ThrowException(exception_shift + 0x02, "Failed to invoke method: " + result.Message);

            regout = result.output;
        }
        void YVM::I_PUSHAR(OVO::Instruction::ARG arg1)
        {
            const int exception_shift = 0x9;
            Wrapper *regx;

            if (arg1.mode != OVO::Instruction::ARG::MODE::SYMBOL)
                return ThrowException(exception_shift + 0x01, "MOV arguments do not fit standard!");

            bool selection = SelectRegister(arg1.value, regx);
            if (!selection)
                return ThrowException(exception_shift + 0x02, "MOV arguments do not fit standard! Current value is: " + std::to_string(arg1.value) + ".");

            argreg.push_back(*regx);
        }
        void YVM::I_POPAR(OVO::Instruction::ARG arg1)
        {
            const int exception_shift = 0x9;
            if (arg1.mode == OVO::Instruction::ARG::MODE::SYMBOL)
            {
                Wrapper *regx;

                if (arg1.mode != OVO::Instruction::ARG::MODE::SYMBOL)
                    return ThrowException(exception_shift + 0x01, "MOV arguments do not fit standard!");

                bool selection = SelectRegister(arg1.value, regx);
                if (!selection)
                    return ThrowException(exception_shift + 0x01, "MOV arguments do not fit standard!");

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
            argreg.clear();
            return;
        }
        void YVM::I_PUSH(OVO::Instruction::ARG arg1)
        {
            const int exception_shift = 0x9;
            Wrapper *regx;

            if (arg1.mode != OVO::Instruction::ARG::MODE::SYMBOL)
                return ThrowException(exception_shift + 0x01, "MOV arguments do not fit standard!");

            bool selection = SelectRegister(arg1.value, regx);
            if (!selection)
                return ThrowException(exception_shift + 0x02, "MOV arguments do not fit standard! Current value is: " + std::to_string(arg1.value) + ".");

            stack.push_back(*regx);
        }
        void YVM::I_POP(OVO::Instruction::ARG arg1)
        {
            const int exception_shift = 0x9;
            if (arg1.mode == OVO::Instruction::ARG::MODE::SYMBOL)
            {
                Wrapper *regx;

                if (arg1.mode != OVO::Instruction::ARG::MODE::SYMBOL)
                    return ThrowException(exception_shift + 0x01, "MOV arguments do not fit standard!");

                bool selection = SelectRegister(arg1.value, regx);
                if (!selection)
                    return ThrowException(exception_shift + 0x01, "MOV arguments do not fit standard!");

                if (argreg.size() == 0)
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
            stack.clear();
            return;
        }
        void YVM::I_CMP(OVO::Instruction::ARG arg1)
        {
            const int exception_shift = 0x9;
            Wrapper *regx;

            if (arg1.mode != OVO::Instruction::ARG::MODE::SYMBOL)
                return ThrowException(exception_shift + 0x01, "MOV arguments do not fit standard!");

            bool selection = SelectRegister(arg1.value, regx);
            if (!selection)
                return ThrowException(exception_shift + 0x02, "MOV arguments do not fit standard!");

            if (!regx->field->Valid())
                return ThrowException(exception_shift + 0x03, "Wrapper is not valid!");

            // Todo: More checks in here. Not everything can be cast as bool.
            // Ideally, one can create a method in the Typed Field where it returns an error if the type can not be cast to bool.
            cmpreg = regx->field->As<bool>();
            return;
        }
        void YVM::I_CMPEQ(OVO::Instruction::ARG arg1, OVO::Instruction::ARG arg2)
        {

            const int exception_shift = 0x0;

            Wrapper *regx;

            if (arg1.mode != OVO::Instruction::ARG::MODE::SYMBOL)
                return ThrowException(exception_shift + 0x1, "MOV arguments do not fit standard!");

            bool selection = SelectRegister(arg1.value, regx);
            if (!selection)
                return ThrowException(exception_shift + 0x2, "MOV arguments do not fit standard! Current value is: " + std::to_string(arg1.value) + ".");

            switch (arg2.mode)
            {
            case OVO::Instruction::ARG::MODE::SYMBOL:
            {
                Wrapper *regy;

                selection = SelectRegister(arg2.value, regy);
                if (!selection)
                    return ThrowException(exception_shift + 0x3, "MOV arguments do not find standard!");

                if (regy->field->GetType() == regx->field->GetType())
                {
                    cmpreg = regy->field->Compare(*(regx->field));
                    return;
                }
                bool can_evaluate = false;
                Wrapper cmp_result = opHandler.EvaluateEquality(*regx, *regy, can_evaluate);

                if (!can_evaluate)
                    return ThrowException(exception_shift + 0x05, "Operator == is not defined for types: " + std::string(regx->field->GetType().name()) + " and " + std::string(regy->field->GetType().name()) + ".");

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

                if (tmp.field->GetType() == regx->field->GetType())
                {
                    cmpreg = tmp.field->Compare(*(regx->field));
                    return;
                }
                bool can_evaluate = false;
                Wrapper cmp_result = opHandler.EvaluateEquality(*regx, tmp, can_evaluate);

                if (!can_evaluate)
                    return ThrowException(exception_shift + 0x05, "Operator == is not defined for types: " + std::string(regx->field->GetType().name()) + " and " + std::string(tmp.field->GetType().name()) + ".");

                cmpreg = cmp_result.field->As<bool>();
                return;
            }
            default:
            {
                return ThrowException(exception_shift + 0x9, "MOV arguments do not fit standard!");
            }
            }
        }
        void YVM::I_CMPNEQ(OVO::Instruction::ARG arg1, OVO::Instruction::ARG arg2)
        {

            const int exception_shift = 0x0;

            Wrapper *regx;

            if (arg1.mode != OVO::Instruction::ARG::MODE::SYMBOL)
                return ThrowException(exception_shift + 0x1, "MOV arguments do not fit standard!");

            bool selection = SelectRegister(arg1.value, regx);
            if (!selection)
                return ThrowException(exception_shift + 0x2, "MOV arguments do not fit standard! Current value is: " + std::to_string(arg1.value) + ".");

            switch (arg2.mode)
            {
            case OVO::Instruction::ARG::MODE::SYMBOL:
            {
                Wrapper *regy;

                selection = SelectRegister(arg2.value, regy);
                if (!selection)
                    return ThrowException(exception_shift + 0x3, "MOV arguments do not find standard!");

                if (regy->field->GetType() == regx->field->GetType())
                {
                    cmpreg = !regy->field->Compare(*(regx->field));
                    return;
                }
                bool can_evaluate = false;
                Wrapper cmp_result = opHandler.EvaluateEquality(*regx, *regy, can_evaluate);

                if (!can_evaluate)
                    return ThrowException(exception_shift + 0x05, "Operator = is not defined for types: " + std::string(regx->field->GetType().name()) + " and " + std::string(regy->field->GetType().name()) + ".");

                cmpreg = !cmp_result.field->As<bool>();
                return;
            }
            case OVO::Instruction::ARG::MODE::DATA:
            {
                auto result = RetrieveData(arg2.value);
                if (!result.ok)
                    return ThrowException(exception_shift + 0x4, "DATA could not be found!");
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
                    return ThrowException(exception_shift + 0x05, "Operator = is not defined for types: " + std::string(regx->field->GetType().name()) + " and " + std::string(tmp.field->GetType().name()) + ".");

                cmpreg = !cmp_result.field->As<bool>();
                return;
            }
            default:
            {
                return ThrowException(exception_shift + 0x9, "MOV arguments do not fit standard!");
            }
            }
        }
        void YVM::I_CMPLS(OVO::Instruction::ARG arg1, OVO::Instruction::ARG arg2)
        {
            const int exception_shift = 0x0;

            Wrapper *regx;

            if (arg1.mode != OVO::Instruction::ARG::MODE::SYMBOL)
                return ThrowException(exception_shift + 0x1, "MOV arguments do not fit standard!");

            bool selection = SelectRegister(arg1.value, regx);
            if (!selection)
                return ThrowException(exception_shift + 0x2, "MOV arguments do not fit standard! Current value is: " + std::to_string(arg1.value) + ".");

            switch (arg2.mode)
            {
            case OVO::Instruction::ARG::MODE::SYMBOL:
            {
                Wrapper *regy;

                selection = SelectRegister(arg2.value, regy);
                if (!selection)
                    return ThrowException(exception_shift + 0x3, "MOV arguments do not find standard!");

                bool can_evaluate = false;
                Wrapper cmp_result = opHandler.EvaluateLessThan(*regx, *regy, can_evaluate);

                if (!can_evaluate)
                    return ThrowException(exception_shift + 0x05, "Operator < is not defined for types: " + std::string(regx->field->GetType().name()) + " and " + std::string(regy->field->GetType().name()) + ".");

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
            const int exception_shift = 0x0;

            Wrapper *regx;

            if (arg1.mode != OVO::Instruction::ARG::MODE::SYMBOL)
                return ThrowException(exception_shift + 0x1, "MOV arguments do not fit standard!");

            bool selection = SelectRegister(arg1.value, regx);
            if (!selection)
                return ThrowException(exception_shift + 0x2, "MOV arguments do not fit standard! Current value is: " + std::to_string(arg1.value) + ".");

            switch (arg2.mode)
            {
            case OVO::Instruction::ARG::MODE::SYMBOL:
            {
                Wrapper *regy;

                selection = SelectRegister(arg2.value, regy);
                if (!selection)
                    return ThrowException(exception_shift + 0x3, "MOV arguments do not find standard!");

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
            const int exception_shift = 0x0;

            Wrapper *regx;

            if (arg1.mode != OVO::Instruction::ARG::MODE::SYMBOL)
                return ThrowException(exception_shift + 0x1, "MOV arguments do not fit standard!");

            bool selection = SelectRegister(arg1.value, regx);
            if (!selection)
                return ThrowException(exception_shift + 0x2, "MOV arguments do not fit standard! Current value is: " + std::to_string(arg1.value) + ".");

            switch (arg2.mode)
            {
            case OVO::Instruction::ARG::MODE::SYMBOL:
            {
                Wrapper *regy;

                selection = SelectRegister(arg2.value, regy);
                if (!selection)
                    return ThrowException(exception_shift + 0x3, "MOV arguments do not find standard!");

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
            const int exception_shift = 0x0;

            Wrapper *regx;

            if (arg1.mode != OVO::Instruction::ARG::MODE::SYMBOL)
                return ThrowException(exception_shift + 0x1, "MOV arguments do not fit standard!");

            bool selection = SelectRegister(arg1.value, regx);
            if (!selection)
                return ThrowException(exception_shift + 0x2, "MOV arguments do not fit standard! Current value is: " + std::to_string(arg1.value) + ".");

            switch (arg2.mode)
            {
            case OVO::Instruction::ARG::MODE::SYMBOL:
            {
                Wrapper *regy;

                selection = SelectRegister(arg2.value, regy);
                if (!selection)
                    return ThrowException(exception_shift + 0x3, "MOV arguments do not find standard!");

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
            const int exception_shift = 0x00;
            if (cmpreg)
            {
                switch (arg1.mode)
                {
                case OVO::Instruction::ARG::MODE::SYMBOL:
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
                default:
                {
                    return ThrowException(exception_shift + 0x9, "MOV arguments do not fit standard!");
                }
                }
            }
        }
        void YVM::I_JNFALSE(OVO::Instruction::ARG arg1)
        {
            const int exception_shift = 0x00;
            if (!cmpreg)
            {
                switch (arg1.mode)
                {
                case OVO::Instruction::ARG::MODE::SYMBOL:
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
                default:
                {
                    return ThrowException(exception_shift + 0x9, "MOV arguments do not fit standard!");
                }
                }
            }
        }
        void YVM::I_JMP(OVO::Instruction::ARG arg1)
        {
            const int exception_shift = 0x00;
            switch (arg1.mode)
            {
            case OVO::Instruction::ARG::MODE::SYMBOL:
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
            default:
            {
                return ThrowException(exception_shift + 0x9, "MOV arguments do not fit standard!");
            }
            }
        }
        void YVM::I_CALL(OVO::Instruction::ARG arg1)
        {
            const int exception_shift = 0x00;

            auto current_instruction = manager.AllocateMemory<unsigned long int>(CurrentInstruction());
            stack.push_back(current_instruction);

            switch (arg1.mode)
            {
            case OVO::Instruction::ARG::MODE::SYMBOL:
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
            default:
            {
                return ThrowException(exception_shift + 0x9, "MOV arguments do not fit standard!");
            }
            }
        }
        void YVM::I_RET()
        {
            const int exception_shift = 0x00;
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
            const int exception_shift = 0x0;

            Wrapper *regx;

            if (arg1.mode != OVO::Instruction::ARG::MODE::SYMBOL)
                return ThrowException(exception_shift + 0x1, "MOV arguments do not fit standard!");

            bool selection = SelectRegister(arg1.value, regx);
            if (!selection)
                return ThrowException(exception_shift + 0x2, "MOV arguments do not fit standard! Current value is: " + std::to_string(arg1.value) + ".");

            Wrapper *regy;

            if (arg2.mode != OVO::Instruction::ARG::MODE::SYMBOL)
                return ThrowException(exception_shift + 0x1, "MOV arguments do not fit standard!");

            selection = SelectRegister(arg2.value, regy);
            if (!selection)
                return ThrowException(exception_shift + 0x2, "MOV arguments do not fit standard! Current value is: " + std::to_string(arg1.value) + ".");

            bool can_add = false;

            Wrapper tmp = opHandler.EvaluateAdd(*regx, *regy, can_add);

            if (!can_add)
                return ThrowException(exception_shift + 0x05, "Operator + is not defined for types: " + std::string(regx->field->GetType().name()) + " and " + std::string(regy->field->GetType().name()) + ".");

            *regx = tmp; // Todo: Is this correct? Should we copy the value of the sum to regx? Or copy it as a new wrapper?
        }
        void YVM::I_SUB(OVO::Instruction::ARG arg1, OVO::Instruction::ARG arg2)
        {
            const int exception_shift = 0x0;

            Wrapper *regx;

            if (arg1.mode != OVO::Instruction::ARG::MODE::SYMBOL)
                return ThrowException(exception_shift + 0x1, "MOV arguments do not fit standard!");

            bool selection = SelectRegister(arg1.value, regx);
            if (!selection)
                return ThrowException(exception_shift + 0x2, "MOV arguments do not fit standard! Current value is: " + std::to_string(arg1.value) + ".");

            Wrapper *regy;

            if (arg2.mode != OVO::Instruction::ARG::MODE::SYMBOL)
                return ThrowException(exception_shift + 0x1, "MOV arguments do not fit standard!");

            selection = SelectRegister(arg2.value, regy);
            if (!selection)
                return ThrowException(exception_shift + 0x2, "MOV arguments do not fit standard! Current value is: " + std::to_string(arg1.value) + ".");

            bool can_sub = false;

            Wrapper tmp = opHandler.EvaluateSubtract(*regx, *regy, can_sub);

            if (!can_sub)
                return ThrowException(exception_shift + 0x05, "Operator - is not defined for types: " + std::string(regx->field->GetType().name()) + " and " + std::string(regy->field->GetType().name()) + ".");

            *regx = tmp; // Todo: Is this correct? Should we copy the value of the sum to regx? Or copy it as a new wrapper?
        }
        void YVM::I_MUL(OVO::Instruction::ARG arg1, OVO::Instruction::ARG arg2)
        {
            const int exception_shift = 0x0;

            Wrapper *regx;

            if (arg1.mode != OVO::Instruction::ARG::MODE::SYMBOL)
                return ThrowException(exception_shift + 0x1, "MOV arguments do not fit standard!");

            bool selection = SelectRegister(arg1.value, regx);
            if (!selection)
                return ThrowException(exception_shift + 0x2, "MOV arguments do not fit standard! Current value is: " + std::to_string(arg1.value) + ".");

            Wrapper *regy;

            if (arg2.mode != OVO::Instruction::ARG::MODE::SYMBOL)
                return ThrowException(exception_shift + 0x1, "MOV arguments do not fit standard!");

            selection = SelectRegister(arg2.value, regy);
            if (!selection)
                return ThrowException(exception_shift + 0x2, "MOV arguments do not fit standard! Current value is: " + std::to_string(arg1.value) + ".");

            bool can_mul = false;

            Wrapper tmp = opHandler.EvaluateMultiply(*regx, *regy, can_mul);

            if (!can_mul)
                return ThrowException(exception_shift + 0x05, "Operator * is not defined for types: " + std::string(regx->field->GetType().name()) + " and " + std::string(regy->field->GetType().name()) + ".");

            *regx = tmp; // Todo: Is this correct? Should we copy the value of the sum to regx? Or copy it as a new wrapper?
        }
        void YVM::I_DIV(OVO::Instruction::ARG arg1, OVO::Instruction::ARG arg2)
        {
            const int exception_shift = 0x0;

            Wrapper *regx;

            if (arg1.mode != OVO::Instruction::ARG::MODE::SYMBOL)
                return ThrowException(exception_shift + 0x1, "MOV arguments do not fit standard!");

            bool selection = SelectRegister(arg1.value, regx);
            if (!selection)
                return ThrowException(exception_shift + 0x2, "MOV arguments do not fit standard! Current value is: " + std::to_string(arg1.value) + ".");

            Wrapper *regy;

            if (arg2.mode != OVO::Instruction::ARG::MODE::SYMBOL)
                return ThrowException(exception_shift + 0x1, "MOV arguments do not fit standard!");

            selection = SelectRegister(arg2.value, regy);
            if (!selection)
                return ThrowException(exception_shift + 0x2, "MOV arguments do not fit standard! Current value is: " + std::to_string(arg1.value) + ".");

            bool can_div = false;

            Wrapper tmp = opHandler.EvaluateDivide(*regx, *regy, can_div);

            if (!can_div)
                return ThrowException(exception_shift + 0x05, "Operator / is not defined for types: " + std::string(regx->field->GetType().name()) + " and " + std::string(regy->field->GetType().name()) + ".");

            *regx = tmp; // Todo: Is this correct? Should we copy the value of the sum to regx? Or copy it as a new wrapper?
        }
        void YVM::I_MOD(OVO::Instruction::ARG arg1, OVO::Instruction::ARG arg2)
        {
            const int exception_shift = 0x0;

            Wrapper *regx;

            if (arg1.mode != OVO::Instruction::ARG::MODE::SYMBOL)
                return ThrowException(exception_shift + 0x1, "MOV arguments do not fit standard!");

            bool selection = SelectRegister(arg1.value, regx);
            if (!selection)
                return ThrowException(exception_shift + 0x2, "MOV arguments do not fit standard! Current value is: " + std::to_string(arg1.value) + ".");

            Wrapper *regy;

            if (arg2.mode != OVO::Instruction::ARG::MODE::SYMBOL)
                return ThrowException(exception_shift + 0x1, "MOV arguments do not fit standard!");

            selection = SelectRegister(arg2.value, regy);
            if (!selection)
                return ThrowException(exception_shift + 0x2, "MOV arguments do not fit standard! Current value is: " + std::to_string(arg1.value) + ".");

            bool can_mod = false;

            Wrapper tmp = opHandler.EvaluateModulo(*regx, *regy, can_mod);

            if (!can_mod)
                return ThrowException(exception_shift + 0x05, "Operator % is not defined for types: " + std::string(regx->field->GetType().name()) + " and " + std::string(regy->field->GetType().name()) + ".");

            *regx = tmp; // Todo: Is this correct? Should we copy the value of the sum to regx? Or copy it as a new wrapper?
        }
        void YVM::I_AND(OVO::Instruction::ARG arg1, OVO::Instruction::ARG arg2)
        {
            const int exception_shift = 0x0;

            Wrapper *regx;

            if (arg1.mode != OVO::Instruction::ARG::MODE::SYMBOL)
                return ThrowException(exception_shift + 0x1, "MOV arguments do not fit standard!");

            bool selection = SelectRegister(arg1.value, regx);
            if (!selection)
                return ThrowException(exception_shift + 0x2, "MOV arguments do not fit standard! Current value is: " + std::to_string(arg1.value) + ".");

            Wrapper *regy;

            if (arg2.mode != OVO::Instruction::ARG::MODE::SYMBOL)
                return ThrowException(exception_shift + 0x1, "MOV arguments do not fit standard!");

            selection = SelectRegister(arg2.value, regy);
            if (!selection)
                return ThrowException(exception_shift + 0x2, "MOV arguments do not fit standard! Current value is: " + std::to_string(arg1.value) + ".");

            bool can_and = false;

            Wrapper tmp = opHandler.EvaluateAnd(*regx, *regy, can_and);

            if (!can_and)
                return ThrowException(exception_shift + 0x05, "Operator & is not defined for types: " + std::string(regx->field->GetType().name()) + " and " + std::string(regy->field->GetType().name()) + ".");

            *regx = tmp; // Todo: Is this correct? Should we copy the value of the sum to regx? Or copy it as a new wrapper?
        }
        void YVM::I_OR(OVO::Instruction::ARG arg1, OVO::Instruction::ARG arg2)
        {
            const int exception_shift = 0x0;

            Wrapper *regx;

            if (arg1.mode != OVO::Instruction::ARG::MODE::SYMBOL)
                return ThrowException(exception_shift + 0x1, "MOV arguments do not fit standard!");

            bool selection = SelectRegister(arg1.value, regx);
            if (!selection)
                return ThrowException(exception_shift + 0x2, "MOV arguments do not fit standard! Current value is: " + std::to_string(arg1.value) + ".");

            Wrapper *regy;

            if (arg2.mode != OVO::Instruction::ARG::MODE::SYMBOL)
                return ThrowException(exception_shift + 0x1, "MOV arguments do not fit standard!");

            selection = SelectRegister(arg2.value, regy);
            if (!selection)
                return ThrowException(exception_shift + 0x2, "MOV arguments do not fit standard! Current value is: " + std::to_string(arg1.value) + ".");

            bool can_or = false;

            Wrapper tmp = opHandler.EvaluateOr(*regx, *regy, can_or);

            if (!can_or)
                return ThrowException(exception_shift + 0x05, "Operator & is not defined for types: " + std::string(regx->field->GetType().name()) + " and " + std::string(regy->field->GetType().name()) + ".");

            *regx = tmp; // Todo: Is this correct? Should we copy the value of the sum to regx? Or copy it as a new wrapper?
        }
        void YVM::I_CAST(OVO::Instruction::ARG arg1, OVO::Instruction::ARG arg2)
        {
            const int exception_shift = 0x9;
            Wrapper *regx;

            if (arg1.mode != OVO::Instruction::ARG::MODE::SYMBOL)
                return ThrowException(exception_shift + 0x01, "MOV arguments do not fit standard!");

            bool selection = SelectRegister(arg1.value, regx);
            if (!selection)
                return ThrowException(exception_shift + 0x02, "MOV arguments do not fit standard! Current value is: " + std::to_string(arg1.value) + ".");

            if (!regx->field->Valid())
                return ThrowException(exception_shift + 0x02, "Cannot cast from void!");
            switch (arg2.mode)
            {
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
            case OVO::Instruction::ARG::MODE::DATA:
            {
                auto result = RetrieveData(arg2.value);
                if (!result.ok)
                    return ThrowException(exception_shift + 0x04, "DATA could not be found!");
                OVO::Data data = result.data;
                if (data.mode != OVO::Data::Mode::STRING)
                    return ThrowException(exception_shift + 0x05, "MOV arguments do not fit standard!");

                std::string wrapperName = data.ToWrapper(data, manager).field->As<std::string>();

                auto symbol_result = workingSymTable->Get(Yolk::Memory::SymbolKey(wrapperName));

                if (!symbol_result.ok)
                    return ThrowException(exception_shift + 0x06, "Could not find variable named \"" + wrapperName + "\".");

                auto wrapper_info = wrapperTable.GetInfo(symbol_result.value.key);

                if (!wrapper_info.alive)
                    return ThrowException(exception_shift + 0x07, "Could not find variable named \"" + wrapperName + "\". It has already been deleted.");
                if (wrapper_info.wrapperType != WrapperType::FieldWrapper)
                    return ThrowException(exception_shift + 0x08, "Wrapper named \"" + wrapperName + "\" is not a field.");

                Wrapper original = wrapperTable.CopyField(symbol_result.value.key);

                if (!original.field->Valid())
                    return ThrowException(exception_shift + 0x03, "Cannot cast to void!");

                bool cast_result = false;
                Wrapper wrapper = opHandler.EvaluateCast(*regx, original.field->GetType(), cast_result);
                if (!cast_result)
                    return ThrowException(exception_shift + 0x04, "Cannot cast between the two types");
                *regx = wrapper;
                return;
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

            if (arg1.mode != OVO::Instruction::ARG::MODE::SYMBOL)
                return ThrowException(exception_shift + 0x01, "MOV arguments do not fit standard!");

            bool selection = SelectRegister(arg1.value, regx);
            if (!selection)
                return ThrowException(exception_shift + 0x02, "MOV arguments do not fit standard! Current value is: " + std::to_string(arg1.value) + ".");

            if (!regx->field->Valid())
                return ThrowException(exception_shift + 0x02, "Cannot cast from void!");
            switch (arg2.mode)
            {
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
            case OVO::Instruction::ARG::MODE::DATA:
            {
                auto result = RetrieveData(arg2.value);
                if (!result.ok)
                    return ThrowException(exception_shift + 0x04, "DATA could not be found!");
                OVO::Data data = result.data;
                if (data.mode != OVO::Data::Mode::STRING)
                    return ThrowException(exception_shift + 0x05, "MOV arguments do not fit standard!");

                std::string wrapperName = data.ToWrapper(data, manager).field->As<std::string>();

                auto symbol_result = workingSymTable->Get(Yolk::Memory::SymbolKey(wrapperName));

                if (!symbol_result.ok)
                    return ThrowException(exception_shift + 0x06, "Could not find variable named \"" + wrapperName + "\".");

                auto wrapper_info = wrapperTable.GetInfo(symbol_result.value.key);

                if (!wrapper_info.alive)
                    return ThrowException(exception_shift + 0x07, "Could not find variable named \"" + wrapperName + "\". It has already been deleted.");
                if (wrapper_info.wrapperType != WrapperType::FieldWrapper)
                    return ThrowException(exception_shift + 0x08, "Wrapper named \"" + wrapperName + "\" is not a field.");

                Wrapper original = wrapperTable.CopyField(symbol_result.value.key);

                if (!original.field->Valid())
                    return ThrowException(exception_shift + 0x03, "Cannot cast to void!");

                regx->field->CastAs(*(original.field));
                return;
            }
            default:
            {
                return ThrowException(exception_shift + 0x0B, "MOV arguments do not fit standard!");
            }
            }
        }
        void YVM::I_NAMEL(OVO::Instruction::ARG arg1, OVO::Instruction::ARG arg2)
        {
            const int exception_shift = 0x9;
            Wrapper *regx;

            if (arg1.mode != OVO::Instruction::ARG::MODE::SYMBOL)
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
            const int exception_shift = 0x9;
            Wrapper *regx;

            if (arg1.mode != OVO::Instruction::ARG::MODE::SYMBOL)
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
            auto wrapper_list = workingSymTable->BranchUp();

            for (auto wrapper : wrapper_list)
            {
                wrapperTable.Erase(wrapper.second.key);
            }
        }
        void YVM::I_BRDW()
        {
            workingSymTable->BranchDown();
        }
        void YVM::I_BRHR(OVO::Instruction::ARG arg1)
        {
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
            workingSymTable = symTable;
        }
        void YVM::I_ZERO()
        {
            return;
        }
        void YVM::I_HALT()
        {
            Running = false;
            status = Status::HALTED;
            Message = "Received Halt instruction!";
        }
    }
}*/