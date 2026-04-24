#pragma once
#include "Core/Component.h"
#include "EnemyComponent.h"

namespace TowerDefence {

    class ProjectileComponent : public Component
    {
    public:
        void Init(EnemyComponent* target, float damage, float speed);
        void Update(float dt) override;
        void Render(sf::RenderWindow* window) override;

    private:
        EnemyComponent* target = nullptr;
        float damage = 20.f;
        float speed = 300.f;
        bool  done = false;
    };

}