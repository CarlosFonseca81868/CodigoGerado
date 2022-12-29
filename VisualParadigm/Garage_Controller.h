#include "Garage_Controller_sm.h"

class Garage_Controller
{
    private:
        Garage_ControllerContext _fsm;


    bool NoObstacle;

    public:
        Garage_Controller() : _fsm(*this) {
        }

        Garage_ControllerContext& getContext() {
            return _fsm;
        }

        void stop() {
            _fsm.stop();
        }

        void fechar() {
            _fsm.fechar();
        }

        void abrir();

        void BotaoPremido() {
            _fsm.BotaoPremido();
        }

        void fim_stop() {
            _fsm.fim_stop();
        }

        void stop_fecho() {
            _fsm.stop_fecho();
        }

};
