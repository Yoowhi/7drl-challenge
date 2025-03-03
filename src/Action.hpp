class Entity;

class Action {
    public:
        Entity* actor;
        int priority;
        virtual void execute() = 0;
};
