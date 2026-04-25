#include "TowerDefenseScene.h"
#include "BaseTowerComponent.h"
#include "SpawnQueue.h"
#include "SpawnFlusher.h"       // ← remplace Engine/SceneModule/ModuleManager
#include "GameState.h"

namespace TowerDefence {

    TowerDefenseScene::TowerDefenseScene()
        : Scene("TowerDefenseScene")
    {
        GameState::Get().Reset();

        // Grille visuelle
        GameObject* gridObj = CreateGameObject("Grid");
        auto* gridRenderer = gridObj->CreateComponent<GridRenderer>();
        gridRenderer->width = GRID_WIDTH;
        gridRenderer->height = GRID_HEIGHT;
        gridRenderer->cellSize = CELL_SIZE;
        gridRenderer->path = enemyPath;

        InitGrid();

        enemyPath = {
            {0,2},{1,2},{2,2},{3,2},{4,2},
            {5,2},{6,2},{7,2},{8,2},{9,2},
            {9,3},{9,4},{9,5},{9,6},{9,7},
            {10,7},{11,7},{12,7},{13,7},{14,7},
            {15,7},{16,7},{17,7},{18,7},{19,7}
        };
        gridRenderer->path = enemyPath;  // maintenant que c'est rempli

        // WaveManager
        GameObject* waveObj = CreateGameObject("WaveManager");
        auto* waveManager = waveObj->CreateComponent<WaveManager>();
        waveManager->SetConfig(enemyPath, CELL_SIZE);

        // TowerPlacementSystem
        GameObject* placementObj = CreateGameObject("PlacementSystem");
        auto* placement = placementObj->CreateComponent<TowerPlacementSystem>();
        placement->SetConfig(&grid, enemyPath, GRID_WIDTH, GRID_HEIGHT, CELL_SIZE);
        placement->towerCost = 50;

        // HUD
        GameObject* hudObj = CreateGameObject("HUD");
        auto* hud = hudObj->CreateComponent<HUDComponent>();
        hud->towerCost = placement->towerCost;

        // BaseTower — bout du chemin {19,7}
        GameObject* baseObj = CreateGameObject("BaseTower");
        auto* base = baseObj->CreateComponent<BaseTowerComponent>();
        base->cellSize = CELL_SIZE;
        base->hp = 30;
        base->maxHp = 30;
        GameState::Get().playerHP = base->hp;
        Maths::Vector2i lastCell = enemyPath.back();
        baseObj->SetPosition(Maths::Vector2f(
            lastCell.x * CELL_SIZE + CELL_SIZE * 0.5f,
            lastCell.y * CELL_SIZE + CELL_SIZE * 0.5f
        ));

       
        GameObject* flusherObj = CreateGameObject("SpawnFlusher");
        flusherObj->CreateComponent<SpawnFlusher>();
    }

    void TowerDefenseScene::InitGrid()
    {
        grid.assign(GRID_HEIGHT, std::vector<CellType>(GRID_WIDTH, CellType::Empty));
    }

}