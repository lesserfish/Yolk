#include "Assembler.h"
#include "../Exceptions.h"
#include <cstddef>
#include <stdlib.h>
#include <cstring>
#include <cstdint>
#include <regex>
#include <map>
#include <sys/types.h>
#include <utility>

namespace Yolk
{
    namespace Assembler
    {
        bool Pattern::Accepts(std::string content, std::string lookahead) const
        {
            return std::regex_match(content, content_regex) && std::regex_match(lookahead, lookahead_regex);
        }
        std::vector<Token> FilterTokens(std::vector<Token> input)
        {
            std::vector<Token> output;
            for(auto token : input)
            {
                if(token.symbol == Symbol::SPACE || token.symbol == Symbol::COMMENT)
                {
                    continue;
                }
                output.push_back(token);
            }
            return output;
        }
        std::vector<Token> Tokenize(std::string input)
        {
            std::vector<Token> output;
            uint64_t start_string = 0;

            std::string content;
            std::string lookahead;
            for(uint64_t i = 0; i <= input.length(); i++)
            {
                content = input.substr(start_string, i - start_string);
                lookahead = i < input.length() ? input.substr(i, -1).substr(0, 1) : "";

                
                //std::cout << "Content: [" + content + "]";
                //std::cout << "\tLookadhead: [" + lookahead + "]\n";

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
                    //std::cout << "Accepted: " << winner->to_content(content) << "\n";
                    output.push_back(Token{winner->symbol, winner->to_content(content)});
                    content = "";
                    lookahead = "";
                }
            }

            if(content.length() > 0){
                throw Yolk::Exceptions::Exception("Failed to parse the following assembly code:" + content);
            }

            return output;
        }

        bool ValidateInstruction(Yolk::VM::OPCode, Yolk::VM::Ovo::Code::Arg, Yolk::VM::Ovo::Code::Arg)
        {
            return true;
        }
        void AssertCondition(int condition, std::string error)
        {
            if(!condition) {
                throw Yolk::Exceptions::Exception(error);
            }
        }
        void GotoNextToken(std::vector<Token>::iterator& it, std::vector<Token>& list) {
            auto current_content = it->content;
            it++;
            if(it == list.end()){
                throw Yolk::Exceptions::Exception("Reached an unexpected end. Last read token: " + current_content);
            }
        }
        std::pair<VM::ArgType, uint64_t> GetValueFromElementary(VM::EType type, std::string value)
        {
            switch(type)
            {
                case VM::EType::CHAR: {
                                          char c = value.c_str()[0];
                                          uint64_t outvalue = c;
                                          auto pair = std::make_pair(VM::ArgType::CHAR, outvalue);
                                          return pair;
                                      }
                case VM::EType::DOUBLE: {
                                            double conv = atof(value.c_str());
                                            uint64_t outvalue;
                                            std::memcpy(&outvalue, &conv, sizeof(uint64_t));
                                            auto pair = std::make_pair(VM::ArgType::DOUBLE, outvalue);
                                            return pair;
                                        }
                case VM::EType::FLOAT: {
                                            double conv = atof(value.c_str());
                                            uint64_t outvalue;
                                            std::memcpy(&outvalue, &conv, sizeof(uint64_t));
                                            auto pair = std::make_pair(VM::ArgType::FLOAT, outvalue);
                                            return pair;
                                       }
                case VM::EType::INT32: {
                                           int64_t conv = std::stoi(value);
                                           uint64_t outvalue;
                                           std::memcpy(&conv, &outvalue, sizeof(uint64_t));
                                           auto pair = std::make_pair(VM::ArgType::INT32, outvalue);
                                           return pair;
                                       }
                case VM::EType::INT64:{
                                          int64_t conv = std::stoi(value);
                                          uint64_t outvalue;
                                          std::memcpy(&conv, &outvalue, sizeof(uint64_t));
                                          auto pair = std::make_pair(VM::ArgType::INT64, outvalue);
                                          return pair;
                                      }
                case VM::EType::UINT32:{
                                           uint64_t outvalue = std::stoi(value);
                                           auto pair = std::make_pair(VM::ArgType::UINT32, outvalue);
                                           return pair;
                                       }
                case VM::EType::UINT64:{
                                           uint64_t conv = std::stol(value);
                                           auto pair = std::make_pair(VM::ArgType::UINT64, conv);
                                           return pair;
                                       }
                case VM::EType::VOID:  {
                                           throw Yolk::Exceptions::Exception("Expected to received a value. Received Void instead.");
                                       }
                case VM::EType::STRING:{
                                           throw Yolk::Exceptions::Exception("Strings should not be attached as string:value.");
                                       }
            }
            throw Yolk::Exceptions::Exception("Error parsing EType");
        }
        Yolk::VM::Ovo::Code::Arg ExtractArg(std::vector<Token>::iterator& it, std::vector<Token>& list, std::map<std::string, size_t>& keymap, Yolk::VM::Ovo& ovo)
        {
            Yolk::VM::Ovo::Code::Arg output;
            if(it->symbol == Symbol::EOL) {
                output.type = Yolk::VM::ArgType::NONE;
                output.value = 0;
            }
            else if(it->symbol == Symbol::STRING) {
                auto text_position = ovo.text.size();
                ovo.text.push_back(it->content.c_str());
                output.type = Yolk::VM::ArgType::STRING;
                output.value = static_cast<uint64_t>(text_position);
            }
            else if(it->symbol == Symbol::KEYPOINT) {
                auto keyname = it->content;
                auto keyvalue = keymap.at(keyname);

                output.type = Yolk::VM::ArgType::UINT64;
                output.value = static_cast<uint64_t>(keyvalue);
            }
            else if(it->symbol == Symbol::NAME) {
                auto text_position = ovo.text.size();
                ovo.text.push_back(it->content.c_str());
                output.type = Yolk::VM::ArgType::NAME;
                output.value = static_cast<uint64_t>(text_position);
            }
            else if(it->symbol == Symbol::REGISTER) {
                auto reg = Yolk::VM::RegisterTypeFromString(it->content);
                output.type = Yolk::VM::ArgType::REGISTER;
                output.value = static_cast<uint64_t>(reg);
            }
            else if(it->symbol == Symbol::ELEMENTARY)
            {
                auto elementary = it->content;
                it++;

                if(it == list.end() || it->symbol == Symbol::EOL)
                {
                    output.type = Yolk::VM::ArgType::ELEMENTARY;
                    output.value = static_cast<uint64_t>(VM::ElementaryFromString(elementary));
                }
                else 
                {
                    if(it->symbol != Symbol::SEPARATOR)
                    {
                        throw Yolk::Exceptions::Exception("Expected a separator after elementary type. Received: " + it->content);
                    }
                    GotoNextToken(it, list);

                    auto etype = VM::ElementaryFromString(elementary);
                    auto numparse = GetValueFromElementary(etype, it->content);

                    output.type = numparse.first;
                    output.value = numparse.second;
                }
            }
            else{
                throw Yolk::Exceptions::Exception("Could not parse Assembly. Was expecting an instruction. Received: " + it->content);
            }
            return output;
        }

        Yolk::VM::Ovo Assemble(std::string input)
        {
            Yolk::VM::Ovo output;
            auto raw_tokens = Tokenize(input);
            auto tokens = FilterTokens(raw_tokens);

            std::map<std::string, size_t> keymap;


            for(auto it = tokens.begin(); it != tokens.end(); it++) {

                if(it->symbol == Symbol::KEYPOINT) {
                    auto keyname = it->content;

                    GotoNextToken(it, tokens);
                    if(it->symbol != Symbol::SEPARATOR) {
                        throw Yolk::Exceptions::Exception("Expected a separator ':' after initiating Keypoint " + keyname);
                    }
                    auto keyvalue = output.code.size();

                    // TODO: Maybe check if this fails??
                    keymap.insert(std::pair(keyname, keyvalue));
                    continue;
                }

                else if(it->symbol == Symbol::INSTRUCTION) {
                    Yolk::VM::OPCode opcode = VM::OPFromString(it->content);
                    GotoNextToken(it, tokens);
                    Yolk::VM::Ovo::Code::Arg arg1 = ExtractArg(it, tokens, keymap, output);
                    GotoNextToken(it, tokens);
                    Yolk::VM::Ovo::Code::Arg arg2 = ExtractArg(it, tokens, keymap, output);
                    Yolk::VM::Ovo::Code instruction {opcode, arg1, arg2};

                    output.code.push_back(instruction);

                    std::cout << "INSTRUCTION: " << instruction << "\t TEXT: ";
                    for(auto x : output.text) {
                        std::cout << x.as_string() << " , ";
                    }
                    std::cout << " ;\n";
                }
                else if(it->symbol == Symbol::SPACE || it->symbol == Symbol::EOL) {
                    continue;
                }
                else {
                    std::string remainder = "Assembly remainder: \n";
                    while(it != tokens.end())
                    {
                        remainder += it->content + "\n";
                        it++;
                    }
                    throw Yolk::Exceptions::Exception("Expected an instruction. Received " + it->content + remainder);
                }

            }

            return output;
        }
    }
}
