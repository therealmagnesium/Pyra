#pragma once
#include "Base.h"
#include "Components.h"
#include "Entity.h"

#include <string>
#include <unordered_map>
#include <vector>
#include <memory>

namespace Scene
{
    typedef std::vector<std::shared_ptr<Entity>> EntityVec;
    typedef std::unordered_map<std::string, EntityVec> EntityMap;

    class EntityManager
    {
    public:
        EntityManager() = default;
        std::shared_ptr<Entity> AddEntity(const char* tag);
        void Update();
        void DrawEntities();

        inline u64 GetEntityCount() { return m_totalEntities; }

        EntityVec& GetEntities();
        EntityVec& GetEntities(const char* tag);

    private:
        u64 m_totalEntities = 0;
        EntityVec m_entities;
        EntityVec m_toAdd;
        EntityMap m_entityMap;
    };
}