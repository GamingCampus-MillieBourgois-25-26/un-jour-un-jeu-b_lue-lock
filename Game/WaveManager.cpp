#include "WaveManager.h"
#include "Core/GameObject.h"
#include "Core/Scene.h"

namespace TowerDefence {

    void WaveManager::Init(const std::vector<Maths::Vector2i>& path, float cs)
    {
        enemyPath = path;
        cellSize = cs;
        spawnTimer = spawnInterval;
    }

    void WaveManager::Update(float dt)
    {
        if (allWavesDone) return;

        if (wavePending)
        {
            waveCooldownTimer -= dt;
            if (waveCooldownTimer <= 0.f)
            {
                wavePending = false;
                enemiesSpawned = 0;
                spawnTimer = spawnInterval;
                currentWave++;
            }
            return;
        }

        if (enemiesSpawned < enemiesPerWave)
        {
            spawnTimer += dt;
            if (spawnTimer >= spawnInterval)
            {
                spawnTimer = 0.f;
                SpawnEnemy();
                enemiesSpawned++;
            }
        }
        else
        {
            if (currentWave >= maxWaves)
                allWavesDone = true;
            else
            {
                wavePending = true;
                waveCooldownTimer = waveCooldown;
            }
        }
    }

    void WaveManager::SpawnEnemy()
    {
        // Récupère la scène via le GameObject owner
        Scene* scene = GetOwner()->GetScene();
        GameObject* obj = scene->CreateGameObject("Enemy");
        auto* enemy = obj->CreateComponent<EnemyComponent>();
        enemy->SetPath(enemyPath, cellSize);
    }

}