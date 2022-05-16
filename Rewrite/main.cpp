#include "src/Yolk/Wrapper/TypedField.h"
#include <iostream>

int main(){
    int x = 12;
    float y = 12;
    Yolk::TypedField xr(x);
    Yolk::TypedField yr(y);

    //auto compres = xr.TryNEQ(12);
    //auto opres = xr.TryAND(0);

    //std::cout << opres << std::endl;
    //std::cout << xr.Print() << std::endl;

    auto check = xr.TryPLUS(yr);
    std::cout << check << std::endl << xr.Print() << std::endl;
}
