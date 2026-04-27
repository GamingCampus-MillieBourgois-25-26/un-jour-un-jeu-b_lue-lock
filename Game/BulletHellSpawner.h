#pragma once

#include "Core/Component.h"

class BulletHellSpawner : public Component
{
public:
    bool isEnabled = true;
    bool canSpawnLaser = false;

    void Update(float _deltaTime) override;

private:
    void SpawnRainBullet();
    void SpawnEnemy();

    float bulletTimer = 0.0f;
    float enemyTimer = 0.0f;
    float laserTimer = 0.0f;

    float angleTimer = 0.0f;

    const float bulletRate = 0.22f;
    const float enemyRate = 4.f;
};