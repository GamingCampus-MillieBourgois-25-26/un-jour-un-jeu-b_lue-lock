#pragma once

#include "Player.h"
#include "Assets/Texture.h"
#include "Components/SpriteRenderer.h"
#include "Core/GameObject.h"
#include "Core/Scene.h"
#include "Modules/AssetsModule.h"
#include "Components/RectangleShapeRenderer.h"

class DefaultScene final : public Scene
{
public:
    DefaultScene() : Scene("DefaultScene")
    {

        GameObject* test = CreateGameObject("Test");
        test->SetPosition({ 300, 300 });

        // PLAYER
        GameObject* player = CreateGameObject("Player");
        player->SetPosition(Maths::Vector2f(300.f, 300.f));
        player->SetScale(Maths::Vector2f(0.3f, 0.3f));
        player->SetRotation(sf::degrees(180.f));

        player->CreateComponent<Player>();

        AssetsModule* assets = Engine::GetInstance()
            ->GetModuleManager()
            ->GetModule<AssetsModule>();

        Texture* playerTexture = assets->LoadAsset<Texture>("spaceShips_001.png");

        if (playerTexture)
        {
            player->CreateComponent<SpriteRenderer>(playerTexture);
        }
    }
};