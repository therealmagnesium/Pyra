#pragma once
#include <imgui.h>

namespace UI
{
    void UISetup();
    void UIShutdown();
    void UIBeginFrame();
    void UIEndFrame();

    ImVec2 GetLargestSizeForViewport();
    ImVec2 GetViewportCenteredPosition(ImVec2 aspectSize);
}
