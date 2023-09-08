#include "Arduino.h"
#include "BdStepper.h"

BdStepper::BdStepper(int passo, int p1, int p2, int p3, int p4){
	pinMode(p1, OUTPUT);
	pinMode(p2, OUTPUT);
	pinMode(p3, OUTPUT);
	pinMode(p4, OUTPUT);
	
	_passo = passo;
	_p1 = p1;
	_p2 = p2;
	_p3 = p3;
	_p4 = p4;	
	
	if(_passo == MEZZO_PASSO){
		_delayTime = DELAY_MEZZO_PASSO;	
	} else if(_passo == PASSO_PIENO_1_PHASE){
		_delayTime = DELAY_PASSO_PIENO_1_PHASE;
	} else if(_passo == PASSO_PIENO_2_PHASE){
		_delayTime = DELAY_PASSO_PIENO_2_PHASE;
	}
}

void BdStepper::impostaVelocita(int um, double velocita){
	if(um == RAD_SEC){
		if(_passo == MEZZO_PASSO){
			_delayTime = (float)DELAY_MEZZO_PASSO * (RAD_SEC_STD / velocita);
		} else if(_passo == PASSO_PIENO_1_PHASE){
			_delayTime = (float)DELAY_PASSO_PIENO_1_PHASE * (RAD_SEC_STD / velocita);
		} else if(_passo == PASSO_PIENO_2_PHASE){
			_delayTime = (float)DELAY_PASSO_PIENO_2_PHASE * (RAD_SEC_STD / velocita);
		}
	}else if(um == GRADI_SEC){
		if(_passo == MEZZO_PASSO){
			_delayTime = (float)DELAY_MEZZO_PASSO * (GRADI_SEC_STD / velocita);
		} else if(_passo == PASSO_PIENO_1_PHASE){
			_delayTime = (float)DELAY_PASSO_PIENO_1_PHASE * (GRADI_SEC_STD / velocita);
		} else if(_passo == PASSO_PIENO_2_PHASE){
			_delayTime = (float)DELAY_PASSO_PIENO_2_PHASE * (GRADI_SEC_STD / velocita);
		}
	}else if(um == GIRI_MIN){
		if(_passo == MEZZO_PASSO){
			_delayTime = (float)DELAY_MEZZO_PASSO * (GIRI_MIN_STD / velocita);
		} else if(_passo == PASSO_PIENO_1_PHASE){
			_delayTime = (float)DELAY_PASSO_PIENO_1_PHASE * (GIRI_MIN_STD / velocita);
		} else if(_passo == PASSO_PIENO_2_PHASE){
			_delayTime = (float)DELAY_PASSO_PIENO_2_PHASE * (GIRI_MIN_STD / velocita);
		}
	}
}


void BdStepper::ruotaPerGradi(int angolo, int verso){
	int i, nStep;
	if(_passo == MEZZO_PASSO){
		nStep = ((double)STEP_PER_GIRO_HALF)*angolo/ANGOLO_GIRO;
			
		if(verso == SENSO_ORARIO){ //senso orario
			
			for(long int n=0; n<nStep; n++){
				i = n % 8;
				digitalWrite(_p1, (i>=1 && i<=2)?HIGH:LOW);
				digitalWrite(_p2, (i>=2 && i<=4)?HIGH:LOW);
				digitalWrite(_p3, (i>=4 && i<=6)?HIGH:LOW);
				digitalWrite(_p4, (i>=6)?HIGH:LOW);
				delayMicroseconds(_delayTime);
			} 
		} else {
			for(long int n=nStep-1; n>=0; n--){
				i = n % 8;
				digitalWrite(_p1, (i>=1 && i<=2)?HIGH:LOW);
				digitalWrite(_p2, (i>=2 && i<=4)?HIGH:LOW);
				digitalWrite(_p3, (i>=4 && i<=6)?HIGH:LOW);
				digitalWrite(_p4, (i>=6)?HIGH:LOW);
				delayMicroseconds(_delayTime);
			} 
		}
	} else if (_passo == PASSO_PIENO_1_PHASE){
		nStep = ((double)STEP_PER_GIRO_FULL)*angolo/ANGOLO_GIRO;
	
		if(verso == SENSO_ORARIO){ //senso orario
			for(long int n=0; n<nStep; n++){
				i = n % 4;
				digitalWrite(_p1, i==0?HIGH:LOW);
				digitalWrite(_p2, i==1?HIGH:LOW);
				digitalWrite(_p3, i==2?HIGH:LOW);
				digitalWrite(_p4, i==3?HIGH:LOW);
				delayMicroseconds(_delayTime);
			} 
		} else {
			for(long int n=nStep-1; n>=0; n--){
				i = n % 4;
				digitalWrite(_p1, i==0?HIGH:LOW);
				digitalWrite(_p2, i==1?HIGH:LOW);
				digitalWrite(_p3, i==2?HIGH:LOW);
				digitalWrite(_p4, i==3?HIGH:LOW);
				delayMicroseconds(_delayTime);
			} 
		}
	} else if(_passo == PASSO_PIENO_2_PHASE){
		nStep = ((double)STEP_PER_GIRO_FULL)*angolo/ANGOLO_GIRO;
	
		if(verso == SENSO_ORARIO){ //senso orario
			for(long int n=0; n<nStep; n++){
				i = n % 4;
				digitalWrite(_p1, i==3 || i==0?HIGH:LOW);
				digitalWrite(_p2, i==0 || i==1?HIGH:LOW);
				digitalWrite(_p3, i==1 || i==2?HIGH:LOW);
				digitalWrite(_p4, i==2 || i==3?HIGH:LOW);
				delayMicroseconds(_delayTime);
			} 
		} else {
			for(long int n=nStep-1; n>=0; n--){
				i = n % 4;
				digitalWrite(_p1, i==3 || i==0?HIGH:LOW);
				digitalWrite(_p2, i==0 || i==1?HIGH:LOW);
				digitalWrite(_p3, i==1 || i==2?HIGH:LOW);
				digitalWrite(_p4, i==2 || i==3?HIGH:LOW);
				delayMicroseconds(_delayTime);
			} 
		}
	}	
}

void BdStepper::ruotaPerMillisecondi(long durata, int verso){
	long startMills;
	int i;
	
	if(_passo == MEZZO_PASSO){
		if(verso == SENSO_ORARIO){ //senso orario
			i=0;
			startMills = millis();
			while(millis() - startMills <= durata){
				digitalWrite(_p1, (i>=1 && i<=2)?HIGH:LOW);
				digitalWrite(_p2, (i>=2 && i<=4)?HIGH:LOW);
				digitalWrite(_p3, (i>=4 && i<=6)?HIGH:LOW);
				digitalWrite(_p4, (i>=6)?HIGH:LOW);
				delayMicroseconds(_delayTime);
				i = (i+1) % 8;
			}
			return;
		} else {
			i=7;
			startMills = millis();
			while(millis() - startMills <= durata){
				digitalWrite(_p1, (i>=1 && i<=2)?HIGH:LOW);
				digitalWrite(_p2, (i>=2 && i<=4)?HIGH:LOW);
				digitalWrite(_p3, (i>=4 && i<=6)?HIGH:LOW);
				digitalWrite(_p4, (i>=6)?HIGH:LOW);
				delayMicroseconds(_delayTime);
				i = (i+7) % 8;
			} 
			return;
		}
	} else if (_passo == PASSO_PIENO_1_PHASE){
		if(verso == SENSO_ORARIO){ //senso orario
			i=0;
			startMills = millis();
			while(millis() - startMills <= durata){
				
				digitalWrite(_p1, i==0?HIGH:LOW);
				digitalWrite(_p2, i==1?HIGH:LOW);
				digitalWrite(_p3, i==2?HIGH:LOW);
				digitalWrite(_p4, i==3?HIGH:LOW);
				delayMicroseconds(_delayTime);
				i = (i+1)%4;
			} 
			return;
		} else {
			i = 3;
			startMills = millis();
			while(millis() - startMills <= durata){
				digitalWrite(_p1, i==0?HIGH:LOW);
				digitalWrite(_p2, i==1?HIGH:LOW);
				digitalWrite(_p3, i==2?HIGH:LOW);
				digitalWrite(_p4, i==3?HIGH:LOW);
				delayMicroseconds(_delayTime);
				i = (i + 3) % 4;	
			} 
			return;
		}
	} else if(_passo == PASSO_PIENO_2_PHASE){
		if(verso == SENSO_ORARIO){ //senso orario
			i=0;
			startMills = millis();
			while(millis() - startMills <= durata){
				digitalWrite(_p1, i==3 || i==0?HIGH:LOW);
				digitalWrite(_p2, i==0 || i==1?HIGH:LOW);
				digitalWrite(_p3, i==1 || i==2?HIGH:LOW);
				digitalWrite(_p4, i==2 || i==3?HIGH:LOW);
				delayMicroseconds(_delayTime);
				i = (i+1)%4;
			} 
			return;
		} else {
			i = 3;
			startMills = millis();
			while(millis() - startMills <= durata){
				digitalWrite(_p1, i==3 || i==0?HIGH:LOW);
				digitalWrite(_p2, i==0 || i==1?HIGH:LOW);
				digitalWrite(_p3, i==1 || i==2?HIGH:LOW);
				digitalWrite(_p4, i==2 || i==3?HIGH:LOW);
				delayMicroseconds(_delayTime);
				i = (i + 3) % 4;
			} 
			return;
		}
	}	
}


