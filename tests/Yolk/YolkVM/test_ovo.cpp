#include <gtest/gtest.h>
#include "../../../src/Yolk/YolkVM/VM.h"

TEST(OVO, LoadSave)
{
    Yolk::VM::Ovo ovo;
    
    ovo.version = 0.1;
    
    ovo.code.push_back(Yolk::VM::Ovo::Code { Yolk::VM::OPCode::COPY, Yolk::VM::Ovo::Code::Arg {Yolk::VM::ArgType::REGISTER, 0}, Yolk::VM::Ovo::Code::Arg {Yolk::VM::ArgType::REGISTER, 1}});
    ovo.code.push_back(Yolk::VM::Ovo::Code { Yolk::VM::OPCode::CLONE, Yolk::VM::Ovo::Code::Arg {Yolk::VM::ArgType::REGISTER, 0}, Yolk::VM::Ovo::Code::Arg {Yolk::VM::ArgType::REGISTER, 1}});
    
    ovo.text.push_back(Yolk::VM::Ovo::Text("Hello there friend!"));
    ovo.text.push_back(Yolk::VM::Ovo::Text("This is the end."));
    
    ovo.ToFile("./demo.ovo");
    
    Yolk::VM::Ovo newovo;
    bool a1 = newovo.FromFile("./demo.ovo");

    EXPECT_TRUE(a1);
    EXPECT_TRUE(ovo == newovo);
}
