#pragma once

#include "../Exceptions.h"
#include "../YolkVM/VM.h"
#include <iostream>
#include <string>
#include <regex>
#include <functional>

namespace Yolk{
    namespace Assembler {

        using regex = std::regex;

        enum class Symbol : uint8_t
        {
            INSTRUCTION,
            REGISTER,
            STRING,
            NUMBER,
            DOUBLE,
            ELEMENTARY,
            SEPARATOR,
            EOL,
            COMMENT,
            SPACE,
            KEYPOINT,
            NAME
        };


        struct Token 
        {
            Symbol symbol;
            std::string content;
        };
        struct Pattern
        {
                Symbol symbol;
                std::function<std::string(std::string)> to_content;
                regex content_regex;
                regex lookahead_regex;
                int priority;
                bool Accepts(std::string, std::string) const;
        };

        std::vector<Token> Tokenize(std::string);
        Yolk::VM::Ovo Assemble(std::string);


        static const Pattern PT_SPACE { 
            Symbol::SPACE,
                [](std::string ) -> std::string
                {
                    return "[SPACE]";
                },
                regex("^ $|^\t$"),
                regex(".|^$|^\n$"),
                0
        };
        static const Pattern PT_EOL { 
            Symbol::EOL,
                [](std::string ) -> std::string
                {
                    return "[EOL]";
                },
                regex("^;$|^\n$"),
                regex(".|^$|^\n$"),
                0
        };

        static const Pattern PT_INSTRUCTION { 
            Symbol::INSTRUCTION,
                [](std::string input) -> std::string
                {
                    return input;
                },
                regex("^MOV$|^COPY$|^CLONE$|^NEW$|^MOVM$|^CALLM$|^PUSHAR$|^POPAR$|^CLRAR$|^PUSH$|^POP$|^CLEAR$|^CMP$|^CMPEQ$|^CMPNEQ$|^CMPLS$|^CMPGT$|^CMPLSEQ$|^CMPGTEQ$|^JNTRUE$|^JNFALSE$|^JMP$|^CALL$|^RET$|^ADD$|^SUB$|^MUL$|^DIV$|^MOD$|^AND$|^OR$|^CAST$|^NAME$|^NAMEG$|^BRUP$|^BRDW$|^BRHZ$|^RSBR$|^ZERO$|^HALT$"),
                regex("\\W|^$|^\n$"),
                0
        };
        static const Pattern PT_NAME { 
            Symbol::NAME,
                [](std::string input) -> std::string
                {
                    return input;
                },
                regex("^\\w+$"),
                regex("\\W|^$|^\n$"),
                2
        };
        static const Pattern PT_SEPARATOR { 
            Symbol::SEPARATOR,
                [](std::string ) -> std::string
                {
                    return "[SEPARATOR]";
                },
                regex("^:$"),
                regex(".|^$|^\n$"),
                0
        };
        static const Pattern PT_ELEMENTARY { 
            Symbol::ELEMENTARY,
                [](std::string input) -> std::string
                {
                    return input;
                },
                regex("^int32$|^int64$|^uint32$|^uint64$|^float$|^double$|^char$|^string$|^void$"),
                regex("\\W|^$|^\n$"),
                1
        };
        static const Pattern PT_NUMBER { 
            Symbol::NUMBER,
                [](std::string input) -> std::string
                {
                    return input;
                },
                regex("^-*\\d+$"),
                regex("^(?!\\d|\\.).*$|^$|^\n$"),
                1
        };
        static const Pattern PT_DOUBLE { 
            Symbol::DOUBLE,
                [](std::string input) -> std::string
                {
                    return input;
                },
                regex("^-*\\d+\\.\\d+$"),
                regex("\\D|^$|^\n$"),
                1
        };
        static const Pattern PT_STRING { 
            Symbol::STRING,
                [](std::string input) -> std::string
                {
                    return input.substr(1, input.length() - 2);
                },
                regex("^\".*\"$"),
                regex(".|^$|^\n$"),
                1
        };
        static const Pattern PT_COMMENT { 
            Symbol::COMMENT,
                [](std::string input) -> std::string
                {
                    return input;
                },
                regex("^//.*$"),
                regex("^\n$|^$|^\n$"),
                1
        };
        static const Pattern PT_KEYPOINT { 
            Symbol::KEYPOINT,
                [](std::string input) -> std::string
                {
                    return input;
                },
                regex("^\\.[A-Z]+$"),
                regex("^(?![A-Z]).*$|^$|^\n$"),
                1
        };
        static const Pattern PT_REGISTER { 
            Symbol::REGISTER,
                [](std::string input) -> std::string
                {
                    return input;
                },
                regex("^REGA$|^REGB$|^REGC$|^REGD$|^REGCMP$|^REGOUT$"),
                regex("\\W|^$|^\n$"),
                1
        };

        static const std::vector<Pattern> PT_SET = { 
            PT_SPACE,
            PT_EOL,
            PT_INSTRUCTION,
            PT_NAME,
            PT_SEPARATOR,
            PT_ELEMENTARY,
            PT_NUMBER,
            PT_DOUBLE,
            PT_STRING,
            PT_COMMENT,
            PT_KEYPOINT,
            PT_REGISTER
        };

    }


}
