#define SDL_MAIN_HANDLED
#include <SDL.h>
#include "Engine.hpp"

Engine* engine;

static const int WIDTH_CELLS = 120;
static const int HEIGHT_CELLS = 70;

int main(int argc, char const* argv[]) {
    auto tileset = tcod::load_tilesheet("./data/tileset.png", {16, 16}, tcod::CHARMAP_CP437);
    tcod::Console* console = new tcod::Console{WIDTH_CELLS, HEIGHT_CELLS};
    auto params = TCOD_ContextParams{};
    params.tcod_version = TCOD_COMPILEDVERSION;
    params.console = console->get();
    params.window_title = "Endless Dungeon";
    params.sdl_window_flags = SDL_WINDOW_RESIZABLE;
    params.columns = WIDTH_CELLS;
    params.rows = HEIGHT_CELLS;
    params.vsync = true;
    params.tileset = tileset.get();
    params.argc = argc;
    params.argv = argv;
    tcod::Context* context = new tcod::Context(params);
    engine = new Engine(WIDTH_CELLS, HEIGHT_CELLS, console, context);
	engine->start();
	return 0;
}
