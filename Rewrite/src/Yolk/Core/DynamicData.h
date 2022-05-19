#pragma once

#include "../Common.h"
#include <memory>
#include <typeindex>
#include <iostream>
#include <string>

namespace Yolk {
    namespace Memory {
        typedef unsigned long long int Viewers;

        class MEMID
        {
            private:
            MEMID() : id(0) {}
            MEMID(const MEMID& cpy) = delete;
            MEMID(MEMID&&) = delete;
            MEMID& operator=(MEMID&&) = delete;
            MEMID& operator=(const MEMID&) = delete;
            public:
            static Identifier Next()
            {
                static MEMID* Singleton = new MEMID();
                Identifier out = Singleton->id;
                Singleton->id++;
                return out;
            }
            private:
            Identifier id;
        };

        struct AbstractData {
            using Pointer = std::shared_ptr<AbstractData>;
            virtual ~AbstractData(){}
            virtual Identifier ID() const { return 0; }
            virtual Viewers ViewersCount() const { return 0; }
            virtual Viewers UpdateViewersCount(Viewers) { return 0; }
            virtual std::type_index GetType() const { return typeid(void); }
            virtual AbstractData::Pointer CreateCopyByValue() {return nullptr;}
            virtual void* GetRawPointer() { return nullptr; }
            virtual unsigned int Size() { return 0; }
            virtual void Debug() {}
        };
        
        template <typename T>
        struct DynamicData : public AbstractData {
            public:
            DynamicData() : lvalue(new T()), id(MEMID::Next()), audience(1) {}
            DynamicData(T other) : lvalue(new T(other)), id(MEMID::Next()), audience(1) {}
            ~DynamicData() {
                delete(lvalue);
            }
            
            Identifier ID() const { return id; }
            Viewers ViewersCount() const { return audience; }
            Viewers UpdateViewersCount(Viewers diff) { audience += diff; return audience; }
            std::type_index GetType() const { return typeid(T); }
            AbstractData::Pointer CreateCopyByValue() {
                AbstractData::Pointer out = std::make_shared<DynamicData<T>>(*lvalue);
                return out;
            }
            T& Get() {
                return *lvalue;
            }
            T* GetPointer() {
                return lvalue;
            }
            unsigned int Size() {
                return sizeof(*lvalue);
            }
            void Debug() {
                constexpr bool hasShiftOperator = requires(T* t){
                    std::cout << *t << std::endl;
                };

                if constexpr(hasShiftOperator)
                {
                    std::cout << *lvalue << " - " << audience << std::endl;
                    return;
                }
                std::cout <<  "[Unknown Object] -  " << audience << std::endl;
            }
            private:
            T* lvalue;
            Identifier id;
            Viewers audience;
        };
    }
}
