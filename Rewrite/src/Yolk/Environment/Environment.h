#pragma once

#include "../Entity/Entity.h"
#include "../Generic.h"
#include <vector>

namespace Yolk {
    class Environment {   
        public:
            struct EntityInfo {
                Entity* entity;
                UUID uuid;    
            };
        public:
            RegisterEntity(Entity *);
            DeregisterEntity(Entity *);
        private:
            std::vector<EntityInfo> entities; 

    }
}
