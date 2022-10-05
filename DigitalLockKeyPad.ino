#include <Keypad.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>
#define UNLOCK_POS 1
#define LOCK_POS 100
LiquidCrystal_I2C lcd(0x27 ,16, 2);
Servo myservo;
int buzzer = 13;
char fctpass[7];
char fpassword[] = {42, 48, 48, 42};
char password[4];
char initial_password[4], new_password[4];
int i = 0;
char key_pressed = 0; 
bool changepass = 0;  
bool factory = 0;
const byte rows = 4;
const byte columns = 4;
char hexaKeys[rows][columns] = {
{'1', '2', '3', 'A'}, 
{'4', '5', '6', 'B'}, 
{'7', '8', '9', 'C'}, 
{'*', '0', '#', 'D'}
};
byte row_pins[rows] = {9, 8, 7, 6};
byte column_pins[columns] = {5, 4, 3, 2};
Keypad keypad_key = Keypad( makeKeymap(hexaKeys), row_pins, column_pins, rows, columns); 

void setup() {
  Serial.begin(9600);
  myservo.attach(12);
  pinMode(buzzer, OUTPUT);
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print(" Welcome Back!! ");
  lcd.setCursor(0, 1);
  lcd.print(" To My Home -,- ");
  delay(5000);
  lcd.clear();
  lcd.print(" Enter Passcode ");
  lcd.setCursor(0, 1);
  changepass = EEPROM.read(10);
    if (changepass == 1) {
    for (int j = 0; j < 4; j++) 
    initial_password[j] = EEPROM.read(j); 
    }else{ 
      initialpassword(); 
      factoryWrite(); 
   }
  factoryRead();
}

void loop() {
  lock();
  key_pressed = keypad_key.getKey();
  if (key_pressed == '#')
    change();
  if (factory == 1)
    changefct();
  if (key_pressed) {
    password[i++] = key_pressed;
    lcd.setCursor(i, 1);
    lcd.print("*");
  }
  if (factory == 0) {
    if (i == 4) {
      delay(200);
      for (int j = 0; j < 4; j++)
        initial_password[j] = EEPROM.read(j);
      if (!(strncmp(password, initial_password, 4)))
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(" !!BingO!! ");
        lcd.setCursor(0, 1);
        lcd.print("Come Back Again");
        unlock();
        delay(5000);
        lcd.setCursor(0, 0);
        lcd.print("How Change Pass#");
        delay(2000);
        lcd.clear();
        lcd.print(" Enter Passcode ");
        lcd.setCursor(0, 1);
        i = 0;
      }else{
        if (!(strncmp(password, fpassword, 4))) {
          factory = 1;
        }
        lock();
        lcd.clear();
        lcd.print("  -|I_Fly|- ");
        lcd.setCursor(0, 3);
        lcd.print("How Change Pass#");
        delay(2000);
        lcd.clear();
        lcd.print(" Enter Passcode ");
        lcd.setCursor(0, 1);
        i = 0;
      }
    }
  }
}

void changefct() {
  int j = 0;
  lcd.clear();
  lcd.print(" #Pai Ty Sa!! @ ");
  lcd.setCursor(0, 1);
  while (j < 7) {
    char key = keypad_key.getKey();
    if (key) {
      new_password[j++] = key;
      lcd.print("*");
    }
    key = 0;
  }
  delay(500);
  if ((strncmp(new_password, fctpass, 7))) {
    lcd.clear();
    lcd.print("  -|I_Fly|- ");
    lcd.setCursor(0, 1);
    lcd.print(" Change by 00");
    delay(2000);
  }else {
    j = 0;
    lcd.clear();
    lcd.print(" New Passcode : ");
    lcd.setCursor(0, 1);
    while (j < 4) {
      char key = keypad_key.getKey();
      if (key) {
        initial_password[j] = key;
        lcd.print("*");
        EEPROM.write(j, key);
        j++;
      }
    }
    changepass = 1;
    EEPROM.write(10, changepass);
    lcd.print("Pass Aledy Chang");
    delay(1000);
  }
  lcd.clear();
  lcd.print(" Enter Passcord ");
  lcd.setCursor(0, 1);
  key_pressed = 0;
  factory = 0;
}

void change() {
  int j = 0;
  lcd.clear();
  lcd.print("Active--Passcord");
  lcd.setCursor(0, 1);
  while (j < 4) {
    char key = keypad_key.getKey();
    if (key) {
      new_password[j++] = key;
      lcd.print("*");
    }
    key = 0;
  }
  delay(500);
  if ((strncmp(new_password, initial_password, 4))) {
    lcd.clear();
    lcd.print(" #Pai Ty Sa!! @ ");
    lcd.setCursor(0, 3);
    lcd.print("How Change Pass#");
    delay(2000);
  }else {
    j = 0;
    lcd.clear();
    lcd.print(" New Passcoed : ");
    lcd.setCursor(0, 1);
    while (j < 4)    {
      char key = keypad_key.getKey();
      if (key) {
        initial_password[j] = key;
        lcd.print("*");
        EEPROM.write(j, key);
        j++;
      }
    }
    changepass = 1;
    EEPROM.write(10, changepass);
    lcd.print("Pass Aledy Chang");
    delay(1000);
  }
  lcd.clear();
  lcd.print(" Enter Passcord ");
  lcd.setCursor(0, 1);
  key_pressed = 0;
}

void initialpassword() {
  for (int j = 0; j < 4; j++)
    EEPROM.write(j, j + 49);
  for (int j = 0; j < 4; j++)
    initial_password[j] = EEPROM.read(j);
}

void factoryWrite() {
  EEPROM.write(20, 48);
  EEPROM.write(21, 48);
  EEPROM.write(22, 48);
  EEPROM.write(23, 65);
  EEPROM.write(24, 66);
  EEPROM.write(25, 67);
  EEPROM.write(26, 68);
}

void factoryRead() {
  fctpass[0] = EEPROM.read(20);
  fctpass[1] = EEPROM.read(21);
  fctpass[2] = EEPROM.read(22);
  fctpass[3] = EEPROM.read(23);
  fctpass[4] = EEPROM.read(24);
  fctpass[5] = EEPROM.read(25);
  fctpass[6] = EEPROM.read(26);
}

void lock() {
  myservo.write(LOCK_POS);
}

void unlock() {
  myservo.write(UNLOCK_POS);
}
