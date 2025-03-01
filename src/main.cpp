#include "libtcod.hpp"
#include "core/Engine.hpp"

Engine engine(80, 50);

int main(int argc, char const* argv[]) {
	engine.start();
	return 0;
}
