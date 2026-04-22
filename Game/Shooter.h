#pragma once

#include "Core/Component.h"
#include "InputModule.h"
#include "Maths/Vector2.h"

class Shooter : public Component
{
public:
    void Update(float deltaTime) override;

    float fireRate = 0.2f;
    float timer = 0.f;
};