#include "ButtonComponent.h"
#include "Engine.h"
#include "SceneModule.h"
#include "WindowModule.h"
#include "TowerDefenseScene.h"

void ButtonComponent::Update(float dt) {

    Maths::Vector2i mouse = InputModule::GetMousePosition();

    sf::Vector2f pos = static_cast<sf::Vector2f>(GetOwner()->GetPosition());
    sf::Vector2f size = static_cast<sf::Vector2f>(GetOwner()->GetScale());

    bounds = sf::FloatRect(pos, size);

    if (InputModule::GetMouseButtonDown(sf::Mouse::Button::Left))
    {
        if (bounds.contains(sf::Vector2f(mouse.x, mouse.y)))
        {
            OnClick();
        }
    }
}

void ButtonComponent::OnClick()
{
    Engine::GetInstance()
        ->GetModuleManager()
        ->GetModule<SceneModule>()
        ->SetScene<TowerDefence::TowerDefenseScene>();
}



