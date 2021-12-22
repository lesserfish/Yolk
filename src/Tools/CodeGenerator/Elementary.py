class OpType:
    def __init__(self, A : str, B : str, tw : bool):
        self.typeA = A
        self.typeB = B
        self.two_way = tw
    def generateInvocation(self, Name : str):
        output = "\top.Register"+Name+"<{},{}>();".format(self.typeA, self.typeB) + "\n";
        if(self.two_way):
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
        for j in range(i + 1, len(types)):
            typeA = types[i]
            typeB = types[j]
            newOp = OpType(typeA, typeB, True)
            out.append(newOp)
    return out;



Add = [ Operation("Add"),
        Operation("Subtract"),
        Operation("Multiply"),
        Operation("Divide"),
        ]
Compare = [ Operation("Equality"),
        Operation("LessThan"),
        Operation("GreaterThan")
        ]

Numeric = GetEveryCombination(["int", "unsigned int","long int", "unsigned long int", "float", "double"])
Signed = GetEveryCombination(["int", "long int", "float", "double"])
Unsigned = GetEveryCombination(["unsigned int", "unsigned long int"])

content = ""

for x in Add:
    x.Set(Numeric)
    content = content + x.GetString() + "\n"

for x in Compare:
    x.Set(Signed)
    content = content + x.GetString()
    x.Set(Unsigned)
    content = content + x.GetString()


output = """
    #pragma once
    #include "Operators.h"
    namespace Yolk
    {{
        namespace VM
        {{

            static void GenerateElementaryOperations(Yolk::VM::Operator& op)
            {{
                {}
            }}
        }}
    }}
""".format(content)


file_out = "Elementary.h_render"
fp = open(file_out, "w")
fp.write(output)
fp.close()

print(output)