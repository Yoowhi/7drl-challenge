class Entity;

class Action {
    public:
        Entity* actor;
        int time;
        int timeLeft;
        virtual void execute() = 0;
};
