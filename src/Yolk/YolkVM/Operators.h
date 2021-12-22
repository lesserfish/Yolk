#pragma once

#include "../Wrapper/Wrapper.h"
#include "../Memory/MemoryManager/MemoryManager.h"
#include <typeindex>
#include <functional>

namespace Yolk
{
    namespace VM
    {
        class Operator
        {
            using UNARY = std::tuple<std::type_index, std::type_index, std::function<Wrapper(Wrapper)>>;
            using BINARY = std::tuple<std::type_index, std::type_index, std::function<Wrapper(Wrapper, Wrapper)>>;
            
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
            std::vector<BINARY> addMap;
			std::vector<BINARY> subtractMap;
			std::vector<BINARY> multiplyMap;
			std::vector<BINARY> divideMap;
			std::vector<BINARY> moduloMap;
			std::vector<BINARY> caddMap;
			std::vector<BINARY> csubtractMap;
			std::vector<BINARY> cmultiplyMap;
			std::vector<BINARY> cdivideMap;
			std::vector<BINARY> equalityMap;
			std::vector<BINARY> inequalityMap;
			std::vector<BINARY> lessthanMap;
			std::vector<BINARY> greaterthanMap;
			std::vector<BINARY> lessorequalthanMap;
			std::vector<BINARY> greaterorequalthanMap;
			std::vector<BINARY> andMap;
			std::vector<BINARY> orMap;
			std::vector<UNARY> plusplusMap;
			std::vector<UNARY> lesslessMap;
			std::vector<UNARY> negationMap;
			
        };
        inline Memory::MemoryManager& Operator::GetMemoryManager() const
        {
            return manager;
        }
        
        Wrapper Operator::EvaluateAdd(Wrapper lhs, Wrapper rhs, bool& status_output)
        {
            for(auto& entry : addMap)
            {
                if(std::get<0>(entry) == lhs.field->GetType() && std::get<1>(entry) == rhs.field->GetType())
                {
                    auto f = std::get<2>(entry);
                    Wrapper out = f(lhs, rhs);
                    status_output = true;
                    return out;
                }
            }
            status_output = false;
            return manager.AllocateMemory<void>();
        }
        Wrapper Operator::EvaluateAdd(Wrapper lhs, Wrapper rhs)
        {
            bool output;
            return EvaluateAdd(lhs, rhs, output);
        }
        			
        Wrapper Operator::EvaluateSubtract(Wrapper lhs, Wrapper rhs, bool& status_output)
        {
            for(auto& entry : subtractMap)
            {
                if(std::get<0>(entry) == lhs.field->GetType() && std::get<1>(entry) == rhs.field->GetType())
                {
                    auto f = std::get<2>(entry);
                    Wrapper out = f(lhs, rhs);
                    status_output = true;
                    return out;
                }
            }
            status_output = false;
            return manager.AllocateMemory<void>();
        }
        Wrapper Operator::EvaluateSubtract(Wrapper lhs, Wrapper rhs)
        {
            bool output;
            return EvaluateSubtract(lhs, rhs, output);
        }
        			
        Wrapper Operator::EvaluateMultiply(Wrapper lhs, Wrapper rhs, bool& status_output)
        {
            for(auto& entry : multiplyMap)
            {
                if(std::get<0>(entry) == lhs.field->GetType() && std::get<1>(entry) == rhs.field->GetType())
                {
                    auto f = std::get<2>(entry);
                    Wrapper out = f(lhs, rhs);
                    status_output = true;
                    return out;
                }
            }
            status_output = false;
            return manager.AllocateMemory<void>();
        }
        Wrapper Operator::EvaluateMultiply(Wrapper lhs, Wrapper rhs)
        {
            bool output;
            return EvaluateMultiply(lhs, rhs, output);
        }
        			
        Wrapper Operator::EvaluateDivide(Wrapper lhs, Wrapper rhs, bool& status_output)
        {
            for(auto& entry : divideMap)
            {
                if(std::get<0>(entry) == lhs.field->GetType() && std::get<1>(entry) == rhs.field->GetType())
                {
                    auto f = std::get<2>(entry);
                    Wrapper out = f(lhs, rhs);
                    status_output = true;
                    return out;
                }
            }
            status_output = false;
            return manager.AllocateMemory<void>();
        }
        Wrapper Operator::EvaluateDivide(Wrapper lhs, Wrapper rhs)
        {
            bool output;
            return EvaluateDivide(lhs, rhs, output);
        }
        			
        Wrapper Operator::EvaluateModulo(Wrapper lhs, Wrapper rhs, bool& status_output)
        {
            for(auto& entry : moduloMap)
            {
                if(std::get<0>(entry) == lhs.field->GetType() && std::get<1>(entry) == rhs.field->GetType())
                {
                    auto f = std::get<2>(entry);
                    Wrapper out = f(lhs, rhs);
                    status_output = true;
                    return out;
                }
            }
            status_output = false;
            return manager.AllocateMemory<void>();
        }
        Wrapper Operator::EvaluateModulo(Wrapper lhs, Wrapper rhs)
        {
            bool output;
            return EvaluateModulo(lhs, rhs, output);
        }
        			
        Wrapper Operator::EvaluateCAdd(Wrapper lhs, Wrapper rhs, bool& status_output)
        {
            for(auto& entry : caddMap)
            {
                if(std::get<0>(entry) == lhs.field->GetType() && std::get<1>(entry) == rhs.field->GetType())
                {
                    auto f = std::get<2>(entry);
                    Wrapper out = f(lhs, rhs);
                    status_output = true;
                    return out;
                }
            }
            status_output = false;
            return manager.AllocateMemory<void>();
        }
        Wrapper Operator::EvaluateCAdd(Wrapper lhs, Wrapper rhs)
        {
            bool output;
            return EvaluateCAdd(lhs, rhs, output);
        }
        			
        Wrapper Operator::EvaluateCSubtract(Wrapper lhs, Wrapper rhs, bool& status_output)
        {
            for(auto& entry : csubtractMap)
            {
                if(std::get<0>(entry) == lhs.field->GetType() && std::get<1>(entry) == rhs.field->GetType())
                {
                    auto f = std::get<2>(entry);
                    Wrapper out = f(lhs, rhs);
                    status_output = true;
                    return out;
                }
            }
            status_output = false;
            return manager.AllocateMemory<void>();
        }
        Wrapper Operator::EvaluateCSubtract(Wrapper lhs, Wrapper rhs)
        {
            bool output;
            return EvaluateCSubtract(lhs, rhs, output);
        }
        			
        Wrapper Operator::EvaluateCMultiply(Wrapper lhs, Wrapper rhs, bool& status_output)
        {
            for(auto& entry : cmultiplyMap)
            {
                if(std::get<0>(entry) == lhs.field->GetType() && std::get<1>(entry) == rhs.field->GetType())
                {
                    auto f = std::get<2>(entry);
                    Wrapper out = f(lhs, rhs);
                    status_output = true;
                    return out;
                }
            }
            status_output = false;
            return manager.AllocateMemory<void>();
        }
        Wrapper Operator::EvaluateCMultiply(Wrapper lhs, Wrapper rhs)
        {
            bool output;
            return EvaluateCMultiply(lhs, rhs, output);
        }
        			
        Wrapper Operator::EvaluateCDivide(Wrapper lhs, Wrapper rhs, bool& status_output)
        {
            for(auto& entry : cdivideMap)
            {
                if(std::get<0>(entry) == lhs.field->GetType() && std::get<1>(entry) == rhs.field->GetType())
                {
                    auto f = std::get<2>(entry);
                    Wrapper out = f(lhs, rhs);
                    status_output = true;
                    return out;
                }
            }
            status_output = false;
            return manager.AllocateMemory<void>();
        }
        Wrapper Operator::EvaluateCDivide(Wrapper lhs, Wrapper rhs)
        {
            bool output;
            return EvaluateCDivide(lhs, rhs, output);
        }
        			
        Wrapper Operator::EvaluateEquality(Wrapper lhs, Wrapper rhs, bool& status_output)
        {
            for(auto& entry : equalityMap)
            {
                if(std::get<0>(entry) == lhs.field->GetType() && std::get<1>(entry) == rhs.field->GetType())
                {
                    auto f = std::get<2>(entry);
                    Wrapper out = f(lhs, rhs);
                    status_output = true;
                    return out;
                }
            }
            status_output = false;
            return manager.AllocateMemory<void>();
        }
        Wrapper Operator::EvaluateEquality(Wrapper lhs, Wrapper rhs)
        {
            bool output;
            return EvaluateEquality(lhs, rhs, output);
        }
        			
        Wrapper Operator::EvaluateInequality(Wrapper lhs, Wrapper rhs, bool& status_output)
        {
            for(auto& entry : inequalityMap)
            {
                if(std::get<0>(entry) == lhs.field->GetType() && std::get<1>(entry) == rhs.field->GetType())
                {
                    auto f = std::get<2>(entry);
                    Wrapper out = f(lhs, rhs);
                    status_output = true;
                    return out;
                }
            }
            status_output = false;
            return manager.AllocateMemory<void>();
        }
        Wrapper Operator::EvaluateInequality(Wrapper lhs, Wrapper rhs)
        {
            bool output;
            return EvaluateInequality(lhs, rhs, output);
        }
        			
        Wrapper Operator::EvaluateLessThan(Wrapper lhs, Wrapper rhs, bool& status_output)
        {
            for(auto& entry : lessthanMap)
            {
                if(std::get<0>(entry) == lhs.field->GetType() && std::get<1>(entry) == rhs.field->GetType())
                {
                    auto f = std::get<2>(entry);
                    Wrapper out = f(lhs, rhs);
                    status_output = true;
                    return out;
                }
            }
            status_output = false;
            return manager.AllocateMemory<void>();
        }
        Wrapper Operator::EvaluateLessThan(Wrapper lhs, Wrapper rhs)
        {
            bool output;
            return EvaluateLessThan(lhs, rhs, output);
        }
        			
        Wrapper Operator::EvaluateGreaterThan(Wrapper lhs, Wrapper rhs, bool& status_output)
        {
            for(auto& entry : greaterthanMap)
            {
                if(std::get<0>(entry) == lhs.field->GetType() && std::get<1>(entry) == rhs.field->GetType())
                {
                    auto f = std::get<2>(entry);
                    Wrapper out = f(lhs, rhs);
                    status_output = true;
                    return out;
                }
            }
            status_output = false;
            return manager.AllocateMemory<void>();
        }
        Wrapper Operator::EvaluateGreaterThan(Wrapper lhs, Wrapper rhs)
        {
            bool output;
            return EvaluateGreaterThan(lhs, rhs, output);
        }
        			
        Wrapper Operator::EvaluateLessOrEqualThan(Wrapper lhs, Wrapper rhs, bool& status_output)
        {
            for(auto& entry : lessorequalthanMap)
            {
                if(std::get<0>(entry) == lhs.field->GetType() && std::get<1>(entry) == rhs.field->GetType())
                {
                    auto f = std::get<2>(entry);
                    Wrapper out = f(lhs, rhs);
                    status_output = true;
                    return out;
                }
            }
            status_output = false;
            return manager.AllocateMemory<void>();
        }
        Wrapper Operator::EvaluateLessOrEqualThan(Wrapper lhs, Wrapper rhs)
        {
            bool output;
            return EvaluateLessOrEqualThan(lhs, rhs, output);
        }
        			
        Wrapper Operator::EvaluateGreaterOrEqualThan(Wrapper lhs, Wrapper rhs, bool& status_output)
        {
            for(auto& entry : greaterorequalthanMap)
            {
                if(std::get<0>(entry) == lhs.field->GetType() && std::get<1>(entry) == rhs.field->GetType())
                {
                    auto f = std::get<2>(entry);
                    Wrapper out = f(lhs, rhs);
                    status_output = true;
                    return out;
                }
            }
            status_output = false;
            return manager.AllocateMemory<void>();
        }
        Wrapper Operator::EvaluateGreaterOrEqualThan(Wrapper lhs, Wrapper rhs)
        {
            bool output;
            return EvaluateGreaterOrEqualThan(lhs, rhs, output);
        }
        			
        Wrapper Operator::EvaluateAnd(Wrapper lhs, Wrapper rhs, bool& status_output)
        {
            for(auto& entry : andMap)
            {
                if(std::get<0>(entry) == lhs.field->GetType() && std::get<1>(entry) == rhs.field->GetType())
                {
                    auto f = std::get<2>(entry);
                    Wrapper out = f(lhs, rhs);
                    status_output = true;
                    return out;
                }
            }
            status_output = false;
            return manager.AllocateMemory<void>();
        }
        Wrapper Operator::EvaluateAnd(Wrapper lhs, Wrapper rhs)
        {
            bool output;
            return EvaluateAnd(lhs, rhs, output);
        }
        			
        Wrapper Operator::EvaluateOr(Wrapper lhs, Wrapper rhs, bool& status_output)
        {
            for(auto& entry : orMap)
            {
                if(std::get<0>(entry) == lhs.field->GetType() && std::get<1>(entry) == rhs.field->GetType())
                {
                    auto f = std::get<2>(entry);
                    Wrapper out = f(lhs, rhs);
                    status_output = true;
                    return out;
                }
            }
            status_output = false;
            return manager.AllocateMemory<void>();
        }
        Wrapper Operator::EvaluateOr(Wrapper lhs, Wrapper rhs)
        {
            bool output;
            return EvaluateOr(lhs, rhs, output);
        }
        			
        Wrapper Operator::EvaluatePlusPlus(Wrapper lhs, bool &status_output)
        {
            for(auto& entry : plusplusMap)
            {
                if(std::get<0>(entry) == lhs.field->GetType())
                {
                    auto f = std::get<2>(entry);
                    Wrapper out = f(lhs);
                    status_output = true;
                    return out;
                }
            }
            status_output = false;
            return manager.AllocateMemory<void>();
        }
        Wrapper Operator::EvaluatePlusPlus(Wrapper lhs)
        {
            bool output;
            return EvaluatePlusPlus(lhs, output);
        }
        			
        Wrapper Operator::EvaluateLessLess(Wrapper lhs, bool &status_output)
        {
            for(auto& entry : lesslessMap)
            {
                if(std::get<0>(entry) == lhs.field->GetType())
                {
                    auto f = std::get<2>(entry);
                    Wrapper out = f(lhs);
                    status_output = true;
                    return out;
                }
            }
            status_output = false;
            return manager.AllocateMemory<void>();
        }
        Wrapper Operator::EvaluateLessLess(Wrapper lhs)
        {
            bool output;
            return EvaluateLessLess(lhs, output);
        }
        			
        Wrapper Operator::EvaluateNegation(Wrapper lhs, bool &status_output)
        {
            for(auto& entry : negationMap)
            {
                if(std::get<0>(entry) == lhs.field->GetType())
                {
                    auto f = std::get<2>(entry);
                    Wrapper out = f(lhs);
                    status_output = true;
                    return out;
                }
            }
            status_output = false;
            return manager.AllocateMemory<void>();
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
            BINARY binary(typeid(T), typeid(F), f);
            addMap.push_back(binary);
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
            BINARY binary(typeid(T), typeid(F), f);
            subtractMap.push_back(binary);
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
            BINARY binary(typeid(T), typeid(F), f);
            multiplyMap.push_back(binary);
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
            BINARY binary(typeid(T), typeid(F), f);
            divideMap.push_back(binary);
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
            BINARY binary(typeid(T), typeid(F), f);
            moduloMap.push_back(binary);
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
            BINARY binary(typeid(T), typeid(F), f);
            caddMap.push_back(binary);
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
            BINARY binary(typeid(T), typeid(F), f);
            csubtractMap.push_back(binary);
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
            BINARY binary(typeid(T), typeid(F), f);
            cmultiplyMap.push_back(binary);
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
            BINARY binary(typeid(T), typeid(F), f);
            cdivideMap.push_back(binary);
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
            BINARY binary(typeid(T), typeid(F), f);
            equalityMap.push_back(binary);
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
            BINARY binary(typeid(T), typeid(F), f);
            inequalityMap.push_back(binary);
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
            BINARY binary(typeid(T), typeid(F), f);
            lessthanMap.push_back(binary);
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
            BINARY binary(typeid(T), typeid(F), f);
            greaterthanMap.push_back(binary);
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
            BINARY binary(typeid(T), typeid(F), f);
            lessorequalthanMap.push_back(binary);
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
            BINARY binary(typeid(T), typeid(F), f);
            greaterorequalthanMap.push_back(binary);
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
            BINARY binary(typeid(T), typeid(F), f);
            andMap.push_back(binary);
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
            BINARY binary(typeid(T), typeid(F), f);
            orMap.push_back(binary);
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
            UNARY unary(typeid(T), f);
            plusplusMap.push_back(unary);
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
            UNARY unary(typeid(T), f);
            lesslessMap.push_back(unary);
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
            UNARY unary(typeid(T), f);
            negationMap.push_back(unary);
        }
        			
    }
}
