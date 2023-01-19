#include "Assembler.h"
#include <cstdint>
#include <regex>

namespace Yolk
{
    namespace Assembler
    {
        bool Pattern::Accepts(std::string content, std::string lookahead) const
        {
            return std::regex_match(content, content_regex) && std::regex_match(lookahead, lookahead_regex);
        }
        std::vector<Token> Tokenize(std::string input)
        {
            std::vector<Token> output;
            uint64_t start_string = 0;

            for(uint64_t i = 0; i <= input.length(); i++)
            {
                std::string content = input.substr(start_string, i - start_string);
                std::string lookahead = i < input.length() ? input.substr(i, -1).substr(0, 1) : "";

                
                std::cout << "Content: [" + content + "]";
                std::cout << "\tLookadhead: [" + lookahead + "]\n";

                int minpriority = -1;
                const Pattern *winner = NULL;
                for(auto& token : PT_SET) {
                    if(token.Accepts(content, lookahead))
                    {
                        start_string = i;
                        if(minpriority == -1 || minpriority > token.priority)
                        {
                            minpriority = token.priority;
                            winner = &token;
                        }
                    }
                }

                if(winner != NULL)
                {
                    std::cout << "Accepted: " << winner->to_content(content) << "\n";
                    output.push_back(Token{winner->symbol, winner->to_content(content)});
                }
            }

            return output;
        }

        Yolk::VM::Ovo ASsemble(std::string )
        {
            Yolk::VM::Ovo output;

            return output;
        }
    }
}
