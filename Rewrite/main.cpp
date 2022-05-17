#include "src/Yolk/Wrapper/TypedField.h"
#include <iostream>

struct Demo{
    int x = 1;
};
int main(){
    int x = 12;
    Demo y;
    
    Yolk::TypedField xr(x);
    Yolk::TypedField yr(y);

    auto check = xr.TryEQ(y);
}
