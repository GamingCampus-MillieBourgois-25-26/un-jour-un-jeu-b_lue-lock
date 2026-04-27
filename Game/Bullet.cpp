#include "Bullet.h"
#include "Health.h"
#include "Components/SquareCollider.h" 
#include "Core/GameObject.h"
#include "Engine.h"
#include "Modules/SceneModule.h"
#include "Core/Scene.h"

void Bullet::Update(float deltaTime) {
    GameObject* owner = GetOwner();
    if (!owner) return;

    // Déplacement
    owner->SetPosition(owner->GetPosition() + (direction * speed * deltaTime));

    // Récupération des modules et de la scène
    auto* sm = Engine::GetInstance()->GetModuleManager()->GetModule<SceneModule>();
    if (!sm) return;

    Scene* scene = sm->GetSceneByName("BulletHell");
    if (!scene) return;

    auto* myCollider = owner->GetComponent<SquareCollider>();
    if (!myCollider) return;

    // 3. Détection de collision
    if (this->isEnemy) {
        GameObject* player = scene->FindGameObject("Player");
        if (player) {
            auto* playerCol = player->GetComponent<SquareCollider>();
            if (playerCol && SquareCollider::IsColliding(*myCollider, *playerCol)) {
                auto* h = player->GetComponent<Health>();
                if (h) h->TakeDamage(1);

                scene->DestroyGameObject(owner);
                return;
            }
        }
    }
    else {
        // LOGIQUE DES TIRS DU JOUEUR
        for (const auto& obj : scene->GetGameObjects()) {

            if (obj->GetName() != "Enemy" || obj.get() == owner) continue;

            auto* targetCol = obj->GetComponent<SquareCollider>();
            if (targetCol && SquareCollider::IsColliding(*myCollider, *targetCol)) {

                auto* h = obj->GetComponent<Health>();
                if (h) {
                    h->TakeDamage(1);
                    Logger::Log(ELogLevel::Debug, "Impact! Vie de l'ennemi : {}", h->currentHealth);
                }

                scene->DestroyGameObject(owner);
                return;
            }
        }
    }

    lifetime += deltaTime;
    if (lifetime > 5.0f) {
        scene->DestroyGameObject(owner);
        return;
    }
}