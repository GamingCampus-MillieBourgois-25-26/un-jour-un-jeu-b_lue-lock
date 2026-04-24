#include "ProjectileComponent.h"
#include "Core/GameObject.h"
#include "Core/Scene.h"
#include <cmath>

namespace TowerDefence {

    void ProjectileComponent::Init(EnemyComponent* t, float dmg, float spd)
    {
        target = t;
        damage = dmg;
        speed = spd;
    }

    void ProjectileComponent::Update(float dt)
    {
        if (done) return;

        // Cible morte ou arrivée → on se détruit
        if (!target || target->IsDead() || target->IsFinished())
        {
            done = true;
            GetOwner()->GetScene()->DestroyGameObject(GetOwner());
            return;
        }

        Maths::Vector2f pos = GetOwner()->GetPosition();
        Maths::Vector2f tgtPos = target->GetOwner()->GetPosition();

        float dx = tgtPos.x - pos.x;
        float dy = tgtPos.y - pos.y;
        float dist = std::sqrt(dx * dx + dy * dy);

        if (dist <= speed * dt)
        {
            // Impact
            target->TakeDamage(damage);
            done = true;
            GetOwner()->GetScene()->DestroyGameObject(GetOwner());
        }
        else
        {
            float nx = dx / dist;
            float ny = dy / dist;
            GetOwner()->SetPosition(Maths::Vector2f(
                pos.x + nx * speed * dt,
                pos.y + ny * speed * dt
            ));
        }
    }

    void ProjectileComponent::Render(sf::RenderWindow* window)
    {
        if (done) return;

        Maths::Vector2f pos = GetOwner()->GetPosition();

        sf::CircleShape dot(4.f);
        dot.setFillColor(sf::Color::Yellow);
        dot.setOrigin(sf::Vector2f(4.f, 4.f));
        dot.setPosition(sf::Vector2f(pos.x, pos.y));
        window->draw(dot);
    }

}