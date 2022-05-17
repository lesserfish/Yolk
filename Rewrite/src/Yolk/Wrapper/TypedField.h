#pragma once

#include <typeindex>
#include <functional>
#include <string>
#include <concepts>
#include <iostream>
#include <sstream>


// Relational Macros

// == Macros
#define EQC(Type) virtual ComparisonOut EQ(Type) {return ComparisonOut();}
#define EQM(Type) ComparisonOut EQ(Type input) { return EQHelper(input); }
// <= Macros
#define LEC(Type) virtual ComparisonOut LE(Type) {return ComparisonOut();}
#define LEM(Type) ComparisonOut LE(Type input) { return LEHelper(input); }
// < Macros
#define LC(Type) virtual ComparisonOut L(Type) {return ComparisonOut();}
#define LM(Type) ComparisonOut L(Type input) { return LHelper(input); }
// >= Macros
#define GEC(Type) virtual ComparisonOut GE(Type) {return ComparisonOut();}
#define GEM(Type) ComparisonOut GE(Type input) { return GEHelper(input); }
// > Macros
#define GC(Type) virtual ComparisonOut G(Type) {return ComparisonOut();}
#define GM(Type) ComparisonOut G(Type input) { return GHelper(input); }
// != Macros
#define NEQC(Type) virtual ComparisonOut NEQ(Type) {return ComparisonOut();}
#define NEQM(Type) ComparisonOut NEQ(Type input) { return NEQHelper(input); }

// Arithmetic Operator Macros

// + Macros
#define PLUSC(Type) virtual bool PLUS(Type) {return false;}
#define PLUSM(Type) bool PLUS(Type input) { return PLUSHelper(input); }
// - Macros
#define SUBC(Type) virtual bool SUB(Type) {return false;}
#define SUBM(Type) bool SUB(Type input) { return SUBHelper(input); }
// * Macros
#define PRODC(Type) virtual bool PROD(Type) {return false;}
#define PRODM(Type) bool PROD(Type input) { return PRODHelper(input); }
// / Macros
#define DIVC(Type) virtual bool DIV(Type) {return false;}
#define DIVM(Type) bool DIV(Type input) { return DIVHelper(input); }
// % Macros
#define MODC(Type) virtual bool MOD(Type) {return false;}
#define MODM(Type) bool MOD(Type input) { return MODHelper(input); }

// Logical Operator Macros

// && Macros
#define ANDC(Type) virtual bool AND(Type) {return false;}
#define ANDM(Type) bool AND(Type input) { return ANDHelper(input); }
// || Macros
#define ORC(Type) virtual bool OR(Type) {return false;}
#define ORM(Type) bool OR(Type input) { return ORHelper(input); }
// ! Macros
#define NOTC() virtual bool NOT() {return false;}
#define NOTM() bool NOT() { return NOTHelper(); }

namespace Yolk {

    class TypedField {
        public:
                struct ComparisonOut {
                    ComparisonOut(bool o = false, bool v = false, std::string m = "") : ok(o), value(v), message(m) {} 
                    bool ok;
                    bool value;
                    std::string message;
                };
                struct None {
                public:
                    virtual unsigned int Size() const {return 0;} 
                    virtual const std::type_index Type() const {return typeid(void);}
                    virtual bool Copy(None*) {
                        return false;
                    }
                    virtual None* Clone() const {
                        return new None(); 
                    }
                    virtual bool Compare(None *) {
                        return false;
                    }
                    virtual std::string Print() const {
                        return "[None]";
                    }
                    virtual void* GetVoidPointer() {
                        return nullptr;
                    };
                    virtual void InvokeBind(TypedField& other) const {
                        other.Free();
                    } 
                    virtual void InvokeCast(TypedField& other) const {
                        other.Free();
                    }
                    virtual ComparisonOut InvokeEQ(None* ){return ComparisonOut();}
                    virtual ComparisonOut InvokeLE(None* ){return ComparisonOut();}
                    virtual ComparisonOut InvokeL(None* ){return ComparisonOut();}
                    virtual ComparisonOut InvokeGE(None* ){return ComparisonOut();}
                    virtual ComparisonOut InvokeG(None* ){return ComparisonOut();}
                    virtual ComparisonOut InvokeNEQ(None* ){return ComparisonOut();}
                    virtual bool InvokePLUS(None* ){return false;}
                    virtual bool InvokeSUB(None* ){return false;}
                    virtual bool InvokePROD(None* ){return false;}
                    virtual bool InvokeDIV(None* ){return false;}
                    virtual bool InvokeMOD(None* ){return false;}
                    virtual bool InvokeAND(None* ){return false;}
                    virtual bool InvokeOR(None* ){return false;}
                    virtual bool InvokeNOT(None* ){return false;}

                    template <typename T> ComparisonOut EQ(T){ return ComparisonOut();}
                    template <typename T> ComparisonOut LE(T){ return ComparisonOut();}
                    template <typename T> ComparisonOut L(T){ return ComparisonOut();}
                    template <typename T> ComparisonOut GE(T){ return ComparisonOut();}
                    template <typename T> ComparisonOut G(T){ return ComparisonOut();}
                    template <typename T> ComparisonOut NEQ(T){ return ComparisonOut();}
                    template <typename T> bool PLUS(T){ return false;}
                    template <typename T> bool SUB(T){ return false;}
                    template <typename T> bool PROD(T){ return false;}
                    template <typename T> bool DIV(T){ return false;}
                    template <typename T> bool MOD(T){ return false;}
                    template <typename T> bool AND(T){ return false;}
                    template <typename T> bool OR(T){ return false;}
                    
                    // Standard operators
                    EQC(TypedField)
                    LEC(TypedField)
                    LC(TypedField)
                    GEC(TypedField)
                    GC(TypedField)
                    NEQC(TypedField)
                    PLUSC(TypedField)
                    SUBC(TypedField)
                    PRODC(TypedField)
                    DIVC(TypedField)
                    MODC(TypedField)
                    ANDC(TypedField)
                    ORC(TypedField)
                    NOTC()


                    // int Operations
                    EQC(int)
                    LEC(int)
                    LC(int)
                    GEC(int)
                    GC(int)
                    NEQC(int)
                    PLUSC(int)
                    SUBC(int)
                    PRODC(int)
                    DIVC(int)
                    MODC(int)
                    ANDC(int)
                    ORC(int)
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
                    template<typename F> ComparisonOut EQHelper(F rvalue){
                        constexpr bool canCompare = requires(T lhs, F rhs) {
                            lhs == rhs;
                        };
                        if constexpr(canCompare) {
                            return ComparisonOut(true, lvalue == rvalue, "");
                        }
                        return ComparisonOut();
                    }
                    template<typename F> ComparisonOut LEHelper(F rvalue){
                        constexpr bool canCompare = requires(T lhs, F rhs) {
                            lhs <= rhs;
                        };
                        if constexpr(canCompare) {
                            return ComparisonOut(true, lvalue <= rvalue, "");
                        }
                        return ComparisonOut();
                    }
                    template<typename F> ComparisonOut LHelper(F rvalue){
                        constexpr bool canCompare = requires(T lhs, F rhs) {
                            lhs < rhs;
                        };
                        if constexpr(canCompare) {
                            return ComparisonOut(true, lvalue < rvalue, "");
                        }
                        return ComparisonOut();
                    }
                    template<typename F> ComparisonOut GEHelper(F rvalue){
                        constexpr bool canCompare = requires(T lhs, F rhs) {
                            lhs >= rhs;
                        };
                        if constexpr(canCompare) {
                            return ComparisonOut(true, lvalue >= rvalue, "");
                        }
                        return ComparisonOut();
                    }
                    template<typename F> ComparisonOut GHelper(F rvalue){
                        constexpr bool canCompare = requires(T lhs, F rhs) {
                            lhs > rhs;
                        };
                        if constexpr(canCompare) {
                            return ComparisonOut(true, lvalue > rvalue, "");
                        }
                        return ComparisonOut();
                    }
                    template<typename F> ComparisonOut NEQHelper(F rvalue){
                        constexpr bool canCompare = requires(T lhs, F rhs) {
                            lhs != rhs;
                        };
                        if constexpr(canCompare) {
                            return ComparisonOut(true, lvalue != rvalue, "");
                        }
                        return ComparisonOut();
                    }
                    template<typename F> bool PLUSHelper(F rvalue){
                        constexpr bool canCompare = requires(T lhs, F rhs) {
                            lhs = lhs + rhs;
                        };
                        if constexpr(canCompare) {
                            lvalue = lvalue + rvalue;
                            return true;
                        }
                        return false;
                    }
                    template<typename F> bool SUBHelper(F rvalue){
                        constexpr bool canCompare = requires(T lhs, F rhs) {
                            lhs = lhs - rhs;
                        };
                        if constexpr(canCompare) {
                            lvalue = lvalue - rvalue;
                            return true;
                        }
                        return false;
                    }
                    template<typename F> bool PRODHelper(F rvalue){
                        constexpr bool canCompare = requires(T lhs, F rhs) {
                            lhs = lhs * rhs;
                        };
                        if constexpr(canCompare) {
                            lvalue = lvalue * rvalue;
                            return true;
                        }
                        return false;
                    }
                    template<typename F> bool DIVHelper(F rvalue){
                        constexpr bool canCompare = requires(T lhs, F rhs) {
                            lhs = lhs / rhs;
                        };
                        if constexpr(canCompare) {
                            lvalue = lvalue / rvalue;
                            return true;
                        }
                        return false;
                    }
                    template<typename F> bool MODHelper(F rvalue){
                        constexpr bool canCompare = requires(T lhs, F rhs) {
                            lhs = lhs % rhs;
                        };
                        if constexpr(canCompare) {
                            lvalue = lvalue % rvalue;
                            return true;
                        }
                        return false;
                    }
                    template<typename F> bool ANDHelper(F rvalue){
                        constexpr bool canCompare = requires(T lhs, F rhs) {
                            lhs = lhs && rhs;
                        };
                        if constexpr(canCompare) {
                            lvalue = lvalue && rvalue;
                            return true;
                        }
                        return false;
                    }
                    template<typename F> bool ORHelper(F rvalue){
                        constexpr bool canCompare = requires(T lhs, F rhs) {
                            lhs = lhs || rhs;
                        };
                        if constexpr(canCompare) {
                            lvalue = lvalue || rvalue;
                            return true;
                        }
                        return false;
                    }
                    bool NOTHelper(){
                        constexpr bool canCompare = requires(T lhs) {
                            lhs = !lhs;
                        };
                        if constexpr(canCompare) {
                            lvalue = !lvalue;
                            return true;
                        }
                        return false;
                    }

                    ComparisonOut InvokeEQ(None* other){
                        return other->EQ(lvalue);
                    }
                    ComparisonOut EQ(TypedField otherfield) {
                        None* other = otherfield.data;
                        if(Type() == other->Type()){
                            constexpr bool canCompare = requires(T lhs, T rhs){
                                lhs == rhs;
                            };
                            if constexpr(canCompare) {
                                T othervalue = static_cast<Thing<T> *>(other)->Get();
                                return ComparisonOut(true, lvalue == othervalue);
                            }
                            return false;
                        } else {
                            return other->InvokeEQ(this);
                        }
                    }
                    ComparisonOut InvokeLE(None* other){
                        return other->LE(lvalue);
                    }
                    ComparisonOut LE(TypedField otherfield) {
                        None* other = otherfield.data;
                        if(Type() == other->Type()){
                            constexpr bool canCompare = requires(T lhs, T rhs){
                                lhs <= rhs;
                            };
                            if constexpr(canCompare) {
                                T othervalue = static_cast<Thing<T> *>(other)->Get();
                                return ComparisonOut(true, lvalue <= othervalue);
                            }
                            return false;
                        } else {
                            return other->InvokeLE(this);
                        }
                    }
                    ComparisonOut InvokeL(None* other){
                        return other->L(lvalue);
                    }
                    ComparisonOut L(TypedField otherfield) {
                        None* other = otherfield.data;
                        if(Type() == other->Type()){
                            constexpr bool canCompare = requires(T lhs, T rhs){
                                lhs < rhs;
                            };
                            if constexpr(canCompare) {
                                T othervalue = static_cast<Thing<T> *>(other)->Get();
                                return ComparisonOut(true, lvalue < othervalue);
                            }
                            return false;
                        } else {
                            return other->InvokeL(this);
                        }
                    }         
                    ComparisonOut InvokeGE(None* other){
                        return other->LE(lvalue);
                    }
                    ComparisonOut GE(TypedField otherfield) {
                        None* other = otherfield.data;
                        if(Type() == other->Type()){
                            constexpr bool canCompare = requires(T lhs, T rhs){
                                lhs >= rhs;
                            };
                            if constexpr(canCompare) {
                                T othervalue = static_cast<Thing<T> *>(other)->Get();
                                return ComparisonOut(true, lvalue >= othervalue);
                            }
                            return false;
                        } else {
                            return other->InvokeGE(this);
                        }
                    }
                    ComparisonOut InvokeG(None* other){
                        return other->G(lvalue);
                    }
                    ComparisonOut G(TypedField otherfield) {
                        None* other = otherfield.data;
                        if(Type() == other->Type()){
                            constexpr bool canCompare = requires(T lhs, T rhs){
                                lhs > rhs;
                            };
                            if constexpr(canCompare) {
                                T othervalue = static_cast<Thing<T> *>(other)->Get();
                                return ComparisonOut(true, lvalue > othervalue);
                            }
                            return false;
                        } else {
                            return other->InvokeG(this);
                        }
                    }
                    ComparisonOut InvokeNEQ(None* other){
                        return other->NEQ(lvalue);
                    }
                    ComparisonOut NEQ(TypedField otherfield) {
                        None* other = otherfield.data;
                        if(Type() == other->Type()){
                            constexpr bool canCompare = requires(T lhs, T rhs){
                                lhs != rhs;
                            };
                            if constexpr(canCompare) {
                                T othervalue = static_cast<Thing<T> *>(other)->Get();
                                return ComparisonOut(true, lvalue != othervalue);
                            }
                            return false;
                        } else {
                            return other->InvokeNOT(this);
                        }
                    }
                    bool InvokePLUS(None* other){
                        return other->PLUS(lvalue);
                    }
                    bool PLUS(TypedField otherfield) {
                        None* other = otherfield.data;
                        if(Type() == other->Type()){
                            constexpr bool canCompare = requires(T lhs, T rhs){
                                lhs = lhs + rhs;
                            };
                            if constexpr(canCompare) {
                                T othervalue = static_cast<Thing<T> *>(other)->Get();
                                lvalue = lvalue + othervalue;
                                return true;
                            }
                            return false;
                        } else {
                            return other->InvokePLUS(this);
                        }
                    }
                    bool InvokeSUB(None* other){
                        return other->SUB(lvalue);
                    }
                    bool SUB(TypedField otherfield) {
                        None* other = otherfield.data;
                        if(Type() == other->Type()){
                            constexpr bool canCompare = requires(T lhs, T rhs){
                                lhs = lhs - rhs;
                            };
                            if constexpr(canCompare) {
                                T othervalue = static_cast<Thing<T> *>(other)->Get();
                                lvalue = lvalue - othervalue;
                                return true;
                            }
                            return false;
                        } else {
                            return other->InvokeSUB(this);
                        }
                    }
                    bool InvokePROD(None* other){
                        return other->PROD(lvalue);
                    }
                    bool PROD(TypedField otherfield) {
                        None* other = otherfield.data;
                        if(Type() == other->Type()){
                            constexpr bool canCompare = requires(T lhs, T rhs){
                                lhs = lhs * rhs;
                            };
                            if constexpr(canCompare) {
                                T othervalue = static_cast<Thing<T> *>(other)->Get();
                                lvalue = lvalue * othervalue;
                                return true;
                            }
                            return false;
                        } else {
                            return other->InvokePROD(this);
                        }
                    }
                    bool InvokeDIV(None* other){
                        return other->DIV(lvalue);
                    }
                    bool DIV(TypedField otherfield) {
                        None* other = otherfield.data;
                        if(Type() == other->Type()){
                            constexpr bool canCompare = requires(T lhs, T rhs){
                                lhs = lhs / rhs;
                            };
                            if constexpr(canCompare) {
                                T othervalue = static_cast<Thing<T> *>(other)->Get();
                                lvalue = lvalue / othervalue;
                                return true;
                            }
                            return false;
                        } else {
                            return other->InvokeDIV(this);
                        }
                    }
                    bool InvokeMOD(None* other){
                        return other->MOD(lvalue);
                    }
                    bool MOD(TypedField otherfield) {
                        None* other = otherfield.data;
                        if(Type() == other->Type()){
                            constexpr bool canCompare = requires(T lhs, T rhs){
                                lhs = lhs % rhs;
                            };
                            if constexpr(canCompare) {
                                T othervalue = static_cast<Thing<T> *>(other)->Get();
                                lvalue = lvalue % othervalue;
                                return true;
                            }
                            return false;
                        } else {
                            return other->InvokeMOD(this);
                        }
                    }
                    bool InvokeAND(None* other){
                        return other->AND(lvalue);
                    }
                    bool AND(TypedField otherfield) {
                        None* other = otherfield.data;
                        if(Type() == other->Type()){
                            constexpr bool canCompare = requires(T lhs, T rhs){
                                lhs = lhs && rhs;
                            };
                            if constexpr(canCompare) {
                                T othervalue = static_cast<Thing<T> *>(other)->Get();
                                lvalue = lvalue && othervalue;
                                return true;
                            }
                            return false;
                        } else {
                            return other->InvokeAND(this);
                        }
                    }
                    bool InvokeOR(None* other){
                        return other->OR(lvalue);
                    }
                    bool OR(TypedField otherfield) {
                        None* other = otherfield.data;
                        if(Type() == other->Type()){
                            constexpr bool canCompare = requires(T lhs, T rhs){
                                lhs = lhs || rhs;
                            };
                            if constexpr(canCompare) {
                                T othervalue = static_cast<Thing<T> *>(other)->Get();
                                lvalue = lvalue || othervalue;
                                return true;
                            }
                            return false;
                        } else {
                            return other->InvokeOR(this);
                        }
                    }
                    bool InvokeNOT(None* other){
                        return other->NOT();
                    }
                    

                    // int Operations 
                    
                    EQM(int)
                    LEM(int)
                    LM(int)
                    GEM(int)
                    GM(int)
                    NEQM(int)
                    PLUSM(int)
                    SUBM(int)
                    PRODM(int)
                    DIVM(int)
                    MODM(int)
                    ANDM(int)
                    ORM(int)
                    NOTM()
                    
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

            template<typename T> ComparisonOut TryEQ(T funvalue);
            template<typename T> ComparisonOut TryLE(T funvalue);
            template<typename T> ComparisonOut TryL(T funvalue);
            template<typename T> ComparisonOut TryGE(T funvalue);
            template<typename T> ComparisonOut TryG(T funvalue);
            template<typename T> ComparisonOut TryNEQ(T funvalue);
            template<typename T> bool TryPLUS(T funvalue);
            template<typename T> bool TrySUB(T funvalue);
            template<typename T> bool TryPROD(T funvalue);
            template<typename T> bool TryDIV(T funvalue);
            template<typename T> bool TryMOD(T funvalue);
            template<typename T> bool TryAND(T funvalue);
            template<typename T> bool TryOR(T funvalue);
            bool TryNOT();
        
        private:
            None* data;
    };
    TypedField::TypedField(){
        data = new None();
    }
    template<typename T> TypedField::TypedField(T& lvalue){
        data = new Thing<T>(lvalue);
    }
    TypedField::TypedField(TypedField& other){
        data = other.data->Clone();
    }
    TypedField::TypedField(const TypedField& other){
        data = other.data->Clone();
    }
    TypedField::~TypedField(){
        free(data);
    }

    template<typename T> T& TypedField::As() const {
        Thing<T>* cast = static_cast<Thing<T> *>(data);
        return cast->Get();
    }
    template<typename T> bool TypedField::SafeAs(T& output) const {
        if(Is<T>()){
            Thing<T> *cast = static_cast<Thing<T> *>(data);
            output = cast->Get();
            return true;
        }
        return false;
    }

    template<typename T> void TypedField::Set(T const& value){
        if(IsNone()) {
            return;
        }
        Thing<T>* cast = static_cast<Thing<T>*>(data);
        cast->Set(value);
    }
    
    bool TypedField::Copy(TypedField& other){
        return data->Copy(other.data);
    }
    template<typename T> bool TypedField::Copy(T&& other){
        Thing<T> h(other);
        return data->Copy(&h);
    }

    const TypedField& TypedField::operator=(TypedField& rightside) {
        data->Copy(rightside.data);
        return *this;
    }
    template<typename T> const TypedField& TypedField::operator=(T&& rightside) const {
        Thing<T> h(rightside);
        data->Copy(&h);
        return *this;
    }
    template<typename T> const TypedField& TypedField::operator=(T& rightside) const {
        Thing<T> h(rightside);
        data->Copy(&h);
        return *this;
    }

    bool TypedField::operator==(TypedField& rightside){
        return data->Compare(rightside.data);
        
    }
    template<typename T> bool TypedField::operator==(T rightside) const {
        Thing<T> h(rightside);
        return data->Compare(&h);
    }

    template<typename T> bool TypedField::Is() const {
        return data->Type() == typeid(T);
    }

    void TypedField::Free() {
        free(data);
        data = new None();
    }

    bool TypedField::IsNone() const {
        return data->Size() == 0;
    }

    void* TypedField::GetVoidPointer() const{
        return data->GetVoidPointer();
    }
    template<typename T> T* TypedField::GetPointer() const {
        if(IsNone()){
            return (T *) GetVoidPointer();
        }
        Thing<T> * cast = static_cast<Thing<T>*>(data);
        return cast->GetPointer();
    }

    std::string TypedField::Print() const {
        return data->Print();
    }

    std::type_index TypedField::Type() const {
        return data->Type();
    }
    unsigned int TypedField::GetSize() const {
        return data->Size();
    }

    template<typename T> void TypedField::Cast() {
        T& ref = As<T>();
        Free();
        Bind(ref);
    }
    void TypedField::CastAs(TypedField& other) {
        other.InvokeCast(*this);
    }

    template<typename T> void TypedField::Bind(T& lvalue) {
        free(data);
        data = new Thing<T>(lvalue);
    }
    void TypedField::Bind(TypedField& other){
        other.InvokeBind(*this);
    }
    void TypedField::InvokeCast(TypedField& other) {
        data->InvokeCast(other);
    }
    void TypedField::InvokeBind(TypedField& other) {
        data->InvokeBind(other);
    }
    template<typename T> TypedField::ComparisonOut TypedField::TryEQ(T funvalue)
    {
        constexpr bool isFundamental = requires(T other){
            data->EQ(other);
        };
        if constexpr(isFundamental) {
            return data->EQ(funvalue);
        }
        return ComparisonOut();
    }
    template<typename T> TypedField::ComparisonOut TypedField::TryLE(T funvalue){
        constexpr bool isFundamental = requires(T other){
            data->LE(other);
        };
        if constexpr(isFundamental) {
            return data->LE(funvalue);
        }
        return ComparisonOut();
    }
    template<typename T> TypedField::ComparisonOut TypedField::TryL(T funvalue){
        constexpr bool isFundamental = requires(T other){
            data->L(other);
        };
        if constexpr(isFundamental) {
            return data->L(funvalue);
        }
        return ComparisonOut();
    }
    template<typename T> TypedField::ComparisonOut TypedField::TryGE(T funvalue){
        constexpr bool isFundamental = requires(T other){
            data->GE(other);
        };
        if constexpr(isFundamental) {
            return data->GE(funvalue);
        }
        return ComparisonOut();
    }
    template<typename T> TypedField::ComparisonOut TypedField::TryG(T funvalue){
        constexpr bool isFundamental = requires(T other){
            data->G(other);
        };
        if constexpr(isFundamental) {
            return data->G(funvalue);
        }
        return ComparisonOut();
    }
    template<typename T> TypedField::ComparisonOut TypedField::TryNEQ(T funvalue){
        constexpr bool isFundamental = requires(T other){
            data->NEQ(other);
        };
        if constexpr(isFundamental) {
            return data->NEQ(funvalue);
        }
        return ComparisonOut();
    }
    template<typename T> bool TypedField::TryPLUS(T funvalue){
        constexpr bool isFundamental = requires(T other){
            data->PLUS(other);
        };
        if constexpr(isFundamental) {
            return data->PLUS(funvalue);
        }
        return false;
    }
    template<typename T> bool TypedField::TrySUB(T funvalue){
        constexpr bool isFundamental = requires(T other){
            data->SUB(other);
        };
        if constexpr(isFundamental) {
            return data->SUB(funvalue);
        }
        return false;
    }
    template<typename T> bool TypedField::TryPROD(T funvalue){
        constexpr bool isFundamental = requires(T other){
            data->PROD(other);
        };
        if constexpr(isFundamental) {
            return data->PROD(funvalue);
        }
        return false;
    }
    template<typename T> bool TypedField::TryDIV(T funvalue){
        constexpr bool isFundamental = requires(T other){
            data->DIV(other);
        };
        if constexpr(isFundamental) {
            return data->DIV(funvalue);
        }
        return false;
    }
    template<typename T> bool TypedField::TryMOD(T funvalue){
        constexpr bool isFundamental = requires(T other){
            data->MOD(other);
        };
        if constexpr(isFundamental) {
            return data->MOD(funvalue);
        }
        return false;
    }
    template<typename T> bool TypedField::TryAND(T funvalue){
        constexpr bool isFundamental = requires(T other){
            data->AND(other);
        };
        if constexpr(isFundamental) {
            return data->AND(funvalue);
        }
        return false;
    }
    template<typename T> bool TypedField::TryOR(T funvalue){
        constexpr bool isFundamental = requires(T other){
            data->OR(other);
        };
        if constexpr(isFundamental) {
            return data->OR(funvalue);
        }
        return false;
    }
    bool TypedField::TryNOT(){
        constexpr bool isFundamental = requires(){
            data->NOT();
        };
        if constexpr(isFundamental) {
            return data->NOT();
        }
        return false;
    }

}
