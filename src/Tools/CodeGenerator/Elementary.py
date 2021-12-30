class OpType:
    def __init__(self, A : str, B : str, tw : bool):
        self.typeA = A
        self.typeB = B
        self.two_way = tw
    def generateInvocation(self, Name : str):
        output = "\top.Register"+Name+"<{},{}>();".format(self.typeA, self.typeB) + "\n";
        if(self.two_way and not(self.typeA == self.typeB)):
            output = output + "\top.Register"+Name+"<{},{}>();".format(self.typeB, self.typeA) + "\n";
        return output
    typeA : str
    typeB : str
    two_way : bool


class Operation:
    def __init__(self, n):
        self.name = n
    def GetString(self):
        output = ""
        for entry in self.ops:
            output = output + entry.generateInvocation(self.name)
        return output
    def Push(self, e : OpType):
        self.ops.append(e)
    def Set(self, l):
        self.ops.clear()
        for e in l:
            self.ops.append(e)
    name : str
    ops = list()

def GetEveryCombination(types):
    out = list()
    for i in range(0, len(types)):
        for j in range(i, len(types)):
            typeA = types[i]
            typeB = types[j]
            newOp = OpType(typeA, typeB, True)
            out.append(newOp)
    return out;



NumericOperations = [ Operation("Add"),
        Operation("Subtract"),
        Operation("Multiply"),
        Operation("Divide"),
        Operation("Cast")
        ]
IntegralOperations = [Operation("Modulo")]
ComparisonOperations = [ Operation("Equality"),
        Operation("LessThan"),
        Operation("GreaterThan"),
        Operation("LessOrEqualThan"),
        Operation("GreaterOrEqualThan")
        ]
LogicalOperations = [ Operation("And"), Operation("Or")]
Numeric = GetEveryCombination(["int", "unsigned int","long int", "unsigned long int", "float", "double", "char", "unsigned char", "bool"])
Integral = GetEveryCombination(["int", "unsigned int", "long", "unsigned long"])
Signed = GetEveryCombination(["int", "long int", "float", "double", "char"])
Unsigned = GetEveryCombination(["unsigned int", "unsigned long int", "unsigned char"])
Boolean = GetEveryCombination(["bool"])

content = ""

for x in NumericOperations:
    x.Set(Numeric)
    content = content + x.GetString() + "\n"
for x in IntegralOperations:
    x.Set(Integral)
    content = content + x.GetString() + "\n"
for x in ComparisonOperations:
    x.Set(Signed)
    content = content + x.GetString() + "\n"
    x.Set(Unsigned)
    content = content + x.GetString() + "\n"

for x in LogicalOperations:
    x.Set(Boolean)
    content = content + x.GetString() + "\n"

output = """
    #pragma once
    #include "Operators.h"
    namespace Yolk
    {{
        namespace VM
        {{
            
            struct Elementary
            {{
                static void GenerateElementaryOperations(Yolk::VM::Operator& op)
                {{
                    {}
                }}
            }};
        }}
    }}
""".format(content)


file_out = "Elementary.h_render"
fp = open(file_out, "w")
fp.write(output)
fp.close()

print(output)