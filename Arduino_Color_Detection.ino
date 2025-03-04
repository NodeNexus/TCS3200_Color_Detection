//NodeNexus
//https://github.com/NodeNexus

//#include <LiquidCrystal_I2C.h> Uncomment the library for I2C Display
#include <LiquidCrystal.h>

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

// TCS3200 pins connected to Arduino
#define s0 8
#define s1 9
#define s2 10
#define s3 11
#define out 12

// Variables
int red = 0;
int green = 0;
int blue = 0;

void setup() {
  Serial.begin(9600);
  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(out, INPUT);
  digitalWrite(s0, HIGH);
  digitalWrite(s1, HIGH);
  lcd.begin(16, 2);
  lcd.setCursor(5, 0);
  lcd.print("Arduino");
  lcd.setCursor(1, 1);
  lcd.print("Color Detection");
}

void loop() {
  color();
  Serial.print("R =");
  Serial.print(red, DEC);
  Serial.print(" G = ");
  Serial.print(green, DEC);
  Serial.print(" B = ");
  Serial.print(blue, DEC);
  Serial.print("\t");

  if (red < blue && red < green && red < 25) {
    if (green - blue >= 10 && green - blue <= 25 && green - (2 * red) >= 8) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Detected Color");
      lcd.setCursor(0, 1);
      lcd.print("Color : ");
      lcd.print("Red");
      Serial.println(" - (Red Color)");
    }

    else if (green - red <= 10 && green - red >= -3 && blue >= green) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Detected Color");
      lcd.setCursor(0, 1);
      lcd.print("Color : ");
      lcd.print("Yellow");
      Serial.println(" - (Yellow Color)");
    }

    else if (blue - red >= 3 && blue - red <= 10 && green - (2 * red) <= 5) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Detected Color");
      lcd.setCursor(0, 1);
      lcd.print("Color : ");
      lcd.print("Pink");
      Serial.println(" - (Pink Color)");
    }

    else if (green - blue >= -5 && green - blue <= 5 && green - (2 * red) <= 5) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Detected Color");
      lcd.setCursor(0, 1);
      lcd.print("Color : ");
      lcd.print("Orange");
      Serial.println(" - (Orange Color)");
    }

  }

  else if (green < red && green < blue && green < 25) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Detected Color");
    lcd.setCursor(0, 1);
    lcd.print("Color : ");
    lcd.print("Green");
    Serial.println(" - (Green Color)");
  }

  else if ((red > green && blue < green) && blue < 25 && red > 40) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Detected Color");
    lcd.setCursor(0, 1);
    lcd.print("Color : ");
    lcd.print("Blue");
    Serial.println(" - (Blue Color)");
  }

  else if (red - (2 * blue) >= -2 && red - (2 * blue) <= 5 && green - red < 10) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Detected Color");
    lcd.setCursor(0, 1);
    lcd.print("Color : ");
    lcd.print("Purple");
    Serial.println(" - (Purple Color)");
  } else if (blue < red && blue < green && (blue && red && green) < 25) {

    if (red - green <= 5 && red - green >= 0 && ((green - blue) || (red - blue)) < 5 && blue < 50) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Detected Color");
      lcd.setCursor(0, 1);
      lcd.print("Color : ");
      lcd.print("White");
      Serial.println(" - (White Color)");
    }
  }
  Serial.println();
  delay(300);
}

void color() {
  digitalWrite(s2, LOW);
  digitalWrite(s3, LOW);
  //count OUT, pRed, RED
  red = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
  digitalWrite(s3, HIGH);
  //count OUT, pBLUE, BLUE
  blue = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
  digitalWrite(s2, HIGH);
  //count OUT, pGreen, GREEN
  green = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
}
