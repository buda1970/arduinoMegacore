int option = 0;
u8 sentido = 0;
 
void setup(){
  Serial.begin(9600);

}
 
void loop(){

  if(option > 100 && sentido == 0){
    sentido = 0xff;
  }
  if(option == 0 && sentido == 0xff){
    sentido = 0;
  }
  
  if(sentido){
    option--;
  }
  else{
    option++;
  }

  Serial.println(option);
  delay(100);
}

