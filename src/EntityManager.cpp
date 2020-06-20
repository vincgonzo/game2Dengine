#include "./EntityManager.h"

void EntityManager::ClearData(){
    for(auto& entity: entities){
        entity->Destroy();
    }
}

bool EntityManager::HasNoEntities() const {
    return entities.size() == 0;
}

void EntityManager::Update(float deltaTime){
    for(auto& entity: entities){
        entity->Update(deltaTime);
    }
}

void EntityManager::Render(){
    for(int layerNumb = 0; layerNumb < NUM_LAYERS; layerNumb++){
        for(auto& entity: GetEntitiesByLayer(static_cast<LayerType>(layerNumb))){
            entity->Render();
        }
    }
}

Entity& EntityManager::AddEntity(std::string entityName, LayerType layer){
    Entity *entity = new Entity(*this, entityName, layer);
    entities.emplace_back(entity);
    return *entity;
}

std::vector<Entity*> EntityManager::GetEntities() const {
    return entities;
}

std::vector<Entity*> EntityManager::GetEntitiesByLayer(LayerType layer) const {
    std::vector<Entity*> selectedEntities;
    for(auto& entity: entities){
        if(entity->layer == layer){
            selectedEntities.emplace_back(entity);
        }
    }
    return selectedEntities;
}

unsigned int  EntityManager::GetEntityCount(){
    return entities.size();
}
