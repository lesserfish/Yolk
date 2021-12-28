class OP:
    def __init__(self, _n, _name, _op):
        self.n = _n
        self.name = _name
        self.operation = _op
    n : int
    name : str
    operation : str



def GetMapDefinition(op : OP):
    if(op.n == 2):
        output = "std::map<PAIR, BINARY> " + op.name.lower() + "Map;\n"
        return output;
    elif(op.n == 1):
        output = "std::map<SINGLE, UNARY> " + op.name.lower() + "Map;\n"
        return output;

def GetEvaluateDefinition(op : OP):
    if(op.n == 2):
        output          = "Wrapper Evaluate"+op.name+"(Wrapper lhs, Wrapper rhs, bool& status_output);\n"
        output = output + "\t\t\tWrapper Evaluate"+op.name+"(Wrapper lhs, Wrapper rhs);\n"
        return output;
    elif(op.n == 1):
        output          = "Wrapper Evaluate"+op.name+"(Wrapper lhs, bool& status_output);\n"
        output = output + "\t\t\tWrapper Evaluate"+op.name+"(Wrapper lhs);\n"
        return output;

def GetRegisterDefinition(op : OP):
    if(op.n == 2):
        output = "template <typename T, typename F> void Register"+op.name+"();\n";
        return output;
    elif(op.n == 1):
        output = "template <typename T> void Register"+op.name+"();\n";
        return output;

def GetRegisterFunctionCode(op : OP):
    if(op.n == 2):
        output = """
        template<typename T, typename F>
        inline void Operator::Register{0}()
        {{
            auto f = [this](Wrapper lhs, Wrapper rhs)
            {{
                T lhst = lhs.field->As<T>();
                F rhsf = rhs.field->As<F>();
                Wrapper output = this->GetMemoryManager().AllocateMemory(lhst {1} rhsf);
                return output;
            }};
            PAIR pair(typeid(T), typeid(F));
            BINARY binary(f);
            {2}Map.insert(std::pair(pair, binary));
        }}
        """.format(op.name, op.operation, op.name.lower())
        return output;
    elif(op.n == 1):
        tmp = ""
        if(op.operation == "!"):
            tmp = "!lhst"
        elif(op.operation == "cast"):
            tmp = "(T)lhst"
        else:
            tmp = "lhst" + op.operation
        output = """
        template<typename T>
        inline void Operator::Register{0}()
        {{
            auto f = [this](Wrapper lhs)
            {{
                T lhst = lhs.field->As<T>();
                Wrapper output = this->GetMemoryManager().AllocateMemory({1});
                return output;
            }};
            SINGLE single(typeid(T));
            UNARY unary(f);

            {2}Map.insert(std::pair(single, unary));
        }}
        """.format(op.name, tmp, op.name.lower())
        return output;

def GetEvaluateCode(op : OP):
    if(op.n == 2):
        output = """
        inline Wrapper Operator::Evaluate{0}(Wrapper lhs, Wrapper rhs, bool& status_output)
        {{
            PAIR pair(lhs.field->GetType(), rhs.field->GetType());
            auto find_result = {1}Map.find(pair);

            if(find_result == {1}Map.end())
            {{
                status_output = false;
                return manager.AllocateMemory<void>();
            }}

            auto f = find_result->second;
            Wrapper out = f(lhs, rhs);
            status_output = true;
            return out;
        }}
        inline Wrapper Operator::Evaluate{0}(Wrapper lhs, Wrapper rhs)
        {{
            bool output;
            return Evaluate{0}(lhs, rhs, output);
        }}
        """.format(op.name, op.name.lower())
        return output;
    elif(op.n == 1):
        output = """
        inline Wrapper Operator::Evaluate{0}(Wrapper lhs, bool &status_output)
        {{
            SINGLE single(lhs.field->GetType());
            auto find_result = {1}Map.find(single);

            if(find_result == {1}Map.end())
            {{
                status_output = false;
                return manager.AllocateMemory<void>();
            }}

            auto f = find_result->second;
            Wrapper out = f(lhs);
            status_output = true;
            return out;

        }}
        inline Wrapper Operator::Evaluate{0}(Wrapper lhs)
        {{
            bool output;
            return Evaluate{0}(lhs, output);
        }}
        """.format(op.name, op.name.lower())
        return output;

template = """
#pragma once

#include "../Wrapper/Wrapper.h"
#include "../Memory/MemoryManager/MemoryManager.h"
#include <typeindex>
#include <functional>
#include <map>
#include <typeindex>
namespace Yolk
{{
    namespace VM
    {{
        class Operator
        {{
            using SINGLE = std::type_index;
            using PAIR = std::pair<std::type_index, std::type_index>;
            using UNARY = std::function<Wrapper(Wrapper)>;
            using BINARY = std::function<Wrapper(Wrapper, Wrapper)>;
            
            public:
            Operator(Memory::MemoryManager& _manager ) : manager(_manager){{}}
            Memory::MemoryManager& GetMemoryManager() const;
            Wrapper EvaluateCast(Wrapper lhs, std::type_index F, bool& status_output);
            Wrapper EvaluateCast(Wrapper lhs, std::type_index F);
            {1}
            template <typename T, typename F> void RegisterCast();
            {2}
            private:
            Memory::MemoryManager& manager;
            std::map<PAIR, UNARY> castMap;
            {0}
        }};
        inline Memory::MemoryManager& Operator::GetMemoryManager() const
        {{
            return manager;
        }}
        inline Wrapper Operator::EvaluateCast(Wrapper lhs, std::type_index F bool& status_output)
        {{
            PAIR pair(lhs.field->GetType(), F);
            auto find_result = castMap.find(pair);

            if(find_result == castMap.end())
            {{
                status_output = false;
                return manager.AllocateMemory<void>();
            }}

            auto f = find_result->second;
            Wrapper out = f(lhs);
            status_output = true;
            return out;
        }}
        inline Wrapper Operator::EvaluateCast(Wrapper lhs, std::type_index F)
        {{
            bool output;
            return EvaluateCast(lhs, F, output);
        }}
        {3}
        template<typename T, typename F>
        inline void Operator::RegisterCast()
        {{
            auto f = [this](Wrapper lhs)
            {{
                T lhst = lhs.field->As<T>();
                Wrapper output = this->GetMemoryManager().AllocateMemory(F(lhst));
                return output;
            }};
            PAIR pair(typeid(T), typeid(F));
            UNARY unary(f);
            castMap.insert(std::pair(pair, unary));
        }}
        {4}
    }}
}}
"""

OPList = list()
OPList.append(OP(2, "Add", "+"))
OPList.append(OP(2, "Subtract", "-"))
OPList.append(OP(2, "Multiply", "*"))
OPList.append(OP(2, "Divide", "/"))
OPList.append(OP(2, "Modulo", "%"))
#OPList.append(OP(2, "CAdd", "+="))
#OPList.append(OP(2, "CSubtract", "-="))
#OPList.append(OP(2, "CMultiply", "*="))
#OPList.append(OP(2, "CDivide", "/="))
OPList.append(OP(2, "Equality", "=="))
OPList.append(OP(2, "Inequality", "!="))
OPList.append(OP(2, "LessThan", "<"))
OPList.append(OP(2, "GreaterThan", ">"))
OPList.append(OP(2, "LessOrEqualThan", "<="))
OPList.append(OP(2, "GreaterOrEqualThan", ">="))
OPList.append(OP(2, "And", "&&"))
OPList.append(OP(2, "Or", "||"))
#OPList.append(OP(1, "PlusPlus", "++"))
#OPList.append(OP(1, "LessLess", "--"))
OPList.append(OP(1, "Negation", "!"))
#OPList.append(OP(1, "Cast", "cast"))

MapDefinitions = ""
EvaluateDefinitions = ""
RegisterDefinitions = ""
RegisterFunctions = ""
EvaluateFunctions = ""

for op in OPList:
    MapDefinitions = MapDefinitions + GetMapDefinition(op) + "\t\t\t"
    EvaluateDefinitions = EvaluateDefinitions + GetEvaluateDefinition(op) + "\t\t\t"
    RegisterDefinitions = RegisterDefinitions + GetRegisterDefinition(op) + "\t\t\t"
    RegisterFunctions = RegisterFunctions + GetRegisterFunctionCode(op) + "\t\t\t"
    EvaluateFunctions = EvaluateFunctions + GetEvaluateCode(op) + "\t\t\t"

final_render = template.format(MapDefinitions, EvaluateDefinitions, RegisterDefinitions, EvaluateFunctions, RegisterFunctions)

out_file = "./Operators.h_render"
fp = open(out_file, "w")
fp.write(final_render)
fp.close()

print(final_render)