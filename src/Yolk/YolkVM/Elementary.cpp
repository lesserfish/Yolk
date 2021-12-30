    #include "Elementary.h"
    namespace Yolk
    {
        namespace VM
        {
                void Elementary::GenerateElementaryOperations(Yolk::VM::Operator& op)
                {
                    op.RegisterAdd<int,int>();
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
					op.RegisterAdd<int,char>();
					op.RegisterAdd<char,int>();
					op.RegisterAdd<int,unsigned char>();
					op.RegisterAdd<unsigned char,int>();
					op.RegisterAdd<int,bool>();
					op.RegisterAdd<bool,int>();
					op.RegisterAdd<unsigned int,unsigned int>();
					op.RegisterAdd<unsigned int,long int>();
					op.RegisterAdd<long int,unsigned int>();
					op.RegisterAdd<unsigned int,unsigned long int>();
					op.RegisterAdd<unsigned long int,unsigned int>();
					op.RegisterAdd<unsigned int,float>();
					op.RegisterAdd<float,unsigned int>();
					op.RegisterAdd<unsigned int,double>();
					op.RegisterAdd<double,unsigned int>();
					op.RegisterAdd<unsigned int,char>();
					op.RegisterAdd<char,unsigned int>();
					op.RegisterAdd<unsigned int,unsigned char>();
					op.RegisterAdd<unsigned char,unsigned int>();
					op.RegisterAdd<unsigned int,bool>();
					op.RegisterAdd<bool,unsigned int>();
					op.RegisterAdd<long int,long int>();
					op.RegisterAdd<long int,unsigned long int>();
					op.RegisterAdd<unsigned long int,long int>();
					op.RegisterAdd<long int,float>();
					op.RegisterAdd<float,long int>();
					op.RegisterAdd<long int,double>();
					op.RegisterAdd<double,long int>();
					op.RegisterAdd<long int,char>();
					op.RegisterAdd<char,long int>();
					op.RegisterAdd<long int,unsigned char>();
					op.RegisterAdd<unsigned char,long int>();
					op.RegisterAdd<long int,bool>();
					op.RegisterAdd<bool,long int>();
					op.RegisterAdd<unsigned long int,unsigned long int>();
					op.RegisterAdd<unsigned long int,float>();
					op.RegisterAdd<float,unsigned long int>();
					op.RegisterAdd<unsigned long int,double>();
					op.RegisterAdd<double,unsigned long int>();
					op.RegisterAdd<unsigned long int,char>();
					op.RegisterAdd<char,unsigned long int>();
					op.RegisterAdd<unsigned long int,unsigned char>();
					op.RegisterAdd<unsigned char,unsigned long int>();
					op.RegisterAdd<unsigned long int,bool>();
					op.RegisterAdd<bool,unsigned long int>();
					op.RegisterAdd<float,float>();
					op.RegisterAdd<float,double>();
					op.RegisterAdd<double,float>();
					op.RegisterAdd<float,char>();
					op.RegisterAdd<char,float>();
					op.RegisterAdd<float,unsigned char>();
					op.RegisterAdd<unsigned char,float>();
					op.RegisterAdd<float,bool>();
					op.RegisterAdd<bool,float>();
					op.RegisterAdd<double,double>();
					op.RegisterAdd<double,char>();
					op.RegisterAdd<char,double>();
					op.RegisterAdd<double,unsigned char>();
					op.RegisterAdd<unsigned char,double>();
					op.RegisterAdd<double,bool>();
					op.RegisterAdd<bool,double>();
					op.RegisterAdd<char,char>();
					op.RegisterAdd<char,unsigned char>();
					op.RegisterAdd<unsigned char,char>();
					op.RegisterAdd<char,bool>();
					op.RegisterAdd<bool,char>();
					op.RegisterAdd<unsigned char,unsigned char>();
					op.RegisterAdd<unsigned char,bool>();
					op.RegisterAdd<bool,unsigned char>();
					op.RegisterAdd<bool,bool>();

					op.RegisterSubtract<int,int>();
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
					op.RegisterSubtract<int,char>();
					op.RegisterSubtract<char,int>();
					op.RegisterSubtract<int,unsigned char>();
					op.RegisterSubtract<unsigned char,int>();
					op.RegisterSubtract<int,bool>();
					op.RegisterSubtract<bool,int>();
					op.RegisterSubtract<unsigned int,unsigned int>();
					op.RegisterSubtract<unsigned int,long int>();
					op.RegisterSubtract<long int,unsigned int>();
					op.RegisterSubtract<unsigned int,unsigned long int>();
					op.RegisterSubtract<unsigned long int,unsigned int>();
					op.RegisterSubtract<unsigned int,float>();
					op.RegisterSubtract<float,unsigned int>();
					op.RegisterSubtract<unsigned int,double>();
					op.RegisterSubtract<double,unsigned int>();
					op.RegisterSubtract<unsigned int,char>();
					op.RegisterSubtract<char,unsigned int>();
					op.RegisterSubtract<unsigned int,unsigned char>();
					op.RegisterSubtract<unsigned char,unsigned int>();
					op.RegisterSubtract<unsigned int,bool>();
					op.RegisterSubtract<bool,unsigned int>();
					op.RegisterSubtract<long int,long int>();
					op.RegisterSubtract<long int,unsigned long int>();
					op.RegisterSubtract<unsigned long int,long int>();
					op.RegisterSubtract<long int,float>();
					op.RegisterSubtract<float,long int>();
					op.RegisterSubtract<long int,double>();
					op.RegisterSubtract<double,long int>();
					op.RegisterSubtract<long int,char>();
					op.RegisterSubtract<char,long int>();
					op.RegisterSubtract<long int,unsigned char>();
					op.RegisterSubtract<unsigned char,long int>();
					op.RegisterSubtract<long int,bool>();
					op.RegisterSubtract<bool,long int>();
					op.RegisterSubtract<unsigned long int,unsigned long int>();
					op.RegisterSubtract<unsigned long int,float>();
					op.RegisterSubtract<float,unsigned long int>();
					op.RegisterSubtract<unsigned long int,double>();
					op.RegisterSubtract<double,unsigned long int>();
					op.RegisterSubtract<unsigned long int,char>();
					op.RegisterSubtract<char,unsigned long int>();
					op.RegisterSubtract<unsigned long int,unsigned char>();
					op.RegisterSubtract<unsigned char,unsigned long int>();
					op.RegisterSubtract<unsigned long int,bool>();
					op.RegisterSubtract<bool,unsigned long int>();
					op.RegisterSubtract<float,float>();
					op.RegisterSubtract<float,double>();
					op.RegisterSubtract<double,float>();
					op.RegisterSubtract<float,char>();
					op.RegisterSubtract<char,float>();
					op.RegisterSubtract<float,unsigned char>();
					op.RegisterSubtract<unsigned char,float>();
					op.RegisterSubtract<float,bool>();
					op.RegisterSubtract<bool,float>();
					op.RegisterSubtract<double,double>();
					op.RegisterSubtract<double,char>();
					op.RegisterSubtract<char,double>();
					op.RegisterSubtract<double,unsigned char>();
					op.RegisterSubtract<unsigned char,double>();
					op.RegisterSubtract<double,bool>();
					op.RegisterSubtract<bool,double>();
					op.RegisterSubtract<char,char>();
					op.RegisterSubtract<char,unsigned char>();
					op.RegisterSubtract<unsigned char,char>();
					op.RegisterSubtract<char,bool>();
					op.RegisterSubtract<bool,char>();
					op.RegisterSubtract<unsigned char,unsigned char>();
					op.RegisterSubtract<unsigned char,bool>();
					op.RegisterSubtract<bool,unsigned char>();
					op.RegisterSubtract<bool,bool>();

					op.RegisterMultiply<int,int>();
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
					op.RegisterMultiply<int,char>();
					op.RegisterMultiply<char,int>();
					op.RegisterMultiply<int,unsigned char>();
					op.RegisterMultiply<unsigned char,int>();
					op.RegisterMultiply<int,bool>();
					op.RegisterMultiply<bool,int>();
					op.RegisterMultiply<unsigned int,unsigned int>();
					op.RegisterMultiply<unsigned int,long int>();
					op.RegisterMultiply<long int,unsigned int>();
					op.RegisterMultiply<unsigned int,unsigned long int>();
					op.RegisterMultiply<unsigned long int,unsigned int>();
					op.RegisterMultiply<unsigned int,float>();
					op.RegisterMultiply<float,unsigned int>();
					op.RegisterMultiply<unsigned int,double>();
					op.RegisterMultiply<double,unsigned int>();
					op.RegisterMultiply<unsigned int,char>();
					op.RegisterMultiply<char,unsigned int>();
					op.RegisterMultiply<unsigned int,unsigned char>();
					op.RegisterMultiply<unsigned char,unsigned int>();
					op.RegisterMultiply<unsigned int,bool>();
					op.RegisterMultiply<bool,unsigned int>();
					op.RegisterMultiply<long int,long int>();
					op.RegisterMultiply<long int,unsigned long int>();
					op.RegisterMultiply<unsigned long int,long int>();
					op.RegisterMultiply<long int,float>();
					op.RegisterMultiply<float,long int>();
					op.RegisterMultiply<long int,double>();
					op.RegisterMultiply<double,long int>();
					op.RegisterMultiply<long int,char>();
					op.RegisterMultiply<char,long int>();
					op.RegisterMultiply<long int,unsigned char>();
					op.RegisterMultiply<unsigned char,long int>();
					op.RegisterMultiply<long int,bool>();
					op.RegisterMultiply<bool,long int>();
					op.RegisterMultiply<unsigned long int,unsigned long int>();
					op.RegisterMultiply<unsigned long int,float>();
					op.RegisterMultiply<float,unsigned long int>();
					op.RegisterMultiply<unsigned long int,double>();
					op.RegisterMultiply<double,unsigned long int>();
					op.RegisterMultiply<unsigned long int,char>();
					op.RegisterMultiply<char,unsigned long int>();
					op.RegisterMultiply<unsigned long int,unsigned char>();
					op.RegisterMultiply<unsigned char,unsigned long int>();
					op.RegisterMultiply<unsigned long int,bool>();
					op.RegisterMultiply<bool,unsigned long int>();
					op.RegisterMultiply<float,float>();
					op.RegisterMultiply<float,double>();
					op.RegisterMultiply<double,float>();
					op.RegisterMultiply<float,char>();
					op.RegisterMultiply<char,float>();
					op.RegisterMultiply<float,unsigned char>();
					op.RegisterMultiply<unsigned char,float>();
					op.RegisterMultiply<float,bool>();
					op.RegisterMultiply<bool,float>();
					op.RegisterMultiply<double,double>();
					op.RegisterMultiply<double,char>();
					op.RegisterMultiply<char,double>();
					op.RegisterMultiply<double,unsigned char>();
					op.RegisterMultiply<unsigned char,double>();
					op.RegisterMultiply<double,bool>();
					op.RegisterMultiply<bool,double>();
					op.RegisterMultiply<char,char>();
					op.RegisterMultiply<char,unsigned char>();
					op.RegisterMultiply<unsigned char,char>();
					op.RegisterMultiply<char,bool>();
					op.RegisterMultiply<bool,char>();
					op.RegisterMultiply<unsigned char,unsigned char>();
					op.RegisterMultiply<unsigned char,bool>();
					op.RegisterMultiply<bool,unsigned char>();
					op.RegisterMultiply<bool,bool>();

					op.RegisterDivide<int,int>();
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
					op.RegisterDivide<int,char>();
					op.RegisterDivide<char,int>();
					op.RegisterDivide<int,unsigned char>();
					op.RegisterDivide<unsigned char,int>();
					op.RegisterDivide<int,bool>();
					op.RegisterDivide<bool,int>();
					op.RegisterDivide<unsigned int,unsigned int>();
					op.RegisterDivide<unsigned int,long int>();
					op.RegisterDivide<long int,unsigned int>();
					op.RegisterDivide<unsigned int,unsigned long int>();
					op.RegisterDivide<unsigned long int,unsigned int>();
					op.RegisterDivide<unsigned int,float>();
					op.RegisterDivide<float,unsigned int>();
					op.RegisterDivide<unsigned int,double>();
					op.RegisterDivide<double,unsigned int>();
					op.RegisterDivide<unsigned int,char>();
					op.RegisterDivide<char,unsigned int>();
					op.RegisterDivide<unsigned int,unsigned char>();
					op.RegisterDivide<unsigned char,unsigned int>();
					op.RegisterDivide<unsigned int,bool>();
					op.RegisterDivide<bool,unsigned int>();
					op.RegisterDivide<long int,long int>();
					op.RegisterDivide<long int,unsigned long int>();
					op.RegisterDivide<unsigned long int,long int>();
					op.RegisterDivide<long int,float>();
					op.RegisterDivide<float,long int>();
					op.RegisterDivide<long int,double>();
					op.RegisterDivide<double,long int>();
					op.RegisterDivide<long int,char>();
					op.RegisterDivide<char,long int>();
					op.RegisterDivide<long int,unsigned char>();
					op.RegisterDivide<unsigned char,long int>();
					op.RegisterDivide<long int,bool>();
					op.RegisterDivide<bool,long int>();
					op.RegisterDivide<unsigned long int,unsigned long int>();
					op.RegisterDivide<unsigned long int,float>();
					op.RegisterDivide<float,unsigned long int>();
					op.RegisterDivide<unsigned long int,double>();
					op.RegisterDivide<double,unsigned long int>();
					op.RegisterDivide<unsigned long int,char>();
					op.RegisterDivide<char,unsigned long int>();
					op.RegisterDivide<unsigned long int,unsigned char>();
					op.RegisterDivide<unsigned char,unsigned long int>();
					op.RegisterDivide<unsigned long int,bool>();
					op.RegisterDivide<bool,unsigned long int>();
					op.RegisterDivide<float,float>();
					op.RegisterDivide<float,double>();
					op.RegisterDivide<double,float>();
					op.RegisterDivide<float,char>();
					op.RegisterDivide<char,float>();
					op.RegisterDivide<float,unsigned char>();
					op.RegisterDivide<unsigned char,float>();
					op.RegisterDivide<float,bool>();
					op.RegisterDivide<bool,float>();
					op.RegisterDivide<double,double>();
					op.RegisterDivide<double,char>();
					op.RegisterDivide<char,double>();
					op.RegisterDivide<double,unsigned char>();
					op.RegisterDivide<unsigned char,double>();
					op.RegisterDivide<double,bool>();
					op.RegisterDivide<bool,double>();
					op.RegisterDivide<char,char>();
					op.RegisterDivide<char,unsigned char>();
					op.RegisterDivide<unsigned char,char>();
					op.RegisterDivide<char,bool>();
					op.RegisterDivide<bool,char>();
					op.RegisterDivide<unsigned char,unsigned char>();
					op.RegisterDivide<unsigned char,bool>();
					op.RegisterDivide<bool,unsigned char>();
					op.RegisterDivide<bool,bool>();

					op.RegisterCast<int,int>();
					op.RegisterCast<int,unsigned int>();
					op.RegisterCast<unsigned int,int>();
					op.RegisterCast<int,long int>();
					op.RegisterCast<long int,int>();
					op.RegisterCast<int,unsigned long int>();
					op.RegisterCast<unsigned long int,int>();
					op.RegisterCast<int,float>();
					op.RegisterCast<float,int>();
					op.RegisterCast<int,double>();
					op.RegisterCast<double,int>();
					op.RegisterCast<int,char>();
					op.RegisterCast<char,int>();
					op.RegisterCast<int,unsigned char>();
					op.RegisterCast<unsigned char,int>();
					op.RegisterCast<int,bool>();
					op.RegisterCast<bool,int>();
					op.RegisterCast<unsigned int,unsigned int>();
					op.RegisterCast<unsigned int,long int>();
					op.RegisterCast<long int,unsigned int>();
					op.RegisterCast<unsigned int,unsigned long int>();
					op.RegisterCast<unsigned long int,unsigned int>();
					op.RegisterCast<unsigned int,float>();
					op.RegisterCast<float,unsigned int>();
					op.RegisterCast<unsigned int,double>();
					op.RegisterCast<double,unsigned int>();
					op.RegisterCast<unsigned int,char>();
					op.RegisterCast<char,unsigned int>();
					op.RegisterCast<unsigned int,unsigned char>();
					op.RegisterCast<unsigned char,unsigned int>();
					op.RegisterCast<unsigned int,bool>();
					op.RegisterCast<bool,unsigned int>();
					op.RegisterCast<long int,long int>();
					op.RegisterCast<long int,unsigned long int>();
					op.RegisterCast<unsigned long int,long int>();
					op.RegisterCast<long int,float>();
					op.RegisterCast<float,long int>();
					op.RegisterCast<long int,double>();
					op.RegisterCast<double,long int>();
					op.RegisterCast<long int,char>();
					op.RegisterCast<char,long int>();
					op.RegisterCast<long int,unsigned char>();
					op.RegisterCast<unsigned char,long int>();
					op.RegisterCast<long int,bool>();
					op.RegisterCast<bool,long int>();
					op.RegisterCast<unsigned long int,unsigned long int>();
					op.RegisterCast<unsigned long int,float>();
					op.RegisterCast<float,unsigned long int>();
					op.RegisterCast<unsigned long int,double>();
					op.RegisterCast<double,unsigned long int>();
					op.RegisterCast<unsigned long int,char>();
					op.RegisterCast<char,unsigned long int>();
					op.RegisterCast<unsigned long int,unsigned char>();
					op.RegisterCast<unsigned char,unsigned long int>();
					op.RegisterCast<unsigned long int,bool>();
					op.RegisterCast<bool,unsigned long int>();
					op.RegisterCast<float,float>();
					op.RegisterCast<float,double>();
					op.RegisterCast<double,float>();
					op.RegisterCast<float,char>();
					op.RegisterCast<char,float>();
					op.RegisterCast<float,unsigned char>();
					op.RegisterCast<unsigned char,float>();
					op.RegisterCast<float,bool>();
					op.RegisterCast<bool,float>();
					op.RegisterCast<double,double>();
					op.RegisterCast<double,char>();
					op.RegisterCast<char,double>();
					op.RegisterCast<double,unsigned char>();
					op.RegisterCast<unsigned char,double>();
					op.RegisterCast<double,bool>();
					op.RegisterCast<bool,double>();
					op.RegisterCast<char,char>();
					op.RegisterCast<char,unsigned char>();
					op.RegisterCast<unsigned char,char>();
					op.RegisterCast<char,bool>();
					op.RegisterCast<bool,char>();
					op.RegisterCast<unsigned char,unsigned char>();
					op.RegisterCast<unsigned char,bool>();
					op.RegisterCast<bool,unsigned char>();
					op.RegisterCast<bool,bool>();

					op.RegisterModulo<int,int>();
					op.RegisterModulo<int,unsigned int>();
					op.RegisterModulo<unsigned int,int>();
					op.RegisterModulo<int,long>();
					op.RegisterModulo<long,int>();
					op.RegisterModulo<int,unsigned long>();
					op.RegisterModulo<unsigned long,int>();
					op.RegisterModulo<unsigned int,unsigned int>();
					op.RegisterModulo<unsigned int,long>();
					op.RegisterModulo<long,unsigned int>();
					op.RegisterModulo<unsigned int,unsigned long>();
					op.RegisterModulo<unsigned long,unsigned int>();
					op.RegisterModulo<long,long>();
					op.RegisterModulo<long,unsigned long>();
					op.RegisterModulo<unsigned long,long>();
					op.RegisterModulo<unsigned long,unsigned long>();

					op.RegisterEquality<int,int>();
					op.RegisterEquality<int,long int>();
					op.RegisterEquality<long int,int>();
					op.RegisterEquality<int,float>();
					op.RegisterEquality<float,int>();
					op.RegisterEquality<int,double>();
					op.RegisterEquality<double,int>();
					op.RegisterEquality<int,char>();
					op.RegisterEquality<char,int>();
					op.RegisterEquality<long int,long int>();
					op.RegisterEquality<long int,float>();
					op.RegisterEquality<float,long int>();
					op.RegisterEquality<long int,double>();
					op.RegisterEquality<double,long int>();
					op.RegisterEquality<long int,char>();
					op.RegisterEquality<char,long int>();
					op.RegisterEquality<float,float>();
					op.RegisterEquality<float,double>();
					op.RegisterEquality<double,float>();
					op.RegisterEquality<float,char>();
					op.RegisterEquality<char,float>();
					op.RegisterEquality<double,double>();
					op.RegisterEquality<double,char>();
					op.RegisterEquality<char,double>();
					op.RegisterEquality<char,char>();

					op.RegisterEquality<unsigned int,unsigned int>();
					op.RegisterEquality<unsigned int,unsigned long int>();
					op.RegisterEquality<unsigned long int,unsigned int>();
					op.RegisterEquality<unsigned int,unsigned char>();
					op.RegisterEquality<unsigned char,unsigned int>();
					op.RegisterEquality<unsigned long int,unsigned long int>();
					op.RegisterEquality<unsigned long int,unsigned char>();
					op.RegisterEquality<unsigned char,unsigned long int>();
					op.RegisterEquality<unsigned char,unsigned char>();

					op.RegisterLessThan<int,int>();
					op.RegisterLessThan<int,long int>();
					op.RegisterLessThan<long int,int>();
					op.RegisterLessThan<int,float>();
					op.RegisterLessThan<float,int>();
					op.RegisterLessThan<int,double>();
					op.RegisterLessThan<double,int>();
					op.RegisterLessThan<int,char>();
					op.RegisterLessThan<char,int>();
					op.RegisterLessThan<long int,long int>();
					op.RegisterLessThan<long int,float>();
					op.RegisterLessThan<float,long int>();
					op.RegisterLessThan<long int,double>();
					op.RegisterLessThan<double,long int>();
					op.RegisterLessThan<long int,char>();
					op.RegisterLessThan<char,long int>();
					op.RegisterLessThan<float,float>();
					op.RegisterLessThan<float,double>();
					op.RegisterLessThan<double,float>();
					op.RegisterLessThan<float,char>();
					op.RegisterLessThan<char,float>();
					op.RegisterLessThan<double,double>();
					op.RegisterLessThan<double,char>();
					op.RegisterLessThan<char,double>();
					op.RegisterLessThan<char,char>();

					op.RegisterLessThan<unsigned int,unsigned int>();
					op.RegisterLessThan<unsigned int,unsigned long int>();
					op.RegisterLessThan<unsigned long int,unsigned int>();
					op.RegisterLessThan<unsigned int,unsigned char>();
					op.RegisterLessThan<unsigned char,unsigned int>();
					op.RegisterLessThan<unsigned long int,unsigned long int>();
					op.RegisterLessThan<unsigned long int,unsigned char>();
					op.RegisterLessThan<unsigned char,unsigned long int>();
					op.RegisterLessThan<unsigned char,unsigned char>();

					op.RegisterGreaterThan<int,int>();
					op.RegisterGreaterThan<int,long int>();
					op.RegisterGreaterThan<long int,int>();
					op.RegisterGreaterThan<int,float>();
					op.RegisterGreaterThan<float,int>();
					op.RegisterGreaterThan<int,double>();
					op.RegisterGreaterThan<double,int>();
					op.RegisterGreaterThan<int,char>();
					op.RegisterGreaterThan<char,int>();
					op.RegisterGreaterThan<long int,long int>();
					op.RegisterGreaterThan<long int,float>();
					op.RegisterGreaterThan<float,long int>();
					op.RegisterGreaterThan<long int,double>();
					op.RegisterGreaterThan<double,long int>();
					op.RegisterGreaterThan<long int,char>();
					op.RegisterGreaterThan<char,long int>();
					op.RegisterGreaterThan<float,float>();
					op.RegisterGreaterThan<float,double>();
					op.RegisterGreaterThan<double,float>();
					op.RegisterGreaterThan<float,char>();
					op.RegisterGreaterThan<char,float>();
					op.RegisterGreaterThan<double,double>();
					op.RegisterGreaterThan<double,char>();
					op.RegisterGreaterThan<char,double>();
					op.RegisterGreaterThan<char,char>();

					op.RegisterGreaterThan<unsigned int,unsigned int>();
					op.RegisterGreaterThan<unsigned int,unsigned long int>();
					op.RegisterGreaterThan<unsigned long int,unsigned int>();
					op.RegisterGreaterThan<unsigned int,unsigned char>();
					op.RegisterGreaterThan<unsigned char,unsigned int>();
					op.RegisterGreaterThan<unsigned long int,unsigned long int>();
					op.RegisterGreaterThan<unsigned long int,unsigned char>();
					op.RegisterGreaterThan<unsigned char,unsigned long int>();
					op.RegisterGreaterThan<unsigned char,unsigned char>();

					op.RegisterLessOrEqualThan<int,int>();
					op.RegisterLessOrEqualThan<int,long int>();
					op.RegisterLessOrEqualThan<long int,int>();
					op.RegisterLessOrEqualThan<int,float>();
					op.RegisterLessOrEqualThan<float,int>();
					op.RegisterLessOrEqualThan<int,double>();
					op.RegisterLessOrEqualThan<double,int>();
					op.RegisterLessOrEqualThan<int,char>();
					op.RegisterLessOrEqualThan<char,int>();
					op.RegisterLessOrEqualThan<long int,long int>();
					op.RegisterLessOrEqualThan<long int,float>();
					op.RegisterLessOrEqualThan<float,long int>();
					op.RegisterLessOrEqualThan<long int,double>();
					op.RegisterLessOrEqualThan<double,long int>();
					op.RegisterLessOrEqualThan<long int,char>();
					op.RegisterLessOrEqualThan<char,long int>();
					op.RegisterLessOrEqualThan<float,float>();
					op.RegisterLessOrEqualThan<float,double>();
					op.RegisterLessOrEqualThan<double,float>();
					op.RegisterLessOrEqualThan<float,char>();
					op.RegisterLessOrEqualThan<char,float>();
					op.RegisterLessOrEqualThan<double,double>();
					op.RegisterLessOrEqualThan<double,char>();
					op.RegisterLessOrEqualThan<char,double>();
					op.RegisterLessOrEqualThan<char,char>();

					op.RegisterLessOrEqualThan<unsigned int,unsigned int>();
					op.RegisterLessOrEqualThan<unsigned int,unsigned long int>();
					op.RegisterLessOrEqualThan<unsigned long int,unsigned int>();
					op.RegisterLessOrEqualThan<unsigned int,unsigned char>();
					op.RegisterLessOrEqualThan<unsigned char,unsigned int>();
					op.RegisterLessOrEqualThan<unsigned long int,unsigned long int>();
					op.RegisterLessOrEqualThan<unsigned long int,unsigned char>();
					op.RegisterLessOrEqualThan<unsigned char,unsigned long int>();
					op.RegisterLessOrEqualThan<unsigned char,unsigned char>();

					op.RegisterGreaterOrEqualThan<int,int>();
					op.RegisterGreaterOrEqualThan<int,long int>();
					op.RegisterGreaterOrEqualThan<long int,int>();
					op.RegisterGreaterOrEqualThan<int,float>();
					op.RegisterGreaterOrEqualThan<float,int>();
					op.RegisterGreaterOrEqualThan<int,double>();
					op.RegisterGreaterOrEqualThan<double,int>();
					op.RegisterGreaterOrEqualThan<int,char>();
					op.RegisterGreaterOrEqualThan<char,int>();
					op.RegisterGreaterOrEqualThan<long int,long int>();
					op.RegisterGreaterOrEqualThan<long int,float>();
					op.RegisterGreaterOrEqualThan<float,long int>();
					op.RegisterGreaterOrEqualThan<long int,double>();
					op.RegisterGreaterOrEqualThan<double,long int>();
					op.RegisterGreaterOrEqualThan<long int,char>();
					op.RegisterGreaterOrEqualThan<char,long int>();
					op.RegisterGreaterOrEqualThan<float,float>();
					op.RegisterGreaterOrEqualThan<float,double>();
					op.RegisterGreaterOrEqualThan<double,float>();
					op.RegisterGreaterOrEqualThan<float,char>();
					op.RegisterGreaterOrEqualThan<char,float>();
					op.RegisterGreaterOrEqualThan<double,double>();
					op.RegisterGreaterOrEqualThan<double,char>();
					op.RegisterGreaterOrEqualThan<char,double>();
					op.RegisterGreaterOrEqualThan<char,char>();

					op.RegisterGreaterOrEqualThan<unsigned int,unsigned int>();
					op.RegisterGreaterOrEqualThan<unsigned int,unsigned long int>();
					op.RegisterGreaterOrEqualThan<unsigned long int,unsigned int>();
					op.RegisterGreaterOrEqualThan<unsigned int,unsigned char>();
					op.RegisterGreaterOrEqualThan<unsigned char,unsigned int>();
					op.RegisterGreaterOrEqualThan<unsigned long int,unsigned long int>();
					op.RegisterGreaterOrEqualThan<unsigned long int,unsigned char>();
					op.RegisterGreaterOrEqualThan<unsigned char,unsigned long int>();
					op.RegisterGreaterOrEqualThan<unsigned char,unsigned char>();

					op.RegisterAnd<bool,bool>();

					op.RegisterOr<bool,bool>();
                }
        }
    }
