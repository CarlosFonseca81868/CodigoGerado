#include "Garage_Controller_sm.h"

#include "Garage_Controller.h"

// Static class declarations.
Garage_ControllerFSM_Fechada Garage_ControllerFSM::Fechada("Garage_ControllerFSM::Fechada", 0);
Garage_ControllerFSM_A_Abrir Garage_ControllerFSM::A_Abrir("Garage_ControllerFSM::A_Abrir", 1);
Garage_ControllerFSM_A_Fechar Garage_ControllerFSM::A_Fechar("Garage_ControllerFSM::A_Fechar", 2);
Garage_ControllerFSM_Aberta Garage_ControllerFSM::Aberta("Garage_ControllerFSM::Aberta", 3);

void Garage_ControllerState::BotaoPremido(Garage_ControllerContext& context) {
  Default(context);
  return;
}

void Garage_ControllerState::fechar(Garage_ControllerContext& context) {
  Default(context);
  return;
}

void Garage_ControllerState::fim_stop(Garage_ControllerContext& context) {
  Default(context);
  return;
}

void Garage_ControllerState::stop(Garage_ControllerContext& context) {
  Default(context);
  return;
}

void Garage_ControllerState::stop_fecho(Garage_ControllerContext& context) {
  Default(context);
  return;
}

void Garage_ControllerState::Default(Garage_ControllerContext& context) {
  throw(
      TransitionUndefinedException(
          context.getState().getName(),
          context.getTransition()));

  return;
}

void Garage_ControllerFSM_Fechada::BotaoPremido(Garage_ControllerContext& context) {
  (context.getState()).Exit(context);
  context.setState(Garage_ControllerFSM::A_Abrir);
  (context.getState()).Entry(context);

  return;
}

void Garage_ControllerFSM_A_Abrir::stop(Garage_ControllerContext& context) {
  (context.getState()).Exit(context);
  context.setState(Garage_ControllerFSM::Aberta);
  (context.getState()).Entry(context);

  return;
}

void Garage_ControllerFSM_A_Fechar::fim_stop(Garage_ControllerContext& context) {
  (context.getState()).Exit(context);
  context.setState(Garage_ControllerFSM::Fechada);
  (context.getState()).Entry(context);

  return;
}

void Garage_ControllerFSM_A_Fechar::stop_fecho(Garage_ControllerContext& context) {
  (context.getState()).Exit(context);
  context.setState(Garage_ControllerFSM::A_Abrir);
  (context.getState()).Entry(context);

  return;
}

void Garage_ControllerFSM_Aberta::fechar(Garage_ControllerContext& context) {
  if (true) {
    (context.getState()).Exit(context);
    // No actions.
    context.setState(Garage_ControllerFSM::A_Fechar);
    (context.getState()).Entry(context);
  } else {
    Garage_ControllerFSM_Default::fechar(context);
  }

  return;
}
