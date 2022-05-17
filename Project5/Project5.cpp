#include <iostream>
#include <time.h>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include <map>
using namespace std;
class Hangman
{
public:
	Hangman()
	{
		cout << "Start - 1, Exit - 0: ";
		cin >> choose;
		if (choose == 1)
		{
			wr.open("kek.txt");
			rd.open("kek.txt");
			setwords();
			randomword();
			win = 2;
			while (win == 2)
			{
				printword();
				cout << "Enter letter: ";
				cin >> letter_choose;
				checkletter();
				checkwin();
			}
		}
	}
	~Hangman()
	{
		delete[] word2; 
	}
private:
	time_t start, end; 
	int win = 2;
	int choose;
	int attempts = 0;
	char letter_choose;
	int life = 6;
	ofstream wr;
	ifstream rd;
	string word;
	char* word2 = nullptr;
	vector<string> words = { "elephant", "table", "water", "computer"};
	list<char> player_words;
	void setwords()
	{
		for (auto w : words)
			wr << w << endl;
	}
	void randomword()
	{
		srand(time(NULL));
		time(&start);
		int ran = rand() % words.size();
		while (ran >= 0)
		{
			getline(rd, word);
			ran--;
		}
		word2 = new char[word.size()];
		for (size_t i = 0; i < word.size(); i++)
		{
			word2[i] = '_';
		}
	}
	void printword()
	{
		for (size_t i = 0; i < word.size(); i++)
		{
			cout << word2[i] << " ";
		}
		cout << endl;
	}
	void checkletter()
	{
		int ok = 0;
		int i = 0;
		for (auto ch : player_words)
		{
			if (ch == letter_choose)
			{
				ok++;
				cout << "You have already entered this letter" << endl;
				break;
			}
		}
		if (ok == 0)
		{
			player_words.push_back(letter_choose);
			attempts++;
		}
		for (auto it = word.begin(); it != word.end(); it++, i++)
		{
			if (*it == letter_choose)
			{
				word2[i] = letter_choose;
				ok++;
			}
		}
		if (ok == 0)
		{
			cout << "Wrong letter!" << endl;
			life--;
			cout << "You have " << life << " life left" << endl;
			if (life == 0)
			{
				cout << "You lose!" << endl;
				win = 0;
				statistics();
			}
		}
	}
	void checkwin()
	{
		int ok = 0;
		for (size_t i = 0; i < word.size(); i++)
		{
			if (word2[i] == '_')
				ok++;
		}
		if (ok == 0)
		{
			cout << "You won!" << endl;
			win = 1;
			statistics();
		}
	}
	void statistics()
	{
		time(&end);
		double seconds = difftime(end, start);
		int minutes = 0;
		minutes = seconds / 60;
		seconds = seconds - (minutes * 60);
		cout << "Wasted time - " << minutes << " minutes and " << seconds << " seconds" << endl;
		cout << "You have made " << attempts << " attempts" << endl;
		cout << "The word was - " << word << endl;
		cout << "The letters you entered: ";
		for (auto ch : player_words)
			cout << ch << " ";
		cout << endl;
	}
};
int main()
{
	Hangman j;
	return 0;
}