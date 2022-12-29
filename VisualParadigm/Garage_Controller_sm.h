#ifndef _H_GARAGE_CONTROLLER_SM
#define _H_GARAGE_CONTROLLER_SM

#define SMC_USES_IOSTREAMS

#include "statemap.h"

// Forward declarations.
class Garage_ControllerFSM;
class Garage_ControllerFSM_Fechada;
class Garage_ControllerFSM_A_Abrir;
class Garage_ControllerFSM_A_Fechar;
class Garage_ControllerFSM_Aberta;
class Garage_ControllerFSM_Default;
class Garage_ControllerState;
class Garage_ControllerContext;
class Garage_Controller;

class Garage_ControllerState :
    public State
{
public:

    Garage_ControllerState(const char *name, int stateId)
    : State(name, stateId)
    {};

    virtual void Entry(Garage_ControllerContext&) {};
    virtual void Exit(Garage_ControllerContext&) {};

    virtual void BotaoPremido(Garage_ControllerContext& context);
    virtual void fechar(Garage_ControllerContext& context);
    virtual void fim_stop(Garage_ControllerContext& context);
    virtual void stop(Garage_ControllerContext& context);
    virtual void stop_fecho(Garage_ControllerContext& context);

protected:

    virtual void Default(Garage_ControllerContext& context);
};

class Garage_ControllerFSM
{
public:

    static Garage_ControllerFSM_Fechada Fechada;
    static Garage_ControllerFSM_A_Abrir A_Abrir;
    static Garage_ControllerFSM_A_Fechar A_Fechar;
    static Garage_ControllerFSM_Aberta Aberta;
};

class Garage_ControllerFSM_Default :
    public Garage_ControllerState
{
public:

    Garage_ControllerFSM_Default(const char *name, int stateId)
    : Garage_ControllerState(name, stateId)
    {};

};

class Garage_ControllerFSM_Fechada :
    public Garage_ControllerFSM_Default
{
public:
    Garage_ControllerFSM_Fechada(const char *name, int stateId)
    : Garage_ControllerFSM_Default(name, stateId)
    {};

    void BotaoPremido(Garage_ControllerContext& context);
};

class Garage_ControllerFSM_A_Abrir :
    public Garage_ControllerFSM_Default
{
public:
    Garage_ControllerFSM_A_Abrir(const char *name, int stateId)
    : Garage_ControllerFSM_Default(name, stateId)
    {};

    void stop(Garage_ControllerContext& context);
};

class Garage_ControllerFSM_A_Fechar :
    public Garage_ControllerFSM_Default
{
public:
    Garage_ControllerFSM_A_Fechar(const char *name, int stateId)
    : Garage_ControllerFSM_Default(name, stateId)
    {};

    void fim_stop(Garage_ControllerContext& context);
    void stop_fecho(Garage_ControllerContext& context);
};

class Garage_ControllerFSM_Aberta :
    public Garage_ControllerFSM_Default
{
public:
    Garage_ControllerFSM_Aberta(const char *name, int stateId)
    : Garage_ControllerFSM_Default(name, stateId)
    {};

    void fechar(Garage_ControllerContext& context);
};

class Garage_ControllerContext :
    public FSMContext
{
public:

    Garage_ControllerContext(Garage_Controller& owner)
    : _owner(owner)
    {
        setState(Garage_ControllerFSM::Fechada);
        Garage_ControllerFSM::Fechada.Entry(*this);
    };

    Garage_Controller& getOwner() const
    {
        return (_owner);
    };

    Garage_ControllerState& getState() const
    {
        if (_state == NULL)
        {
            throw StateUndefinedException();
        }

        return (dynamic_cast<Garage_ControllerState&>(*_state));
    };

    void BotaoPremido()
    {
        (getState()).BotaoPremido(*this);
    };

    void fechar()
    {
        (getState()).fechar(*this);
    };

    void fim_stop()
    {
        (getState()).fim_stop(*this);
    };

    void stop()
    {
        (getState()).stop(*this);
    };

    void stop_fecho()
    {
        (getState()).stop_fecho(*this);
    };

private:

    Garage_Controller& _owner;
};

#endif
