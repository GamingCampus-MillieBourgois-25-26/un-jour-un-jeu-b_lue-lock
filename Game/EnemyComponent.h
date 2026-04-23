#pragma once
#include "Core/Component.h"
#include "Maths/Vector2.h"
#include "SFML/Graphics.hpp"
#include <vector>

namespace TowerDefence {

    class EnemyComponent : public Component
    {
    public:
        // Initialise le chemin (liste de cases en coordonnées grille)
        void SetPath(const std::vector<Maths::Vector2i>& path, float cellSize);

        void Update(float dt) override;
        void Render(sf::RenderWindow* window) override;

        bool IsFinished() const;

    private:
        std::vector<Maths::Vector2i> path;   // cases à parcourir
        float cellSize = 50.f;

        int   currentWaypoint = 0;           // index case courante
        float speed = 120.f;                 // pixels/seconde

        Maths::Vector2f worldTarget;         // position monde de la prochaine case
        bool  finished = false;

        Maths::Vector2f GridToWorld(const Maths::Vector2i& cell) const;
    };

}