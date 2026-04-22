#include "Shooter.h"
#include "Bullet.h"
#include "Core/GameObject.h"
#include "Engine.h"
#include "Modules/SceneModule.h"
#include "Components/RectangleShapeRenderer.h"

void Shooter::Update(float deltaTime)
{
    timer += deltaTime;

    if (!InputModule::GetMouseButton(sf::Mouse::Button::Left))
        return;

    if (timer < fireRate)
        return;

    timer = 0.0f;

    // position joueur
    auto pos = GetOwner()->GetPosition();

    // direction souris
    Maths::Vector2f mouse(
        (float)InputModule::GetMousePosition().x,
        (float)InputModule::GetMousePosition().y
    );

    Maths::Vector2f dir = mouse - pos;

    float len = dir.Magnitude();
    if (len != 0)
        dir = dir / len;

    // récupérer scène
    SceneModule* sceneModule =
        Engine::GetInstance()->GetModuleManager()->GetModule<SceneModule>();

    Scene* scene = sceneModule->GetScenesList().front().get();

    // créer bullet
    GameObject* bullet = scene->CreateGameObject("Bullet");
    bullet->SetPosition(pos);

    // logique bullet
    Bullet* b = bullet->CreateComponent<Bullet>();
    b->direction = dir;

    // VISUALISATION
    auto* renderer = bullet->CreateComponent<RectangleShapeRenderer>();
    renderer->SetColor(sf::Color::Yellow);
    renderer->SetSize(Maths::Vector2f(10.f, 10.f));
}