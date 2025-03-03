class PlayerController : public Controller {
    public:
        PlayerController(Entity* owner);
        ~PlayerController();
        void update();
};
