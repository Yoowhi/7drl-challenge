#include "libtcod.hpp"
#include "Controller.hpp"
#include "Entity.hpp"

Controller::Controller(Entity* owner) : owner(owner) {}

Controller::~Controller() {}

void Controller::update() {}
