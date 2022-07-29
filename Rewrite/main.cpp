#include "src/Yolk/Yolk.h"
#include "src/Yolk/Assembler/Assembler.h"
#include <iostream>
#include <string>
#include <cstdio>

int main(){
    std::string source= "MOV REGA REGB\n"
                        "ADD REGA REGC\n"
                        "#This is a comment\n"
                        "ADD REGA int32:128";
    auto tokers = Yolk::Assembler::GetTokens(source, Yolk::Assembler::TokenArray);
    Yolk::Assembler::CleanTokens(tokers);

    for(auto it = tokers.begin(); it != tokers.end(); it++)
    {
        std::cout << it->content << std::endl;
    }

}
