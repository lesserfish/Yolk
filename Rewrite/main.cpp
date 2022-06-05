#include "src/Yolk/Core/Core.h"
#include "src/Yolk/Memory/Memory.h"
#include "src/Yolk/YolkVM/VM.h"
#include <iostream>
#include <string>
#include <cstdio>

int main(){
    int x = 4;
    int y = 0;

    Yolk::TypedField xr(x);
    Yolk::TypedField yr(y);

    xr.TryDIV(yr);

    std::cout << xr.Print() << std::endl;
}
