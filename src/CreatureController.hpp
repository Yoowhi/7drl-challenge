class CreatureController : public Controller {
    public:
        CreatureController(Entity* owner);
        ~CreatureController();
        void update();
};
