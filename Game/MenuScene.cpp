#include "MenuScene.h"

MenuScene::MenuScene() : Scene("MenuScene") {

    CreateButton("Play TD", Maths::Vector2f(20, 20));

}

void MenuScene::CreateButton(const std::string& name, const Maths::Vector2f& pos) {
  
    GameObject* button = CreateGameObject(name);

    button->SetPosition(Maths::Vector2f(200, 200));
    button->SetScale(Maths::Vector2f(200, 80)); 

    auto* rect = button->CreateComponent<RectangleShapeRenderer>();
    rect->SetColor(sf::Color::Blue);

    button->CreateComponent<ButtonComponent>();
}