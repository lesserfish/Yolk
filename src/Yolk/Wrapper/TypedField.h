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
            virtual bool Compare(HB *) const { return false; };
            virtual std::string Print() const { return "void"; };
            virtual HB *clone() const = 0;
            virtual void* GetVoidPointer() const{ return nullptr; };
            virtual void InvokeCast(TypedField& other) const {other.Free();};

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
                constexpr bool hasComparison = requires(T t){
                    t == t;
                };

                if (other->GetType() != GetType()) return false;
                H<T> *cast = static_cast<H<T> *>(other);

                if constexpr (hasComparison)
                {
                    return cast->Get() == value;
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
                return typeid(T);
                return Type;
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

        template <typename T> 
        T &As() const;
        template <typename T> 
        bool SafeAs(T &output) const;
        
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
        template <typename T>
        bool Compare(T &&other) const;

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
        template <typename T>
        inline T& TypedField::As() const
        {
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
        inline bool TypedField::Compare(TypedField &other) const
        {
            if (!Valid() || !other.Valid())
                return false;
            return Data->Compare(other.Data);
        }
        template <typename T>
        bool inline TypedField::Compare(T &&other) const
        {
            if (!Valid())
                return false;
            H<T> h(other);
            return Data->Compare(&h);
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
        template <typename T>
        inline std::shared_ptr<T> TypedField::Create(T value, TypedField &ref)
        {
            std::shared_ptr<T> new_value = std::make_shared<T>(value);
            ref.Bind(*new_value);
            return new_value;
        }

}