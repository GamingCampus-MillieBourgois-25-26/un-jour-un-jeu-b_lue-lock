#pragma once

#include "Core/Component.h"
#include "Maths/Vector2.h"

class Bullet : public Component
{
public:
    Maths::Vector2f direction = Maths::Vector2f::Zero;
    float speed = 400.f;
    float lifeTime = 2.f;
    float timer = 0.f;

    void Update(float dt) override;
};