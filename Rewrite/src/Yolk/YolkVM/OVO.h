#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <array>

namespace Yolk
{
    namespace VM
    {
        static const char MAGIC[] = "sunny side up!";

        enum class OPCode : uint8_t
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

        const std::array<OPCode, 40> AllOPCodes = {
            OPCode::MOV,
            OPCode::COPY,
            OPCode::CLONE,
            OPCode::NEW,
            OPCode::MOVM,
            OPCode::CALLM,
            OPCode::PUSHAR,
            OPCode::POPAR,
            OPCode::CLRAR,
            OPCode::PUSH,
            OPCode::POP,
            OPCode::CLEAR,
            OPCode::CMP,
            OPCode::CMPEQ,
            OPCode::CMPNEQ,
            OPCode::CMPLS,
            OPCode::CMPGT,
            OPCode::CMPLSEQ,
            OPCode::CMPGTEQ,
            OPCode::JNTRUE,
            OPCode::JNFALSE,
            OPCode::JMP,
            OPCode::CALL,
            OPCode::RET,
            OPCode::ADD,
            OPCode::SUB,
            OPCode::MUL,
            OPCode::DIV,
            OPCode::MOD,
            OPCode::AND,
            OPCode::OR,
            OPCode::CAST,
            OPCode::NAME,
            OPCode::NAMEG,
            OPCode::BRUP,
            OPCode::BRDW,
            OPCode::BRHZ,
            OPCode::RSBR,
            OPCode::ZERO,
            OPCode::HALT
        };

        enum class ArgType : uint8_t       
        {
            REGISTER,
			NAME,
            INT32,
			INT64,
			UINT32,
            UINT64,
            FLOAT,
			DOUBLE,
			CHAR,
			STRING,
			VOID,
		    ELEMENTARY,
            NONE
        };

        enum class EType : uint8_t
        {
            INT32,
			UINT32,
            INT64,
            UINT64,
            FLOAT,
			DOUBLE,
			CHAR,
			STRING,
			VOID
        };

        enum class RegisterType : uint64_t
        {
            REGA,
            REGB,
            REGC,
            REGD,
            REGOUT,
            REGM,
            RECMP,
        };

        struct Ovo
        {
            struct Code
            {
                bool operator==(const Code& other)
                {
                    return (opcode == other.opcode) && (arg1.type == other.arg1.type) && (arg1.value == other.arg1.value) && (arg2.type == other.arg2.type) && (arg2.value == other.arg2.value);
                }
                struct Arg
                {
                    ArgType type;
                    uint64_t value;
                };
                
                OPCode opcode;
                Arg arg1;
                Arg arg2;
            };
            struct Text
            {
                bool operator==(const Text& other)
                {
                    if(size != other.size){
                        return false;
                    }
                    for(uint64_t i = 0; i < size; i++){
                        if(content[i] != other.content[i]){
                            return false;
                        }
                    }
                    return true;
                }
                static uint64_t get_length(const char* c) {
                    uint64_t l = 0;
                    while(*c != '\0'){
                        l++;
                        c++;
                    }
                    return l;
                }
                std::string as_string()
                {
                    std::string out = "";
                    for(uint64_t i = 0; i < size; i++){
                        out += content[i];
                    }
                    return out;
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
                Text(const Text& other) : content(new char(other.size)), size(other.size)
                {
                    for(uint64_t i = 0; i < other.size; i++)
                    {
                        content[i] = other.content[i];
                    }
                }
                ~Text()
                {
                    delete content;
                }
                private:
                char* content;
                const uint64_t size;
                
            };
            bool operator==(const Ovo& other)
            {
                if(version != other.version){
                    return false;
                }
                if(code.size() != other.code.size()){
                    return false;
                }

                for(uint64_t i = 0; i < code.size(); i++)
                {
                    if(code.at(i) != other.code.at(i)){
                        return false;
                    }
                }
                if(text.size() != other.text.size()){
                    return false;
                }
                for(uint64_t i = 0; i < text.size(); i++){
                    if(text.at(i) != other.text.at(i)){
                        return false;
                    }
                }
                return true;
            }
            double version;
            std::vector<Code> code;
            std::vector<Text> text;

            bool ToFile(std::string);
            bool FromFile(std::string);

        };

        static bool IsLowEndian()
        {
            int n = 1;
            if(*(char *)&n == 1){
                return true;
            }
            return false;
        }

        // EndianMemCpy:
        // EndianMemCpy is used to write/read Ovo files.
        // CPU <----- EndianMemcpy -----> File
        //
        // In Low Endian systems, EndianMemcpy behaves exactly like memcpy, so it becomes:
        //
        // (Low endian binary cpu data) <---- Memcpy ------> (Low Endian binary file data)
        //
        // However, in high endian systems, it first inverts the endianness of the data, so this becomces:
        //
        // (High endian binary cpu data) <----- Invert and Memcpy -------> (Low Endian binary file data)
        //
        // Note that in both cases, files follow the standard of having data written in low endian.
        //

        static void EndianMemcpy(char* origin, char* destiny, uint64_t size) 
        {
            if(IsLowEndian()) {
                for(uint64_t i = 0; i < size; i++)
                {
                    destiny[i] = origin[i]; 
                }
            }
            else {
                for(uint64_t i = 0; i < size; i++)
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

            // Read Magic Numbers:
            
            char magic[sizeof(MAGIC) - 1]; // Ignore \0
            
            file.read(magic, sizeof(MAGIC) - 1);

            for(uint64_t i = 0; i < sizeof(MAGIC) - 1; i++)
            {
                if(magic[i] != MAGIC[i]){
                    return false;
                }
            }

            // Read OVO Version:
            
            char version_cstr[sizeof(double)];
            file.read(version_cstr, sizeof(version_cstr));
            
            EndianMemcpy(version_cstr, (char *)&version, sizeof(version_cstr));

            // Read Code Array:
            
            // Read Size of Code Array:
            
            char codesize_cstr[sizeof(uint64_t)];
            file.read(codesize_cstr, sizeof(codesize_cstr));
            
            uint64_t codesize = code.size();
            EndianMemcpy(codesize_cstr, (char *)&codesize, sizeof(codesize_cstr));

            // Read each line of code

            for(uint64_t t = 0; t < codesize; t++)
            {
                char opcode_cstr[sizeof(OPCode)];
                file.read(opcode_cstr, sizeof(opcode_cstr));
                
                uint8_t opcode;
                EndianMemcpy(opcode_cstr, (char *)&opcode, sizeof(opcode_cstr));

                char arg1arg_cstr[sizeof(ArgType)];
                file.read(arg1arg_cstr, sizeof(arg1arg_cstr));
                
                uint8_t arg1arg;
                EndianMemcpy(arg1arg_cstr, (char *)&arg1arg, sizeof(arg1arg_cstr));
                
                char arg1val_cstr[sizeof(uint64_t)];
                file.read(arg1val_cstr, sizeof(arg1val_cstr));
                
                uint64_t arg1val;
                EndianMemcpy(arg1val_cstr, (char *)&arg1val, sizeof(arg1val_cstr));

                char arg2arg_cstr[sizeof(ArgType)];
                file.read(arg2arg_cstr, sizeof(arg2arg_cstr));
                
                uint8_t arg2arg;
                EndianMemcpy(arg2arg_cstr, (char *)&arg2arg, sizeof(arg2arg_cstr));
                
                char arg2val_cstr[sizeof(uint64_t)];
                file.read(arg2val_cstr, sizeof(arg2val_cstr));
                
                uint64_t arg2val;
                EndianMemcpy(arg2val_cstr, (char *)&arg2val, sizeof(arg2val_cstr));

                code.push_back( Code {
                                        static_cast<OPCode>(opcode),
                                        Code::Arg { static_cast<ArgType>(arg1arg), 
                                                    arg1val },
                                        Code::Arg { static_cast<ArgType>(arg2arg), 
                                                    arg2val },
                                });

            }
            
            // Read Text Array:

            // Read Size of Text Array:
            
            char textarraysize_cstr[sizeof(uint64_t)];
            file.read(textarraysize_cstr, sizeof(textarraysize_cstr));
            
            uint64_t textarraysize;
            EndianMemcpy(textarraysize_cstr, (char *)&textarraysize, sizeof(textarraysize_cstr));

            // Read each line of text:
            
            for(uint64_t t = 0; t < textarraysize; t++)
            {
                char textsize_cstr[sizeof(uint64_t)];
                file.read(textsize_cstr, sizeof(textsize_cstr));
                
                uint64_t textsize;
                EndianMemcpy(textsize_cstr, (char *)&textsize, sizeof(textsize_cstr));

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
            
            file.write(MAGIC, sizeof(MAGIC) - 1); // Ignore \0

            // Write OVO Version:
            
            char version_cstr[sizeof(double)];
            EndianMemcpy((char *) &version, version_cstr, sizeof(version_cstr));
            file.write(version_cstr, sizeof(version_cstr));

            // Write Code Array:
            
            // Write Size of Code Array:
            
            uint64_t codesize = code.size();
            char codesize_cstr[sizeof(codesize)];
            EndianMemcpy((char*)&codesize, codesize_cstr, sizeof(codesize_cstr));

            file.write(codesize_cstr, sizeof(codesize_cstr));

            // Write each line of code

            for(auto codeline = code.begin(); codeline != code.end(); codeline++)
            {
                uint8_t opcode = static_cast<uint8_t>(codeline->opcode);
                char opcode_cstr[sizeof(opcode)];
                EndianMemcpy((char *)&opcode, opcode_cstr, sizeof(opcode_cstr));

                uint8_t arg1arg = static_cast<uint8_t>(codeline->arg1.type);
                char arg1arg_cstr[sizeof(arg1arg)];
                EndianMemcpy((char *)&arg1arg, arg1arg_cstr, sizeof(arg1arg_cstr));
                
                uint64_t arg1val = codeline->arg1.value;
                char arg1val_cstr[sizeof(arg1val)];
                EndianMemcpy((char *)&arg1val, arg1val_cstr, sizeof(arg1val_cstr));

                uint8_t arg2arg = static_cast<uint8_t>(codeline->arg2.type);
                char arg2arg_cstr[sizeof(arg2arg)];
                EndianMemcpy((char *)&arg2arg, arg2arg_cstr, sizeof(arg2arg_cstr));
                
                uint64_t arg2val = codeline->arg2.value;
                char arg2val_cstr[sizeof(arg2val)];
                EndianMemcpy((char *)&arg2val, arg2val_cstr, sizeof(arg2val_cstr));
                

                file.write(opcode_cstr, sizeof(opcode_cstr));
                file.write(arg1arg_cstr, sizeof(arg1arg_cstr));
                file.write(arg1val_cstr, sizeof(arg1val_cstr));
                file.write(arg2arg_cstr, sizeof(arg2arg_cstr));
                file.write(arg2val_cstr, sizeof(arg2val_cstr));
            }
            
            // Write Text Array:

            // Write Size of Text Array:
            
            uint64_t textarraysize = text.size();
            char textarraysize_cstr[sizeof(textarraysize)];
            EndianMemcpy((char *)&textarraysize, textarraysize_cstr, sizeof(textarraysize_cstr));

            file.write(textarraysize_cstr, sizeof(textarraysize_cstr));

            // Write each line of text:
            
            for(auto line = text.begin(); line != text.end(); line++)
            {
                std::string textcontent = line->as_string();
                
                uint64_t textsize = textcontent.size() * sizeof(char);
                char textsize_cstr[sizeof(textsize)];
                EndianMemcpy((char *)&textsize, textsize_cstr, sizeof(textsize_cstr));
                
                file.write(textsize_cstr, sizeof(textsize_cstr));
                file.write(textcontent.c_str(), textsize); // Writing Text array is Writing Byte array which does not require Endian conversion
            }
            
            file.close();
            // END
            return true;
        }
    }
}
