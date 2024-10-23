#include "Application.h"
#include "UI.h"

#include <raylib.h>
#include <rlImGui.h>
#include <rlgl.h>
#include <imgui.h>

using namespace UI;

namespace Core
{
    static bool appInitialized = false;
    Application* Application::s_instance = NULL;
    Application* App;

    Application::Application(ApplicationSpecification& spec) : m_specification(spec)
    {
        if (appInitialized)
        {
            TraceLog(LOG_ERROR, "Application cannot be initialized more than once!");
            return;
        }

        App = s_instance = this;

        InitWindow(m_specification.windowWidth, m_specification.windowHeight, m_specification.name.c_str());
        SetWindowState(FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_TOPMOST);
        SetTargetFPS(60);
        SetExitKey(KEY_NULL);

        m_editorCamera.position = (v3){0.f, 3.f, 10.f};
        m_editorCamera.target = (v3){0.f, 0.f, 0.f};
        m_editorCamera.up = (v3){0.f, 1.f, 0.f};
        m_editorCamera.projection = CAMERA_PERSPECTIVE;
        m_editorCamera.fovy = 45.f;

        m_primaryCamera = &m_editorCamera;
        m_framebuffer = LoadRenderTexture(m_specification.windowWidth, m_specification.windowHeight);

        UISetup();

        appInitialized = true;
    }

    Application::~Application()
    {
        UIShutdown();
        CloseWindow();
    }

    void Application::Run()
    {
        if (!appInitialized)
        {
            TraceLog(LOG_FATAL, "Cannot run the application because it's not initialized!");
            this->Quit();
            return;
        }

        if (!m_primaryCamera)
        {
            TraceLog(LOG_FATAL, "Cannot run the application because no primary camera is set!");
            this->Quit();
            return;
        }

        while (m_isRunning)
        {
            m_isRunning = !WindowShouldClose();
            if (IsKeyPressed(KEY_ESCAPE))
                this->Quit();

            m_specification.windowWidth = GetScreenWidth();
            m_specification.windowHeight = GetScreenHeight();

            UpdateCamera(m_primaryCamera, CAMERA_FREE);

            this->OnUpdate();
            m_entityManager.Update();

            BeginTextureMode(m_framebuffer);
            {
                ClearBackground({15, 15, 25, 255});
                BeginMode3D(*m_primaryCamera);
                {
                    m_entityManager.DrawEntities();
                    this->OnRender();
                }
                EndMode3D();
            }
            EndTextureMode();

            BeginDrawing();
            {
                ClearBackground({15, 15, 25, 255});

                UIBeginFrame();
                {
                    this->OnRenderUI();
                }
                UIEndFrame();
            }
            EndDrawing();
        }

        this->OnShutdown();
    }

    void Application::Quit()
    {
        m_isRunning = false;
    }
}
