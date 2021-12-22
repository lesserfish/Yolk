    #pragma once
    #include "Operators.h"
    namespace Yolk
    {
        namespace VM
        {

            static void GenerateElementaryOperations(Yolk::VM::Operator& op)
            {
                	op.RegisterAdd<int,unsigned int>();
	op.RegisterAdd<unsigned int,int>();
	op.RegisterAdd<int,long int>();
	op.RegisterAdd<long int,int>();
	op.RegisterAdd<int,unsigned long int>();
	op.RegisterAdd<unsigned long int,int>();
	op.RegisterAdd<int,float>();
	op.RegisterAdd<float,int>();
	op.RegisterAdd<int,double>();
	op.RegisterAdd<double,int>();
	op.RegisterAdd<unsigned int,long int>();
	op.RegisterAdd<long int,unsigned int>();
	op.RegisterAdd<unsigned int,unsigned long int>();
	op.RegisterAdd<unsigned long int,unsigned int>();
	op.RegisterAdd<unsigned int,float>();
	op.RegisterAdd<float,unsigned int>();
	op.RegisterAdd<unsigned int,double>();
	op.RegisterAdd<double,unsigned int>();
	op.RegisterAdd<long int,unsigned long int>();
	op.RegisterAdd<unsigned long int,long int>();
	op.RegisterAdd<long int,float>();
	op.RegisterAdd<float,long int>();
	op.RegisterAdd<long int,double>();
	op.RegisterAdd<double,long int>();
	op.RegisterAdd<unsigned long int,float>();
	op.RegisterAdd<float,unsigned long int>();
	op.RegisterAdd<unsigned long int,double>();
	op.RegisterAdd<double,unsigned long int>();
	op.RegisterAdd<float,double>();
	op.RegisterAdd<double,float>();

	op.RegisterSubtract<int,unsigned int>();
	op.RegisterSubtract<unsigned int,int>();
	op.RegisterSubtract<int,long int>();
	op.RegisterSubtract<long int,int>();
	op.RegisterSubtract<int,unsigned long int>();
	op.RegisterSubtract<unsigned long int,int>();
	op.RegisterSubtract<int,float>();
	op.RegisterSubtract<float,int>();
	op.RegisterSubtract<int,double>();
	op.RegisterSubtract<double,int>();
	op.RegisterSubtract<unsigned int,long int>();
	op.RegisterSubtract<long int,unsigned int>();
	op.RegisterSubtract<unsigned int,unsigned long int>();
	op.RegisterSubtract<unsigned long int,unsigned int>();
	op.RegisterSubtract<unsigned int,float>();
	op.RegisterSubtract<float,unsigned int>();
	op.RegisterSubtract<unsigned int,double>();
	op.RegisterSubtract<double,unsigned int>();
	op.RegisterSubtract<long int,unsigned long int>();
	op.RegisterSubtract<unsigned long int,long int>();
	op.RegisterSubtract<long int,float>();
	op.RegisterSubtract<float,long int>();
	op.RegisterSubtract<long int,double>();
	op.RegisterSubtract<double,long int>();
	op.RegisterSubtract<unsigned long int,float>();
	op.RegisterSubtract<float,unsigned long int>();
	op.RegisterSubtract<unsigned long int,double>();
	op.RegisterSubtract<double,unsigned long int>();
	op.RegisterSubtract<float,double>();
	op.RegisterSubtract<double,float>();

	op.RegisterMultiply<int,unsigned int>();
	op.RegisterMultiply<unsigned int,int>();
	op.RegisterMultiply<int,long int>();
	op.RegisterMultiply<long int,int>();
	op.RegisterMultiply<int,unsigned long int>();
	op.RegisterMultiply<unsigned long int,int>();
	op.RegisterMultiply<int,float>();
	op.RegisterMultiply<float,int>();
	op.RegisterMultiply<int,double>();
	op.RegisterMultiply<double,int>();
	op.RegisterMultiply<unsigned int,long int>();
	op.RegisterMultiply<long int,unsigned int>();
	op.RegisterMultiply<unsigned int,unsigned long int>();
	op.RegisterMultiply<unsigned long int,unsigned int>();
	op.RegisterMultiply<unsigned int,float>();
	op.RegisterMultiply<float,unsigned int>();
	op.RegisterMultiply<unsigned int,double>();
	op.RegisterMultiply<double,unsigned int>();
	op.RegisterMultiply<long int,unsigned long int>();
	op.RegisterMultiply<unsigned long int,long int>();
	op.RegisterMultiply<long int,float>();
	op.RegisterMultiply<float,long int>();
	op.RegisterMultiply<long int,double>();
	op.RegisterMultiply<double,long int>();
	op.RegisterMultiply<unsigned long int,float>();
	op.RegisterMultiply<float,unsigned long int>();
	op.RegisterMultiply<unsigned long int,double>();
	op.RegisterMultiply<double,unsigned long int>();
	op.RegisterMultiply<float,double>();
	op.RegisterMultiply<double,float>();

	op.RegisterDivide<int,unsigned int>();
	op.RegisterDivide<unsigned int,int>();
	op.RegisterDivide<int,long int>();
	op.RegisterDivide<long int,int>();
	op.RegisterDivide<int,unsigned long int>();
	op.RegisterDivide<unsigned long int,int>();
	op.RegisterDivide<int,float>();
	op.RegisterDivide<float,int>();
	op.RegisterDivide<int,double>();
	op.RegisterDivide<double,int>();
	op.RegisterDivide<unsigned int,long int>();
	op.RegisterDivide<long int,unsigned int>();
	op.RegisterDivide<unsigned int,unsigned long int>();
	op.RegisterDivide<unsigned long int,unsigned int>();
	op.RegisterDivide<unsigned int,float>();
	op.RegisterDivide<float,unsigned int>();
	op.RegisterDivide<unsigned int,double>();
	op.RegisterDivide<double,unsigned int>();
	op.RegisterDivide<long int,unsigned long int>();
	op.RegisterDivide<unsigned long int,long int>();
	op.RegisterDivide<long int,float>();
	op.RegisterDivide<float,long int>();
	op.RegisterDivide<long int,double>();
	op.RegisterDivide<double,long int>();
	op.RegisterDivide<unsigned long int,float>();
	op.RegisterDivide<float,unsigned long int>();
	op.RegisterDivide<unsigned long int,double>();
	op.RegisterDivide<double,unsigned long int>();
	op.RegisterDivide<float,double>();
	op.RegisterDivide<double,float>();

	op.RegisterEquality<int,long int>();
	op.RegisterEquality<long int,int>();
	op.RegisterEquality<int,float>();
	op.RegisterEquality<float,int>();
	op.RegisterEquality<int,double>();
	op.RegisterEquality<double,int>();
	op.RegisterEquality<long int,float>();
	op.RegisterEquality<float,long int>();
	op.RegisterEquality<long int,double>();
	op.RegisterEquality<double,long int>();
	op.RegisterEquality<float,double>();
	op.RegisterEquality<double,float>();
	op.RegisterEquality<unsigned int,unsigned long int>();
	op.RegisterEquality<unsigned long int,unsigned int>();
	op.RegisterLessThan<int,long int>();
	op.RegisterLessThan<long int,int>();
	op.RegisterLessThan<int,float>();
	op.RegisterLessThan<float,int>();
	op.RegisterLessThan<int,double>();
	op.RegisterLessThan<double,int>();
	op.RegisterLessThan<long int,float>();
	op.RegisterLessThan<float,long int>();
	op.RegisterLessThan<long int,double>();
	op.RegisterLessThan<double,long int>();
	op.RegisterLessThan<float,double>();
	op.RegisterLessThan<double,float>();
	op.RegisterLessThan<unsigned int,unsigned long int>();
	op.RegisterLessThan<unsigned long int,unsigned int>();
	op.RegisterGreaterThan<int,long int>();
	op.RegisterGreaterThan<long int,int>();
	op.RegisterGreaterThan<int,float>();
	op.RegisterGreaterThan<float,int>();
	op.RegisterGreaterThan<int,double>();
	op.RegisterGreaterThan<double,int>();
	op.RegisterGreaterThan<long int,float>();
	op.RegisterGreaterThan<float,long int>();
	op.RegisterGreaterThan<long int,double>();
	op.RegisterGreaterThan<double,long int>();
	op.RegisterGreaterThan<float,double>();
	op.RegisterGreaterThan<double,float>();
	op.RegisterGreaterThan<unsigned int,unsigned long int>();
	op.RegisterGreaterThan<unsigned long int,unsigned int>();

            }
        }
    }
