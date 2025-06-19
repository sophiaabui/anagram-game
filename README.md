Sophia Bui
ISC 3313 Final Project

///////////////////////////////////////////////////////////////

The code (final.cpp) implements an Anagram Game where players are presented with a
scrambled word and are required to guess the original word. The game continues 
until the player either correctly guesses the word, runs out of points, or 
chooses to exit the game. The program tracks the player's score and displays it
after each round. The word bank is loaded from a file, and each word is shuffled
to create an anagram for the player to solve. If the player guesses incorrectly, 
the correct word is provided, and a new anagram is presented for the next round.
The game ends when the player's score reaches 0 or exceeds 400 points.

//////////////////////////////////////////////////////////////////
 To compile and run final.cpp:
 >> g++ final.cpp
 >> ./a.out
