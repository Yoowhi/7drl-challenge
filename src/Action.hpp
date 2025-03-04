class Entity;

class Action {
    public:
        Entity* actor;
        int priority;
        int priorityLeft;
        virtual void execute() = 0;
};
