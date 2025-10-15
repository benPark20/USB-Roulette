#include <Keyboard.h>
#define R 19
#define G 20
#define B 21
#define BTN 12

int randomNum = 0;
int colorArr[] = {0, 127, 255};
bool hasSpun = false;

void setup() {
  Serial.begin(115200);
  Keyboard.begin();
  pinMode(BTN, INPUT_PULLUP);
  pinMode(R, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(B, OUTPUT);
}

void loop() {
  if (digitalRead(BTN) == LOW && !hasSpun) {
    hasSpun = true;
    randomNum = random(0, 7);
    Serial.print("Spinning... randomNum = ");
    Serial.println(randomNum);

    cycleColors(randomNum);
    stopOnColor(randomNum);
    roulette(randomNum);
  }

  if (digitalRead(BTN) == HIGH && hasSpun) {
    hasSpun = false;
  }
}

void cycleColors(int finalColor) {
  unsigned long delayTime = 20;
  unsigned long maxDelay = 400;
  float slowdownFactor = 1.08;
  int totalSteps = 15 + random(0, 20);

  for (int step = 0; step < totalSteps; step++) {
    analogWrite(R, colorArr[random(0, 3)]);
    analogWrite(G, colorArr[random(0, 3)]);
    analogWrite(B, colorArr[random(0, 3)]);
    delay(delayTime);
    delayTime = min((unsigned long)(delayTime * slowdownFactor), maxDelay);
  }
}

void stopOnColor(int n) {
  int r = 0, g = 0, b = 0;

  switch (n) {
    case 0: r = 255; break;
    case 1: g = 255; break;
    case 2: b = 255; break;
    case 3: r = 255; g = 255; break;
    case 4: g = 255; b = 255; break;
    case 5: r = 255; b = 255; break;
    case 6: r = 255; g = 255; b = 255; break;
  }

  for (int i = 0; i < 2; i++) {
    analogWrite(R, r);
    analogWrite(G, g);
    analogWrite(B, b);
    delay(625);
    analogWrite(R, 0);
    analogWrite(G, 0);
    analogWrite(B, 0);
    delay(250);
  }

  analogWrite(R, r);
  analogWrite(G, g);
  analogWrite(B, b);
}

void roulette(int i) {
  Serial.print("Result: ");
  switch (i) {
    case 0:
      Serial.println("RED");
      //lock screen
      Keyboard.press(KEY_LEFT_GUI);
      Keyboard.press('l');
      delay(100);
      Keyboard.releaseAll();
      break;
    case 1:
      Serial.println("GREEN");
      //notepad
      Keyboard.press(KEY_LEFT_GUI);
      Keyboard.releaseAll();
      Keyboard.print("notepad");
      Keyboard.press(KEY_RETURN);
      Keyboard.releaseAll();
      delay(600);
      Keyboard.print("you just lost the game");
      break;
    case 2:
      Serial.println("BLUE");
      //six seven
      Keyboard.press(KEY_LEFT_GUI);
      Keyboard.releaseAll();
      Keyboard.print("calc");
      Keyboard.press(KEY_RETURN);
      Keyboard.releaseAll();
      Keyboard.print("67*67");
      Keyboard.press(KEY_RETURN);
      Keyboard.releaseAll();
      Keyboard.print("/109.48");
      Keyboard.press(KEY_RETURN);
      Keyboard.releaseAll();
      break;
    case 3:
      Serial.println("YELLOW");
      //putting the "hack" in hack club
      Keyboard.press(KEY_LEFT_GUI);
      Keyboard.releaseAll();
      Keyboard.print("cmd");
      Keyboard.press(KEY_RETURN);
      Keyboard.releaseAll();
      delay(1000);
      Keyboard.print("echo Initializing hacking sequence...");
      Keyboard.write(KEY_RETURN);
      Keyboard.print("ping localhost -t");
      Keyboard.write(KEY_RETURN);
      break;
    case 4:
      Serial.println("CYAN");
      //Switch between windows
      for (int k = 0; k < 5; k++) {
        Keyboard.press(KEY_LEFT_ALT);
        Keyboard.press(KEY_TAB);
        Keyboard.releaseAll();
        delay(300);
        Keyboard.press(KEY_UP_ARROW);
        Keyboard.releaseAll();
        delay(100);
      }
      break;
    case 5:
      Serial.println("MAGENTA");
      //open edge :skull:
      Keyboard.press(KEY_LEFT_GUI);
      Keyboard.releaseAll();
      Keyboard.print("edge");
      Keyboard.press(KEY_RETURN);
      Keyboard.releaseAll();
      delay(500);
      Keyboard.print("microsoft jumpscare");
      Keyboard.press(KEY_RETURN);
      Keyboard.releaseAll();
      break;
    case 6:
      Serial.println("WHITE");
      //screenshot
      Keyboard.press(KEY_LEFT_GUI);
      Keyboard.press(KEY_PRINT_SCREEN);
      delay(100);
      Keyboard.releaseAll();
      break;
  }
}
