#include <IRremote.h>
#include  <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F, 16, 2);

const int IR_RECEIVE_PIN = 5;
int RECEIVED = 0;

int LED_1 = 6;
int LED_2 = 7;
int LED_3 = 8;
int LED_4 = 9;

int LED_1_STATE = 0;
int LED_2_STATE = 0;
int LED_3_STATE = 0;
int LED_4_STATE = 0;

unsigned long LED_1_LAST_BUTTON_TIME = millis();
unsigned long LED_2_LAST_BUTTON_TIME = millis();
unsigned long LED_3_LAST_BUTTON_TIME = millis();
unsigned long LED_4_LAST_BUTTON_TIME = millis();


const int TIME_OUT_DELAY = 120;

void setup()
{
  Serial.begin(9600);
  Serial.println("IR Receive test");
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);
  pinMode(LED_4, OUTPUT);
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print(" Innovator Park");
  lcd.setCursor(0, 1);
  lcd.print("  Quadrant 1.0");
}

void loop()
{
  if (IrReceiver.decode()) {
    RECEIVED = IrReceiver.decodedIRData.command, HEX;
    Serial.println(RECEIVED);

    if (RECEIVED == 77) {
      digitalWrite(LED_1, HIGH);
      LED_1_STATE = 1;
      LED_1_LAST_BUTTON_TIME  = millis();
    }
    else if (RECEIVED == REPEAT &&  LED_1_STATE == 1)
    {
      LED_1_LAST_BUTTON_TIME = millis();
    }

    if (RECEIVED == 84) {
      digitalWrite(LED_2, HIGH);
      LED_2_STATE = 1;
      LED_2_LAST_BUTTON_TIME  = millis();
    }
    else if (RECEIVED == REPEAT &&  LED_2_STATE == 1)
    {
      LED_2_LAST_BUTTON_TIME = millis();
    }

    if (RECEIVED == 22) {
      digitalWrite(LED_3, HIGH);
      LED_3_STATE = 1;
      LED_3_LAST_BUTTON_TIME  = millis();
    }
    else if (RECEIVED == REPEAT &&  LED_3_STATE == 1)
    {
      LED_3_LAST_BUTTON_TIME = millis();
    }

    if (RECEIVED == 76) {
      digitalWrite(LED_4, HIGH);
      LED_4_STATE = 1;
      LED_4_LAST_BUTTON_TIME  = millis();
    }
    else if (RECEIVED == REPEAT &&  LED_4_STATE == 1)
    {
      LED_4_LAST_BUTTON_TIME = millis();
    }

    IrReceiver.resume();
  }

  if ((millis() -  LED_1_LAST_BUTTON_TIME > TIME_OUT_DELAY) &&  LED_1_STATE == 1)
  {
    digitalWrite(LED_1, LOW);
    LED_1_STATE = 0;
  }

  if ((millis() -  LED_2_LAST_BUTTON_TIME > TIME_OUT_DELAY) &&  LED_2_STATE == 1)
  {
    digitalWrite(LED_2, LOW);
    LED_2_STATE = 0;
  }

  if ((millis() -  LED_3_LAST_BUTTON_TIME > TIME_OUT_DELAY) &&  LED_3_STATE == 1)
  {
    digitalWrite(LED_3, LOW);
    LED_3_STATE = 0;
  }

  if ((millis() -  LED_4_LAST_BUTTON_TIME > TIME_OUT_DELAY) &&  LED_4_STATE == 1)
  {
    digitalWrite(LED_4, LOW);
    LED_4_STATE = 0;
  }
}
