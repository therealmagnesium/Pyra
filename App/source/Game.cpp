#include "Game.h"

#include <Application.h>
#include <Entity.h>
#include <EntityManager.h>

#include <raylib.h>

using namespace Core;
using namespace Scene;

Game::Game(ApplicationSpecification& spec) : Application(spec)
{
    const ApplicationSpecification& appInfo = this->GetSpecification();
    DisableCursor();

    m_camera.position = (v3){0.f, 3.f, 10.f};
    m_camera.target = (v3){0.f, 0.f, 0.f};
    m_camera.up = (v3){0.f, 1.f, 0.f};
    m_camera.projection = CAMERA_PERSPECTIVE;
    m_camera.fovy = 45.f;

    this->SetPrimaryCamera(&m_camera);
}

void Game::OnUpdate()
{
}

void Game::OnRender()
{
    DrawGrid(50, 1.f);
    DrawCubeV((v3){0.f, 0.f, 0.f}, (v3){2.f, 2.f, 2.f}, BLUE);
}
void Game::OnRenderUI()
{
    DrawFPS(20, 20);
}

void Game::OnShutdown()
{
}
