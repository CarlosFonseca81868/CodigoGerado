/*********************************/
/* Please do not edit this class */
/* Content change without notify */
/*********************************/

#include "Garage_Controller.h"

void state_Fechada(Garage_Controller *aGarage_Controller) {
  printf("Please select transition:\n");
  printf("1. BotaoPremido\n");
  printf("0. quit\n");
  int choice;
  scanf("%d", &choice);
  switch (choice) {
    case 1:
      aGarage_Controller->BotaoPremido();
      break;
    case 0:
      exit(0);
  }
}

void state_A_Fechar(Garage_Controller *aGarage_Controller) {
  printf("Please select transition:\n");
  printf("1. FimFecho\n");
  printf("2. Obstacle\n");
  printf("0. quit\n");
  int choice;
  scanf("%d", &choice);
  switch (choice) {
    case 1:
      aGarage_Controller->fim_stop();
      break;
    case 2:
      aGarage_Controller->stop_fecho();
      break;
    case 0:
      exit(0);
  }
}

void state_Aberta(Garage_Controller *aGarage_Controller) {
  printf("Please select transition:\n");
  printf("1. BotaoPremido\n");
  printf("0. quit\n");
  int choice;
  scanf("%d", &choice);
  switch (choice) {
    case 1:
      aGarage_Controller->fechar();
      break;
    case 0:
      exit(0);
  }
}

void state_A_Abrir(Garage_Controller *aGarage_Controller) {
  printf("Please select transition:\n");
  printf("1. FimAbertura\n");
  printf("0. quit\n");
  int choice;
  scanf("%d", &choice);
  switch (choice) {
    case 1:
      aGarage_Controller->stop();
      break;
    case 0:
      exit(0);
  }
}

int main(int argc, char **argv) {
  Garage_Controller lGarage_Controller;
  while (true) {
    printf("Current state: %s\n", lGarage_Controller.getContext().getState().getName());
    if (&lGarage_Controller.getContext().getState() == &Garage_ControllerFSM::Fechada) {
      state_Fechada(&lGarage_Controller);
    } else if (&lGarage_Controller.getContext().getState() == &Garage_ControllerFSM::A_Fechar) {
      state_A_Fechar(&lGarage_Controller);
    } else if (&lGarage_Controller.getContext().getState() == &Garage_ControllerFSM::Aberta) {
      state_Aberta(&lGarage_Controller);
    } else if (&lGarage_Controller.getContext().getState() == &Garage_ControllerFSM::A_Abrir) {
      state_A_Abrir(&lGarage_Controller);
    }
  }
}
