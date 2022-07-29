#pragma once

#include "Tokenizer.h"
#include <vector>
namespace Yolk
{
    namespace Assembler
    {
        Tokenizer INSTRUCTION(Token(Symbol::INSTRUCTION),
                                "MOV|COPY|CLONE|NEW|MOVM|CALLM|PUSHAR|POPAR|CLRAR|PUSH|POP|CLEAR|CMP|CMPEQ|CMPNEQ|CMPLS|CMPGT|CMPLSEQ|CMPGTEQ|JNTRUE|JNFALSE|JMP|CALL|RET|ADD|SUB|MUL|DIV|MOD|AND|OR|CAST|NAME|NAMEG|BRUP|BRDW|BRHZ|RSBR|ZERO|HALT",
                                "\\s|\n|^$");
        Tokenizer SPACE(Token(Symbol::SPACE),
                                "\\s",
                                ".*|\n|^$");
        Tokenizer REG(Token(Symbol::REGISTER),
                                "REGA|REGB|REGC|REGD|REGOUT|REGM|REGCMP",
                                "\\s|.*|\n|^$");
        Tokenizer STRING(Token(Symbol::STRING),
                                "\".*\"",
                                "\\s|\n|.*|^$");
        Tokenizer NUMBER(Token(Symbol::NUMBER),
                                "\\d+",
                                "\\s|\n|\\D|^$");
        Tokenizer FNUMBER(Token(Symbol::FNUMBER),
                                "\\d+.\\d+",
                                "\\s|\n|\\D|^$");
        Tokenizer ELEMENTARY(Token(Symbol::ELEMENTARY),
                                "int32|uint32|int64|uint64|float|double|char|string|void",
                                "\\s|\n|\\W|^$");
        Tokenizer SEPARATOR(Token(Symbol::SEPARATOR),
                                ":",
                                ".*|\\s|\n|^$");
        Tokenizer EOL(Token(Symbol::EOL),
                                ";|\n",
                                ".*|\\s|\n|^$");
        Tokenizer COMMENT(Token(Symbol::COMMENT),
                                "#.*",
                                "\\n|^$");
        
        static std::vector<Tokenizer> TokenArray = {INSTRUCTION, SPACE, REG, STRING, NUMBER, FNUMBER, ELEMENTARY, SEPARATOR, EOL, COMMENT};
    }
}
