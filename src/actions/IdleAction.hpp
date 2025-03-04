class IdleAction : public Action {
    public:
        int x, y;

        IdleAction(Entity* actor);
        void execute();
};
