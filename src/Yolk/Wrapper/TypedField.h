#pragma once

#include <type_traits>
#include <concepts>
#include <typeindex>
#include <memory>
#include <iostream>
#include <sstream>
#include <iostream>
#include <string>

namespace Yolk
{
    struct TypedField
    {
    public:

        using Pointer = std::shared_ptr<TypedField>;
        struct HB
        {
            virtual void Debug() const { std::cout << "Default\n"; };
            virtual const std::type_index GetType() const { return typeid(void);};
            virtual unsigned int GetSize() const { return 0;};
            virtual bool Copy(HB *, bool) {return false;};
            virtual std::string Print() const { return "void"; };
            virtual HB *clone() const = 0;
            virtual void* GetVoidPointer() const{ return nullptr; };
            virtual void InvokeCast(TypedField& other) const {other.Free();};
            virtual void InvokeBind(TypedField&) const {};
            virtual bool Compare(HB *) const { return false; };
            virtual bool CompareLess(HB *) const { return false;}
            virtual bool CompareGreater(HB *) const { return false;}
            virtual bool CompareLessEqual(HB *) const { return false;}
            virtual bool CompareGreaterEqual(HB *) const { return false;}
            virtual bool TryAdd(HB *){return false;}
            virtual bool TrySub(HB *){return false;}
            virtual bool TryMul(HB *){return false;}
            virtual bool TryDiv(HB *){return false;}
            virtual bool TryMod(HB *){return false;}
            virtual bool TryAnd(HB *){return false;}
            virtual bool TryOr(HB *){return false;}

            virtual bool TryAdd(int) {return false;}
            virtual bool TryAdd(long) {return false;}
            virtual bool TryAdd(unsigned int) {return false;}
            virtual bool TryAdd(unsigned long) {return false;}
            virtual bool TryAdd(float) {return false;}
            virtual bool TryAdd(double) {return false;}
            virtual bool TryAdd(char) {return false;}
            virtual bool TryAdd(unsigned char) {return false;}
            virtual bool TryAdd(bool) {return false;}
            virtual bool TryAdd(std::string) {return false;}
            virtual bool TrySub(int) {return false;}
            virtual bool TrySub(long) {return false;}
            virtual bool TrySub(unsigned int) {return false;}
            virtual bool TrySub(unsigned long) {return false;}
            virtual bool TrySub(float) {return false;}
            virtual bool TrySub(double) {return false;}
            virtual bool TrySub(char) {return false;}
            virtual bool TrySub(unsigned char) {return false;}
            virtual bool TrySub(bool) {return false;}
            virtual bool TryMul(int) {return false;}
            virtual bool TryMul(long) {return false;}
            virtual bool TryMul(unsigned int) {return false;}
            virtual bool TryMul(unsigned long) {return false;}
            virtual bool TryMul(float) {return false;}
            virtual bool TryMul(double) {return false;}
            virtual bool TryMul(char) {return false;}
            virtual bool TryMul(unsigned char) {return false;}
            virtual bool TryMul(bool) {return false;}
            virtual bool TryDiv(int) {return false;}
            virtual bool TryDiv(long) {return false;}
            virtual bool TryDiv(unsigned int) {return false;}
            virtual bool TryDiv(unsigned long) {return false;}
            virtual bool TryDiv(float) {return false;}
            virtual bool TryDiv(double) {return false;}
            virtual bool TryDiv(char) {return false;}
            virtual bool TryDiv(unsigned char) {return false;}
            virtual bool TryDiv(bool) {return false;}
            virtual bool TryMod(int) {return false;}
            virtual bool TryMod(long) {return false;}
            virtual bool TryMod(unsigned int) {return false;}
            virtual bool TryMod(unsigned long) {return false;}
            virtual bool TryMod(float) {return false;}
            virtual bool TryMod(double) {return false;}
            virtual bool TryMod(char) {return false;}
            virtual bool TryMod(unsigned char) {return false;}
            virtual bool TryMod(bool) {return false;}
            virtual bool TryAnd(int) {return false;}
            virtual bool TryAnd(long) {return false;}
            virtual bool TryAnd(unsigned int) {return false;}
            virtual bool TryAnd(unsigned long) {return false;}
            virtual bool TryAnd(float) {return false;}
            virtual bool TryAnd(double) {return false;}
            virtual bool TryAnd(char) {return false;}
            virtual bool TryAnd(unsigned char) {return false;}
            virtual bool TryAnd(bool) {return false;}
            virtual bool TryOr(int) {return false;}
            virtual bool TryOr(long) {return false;}
            virtual bool TryOr(unsigned int) {return false;}
            virtual bool TryOr(unsigned long) {return false;}
            virtual bool TryOr(float) {return false;}
            virtual bool TryOr(double) {return false;}
            virtual bool TryOr(char) {return false;}
            virtual bool TryOr(unsigned char) {return false;}
            virtual bool TryOr(bool) {return false;}

            virtual int Compare(std::string) const {return -1;}
            virtual int Compare(int) const {return -1;}
            virtual int Compare(long) const {return -1;}
            virtual int Compare(unsigned int) const {return -1;}
            virtual int Compare(unsigned long) const {return -1;}
            virtual int Compare(float) const {return -1;}
            virtual int Compare(double) const {return -1;}
            virtual int Compare(char) const {return -1;}
            virtual int Compare(unsigned char) const {return -1;}
            virtual int Compare(bool) const {return -1;}
            virtual int CompareLess(int) const {return -1;}
            virtual int CompareLess(long) const {return -1;}
            virtual int CompareLess(unsigned int) const {return -1;}
            virtual int CompareLess(unsigned long) const {return -1;}
            virtual int CompareLess(float) const {return -1;}
            virtual int CompareLess(double) const {return -1;}
            virtual int CompareLess(char) const {return -1;}
            virtual int CompareLess(unsigned char) const {return -1;}
            virtual int CompareLess(bool) const {return -1;}
            virtual int CompareGreater(int) const {return -1;}
            virtual int CompareGreater(long) const {return -1;}
            virtual int CompareGreater(unsigned int) const {return -1;}
            virtual int CompareGreater(unsigned long) const {return -1;}
            virtual int CompareGreater(float) const {return -1;}
            virtual int CompareGreater(double) const {return -1;}
            virtual int CompareGreater(char) const {return -1;}
            virtual int CompareGreater(unsigned char) const {return -1;}
            virtual int CompareGreater(bool) const {return -1;}
            virtual int CompareLessEqual(int) const {return -1;}
            virtual int CompareLessEqual(long) const {return -1;}
            virtual int CompareLessEqual(unsigned int) const {return -1;}
            virtual int CompareLessEqual(unsigned long) const {return -1;}
            virtual int CompareLessEqual(float) const {return -1;}
            virtual int CompareLessEqual(double) const {return -1;}
            virtual int CompareLessEqual(char) const {return -1;}
            virtual int CompareLessEqual(unsigned char) const {return -1;}
            virtual int CompareLessEqual(bool) const {return -1;}
            virtual int CompareGreaterEqual(int) const {return -1;}
            virtual int CompareGreaterEqual(long) const {return -1;}
            virtual int CompareGreaterEqual(unsigned int) const {return -1;}
            virtual int CompareGreaterEqual(unsigned long) const {return -1;}
            virtual int CompareGreaterEqual(float) const {return -1;}
            virtual int CompareGreaterEqual(double) const {return -1;}
            virtual int CompareGreaterEqual(char) const {return -1;}
            virtual int CompareGreaterEqual(unsigned char) const {return -1;}
            virtual int CompareGreaterEqual(bool) const {return -1;}


        };
        template <typename T>
        struct H : public HB
        {
            using PTR = std::shared_ptr<H<T>>;
            H(T &_value) : value(_value), Type(typeid(_value)){}
            T& Get() const{
                return value;
            }
            void Set(T const &_value){
                value = _value;
            }
            bool Copy(HB *other, bool Force = false)
            {
                constexpr bool Const = std::is_const<T>::value;
                constexpr bool Copyable = requires(T t, T f){
                    t = f;
                };

                if (other->GetType() != GetType() && !Force)
                    return false;

                if constexpr(!Const && Copyable)
                {
                    H<T> *cast = static_cast<H<T> *>(other);
                    value = cast->Get();
                    return true;
                }
                else{
                    if constexpr(Const)
                    {
                        std::cout << "Const" << std::endl;
                    }
                    if constexpr(!Copyable)
                    {
                        std::cout << "Non Copyable" << std::endl;
                    }
                    return false;
                }
            }
            bool Compare(HB *other) const
            {
                
                if(other->GetType() != Type)
                    return false;
                
                
                constexpr bool hasComparison = requires(T t){
                    t == t;
                };

                H<T> *cast = static_cast<H<T> *>(other);

                if constexpr (hasComparison)
                {
                    return cast->value == value;
                }
                else
                {
                    if (GetSize() != cast->GetSize())
                        return false;

                    char *here = (char *)&value;
                    char *there = (char *)&cast->value;

                    bool eq = true;
                    for (unsigned int i = 0; i < GetSize(); i++)
                    {
                        eq = eq && (*here == *there);
                    }
                    return eq;
                }
            }
            bool CompareLess(HB *other) const { 
                if(other->GetType() != Type)
                    return false;
                
                
                constexpr bool hasComparison = requires(T t){
                    t < t;
                };

                H<T> *cast = static_cast<H<T> *>(other);

                if constexpr (hasComparison)
                {
                    return cast->value < value;
                }
                return false;
            }
            bool CompareGreater(HB *other) const { 
                if(other->GetType() != Type)
                    return false;
                
                
                constexpr bool hasComparison = requires(T t){
                    t > t;
                };

                H<T> *cast = static_cast<H<T> *>(other);

                if constexpr (hasComparison)
                {
                    return cast->value > value;
                }
                return false;
            }
            bool CompareLessEqual(HB *other) const { 
                if(other->GetType() != Type)
                    return false;
                
                
                constexpr bool hasComparison = requires(T t){
                    t <= t;
                };

                H<T> *cast = static_cast<H<T> *>(other);

                if constexpr (hasComparison)
                {
                    return cast->value <= value;
                }
                return false;
            }
            bool CompareGreaterEqual(HB *other) const {
                if(other->GetType() != Type)
                    return false;
                
                
                constexpr bool hasComparison = requires(T t){
                    t >= t;
                };

                H<T> *cast = static_cast<H<T> *>(other);

                if constexpr (hasComparison)
                {
                    return cast->value >= value;
                }
                return false;
            }
            bool TryAdd(HB *other)
            {
                if(other->GetType() != Type)
                    return false;
                
                constexpr bool canSum = requires(T t)
                {
                    t = t + t;
                };

                if constexpr (canSum)
                {
                    H<T> *cast = static_cast<H<T> *>(other);
                    value = value + cast->value;
                    return true;
                }
                return false;
            }
            bool TrySub(HB *other)
            {
                if(other->GetType() != Type)
                    return false;
                
                constexpr bool canSub = requires(T t)
                {
                    t = t - t;
                };

                if constexpr (canSub)
                {
                    H<T> *cast = static_cast<H<T> *>(other);
                    value = value - cast->value;
                    return true;
                }
                return false;
            }
            bool TryMul(HB *other)
            {
                if(other->GetType() != Type)
                    return false;
                
                constexpr bool is_bool = std::is_same<bool, T>::value || std::is_same<bool&, T>::value;
                constexpr bool canMul = requires(T t)
                {
                    t = t * t;
                };

                if constexpr (canMul)
                {
                    H<T> *cast = static_cast<H<T> *>(other);
                    if constexpr(is_bool)
                        value = value && cast->value;
                    else
                        value = value * cast->value;
                    return true;
                }
                return false;
            }
            bool TryDiv(HB *other)
            {
                if(other->GetType() != Type)
                    return false;
                
                constexpr bool canDiv = requires(T t)
                {
                    t = t / t;
                };

                if constexpr (canDiv)
                {
                    H<T> *cast = static_cast<H<T> *>(other);
                    value = value / cast->value;
                    return true;
                }
                return false;
            }
            bool TryMod(HB *other)
            {
                if(other->GetType() != Type)
                    return false;
                
                constexpr bool canMod = requires(T t)
                {
                    t = t % t;
                };

                if constexpr (canMod)
                {
                    H<T> *cast = static_cast<H<T> *>(other);
                    value = value % cast->value;
                    return true;
                }
                return false;
            }
            bool TryAnd(HB *other)
            {
                if(other->GetType() != Type)
                    return false;
                
                constexpr bool canAnd = requires(T t)
                {
                    t = t && t;
                };

                if constexpr (canAnd)
                {
                    H<T> *cast = static_cast<H<T> *>(other);
                    value = value && cast->value;
                    return true;
                }
                return false;
            }
            bool TryOr(HB *other)
            {
                if(other->GetType() != Type)
                    return false;
                
                constexpr bool canOr = requires(T t)
                {
                    t = t || t;
                };

                if constexpr (canOr)
                {
                    H<T> *cast = static_cast<H<T> *>(other);
                    value = value || cast->value;
                    return true;
                }
                return false;
            }
            std::string Print() const
            {
                std::stringstream buffer;
                constexpr bool hasShiftOperator = requires(T t){
                    buffer << t << std::endl;
                };

                if constexpr(hasShiftOperator)
                {
                    buffer << value;
                    return buffer.str();
                }
                return "[Unknown Object]";
            }
            void Debug() const{
                std::cout << Type.name() << std::endl;
            }
            const std::type_index GetType() const{
                //return typeid(T);
                return Type;        // <-- Faster
            }
            unsigned int GetSize() const{
                return sizeof(value);
            }
            void *GetVoidPointer() const{
                return (void *)&value;
            }
            HB *clone() const
            {
                HB *out = new H<T>(value);
                return out;
            }
            void InvokeCast(TypedField& other) const
            {
                other.Cast<T>();
            }
            void InvokeBind(TypedField& other) const
            {
                other.Bind<T>(value);
            }

//            bool TryAdd(long other) {return AddHelper<long>(other);}
            template<typename F>
            int CompareHelper(F other) const
            {
                constexpr bool has_comparison = requires(T t)
                {
                    t == other;
                };

                if constexpr(has_comparison)
                {
                    return value == other;
                }
                return -1;
            }
            template<typename F>
            int CompareLessHelper(F other) const
            {
                constexpr bool has_comparison = requires(T t)
                {
                    t < other;
                };

                if constexpr(has_comparison)
                {
                    return value < other;
                }
                return -1;
            }
            template<typename F>
            int CompareGreaterHelper(F other) const
            {
                constexpr bool has_comparison = requires(T t)
                {
                    t > other;
                };

                if constexpr(has_comparison)
                {
                    return value > other;
                }
                return -1;
            }
            template<typename F>
            int CompareLessEqualHelper(F other) const
            {
                constexpr bool has_comparison = requires(T t)
                {
                    t <= other;
                };

                if constexpr(has_comparison)
                {
                    return value <= other;
                }
                return -1;
            }
            template<typename F>
            int CompareGreaterEqualHelper(F other) const
            {
                constexpr bool has_comparison = requires(T t)
                {
                    t >= other;
                };

                if constexpr(has_comparison)
                {
                    return value >= other;
                }
                return -1;
            }
            template<typename F>
            bool AddHelper(F other)
            {
                constexpr bool can_add = requires(T t)
                {
                    t = t + other;
                };
                if constexpr(can_add)
                {
                    value = value + other;
                    return true;
                }
                return false;
            }
            template<typename F>
            bool SubHelper(F other)
            {
                constexpr bool can_add = requires(T t)
                {
                    t = t - other;
                };
                if constexpr(can_add)
                {
                    value = value - other;
                    return true;
                }
                return false;
            }
            template<typename F>
            bool MulHelper(F other)
            {
                constexpr bool is_bool = std::is_same<bool, T>::value || std::is_same<bool&, T>::value;
                constexpr bool can_add = requires(T t)
                {
                    t = t * other;
                };
                if constexpr(can_add)
                {
                    if constexpr(is_bool)
                        value = value && other;
                    else
                        value = value * other;
                    return true;
                }
                return false;
            }
            template<typename F>
            bool DivHelper(F other)
            {
                constexpr bool can_add = requires(T t)
                {
                    t = t / other;
                };
                if constexpr(can_add)
                {
                    value = value / other;
                    return true;
                }
                return false;
            }
            template<typename F>
            bool ModHelper(F other)
            {
                constexpr bool can_add = requires(T t)
                {
                    t = t % other;
                };
                if constexpr(can_add)
                {
                    value = value % other;
                    return true;
                }
                return false;
            }
            template<typename F>
            bool AndHelper(F other)
            {
                constexpr bool can_add = requires(T t)
                {
                    t = t && other;
                };
                if constexpr(can_add)
                {
                    value = value && other;
                    return true;
                }
                return false;
            }
            template<typename F>
            bool OrHelper(F other)
            {
                constexpr bool can_add = requires(T t)
                {
                    t = t || other;
                };
                if constexpr(can_add)
                {
                    value = value || other;
                    return true;
                }
                return false;
            }

            bool TryAdd(int other) {return AddHelper<int>(other);}
            bool TryAdd(long other) {return AddHelper<long>(other);}
            bool TryAdd(unsigned int other) {return AddHelper<unsigned int>(other);}
            bool TryAdd(unsigned long other) {return AddHelper<unsigned long>(other);}
            bool TryAdd(float other) {return AddHelper<float>(other);}
            bool TryAdd(double other) {return AddHelper<double>(other);}
            bool TryAdd(char other) {return AddHelper<char>(other);}
            bool TryAdd(std::string other) {return AddHelper<std::string>(other);}
            bool TryAdd(unsigned char other) {return AddHelper<unsigned char>(other);}
            bool TryAdd(bool other) {return AddHelper<bool>(other);}
            bool TrySub(int other) {return AddHelper<int>(other);}
            bool TrySub(long other) {return AddHelper<long>(other);}
            bool TrySub(unsigned int other) {return AddHelper<unsigned int>(other);}
            bool TrySub(unsigned long other) {return AddHelper<unsigned long>(other);}
            bool TrySub(float other) {return AddHelper<float>(other);}
            bool TrySub(double other) {return AddHelper<double>(other);}
            bool TrySub(char other) {return AddHelper<char>(other);}
            bool TrySub(unsigned char other) {return AddHelper<unsigned char>(other);}
            bool TrySub(bool other) {return AddHelper<bool>(other);}
            bool TryMul(int other) {return AddHelper<int>(other);}
            bool TryMul(long other) {return AddHelper<long>(other);}
            bool TryMul(unsigned int other) {return AddHelper<unsigned int>(other);}
            bool TryMul(unsigned long other) {return AddHelper<unsigned long>(other);}
            bool TryMul(float other) {return AddHelper<float>(other);}
            bool TryMul(double other) {return AddHelper<double>(other);}
            bool TryMul(char other) {return AddHelper<char>(other);}
            bool TryMul(unsigned char other) {return AddHelper<unsigned char>(other);}
            bool TryMul(bool other) {return AddHelper<bool>(other);}
            bool TryDiv(int other) {return AddHelper<int>(other);}
            bool TryDiv(long other) {return AddHelper<long>(other);}
            bool TryDiv(unsigned int other) {return AddHelper<unsigned int>(other);}
            bool TryDiv(unsigned long other) {return AddHelper<unsigned long>(other);}
            bool TryDiv(float other) {return AddHelper<float>(other);}
            bool TryDiv(double other) {return AddHelper<double>(other);}
            bool TryDiv(char other) {return AddHelper<char>(other);}
            bool TryDiv(unsigned char other) {return AddHelper<unsigned char>(other);}
            bool TryDiv(bool other) {return AddHelper<bool>(other);}
            bool TryMod(int other) {return AddHelper<int>(other);}
            bool TryMod(long other) {return AddHelper<long>(other);}
            bool TryMod(unsigned int other) {return AddHelper<unsigned int>(other);}
            bool TryMod(unsigned long other) {return AddHelper<unsigned long>(other);}
            bool TryMod(float other) {return AddHelper<float>(other);}
            bool TryMod(double other) {return AddHelper<double>(other);}
            bool TryMod(char other) {return AddHelper<char>(other);}
            bool TryMod(unsigned char other) {return AddHelper<unsigned char>(other);}
            bool TryMod(bool other) {return AddHelper<bool>(other);}
            bool TryAnd(int other) {return AddHelper<int>(other);}
            bool TryAnd(long other) {return AddHelper<long>(other);}
            bool TryAnd(unsigned int other) {return AddHelper<unsigned int>(other);}
            bool TryAnd(unsigned long other) {return AddHelper<unsigned long>(other);}
            bool TryAnd(float other) {return AddHelper<float>(other);}
            bool TryAnd(double other) {return AddHelper<double>(other);}
            bool TryAnd(char other) {return AddHelper<char>(other);}
            bool TryAnd(unsigned char other) {return AddHelper<unsigned char>(other);}
            bool TryAnd(bool other) {return AddHelper<bool>(other);}
            bool TryOr(int other) {return AddHelper<int>(other);}
            bool TryOr(long other) {return AddHelper<long>(other);}
            bool TryOr(unsigned int other) {return AddHelper<unsigned int>(other);}
            bool TryOr(unsigned long other) {return AddHelper<unsigned long>(other);}
            bool TryOr(float other) {return AddHelper<float>(other);}
            bool TryOr(double other) {return AddHelper<double>(other);}
            bool TryOr(char other) {return AddHelper<char>(other);}
            bool TryOr(unsigned char other) {return AddHelper<unsigned char>(other);}
            bool TryOr(bool other) {return AddHelper<bool>(other);}
        
            template<typename K>
            int Compare(std::string other) const {return CompareHelper(other);}
            int Compare(float other) const{return CompareHelper(other);}
            int Compare(double other) const{return CompareHelper(other);}
            int Compare(bool other) const{return CompareHelper(other);}
            int Compare(int other) const
            {
                constexpr bool is_unsigned = std::is_unsigned<T>::value;
                if constexpr(is_unsigned)
                    return CompareHelper((unsigned int)other);
                else
                    return CompareHelper(other);
            }
            int Compare(long other) const
            {
                constexpr bool is_unsigned = std::is_unsigned<T>::value;
                if constexpr(is_unsigned)
                    return CompareHelper((unsigned long)other);
                else
                    return CompareHelper(other);
            }
            int Compare(char other) const
            {
                constexpr bool is_unsigned = std::is_unsigned<T>::value;
                if constexpr(is_unsigned)
                    return CompareHelper((unsigned char)other);
                else
                    return CompareHelper(other);
            }
            int Compare(unsigned int other) const
            {
                constexpr bool is_unsigned = std::is_unsigned<T>::value;
                if constexpr(is_unsigned)
                    return CompareHelper(other);
                else
                    return CompareHelper((int)other);
            }
            int Compare(unsigned long other) const
            {
                constexpr bool is_unsigned = std::is_unsigned<T>::value;
                if constexpr(is_unsigned)
                    return CompareHelper(other);
                else
                    return CompareHelper((long)other);
            }
            int Compare(unsigned char other) const
            {
                constexpr bool is_unsigned = std::is_unsigned<T>::value;
                if constexpr(is_unsigned)
                    return CompareHelper(other);
                else
                    return CompareHelper((char)other);
            }
            int CompareLess(float other) const{return CompareLessHelper(other);}
            int CompareLess(double other) const{return CompareLessHelper(other);}
            int CompareLess(bool other) const{return CompareLessHelper(other);}
            int CompareLess(int other) const
            {
                constexpr bool is_unsigned = std::is_unsigned<T>::value;
                if constexpr(is_unsigned)
                    return CompareHelper((unsigned int)other);
                else
                    return CompareHelper(other);
            }
            int CompareLess(long other) const
            {
                constexpr bool is_unsigned = std::is_unsigned<T>::value;
                if constexpr(is_unsigned)
                    return CompareHelper((unsigned long)other);
                else
                    return CompareHelper(other);
            }
            int CompareLess(char other) const
            {
                constexpr bool is_unsigned = std::is_unsigned<T>::value;
                if constexpr(is_unsigned)
                    return CompareHelper((unsigned char)other);
                else
                    return CompareHelper(other);
            }
            int CompareLess(unsigned int other) const
            {
                constexpr bool is_unsigned = std::is_unsigned<T>::value;
                if constexpr(is_unsigned)
                    return CompareHelper(other);
                else
                    return CompareHelper((int)other);
            }
            int CompareLess(unsigned long other) const
            {
                constexpr bool is_unsigned = std::is_unsigned<T>::value;
                if constexpr(is_unsigned)
                    return CompareHelper(other);
                else
                    return CompareHelper((long)other);
            }
            int CompareLess(unsigned char other) const
            {
                constexpr bool is_unsigned = std::is_unsigned<T>::value;
                if constexpr(is_unsigned)
                    return CompareHelper(other);
                else
                    return CompareHelper((char)other);
            }
            int CompareGreater(float other) const{return CompareGreaterHelper(other);}
            int CompareGreater(double other) const{return CompareGreaterHelper(other);}
            int CompareGreater(bool other) const{return CompareGreaterHelper(other);}
            int CompareGreater(int other) const
            {
                constexpr bool is_unsigned = std::is_unsigned<T>::value;
                if constexpr(is_unsigned)
                    return CompareHelper((unsigned int)other);
                else
                    return CompareHelper(other);
            }
            int CompareGreater(long other) const
            {
                constexpr bool is_unsigned = std::is_unsigned<T>::value;
                if constexpr(is_unsigned)
                    return CompareHelper((unsigned long)other);
                else
                    return CompareHelper(other);
            }
            int CompareGreater(char other) const
            {
                constexpr bool is_unsigned = std::is_unsigned<T>::value;
                if constexpr(is_unsigned)
                    return CompareHelper((unsigned char)other);
                else
                    return CompareHelper(other);
            }
            int CompareGreater(unsigned int other) const
            {
                constexpr bool is_unsigned = std::is_unsigned<T>::value;
                if constexpr(is_unsigned)
                    return CompareHelper(other);
                else
                    return CompareHelper((int)other);
            }
            int CompareGreater(unsigned long other) const
            {
                constexpr bool is_unsigned = std::is_unsigned<T>::value;
                if constexpr(is_unsigned)
                    return CompareHelper(other);
                else
                    return CompareHelper((long)other);
            }
            int CompareGreater(unsigned char other) const
            {
                constexpr bool is_unsigned = std::is_unsigned<T>::value;
                if constexpr(is_unsigned)
                    return CompareHelper(other);
                else
                    return CompareHelper((char)other);
            }
            int CompareLessEqual(float other) const{return CompareLessEqualHelper(other);}
            int CompareLessEqual(double other) const{return CompareLessEqualHelper(other);}
            int CompareLessEqual(bool other) const{return CompareLessEqualHelper(other);}
            int CompareLessEqual(int other) const
            {
                constexpr bool is_unsigned = std::is_unsigned<T>::value;
                if constexpr(is_unsigned)
                    return CompareHelper((unsigned int)other);
                else
                    return CompareHelper(other);
            }
            int CompareLessEqual(long other) const
            {
                constexpr bool is_unsigned = std::is_unsigned<T>::value;
                if constexpr(is_unsigned)
                    return CompareHelper((unsigned long)other);
                else
                    return CompareHelper(other);
            }
            int CompareLessEqual(char other) const
            {
                constexpr bool is_unsigned = std::is_unsigned<T>::value;
                if constexpr(is_unsigned)
                    return CompareHelper((unsigned char)other);
                else
                    return CompareHelper(other);
            }
            int CompareLessEqual(unsigned int other) const
            {
                constexpr bool is_unsigned = std::is_unsigned<T>::value;
                if constexpr(is_unsigned)
                    return CompareHelper(other);
                else
                    return CompareHelper((int)other);
            }
            int CompareLessEqual(unsigned long other) const
            {
                constexpr bool is_unsigned = std::is_unsigned<T>::value;
                if constexpr(is_unsigned)
                    return CompareHelper(other);
                else
                    return CompareHelper((long)other);
            }
            int CompareLessEqual(unsigned char other) const
            {
                constexpr bool is_unsigned = std::is_unsigned<T>::value;
                if constexpr(is_unsigned)
                    return CompareHelper(other);
                else
                    return CompareHelper((char)other);
            }
            int CompareGreaterEqual(float other) const{return CompareGreaterEqualHelper(other);}
            int CompareGreaterEqual(double other) const{return CompareGreaterEqualHelper(other);}
            int CompareGreaterEqual(bool other) const{return CompareGreaterEqualHelper(other);}
            int CompareGreaterEqual(int other) const
            {
                constexpr bool is_unsigned = std::is_unsigned<T>::value;
                if constexpr(is_unsigned)
                    return CompareHelper((unsigned int)other);
                else
                    return CompareHelper(other);
            }
            int CompareGreaterEqual(long other) const
            {
                constexpr bool is_unsigned = std::is_unsigned<T>::value;
                if constexpr(is_unsigned)
                    return CompareHelper((unsigned long)other);
                else
                    return CompareHelper(other);
            }
            int CompareGreaterEqual(char other) const
            {
                constexpr bool is_unsigned = std::is_unsigned<T>::value;
                if constexpr(is_unsigned)
                    return CompareHelper((unsigned char)other);
                else
                    return CompareHelper(other);
            }
            int CompareGreaterEqual(unsigned int other) const
            {
                constexpr bool is_unsigned = std::is_unsigned<T>::value;
                if constexpr(is_unsigned)
                    return CompareHelper(other);
                else
                    return CompareHelper((int)other);
            }
            int CompareGreaterEqual(unsigned long other) const
            {
                constexpr bool is_unsigned = std::is_unsigned<T>::value;
                if constexpr(is_unsigned)
                    return CompareHelper(other);
                else
                    return CompareHelper((long)other);
            }
            int CompareGreaterEqual(unsigned char other) const
            {
                constexpr bool is_unsigned = std::is_unsigned<T>::value;
                if constexpr(is_unsigned)
                    return CompareHelper(other);
                else
                    return CompareHelper((char)other);
            }


            private:

            T &value;
            std::type_index Type;
        };

        TypedField();
        TypedField(TypedField &ref);
        TypedField(const TypedField &ref);
        ~TypedField();
        template <typename T> 
        TypedField(T &ref);

        template <typename T> 
        void Bind(T &ref);
        void Bind(TypedField& other);

        template <typename T> 
        T &As() const;
        template <typename T> 
        bool SafeAs(T &output) const;
        template <typename T>
        T& FastAs() const;
        
        template <typename T> 
        void Set(T const &value);
        bool Copy(TypedField &ref, bool Force = false);
        
        template <typename T> 
        bool Copy(T &&value, bool Force = false);
        bool operator=(TypedField &ref);
        
        template <typename T>
        bool operator=(T &&value);
        
        template <typename T> 
        bool operator=(T &ref);
        
        bool Compare(TypedField &other) const;
        bool CompareLess(TypedField &other) const; 
        bool CompareGreater(TypedField &other) const;
        bool CompareLessEqual(TypedField &other) const;
        bool CompareGreaterEqual(TypedField &other) const;
        template <typename T> int Compare(T &&other) const;
        template <typename T> int CompareLess(T &&other) const;
        template <typename T> int CompareGreater(T &&other) const;
        template <typename T> int CompareLessEqual(T &&other) const;
        template <typename T> int CompareGreaterEqual(T &&other) const;

        template <typename T>
        bool operator==(T other) const;
        bool operator==(TypedField &other) const;
        
        template <typename T> 
        bool Is();
        
        void Debug();
        void Free();
        bool Valid() const;
        
        void *GetVoidPointer() const;
        template <typename T>
        T* GetPointer() const;
        
        std::string Print() const;
        
        std::type_index GetType() const;
        unsigned int GetSize() const;

        template<typename T>
        void Cast();
        void CastAs(TypedField& other);

        void InvokeCast(TypedField& other);
        void InvokeBind(TypedField& other);

        bool TryAdd(TypedField& other);
        bool TrySub(TypedField& other);
        bool TryMul(TypedField& other);
        bool TryDiv(TypedField& other);
        bool TryMod(TypedField& other);
        bool TryAnd(TypedField& other);
        bool TryOr(TypedField& other);
        
        template <typename T> bool TryAdd(T&& other);
        template <typename T> bool TrySub(T&& other);
        template <typename T> bool TryMul(T&& other);
        template <typename T> bool TryDiv(T&& other);
        template <typename T> bool TryMod(T&& other);
        template <typename T> bool TryAnd(T&& other);
        template <typename T> bool TryOr(T&& other);

        template <typename T>
        static std::shared_ptr<T> Create(T value, TypedField &ref);
        HB *Data;
    };
        inline TypedField::TypedField() : Data(nullptr) {}
        inline TypedField::TypedField(TypedField &ref) : Data(nullptr)
        {
            if (ref.Valid())
                Data = ref.Data->clone();
        }
        inline TypedField::TypedField(const TypedField &ref) : Data(nullptr)
        {
            if (ref.Valid())
                Data = ref.Data->clone();
        }
        template <typename T>
        inline TypedField::TypedField(T &ref)
        {

            Data = new H<T>(ref);
        }
        inline TypedField::~TypedField()
        {
            Free();
        }
        template <typename T>
        inline void TypedField::Bind(T &ref)
        {
            Free();
            Data = new H<T>(ref);
        }
        inline void TypedField::Bind(TypedField& other)
        {
            if(!other.Valid())
                return;
            other.InvokeBind(*this);
        }
        template <typename T>
        inline T& TypedField::As() const
        {
            //return FastAs<T>();

            // Todo: What about this?

            H<T> *cast = static_cast<H<T> *>(Data);
            return cast->Get();
        }

        template <typename T>
        inline bool TypedField::SafeAs(T &output) const
        {
            if (!Valid())
                return false;
            
            if(GetType() != typeid(T))
                return false;
            H<T> *cast = static_cast<H<T> *>(Data);
            output = cast->Get();
            return true;
        }
        template <typename T>
        inline T& TypedField::FastAs() const
        {
            H<T> *cast = reinterpret_cast<H<T> *>(Data);
            return cast->Get();
        }
        template <typename T>
        inline void TypedField::Set(T const &value) // Sets the value without changing reference
        {
            if (!Valid())
                return;
            H<T> *cast = static_cast<H<T> *>(Data);
            return cast->Set(value);
        }
        template <typename T>
        inline bool TypedField::Is()
        {
            if (!Valid())
                return (typeid(T) == typeid(void));
            return (typeid(T) == Data->GetType());
        }

        inline bool TypedField::Copy(TypedField &ref, bool Force)
        {
            if (!ref.Valid() || !Valid())
                return false;
            return Data->Copy(ref.Data, Force);
        }
        template <typename T>
        inline bool TypedField::Copy(T &&value, bool Force)
        {
            if (!Valid())
                return false;
            H<T> h(value);
            return Data->Copy(&h, Force);
        }
        bool inline TypedField::operator=(TypedField &ref)
        {
            return Data->Copy(ref.Data, false);
        }

        template <typename T>
        inline bool TypedField::operator=(T &&value)
        {
            H<T> h(value);
            return Data->Copy(&h, false);
        }

        template <typename T>
        inline bool TypedField::operator=(T &ref)
        {
            if (Data)
            {
                H<T> h(ref);
                return Data->Copy(&h, false);
            }
            Bind(ref);
            return true;
        }

        template <typename T>
        inline bool TypedField::operator==(T other) const
        {
            if (!Valid())
                return false;
            H<T> h(other);
            return Data->Compare(&h);
        }
        inline bool TypedField::operator==(TypedField &other) const
        {
            if (!Valid() || !other.Valid())
                return false;
            return Data->Compare(other.Data);
        }
        inline void TypedField::Debug()
        {
            Data->Debug();
        }
        inline void TypedField::Free()
        {
            if (Data)
                free(Data);
            Data = nullptr;
        }
        inline bool TypedField::Valid() const
        {
            if (Data)
                return true;
            return false;
        }
        inline void* TypedField::GetVoidPointer() const
        {
            if(Data)
                return Data->GetVoidPointer();
            return nullptr;
        }
        template <typename T>
        inline T* TypedField::GetPointer() const
        {
            if(Data){
                void * raw_ptr = Data->GetVoidPointer();
                return (T *)raw_ptr;
            }
            return nullptr;
        }
        inline std::string TypedField::Print() const
        {
            if(Data)
                return Data->Print();
            return "[None]";
        }
        inline std::type_index TypedField::GetType() const
        {
            if (!Valid())
                return typeid(void);
            return Data->GetType();
        }
        inline unsigned int TypedField::GetSize() const
        {
            if (!Valid())
                return 0;
            return Data->GetSize();
        }
        template <typename T>
        inline void TypedField::Cast()
        {
            T& ref = As<T>();
            Free();
            Bind(ref);
        }
        inline void TypedField::CastAs(TypedField& other)
        {
            other.InvokeCast(*this);
        }
        inline void TypedField::InvokeCast(TypedField& other)
        {
            Data->InvokeCast(other);
        }
        inline void TypedField::InvokeBind(TypedField& other)
        {
            if(!Valid())
                return;
            Data->InvokeBind(other);
        }
        template <typename T>
        inline std::shared_ptr<T> TypedField::Create(T value, TypedField &ref)
        {
            std::shared_ptr<T> new_value = std::make_shared<T>(value);
            ref.Bind(*new_value);
            return new_value;
        }
        inline bool TypedField::TryAdd(TypedField& other){
            if(!Valid())
                return false;
            return Data->TryAdd(other.Data);
        }
        inline bool TypedField::TrySub(TypedField& other){
            if(!Valid())
                return false;
            return Data->TrySub(other.Data);
        }
        inline bool TypedField::TryMul(TypedField& other){
            if(!Valid())
                return false;
            return Data->TryMul(other.Data);
        }
        inline bool TypedField::TryDiv(TypedField& other){
            if(!Valid())
                return false;
            return Data->TryDiv(other.Data);
        }
        inline bool TypedField::TryMod(TypedField& other){
            if(!Valid())
                return false;
            return Data->TryMod(other.Data);
        }
        inline bool TypedField::TryAnd(TypedField& other){
            if(!Valid())
                return false;
            return Data->TryAnd(other.Data);
        }
        inline bool TypedField::TryOr(TypedField& other){
            if(!Valid())
                return false;
            return Data->TryOr(other.Data);
        }
        template<typename T>
        inline bool TypedField::TryAdd(T&& other)
        {
            if(!Valid())
                return false;
            return Data->TryAdd(other);
        }
        template<typename T>
        inline bool TypedField::TrySub(T&& other)
        {
            if(!Valid())
                return false;
            return Data->TrySub(other);
        }
        template<typename T>
        inline bool TypedField::TryMul(T&& other)
        {
            if(!Valid())
                return false;
            return Data->TryMul(other);
        }
        template<typename T>
        inline bool TypedField::TryDiv(T&& other)
        {
            if(!Valid())
                return false;
            return Data->TryDiv(other);
        }
        template<typename T>
        inline bool TypedField::TryMod(T&& other)
        {
            if(!Valid())
                return false;
            return Data->TryMod(other);
        }
        template<typename T>
        inline bool TypedField::TryAnd(T&& other)
        {
            if(!Valid())
                return false;
            return Data->TryAnd(other);
        }
        template<typename T>
        inline bool TypedField::TryOr(T&& other)
        {
            if(!Valid())
                return false;
            return Data->TryOr(other);
        }
        inline bool TypedField::Compare(TypedField &other) const
        {
            if (!Valid() || !other.Valid())
                return false;
            return Data->Compare(other.Data);
        }
        inline bool TypedField::CompareLess(TypedField &other) const
        {
            if (!Valid() || !other.Valid())
                return false;
            return Data->CompareLess(other.Data);
        }
        inline bool TypedField::CompareGreater(TypedField &other) const
        {
            if (!Valid() || !other.Valid())
                return false;
            return Data->CompareGreater(other.Data);
        }
        inline bool TypedField::CompareLessEqual(TypedField &other) const
        {
            if (!Valid() || !other.Valid())
                return false;
            return Data->CompareLessEqual(other.Data);
        }
        inline bool TypedField::CompareGreaterEqual(TypedField &other) const
        {
            if (!Valid() || !other.Valid())
                return false;
            return Data->CompareGreaterEqual(other.Data);
        }
        template <typename T>
        int inline TypedField::Compare(T &&other) const
        {
            if (!Valid())
                return -3;
            return Data->Compare(other);
        }
        template <typename T>
        int inline TypedField::CompareLess(T &&other) const
        {
            if (!Valid())
                return -3;
            return Data->CompareLess(other);
        }
        template <typename T>
        int inline TypedField::CompareGreater(T &&other) const
        {
            if (!Valid())
                return -3;
            return Data->CompareGreater(other);
        }
        template <typename T>
        int inline TypedField::CompareLessEqual(T &&other) const
        {
            if (!Valid())
                return -3;
            return Data->CompareLessEqual(other);
        }
        template <typename T>
        int inline TypedField::CompareGreaterEqual(T &&other) const
        {
            if (!Valid())
                return -3;
            return Data->CompareGreaterEqual(other);
        }
        
        
        
        

}