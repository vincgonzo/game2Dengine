#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include <string>

#include "./Component.h"
#include "./EntityManager.h"

class Entity {
    private:
        EntityManager& manager;
        bool isActive;
        std::vector<Component*> components;
    public:
        std::string name;
        Entity(EntityManager& manager);
        Entity(EntityManager& manager, std::string name);
        void Update(float delataTime);
        void Render();
        void Destroy();
        bool IsAcitve() const;
};

#endif
