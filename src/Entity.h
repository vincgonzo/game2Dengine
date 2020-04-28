#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include <string>

#include "./Constants.h"
#include "./Component.h"
#include "./EntityManager.h"

class EntityManager;
class Component;

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
        bool IsActive() const;
};

#endif
