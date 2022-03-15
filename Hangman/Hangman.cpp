#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <ctime>

using namespace std;

string chooseWord(const string fileName);
void renderGame(string guessedWord, string& badGuess, int badGuessCount);
char readAGuess();
bool contains(string word, char guess);
string update(string guessedWord, string word, char guess);

const int MAX_BAD_GUESSES = 7;
const string DATA_WORD = "Word.txt";

int main() {
    srand(time(NULL));
    char Playagain = 'n';
    do {
        int badGuessCount = 0;
        string word = chooseWord(DATA_WORD);
        string guessWord = string(word.size(), '-');
        string badGuess = "";
        do {
            renderGame(guessWord, badGuess, badGuessCount);
            char guess = readAGuess();
            if (contains(word, guess)) guessWord = update(guessWord, word, guess);
            else {
                badGuessCount ++;
                badGuess += guess;
            }
        } while (badGuessCount < MAX_BAD_GUESSES && guessWord != word);
        renderGame(guessWord, badGuess, badGuessCount);
        if (badGuessCount < MAX_BAD_GUESSES) cout << "Congratulation! You win!\n";
        else cout << "Oh no! You lost! The correct word is: " << word << endl;
        cout << " \nTry again? ('y' for yes, 'n' for no)\n";
        cin >> Playagain;
    } while (Playagain == 'y');
    cout << "GOOD BYE\n";
	return 0;
}

const string FIGURE[] = {
    "___________________  \n"
    "  |                  \n"
    "  |                  \n"
    "  |                  \n"
    "  |                  \n"
    "__|___               \n",
    "___________________  \n"
    "  |              |   \n"
    "  |                  \n"
    "  |                  \n"
    "  |                  \n"
    "__|___               \n",
    "___________________  \n"
    "  |              |   \n"
    "  |              O   \n"
    "  |                  \n"
    "  |                  \n"
    "__|___               \n",
    "___________________  \n"
    "  |              |   \n"
    "  |              O   \n"
    "  |              |   \n"
    "  |                  \n"
    "__|___               \n",
    "___________________  \n"
    "  |              |   \n"
    "  |              O   \n"
    "  |             /|   \n"
    "  |                  \n"
    "__|___               \n",
    "___________________  \n"
    "  |              |   \n"
    "  |              O   \n"
    "  |             /|\\ \n"
    "  |                  \n"
    "__|___               \n",
    "___________________  \n"
    "  |              |   \n"
    "  |              O   \n"
    "  |             /|\\ \n"
    "  |             /    \n"
    "__|___               \n",
    "___________________  \n"
    "  |              |   \n"
    "  |              O   \n"
    "  |             /|\\ \n"
    "  |             / \\ \n"
    "__|___               \n"};

string chooseWord(const string fileName) {
	vector<string> wordlist;
	ifstream file(fileName);
  	if (file.is_open()) {
	    string word;
		while (file >> word) {
            wordlist.push_back(word);
        }
    	file.close();
  	}
  	int random = rand() % wordlist.size();
    return (wordlist[random]);
}

void renderGame(string guessedWord, string& badGuess, int badGuessCount){
    const int LINES = 30;
	for (int i = 0; i < LINES; i++) cout << endl;
    cout << guessedWord << endl;
    cout << FIGURE[badGuessCount];
    cout << "Number of wrong guesses: " << badGuessCount << endl;
    if (badGuessCount > 0) {
        cout << "Wrong " << (badGuessCount == 1 ? "guess: " : "guesses: "); 
        cout << badGuess << endl;
    }
};

char readAGuess() {
    char input;
    cout << "Your guess: ";
    cin >> input;
    return input;
}

bool contains(string word, char guess){
    return (word.find_first_of(guess) != string::npos);
};

string update(string guessedWord, string word, char guess){
    for (int i = 0; i <= guessedWord.size(); i++) {
        if (word[i] == guess) {
            guessedWord[i] = guess;
        }
    }
    return guessedWord;
};
