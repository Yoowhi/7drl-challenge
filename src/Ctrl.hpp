#pragma once
#include "SDL.h"

class Ctrl {
    public:
        static const SDL_Scancode UP = SDL_SCANCODE_W;
        static const SDL_Scancode UPRIGHT = SDL_SCANCODE_E;
        static const SDL_Scancode RIGHT = SDL_SCANCODE_D;
        static const SDL_Scancode DOWNRIGHT = SDL_SCANCODE_C;
        static const SDL_Scancode DOWN = SDL_SCANCODE_X;
        static const SDL_Scancode DOWNLEFT = SDL_SCANCODE_Z;
        static const SDL_Scancode LEFT = SDL_SCANCODE_A;
        static const SDL_Scancode UPLEFT = SDL_SCANCODE_Q;
        static const SDL_Scancode IDLE = SDL_SCANCODE_S;
        static const SDL_Scancode ACTIVATE = SDL_SCANCODE_F;
        static const SDL_Scancode USE0 = SDL_SCANCODE_Y;
        static const SDL_Scancode USE1 = SDL_SCANCODE_U;
        static const SDL_Scancode USE2 = SDL_SCANCODE_I;
        static const SDL_Scancode USE3 = SDL_SCANCODE_O;
        static const SDL_Scancode USE4 = SDL_SCANCODE_P;
        static const SDL_Scancode INCREASE_STRENGTH = SDL_SCANCODE_V;
        static const SDL_Scancode INCREASE_HEALTH = SDL_SCANCODE_B;
        static const SDL_Scancode INCREASE_AGILITY = SDL_SCANCODE_N;
        static const SDL_Scancode INCREASE_ENDURANCE = SDL_SCANCODE_M;
};
