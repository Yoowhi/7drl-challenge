#include "StairsAction.hpp"
#include "../Entity.hpp"
#include "../Being.hpp"
#include "../Stairs.hpp"
#include "../Engine.hpp"

StairsAction::StairsAction(Entity* actor, Stairs* stairs) : Action(actor, 100), stairs(stairs) {}

void StairsAction::execute() {
    switch (stairs->direction)
    {
        case Stairs::UP: engine.state = Engine::UPSTAIRS; break;
        case Stairs::DOWN: engine.state = Engine::DOWNSTAIRS; break;
        default: throw std::runtime_error("Unknown Stairs direction");
    }
    actor->being->restoreStamina(this->time);
}
