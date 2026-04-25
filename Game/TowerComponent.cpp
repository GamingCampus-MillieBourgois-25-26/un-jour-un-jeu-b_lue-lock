#include "TowerDefenseScene.h"
#include "SpawnQueue.h"
#include "GameState.h"
#include "HUDComponent.h"
#include "SceneModule.h"
#include "Engine.h"
#include "ModuleManager.h"

namespace TowerDefence {

    TowerDefenseScene::TowerDefenseScene()
        : Scene("TowerDefenseScene")
    {
        // Reset de l'état global
        GameState::Get().Reset();

        // Grille visuelle
        GameObject* gridObj = CreateGameObject("Grid");
        auto* gridRenderer = gridObj->CreateComponent<GridRenderer>();
        gridRenderer->width = GRID_WIDTH;
        gridRenderer->height = GRID_HEIGHT;
        gridRenderer->cellSize = CELL_SIZE;

        InitGrid();

        enemyPath = {
            {0,2},{1,2},{2,2},{3,2},{4,2},
            {5,2},{6,2},{7,2},{8,2},{9,2},
            {9,3},{9,4},{9,5},{9,6},{9,7},
            {10,7},{11,7},{12,7},{13,7},{14,7},
            {15,7},{16,7},{17,7},{18,7},{19,7}
        };

        // Colorer le chemin sur la grille
        gridRenderer->path = enemyPath;

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

        // Callback flush SpawnQueue
        Engine::GetInstance()
            ->GetModuleManager()
            ->GetModule<SceneModule>()
            ->onPresent = []()
            {
                SpawnQueue::Get().Flush();
            };
    }

    void TowerDefenseScene::InitGrid()
    {
        grid.assign(GRID_HEIGHT, std::vector<CellType>(GRID_WIDTH, CellType::Empty));
    }

}