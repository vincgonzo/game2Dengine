#include "./EntityManager.h"
#include "./Collision.h"
#include "./Components/ColliderComponent.h"

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

CollisionType EntityManager::CheckCollisions() const {
    for(auto& entity: entities){
        if(entity->HasComponent<ColliderComponent>()){
            ColliderComponent* thisCollider = entity->GetComponent<ColliderComponent>();
            for(auto& otherEntity: entities){
                if(entity->name.compare(otherEntity->name) != 0 && otherEntity->HasComponent<ColliderComponent>()){
                    ColliderComponent* otherCollider = otherEntity->GetComponent<ColliderComponent>();
                    if(Collision::CheckRectangleCollision(thisCollider->collider, otherCollider->collider)){
                        if(thisCollider->colliderTag.compare("PLAYER") == 0 && otherCollider->colliderTag.compare("ENEMY") == 0)
                        {
                            return PLAYER_ENEMY_COLLISION; 
                        }
                        if(thisCollider->colliderTag.compare("PLAYER") == 0 && otherCollider->colliderTag.compare("PROJECTILE") == 0)
                        {
                            return PLAYER_PROJECTILE_COLLISION; 
                        }
                        if(thisCollider->colliderTag.compare("ENEMY") == 0 && otherCollider->colliderTag.compare("FRIENDLY_PROJECTILE") == 0)
                        {
                            return ENEMY_PROJECTILE_COLLISION; 
                        }
                        if(thisCollider->colliderTag.compare("PLAYER") == 0 && otherCollider->colliderTag.compare("LEVEL_COMPLETE") == 0)
                        {
                            return PLAYER_LEVEL_COMPLETE_COLLISION; 
                        }
                    }
                }
            }
        }
    }
    return NO_COLLISION;
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
