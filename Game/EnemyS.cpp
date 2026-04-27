#include "EnemyS.h"
#include "BulletS.h"
#include "BHGameState.h"
#include "SpawnQueue.h"
#include "Core/GameObject.h"
#include "Core/Scene.h"
#include <cmath>
#include <SFML/Graphics.hpp>

static constexpr float PI = 3.14159265f;

namespace BulletHell {

    void EnemyS::TakeDamage(float dmg)
    {
        if (dead) return;
        hp -= dmg;
        if (hp <= 0.f) { dead = true; BHGameState::Get().score += scoreValue; }
    }

    void EnemyS::SpawnBullet(Scene* scene, Maths::Vector2f pos,
        Maths::Vector2f dir, float spd, float r)
    {
        static int bid = 0;
        std::string name = "EBullet_" + std::to_string(bid++);
        TowerDefence::SpawnQueue::Get().Push([scene, name, pos, dir, spd, r]()
            {
                GameObject* obj = scene->CreateGameObject(name);
                obj->SetPosition(pos);
                auto* b = obj->CreateComponent<BulletS>();
                b->direction = dir;
                b->speed = spd;
                b->isEnemy = true;
                b->radius = r;
            });
    }

    void EnemyS::ShootLine()
    {
        Scene* scene = GetOwner()->GetScene();
        Maths::Vector2f pos = GetOwner()->GetPosition();
        for (int i = -1; i <= 1; i++)
        {
            float dx = i * 0.3f, dy = 1.f;
            float len = std::sqrt(dx * dx + dy * dy);
            SpawnBullet(scene, pos, Maths::Vector2f(dx / len, dy / len), 220.f, 6.f);
        }
    }

    void EnemyS::ShootSpiral(float dt)
    {
        Scene* scene = GetOwner()->GetScene();
        Maths::Vector2f pos = GetOwner()->GetPosition();
        angle += 180.f * dt;
        float rad = angle * PI / 180.f;
        for (int i = 0; i < 4; i++)
        {
            float a = rad + i * (PI / 2.f);
            SpawnBullet(scene, pos, Maths::Vector2f(std::cos(a), std::sin(a)), 180.f, 5.f);
        }
    }

    void EnemyS::ShootBurst()
    {
        Scene* scene = GetOwner()->GetScene();
        Maths::Vector2f pos = GetOwner()->GetPosition();
        for (int i = 0; i < 8; i++)
        {
            float a = i * (2.f * PI / 8.f);
            SpawnBullet(scene, pos, Maths::Vector2f(std::cos(a), std::sin(a)), 160.f, 6.f);
        }
    }

    void EnemyS::Update(float dt)
    {
        if (dead || done || BHGameState::Get().gameOver) return;
        Maths::Vector2f pos = GetOwner()->GetPosition();
        pos.x += velocity.x * dt;
        pos.y += velocity.y * dt;
        GetOwner()->SetPosition(pos);
        if (pos.y > 660.f) { done = true; return; }
        shootTimer += dt;
        if (pattern == EnemyPattern::Spiral)
            ShootSpiral(dt);
        else if (shootTimer >= shootRate)
        {
            shootTimer = 0.f;
            if (pattern == EnemyPattern::Line)  ShootLine();
            if (pattern == EnemyPattern::Burst) ShootBurst();
        }
    }

    void EnemyS::Render(sf::RenderWindow* window)
    {
        if (dead || done) return;
        Maths::Vector2f pos = GetOwner()->GetPosition();
        sf::CircleShape body(radius);
        body.setOrigin({ radius, radius });
        body.setPosition({ pos.x, pos.y });
        sf::Color col = sf::Color(80, 200, 80);
        if (pattern == EnemyPattern::Spiral) col = sf::Color(200, 80, 200);
        if (pattern == EnemyPattern::Burst)  col = sf::Color(200, 140, 30);
        body.setFillColor(col);
        body.setOutlineColor(sf::Color::White);
        body.setOutlineThickness(2.f);
        window->draw(body);
    }

    void EnemyS::Present()
    {
        if (dead || done) GetOwner()->MarkForDeletion();
    }
}