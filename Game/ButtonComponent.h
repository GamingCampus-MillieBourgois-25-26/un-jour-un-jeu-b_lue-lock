#pragma once
#include "Core/Component.h"
#include "InputModule.h"
#include "Engine.h"
#include "SceneModule.h"
#include "TowerDefenseScene.h"

class ButtonComponent : public Component
{
public:
    void Update(float dt) override;
    void OnClick();

    sf::FloatRect bounds;
};