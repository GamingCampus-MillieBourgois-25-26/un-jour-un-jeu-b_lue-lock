#include "EnemyComponent.h"
#include "Core/GameObject.h"
#include <cmath>

namespace TowerDefence {

    Maths::Vector2f EnemyComponent::GridToWorld(const Maths::Vector2i& cell) const
    {
        return Maths::Vector2f(
            cell.x * cellSize + cellSize * 0.5f,
            cell.y * cellSize + cellSize * 0.5f
        );
    }

    void EnemyComponent::SetPath(const std::vector<Maths::Vector2i>& p, float cs)
    {
        path = p;
        cellSize = cs;
        currentWaypoint = 0;
        finished = false;

        if (!path.empty())
        {
            worldTarget = GridToWorld(path[0]);
            GetOwner()->SetPosition(worldTarget);
        }
    }

    void EnemyComponent::Update(float dt)
    {
        if (finished || path.empty()) return;

        Maths::Vector2f pos = GetOwner()->GetPosition();

        // Vecteur vers la cible
        float dx = worldTarget.x - pos.x;
        float dy = worldTarget.y - pos.y;
        float dist = std::sqrt(dx * dx + dy * dy);

        if (dist <= speed * dt)
        {
            // On est arrivé à cette case — snap et passer à la suivante
            GetOwner()->SetPosition(worldTarget);
            currentWaypoint++;

            if (currentWaypoint >= static_cast<int>(path.size()))
            {
                finished = true;
                return;
            }

            worldTarget = GridToWorld(path[currentWaypoint]);
        }
        else
        {
            // Avancer vers la cible
            float nx = dx / dist;
            float ny = dy / dist;
            GetOwner()->SetPosition(Maths::Vector2f(
                pos.x + nx * speed * dt,
                pos.y + ny * speed * dt
            ));
        }
    }

    void EnemyComponent::Render(sf::RenderWindow* window)
    {
        if (finished) return;

        Maths::Vector2f pos = GetOwner()->GetPosition();

        sf::CircleShape circle(cellSize * 0.35f);
        circle.setFillColor(sf::Color::Red);
        circle.setOrigin(sf::Vector2f(cellSize * 0.35f, cellSize * 0.35f));
        circle.setPosition(sf::Vector2f(pos.x, pos.y));
        window->draw(circle);
    }

    bool EnemyComponent::IsFinished() const { return finished; }

}