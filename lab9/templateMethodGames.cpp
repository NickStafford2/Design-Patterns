// Project:     Template Method Games
// Author:      Nicholas Stafford
//               - based on code originally from Mikhail Nesterenko
// Class:       CS3
// Due:         4/5/18
// Description: Games, Template Method example

#include <ctime>
#include <cstdlib>
#include <iostream>
#include <string>
#include <algorithm>

using std::cout; 
using std::endl;
using std::cin;
using std::string;

// template for any game where players take turns to make moves
// and there is a winner
class Game {
public:
  Game() :playersCount_(0), movesCount_(0), playerWon_(noWinner) {}

  // template method
  void playGame(const int playersCount = 0) {
    playersCount_ = playersCount;
    movesCount_ = 0;

    initializeGame();

    for (int i = 0; !endOfGame(); i = (i + 1) % playersCount_) {
      makeMove(i);
      if (i == playersCount_ - 1)
        ++movesCount_;
    }

    printWinner();
  }

  virtual ~Game() {}

protected:
  // primitive operations
  virtual void initializeGame() = 0;
  virtual void makeMove(int player) = 0;
  virtual void printWinner() = 0;
  virtual bool endOfGame() {
    return playerWon_ != noWinner;
  } // this is a hook
    // returns true if winner is decided
  static const int noWinner = -1;

  int playersCount_;
  int movesCount_;
  int playerWon_;
};

// Monopoly - a concrete game implementing primitive 
// operations for the template method
class Monopoly : public Game {
public:
  // implementing concrete methods
  void initializeGame() {
    playersCount_ = rand() % numPlayers_ + 1; // initialize players
  }

  void makeMove(int player) {
    if (movesCount_ > minMoves_) {
      const int chance = minMoves_ + rand() % (maxMoves_ - minMoves_);
      if (chance < movesCount_) playerWon_ = player;
    }
  }

  void printWinner() {
    cout << "Monopoly, player " << playerWon_ << " won in "
      << movesCount_ << " moves." << endl;
  }

private:
  static const int numPlayers_ = 8; // max number of players
  static const int minMoves_ = 20; // nobody wins before minMoves_
  static const int maxMoves_ = 200; // somebody wins before maxMoves_
};

// Chess - another game implementing
//  primitive operations
class Chess : public Game {
public:
  void initializeGame() {
    playersCount_ = numPlayers_; // initalize players
    for (int i = 0; i < numPlayers_; ++i)
      experience_[i] = rand() % maxExperience_ + 1;
  }

  void makeMove(int player) {
    if (movesCount_ > minMoves_) {
      const int chance = (rand() % maxMoves_) / experience_[player];
      if (chance < movesCount_) playerWon_ = player;
    }
  }

  void printWinner() {
    cout << "Chess, player " << playerWon_
      << " with experience " << experience_[playerWon_]
      << " won in " << movesCount_ << " moves over"
      << " player with experience " << experience_[playerWon_ == 0 ? 1 : 0]
      << endl;
  }

private:
  static const int numPlayers_ = 2;
  static const int minMoves_ = 2; // nobody wins before minMoves_
  static const int maxMoves_ = 100; // somebody wins before maxMoves_
  static const int maxExperience_ = 3; // player's experience
                                       // the higher, the greater probability of winning
  int experience_[numPlayers_];
};

// dice game
class Dice : public Game {
public:
  void initializeGame() {
    playersCount_ = skNumPlayers_; // initalize players

  }
  void makeMove(int player) {
    // there are three rounds, 1, 2, 3. At the begining of rounds 2 and 3, 
    // players must decide if they wish to skip this round
    if (movesCount_ > 0 && player == compID) {
      compDecideToSkip();
      humnDecideToSkip();
    }
    if (compDecidedToSkip == true && humnDecidedToSkip == true) {
      cout << "Both players skipped. Game over." << endl;
      determineWinner();
    }
    else { // if one of the players didn't skip
      if (player == compID) { // computers turn
        cout << "Computer rolled: ";
        if (compDecidedToSkip == true)
          cout << "skipped       ";
        else {
          int roll = roll5Dice();
          if (roll > compHighScore)
            compHighScore = roll;
        }
        cout << " | computers's highest score =";
        cleanOutput(compHighScore);
      }
      else if (player == humnID) { // human's turn
        cout << "You rolled:      ";
        if (humnDecidedToSkip == true)
          cout << "skipped       ";
        else {
          int roll = roll5Dice();
          if (roll > humnHighScore)
            humnHighScore = roll;
        }
        cout << " |        your highest score =";
        cleanOutput(humnHighScore);
      }

      // if game is over, determine a winner
      if (movesCount_ == skMaxNumMoves - 1 && player == humnID) {
        cout << "\nEnd of Round 3. Game over." << endl;
        determineWinner();
      }
    }
    cout << endl;
  }

  void printWinner() {
    if (playerWon_ == humnID)
      cout << "You Win!" << endl;
    else
      cout << "You Lose." << endl;
  }

  int roll5Dice() { 
    int sum = 0; 
    for (int i = 0; i < 5; ++i) {
      int dice = rand() % 5 + 1; // between 1 and 6
      cout << dice << " ";
      sum += dice;
    }
    cout << "= ";
    cleanOutput(sum);
    return sum; // sum is between 5 and 30
  }

  void cleanOutput(int n) {
    if (n < 10) 
      cout << " ";
    cout << n;
  }

  void compDecideToSkip() {
    // comp skip is random. 
    int n = rand() % 2;
    if (n == 0) 
      compDecidedToSkip = false;
    else 
      compDecidedToSkip = true;

    // a smart player would never skip but the computer isn't smart
    /* // or skip if you are winning
    if (compHighScore > humnHighScore)
      compDecidedToSkip = false;
    else
    compDecidedToSkip = true;
    */
  }

  void humnDecideToSkip() {
    string input;
    // get input from user
    while (true) {
      cout << "Roll Again? [y/n] ";
      cin >> input;
      // clean up the string
      std::transform(input.begin(), input.end(), input.begin(), tolower);
      std::remove_if(input.begin(), input.end(), isspace); // remove whitespace

      if (input == "n" || input == "no") {
        humnDecidedToSkip = true;
        cout << endl;
        break;
      }
      else if (input == "y" || input == "yes") {
        humnDecidedToSkip = false;
        cout << endl;
        break;
      }
      else
        cout << "     -invalid input." << endl;
    }
  }

  void determineWinner() {
    playerWon_;
    if (humnHighScore > compHighScore)
      playerWon_ = humnID;
    else
      playerWon_ = compID;
  }
private:
  // two players. one human and one computer
  static const int skNumPlayers_ = 2;

  int compHighScore = 0;
  int humnHighScore = 0;

  bool humnDecidedToSkip = false;
  bool compDecidedToSkip = false;

  static int sComputerWinRatio;
  static const int skMaxNumMoves = 3;
  static const int compID = 0;
  static const int humnID = 1;

};





int main() {
  srand(static_cast<unsigned int>(time(nullptr)));

  Game* gp = nullptr;

  // play chess 10 times
  for (int i = 0; i < 10; ++i) {
    gp = new Chess;
    gp->playGame();
    delete gp;
  }
  cout << endl;

  // play monopoly 5 times
  for (int i = 0; i < 5; ++i) {
    gp = new Monopoly;
    gp->playGame();
    delete gp;
  }
  cout << endl;

  // play Dice 10 times
  for (int i = 0; i < 10; ++i) {
    cout << "Dice Game " << i+1 << " ----------------------------------------------------------------- " << endl;
    gp = new Dice;
    gp->playGame();
    delete gp;
    cout << "-----------------------------------------------------------------------------\n" << endl;

    cout << endl;
  }
}