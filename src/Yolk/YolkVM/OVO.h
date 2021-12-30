#pragma once

#include "../Wrapper/Wrapper.h"
#include "../Memory/MemoryManager/MemoryManager.h"
#include <array>
#include <cstring>
#include <deque>

namespace Yolk
{
    namespace VM
    {
        struct OVO
        {
            using Byte = unsigned char;
            using Usize = long unsigned int;
            struct Instruction
            {
                using CHUNK = unsigned long int;
                enum INSTRUCTION
                {
                    MOV,     // Moves ARG2 onto ARG1. ARG1 is a Register. ARG2 is either a Register or a Data consisting of the name of a Wrapper.
                    SET,     // Sets ARG1 equal to ARG2. ARG1 is a Register. ARG2 is either a symbol consisting of the data type, or DATA consisting of its value.
                    CLONE,   // ARG1 is a new wrapper with new Typed Field with same value as ARG2
                    MOVM,    // Moves ARG1 onto Method Register
                    CALLM,   // Invokes Method Register with current Argument Register, puts output in output Register
                    PUSHAR,  // Pushes ARG1 onto Argument Register
                    POPAR,   // Pops Argument Register onto ARG1
                    CLRAR,   // Clears Argument Register
                    CMP,     // ARG1 == true? (as a wrapper).
                    CMPEQ,   // Compares whether ARG1 equals ARG2
                    CMPLS,   // Compares whether ARG1 < ARG2
                    CMPGT,   // Compares whether ARG1 > ARG2
                    CMPLSEQ, // Compares whether ARG1 <= ARG2
                    CMPGTEQ, // Compares whether ARG1 >= ARG2
                    JNTRUE,  // Jumps to ARG1 if comparison register is true
                    JNFALSE, // Jumps at ARG1 if comparison register is false
                    JMP,     // Unconditionally jumps to ARG1
                    ADD,     // ARG1 = ARG1 + ARG2
                    SUN,     // ARG1 = ARG1 - ARG2
                    MUL,     // ARG1 = ARG1 * ARG2
                    DIV,     // ARG1 = ARG1 / ARG2
                    MOD,     // ARG1 = ARG1 % ARG2
                    AND,     // ARG1 = ARG1 && ARG2 (?)
                    OR,      // ARG1 = ARG1 || ARG2 (?)
                    CAST,    // Casts ARG1 to ARG2. ARG2 can by a Symbol representing elementary type, or DATA with the Name of a wrapper.
                    COPY,    // Copies the value of ARG2 onto ARG1
                    NAMEL,   // Stores the wrapper in ARG1 onto the memory block of YolkVM with name ARG2
                    NAMEG,   // Stores the wrapper in ARG1 onto the memory block of the object with name ARG2.
                    BRUP,    // Branches up
                    BRDW,    // Branches down
                    BRHZ,    // Branches horizontally
                    ZERO,    // Does nothing
                    HALT     // Stops the processor.
                };
                struct ARG
                {
                    enum MODE
                    {
                        NONE,   // Argument is Empty
                        SYMBOL, // Argument represents a Symbol (Which pretty much means Integer. Used only for deciding between subinstructions).
                        REG,    // Argument represents a Register
                        DATA,   // Argument represents Data
                    };
                    MODE mode; // Mode of the argument
                    CHUNK value; // Argument value
                };

                INSTRUCTION instruction;
                ARG arg1;
                ARG arg2;
            };
            struct Data
            {
                using Byte = unsigned char;
                using Usize = long unsigned int;
                enum Mode : Byte
                {
                    VOID,
                    INT,
                    UINT,
                    LONG,
                    ULONG,
                    FLOAT,
                    DOUBLE,
                    BOOL,
                    CHAR,
                    UCHAR,
                    STRING
                };
                std::vector<Byte> content;
                Usize size;
                Mode mode;
                
                Data();
                template<typename T>
                Data(T _content);
                Data(void *_content, Usize _size, Mode _mode);
                
                
                static void ToContainer(std::vector<Byte> *destiny, const void *origin, Usize size);
                static void FromContainer(void *destiny, std::vector<Byte> *origin, Usize size);
                static Wrapper ToWrapper(Data data, Memory::MemoryManager &manager);
                template <typename T>
                static Data GenerateData(T value);
                static Data FromString(std::string Input);
                static std::string ToString(Data data);

                private:

                static Mode GetModeFromString(void*& string);
                static Usize GetSizeFromString(void*& string);
                static void PutModeFromData(Mode mode, void*& string);
                static void PutSizeFromData(Usize size, void*& string);
            };

            std::deque<Instruction> InstructionSet;
            std::deque<Data> DataSet;

            std::string ToString();
            OVO FromString(std::string File);
        };

        inline void OVO::Data::ToContainer(std::vector<Byte> *destiny, const void *origin, Usize size)
        {
            Usize i = 0;
            Byte *byte = (Byte *) origin;
            for(; i < size / sizeof(Byte); i++, byte++)
            {
                Byte c = *byte;
                destiny->push_back(c);
            }
        }
        inline void OVO::Data::FromContainer(void *destiny, std::vector<Byte>* origin, Usize size)
        {
            Usize i = 0;
            Byte *byte = (Byte *) destiny;
            for(; i < size / sizeof(Byte); i++, byte++)
            {
                *byte = origin->at(i);
            }
        }
        inline Wrapper OVO::Data::ToWrapper(Data data, Memory::MemoryManager &manager)
        {
            switch(data.mode)
            {
                case Data::INT:
                {
                    int value_int;
                    FromContainer(&value_int, &data.content, sizeof(int));
                    return manager.AllocateMemory<int>(value_int);
                }
                case Data::UINT:
                {
                    unsigned int value_uint;
                    FromContainer(&value_uint, &data.content, sizeof(unsigned int));
                    return manager.AllocateMemory<unsigned int>(value_uint);
                }
                case Data::LONG:
                {
                    long value_long;
                    FromContainer(&value_long, &data.content, sizeof(long));
                    return manager.AllocateMemory<long>(value_long);
                }
                case Data::ULONG:
                {
                    unsigned long value_ulong;
                    FromContainer(&value_ulong, &data.content, sizeof(unsigned long));
                    return manager.AllocateMemory<unsigned long>(value_ulong);
                }
                case Data::FLOAT:
                {
                    float value_float;
                    FromContainer(&value_float, &data.content, sizeof(float));
                    return manager.AllocateMemory<float>(value_float);
                }
                case Data::DOUBLE:
                {
                    double value_double;
                    FromContainer(&value_double, &data.content, sizeof(double));
                    return manager.AllocateMemory<double>(value_double);
                }
                case Data::BOOL:
                {
                    bool value_bool;
                    FromContainer(&value_bool, &data.content, sizeof(bool));
                    return manager.AllocateMemory<bool>(value_bool);
                }
                case Data::CHAR:
                {
                    char value_char;
                    FromContainer(&value_char, &data.content, sizeof(char));
                    return manager.AllocateMemory<char>(value_char);
                }
                case Data::UCHAR:
                {
                    unsigned char value_uchar;
                    FromContainer(&value_uchar, &data.content, sizeof(unsigned char));
                    return manager.AllocateMemory<unsigned char>(value_uchar);
                }
                case Data::STRING:
                {
                    std::string value_string = "";
                    for(auto byte : data.content)
                    {
                        char character = (char) byte;
                        value_string.insert(value_string.end(), character);
                    }
                    return manager.AllocateMemory<std::string>(value_string);
                }
                case Data::VOID:
                {
                    return manager.GenerateVoidWrapper();
                }
                default:
                {
                    return manager.GenerateVoidWrapper();
                }
            }
        }
        template<typename T>
        inline OVO::Data OVO::Data::GenerateData(T _content)
        {
            return Data(_content);
        }
        template<typename T>
        inline OVO::Data::Data(T) : content(), size(0), mode(Mode::VOID)
        {
        }
        template<> inline OVO::Data::Data(int _content) : content(), size(sizeof(int)), mode(Mode::INT)
        {
            ToContainer(&content, &_content, size);   
        }
        template<> inline OVO::Data::Data(unsigned int _content) : content(), size(sizeof(unsigned int)), mode(Mode::UINT)
        {
            ToContainer(&content, &_content, size);   
        }
        template<> inline OVO::Data::Data(long _content) : content(), size(sizeof(long)), mode(Mode::LONG)
        {
            ToContainer(&content, &_content, size);   
        }
        template<> inline OVO::Data::Data(unsigned long _content) : content(), size(sizeof(unsigned long)), mode(Mode::ULONG)
        {
            ToContainer(&content, &_content, size);   
        }
        template<> inline OVO::Data::Data(float _content) : content(), size(sizeof(float)), mode(Mode::FLOAT)
        {
            ToContainer(&content, &_content, size);   
        }
        template<> inline OVO::Data::Data(double _content) : content(), size(sizeof(double)), mode(Mode::DOUBLE)
        {
            ToContainer(&content, &_content, size);   
        }
        template<> inline OVO::Data::Data(bool _content) : content(), size(sizeof(bool)), mode(Mode::BOOL)
        {
            ToContainer(&content, &_content, size);   
        }
        template<> inline OVO::Data::Data(char _content) : content(), size(sizeof(char)), mode(Mode::CHAR)
        {
            ToContainer(&content, &_content, size);   
        }
        template<> inline OVO::Data::Data(unsigned char _content) : content(), size(sizeof(unsigned char)), mode(Mode::UCHAR)
        {
            ToContainer(&content, &_content, size);   
        }
        template<> inline OVO::Data::Data(std::string _content) : content(), size(sizeof(char) * _content.length()), mode(Mode::STRING)
        { 
            const char* as_cstr = _content.c_str();
            ToContainer(&content, as_cstr, size);
        }
        inline OVO::Data::Data() : content(), size(0), mode(Mode::VOID) {}
        inline OVO::Data::Data(void *_content, Usize _size, Mode _mode) : content(), size(_size), mode(_mode)
        {
            ToContainer(&content, _content, _size);
        }
        inline OVO::Usize OVO::Data::GetSizeFromString(void*& string)
        {
            Usize *sizeptr = (Usize *) string;
            Usize out = *sizeptr;

            sizeptr++;

            string = (void *) sizeptr;

            return out;
        }
        inline void OVO::Data::PutSizeFromData(Usize size, void*& out)
        {
            Usize *sizeptr = (Usize *) out;
            *sizeptr = size;

            sizeptr++;

            out = (void *) sizeptr;
        }
        inline void OVO::Data::PutModeFromData(Mode mode, void*& out)
        {
            Mode *modeptr = (Mode *) out;
            *modeptr = mode;

            modeptr++;

            out = (void *) modeptr;
        }
        inline OVO::Data::Mode OVO::Data::GetModeFromString(void*& string)
        {
            Mode *modeptr = (Mode *) string;
            Mode mode = *modeptr;

            modeptr++;

            string = (void *) modeptr;

            return mode;
        } 
        inline OVO::Data OVO::Data::FromString(std::string _content)
        {
            Usize content_size = _content.length() * sizeof(char);
            Usize header_size = sizeof(Usize) + sizeof(Mode);

            if(header_size >= content_size) // If there is no content.
                return Data();
            
            const char* as_cstr = _content.c_str();
            void *ptr = (void *) as_cstr;

            Usize size = GetSizeFromString(ptr);
            Mode mode = GetModeFromString(ptr);

            return Data(ptr, size, mode);

        }
        inline std::string OVO::Data::ToString(Data data)
        {
            const Usize usize_size = sizeof(Usize);
            const Usize mode_size = sizeof(Mode);
            const Usize content_size = data.size;

            const Usize total_size = usize_size + mode_size + content_size;
            
            Byte *byte_content = new Byte[total_size];

            void *ptr = (void *) byte_content;

            PutSizeFromData(data.size, ptr);
            PutModeFromData(data.mode, ptr);
            FromContainer(ptr, &data.content, data.size);

            std::string output(reinterpret_cast<char const *>(byte_content), total_size);
            free(byte_content);

            return output;
        }
 
    }
}