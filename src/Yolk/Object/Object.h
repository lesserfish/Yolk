#pragma once

#include "../Environment/Environment.h"
#include <string>

namespace Yolk {
    class Entity {
       
        public:
        struct InitOptions {};
        Entity(InitOptions options);

        public:
        
        template<typename Type> RegisterField(std::string, Type&);
        template<typename Out, typename... In> RegisterMethod(std::string, std::function<Out(In...)>);
        RegisterEntity(std::string, Entity* );
        DeregisterName(std::string);

        ExecuteScript(std::string source);


        private:
        Environment env;

    };
}
