#pragma once
#include "Core/Component.h"
#include <SFML/Graphics.hpp>

namespace TowerDefence {

    class BaseTowerComponent : public Component
    {
    public:
        void Render(sf::RenderWindow* window) override;

       
        void TakeDamage(int amount);

        int hp = 30;
        int maxHp = 30;

        float cellSize = 50.f;

        sf::Color color = sf::Color(255, 140, 0);  
    };

}