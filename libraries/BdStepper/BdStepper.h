/*
    BdStepper.h - Libreria per comandare un motore passo-passo
    28BYJ-48 attraverso il driver ULN2003.
    Creato da Andrea Bidinost, 16 Novembre 2019.

    Rilasciato solo per utilizzo privato.
*/

#include "Arduino.h"
#ifndef BdStepper_h
#define BdStepper_h

#define STEP_PER_GIRO_HALF 4096
#define STEP_PER_GIRO_FULL 2048

#define ANGOLO_GIRO 360

#define SENSO_ORARIO 1
#define SENSO_ANTI_ORARIO -1

#define MEZZO_PASSO 0
#define PASSO_PIENO_1_PHASE 1
#define PASSO_PIENO_2_PHASE 2

#define DELAY_MEZZO_PASSO 1000
#define DELAY_PASSO_PIENO_1_PHASE 2019
#define DELAY_PASSO_PIENO_2_PHASE 2018

#define RAD_SEC 1
#define GRADI_SEC 2
#define GIRI_MIN 3

#define RAD_SEC_STD 1.496
#define GRADI_SEC_STD 85.71
#define GIRI_MIN_STD 14.28

class BdStepper{
	public:
		BdStepper(int passo, int p1, int p2, int p3, int p4);
		void ruotaPerGradi(int angolo, int verso);
		void ruotaPerMillisecondi(long durata, int verso);
		void impostaVelocita(int um, double velocita);
	private:
		int _passo, _p1, _p2, _p3, _p4;
		int _delayTime;
};

#endif
