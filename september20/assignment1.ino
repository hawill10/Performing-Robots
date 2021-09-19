const int in1Pin = 3;
const int in2Pin = 4;
const int in3Pin = 5;
const int in4Pin = 6;

const int greenLED = 8;
const int redLED = 9;

const int button1 = 11;
const int button2 = 12;

int button1State = 0;
int button2State = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
  pinMode(in3Pin, OUTPUT);
  pinMode(in4Pin, OUTPUT);

  pinMode(greenLED, OUTPUT);
  pinMode(redLED, OUTPUT);

  pinMode(button1, INPUT);
  pinMode(button2, INPUT);

  digitalWrite(in1Pin, LOW);
  digitalWrite(in2Pin, LOW);
  digitalWrite(in3Pin, LOW);
  digitalWrite(in4Pin, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  button1State = digitalRead(button1);
  button2State = digitalRead(button2);

  if (button1State == HIGH) {
    digitalWrite(greenLED, HIGH);
    digitalWrite(redLED, LOW);
    
    analogWrite(in1Pin, 150);
    digitalWrite(in2Pin, LOW);

    analogWrite(in3Pin, 150);
    digitalWrite(in4Pin, LOW);
  } else {
    
    digitalWrite(greenLED, LOW);
    digitalWrite(redLED, HIGH);
    
    digitalWrite(in1Pin, LOW);
    digitalWrite(in2Pin, LOW);
    digitalWrite(in3Pin, LOW);
    digitalWrite(in4Pin, LOW);
  }
}
