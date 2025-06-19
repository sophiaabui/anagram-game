#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

// Class representing the Anagram Game
class AnagramGame {
private:
    vector<string> words;   // Vector to store the words from the file
    string selectedWord;    // The word selected for the current round
    string shuffledWord;    // The shuffled version of the selected word
    int score;              // Player's score

    // Function to shuffle a word
    string shuffleWord(const string& word) {
        string shuffled = word;
        random_shuffle(shuffled.begin(), shuffled.end());
        return shuffled;
    }

    // Function to check if two words are anagrams
    bool isAnagram(const string& word1, const string& word2) {
        if (word1.length() != word2.length() || word1 == word2)
            return false;

        int count[26] = {0}; // Assuming only lowercase letters
        for (char c : word1)
            count[c - 'a']++;

        for (char c : word2) {
            if (--count[c - 'a'] < 0)
                return false;
        }

        return true;
    }

public:
    // Constructor to initialize the game
    AnagramGame(const string& filename) : score(100) {
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Error: Unable to open file " << filename << endl;
            exit(1);
        }

        string word;
        while (getline(file, word)) {
            words.push_back(word);
        }

        srand(static_cast<unsigned int>(time(nullptr)));
        selectWord(); // Selects the first word for the game
    }

    // Function to select a word for the current round
    void selectWord() {
        selectedWord = words[rand() % words.size()];
        shuffledWord = shuffleWord(selectedWord);
        // Ensure the presented anagram is actually an anagram of the selected word
        while (!isAnagram(selectedWord, shuffledWord)) {
            shuffledWord = shuffleWord(selectedWord);
        }
    }

    // Function to check the player's guess
    pair<bool, string> checkGuess(const string& guess) {
        string guessLower = guess;
        transform(guessLower.begin(), guessLower.end(), guessLower.begin(), ::tolower);
        if (guessLower == selectedWord) {
            score += 100;
            selectWord(); // Select a new word for the next round
            return {true, ""};
        } else {
            score -= 50;
            if (score <= 0) {
                score = 0;
                return {false, ""};
            }
            return {false, selectedWord}; // Return the correct word if guess is incorrect
        }
    }

    // Function to get the player's score
    int getScore() const {
        return score;
    }

    // Function to get the shuffled word for display
    string getShuffledWord() const {
        return shuffledWord;
    }

    // Function to get the selected word
    string getSelectedWord() const {
        return selectedWord;
    }
};

// Function to display a cat figure
void displayCatFigure() {
    cout << "  /\\_/\\   " << endl;
    cout << " ( o.o )  " << endl;
    cout << "  > ^ <   " << endl;
}

int main() {
    string filename = "sgb-words.txt";

    // Initialize the AnagramGame object with the file containing the words
    AnagramGame game(filename);

    cout << "Welcome to the Anagram Game!\n";

    bool firstRound = true;
    while (true) {
        if (!firstRound) {
            cout << "Score: " << game.getScore() << endl;
        }
        cout << "Unscramble the letters to form a word.\n";
        cout << "Here is your anagram: " << game.getShuffledWord() << endl;

        cout << "Enter your guess (type 'exit' to quit): ";
        string guess;
        cin >> guess;

        if (guess == "exit") {
            cout << "Thanks for playing! Your final score is: " << game.getScore() << endl;
            break;
        }

        // Check the player's guess and handle accordingly
        auto result = game.checkGuess(guess);
        if (result.first) {
            cout << "Congratulations! You guessed the word correctly.\n";
        } else {
            cout << "Sorry, that's incorrect. ";
            if (!result.second.empty()) {
                cout << "The correct word is: " << result.second << endl;
            } else {
                cout << endl;
            }
        }

        // Check if the game is won or lost
        if (game.getScore() >= 400) {
            cout << "Congratulations! You've won the game!\n";
            displayCatFigure();
            break;
        }

        if (game.getScore() == 0) {
            cout << "You've run out of points! Game over.\n";
            break;
        }

        game.selectWord(); // Select a new word for the next round

        if (firstRound) {
            firstRound = false;
        }
    }

    return 0;
}