#pragma once
#include "Core/Component.h"
#include "BulletS.h"
#include "Modules/AssetsModule.h"
#include <cmath>

namespace BulletHell {

    class BulletS : public Component {

    public:
        Maths::Vector2f direction;
        float speed = 600.0f;

        void Update(float dt) override {
            // Déplacement
            Maths::Vector2f pos = GetOwner()->GetPosition();
            GetOwner()->SetPosition(pos + (direction * speed * dt));

            // Destruction si hors écran (600x600 selon ton WindowModule)
            if (pos.x < -50 || pos.x > 650 || pos.y < -50 || pos.y > 650) {
                GetOwner()->MarkForDeletion();
            }
        }
    };
}