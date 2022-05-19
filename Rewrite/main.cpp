#include "src/Yolk/Core/Core.h"
#include <iostream>
#include <string>

int main(){
    Yolk::Memory::DynamicMemory manager;
    manager.Debug("Should be empty.");
    auto o = manager.AllocateMemory<int>();

    *(o.wrapper.field) = 12;

    //EXPECT_STREQ(o.wrapper.field->Print().c_str(), "12");
    
    manager.Debug("One element with one viewer.");
    std::vector<Yolk::Wrapper> WrapperVec;
    WrapperVec.push_back(o.wrapper);
    manager.Debug("One element with two viewers.");
    WrapperVec.push_back(o.wrapper);
    manager.Debug("One element with three viewer.");
    WrapperVec.push_back(o.wrapper);

    //EXPECT_EQ(manager.UpdateViewersCount(o.wrapper.ID, 0), 4);
    WrapperVec.pop_back();
    //EXPECT_EQ(manager.UpdateViewersCount(o.wrapper.ID, 0), 3);
    WrapperVec.pop_back();
    *(WrapperVec.at(0).field) = 15;
    //EXPECT_EQ(manager.UpdateViewersCount(o.wrapper.ID, 0), 2);
    WrapperVec.pop_back();
    //EXPECT_EQ(manager.UpdateViewersCount(o.wrapper.ID, 0), 1);
    //EXPECT_STREQ(o.wrapper.field->Print().c_str(), "15");
    manager.Debug("One element with one viewer.Bye!");

}
