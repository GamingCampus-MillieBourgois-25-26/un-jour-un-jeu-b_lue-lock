#include "TowerComponent.h"
#include "Core/GameObject.h"

namespace TowerDefence {

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