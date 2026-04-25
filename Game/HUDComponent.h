#pragma once
#include "Core/Component.h"
#include "GameState.h"
#include <SFML/Graphics.hpp>

namespace TowerDefence {

    class HUDComponent : public Component
    {
    public:
        void Start()  override;
        void Render(sf::RenderWindow* window) override;

        // Coût d'une tour affiché dans le HUD
        int towerCost = 50;

    private:
        sf::Font font;
        bool     fontLoaded = false;

        void DrawText(sf::RenderWindow* window,
            const std::string& text,
            float x, float y,
            unsigned int size,
            sf::Color color);
    };
}