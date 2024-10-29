#include "EntityManager.h"
#include "Components.h"
#include "Application.h"

#include <raylib.h>
#include <raymath.h>
#include <algorithm>
#include <memory>
#include <string>

using namespace Core;

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

        for (auto& entity : m_entities)
        {
            if (entity->IsAlive())
            {
                bool hasTransform = entity->HasComponent<TransformComponent>();
                bool hasModel = entity->HasComponent<ModelComponent>();
                bool hasCamera = entity->HasComponent<CameraComponent>();

                if (hasTransform && hasModel)
                {
                    TransformComponent& cTransform = entity->GetComponent<TransformComponent>();
                    ModelComponent& cModel = entity->GetComponent<ModelComponent>();

                    Vector3 rotation = (v3){
                        DEG2RAD * cTransform.rotation.x,
                        DEG2RAD * cTransform.rotation.y,
                        DEG2RAD * cTransform.rotation.z,
                    };

                    cModel.model->transform = MatrixRotateXYZ(rotation);
                    cModel.model->transform = MatrixScale(V3_OPEN(cTransform.scale));
                }

                if (hasCamera)
                {
                    CameraComponent& cCamera = entity->GetComponent<CameraComponent>();
                    if (cCamera.isPrimary)
                    {
                        App->SetPrimaryCamera(&cCamera.camera);
                    }

                    if (hasTransform)
                    {
                        TransformComponent& cTransform = entity->GetComponent<TransformComponent>();
                        cTransform.position = cCamera.camera.position;
                    }
                }
            }
        }
    }

    void EntityManager::DrawEntities()
    {
        for (auto& entity : m_entities)
        {
            if (entity->IsAlive())
            {
                bool hasTransform = entity->HasComponent<TransformComponent>();
                bool hasModel = entity->HasComponent<ModelComponent>();
                bool hasCamera = entity->HasComponent<CameraComponent>();

                if (hasTransform && hasModel)
                {
                    TransformComponent& cTransform = entity->GetComponent<TransformComponent>();
                    ModelComponent& cModel = entity->GetComponent<ModelComponent>();

                    DrawModel(*cModel.model, cTransform.position, 1.f, cModel.tint);
                }
            }
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
