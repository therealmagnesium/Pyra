#include "EntityManager.h"
#include "Components.h"

#include <raylib.h>
#include <algorithm>
#include <memory>
#include <string>

namespace Scene
{
    std::shared_ptr<Entity> EntityManager::AddEntity(const char* tag)
    {
        std::shared_ptr<Entity> entity = std::make_shared<Entity>(m_totalEntities++, tag);
        entity->SetActive(true);
        m_toAdd.push_back(entity);
        return entity;
    }

    void EntityManager::Update()
    {
        for (auto& entity : m_toAdd)
        {
            const char* entityTag = entity->GetTag();
            m_entities.push_back(entity);
            m_entityMap[entityTag].push_back(entity);
        }

        for (u64 i = 0; i < m_entities.size(); i++)
        {
            auto& entity = m_entities[i];
            const char* entityTag = entity->GetTag();
            if (!entity->IsAlive())
            {
                m_entities.erase(m_entities.begin() + i);
                m_entityMap[entityTag].erase(m_entities.begin() + i);
            }
        }

        m_toAdd.clear();
    }

    void EntityManager::DrawEntities()
    {
        for (u64 i = 0; i < m_entities.size(); i++)
        {
        }
    }

    EntityVec& EntityManager::GetEntities()
    {
        return m_entities;
    }
    EntityVec& EntityManager::GetEntities(const char* tag)
    {
        return m_entityMap[tag];
    }
}
