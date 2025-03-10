#include "StairsAction.hpp"
#include "../Entity.hpp"
#include "../Being.hpp"
#include "../Stairs.hpp"
#include "../Engine.hpp"

StairsAction::StairsAction(Entity* actor, Stairs* stairs) : Action(actor, -1000000), stairs(stairs) {}

void StairsAction::execute() {
    switch (stairs->direction) {
        case Stairs::UP: engine->state = Engine::UPSTAIRS; break;
        case Stairs::DOWN: engine->state = Engine::DOWNSTAIRS; break;
        default: throw "Unknown Stairs direction";
    }
}
