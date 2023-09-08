int pos, dir;

void setup() {

  pinMode(3, OUTPUT);

  pos=150;
  dir=1;

}

void loop() {
  analogWrite(3, pos);

  if(dir==1){
    pos+=1;
    if(pos>240){
      dir=0;
    }
  }

  else{
    pos-=1;
    if(pos<80){
      dir=1;
    }
  }

  delay(10);
}
