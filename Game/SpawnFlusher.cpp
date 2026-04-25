#pragma once
#include "Core/Component.h"
#include "SpawnQueue.h"

namespace TowerDefence {

    class SpawnFlusher : public Component {

    public:

        void Present() override {

            SpawnQueue::Get().Flush();

        }
    };
}