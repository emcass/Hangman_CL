#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

std::string words[185];

int maxWrong = 10;

void read_record() {

	std::ifstream myFile("words.csv");

	if (!myFile.is_open()) {
		std::cout << "Could not open file" << std::endl;
	}

	if (!myFile.good()) {
		std::cout << "File not good" << std::endl;
	}

	std::string line, word;

	int i = 0;

	while (std::getline(myFile, line)) {
		
		

		std::stringstream ss(line);

		while (ss >> word) {
			std::string editedWord = word;
			editedWord = word.substr(1, word.length() - 3);

			std::string finWord = "";

			for (int j = 0; j < editedWord.length(); j++) {
				finWord += std::tolower(editedWord.at(j));
			}
			words[i] = finWord;
			i++;
		}
	}

}

void revealWord(int index) {
	std::cout << "Your word to guess is: " << words[index] << std::endl;
}

bool checkIfCharIsValid(char c) {
	std::string valid = "abcdefghijklmnopqrstuvwxyz";

	return (valid.find(c) != std::string::npos);

}

void didWin() {
	std::cout << "CONGRATS YOU HAVE WON!\n";
}

void lose() {
	std::cout << "LOSER! Better luck next time.\n\n\n\n\n";
}

int main() {
	
	std::cout << "WELCOME TO HANGMAN" << std::endl;

	read_record();

	std::srand(std::time(0));
	int rNum = std::rand() % 185;

	std::string wordToGuess = words[rNum];

	std::string wrongLetters = "";
	std::string correctLetters = "";

	bool gameOver = false;

	while (!gameOver) {
		std::cout << "\t";
		for (int i = 0; i < wordToGuess.length(); i++) {
			if (correctLetters.find(wordToGuess.at(i)) != std::string::npos) {
				std::cout << wordToGuess.at(i);
			}
			else {
				std::cout << "_ ";
			}
		}

		std::cout << "\n\n";

		std::cout << "Incorrect Letters: " << wrongLetters << " (" << wrongLetters.length() << "/" << maxWrong << ")";

		//for (int i = 0; i < wrongLetters.length(); i++) {
		//	std::cout << "" + wrongLetters.at(i) << ", ";
		//}

		std::cout << std::endl;

		std::cout << "Please guess a letter: ";
		std::string input;
		std::cin >> input;

		std::cout << "Input was: " << input << std::endl;

		if (!input.compare("quit")) {
			gameOver = true;
		}
		else if (!input.compare("reveal")) {
			revealWord(rNum);
		}
		else {

			char inputChar = input.at(0);

			if (checkIfCharIsValid(inputChar)) {


				// GUESS WAS IN WORD
				if (wordToGuess.find(inputChar) != std::string::npos) {
					std::cout << "CORRECT" << std::endl;

					if (correctLetters.find(inputChar) == std::string::npos) {
						correctLetters += inputChar;
					}

					bool missing = false;

					// IF GAME HAS BEEN COMPLETED
					for (int i = 0; i < wordToGuess.length(); i++) {
						if (correctLetters.find(wordToGuess.at(i)) == std::string::npos) {
							missing = true;
						}
					}

					if (!missing) {
						didWin();
						return 1;
					}
				}
				// GUESS WAS NOT IN WORD
				else {
					std::cout << "WRONG" << std::endl;
					if (wrongLetters.find(inputChar) == std::string::npos) {
						wrongLetters += inputChar;
					}

					if (wrongLetters.length() >= maxWrong) {
						lose();
						return -1;
					}
				}
			}
			else {
				std::cout << "You entered an invalid character" << std::endl;
			}
		}
		std::cout << "\n\n\n--------------------------------------------\n\n\tHANGMAN\n\n\n";
	}
}