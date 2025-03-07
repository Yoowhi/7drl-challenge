#pragma once
class Stairs {
    public:
        enum Direction {
            UP,
            DOWN
        } direction;

        Stairs(Direction direction);
};
