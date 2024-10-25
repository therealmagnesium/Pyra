#pragma once
#include "Base.h"
#include "Entity.h"
#include "EntityManager.h"

#include <raylib.h>
#include <string>

using namespace Scene;

namespace Core
{
    struct ApplicationSpecification
    {
        std::string name = "Untitled";
        std::string version = "1.0-dev";
        std::string author = "No author specified";

        u32 windowWidth = 1280;
        u32 windowHeight = 720;

        bool isVsyncEnabled = true;
    };

    class Application
    {
    public:
        Application() = default;
        Application(ApplicationSpecification& spec);
        ~Application();

        void Run();
        void Quit();

        static inline Application* Get() { return s_instance; }
        inline bool IsDebugEnabled() const { return m_isDebugEnabled; }
        inline const ApplicationSpecification& GetSpecification() const { return m_specification; }
        inline const RenderTexture& GetFramebuffer() const { return m_framebuffer; }
        inline const Shader& GetDefaultShader() const { return m_defaultShader; }

        inline void SetDebugEnabled(bool debug) { m_isDebugEnabled = debug; }
        inline void SetPrimaryCameraLock(bool locked) { m_isPrimaryCameraLocked = locked; }
        inline void SetPrimaryCamera(Camera* camera) { m_primaryCamera = camera; }
        inline std::shared_ptr<Entity> CreateEntity(const char* tag) { return m_entityManager.AddEntity(tag); }

    protected:
        virtual void OnUpdate() {}
        virtual void OnRender() {}
        virtual void OnRenderUI() {}
        virtual void OnShutdown() {}

    private:
        bool m_isRunning = true;
        bool m_isDebugEnabled = true;
        bool m_isPrimaryCameraLocked = true;
        ApplicationSpecification m_specification;
        EntityManager m_entityManager;

        RenderTexture m_framebuffer;
        Shader m_defaultShader;
        Camera m_editorCamera;
        Camera* m_primaryCamera = NULL;

        static Application* s_instance;
    };

    extern Application* App;
}
