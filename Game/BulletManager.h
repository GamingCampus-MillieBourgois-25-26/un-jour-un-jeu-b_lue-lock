#pragma once

#include "Core/Component.h"

class BulletManager : public Component
{
public:
    void Update(float _delta_time) override;

private:
    float spawnTimer = 0.0f;
    float spawnRate = 0.25f;
    float angle = 0.0f;
};