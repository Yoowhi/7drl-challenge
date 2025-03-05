#include "libtcod.hpp"
#include "Controller.hpp"
#include "Action.hpp"
#include "Entity.hpp"
#include "Being.hpp"
#include "Map.hpp"
#include "ActionQueue.hpp"
#include "Engine.hpp"


Action::Action(Entity* actor, int time) : actor(actor), time(time), timeLeft(time) {
    float mult = this->actor->being->getTimeMultiplier();
    this->time = (int)((float)this->time * mult);
    this->timeLeft = this->time;
}
