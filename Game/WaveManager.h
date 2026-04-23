#pragma once
#include "Core/Component.h"
#include "EnemyComponent.h"
#include <vector>

namespace TowerDefence {

    class WaveManager : public Component
    {
    public:
        void Init(const std::vector<Maths::Vector2i>& path, float cellSize);
        void Update(float dt) override;

        int   maxWaves = 3;
        int   enemiesPerWave = 5;
        float spawnInterval = 1.5f;
        float waveCooldown = 5.f;

        int  GetCurrentWave() const { return currentWave; }
        bool IsAllWavesDone() const { return allWavesDone; }

    private:
        void SpawnEnemy();

        std::vector<Maths::Vector2i> enemyPath;
        float cellSize = 50.f;

        int   currentWave = 1;
        int   enemiesSpawned = 0;
        float spawnTimer = 0.f;
        float waveCooldownTimer = 0.f;
        bool  wavePending = false;
        bool  allWavesDone = false;
    };

}