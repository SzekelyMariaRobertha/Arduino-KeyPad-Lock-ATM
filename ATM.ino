#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
#define PasswordLength 5 // cifre necesare pt pin (4) + caracter null (1)

// definire pini pentru butoanele externe
#define k1 A1
#define k2 A2
#define k3 A3
#define k4 A4

const byte ROWS = 4; 
const byte COLS = 4; 
char keys[ROWS][COLS] = {
    {'1','2','3','A'},
    {'4','5','6','B'},
    {'7','8','9','C'},
    {'*','0','#','D'}
};

byte rowPins[ROWS] = {5, 4, 3, 2}; // conectez randurile la pini
byte colPins[COLS] = {9, 8, 7, 6}; // conectez coloanele la pini

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS );
LiquidCrystal_I2C lcd(0x27, 16, 2);

String lng = "";

char inputPassword[PasswordLength]; // aici retin ce se introduce
char correctPassword[PasswordLength] = "1379"; // aici retin parola corecta
int cnt = 0; // ca sa verific de cate ori s-a apasat pe keypad

const int numOfItems = 5;
int currItem = 0;
String menuitemsEn[numOfItems] = {"1. View Balance", "2. Add Money", "3. Get Money", "4. Cancel", "5. Exchange"};
String menuitemsRo[numOfItems] = {"1. Interogare", "2. Depunere", "3. Retragere", "4. Anulare", "5. Curs Valutar"};

float balance = 1000;
char inMoney[4];
char outMoney[4];
int inMoneyy = 0;
int outMoneyy = 0;
int cntMoney = 0;
int ok = 0;

char cursValutar[4];
float USD = 4.58;
float EUR = 4.96;
float cursValutarDouble;

void setup(){
    Serial.begin(9600);
    pinMode(k1, INPUT_PULLUP);
    pinMode(k2, INPUT_PULLUP);
    pinMode(k3, INPUT_PULLUP);
    pinMode(k4, INPUT_PULLUP);

    lcd.init();
    lcd.backlight();
    lcd.setCursor(6, 0);
    lcd.print("ATM");
    lcd.setCursor(4, 1);
    lcd.print("Welcome!");
    delay(3000);
}

void loop() 
{
    if (ok == 0) {
        language();
        password();
    } else {
        menu();
    }
}

void language()
{ 
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Choose language");
    delay(1000);
    lcd.setCursor(9, 1);
    lcd.print("wait...");
    delay(3000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("[A] English");
    lcd.setCursor(0, 1);
    lcd.print("[B] Romanian");
    char key = keypad.waitForKey();
    if (key) {
        switch (key)
        {
          case 'A':
            lng = "English";
            break;

          case 'B':
            lng = "Romanian";
            break;
        }
    }
}

void password() 
{
  if (lng == "English") {
      lcd.clear();
      lcd.setCursor(1, 0);
      lcd.print("Type password:");
  } else {
      lcd.clear();
      lcd.setCursor(1, 0);
      lcd.print("Introdu pinul:");
  }

  char key;
  cnt = 0;
  while (cnt < 5) { // cnt merge doar pana la 4 = dimensiunea parolei
      if (cnt == 4) {
        key = keypad.waitForKey(); // aici verific daca s au introdus mai mult de 4 cifre
        break;
      } else {
        key = keypad.waitForKey();
        if (key != NO_KEY && key != 'A' && key != 'B' && key != 'C' && key != 'D' && key != '*' && key != '#') { // verific daca sunt apasari doar in zona de cifre
            inputPassword[cnt] = key; // adaug datele introduse in variabila aleasa
            lcd.setCursor(cnt + 6, 1); // am adaugat 6 ca sa centrez parola doar
            lcd.print("*"); // afisez stelute in loc de cifre
            cnt++;
        } else if (key == 'C' or key == 'D') { // C e pentru Clear si D pentru Enter
            break;
        }
      }
  }

  if (key == 'D') {
        checkPassword();
  } else if (key == 'C') { // C e pentru clear
        // sterg a doua linie de pe lcd
        lcd.setCursor(0, 1); 
        for (int i = 0; i < 16; i++){
          lcd.print(" ");
        }
        clearPassword();
        password(); // daca nu l as intoarce in password(), ar merge in loop si ar astepta key din fct de language
  }  else {
      if (lng == "English") {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("PIN too long");  
            delay(2000);      
        } else {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("PIN prea lung");  
            delay(2000); 
        } 
        password();
  }

}

void checkPassword () 
{
    lcd.clear();
    lcd.setCursor(0,0);

    if (strcmp(inputPassword, correctPassword) == 0) { // cazul in care parolele corespund
        lcd.setCursor(0, 0);
        if (lng == "English") {
            lcd.print("Correct PIN");        
        } else {
            lcd.print("PIN corect");
        } 

        delay(2000);
        lcd.clear();
        clearPassword();
        ok = 1;
        return;
        
    } else { // cazul in care parolele nu corespund
        lcd.setCursor(0, 0);
        if (lng == "English") {
            lcd.print("Incorrect PIN");
        } else {
            lcd.print("PIN gresit");
        }
        delay(2000);
        lcd.clear();
        clearPassword();
        password();
    }
}

void clearPassword() { // cu aceasta functie sterg datele introduse de utilizator
      while (cnt != 0) {
          cnt--;
          inputPassword[cnt] = "";
      }
}

void clearInMoney() { // cu aceasta functie sterg datele introduse de utilizator
      while (cntMoney != 0) {
          cntMoney--;
          inMoney[cntMoney] = "";
      }
}

void clearOutMoney() { // cu aceasta functie sterg datele introduse de utilizator
      while (cntMoney != 0) {
          cntMoney--;
          outMoney[cntMoney] = "";
      }
}

void menu() {
    if (lng == "English") {
        lcd.print(menuitemsEn[currItem]);
    } else {
        lcd.print(menuitemsRo[currItem]);
    }
   
    char key = keypad.waitForKey();
    if (key) {
        switch (key)
        {
          case '*': // back
            if (currItem == 0) {
              currItem = numOfItems - 1;
            } else {
              currItem--;
            }
            break;

          case '#': // forward
            if (currItem == numOfItems - 1) {
              currItem = 0;
            } else {
              currItem++;
            }
            break;

          case 'D': // Enter
            if (currItem == 0) {
                viewBalance();
            } else if (currItem == 1) {
                addMoney();
            } else if (currItem == 2) {
                getMoney();
            } else if (currItem == 3) {
                ccc();
            } else {
                exchange();
            }
         }
    }
    lcd.clear();
    lcd.setCursor(0, 0);
}

void viewBalance () {
  if (lng == "English") {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Balance: ");
      lcd.print(balance);
      delay(3000);
  } else {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Sold: ");
      lcd.print(balance);
      delay(3000);
  }
}

void addMoney() {
  if (lng == "English") {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("How much?");
      lcd.setCursor(1, 0);
  } else {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Ce suma?");
      lcd.setCursor(1, 0);
  }

  char key;
  while (cntMoney < 5) { // poate introduce maxim 4 cifre
      key = keypad.waitForKey();
      if (key != NO_KEY && key != 'A' && key != 'B' && key != 'C' && key != 'D' && key != '*' && key != '#') { // verific daca sunt apasari doarin zona de cifre
          inMoney[cntMoney] = key; // adaug datele introduse in variabila aleasa
          lcd.setCursor(cntMoney, 1); 
          lcd.print(key); 
          cntMoney++; 
      } else if (key == 'D' or key == 'C') {
        break;
      } 
  }

  if (key == 'D') {
    inMoneyy = atoi(inMoney); // transform din string in valoare intreaga
    balance = balance + inMoneyy;
    clearInMoney();
    
    if (lng == "English") {
        lcd.clear();
        lcd.setCursor(5, 0);
        lcd.print("Added");
        lcd.setCursor(2, 1);
        lcd.print("successfully");
        delay(3000);
    } else {
        lcd.clear();
        lcd.setCursor(4, 0);
        lcd.print("Adaugati");
        lcd.setCursor(4, 1);
        lcd.print("cu succes");
        delay(3000);
    }
  } else if (key == 'C') {
        lcd.setCursor(0, 1);
        for (int i = 0; i < 16; i++){
          lcd.print(" ");
        }
        clearInMoney();
        addMoney(); 
  } else {
    lcd.clear(); // cazul in care depaseste 4 cifre
    lcd.setCursor(0, 0);
    clearInMoney();
    if (lng == "English"){
      lcd.print("Not added");
      lcd.setCursor(0, 1);
      lcd.print("Too much money");
      delay(3000);
      addMoney();
    } else {
      lcd.print("Nu s-au adaugat");
      lcd.setCursor(0, 1);
      lcd.print("Suma prea mare");
      delay(3000);
      addMoney();
    }
  }
}

void getMoney() {
  if (lng == "English") {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("How much?");
      lcd.setCursor(1, 0);
  } else {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Ce suma?");
      lcd.setCursor(1, 0);
  }

  char key;
  while (cntMoney < 5) { // maxim 4 cifre
      key = keypad.waitForKey();
      if (key != NO_KEY && key != 'A' && key != 'B' && key != 'C' && key != 'D' && key != '*' && key != '#') { // verific daca sunt apasari doa rin zona de cifre
          outMoney[cntMoney] = key; // adaug datele introduse in variabila aleasa
          lcd.setCursor(cntMoney, 1); 
          lcd.print(key); 
          cntMoney++;
      } else if (key == 'D' or key == 'C') {
        break;
      } 
  }

  if (key == 'D') {
    outMoneyy = atoi(outMoney);
    clearOutMoney();
    if (outMoneyy > balance) { // valoare introdusa de utilizator este mai mare decat valoare din cont
        outMoneyy = 0;
        if (lng == "English") {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("You don't have");
            lcd.setCursor(0, 1);
            lcd.print("that much money");
            delay(3000);
        } else {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Nu aveti atatia");
            lcd.setCursor(0, 1);
            lcd.print("bani in cont");
            delay(3000);
        }
        return;
    } else { // valoare introdusa este mai mica sau egala cu valoarea din cont
          balance = balance - outMoneyy;
          if (lng == "English") {
              lcd.clear();
              lcd.setCursor(5, 0);
              lcd.print("Money");
              lcd.setCursor(3, 1);
              lcd.print("withdrawn");
              delay(3000);
          } else {
              lcd.clear();
              lcd.setCursor(2, 0);
              lcd.print("Bani retrasi");
              delay(3000);
          }
    }
  } else if (key == 'C') {
        lcd.setCursor(0, 1); // sterg a doua linie de pe lcd
        for (int i = 0; i < 16; i++){
          lcd.print(" ");
        }
        clearOutMoney();
        outMoneyy = 0;
        getMoney(); 
  } else { // cazul in care depaseste 4 cifre
    lcd.clear();
    lcd.setCursor(0, 0);
    clearOutMoney();
    outMoneyy = 0;
    if (lng == "English"){
      lcd.print("Not permited");
      lcd.setCursor(0, 1);
      lcd.print("Too much money");
      delay(3000);
    } else {
      lcd.print("Actiune nepermisa");
      lcd.setCursor(0, 1);
      lcd.print("Suma prea mare");
      delay(3000);
    }
    return;
  }
}

void ccc() { // functia de cancel care ma intoarce in alegerea limbii si ma pozitioneaza din nou pe prima optiune din meniu
        currItem = 0;
        ok = 0;
}

void exchange() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("[K1] USD - ");
  lcd.print(USD);
  lcd.setCursor(0, 1);
  lcd.print("[K2] EUR - ");
  lcd.print(EUR);
  readButtons();
}

void readButtons() {
    while (1) {
        if (digitalRead(k1) == 0) {
            dtostrf(USD, 4, 2, cursValutar); // pune in cursValutar, valoare lui USD ca strign ca sa poata fi afisat
            cursValutarDouble = USD;
                 
            Serial.print(outMoneyy);

            if (outMoneyy <= balance) { // exclud cazurile in care introduce valoarea care are prea multe cifre sau nu exista suficienti bani in cont
                getMoney();
                lcd.clear();
                lcd.setCursor(0, 0);
                if (lng == "Romanian") {
                    lcd.print("Suma retrasa");
                    lcd.setCursor(0, 1);
                    lcd.print(outMoneyy / cursValutarDouble);
                    lcd.setCursor(6, 1);
                    lcd.print("USD");
                } else {
                    lcd.print("Value withdrawn:");
                  lcd.setCursor(0, 1);
                  lcd.print(outMoneyy / cursValutarDouble);
                  lcd.setCursor(6, 1);
                  lcd.print("USD");
                }
                
                delay(3000);
            }
            break;
        } else if (digitalRead(k2) == 0) {
          dtostrf(EUR, 4, 2, cursValutar);
          cursValutarDouble = EUR;
          

          Serial.print(outMoneyy);

          if (outMoneyy <= balance) {
              getMoney();
              lcd.clear();
              lcd.setCursor(0, 0);
              if (lng == "Romanian") {
                    lcd.print("Suma retrasa:");
                    lcd.setCursor(0, 1);
                    lcd.print(outMoneyy / cursValutarDouble);
                    lcd.setCursor(6, 1);
                    lcd.print("USD");
                } else {
                    lcd.print("Value withdrawn:");
                    lcd.setCursor(0, 1);
                    lcd.print(outMoneyy / cursValutarDouble);
                    lcd.setCursor(6, 1);
                    lcd.print("USD");
                }
              delay(3000);
          }
          break;
        } else if (digitalRead(k3) == 0) {
          Serial.println("K3");
          delay(100);
          break;
        } else if (digitalRead(k4) == 0) {
          Serial.println("K4");
          delay(100);
          break;
        }
    }
}