int ledPin = 0; // мигающий СД  
int releyPin = 1; // пин реле
int switchPin = 2; // кнопка

int value; // переменная для состояния чамигасты ния СД
int state; // переменная хранения состояния кнопки - нажали \ отпустили
int val; // переменная анения для храненря состояния кнопки 
int c;  // счетчик нажатия

#define TIME0 1800000   // время простоя реле 30 мин
#define TIME1 300000    // время работы при 1 нажатии 5 мин
#define TIME2 600000    // время работы при 2-ъ нажатиях 10 мин

//#define TIME0 6000    // время простоя реле 30 мин
//#define TIME1 2000    // время работы при 1 нажатии 5 мин
//#define TIME2 4000    // время работы при 2-ъ нажатиях 10 мин

unsigned long int time; // переменная для работы таймера и мигания СД
long previousMillis = 0;  // переменная для работы таймера и мигания СД

void setup()
{
  pinMode(ledPin, OUTPUT);
  pinMode(releyPin, OUTPUT);
  pinMode(switchPin, INPUT);
  digitalWrite(ledPin, HIGH);
  digitalWrite(releyPin, HIGH);
}

void loop()
{
  state = digitalRead(switchPin);

  if (state == HIGH && c == 0) // нажали кнопку
  {
    c = 1;
  }
  if (state == LOW && c == 1) // отпустили кнопку
  {
    val = ++val;
    if (val == 4)
    {
      val = 0;
    }
    c = 0;
     time = millis(); // обнуляем счетчик
  }

  if (val == 0) // Состояние включенного. После простоя реле выключаеться
  {
    digitalWrite(ledPin, HIGH);
    digitalWrite(releyPin, HIGH);
    if (millis() - time > TIME0)
    { val = 3; c = 0; }
  }
  if (val == 1) // Состояние кнопки 1, время ее работы 
  {
    prog (350); // вызов программы управления выводами, реле, СД; параметр - частота моргания СД
    if (millis() - time > TIME2)
    { val = 3; c = 0; }
  }
  
  if (val == 2) // Состояние кнопки 1, время ее работы 
  {
    prog (150); // вызов программы управления выводами, реле, СД; параметр - частота моргания СД    
    if (millis() - time > TIME2)
    { val = 3; c = 0; }
  }

if (val == 3) // выключенное состояние
  {
  digitalWrite(ledPin, LOW);
  digitalWrite(releyPin, LOW);
  }
   delay(10);
}


void prog (int blinktime) // программа управления выводами, реле и СД; параметр - частота моргания СД
{
    digitalWrite(releyPin, HIGH); // включаем реле
    if (millis() - previousMillis > blinktime) {
    previousMillis = millis();   // запоминаем текущее время
    if (value == LOW){     // если светодиод был выключен – включаем и наоборот :)
      value = HIGH;
    }else{
      value = LOW;
    }  
      digitalWrite(ledPin, value);
  } 
}

