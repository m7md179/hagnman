#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<windows.h>
#include<time.h>
using namespace std;

void printMessage(string message, bool printTop = true, bool printBottom = true) {

	if (printTop)
	{
		cout << "+---------------------------------+" << endl;
		cout << "|";
	}
	else
	{
		cout << '|';
	}
	bool front = true;
	for (int i = message.length(); i < 33 ; i++)
	{
		if (front)
		{
			message = " " + message;
		}
		else
		{
			message = message + " ";
		}
		front = !front;
	}
	cout << message;
	if (printBottom)
	{

		cout << "|" << endl;
		cout << "+---------------------------------+" << endl;
	}
	else
	{
		cout << '|' << endl;
	}
}
void drewHangMan(int guessCount = 0) {
	
	if (guessCount>=1)
	{
		printMessage("|", false, false);
	}
	else
	{
		printMessage("", false, false);
	}
	if (guessCount >= 2)
	{
		printMessage("|", false, false);
	}
	else
	{
		printMessage("", false, false);
	}
	if (guessCount >= 3)
	{
		printMessage("O", false, false);
	}
	else
	{
		printMessage("", false, false);
	}
	if (guessCount == 4)
	{
		printMessage("/  ", false, false);
	}
	if (guessCount == 5)
	{
		printMessage("/| ", false, false);
	}
	if (guessCount >= 6)
	{
		printMessage("/|\\", false, false);
	}
	else
	{
		printMessage("", false, false);
	}
	if (guessCount >= 7)
	{
		printMessage("|", false, false);
	}
	else
	{
		printMessage("", false, false);
	}
	if (guessCount == 8)
	{
		printMessage("/  ", false, false);
	}
	if (guessCount >= 9)
	{
		printMessage("/ \\", false, false);
	}
	else
	{
		printMessage("", false, false);
	}
	

}
void printLatters(string input,char from,char to) {
	string s;
	for (char i = from; i <= to; i++)
	{
		if (input.find(i)==string::npos)
		{
			s += i;
			s += " ";
		}
		else
		{
			s += "  ";
		}
	}
	printMessage(s, false, false);

}
void availableLatters(string taken) {

	printMessage("Available letters");
	printLatters(taken, 'A', 'M');
	printLatters(taken, 'N', 'Z');
}
bool chickWordAndChickWin(string word,string guessed) {

	bool won = true;
	string s;
	for (int i = 0; i < word.length(); i++)
	{
		if (guessed.find(word[i])==string::npos)
		{
			won = false;
			s += "_ ";
		}
		else
		{
			s += word[i];
			s += " ";
		}
	}
	printMessage(s, false);

	return won;
}
string loudRandomWord(string path) {
	int lineCount = 0;
	string word;
	vector<string>v;
	ifstream reader(path);
	if (reader.is_open())
	{
		while (getline(reader,word))
		{
			v.push_back(word);
		}
		int randomLine = rand() % v.size();
		word = v.at(randomLine);
		reader.close();
	}
	return word;
}
int triesToGuess(string word,string guessed) {
	int error = 0;
	for (int i = 0; i < guessed.length(); i++)
	{
		if (word.find(guessed[i])==string::npos)
		{
			error++;
		}
	}
	return error;
}
int main() {
	srand(time(0));
	string guesses ;
	string wordToGuess;
	int tries = 0;
	bool win = false;
	wordToGuess = loudRandomWord("words.txt");
	do
	{
		system("cls");
		printMessage("HANG MAN");
		drewHangMan(tries);
		printMessage("+----------+", false, false);
		printMessage("|          |", false, false);
		availableLatters(guesses);
		printMessage("Guess the word ");
		win = chickWordAndChickWin(wordToGuess, guesses);

		if (win) {
			break;
		}
		char x;
		cout << "> ";
		cin >> x;
		if (guesses.find(x)==string::npos)
		{
			guesses += x;
		}
		tries = triesToGuess(wordToGuess, guesses);

	} while (tries<10);

	if (win)
	{
		cout << "You won";
	}
	else
	{
		cout << "You lost";
	}
	
	return 0;
}
/*
+---------------------------------+
|             HANG MAN            |
+---------------------------------+
|               |                 |
|               |                 |
|               O                 |
|              /|\                |
|               |                 |
|              / \                |
|         +----------+            |
|         |          |            |
+---------------------------------+
|        Available letters        |
+---------------------------------+
|     A B C D E F G H I J K L M   |
|     N O P Q R S T U V W X Y Z   |
+---------------------------------+
|         Guess the word          |
+---------------------------------+
| _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ |
+---------------------------------+
>
*/