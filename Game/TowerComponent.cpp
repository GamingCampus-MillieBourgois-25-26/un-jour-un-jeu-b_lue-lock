#include "TowerComponent.h"
#include "EnemyComponent.h"
#include "Core/GameObject.h"
#include "Core/Scene.h"
#include <cmath>

namespace TowerDefence {

    void TowerComponent::Update(float dt)
    {
        fireTimer += dt;
        if (fireTimer < 1.f / fireRate)
            return;

        fireTimer = 0.f;

        EnemyComponent* target = FindClosestEnemy();
        if (target)
        {
            target->TakeDamage(damage);
            hasPendingShot = true;
            pendingTarget = target->GetOwner()->GetName();
        }
    }

    void TowerComponent::Render(sf::RenderWindow* window)
    {
        Maths::Vector2f pos = GetOwner()->GetPosition();
        float radius = cellSize * 0.4f;

        // Corps de la tour
        sf::CircleShape body(radius);
        body.setFillColor(color);
        body.setPosition({ pos.x - radius, pos.y - radius });
        window->draw(body);

        // Cercle de portée (semi-transparent)
        sf::CircleShape rangeCircle(range);
        rangeCircle.setFillColor(sf::Color::Transparent);
        rangeCircle.setOutlineColor(sf::Color(255, 255, 255, 60));
        rangeCircle.setOutlineThickness(1.f);
        rangeCircle.setPosition({ pos.x - range, pos.y - range });
        window->draw(rangeCircle);
    }

    void TowerComponent::Present()
    {
        hasPendingShot = false;
        pendingTarget.clear();
    }

    EnemyComponent* TowerComponent::FindClosestEnemy()
    {
        EnemyComponent* closest = nullptr;
        float minDist = range;

        Maths::Vector2f pos = GetOwner()->GetPosition();
        Scene* scene = GetOwner()->GetScene();
        if (!scene)
            return nullptr;

        for (const auto& go : scene->GetGameObjects())
        {
            auto* enemy = go->GetComponent<EnemyComponent>();
            if (!enemy || enemy->IsDead() || enemy->IsFinished())
                continue;

            Maths::Vector2f ePos = go->GetPosition();
            float dx = ePos.x - pos.x;
            float dy = ePos.y - pos.y;
            float dist = std::sqrt(dx * dx + dy * dy);

            if (dist < minDist)
            {
                minDist = dist;
                closest = enemy;
            }
        }
        return closest;
    }

} // namespace TowerDefence