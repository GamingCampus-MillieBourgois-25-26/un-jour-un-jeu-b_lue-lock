#pragma once

#include "Core/Scene.h"
#include "Core/GameObject.h"
#include "Engine.h"
#include "Modules/AssetsModule.h"
#include "Components/SpriteRenderer.h"
#include "Assets/Texture.h"

#include "Player.h"
#include "Shooter.h"
#include "Health.h"
#include "GameManager.h"
#include "AsteroidSpawner.h"
#include "SquareCollider.h"

class BulletHellScene final : public Scene
{
public:
    BulletHellScene() : Scene("BulletHell", false)
    {
        InitScene();
    }

private:
    void InitScene()
    {
        GameObject* manager = CreateGameObject("GameManager");
        manager->CreateComponent<GameManager>();

        GameObject* spawner = CreateGameObject("Spawner");
        spawner->CreateComponent<AsteroidSpawner>();

        GameObject* player = CreateGameObject("Player");
        player->SetPosition(Maths::Vector2f(400.f, 400.f));
        player->SetScale(Maths::Vector2f(0.7f, 0.7f));

        auto* playerCol = player->CreateComponent<SquareCollider>();
        if (playerCol) {
            playerCol->SetWidth(40.0f);
            playerCol->SetHeight(40.0f);
        }

        player->CreateComponent<Player>();
        player->CreateComponent<Shooter>();

        auto* hp = player->CreateComponent<Health>();
        if (hp) {
            hp->currentHealth = 10;
        }

        AssetsModule* assets = Engine::GetInstance()
            ->GetModuleManager()
            ->GetModule<AssetsModule>();

        if (assets) {
            Texture* playerTexture = assets->LoadAsset<Texture>("enemyRed5.png");
            if (playerTexture) {
                player->CreateComponent<SpriteRenderer>(playerTexture);
            }
        }
    }
};