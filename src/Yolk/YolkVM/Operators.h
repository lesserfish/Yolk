#pragma once

#include "../Wrapper/Wrapper.h"
#include "../Memory/MemoryManager/MemoryManager.h"
#include <typeindex>
#include <functional>
#include <map>
#include <typeindex>
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
			Wrapper EvaluateCAdd(Wrapper lhs, Wrapper rhs, bool& status_output);
			Wrapper EvaluateCAdd(Wrapper lhs, Wrapper rhs);
			Wrapper EvaluateCSubtract(Wrapper lhs, Wrapper rhs, bool& status_output);
			Wrapper EvaluateCSubtract(Wrapper lhs, Wrapper rhs);
			Wrapper EvaluateCMultiply(Wrapper lhs, Wrapper rhs, bool& status_output);
			Wrapper EvaluateCMultiply(Wrapper lhs, Wrapper rhs);
			Wrapper EvaluateCDivide(Wrapper lhs, Wrapper rhs, bool& status_output);
			Wrapper EvaluateCDivide(Wrapper lhs, Wrapper rhs);
			Wrapper EvaluateEquality(Wrapper lhs, Wrapper rhs, bool& status_output);
			Wrapper EvaluateEquality(Wrapper lhs, Wrapper rhs);
			Wrapper EvaluateInequality(Wrapper lhs, Wrapper rhs, bool& status_output);
			Wrapper EvaluateInequality(Wrapper lhs, Wrapper rhs);
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
			Wrapper EvaluatePlusPlus(Wrapper lhs, bool& status_output);
			Wrapper EvaluatePlusPlus(Wrapper lhs);
			Wrapper EvaluateLessLess(Wrapper lhs, bool& status_output);
			Wrapper EvaluateLessLess(Wrapper lhs);
			Wrapper EvaluateNegation(Wrapper lhs, bool& status_output);
			Wrapper EvaluateNegation(Wrapper lhs);
			
            template <typename T, typename F> void RegisterAdd();
			template <typename T, typename F> void RegisterSubtract();
			template <typename T, typename F> void RegisterMultiply();
			template <typename T, typename F> void RegisterDivide();
			template <typename T, typename F> void RegisterModulo();
			template <typename T, typename F> void RegisterCAdd();
			template <typename T, typename F> void RegisterCSubtract();
			template <typename T, typename F> void RegisterCMultiply();
			template <typename T, typename F> void RegisterCDivide();
			template <typename T, typename F> void RegisterEquality();
			template <typename T, typename F> void RegisterInequality();
			template <typename T, typename F> void RegisterLessThan();
			template <typename T, typename F> void RegisterGreaterThan();
			template <typename T, typename F> void RegisterLessOrEqualThan();
			template <typename T, typename F> void RegisterGreaterOrEqualThan();
			template <typename T, typename F> void RegisterAnd();
			template <typename T, typename F> void RegisterOr();
			template <typename T> void RegisterPlusPlus();
			template <typename T> void RegisterLessLess();
			template <typename T> void RegisterNegation();
			
            private:
            Memory::MemoryManager& manager;
            std::map<PAIR, BINARY> addMap;
			std::map<PAIR, BINARY> subtractMap;
			std::map<PAIR, BINARY> multiplyMap;
			std::map<PAIR, BINARY> divideMap;
			std::map<PAIR, BINARY> moduloMap;
			std::map<PAIR, BINARY> caddMap;
			std::map<PAIR, BINARY> csubtractMap;
			std::map<PAIR, BINARY> cmultiplyMap;
			std::map<PAIR, BINARY> cdivideMap;
			std::map<PAIR, BINARY> equalityMap;
			std::map<PAIR, BINARY> inequalityMap;
			std::map<PAIR, BINARY> lessthanMap;
			std::map<PAIR, BINARY> greaterthanMap;
			std::map<PAIR, BINARY> lessorequalthanMap;
			std::map<PAIR, BINARY> greaterorequalthanMap;
			std::map<PAIR, BINARY> andMap;
			std::map<PAIR, BINARY> orMap;
			std::map<SINGLE, UNARY> plusplusMap;
			std::map<SINGLE, UNARY> lesslessMap;
			std::map<SINGLE, UNARY> negationMap;
			
        };
        inline Memory::MemoryManager& Operator::GetMemoryManager() const
        {
            return manager;
        }
        
        Wrapper Operator::EvaluateAdd(Wrapper lhs, Wrapper rhs, bool& status_output)
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
        Wrapper Operator::EvaluateAdd(Wrapper lhs, Wrapper rhs)
        {
            bool output;
            return EvaluateAdd(lhs, rhs, output);
        }
        			
        Wrapper Operator::EvaluateSubtract(Wrapper lhs, Wrapper rhs, bool& status_output)
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
        Wrapper Operator::EvaluateSubtract(Wrapper lhs, Wrapper rhs)
        {
            bool output;
            return EvaluateSubtract(lhs, rhs, output);
        }
        			
        Wrapper Operator::EvaluateMultiply(Wrapper lhs, Wrapper rhs, bool& status_output)
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
        Wrapper Operator::EvaluateMultiply(Wrapper lhs, Wrapper rhs)
        {
            bool output;
            return EvaluateMultiply(lhs, rhs, output);
        }
        			
        Wrapper Operator::EvaluateDivide(Wrapper lhs, Wrapper rhs, bool& status_output)
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
        Wrapper Operator::EvaluateDivide(Wrapper lhs, Wrapper rhs)
        {
            bool output;
            return EvaluateDivide(lhs, rhs, output);
        }
        			
        Wrapper Operator::EvaluateModulo(Wrapper lhs, Wrapper rhs, bool& status_output)
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
        Wrapper Operator::EvaluateModulo(Wrapper lhs, Wrapper rhs)
        {
            bool output;
            return EvaluateModulo(lhs, rhs, output);
        }
        			
        Wrapper Operator::EvaluateCAdd(Wrapper lhs, Wrapper rhs, bool& status_output)
        {
            PAIR pair(lhs.field->GetType(), rhs.field->GetType());
            auto find_result = caddMap.find(pair);

            if(find_result == caddMap.end())
            {
                status_output = false;
                return manager.AllocateMemory<void>();
            }

            auto f = find_result->second;
            Wrapper out = f(lhs, rhs);
            status_output = true;
            return out;
        }
        Wrapper Operator::EvaluateCAdd(Wrapper lhs, Wrapper rhs)
        {
            bool output;
            return EvaluateCAdd(lhs, rhs, output);
        }
        			
        Wrapper Operator::EvaluateCSubtract(Wrapper lhs, Wrapper rhs, bool& status_output)
        {
            PAIR pair(lhs.field->GetType(), rhs.field->GetType());
            auto find_result = csubtractMap.find(pair);

            if(find_result == csubtractMap.end())
            {
                status_output = false;
                return manager.AllocateMemory<void>();
            }

            auto f = find_result->second;
            Wrapper out = f(lhs, rhs);
            status_output = true;
            return out;
        }
        Wrapper Operator::EvaluateCSubtract(Wrapper lhs, Wrapper rhs)
        {
            bool output;
            return EvaluateCSubtract(lhs, rhs, output);
        }
        			
        Wrapper Operator::EvaluateCMultiply(Wrapper lhs, Wrapper rhs, bool& status_output)
        {
            PAIR pair(lhs.field->GetType(), rhs.field->GetType());
            auto find_result = cmultiplyMap.find(pair);

            if(find_result == cmultiplyMap.end())
            {
                status_output = false;
                return manager.AllocateMemory<void>();
            }

            auto f = find_result->second;
            Wrapper out = f(lhs, rhs);
            status_output = true;
            return out;
        }
        Wrapper Operator::EvaluateCMultiply(Wrapper lhs, Wrapper rhs)
        {
            bool output;
            return EvaluateCMultiply(lhs, rhs, output);
        }
        			
        Wrapper Operator::EvaluateCDivide(Wrapper lhs, Wrapper rhs, bool& status_output)
        {
            PAIR pair(lhs.field->GetType(), rhs.field->GetType());
            auto find_result = cdivideMap.find(pair);

            if(find_result == cdivideMap.end())
            {
                status_output = false;
                return manager.AllocateMemory<void>();
            }

            auto f = find_result->second;
            Wrapper out = f(lhs, rhs);
            status_output = true;
            return out;
        }
        Wrapper Operator::EvaluateCDivide(Wrapper lhs, Wrapper rhs)
        {
            bool output;
            return EvaluateCDivide(lhs, rhs, output);
        }
        			
        Wrapper Operator::EvaluateEquality(Wrapper lhs, Wrapper rhs, bool& status_output)
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
        Wrapper Operator::EvaluateEquality(Wrapper lhs, Wrapper rhs)
        {
            bool output;
            return EvaluateEquality(lhs, rhs, output);
        }
        			
        Wrapper Operator::EvaluateInequality(Wrapper lhs, Wrapper rhs, bool& status_output)
        {
            PAIR pair(lhs.field->GetType(), rhs.field->GetType());
            auto find_result = inequalityMap.find(pair);

            if(find_result == inequalityMap.end())
            {
                status_output = false;
                return manager.AllocateMemory<void>();
            }

            auto f = find_result->second;
            Wrapper out = f(lhs, rhs);
            status_output = true;
            return out;
        }
        Wrapper Operator::EvaluateInequality(Wrapper lhs, Wrapper rhs)
        {
            bool output;
            return EvaluateInequality(lhs, rhs, output);
        }
        			
        Wrapper Operator::EvaluateLessThan(Wrapper lhs, Wrapper rhs, bool& status_output)
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
        Wrapper Operator::EvaluateLessThan(Wrapper lhs, Wrapper rhs)
        {
            bool output;
            return EvaluateLessThan(lhs, rhs, output);
        }
        			
        Wrapper Operator::EvaluateGreaterThan(Wrapper lhs, Wrapper rhs, bool& status_output)
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
        Wrapper Operator::EvaluateGreaterThan(Wrapper lhs, Wrapper rhs)
        {
            bool output;
            return EvaluateGreaterThan(lhs, rhs, output);
        }
        			
        Wrapper Operator::EvaluateLessOrEqualThan(Wrapper lhs, Wrapper rhs, bool& status_output)
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
        Wrapper Operator::EvaluateLessOrEqualThan(Wrapper lhs, Wrapper rhs)
        {
            bool output;
            return EvaluateLessOrEqualThan(lhs, rhs, output);
        }
        			
        Wrapper Operator::EvaluateGreaterOrEqualThan(Wrapper lhs, Wrapper rhs, bool& status_output)
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
        Wrapper Operator::EvaluateGreaterOrEqualThan(Wrapper lhs, Wrapper rhs)
        {
            bool output;
            return EvaluateGreaterOrEqualThan(lhs, rhs, output);
        }
        			
        Wrapper Operator::EvaluateAnd(Wrapper lhs, Wrapper rhs, bool& status_output)
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
        Wrapper Operator::EvaluateAnd(Wrapper lhs, Wrapper rhs)
        {
            bool output;
            return EvaluateAnd(lhs, rhs, output);
        }
        			
        Wrapper Operator::EvaluateOr(Wrapper lhs, Wrapper rhs, bool& status_output)
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
        Wrapper Operator::EvaluateOr(Wrapper lhs, Wrapper rhs)
        {
            bool output;
            return EvaluateOr(lhs, rhs, output);
        }
        			
        Wrapper Operator::EvaluatePlusPlus(Wrapper lhs, bool &status_output)
        {
            SINGLE single(lhs.field->GetType());
            auto find_result = plusplusMap.find(single);

            if(find_result == plusplusMap.end())
            {
                status_output = false;
                return manager.AllocateMemory<void>();
            }

            auto f = find_result->second;
            Wrapper out = f(lhs);
            status_output = true;
            return out;

        }
        Wrapper Operator::EvaluatePlusPlus(Wrapper lhs)
        {
            bool output;
            return EvaluatePlusPlus(lhs, output);
        }
        			
        Wrapper Operator::EvaluateLessLess(Wrapper lhs, bool &status_output)
        {
            SINGLE single(lhs.field->GetType());
            auto find_result = lesslessMap.find(single);

            if(find_result == lesslessMap.end())
            {
                status_output = false;
                return manager.AllocateMemory<void>();
            }

            auto f = find_result->second;
            Wrapper out = f(lhs);
            status_output = true;
            return out;

        }
        Wrapper Operator::EvaluateLessLess(Wrapper lhs)
        {
            bool output;
            return EvaluateLessLess(lhs, output);
        }
        			
        Wrapper Operator::EvaluateNegation(Wrapper lhs, bool &status_output)
        {
            SINGLE single(lhs.field->GetType());
            auto find_result = negationMap.find(single);

            if(find_result == negationMap.end())
            {
                status_output = false;
                return manager.AllocateMemory<void>();
            }

            auto f = find_result->second;
            Wrapper out = f(lhs);
            status_output = true;
            return out;

        }
        Wrapper Operator::EvaluateNegation(Wrapper lhs)
        {
            bool output;
            return EvaluateNegation(lhs, output);
        }
        			
        
        template<typename T, typename F>
        inline void Operator::RegisterAdd()
        {
            auto f = [this](Wrapper lhs, Wrapper rhs)
            {
                T lhst = lhs.field->As<T>();
                F rhsf = rhs.field->As<F>();
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
                T lhst = lhs.field->As<T>();
                F rhsf = rhs.field->As<F>();
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
                T lhst = lhs.field->As<T>();
                F rhsf = rhs.field->As<F>();
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
                T lhst = lhs.field->As<T>();
                F rhsf = rhs.field->As<F>();
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
                T lhst = lhs.field->As<T>();
                F rhsf = rhs.field->As<F>();
                Wrapper output = this->GetMemoryManager().AllocateMemory(lhst % rhsf);
                return output;
            };
            PAIR pair(typeid(T), typeid(F));
            BINARY binary(f);
            moduloMap.insert(std::pair(pair, binary));
        }
        			
        template<typename T, typename F>
        inline void Operator::RegisterCAdd()
        {
            auto f = [this](Wrapper lhs, Wrapper rhs)
            {
                T lhst = lhs.field->As<T>();
                F rhsf = rhs.field->As<F>();
                Wrapper output = this->GetMemoryManager().AllocateMemory(lhst += rhsf);
                return output;
            };
            PAIR pair(typeid(T), typeid(F));
            BINARY binary(f);
            caddMap.insert(std::pair(pair, binary));
        }
        			
        template<typename T, typename F>
        inline void Operator::RegisterCSubtract()
        {
            auto f = [this](Wrapper lhs, Wrapper rhs)
            {
                T lhst = lhs.field->As<T>();
                F rhsf = rhs.field->As<F>();
                Wrapper output = this->GetMemoryManager().AllocateMemory(lhst -= rhsf);
                return output;
            };
            PAIR pair(typeid(T), typeid(F));
            BINARY binary(f);
            csubtractMap.insert(std::pair(pair, binary));
        }
        			
        template<typename T, typename F>
        inline void Operator::RegisterCMultiply()
        {
            auto f = [this](Wrapper lhs, Wrapper rhs)
            {
                T lhst = lhs.field->As<T>();
                F rhsf = rhs.field->As<F>();
                Wrapper output = this->GetMemoryManager().AllocateMemory(lhst *= rhsf);
                return output;
            };
            PAIR pair(typeid(T), typeid(F));
            BINARY binary(f);
            cmultiplyMap.insert(std::pair(pair, binary));
        }
        			
        template<typename T, typename F>
        inline void Operator::RegisterCDivide()
        {
            auto f = [this](Wrapper lhs, Wrapper rhs)
            {
                T lhst = lhs.field->As<T>();
                F rhsf = rhs.field->As<F>();
                Wrapper output = this->GetMemoryManager().AllocateMemory(lhst /= rhsf);
                return output;
            };
            PAIR pair(typeid(T), typeid(F));
            BINARY binary(f);
            cdivideMap.insert(std::pair(pair, binary));
        }
        			
        template<typename T, typename F>
        inline void Operator::RegisterEquality()
        {
            auto f = [this](Wrapper lhs, Wrapper rhs)
            {
                T lhst = lhs.field->As<T>();
                F rhsf = rhs.field->As<F>();
                Wrapper output = this->GetMemoryManager().AllocateMemory(lhst == rhsf);
                return output;
            };
            PAIR pair(typeid(T), typeid(F));
            BINARY binary(f);
            equalityMap.insert(std::pair(pair, binary));
        }
        			
        template<typename T, typename F>
        inline void Operator::RegisterInequality()
        {
            auto f = [this](Wrapper lhs, Wrapper rhs)
            {
                T lhst = lhs.field->As<T>();
                F rhsf = rhs.field->As<F>();
                Wrapper output = this->GetMemoryManager().AllocateMemory(lhst != rhsf);
                return output;
            };
            PAIR pair(typeid(T), typeid(F));
            BINARY binary(f);
            inequalityMap.insert(std::pair(pair, binary));
        }
        			
        template<typename T, typename F>
        inline void Operator::RegisterLessThan()
        {
            auto f = [this](Wrapper lhs, Wrapper rhs)
            {
                T lhst = lhs.field->As<T>();
                F rhsf = rhs.field->As<F>();
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
                T lhst = lhs.field->As<T>();
                F rhsf = rhs.field->As<F>();
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
                T lhst = lhs.field->As<T>();
                F rhsf = rhs.field->As<F>();
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
                T lhst = lhs.field->As<T>();
                F rhsf = rhs.field->As<F>();
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
                T lhst = lhs.field->As<T>();
                F rhsf = rhs.field->As<F>();
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
                T lhst = lhs.field->As<T>();
                F rhsf = rhs.field->As<F>();
                Wrapper output = this->GetMemoryManager().AllocateMemory(lhst || rhsf);
                return output;
            };
            PAIR pair(typeid(T), typeid(F));
            BINARY binary(f);
            orMap.insert(std::pair(pair, binary));
        }
        			
        template<typename T>
        inline void Operator::RegisterPlusPlus()
        {
            auto f = [this](Wrapper lhs)
            {
                T lhst = lhs.field->As<T>();
                Wrapper output = this->GetMemoryManager().AllocateMemory(lhst++);
                return output;
            };
            SINGLE single(typeid(T));
            UNARY unary(f);

            plusplusMap.insert(std::pair(single, unary));
        }
        			
        template<typename T>
        inline void Operator::RegisterLessLess()
        {
            auto f = [this](Wrapper lhs)
            {
                T lhst = lhs.field->As<T>();
                Wrapper output = this->GetMemoryManager().AllocateMemory(lhst--);
                return output;
            };
            SINGLE single(typeid(T));
            UNARY unary(f);

            lesslessMap.insert(std::pair(single, unary));
        }
        			
        template<typename T>
        inline void Operator::RegisterNegation()
        {
            auto f = [this](Wrapper lhs)
            {
                T lhst = lhs.field->As<T>();
                Wrapper output = this->GetMemoryManager().AllocateMemory(!lhst);
                return output;
            };
            SINGLE single(typeid(T));
            UNARY unary(f);

            negationMap.insert(std::pair(single, unary));
        }
        			
    }
}
