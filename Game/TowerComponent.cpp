#include "TowerComponent.h"
#include "ProjectileComponent.h"
#include "EnemyComponent.h"
#include "Core/GameObject.h"
#include "Core/Scene.h"
#include <cmath>
#include <limits>

namespace TowerDefence {

    EnemyComponent* TowerComponent::FindClosestEnemy() const {
        Scene* scene = GetOwner()->GetScene();
        Maths::Vector2f myPos = GetOwner()->GetPosition();

        EnemyComponent* closest = nullptr;
        float bestDist = std::numeric_limits<float>::max();

        for (const auto& go : scene->GetGameObjects())
        {
            auto* enemy = go->GetComponent<EnemyComponent>();
            if (!enemy || enemy->IsDead() || enemy->IsFinished())
                continue;

            Maths::Vector2f ePos = go->GetPosition();
            float dx = ePos.x - myPos.x;
            float dy = ePos.y - myPos.y;
            float dist = std::sqrt(dx * dx + dy * dy);

            if (dist <= range && dist < bestDist)
            {
                bestDist = dist;
                closest = enemy;
            }
        }

        return closest;
    }

    void TowerComponent::Update(float dt)
    {
        fireTimer += dt;

        if (fireTimer >= 1.f / fireRate)
        {
            EnemyComponent* target = FindClosestEnemy();
            if (target)
            {
                fireTimer = 0.f;

                // Spawner un projectile à la position de la tour
                Scene* scene = GetOwner()->GetScene();
                GameObject* proj = scene->CreateGameObject("Projectile");
                proj->SetPosition(GetOwner()->GetPosition());

                auto* projectile = proj->CreateComponent<ProjectileComponent>();
                projectile->Init(target, damage, 300.f);
            }
        }
    }

    void TowerComponent::Render(sf::RenderWindow* window)
    {
        Maths::Vector2f pos = GetOwner()->GetPosition();

        float margin = cellSize * 0.1f;
        float size = cellSize - margin * 2.f;

        sf::RectangleShape shape(sf::Vector2f(size, size));
        shape.setFillColor(color);
        shape.setPosition(sf::Vector2f(pos.x + margin, pos.y + margin));
        window->draw(shape);
    }

}