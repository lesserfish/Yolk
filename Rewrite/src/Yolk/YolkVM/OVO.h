#include <vector>
#include <string>
#include <fstream>
#include <boost/endian/conversion.hpp>

namespace Yolk
{
    namespace VM
    {
        char MAGIC[] = "sunny side up.";

        enum class Instruction : uint8_t
        {
            MOV,
            COPY,
            CLONE,
            NEW,
            MOVM,
            CALLM,
            PUSHAR,
            POPAR,
            CLRAR,
            PUSH,
            POP,
            CLEAR,
            CMP,
            CMPEQ,
            CMPNEQ,
            CMPLS,
            CMPGT,
            CMPLSEQ,
            CMPGTEQ,
            JNTRUE,
            JNFALSE,
            JMP,
            CALL,
            RET,
            ADD,
            SUB,
            MUL,
            DIV,
            MOD,
            AND,
            OR,
            CAST,
            NAME,
            NAMEG,
            BRUP,
            BRDW,
            BRHZ,
            RSBR,
            ZERO,
            HALT
        };

        enum class ArgType : uint8_t       
        {
            REGISTER,
			NAME,
			INT,
			UINT,
			DOUBLE,
			CHAR,
			STRING,
			VOID,
			TYPE        
        };

        enum class EType : uint8_t
        {
            INT,
			UINT,
			DOUBLE,
			CHAR,
			STRING,
			VOID
        };

        struct Ovo
        {
            struct Code
            {
                struct Arg
                {
                    ArgType type;
                    uint64_t value;
                };
                
                Instruction instruction;
                Arg arg1;
                Arg arg2;
            };
            struct Text
            {
                static uint64_t get_length(const char* c) {
                    uint64_t l = 0;
                    while(*c != '\0'){
                        l++;
                        c++;
                    }
                    return l;
                }
                Text(const char *c) : content(new char(get_length(c))), size(get_length(c)) 
                {
                    for(uint64_t i = 0; i < size; i++)
                    {
                        content[i] = c[i];
                    }
                }
                Text(const char* c, uint64_t s) : content(new char(s)), size(s)
                {
                    for(uint64_t i = 0; i < s; i++)
                    {
                        content[i] = c[i];
                    }
                }
                char* content;
                const uint64_t size;
                std::string as_string()
                {
                    std::string out = "";
                    for(uint64_t i = 0; i < size; i++){
                        out += content[i];
                    }
                    return out;
                }
            };
            double version;
            std::vector<Code> code;
            std::vector<Text> text;

            bool ToFile(std::string);
            bool FromFile(std::string);

            std::string GetText(uint64_t position) {
                if(position >= text.size()){
                    return "";
                }
                return text.at(position).as_string();
            }

        };

        static bool IsHighEndian()
        {
            int n = 1;
            if(*(char *)&n == 1){
                return false;
            }
            return true;
        }
        static void LOEndian(char* origin, char* destiny, uint64_t size) {
            if(!IsHighEndian()) {
                for(uint64_t i = 0; i < size; i++)
                {
                    destiny[i] = origin[i]; 
                }
            }
            else {
                for(uint64_t i = 0; i < size;)
                {
                    destiny[i] = origin[size - 1 - i]; 
                }
            }
        }
        inline bool Ovo::FromFile(std::string path)
        {
            code.clear();
            text.clear();

            std::ifstream file;
            file.open(path, std::ios::binary | std::ios::in);

            if(file.fail())
            {
                return false;
            }

            // Write Magic Numbers:
            
            char magic[sizeof(MAGIC) - 1]; // Ignore \0
            
            LOEndian(MAGIC, magic, sizeof(MAGIC) - 1);
            file.read(magic, sizeof(magic));

            for(uint64_t i = 0; i < sizeof(MAGIC) - 1; i++)
            {
                if(magic[i] != MAGIC[i]){
                    return false;
                }
            }

            // Read OVO Version:
            
            char version_cstr[sizeof(double)];
            file.read(version_cstr, sizeof(version_cstr));
            
            LOEndian(version_cstr, (char *)&version, sizeof(version_cstr));

            // Write Code Array:
            
            // Write Size of Code Array:
            
            char codesize_cstr[sizeof(uint64_t)];
            file.read(codesize_cstr, sizeof(codesize_cstr));
            
            uint64_t codesize = code.size();
            LOEndian(codesize_cstr, (char *)&codesize, sizeof(codesize_cstr));

            // Write each line of code

            for(uint64_t t = 0; t < codesize; t++)
            {
                char instruction_cstr[sizeof(Instruction)];
                file.read(instruction_cstr, sizeof(instruction_cstr));
                
                uint8_t instruction;
                LOEndian(instruction_cstr, (char *)&instruction, sizeof(instruction_cstr));

                char arg1arg_cstr[sizeof(ArgType)];
                file.read(arg1arg_cstr, sizeof(arg1arg_cstr));
                
                uint8_t arg1arg;
                LOEndian(arg1arg_cstr, (char *)&arg1arg, sizeof(arg1arg_cstr));
                
                char arg1val_cstr[sizeof(uint64_t)];
                file.read(arg1val_cstr, sizeof(arg1val_cstr));
                
                uint64_t arg1val;
                LOEndian(arg1val_cstr, (char *)&arg1val, sizeof(arg1val_cstr));

                char arg2arg_cstr[sizeof(ArgType)];
                file.read(arg2arg_cstr, sizeof(arg2arg_cstr));
                
                uint8_t arg2arg;
                LOEndian(arg2arg_cstr, (char *)&arg2arg, sizeof(arg2arg_cstr));
                
                char arg2val_cstr[sizeof(uint64_t)];
                file.read(arg2val_cstr, sizeof(arg2val_cstr));
                
                uint64_t arg2val;
                LOEndian(arg2val_cstr, (char *)&arg2val, sizeof(arg2val_cstr));

                code.push_back( Code {
                                        static_cast<Instruction>(instruction),
                                        Code::Arg { static_cast<ArgType>(arg1arg), 
                                                    arg1val },
                                        Code::Arg { static_cast<ArgType>(arg2arg), 
                                                    arg2val },
                                });

            }
            
            // Write Text Array:

            // Write Size of Text Array:
            
            char textarraysize_cstr[sizeof(uint64_t)];
            file.read(textarraysize_cstr, sizeof(textarraysize_cstr));
            
            uint64_t textarraysize;
            LOEndian(textarraysize_cstr, (char *)&textarraysize, sizeof(textarraysize_cstr));

            // Write each line of text:
            
            for(uint64_t t = 0; t < textarraysize; t++)
            {
                char textsize_cstr[sizeof(uint64_t)];
                file.read(textsize_cstr, sizeof(textsize_cstr));
                
                uint64_t textsize;
                LOEndian(textsize_cstr, (char *)&textsize, sizeof(textsize_cstr));

                char* content_cstr = new char(textsize);
                file.read(content_cstr, textsize);
                
                text.push_back(Text(content_cstr, textsize));
                delete content_cstr;
            }

            file.close();
            // END
            return true;

        }
        inline bool Ovo::ToFile(std::string path)
        {
            std::ofstream file;
            file.open(path, std::ios::binary | std::ios::out);

            if(file.fail())
            {
                return false;
            }

            // Write Magic Numbers:
            
            char magic[sizeof(MAGIC) - 1]; // Ignore \0
            
            LOEndian(MAGIC, magic, sizeof(MAGIC) - 1);
            file.write(magic, sizeof(magic));

            // Write OVO Version:
            
            char version_cstr[sizeof(double)];
            LOEndian((char *) &version, version_cstr, sizeof(version_cstr));
            file.write(version_cstr, sizeof(version_cstr));

            // Write Code Array:
            
            // Write Size of Code Array:
            
            uint64_t codesize = code.size();
            char codesize_cstr[sizeof(codesize)];
            LOEndian((char*)&codesize, codesize_cstr, sizeof(codesize_cstr));

            file.write(codesize_cstr, sizeof(codesize_cstr));

            // Write each line of code

            for(auto codeline = code.begin(); codeline != code.end(); codeline++)
            {
                uint8_t instruction = static_cast<uint8_t>(codeline->instruction);
                char instruction_cstr[sizeof(instruction)];
                LOEndian((char *)&instruction, instruction_cstr, sizeof(instruction_cstr));

                uint8_t arg1arg = static_cast<uint8_t>(codeline->arg1.type);
                char arg1arg_cstr[sizeof(arg1arg)];
                LOEndian((char *)&arg1arg, arg1arg_cstr, sizeof(arg1arg_cstr));
                
                uint64_t arg1val = codeline->arg1.value;
                char arg1val_cstr[sizeof(arg1val)];
                LOEndian((char *)&arg1val, arg1val_cstr, sizeof(arg1val_cstr));

                uint8_t arg2arg = static_cast<uint8_t>(codeline->arg2.type);
                char arg2arg_cstr[sizeof(arg2arg)];
                LOEndian((char *)&arg2arg, arg2arg_cstr, sizeof(arg2arg_cstr));
                
                uint64_t arg2val = codeline->arg2.value;
                char arg2val_cstr[sizeof(arg2val)];
                LOEndian((char *)&arg2val, arg2val_cstr, sizeof(arg2val_cstr));
                

                file.write(instruction_cstr, sizeof(instruction_cstr));
                file.write(arg1arg_cstr, sizeof(arg1arg_cstr));
                file.write(arg1val_cstr, sizeof(arg1val_cstr));
                file.write(arg2arg_cstr, sizeof(arg2arg_cstr));
                file.write(arg2val_cstr, sizeof(arg2val_cstr));
            }
            
            // Write Text Array:

            // Write Size of Text Array:
            
            uint64_t textarraysize = text.size();
            char textarraysize_cstr[sizeof(textarraysize)];
            LOEndian((char *)&textarraysize, textarraysize_cstr, sizeof(textarraysize_cstr));

            file.write(textarraysize_cstr, sizeof(textarraysize_cstr));

            // Write each line of text:
            
            for(auto line = text.begin(); line != text.end(); line++)
            {
                std::string textcontent = line->as_string();
                
                uint64_t textsize = textcontent.size() * sizeof(char);
                char textsize_cstr[sizeof(textsize)];
                LOEndian((char *)&textsize, textsize_cstr, sizeof(textsize_cstr));
                
                file.write(textsize_cstr, sizeof(textsize_cstr));
                file.write(textcontent.c_str(), textsize); // Writing Text array is Writing Byte array which does not require Endian conversion
            }
            
            file.write(magic, sizeof(magic));
            file.close();
            // END
            return true;
        }
    }
}
