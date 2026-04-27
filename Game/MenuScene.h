#pragma once

#include "Core/Scene.h"
#include "Core/GameObject.h"
#include "MainMenu.h"

class MenuScene final : public Scene
{
public:
    MenuScene() : Scene("MenuScene", true)
    {
        GameObject* menuManager = CreateGameObject("MenuManager");
        if (menuManager)
        {
            menuManager->CreateComponent<MainMenu>();
        }
    }
};