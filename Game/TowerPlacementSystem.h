#pragma once
#include "Core/Component.h"
#include "CellType.h"
#include "Maths/Vector2.h"
#include <vector>

namespace TowerDefence {

    class TowerPlacementSystem : public Component
    {
    public:
        void Init(
            std::vector<std::vector<CellType>>* grid,
            const std::vector<Maths::Vector2i>& enemyPath,
            int gridWidth, int gridHeight, float cellSize
        );

        void Update(float dt) override;

    private:
        bool CanPlace(int gx, int gy) const;
        void PlaceTower(int gx, int gy);
        Maths::Vector2f GridToWorld(int gx, int gy) const;

        std::vector<std::vector<CellType>>* grid = nullptr;
        std::vector<Maths::Vector2i> enemyPath;

        int   gridWidth = 20;
        int   gridHeight = 12;
        float cellSize = 50.f;

        bool wasClickedLastFrame = false;
    };

}