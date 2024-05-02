
// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 10, d5 = 9, d6 = 8, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int buttonR = 19;
const int buttonP = 20;
const int buttonS = 21;

//miscellaneous variables
int player_1_points = 0;
int player_2_points = 0;
int beginState = 0;
int seed = 0;
int seedState = 0;


void setup() {
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  pinMode(buttonR, INPUT_PULLUP);
  pinMode(buttonP, INPUT_PULLUP);
  pinMode(buttonS, INPUT_PULLUP);
}

void loop() {
  //the introduction to the game, only happens on startup and ignored on loops.
  while (beginState == 0) {
  lcd.print("Welcome to");
  delay(2000);
  lcd.clear();
  lcd.print("rock");
  tone(15, 150, 150);
  delay(150);
  tone(15, 190, 450);
  delay(650);
  lcd.clear();
  lcd.print("paper");
  tone(15, 130, 150);
  delay(150);
  tone(15, 170, 450);
  delay(650);
  lcd.clear();
  lcd.print("scissors");
  tone(15, 110, 150);
  delay(150);
  tone(15, 150, 450);
  delay(2000);
  beginState = 1;
  }
  //this part of the loop pauses the script until a button is pressed
  //it has a secondary function that decides the seed used for the random number generator. Loop within a loop.
  while (digitalRead(buttonR) == HIGH && digitalRead(buttonP) == HIGH && digitalRead(buttonS) == HIGH && seedState == 0) {
    if (seed == 0) {
    lcd.clear();
    lcd.print("press any button");
    lcd.setCursor(0, 1);
    lcd.print("to continue");
    }
    seed = seed + 1;
    delay(20);
    randomSeed(seed);
  }
  seedState = 1;
  lcd.clear();
  delay(500);
  //names player 1 and 2 (human and computer)
  String player_1 = askMove();
  tone(15, 500, 250);
  String player_2 = giveRandom();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(player_1);
  lcd.setCursor(0, 1);
  lcd.print(player_2);
  delay(2200);
  lcd.clear();
  lcd.print(compareMoves(player_1, player_2));
  lcd.setCursor(15, 0);
  lcd.print(player_1_points);
  lcd.setCursor(15, 1);
  lcd.print(player_2_points);
  delay(3000);
  if (player_1_points == 3) {
    lcd.clear();
    lcd.print("Player 1 won!!");
    player_1_points = 0;
    player_2_points = 0;
    delay(4000);
  }
  if (player_2_points == 3) {
    lcd.clear();
    lcd.print("Player 2 won!!");
    player_1_points = 0;
    player_2_points = 0;
    delay(4000);
  }
}

// gives a random number with a fixed seed, so every pattern is the same when booted up
String giveRandom() {
  int number = rand() % 3 + 1;
  String move = "";
  if (number == 1) {
    move = "ROCK";
  }
  else if (number == 2) {
    move = "PAPER";
  }
  else if (number == 3) {
    move = "SCISSORS";
  } 
  return move;
}

//this method asks the player their move
String askMove() {
  lcd.print("Choose your move");
  String move = "";
  int a = 0;
  while (a == 0) {
    if (digitalRead(buttonR) == LOW) {
      move = "ROCK";
      a = 1;
    }
    if (digitalRead(buttonP) == LOW) {
      move = "PAPER";
      a = 1;
    }
    if (digitalRead(buttonS) == LOW) {
      move = "SCISSORS";
      a = 1;
    }
  }
  return move;
      
}

// gets both players moves and determines who won.
String compareMoves(String p1, String p2) {
  if (p1 == "ROCK" && p2 == "PAPER") {
    player_2_points++;
    lose();
    return "Player 2 wins";
  }
  else if (p1 == "ROCK" && p2 == "SCISSORS") {
    player_1_points++;
    win();
    return "Player 1 wins";
  }
  else if (p1 == "ROCK" && p2 == "ROCK") {
    tie();
    return "it's a tie";
  }
  else if (p1 == "PAPER" && p2 == "SCISSORS") {
    lose();
    player_2_points++;
    return "Player 2 wins";
  }
  else if (p1 == "PAPER" && p2 == "ROCK") {
    win();
    player_1_points++;
    return "Player 1 wins";
  }
  else if (p1 == "PAPER" && p2 == "PAPER") {
    tie();
    return "it's tie";
  }
  else if (p1 == "SCISSORS" && p2 == "ROCK") {
    lose();
    player_2_points++;
    return "Player 2 wins";
  }
  else if (p1 == "SCISSORS" && p2 == "PAPER") {
    win();
    player_1_points++;
    return "Player 1 wins";
  }
  else if (p1 == "SCISSORS" && p2 == "SCISSORS") {
    tie();
    return "it's a tie";
  }
  else {
    return "did not work";
  }
}

void win() {
  tone(15, 400, 300);
  delay(350);
  tone(15, 500, 400);
}

void lose() {
  tone(15, 200, 400);
  delay(800);
  tone(15, 120, 600);
}

void tie() {
   tone(15, 100, 200);
   delay(400);
   tone(15, 100, 200);
   delay(400);
   tone(15, 100, 200);
}
 
