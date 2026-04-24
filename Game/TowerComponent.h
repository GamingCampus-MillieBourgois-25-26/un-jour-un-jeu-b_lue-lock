#pragma once
#include "Core/Component.h"
#include "SFML/Graphics.hpp"

namespace TowerDefence {

    class TowerComponent : public Component
    {
    public:
        void Update(float dt) override;
        void Render(sf::RenderWindow* window) override;

        float cellSize = 50.f;
        float range = 150.f;   // portée en pixels
        float fireRate = 1.f;     // tirs par seconde
        float damage = 20.f;

        sf::Color color = sf::Color(30, 144, 255);

    private:
        float fireTimer = 0.f;

        class EnemyComponent* FindClosestEnemy() const;
    };

}