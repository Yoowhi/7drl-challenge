class MoveAction : public Action {
    public:
        int x, y;

        MoveAction(Entity* actor, int x, int y);
        void execute();
};
