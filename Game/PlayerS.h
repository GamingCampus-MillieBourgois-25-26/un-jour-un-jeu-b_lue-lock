#pragma once

#include "Core/Component.h"
#include "Modules/InputModule.h"
#include "Modules/AssetsModule.h"
#include "Maths/Vector2.h"
#include "Components/SpriteRenderer.h"
#include "BulletS.h"

namespace BulletHell {

    class PlayerS : public Component {

    private:

        float speedS = 500.0f;
        float fireRate = 0.15f;
        float fireTimer = 0.0f;

    public:

        PlayerS() = default;
        virtual ~PlayerS() override = default;

        void updateS(float dt) override {

            Maths::Vector2f move = Maths::Vector2f::Zero;

            if (InputModule::GetKey(sf::Keyboard::Key::Z)) move.y -= 1;
            if (InputModule::GetKey(sf::Keyboard::Key::S)) move.y += 1;
            if (InputModule::GetKey(sf::Keyboard::Key::Q)) move.x -= 1;
            if (InputModule::GetKey(sf::Keyboard::Key::D)) move.x += 1;
            if (move != Maths::Vector2f::Zero) {

                // Si ton moteur n'a pas .Normalize(), on le fera à la main
                // move = move.Normalize(); 

                // Mise à jour de la position du GameObject propriétaire
                Maths::Vector2f currentPos = GetOwner()->GetPosition();
                GetOwner()->SetPosition(currentPos + (move * speedS * dt));
            }
        }
    };
}
