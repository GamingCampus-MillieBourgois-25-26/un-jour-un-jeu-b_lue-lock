#pragma once
#include "Core/Component.h"
#include "SFML/Graphics.hpp"

namespace TowerDefence {

    class TowerComponent : public Component
    {
    public:
        void Render(sf::RenderWindow* window) override;

        float cellSize = 50.f;
        sf::Color color = sf::Color(30, 144, 255); // bleu dodger
    };

}