#include "libtcod.hpp"
#include "Controller.hpp"
#include "PlayerController.hpp"
#include "Entity.hpp"
#include "Action.hpp"
#include "ActionQueue.hpp"
#include "Engine.hpp"

Engine engine(80, 50);

int main(int argc, char const* argv[]) {
	engine.start();
	return 0;
}
