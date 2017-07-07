int sequence[100];
int currentLength = 0;
int inputCount = 0;
int lastInput = 0;
int expectedRead = 0;
bool buttonPressed = false;
bool waiting = false;
bool resetFlag = false;

void setup() {
  Serial.begin(115200);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  Reset();
}

void Reset(){
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  Serial.println("Reset");
  for(int i = 0; i < 10; i++){
    digitalWrite(5, HIGH);
    digitalWrite(6, HIGH);
    delay(250);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    delay(250);
  }
  currentLength = 0;
  inputCount = 0;
  lastInput = 0;
  expectedRead = 0;
  buttonPressed = false;
  waiting = false;
  resetFlag = false;
}

void loop() {
  if(!waiting){
    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);
    sequence[currentLength] = random(5,7);
    currentLength++;
    for(int i = 0; i < currentLength; i++){
      Serial.println(sequence[i]);
      digitalWrite(sequence[i], HIGH);
      delay(500);
      digitalWrite(sequence[i], LOW);
      delay(250);
    }    
    waiting = true;
  }else{
    pinMode(5, INPUT);
    pinMode(6, INPUT);
    if(!buttonPressed){
      expectedRead = sequence[inputCount];
      Serial.print("Expected ");
      Serial.println(expectedRead);
      for(int i = 5; i <= 6; i++){
        if(i==expectedRead)
          continue;
        if(digitalRead(i) == 1){
          Serial.print("Read ");
          Serial.println(i);
          lastInput = i;
          resetFlag = true;
          buttonPressed = true;
        }
      }
    }
    if(digitalRead(expectedRead) == 1 && !buttonPressed)
    {
      Serial.print("Read ");
      Serial.println(expectedRead);
      lastInput = expectedRead;
      inputCount++;
      buttonPressed = true;
    }else{
      if(buttonPressed && digitalRead(lastInput) == 0){
        buttonPressed = false;
        if(resetFlag)
          Reset();
        else{
          if(inputCount == currentLength){
            waiting = false;
            inputCount = 0;   
            delay(2000);
          }
        }
      }
    }
    
  }

}
