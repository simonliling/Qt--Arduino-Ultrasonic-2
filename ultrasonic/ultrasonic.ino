const int trigPin = 9;
const int echoPin = 10;
const int ledPin  = 8;
long duration;
int cm, dataled = 0;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);
  duration = pulseIn(echoPin, HIGH);
  cm = duration * 0.034/2;
  
  if(cm <= 5){
    digitalWrite(ledPin, HIGH);
    dataled = 1;
  }

  if(cm >= 10){
    digitalWrite(ledPin, LOW);
    dataled = 0;
  }
  
  if(Serial.available()) {
    int x = Serial.read();
    if(x == '0'){
      digitalWrite(ledPin, LOW);
      dataled = 0;
    }    
  }
  
  Serial.print("data1:");
  Serial.print(cm);
  Serial.print(", ");
  Serial.print("data2:");
  Serial.print(dataled);
  Serial.print(", ");
  Serial.flush();
  delay(100);
}
