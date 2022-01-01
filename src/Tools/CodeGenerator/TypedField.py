class AOP:
    def __init__(self, _name):
        self.name = _name
    def _render_virtheader(self, ttype : str):
        out = """virtual bool Try{0}({1}) {{return false;}}\n""".format(self.name, ttype)
        return out
    def _render_header(self, ttype : str):
        out = """bool Try{0}({1} other) {{return AddHelper<{1}>(other);}}\n""".format(self.name, ttype)
        return out
    name : str

class BOP:
    def __init__(self, _name):
        self.name = _name
    def _render_virtheader(self, ttype : str):
        out = """virtual int Compare{0}({1}) const {{return -1;}}\n""".format(self.name, ttype)
        return out;
    def _render_header(self, ttype : str):
        out = """
        int Compare{0}({1} other) const{{return Compare{0}Helper(other);}}""".format(self.name, ttype)
        return out
    def _render_signed_header(self, ttype : str):
        out = """
        int Compare{0}({1} other) const
        {{
            constexpr bool is_unsigned = std::is_unsigned<T>::value;
            if constexpr(is_unsigned)
                return CompareHelper((unsigned {1})other);
            else
                return CompareHelper(other);
        }}""".format(self.name, ttype)
        return out
    def _render_unsigned_header(self, ttype : str):
        out = """
        int Compare{0}(unsigned {1} other) const
        {{
            constexpr bool is_unsigned = std::is_unsigned<T>::value;
            if constexpr(is_unsigned)
                return CompareHelper(other);
            else
                return CompareHelper(({1})other);
        }}""".format(self.name, ttype)
        return out
    name : str


Arithmetic = [AOP("Add"), AOP("Sub"), AOP("Mul"), AOP("Div"), AOP("Mod"), AOP("And"), AOP("Or")]
Boolean = [BOP(""), BOP("Less"), BOP("Greater"), BOP("LessEqual"), BOP("GreaterEqual")]

etypes = ["int", "long", "unsigned int", "unsigned long", "float", "double", "char", "unsigned char", "bool"]

ntypes = ["float", "double", "bool", "std::string"]
stypes = ["int", "long", "char"]
utypes = ["int", "long", "char"]


VIRTA = ""
VIRTO = ""
NVA = ""
NVO = ""
for A in Arithmetic:
    for t in etypes:
        VIRTA = VIRTA + A._render_virtheader(t)
        NVA = NVA + A._render_header(t)

for A in Boolean:
    for t in ntypes:
        VIRTO = VIRTO + A._render_virtheader(t)
        NVO = NVO + A._render_header(t)
    for t in stypes:
        VIRTO = VIRTO + A._render_virtheader(t)
        NVO = NVO + A._render_signed_header(t)
    for t in utypes:
        VIRTO = VIRTO + A._render_virtheader(t)
        NVO = NVO + A._render_unsigned_header(t)

    

output = VIRTA + "\n" + VIRTO + "\n" + NVA + "\n" + NVO

ofile = open("TypedField.h.render", "w")
ofile.write(output)
ofile.close()

print(output)