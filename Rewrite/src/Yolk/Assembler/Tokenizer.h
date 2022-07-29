#pragma once

#include "../Exceptions.h"
#include "../YolkVM/VM.h"
#include <iostream>
#include <string>
#include <regex>

namespace Yolk
{
    namespace Assembler
    {
        enum class Symbol : uint8_t
        {
            INSTRUCTION,
            REGISTER,
			STRING,
            NUMBER,
            FNUMBER,
            ELEMENTARY,
            SEPARATOR,
            EOL,
            COMMENT,
            SPACE
        };

        class Token
        {
            public:
                Token(Symbol s, std::string c = "") : symbol(s), content(c) {}
                Symbol symbol;
                std::string content;
        };
        class Tokenizer
        {
            public:
                Tokenizer(Token t, std::string c_r, std::string la_r, int p = 0) : 
                    token(t), 
                    content_regex(c_r), 
                    lookahead_regex(la_r),
                    priority(p)
                {}
                bool Accepts(std::string content, std::string remainder = "")
                {
                    token.content = content;
                    return std::regex_match(content, content_regex) && std::regex_match(remainder, lookahead_regex);   
                }
                Token GetToken()
                {
                    return token;
                }
                int Priority() { return priority; }
            private:
                Token token;
                std::regex content_regex;
                std::regex lookahead_regex;
                int priority;
        };
        
        static void CleanTokens(std::vector<Token>& tokers)
        {
            for(auto iter = tokers.begin(); iter <= tokers.end(); )
            {
                if(iter->symbol == Symbol::SPACE 
                        || iter->symbol == Symbol::EOL 
                        || iter->symbol == Symbol::COMMENT)
                {
                    iter = tokers.erase(iter);
                } else
                {
                    iter++;
                }
            }
        }
        
        std::vector<Token> GetTokens(std::string source, std::vector<Tokenizer> tokers)
        {
            std::vector<Token> out;
            uint64_t start_string = 0;
            for(uint64_t i = 0; i <= source.length(); i++)
            {
                std::string content = source.substr(start_string, i - start_string);
                std::string remainder = i < source.length() ? source.substr(i, -1).substr(0,1) : "";

                //std::cout << content << "\t" << remainder << "\n";
                
                std::vector<Tokenizer> accepted;
                
                int minpriority = -1;
                Tokenizer* winner = NULL;
                for(auto& tokenizer : tokers)
                {
                    if(tokenizer.Accepts(content, remainder))
                    {
                        //std::cout << "Accepted: " << content << std::endl;
                        start_string = i;
                        if(minpriority == -1 || minpriority > tokenizer.Priority())
                        {
                            minpriority = tokenizer.Priority();
                            winner = &tokenizer;
                        }
                    }
                }
                if(winner != NULL)
                {
                    out.push_back(winner->GetToken());
                }
            }
            return out;
        }

        void AssertEquality(bool input, std::string error)
        {
            if(!input)
            {
                throw Yolk::Exceptions::Exception(error);
            }
        }
        Yolk::VM::Ovo Assemble(std::vector<Token>& tokers)
        {
            Yolk::VM::Ovo out;
            std::string line = "";
            for(auto it = tokers.begin(); it != tokers.end(); it++)
            {
                AssertEquality(it->symbol == Symbol::INSTRUCTION, "Line of code does not begin with instruction");
                VM::OPCode opcode = VM::OPFromString(it->content);
                line += it->content + "\t"; 
                it++;

                AssertEquality(it != tokers.end(), "Missing content in line: " + line);

            }
            return out;
        }
    }
}
