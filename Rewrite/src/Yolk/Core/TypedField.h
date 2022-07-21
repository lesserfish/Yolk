#pragma once

// TODO: Remove this? Without it, it gives a shit ton of warnings.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-compare"

#include "../Exceptions.h"
#include "../Common.h"
#include <typeindex>
#include <functional>
#include <memory>
#include <string>
#include <concepts>
#include <iostream>
#include <sstream>
#include <exception>

// Relational Macros

// == Macros
#define EQC(Type) virtual bool EQ(Type) {return false;}
#define EQM(Type) bool EQ(Type input) { return EQHelper(input); }
// <= Macros
#define LEC(Type) virtual bool LE(Type) {return false;}
#define LEM(Type) bool LE(Type input) { return LEHelper(input); }
// < Macros
#define LC(Type) virtual bool L(Type) {return false;}
#define LM(Type) bool L(Type input) { return LHelper(input); }
// >= Macros
#define GEC(Type) virtual bool GE(Type) {return false;}
#define GEM(Type) bool GE(Type input) { return GEHelper(input); }
// > Macros
#define GC(Type) virtual bool G(Type) {return false;}
#define GM(Type) bool G(Type input) { return GHelper(input); }
// != Macros
#define NEQC(Type) virtual bool NEQ(Type) {return false;}
#define NEQM(Type) bool NEQ(Type input) { return NEQHelper(input); }

// Arithmetic Operator Macros

// Set Macros
#define SETC(Type) virtual void SET(Type) {}
#define SETM(Type) void SET(Type input) { return SETHelper(input); }
// + Macros
#define PLUSC(Type) virtual void PLUS(Type) {}
#define PLUSM(Type) void PLUS(Type input) { return PLUSHelper(input); }
// - Macros
#define SUBC(Type) virtual void SUB(Type) {}
#define SUBM(Type) void SUB(Type input) { return SUBHelper(input); }
// * Macros
#define PRODC(Type) virtual void PROD(Type) {}
#define PRODM(Type) void PROD(Type input) { return PRODHelper(input); }
// / Macros
#define DIVC(Type) virtual void DIV(Type) {}
#define DIVM(Type) void DIV(Type input) { return DIVHelper(input); }
// % Macros
#define MODC(Type) virtual void MOD(Type) {}
#define MODM(Type) void MOD(Type input) { return MODHelper(input); }

// Logical Operator Macros

// && Macros
#define ANDC(Type) virtual void AND(Type) {}
#define ANDM(Type) void AND(Type input) { return ANDHelper(input); }
// || Macros
#define ORC(Type) virtual void OR(Type) {}
#define ORM(Type) void OR(Type input) { return ORHelper(input); }
// ! Macros
#define NOTC() virtual void NOT() {}
#define NOTM() void NOT() { return NOTHelper(); }
// Bool Macros
#define BOOLC() virtual bool BOOL() {return false;}
#define BOOLM() bool BOOL() { return BOOLHelper(); }


// Elementary Types Macros
#define ARITHMETICC(Type) EQC(Type) \
    LEC(Type)\
    LC(Type)\
    GEC(Type)\
    GC(Type)\
    NEQC(Type)\
    SETC(Type)\
    PLUSC(Type)\
    SUBC(Type)\
    PRODC(Type)\
    DIVC(Type)\
    MODC(Type)\
    ANDC(Type)\
    ORC(Type)

#define ARITHMETICM(Type) EQM(Type) \
    LEM(Type)\
    LM(Type)\
    GEM(Type)\
    GM(Type)\
    NEQM(Type)\
    SETM(Type)\
    PLUSM(Type)\
    SUBM(Type)\
    PRODM(Type)\
    DIVM(Type)\
    MODM(Type)\
    ANDM(Type)\
    ORM(Type)


namespace Yolk {

    struct TFException : public Yolk::Exceptions::Exception {
        private:
            std::string message;
        public:
            TFException(std::string m = "TypedField exception thrown") : Yolk::Exceptions::Exception(m), message(m) {}
        virtual const char* what() const throw() {
            return message.c_str();
        }
    };

    class TypedField {
        public:
                using Pointer = std::shared_ptr<TypedField>;
                struct CopyByValueOut {
                    CopyByValueOut(TypedField::Pointer f, Memory::AbstractData::Pointer d) : field(f), datapointer(d) {}
                    TypedField::Pointer field;
                    Memory::AbstractData::Pointer datapointer;
                };
                struct None {
                public:
                    virtual ~None() {}
                    virtual unsigned int Size() const {return 0;} 
                    virtual const std::type_index Type() const {return typeid(void);}
                    virtual bool Copy(None*) {
                        throw  TFException("Invalid wrapper. Is none.");
                        return false;
                    }
                    virtual None* Clone() const {
                        return new None(); 
                    }
                    virtual CopyByValueOut CopyByValue() {
                        throw TFException("Invalid wrapper. Is none.");
                    }
                    virtual bool Compare(None *) {
                        return false;
                    }
                    virtual std::string Print() const {
                        return "[None]";
                    }
                    virtual void* GetVoidPointer() {
                        throw  TFException("Invalid wrapper. Is none.");
                        return nullptr;
                    };
                    virtual void InvokeBind(TypedField& other) const {
                        other.Free();
                    } 
                    virtual void InvokeCast(TypedField& other) const {
                        other.Free();
                    }
                    virtual bool InvokeEQ(None* ){throw  TFException("Invalid wrapper. Is none."); return false;}
                    virtual bool InvokeLE(None* ){throw  TFException("Invalid wrapper. Is none."); return false;}
                    virtual bool InvokeL(None* ){throw  TFException("Invalid wrapper. Is none."); return false;}
                    virtual bool InvokeGE(None* ){throw  TFException("Invalid wrapper. Is none."); return false;}
                    virtual bool InvokeG(None* ){throw  TFException("Invalid wrapper. Is none."); return false;}
                    virtual bool InvokeNEQ(None* ){throw  TFException("Invalid wrapper. Is none."); return false;}
                    virtual void InvokeSET(None* ){throw  TFException("Invalid wrapper. Is none.");}
                    virtual void InvokePLUS(None* ){throw  TFException("Invalid wrapper. Is none.");}
                    virtual void InvokeSUB(None* ){throw  TFException("Invalid wrapper. Is none.");}
                    virtual void InvokePROD(None* ){throw  TFException("Invalid wrapper. Is none.");}
                    virtual void InvokeDIV(None* ){throw  TFException("Invalid wrapper. Is none.");}
                    virtual void InvokeMOD(None* ){throw  TFException("Invalid wrapper. Is none.");}
                    virtual void InvokeAND(None* ){throw  TFException("Invalid wrapper. Is none.");}
                    virtual void InvokeOR(None* ){throw  TFException("Invalid wrapper. Is none.");}
                    virtual void InvokeNOT(None* ){throw  TFException("Invalid wrapper. Is none.");}

                    template <typename T> bool EQ(T){throw  TFException("Unsupported types."); return false;}
                    template <typename T> bool LE(T){throw  TFException("Unsupported types."); return false;}
                    template <typename T> bool L(T){throw  TFException("Unsupported types."); return false;}
                    template <typename T> bool GE(T){throw  TFException("Unsupported types."); return false;}
                    template <typename T> bool G(T){throw  TFException("Unsupported types."); return false;}
                    template <typename T> bool NEQ(T){throw  TFException("Unsupported types."); return false;}
                    template <typename T> void SET(T){throw  TFException("Unsupported types.");}
                    template <typename T> void PLUS(T){ throw TFException("Unsupported types.");}
                    template <typename T> void SUB(T){ throw TFException("Unsupported types.");}
                    template <typename T> void PROD(T){ throw TFException("Unsupported types.");}
                    template <typename T> void DIV(T){ throw TFException("Unsupported types.");}
                    template <typename T> void MOD(T){ throw TFException("Unsupported types.");}
                    template <typename T> void AND(T){ throw TFException("Unsupported types.");}
                    template <typename T> void OR(T){ throw TFException("Unsupported types.");}
                    
                    // Non-typed method
                    NOTC()
                    BOOLC()

                    // Standard operators
                    EQC(TypedField)
                    LEC(TypedField)
                    LC(TypedField)
                    GEC(TypedField)
                    GC(TypedField)
                    NEQC(TypedField)
                    SETC(TypedField)
                    PLUSC(TypedField)
                    SUBC(TypedField)
                    PRODC(TypedField)
                    DIVC(TypedField)
                    MODC(TypedField)
                    ANDC(TypedField)
                    ORC(TypedField)


                    // int Operations

                    ARITHMETICC(int)
                    
            };

            template <typename T> struct Thing : public None {
                public:
                    Thing(T & _lvalue) : lvalue(_lvalue) {}
                    T& Get() const {
                        return lvalue;
                    }
                    void Set(T const &rvalue) {
                        lvalue = rvalue;
                    }
                    unsigned int Size() const {
                        return sizeof(lvalue);
                    } 
                    const std::type_index Type() const {
                        return typeid(lvalue);
                    }
                    bool Copy(None* other){
                        constexpr bool IsConst = std::is_const<T>::value;
                        constexpr bool IsCopyable = requires(T t, T f){
                            t = f; 
                        };

                        if(other->Type() != Type()){
                            return false;
                        } else if constexpr(IsConst) {
                            return false;
                        } else if constexpr(!IsCopyable) {
                            return false;
                        } else {
                            Thing<T>* cast = static_cast<Thing<T> *>(other);  
                            lvalue = cast->Get();
                        }
                        
                        return true;
                    }
                    bool Compare(None *other){
                        if(other->Type() != Type()){
                            return false;
                        } 
                        constexpr bool canCompare = requires(T lhs, T rhs){
                            lhs == rhs;
                        };
                        
                        Thing<T> *cast = static_cast<Thing<T> *>(other);
                        if constexpr(canCompare){
                            return lvalue == cast->lvalue;
                        } else {
                            if(cast->Size() != Size()){
                                return false;
                            }
                            unsigned char *here = (unsigned char *) &lvalue;
                            unsigned char *there = (unsigned char *) &cast->lvalue;

                            bool eq = true;
                            unsigned int lsize = Size();
                            for(unsigned int i = 0; i < lsize; i++){
                                eq = eq && (*here == *there);
                                here++;
                                there++;
                            }
                            return eq;
                        }
                        return false;
                    }
                    None* Clone() const {
                        None *clone = new Thing<T>(lvalue);
                        return clone;
                    }
                    CopyByValueOut CopyByValue() {
                        constexpr bool canCreate = requires(){
                            new Memory::DynamicData<T>(lvalue);
                        };
                        constexpr bool canFree = requires(){
                            delete(new T(lvalue));
                        };

                        if constexpr(canCreate && canFree) {
                            Memory::AbstractData::Pointer dptr = std::make_shared<Memory::DynamicData<T>>(lvalue);
                            T& ref = dynamic_pointer_cast<Memory::DynamicData<T>>(dptr)->Get();
                            Pointer tfptr(new TypedField(ref));
                            return CopyByValueOut(tfptr, dptr);
                        }
                        throw TFException("Failed to copy by wrapper by value.");
                    }
                    std::string Print() const {
                        std::stringstream buffer;
                        constexpr bool hasShiftOperator = requires(T t){
                            buffer << t << std::endl;
                        };

                        if constexpr(hasShiftOperator)
                        {
                            buffer << lvalue;
                            return buffer.str();
                        }
                        return "[Unknown Object]";
                    }
                    void* GetVoidPointer() {
                        return (void *)&lvalue;
                    };
                    void InvokeBind(TypedField& other) const {
                        other.Bind<T>(lvalue);
                    } 
                    void InvokeCast(TypedField& other) const {
                        other.Cast<T>();
                    }
                    template<typename F> bool EQHelper(F rvalue){
                        constexpr bool canCompare = requires(T lhs, F rhs) {
                            lhs == rhs;
                        };
                        if constexpr(canCompare) {
                            return lvalue == rvalue;
                        }
                        throw TFException("Attempted comparison between unsupported types");
                        return false;
                    }
                    template<typename F> bool LEHelper(F rvalue){
                        constexpr bool canCompare = requires(T lhs, F rhs) {
                            lhs <= rhs;
                        };
                        if constexpr(canCompare) {
                            return lvalue <= rvalue;
                        }
                        throw TFException("Attempted comparison between unsupported types");
						return false;
                    }
                    template<typename F> bool LHelper(F rvalue){
                        constexpr bool canCompare = requires(T lhs, F rhs) {
                            lhs < rhs;
                        };
                        if constexpr(canCompare) {
                            return lvalue < rvalue;
                        }
                        throw TFException("Attempted comparison between unsupported types");
						return false;
                    }
                    template<typename F> bool GEHelper(F rvalue){
                        constexpr bool canCompare = requires(T lhs, F rhs) {
                            lhs >= rhs;
                        };
                        if constexpr(canCompare) {
                            return lvalue >= rvalue;
                        }
                        throw TFException("Attempted comparison between unsupported types");
						return false;
                    }
                    template<typename F> bool GHelper(F rvalue){
                        constexpr bool canCompare = requires(T lhs, F rhs) {
                            lhs > rhs;
                        };
                        if constexpr(canCompare) {
                            return lvalue > rvalue;
                        }
                        throw TFException("Attempted comparison between unsupported types");
						return false;
                    }
                    template<typename F> bool NEQHelper(F rvalue){
                        constexpr bool canCompare = requires(T lhs, F rhs) {
                            lhs != rhs;
                        };
                        if constexpr(canCompare) {
                            return lvalue != rvalue;
                        }
                        throw TFException("Attempted comparison between unsupported types");
						return false;
                    }
                    template<typename F> void SETHelper(F rvalue)
                    {
                        constexpr bool canCompare = requires(T lhs, F rhs) {
                            lhs = rhs;
                        };
                        if constexpr(canCompare)
                        {
                            lvalue = rvalue;
                            return;
                        }
                        throw TFException("Attempted operation between unsupported types");
                    }
                    template<typename F> void PLUSHelper(F rvalue){
                        constexpr bool canCompare = requires(T lhs, F rhs) {
                            lhs = lhs + rhs;
                        };
                        if constexpr(canCompare) {
                            lvalue = lvalue + rvalue;
                            return;
                        }
                        throw TFException("Attempted operation between unsupported types");
						
                    }
                    template<typename F> void SUBHelper(F rvalue){
                        constexpr bool canCompare = requires(T lhs, F rhs) {
                            lhs = lhs - rhs;
                        };
                        if constexpr(canCompare) {
                            lvalue = lvalue - rvalue;
                            return;
                        }
                        throw TFException("Attempted operation between unsupported types");
						
                    }
                    template<typename F> void PRODHelper(F rvalue){
                        constexpr bool canCompare = requires(T lhs, F rhs) {
                            lhs = lhs * rhs;
                        };
                        if constexpr(canCompare) {
                            lvalue = lvalue * rvalue;
                            return;
                        }
                        throw TFException("Attempted operation between unsupported types");
						
                    }
                    template<typename F> void DIVHelper(F rvalue){
                        constexpr bool canCompare = requires(T lhs, F rhs) {
                            lhs = lhs / rhs;
                        };
                        if constexpr(canCompare) {
                            lvalue = lvalue / rvalue;
                            return;
                        }
                        throw TFException("Attempted operation between unsupported types");
						
                    }
                    template<typename F> void MODHelper(F rvalue){
                        constexpr bool canCompare = requires(T lhs, F rhs) {
                            lhs = lhs % rhs;
                        };
                        if constexpr(canCompare) {
                            lvalue = lvalue % rvalue;
                            return;
                        }
                        throw TFException("Attempted operation between unsupported types");
						
                    }
                    template<typename F> void ANDHelper(F rvalue){
                        constexpr bool canCompare = requires(T lhs, F rhs) {
                            lhs = lhs && rhs;
                        };
                        if constexpr(canCompare) {
                            lvalue = lvalue && rvalue;
                            return;
                        }
                        throw TFException("Attempted operation between unsupported types");
						
                    }
                    template<typename F> void ORHelper(F rvalue){
                        constexpr bool canCompare = requires(T lhs, F rhs) {
                            lhs = lhs || rhs;
                        };
                        if constexpr(canCompare) {
                            lvalue = lvalue || rvalue;
                            return;
                        }
                        throw TFException("Attempted operation between unsupported types");
						
                    }
                    void NOTHelper(){
                        constexpr bool canCompare = requires(T lhs) {
                            lhs = !lhs;
                        };
                        if constexpr(canCompare) {
                            lvalue = !lvalue;
                            return;
                        }
                        throw TFException("Attempted operation between unsupported types");
						
                    }
                    bool BOOLHelper(){
                        constexpr bool canCompare = requires(T lhs, bool a) {
                            a = (bool)lhs;
                        };
                        if constexpr(canCompare) {
                            bool out = (bool)lvalue;
                            return out;
                        }
                        throw TFException("Attempted operation between unsupported types");
                    }

                    bool InvokeEQ(None* other){
                        return other->EQ(lvalue);
                    }
                    bool EQ(TypedField otherfield) {
                        None* other = otherfield.data;
                        if(Type() == other->Type()){
                            constexpr bool canCompare = requires(T lhs, T rhs){
                                lhs == rhs;
                            };
                            if constexpr(canCompare) {
                                T othervalue = static_cast<Thing<T> *>(other)->Get();
                                return lvalue == othervalue;
                            }
                            throw TFException("Attempted comparison between unsupported types");
							return false;
                        } else {
                            return other->InvokeEQ(this);
                        }
                    }
                    bool InvokeLE(None* other){
                        return other->LE(lvalue);
                    }
                    bool LE(TypedField otherfield) {
                        None* other = otherfield.data;
                        if(Type() == other->Type()){
                            constexpr bool canCompare = requires(T lhs, T rhs){
                                lhs <= rhs;
                            };
                            if constexpr(canCompare) {
                                T othervalue = static_cast<Thing<T> *>(other)->Get();
                                return lvalue <= othervalue;
                            }
                            throw TFException("Attempted comparison between unsupported types");
							return false;
                        } else {
                            return other->InvokeLE(this);
                        }
                    }
                    bool InvokeL(None* other){
                        return other->L(lvalue);
                    }
                    bool L(TypedField otherfield) {
                        None* other = otherfield.data;
                        if(Type() == other->Type()){
                            constexpr bool canCompare = requires(T lhs, T rhs){
                                lhs < rhs;
                            };
                            if constexpr(canCompare) {
                                T othervalue = static_cast<Thing<T> *>(other)->Get();
                                return lvalue < othervalue;
                            }
                            throw TFException("Attempted comparison between unsupported types");
							return false;
                        } else {
                            return other->InvokeL(this);
                        }
                    }         
                    bool InvokeGE(None* other){
                        return other->LE(lvalue);
                    }
                    bool GE(TypedField otherfield) {
                        None* other = otherfield.data;
                        if(Type() == other->Type()){
                            constexpr bool canCompare = requires(T lhs, T rhs){
                                lhs >= rhs;
                            };
                            if constexpr(canCompare) {
                                T othervalue = static_cast<Thing<T> *>(other)->Get();
                                return lvalue >= othervalue;
                            }
                            throw TFException("Attempted comparison between unsupported types");
							return false;
                        } else {
                            return other->InvokeGE(this);
                        }
                    }
                    bool InvokeG(None* other){
                        return other->G(lvalue);
                    }
                    bool G(TypedField otherfield) {
                        None* other = otherfield.data;
                        if(Type() == other->Type()){
                            constexpr bool canCompare = requires(T lhs, T rhs){
                                lhs > rhs;
                            };
                            if constexpr(canCompare) {
                                T othervalue = static_cast<Thing<T> *>(other)->Get();
                                return lvalue > othervalue;
                            }
                            throw TFException("Attempted comparison between unsupported types");
							return false;
                        } else {
                            return other->InvokeG(this);
                        }
                    }
                    bool InvokeNEQ(None* other){
                        return other->NEQ(lvalue);
                    }
                    bool NEQ(TypedField otherfield) {
                        None* other = otherfield.data;
                        if(Type() == other->Type()){
                            constexpr bool canCompare = requires(T lhs, T rhs){
                                lhs != rhs;
                            };
                            if constexpr(canCompare) {
                                T othervalue = static_cast<Thing<T> *>(other)->Get();
                                return lvalue != othervalue;
                            }
                            throw TFException("Attempted comparison between unsupported types");
							return false;
                        } else {
                            return other->InvokeNEQ(this);
                        }
                    }
                    void InvokeSET(None* other) {
                        other->SET(lvalue);
                    }
                    void InvokePLUS(None* other){
                        other->PLUS(lvalue);
                    }
                    void SET(TypedField otherfield) {
                        None* other = otherfield.data;
                        if(Type() == other->Type()){
                            constexpr bool canCompare = requires(T lhs, T rhs){
                                lhs = rhs;
                            };
                            if constexpr(canCompare) {
                                T othervalue = static_cast<Thing<T> *>(other)->Get();
                                lvalue = othervalue;
                                return;
                            }
                            throw TFException("Attempted operation between unsupported types");
							
                        } else {
                            other->InvokeSET(this);
                        }
                    }

                    void PLUS(TypedField otherfield) {
                        None* other = otherfield.data;
                        if(Type() == other->Type()){
                            constexpr bool canCompare = requires(T lhs, T rhs){
                                lhs = lhs + rhs;
                            };
                            if constexpr(canCompare) {
                                T othervalue = static_cast<Thing<T> *>(other)->Get();
                                lvalue = lvalue + othervalue;
                                return;
                            }
                            throw TFException("Attempted operation between unsupported types");
							
                        } else {
                            other->InvokePLUS(this);
                        }
                    }
                    void InvokeSUB(None* other){
                        other->SUB(lvalue);
                    }
                    void SUB(TypedField otherfield) {
                        None* other = otherfield.data;
                        if(Type() == other->Type()){
                            constexpr bool canCompare = requires(T lhs, T rhs){
                                lhs = lhs - rhs;
                            };
                            if constexpr(canCompare) {
                                T othervalue = static_cast<Thing<T> *>(other)->Get();
                                lvalue = lvalue - othervalue;
                                return;
                            }
                            throw TFException("Attempted operation between unsupported types");
							
                        } else {
                            other->InvokeSUB(this);
                        }
                    }
                    void InvokePROD(None* other){
                        other->PROD(lvalue);
                    }
                    void PROD(TypedField otherfield) {
                        None* other = otherfield.data;
                        if(Type() == other->Type()){
                            constexpr bool canCompare = requires(T lhs, T rhs){
                                lhs = lhs * rhs;
                            };
                            if constexpr(canCompare) {
                                T othervalue = static_cast<Thing<T> *>(other)->Get();
                                lvalue = lvalue * othervalue;
                                return;
                            }
                            throw TFException("Attempted operation between unsupported types");
							
                        } else {
                            other->InvokePROD(this);
                        }
                    }
                    void InvokeDIV(None* other){
                        other->DIV(lvalue);
                    }
                    void DIV(TypedField otherfield) {
                        None* other = otherfield.data;
                        if(Type() == other->Type()){
                            constexpr bool canCompare = requires(T lhs, T rhs){
                                lhs = lhs / rhs;
                            };
                            if constexpr(canCompare) {
                                T othervalue = static_cast<Thing<T> *>(other)->Get();
                                lvalue = lvalue / othervalue;
                                return;
                            }
                            throw TFException("Attempted operation between unsupported types");
							
                        } else {
                            other->InvokeDIV(this);
                        }
                    }
                    void InvokeMOD(None* other){
                        other->MOD(lvalue);
                    }
                    void MOD(TypedField otherfield) {
                        None* other = otherfield.data;
                        if(Type() == other->Type()){
                            constexpr bool canCompare = requires(T lhs, T rhs){
                                lhs = lhs % rhs;
                            };
                            if constexpr(canCompare) {
                                T othervalue = static_cast<Thing<T> *>(other)->Get();
                                lvalue = lvalue % othervalue;
                                return;
                            }
                            throw TFException("Attempted operation between unsupported types");
							
                        } else {
                            other->InvokeMOD(this);
                        }
                    }
                    void InvokeAND(None* other){
                        other->AND(lvalue);
                    }
                    void AND(TypedField otherfield) {
                        None* other = otherfield.data;
                        if(Type() == other->Type()){
                            constexpr bool canCompare = requires(T lhs, T rhs){
                                lhs = lhs && rhs;
                            };
                            if constexpr(canCompare) {
                                T othervalue = static_cast<Thing<T> *>(other)->Get();
                                lvalue = lvalue && othervalue;
                                return;
                            }
                            throw TFException("Attempted operation between unsupported types");
							
                        } else {
                            other->InvokeAND(this);
                        }
                    }
                    void InvokeOR(None* other){
                        other->OR(lvalue);
                    }
                    void OR(TypedField otherfield) {
                        None* other = otherfield.data;
                        if(Type() == other->Type()){
                            constexpr bool canCompare = requires(T lhs, T rhs){
                                lhs = lhs || rhs;
                            };
                            if constexpr(canCompare) {
                                T othervalue = static_cast<Thing<T> *>(other)->Get();
                                lvalue = lvalue || othervalue;
                                return;
                            }
                            throw TFException("Attempted operation between unsupported types");
							
                        } else {
                            other->InvokeOR(this);
                        }
                    }
                    void InvokeNOT(None* other){
                        other->NOT();
                    }
                    

                    NOTM()
                    BOOLM()

                    // int Operations 
                    ARITHMETICM(int)
                    
                private:
                    T& lvalue;
                };
        public:
            TypedField();
            template<typename T> TypedField(T& lvalue);
            TypedField(TypedField& other);
            TypedField(const TypedField& other);
            ~TypedField();

            void Debug() {
                std::string a = "ASD";
                data->EQ(a);
            }

            template<typename T> T& As() const;
            template<typename T> bool SafeAs(T& output) const;

            template<typename T> void Set(T const& value);
            
            bool Copy(TypedField& other);
            template<typename T> bool Copy(T&& other);

            const TypedField& operator=(TypedField& rightside);
            template<typename T> const TypedField& operator=(T&& rightside) const;
            template<typename T> const TypedField& operator=(T& rightside) const;

            bool operator==(TypedField& rightside);
            template<typename T> bool operator==(T rightside) const;

            template<typename T> bool Is() const;

            void Free();

            bool IsNone() const;

            void* GetVoidPointer() const;
            template<typename T> T* GetPointer() const;

            std::string Print() const;

            std::type_index Type() const;
            unsigned int GetSize() const;

            template<typename T> void Cast();
            void CastAs(TypedField& other);

            template<typename T> void Bind(T& lvalue);
            void Bind(TypedField& other);

            void InvokeCast(TypedField& other);
            void InvokeBind(TypedField& other);

            CopyByValueOut CopyByValue();

            template<typename T> bool TryEQ(T funvalue);
            template<typename T> bool TryLE(T funvalue);
            template<typename T> bool TryL(T funvalue);
            template<typename T> bool TryGE(T funvalue);
            template<typename T> bool TryG(T funvalue);
            template<typename T> bool TryNEQ(T funvalue);
            template<typename T> void TrySET(T funvalue);
            template<typename T> void TryPLUS(T funvalue);
            template<typename T> void TrySUB(T funvalue);
            template<typename T> void TryPROD(T funvalue);
            template<typename T> void TryDIV(T funvalue);
            template<typename T> void TryMOD(T funvalue);
            template<typename T> void TryAND(T funvalue);
            template<typename T> void TryOR(T funvalue);
            void TryNOT();
            bool TryBOOL();
        
        private:
            None* data;
    };
    inline TypedField::TypedField(){
        data = new None();
    }
    template<typename T> inline TypedField::TypedField(T& lvalue){
        data = new Thing<T>(lvalue);
    }
    inline TypedField::TypedField(TypedField& other){
        data = other.data->Clone();
    }
    inline TypedField::TypedField(const TypedField& other){
        data = other.data->Clone();
    }
    inline TypedField::~TypedField(){
        delete(data);
    }

    template<typename T> inline T& TypedField::As() const {
        Thing<T>* cast = static_cast<Thing<T> *>(data);
        return cast->Get();
    }
    template<typename T> inline bool TypedField::SafeAs(T& output) const {
        if(Is<T>()){
            Thing<T> *cast = static_cast<Thing<T> *>(data);
            output = cast->Get();
            return true;
        }
        return false;
    }

    template<typename T> inline void TypedField::Set(T const& value){
        if(IsNone()) {
            return;
        }
        Thing<T>* cast = static_cast<Thing<T>*>(data);
        cast->Set(value);
    }
    
    inline bool TypedField::Copy(TypedField& other){
        return data->Copy(other.data);
    }
    inline TypedField::CopyByValueOut TypedField::CopyByValue(){
        return data->CopyByValue();
    }
    template<typename T> inline bool TypedField::Copy(T&& other){
        Thing<T> h(other);
        return data->Copy(&h);
    }

    inline const TypedField& TypedField::operator=(TypedField& rightside) {
        data->Copy(rightside.data);
        return *this;
    }
    template<typename T> inline const TypedField& TypedField::operator=(T&& rightside) const {
        Thing<T> h(rightside);
        data->Copy(&h);
        return *this;
    }
    template<typename T> inline const TypedField& TypedField::operator=(T& rightside) const {
        Thing<T> h(rightside);
        data->Copy(&h);
        return *this;
    }

    inline bool TypedField::operator==(TypedField& rightside){
        return data->Compare(rightside.data);
        
    }
    template<typename T> inline bool TypedField::operator==(T rightside) const {
        Thing<T> h(rightside);
        return data->Compare(&h);
    }

    template<typename T> inline bool TypedField::Is() const {
        return data->Type() == typeid(T);
    }

    inline void TypedField::Free() {
        delete(data);
        data = new None();
    }

    inline bool TypedField::IsNone() const {
        return data->Size() == 0;
    }

    inline void* TypedField::GetVoidPointer() const{
        return data->GetVoidPointer();
    }
    template<typename T> inline T* TypedField::GetPointer() const {
        if(IsNone()){
            return (T *) GetVoidPointer();
        }
        Thing<T> * cast = static_cast<Thing<T>*>(data);
        return cast->GetPointer();
    }

    inline std::string TypedField::Print() const {
        return data->Print();
    }

    inline std::type_index TypedField::Type() const {
        return data->Type();
    }
    inline unsigned int TypedField::GetSize() const {
        return data->Size();
    }

    template<typename T> inline void TypedField::Cast() {
        T& ref = As<T>();
        Free();
        Bind(ref);
    }
    inline void TypedField::CastAs(TypedField& other) {
        other.InvokeCast(*this);
    }

    template<typename T> inline void TypedField::Bind(T& lvalue) {
        delete(data);
        data = new Thing<T>(lvalue);
    }
    inline void TypedField::Bind(TypedField& other){
        other.InvokeBind(*this);
    }
    inline void TypedField::InvokeCast(TypedField& other) {
        data->InvokeCast(other);
    }
    inline void TypedField::InvokeBind(TypedField& other) {
        data->InvokeBind(other);
    }
    template<typename T> inline bool TypedField::TryEQ(T funvalue)
    {
        constexpr bool isFundamental = requires(T other){
            data->EQ(other);
        };
        if constexpr(isFundamental) {
            return data->EQ(funvalue);
        }
        return false;
    }
    template<typename T> inline bool TypedField::TryLE(T funvalue){
        constexpr bool isFundamental = requires(T other){
            data->LE(other);
        };
        if constexpr(isFundamental) {
            return data->LE(funvalue);
        }
        return false;
    }
    template<typename T> inline bool TypedField::TryL(T funvalue){
        constexpr bool isFundamental = requires(T other){
            data->L(other);
        };
        if constexpr(isFundamental) {
            return data->L(funvalue);
        }
        return false;
    }
    template<typename T> inline bool TypedField::TryGE(T funvalue){
        constexpr bool isFundamental = requires(T other){
            data->GE(other);
        };
        if constexpr(isFundamental) {
            return data->GE(funvalue);
        }
        return false;
    }
    template<typename T> inline bool TypedField::TryG(T funvalue){
        constexpr bool isFundamental = requires(T other){
            data->G(other);
        };
        if constexpr(isFundamental) {
            return data->G(funvalue);
        }
        return false;
    }
    template<typename T> inline bool TypedField::TryNEQ(T funvalue){
        constexpr bool isFundamental = requires(T other){
            data->NEQ(other);
        };
        if constexpr(isFundamental) {
            return data->NEQ(funvalue);
        }
        return false;
    }
    template<typename T> inline void TypedField::TrySET(T funvalue){
        constexpr bool isFundamental = requires(T other){
            data->SET(other);
        };
        if constexpr(isFundamental) {
            return data->SET(funvalue);
        }
        
    }
    template<typename T> inline void TypedField::TryPLUS(T funvalue){
        constexpr bool isFundamental = requires(T other){
            data->PLUS(other);
        };
        if constexpr(isFundamental) {
            return data->PLUS(funvalue);
        }
        
    }
    template<typename T> inline void TypedField::TrySUB(T funvalue){
        constexpr bool isFundamental = requires(T other){
            data->SUB(other);
        };
        if constexpr(isFundamental) {
            return data->SUB(funvalue);
        }
        
    }
    template<typename T> inline void TypedField::TryPROD(T funvalue){
        constexpr bool isFundamental = requires(T other){
            data->PROD(other);
        };
        if constexpr(isFundamental) {
            return data->PROD(funvalue);
        }
        
    }
    template<typename T> inline void TypedField::TryDIV(T funvalue){
        constexpr bool isFundamental = requires(T other){
            data->DIV(other);
        };
        if constexpr(isFundamental) {
            return data->DIV(funvalue);
        }
        
    }
    template<typename T> inline void TypedField::TryMOD(T funvalue){
        constexpr bool isFundamental = requires(T other){
            data->MOD(other);
        };
        if constexpr(isFundamental) {
            return data->MOD(funvalue);
        }
        
    }
    template<typename T> inline void TypedField::TryAND(T funvalue){
        constexpr bool isFundamental = requires(T other){
            data->AND(other);
        };
        if constexpr(isFundamental) {
            return data->AND(funvalue);
        }
        
    }
    template<typename T> inline void TypedField::TryOR(T funvalue){
        constexpr bool isFundamental = requires(T other){
            data->OR(other);
        };
        if constexpr(isFundamental) {
            return data->OR(funvalue);
        }
        
    }
    inline void TypedField::TryNOT(){
        constexpr bool isFundamental = requires(){
            data->NOT();
        };
        if constexpr(isFundamental) {
            return data->NOT();
        }
        
    }
    inline bool TypedField::TryBOOL(){
        constexpr bool isFundamental = requires(){
            data->BOOL();
        };
        if constexpr(isFundamental) {
            return data->BOOL();
        }
        
    }

}

#pragma GCC diagnostic pop
