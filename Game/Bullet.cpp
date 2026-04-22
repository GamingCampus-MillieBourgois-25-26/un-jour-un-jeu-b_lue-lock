#include "Bullet.h"
#include "Core/GameObject.h"

void Bullet::Update(float deltaTime)
{
    timer += deltaTime;

    if (timer >= lifeTime)
    {
        GetOwner()->Destroy();
        return;
    }

    auto pos = GetOwner()->GetPosition();
    pos += direction * speed * deltaTime;

    GetOwner()->SetPosition(pos);
}