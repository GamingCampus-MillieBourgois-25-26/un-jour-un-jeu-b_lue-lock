#include "ButtonMenu.h"


void ButtonMenu::Update(float dt)
{
    if (!rect)
        return;

    if (InputModule::GetMouseButtonDown(sf::Mouse::Button::Left)) {

        Maths::Vector2i mouse = InputModule::GetMousePosition();

        Maths::Vector2f pos = GetOwner()->GetPosition();
        Maths::Vector2f size = rect->GetSize();

        sf::FloatRect bounds(
            sf::Vector2f(pos.x, pos.y),
            sf::Vector2f(size.x, size.y)
        );

        if (bounds.contains(sf::Vector2f(mouse.x, mouse.y))) {

            if (onClick)
                onClick();
        }
    }
}
