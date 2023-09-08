//--------------------------------------------------------------------------------
//codice per muovere motore passo passo per millisecondi con un senso orario
/*
#include "BdStepper.h" //libreria del prof
BdStepper motore(MEZZO_PASSO, 8,9,10,11); //classe per gestire i pin di entrata del motore
void setup() {
  }
void loop() {
  motore.ruotaPerMillisecondi(2000, SENSO_ORARIO); //2000 = millisecondi/SENSO_ORARIO = senso di rotazione
  delay(10);
  }
*/
//---------------------------------------------------------------------------------

//---------------------------------------------------------------------------------
//codice per muovere motore passo passo per gradi in senso orario full_step 1 fase
/*
#include "BdStepper.h" //libreria del prof
BdStepper motore(PASSO_PIENO_1_PHASE, 8,9,10,11); //classe per gestire i pin di entrata del motore
void setup() {
  }
void loop() {
  motore.ruotaPerGradi(90, SENSO_ORARIO); //90 = gradi/SENSO_ORARIO = senso di rotazione
  delay(10);
  }
*/
//---------------------------------------------------------------------------------


//---------------------------------------------------------------------------------
//codice per muovere motore passo passo per gradi in senso orario full_step 2 fase
/*
#include "BdStepper.h" //libreria del prof
BdStepper motore(PASSO_PIENO_2_PHASE, 8,9,10,11); //classe per gestire i pin di entrata del motore
void setup() {
  }
void loop() {
  motore.ruotaPerGradi(180, SENSO_ORARIO); //180 = gradi/SENSO_ORARIO = senso di rotazione
  delay(10);
  }
*/
//---------------------------------------------------------------------------------


//---------------------------------------------------------------------------------
//codice per muovere motore passo passo per gradi in senso orario HALF STEP
/*
#include "BdStepper.h" //libreria del prof
BdStepper motore(MEZZO PASSO, 8,9,10,11); //classe per gestire i pin di entrata del motore
void setup() {
  }
void loop() {
  motore.ruotaPerGradi(5, SENSO_ORARIO); //5 = gradi/SENSO_ORARIO = senso di rotazione
  delay(10);
  }
*/
//---------------------------------------------------------------------------------