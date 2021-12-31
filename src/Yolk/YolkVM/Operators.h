#pragma once

#include "../Wrapper/Wrapper.h"
#include "../Memory/MemoryManager/MemoryManager.h"
#include <typeindex>
#include <functional>
#include <unordered_map>
#include <typeindex>


namespace std
{
    template<>
    struct hash<std::pair<std::type_index, std::type_index>>
    {
        size_t operator()(const std::pair<std::type_index, std::type_index>& pair) const
        {
            return pair.first.hash_code() + pair.second.hash_code();
        }
    };
}
namespace Yolk
{
    namespace VM
    {
        class Operator
        {
            using SINGLE = std::type_index;
            using PAIR = std::pair<std::type_index, std::type_index>;
            using UNARY = std::function<Wrapper(Wrapper)>;
            using BINARY = std::function<Wrapper(Wrapper, Wrapper)>;
            
            public:
            Operator(Memory::MemoryManager& _manager ) : manager(_manager){}
            Memory::MemoryManager& GetMemoryManager() const;
            Wrapper EvaluateCast(Wrapper lhs, std::type_index F, bool& status_output);
            Wrapper EvaluateCast(Wrapper lhs, std::type_index F);
            Wrapper EvaluateAdd(Wrapper lhs, Wrapper rhs, bool& status_output);
			Wrapper EvaluateAdd(Wrapper lhs, Wrapper rhs);
			Wrapper EvaluateSubtract(Wrapper lhs, Wrapper rhs, bool& status_output);
			Wrapper EvaluateSubtract(Wrapper lhs, Wrapper rhs);
			Wrapper EvaluateMultiply(Wrapper lhs, Wrapper rhs, bool& status_output);
			Wrapper EvaluateMultiply(Wrapper lhs, Wrapper rhs);
			Wrapper EvaluateDivide(Wrapper lhs, Wrapper rhs, bool& status_output);
			Wrapper EvaluateDivide(Wrapper lhs, Wrapper rhs);
			Wrapper EvaluateModulo(Wrapper lhs, Wrapper rhs, bool& status_output);
			Wrapper EvaluateModulo(Wrapper lhs, Wrapper rhs);
			Wrapper EvaluateEquality(Wrapper lhs, Wrapper rhs, bool& status_output);
			Wrapper EvaluateEquality(Wrapper lhs, Wrapper rhs);
			Wrapper EvaluateLessThan(Wrapper lhs, Wrapper rhs, bool& status_output);
			Wrapper EvaluateLessThan(Wrapper lhs, Wrapper rhs);
			Wrapper EvaluateGreaterThan(Wrapper lhs, Wrapper rhs, bool& status_output);
			Wrapper EvaluateGreaterThan(Wrapper lhs, Wrapper rhs);
			Wrapper EvaluateLessOrEqualThan(Wrapper lhs, Wrapper rhs, bool& status_output);
			Wrapper EvaluateLessOrEqualThan(Wrapper lhs, Wrapper rhs);
			Wrapper EvaluateGreaterOrEqualThan(Wrapper lhs, Wrapper rhs, bool& status_output);
			Wrapper EvaluateGreaterOrEqualThan(Wrapper lhs, Wrapper rhs);
			Wrapper EvaluateAnd(Wrapper lhs, Wrapper rhs, bool& status_output);
			Wrapper EvaluateAnd(Wrapper lhs, Wrapper rhs);
			Wrapper EvaluateOr(Wrapper lhs, Wrapper rhs, bool& status_output);
			Wrapper EvaluateOr(Wrapper lhs, Wrapper rhs);
			
            template <typename T, typename F> void RegisterCast();
            template <typename T, typename F> void RegisterAdd();
			template <typename T, typename F> void RegisterSubtract();
			template <typename T, typename F> void RegisterMultiply();
			template <typename T, typename F> void RegisterDivide();
			template <typename T, typename F> void RegisterModulo();
			template <typename T, typename F> void RegisterEquality();
			template <typename T, typename F> void RegisterLessThan();
			template <typename T, typename F> void RegisterGreaterThan();
			template <typename T, typename F> void RegisterLessOrEqualThan();
			template <typename T, typename F> void RegisterGreaterOrEqualThan();
			template <typename T, typename F> void RegisterAnd();
			template <typename T, typename F> void RegisterOr();
			
            private:
            Memory::MemoryManager& manager;
            std::unordered_map<PAIR, UNARY> castMap;
            std::unordered_map<PAIR, BINARY> addMap;
			std::unordered_map<PAIR, BINARY> subtractMap;
			std::unordered_map<PAIR, BINARY> multiplyMap;
			std::unordered_map<PAIR, BINARY> divideMap;
			std::unordered_map<PAIR, BINARY> moduloMap;
			std::unordered_map<PAIR, BINARY> equalityMap;
			std::unordered_map<PAIR, BINARY> lessthanMap;
			std::unordered_map<PAIR, BINARY> greaterthanMap;
			std::unordered_map<PAIR, BINARY> lessorequalthanMap;
			std::unordered_map<PAIR, BINARY> greaterorequalthanMap;
			std::unordered_map<PAIR, BINARY> andMap;
			std::unordered_map<PAIR, BINARY> orMap;
			
        };
        inline Memory::MemoryManager& Operator::GetMemoryManager() const
        {
            return manager;
        }
        inline Wrapper Operator::EvaluateCast(Wrapper lhs, std::type_index F, bool& status_output)
        {
            PAIR pair(lhs.field->GetType(), F);
            auto find_result = castMap.find(pair);

            if(find_result == castMap.end())
            {
                status_output = false;
                return manager.AllocateMemory<void>();
            }

            auto f = find_result->second;
            Wrapper out = f(lhs);
            status_output = true;
            return out;
        }
        inline Wrapper Operator::EvaluateCast(Wrapper lhs, std::type_index F)
        {
            bool output;
            return EvaluateCast(lhs, F, output);
        }
        
        inline Wrapper Operator::EvaluateAdd(Wrapper lhs, Wrapper rhs, bool& status_output)
        {
            PAIR pair(lhs.field->GetType(), rhs.field->GetType());
            auto find_result = addMap.find(pair);

            if(find_result == addMap.end())
            {
                status_output = false;
                return manager.AllocateMemory<void>();
            }

            auto f = find_result->second;
            Wrapper out = f(lhs, rhs);
            status_output = true;
            return out;
        }
        inline Wrapper Operator::EvaluateAdd(Wrapper lhs, Wrapper rhs)
        {
            bool output;
            return EvaluateAdd(lhs, rhs, output);
        }
        			
        inline Wrapper Operator::EvaluateSubtract(Wrapper lhs, Wrapper rhs, bool& status_output)
        {
            PAIR pair(lhs.field->GetType(), rhs.field->GetType());
            auto find_result = subtractMap.find(pair);

            if(find_result == subtractMap.end())
            {
                status_output = false;
                return manager.AllocateMemory<void>();
            }

            auto f = find_result->second;
            Wrapper out = f(lhs, rhs);
            status_output = true;
            return out;
        }
        inline Wrapper Operator::EvaluateSubtract(Wrapper lhs, Wrapper rhs)
        {
            bool output;
            return EvaluateSubtract(lhs, rhs, output);
        }
        			
        inline Wrapper Operator::EvaluateMultiply(Wrapper lhs, Wrapper rhs, bool& status_output)
        {
            PAIR pair(lhs.field->GetType(), rhs.field->GetType());
            auto find_result = multiplyMap.find(pair);

            if(find_result == multiplyMap.end())
            {
                status_output = false;
                return manager.AllocateMemory<void>();
            }

            auto f = find_result->second;
            Wrapper out = f(lhs, rhs);
            status_output = true;
            return out;
        }
        inline Wrapper Operator::EvaluateMultiply(Wrapper lhs, Wrapper rhs)
        {
            bool output;
            return EvaluateMultiply(lhs, rhs, output);
        }
        			
        inline Wrapper Operator::EvaluateDivide(Wrapper lhs, Wrapper rhs, bool& status_output)
        {
            PAIR pair(lhs.field->GetType(), rhs.field->GetType());
            auto find_result = divideMap.find(pair);

            if(find_result == divideMap.end())
            {
                status_output = false;
                return manager.AllocateMemory<void>();
            }

            auto f = find_result->second;
            Wrapper out = f(lhs, rhs);
            status_output = true;
            return out;
        }
        inline Wrapper Operator::EvaluateDivide(Wrapper lhs, Wrapper rhs)
        {
            bool output;
            return EvaluateDivide(lhs, rhs, output);
        }
        			
        inline Wrapper Operator::EvaluateModulo(Wrapper lhs, Wrapper rhs, bool& status_output)
        {
            PAIR pair(lhs.field->GetType(), rhs.field->GetType());
            auto find_result = moduloMap.find(pair);

            if(find_result == moduloMap.end())
            {
                status_output = false;
                return manager.AllocateMemory<void>();
            }

            auto f = find_result->second;
            Wrapper out = f(lhs, rhs);
            status_output = true;
            return out;
        }
        inline Wrapper Operator::EvaluateModulo(Wrapper lhs, Wrapper rhs)
        {
            bool output;
            return EvaluateModulo(lhs, rhs, output);
        }
        			
        inline Wrapper Operator::EvaluateEquality(Wrapper lhs, Wrapper rhs, bool& status_output)
        {
            PAIR pair(lhs.field->GetType(), rhs.field->GetType());
            auto find_result = equalityMap.find(pair);

            if(find_result == equalityMap.end())
            {
                status_output = false;
                return manager.AllocateMemory<void>();
            }

            auto f = find_result->second;
            Wrapper out = f(lhs, rhs);
            status_output = true;
            return out;
        }
        inline Wrapper Operator::EvaluateEquality(Wrapper lhs, Wrapper rhs)
        {
            bool output;
            return EvaluateEquality(lhs, rhs, output);
        }
        			
        inline Wrapper Operator::EvaluateLessThan(Wrapper lhs, Wrapper rhs, bool& status_output)
        {
            PAIR pair(lhs.field->GetType(), rhs.field->GetType());
            auto find_result = lessthanMap.find(pair);

            if(find_result == lessthanMap.end())
            {
                status_output = false;
                return manager.AllocateMemory<void>();
            }

            auto f = find_result->second;
            Wrapper out = f(lhs, rhs);
            status_output = true;
            return out;
        }
        inline Wrapper Operator::EvaluateLessThan(Wrapper lhs, Wrapper rhs)
        {
            bool output;
            return EvaluateLessThan(lhs, rhs, output);
        }
        			
        inline Wrapper Operator::EvaluateGreaterThan(Wrapper lhs, Wrapper rhs, bool& status_output)
        {
            PAIR pair(lhs.field->GetType(), rhs.field->GetType());
            auto find_result = greaterthanMap.find(pair);

            if(find_result == greaterthanMap.end())
            {
                status_output = false;
                return manager.AllocateMemory<void>();
            }

            auto f = find_result->second;
            Wrapper out = f(lhs, rhs);
            status_output = true;
            return out;
        }
        inline Wrapper Operator::EvaluateGreaterThan(Wrapper lhs, Wrapper rhs)
        {
            bool output;
            return EvaluateGreaterThan(lhs, rhs, output);
        }
        			
        inline Wrapper Operator::EvaluateLessOrEqualThan(Wrapper lhs, Wrapper rhs, bool& status_output)
        {
            PAIR pair(lhs.field->GetType(), rhs.field->GetType());
            auto find_result = lessorequalthanMap.find(pair);

            if(find_result == lessorequalthanMap.end())
            {
                status_output = false;
                return manager.AllocateMemory<void>();
            }

            auto f = find_result->second;
            Wrapper out = f(lhs, rhs);
            status_output = true;
            return out;
        }
        inline Wrapper Operator::EvaluateLessOrEqualThan(Wrapper lhs, Wrapper rhs)
        {
            bool output;
            return EvaluateLessOrEqualThan(lhs, rhs, output);
        }
        			
        inline Wrapper Operator::EvaluateGreaterOrEqualThan(Wrapper lhs, Wrapper rhs, bool& status_output)
        {
            PAIR pair(lhs.field->GetType(), rhs.field->GetType());
            auto find_result = greaterorequalthanMap.find(pair);

            if(find_result == greaterorequalthanMap.end())
            {
                status_output = false;
                return manager.AllocateMemory<void>();
            }

            auto f = find_result->second;
            Wrapper out = f(lhs, rhs);
            status_output = true;
            return out;
        }
        inline Wrapper Operator::EvaluateGreaterOrEqualThan(Wrapper lhs, Wrapper rhs)
        {
            bool output;
            return EvaluateGreaterOrEqualThan(lhs, rhs, output);
        }
        			
        inline Wrapper Operator::EvaluateAnd(Wrapper lhs, Wrapper rhs, bool& status_output)
        {
            PAIR pair(lhs.field->GetType(), rhs.field->GetType());
            auto find_result = andMap.find(pair);

            if(find_result == andMap.end())
            {
                status_output = false;
                return manager.AllocateMemory<void>();
            }

            auto f = find_result->second;
            Wrapper out = f(lhs, rhs);
            status_output = true;
            return out;
        }
        inline Wrapper Operator::EvaluateAnd(Wrapper lhs, Wrapper rhs)
        {
            bool output;
            return EvaluateAnd(lhs, rhs, output);
        }
        			
        inline Wrapper Operator::EvaluateOr(Wrapper lhs, Wrapper rhs, bool& status_output)
        {
            PAIR pair(lhs.field->GetType(), rhs.field->GetType());
            auto find_result = orMap.find(pair);

            if(find_result == orMap.end())
            {
                status_output = false;
                return manager.AllocateMemory<void>();
            }

            auto f = find_result->second;
            Wrapper out = f(lhs, rhs);
            status_output = true;
            return out;
        }
        inline Wrapper Operator::EvaluateOr(Wrapper lhs, Wrapper rhs)
        {
            bool output;
            return EvaluateOr(lhs, rhs, output);
        }
        			
        template<typename T, typename F>
        inline void Operator::RegisterCast()
        {
            auto f = [this](Wrapper lhs)
            {
                T lhst = lhs.field->FastAs<T>();
                Wrapper output = this->GetMemoryManager().AllocateMemory(F(lhst));
                return output;
            };
            PAIR pair(typeid(T), typeid(F));
            UNARY unary(f);
            castMap.insert(std::pair(pair, unary));
        }
        
        template<typename T, typename F>
        inline void Operator::RegisterAdd()
        {
            auto f = [this](Wrapper lhs, Wrapper rhs)
            {
                T lhst = lhs.field->FastAs<T>();
                F rhsf = rhs.field->FastAs<F>();
                Wrapper output = this->GetMemoryManager().AllocateMemory(lhst + rhsf);
                return output;
            };
            PAIR pair(typeid(T), typeid(F));
            BINARY binary(f);
            addMap.insert(std::pair(pair, binary));
        }
        			
        template<typename T, typename F>
        inline void Operator::RegisterSubtract()
        {
            auto f = [this](Wrapper lhs, Wrapper rhs)
            {
                T lhst = lhs.field->FastAs<T>();
                F rhsf = rhs.field->FastAs<F>();
                Wrapper output = this->GetMemoryManager().AllocateMemory(lhst - rhsf);
                return output;
            };
            PAIR pair(typeid(T), typeid(F));
            BINARY binary(f);
            subtractMap.insert(std::pair(pair, binary));
        }
        			
        template<typename T, typename F>
        inline void Operator::RegisterMultiply()
        {
            auto f = [this](Wrapper lhs, Wrapper rhs)
            {
                T lhst = lhs.field->FastAs<T>();
                F rhsf = rhs.field->FastAs<F>();
                Wrapper output = this->GetMemoryManager().AllocateMemory(lhst * rhsf);
                return output;
            };
            PAIR pair(typeid(T), typeid(F));
            BINARY binary(f);
            multiplyMap.insert(std::pair(pair, binary));
        }
        			
        template<typename T, typename F>
        inline void Operator::RegisterDivide()
        {
            auto f = [this](Wrapper lhs, Wrapper rhs)
            {
                T lhst = lhs.field->FastAs<T>();
                F rhsf = rhs.field->FastAs<F>();
                Wrapper output = this->GetMemoryManager().AllocateMemory(lhst / rhsf);
                return output;
            };
            PAIR pair(typeid(T), typeid(F));
            BINARY binary(f);
            divideMap.insert(std::pair(pair, binary));
        }
        			
        template<typename T, typename F>
        inline void Operator::RegisterModulo()
        {
            auto f = [this](Wrapper lhs, Wrapper rhs)
            {
                T lhst = lhs.field->FastAs<T>();
                F rhsf = rhs.field->FastAs<F>();
                Wrapper output = this->GetMemoryManager().AllocateMemory(lhst % rhsf);
                return output;
            };
            PAIR pair(typeid(T), typeid(F));
            BINARY binary(f);
            moduloMap.insert(std::pair(pair, binary));
        }
        			
        template<typename T, typename F>
        inline void Operator::RegisterEquality()
        {
            auto f = [this](Wrapper lhs, Wrapper rhs)
            {
                T lhst = lhs.field->FastAs<T>();
                F rhsf = rhs.field->FastAs<F>();
                Wrapper output = this->GetMemoryManager().AllocateMemory(lhst == rhsf);
                return output;
            };
            PAIR pair(typeid(T), typeid(F));
            BINARY binary(f);
            equalityMap.insert(std::pair(pair, binary));
        }
        			
        template<typename T, typename F>
        inline void Operator::RegisterLessThan()
        {
            auto f = [this](Wrapper lhs, Wrapper rhs)
            {
                T lhst = lhs.field->FastAs<T>();
                F rhsf = rhs.field->FastAs<F>();
                Wrapper output = this->GetMemoryManager().AllocateMemory(lhst < rhsf);
                return output;
            };
            PAIR pair(typeid(T), typeid(F));
            BINARY binary(f);
            lessthanMap.insert(std::pair(pair, binary));
        }
        			
        template<typename T, typename F>
        inline void Operator::RegisterGreaterThan()
        {
            auto f = [this](Wrapper lhs, Wrapper rhs)
            {
                T lhst = lhs.field->FastAs<T>();
                F rhsf = rhs.field->FastAs<F>();
                Wrapper output = this->GetMemoryManager().AllocateMemory(lhst > rhsf);
                return output;
            };
            PAIR pair(typeid(T), typeid(F));
            BINARY binary(f);
            greaterthanMap.insert(std::pair(pair, binary));
        }
        			
        template<typename T, typename F>
        inline void Operator::RegisterLessOrEqualThan()
        {
            auto f = [this](Wrapper lhs, Wrapper rhs)
            {
                T lhst = lhs.field->FastAs<T>();
                F rhsf = rhs.field->FastAs<F>();
                Wrapper output = this->GetMemoryManager().AllocateMemory(lhst <= rhsf);
                return output;
            };
            PAIR pair(typeid(T), typeid(F));
            BINARY binary(f);
            lessorequalthanMap.insert(std::pair(pair, binary));
        }
        			
        template<typename T, typename F>
        inline void Operator::RegisterGreaterOrEqualThan()
        {
            auto f = [this](Wrapper lhs, Wrapper rhs)
            {
                T lhst = lhs.field->FastAs<T>();
                F rhsf = rhs.field->FastAs<F>();
                Wrapper output = this->GetMemoryManager().AllocateMemory(lhst >= rhsf);
                return output;
            };
            PAIR pair(typeid(T), typeid(F));
            BINARY binary(f);
            greaterorequalthanMap.insert(std::pair(pair, binary));
        }
        			
        template<typename T, typename F>
        inline void Operator::RegisterAnd()
        {
            auto f = [this](Wrapper lhs, Wrapper rhs)
            {
                T lhst = lhs.field->FastAs<T>();
                F rhsf = rhs.field->FastAs<F>();
                Wrapper output = this->GetMemoryManager().AllocateMemory(lhst && rhsf);
                return output;
            };
            PAIR pair(typeid(T), typeid(F));
            BINARY binary(f);
            andMap.insert(std::pair(pair, binary));
        }
        			
        template<typename T, typename F>
        inline void Operator::RegisterOr()
        {
            auto f = [this](Wrapper lhs, Wrapper rhs)
            {
                T lhst = lhs.field->FastAs<T>();
                F rhsf = rhs.field->FastAs<F>();
                Wrapper output = this->GetMemoryManager().AllocateMemory(lhst || rhsf);
                return output;
            };
            PAIR pair(typeid(T), typeid(F));
            BINARY binary(f);
            orMap.insert(std::pair(pair, binary));
        }
        			
    }
}
