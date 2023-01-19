#include "src/Yolk/Yolk.h"
#include "src/Yolk/Assembler/Assembler.h"
#include <cstdint>
#include <iostream>
#include <string>
#include <cstdio>

int main(){
    std::string source= "MOV REGA REGB\n"
                        "ADD REGB REGC\n"
                        "ADD REGA uint64:128\n"
                        "SUB REGB double:-127.35 // We Add something to the register\n"
                        ".LOOP:\n"
                        "CMPEQ REGA REGB\n"
                        "JMP .LOOP\n"
                        "MOV REGA Text\n"
                        "MOV REGB \"The string is valid\"";
                        

    auto output = Yolk::Assembler::Tokenize(source);
    
    std::cout << "Got " << output.size() << " elements. Showing them in order: \n";

    for(auto& i : output){
        std::cout << i.content << "\n";
    }
}
