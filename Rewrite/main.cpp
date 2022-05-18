#include "src/Yolk/Core/Core.h"
#include <iostream>

int main(){
    int a = 12;
    Yolk::TypedField x = a;
    auto cp = x.CopyByValue();
    std::cout << ((cp.ok == true) ? "Ok" : "Not Ok") << std::endl;
    auto cptf = cp.field;
    std::cout << cptf->Print() << std::endl;
    x = 24;
    std::cout << x.Print() << std::endl;
    std::cout << cptf->Print() << std::endl;
}
