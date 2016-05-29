#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <limits>
using namespace std;

string name, type;
int health, strength, magic = 0;
int pickChar = NULL;

void loadCharacter();
void createChar();

int main()
{//initiates TextQuest
	int begin = 0;
	while (begin == 0)
	{
		cout << "Hello adventurer! Welcome to TextQuest!" << endl;
		cout << "Would you like to load a previous save or create a new character?: " << endl;
		cout << "1. Load saved game." << endl;
		cout << "2. Create new character." << endl;
		cout << ">";

		int play = 0;
		cin >> play;
		cin.ignore();

		if (play == 1) //loads a previously saved character
		{
			loadCharacter();

			begin = 1;
		}
		else if (play == 2) //creates a new character
		{
			createChar();

			begin = 1;
		}
		else //validation check, must load or create character
		{
			cout << "Please enter 1 to load a previous save or enter 2 to create a new character." << endl;
			cout << ">";
			cin.clear();
			cin.ignore();
		}
	}

	//main game loop
	fstream gameLoop;
	gameLoop.open("gameLoop.txt");
	gameLoop << "An enemy Warrior strikes you with his weapon!,-50" << endl;
	gameLoop << "An enemy Mage casts an evil spell on you!,-20" << endl;
	gameLoop << "You found a health potion!,+25" << endl;
	gameLoop << "An enemy Rogue backstabs you from the shadows!,-40" << endl;
	gameLoop << "You got eaten by a dragon!,-1000" << endl;
	gameLoop.close();

	fstream gameEvents;
	gameEvents.open("gameLoop.txt");

	//asks player if they wish to continue
	int yn = 0;
	cout << "Are you ready to continue your adventure?" << endl;
	cout << "1. Yes" << endl;
	cout << "2. No" << endl;
	cout << ">";
	cin >> yn;

	//loops through game events, asking the player if they wish to continue after each event
	if (yn == 1)
	{
		int q = 0;
		string events1;
		string events2;
		string cont;
		cont = "y";
		while ((getline(gameEvents, events1)) && q == 0)
		{
			//if player says 'y' then continue with game events and update health/stats, end if player's character dies
			if (cont == "y")
			{
				getline(stringstream(events1), events2);
				cout << events2 << endl;
				string substr = events2.substr(events2.find(",") + 1);
				int damage = atoi(substr.c_str());
				::health += damage;
				cout << "You have " << ::health << " health left!" << endl;

				if (health <= 0)
				{
					cout << "You have died!" << endl;
					system("pause");
					return 0;
				}

				cout << "Would you like to continue? (y/n)" << endl;
				cout << ">";
				cin >> cont;
			}
			//if players enters 'n' it saves the game and quits
			else if (cont == "n")
			{
				ifstream currChar("charFile.txt");
				string strReplace;

				for (int i = 0; i < ::pickChar - 1; i++)
				{
					currChar.ignore(numeric_limits<streamsize>::max(), '\n');
				}

				getline(currChar, strReplace);
				currChar.close();

				ifstream oldSaves("charFile.txt");
				ofstream newSaves("tempFile.txt");
				string strTemp;
				stringstream ss;
				string newsave;
				ss << ::name << "," << ::type << "," << ::health << "," << ::strength << "," << ::magic;
				newsave = ss.str();

				while (oldSaves >> strTemp)
				{
					if (strTemp == strReplace)
					{
						strTemp = newsave;
					}
					if (!(strTemp.empty()))
					{
						strTemp += "\n";
					}
					newSaves << strTemp;
				}
				oldSaves.close();
				newSaves.close();

				fstream saveChar("charFile.txt");
				fstream tempSave("tempFile.txt");
				string finalSave;
				while (tempSave)
				{
					getline(tempSave, finalSave);
					if (!(finalSave.empty()))
					{
						finalSave += '\n';
					}
					saveChar << finalSave;
				}
				saveChar.close();
				tempSave.close();

				fstream newCurrent;
				newCurrent.open("currentChar.txt");
				newCurrent << ::name << " " << ::type << " " << ::health << " " << ::strength << " " << ::magic;
				newCurrent.close();

				cout << "Saving... " << endl;

				q = 2;
			}
			//validation check for continuation
			else
			{
				cout << "Please enter y or n." << endl;
				cin.clear();
				cin >> cont;
			}
		}
		if (q == 2)
		{
			cout << "You have ended the game." << endl;
		}
		else
		{
			cout << "You have reached the end of the game." << endl;
		}
	}
	else if (yn == 2)
	{
		cout << "You have chosen not to continue." << endl;
	}
	else
	{
		cout << "Please enter 1 or 2 to decide whether to continue your adventure." << endl;
	}
	system("pause");
}

void loadCharacter()
{
	ifstream savedFile;
	savedFile.open("charName.txt");
	cout << "Please select an existing character to play:" << endl;

	ifstream numChar;
	numChar.open("charFile.txt");

	//counts number of saved characters in text file
	int charCount = 0;
	string line;

	while (getline(numChar, line))
	{
		charCount++;
	}

	cout << "Total saved characters: " << charCount << endl;
	numChar.close();

	string savedgame;
	string savedgame2;
	int k = 0;
	while (getline(savedFile, savedgame))
	{
		getline(stringstream(savedgame), savedgame2);
		cout << ++k << ". " << savedgame2 << endl;
	}


	ifstream savedChar;
	string load;
	savedChar.open("charFile.txt");

	//player chooses from a list of previously saved characters

	int chooseChar = 0;

	while (chooseChar == 0)
	{
		cout << ">";
		cin >> ::pickChar;

		//checks whether player is picking an existing character from the list
		if (::pickChar < 0 || ::pickChar > charCount)
		{
			cout << "That load game doesn't exist, please load an existing character." << endl;
			cin.clear();
			cin.ignore();
		}
		//loads first character/line if player enters '1'
		else if (::pickChar == 1)
		{
			getline(savedChar, load);
			cout << "Loading..." << load << endl;
			chooseChar = 1;
		}
		//if player enters number greater than 1, loops through file and ignores lines/characters up to the one player chose
		else
		{
			savedChar.seekg(ios::beg);
			for (int i = 0; i < ::pickChar - 1; i++)
			{
				savedChar.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			getline(savedChar, load);
			cout << "Loading... " << load << endl;
			savedChar.close();
			chooseChar = 1;
		}
		//loads chosen character into currentChar file.
		fstream currentChar;
		currentChar.open("currentChar.txt");
		currentChar << load;
		currentChar.close();

		string stream;
		fstream currentChar2;
		currentChar2.open("currentChar.txt");
		currentChar2 >> stream;
		currentChar2.close();

		//splits line by delimiters ',' and replaces with white space
		for (int i = 0; i < stream.length(); i++)
		{
			if (stream[i] == ',')
			{
				stream[i] = ' ';
			}
		}
		fstream currentChar3;
		currentChar3.open("currentChar.txt");
		currentChar3 << stream;
		currentChar3.close();

		fstream currentChar4;
		currentChar4.open("currentChar.txt");

		//assigns character's stats to global variables
		currentChar4 >> ::name;
		currentChar4 >> ::type;
		currentChar4 >> ::health;
		currentChar4 >> ::strength;
		currentChar4 >> ::magic;

		currentChar4.close();
	}
}

void createChar()
{
	ofstream nameFile;
	nameFile.open("charName.txt", ios_base::app);

	string charName; //assigning your new character's name
	cout << "What would you like your character's name to be? " << endl;
	cin >> charName;
	nameFile << charName << endl;
	nameFile.close();

	string temp;
	string temp2;
	fstream vocation;
	vocation.open("vocation.txt");

	int i = 0;
	while (getline(vocation, temp))
	{
		getline(stringstream(temp), temp2, ',');
		cout << i++ << ". " << temp2 << endl;
	}

	int charClass = 0;
	cout << "Please select a class by entering the associated number: " << endl;
	cout << ">";
	cin >> charClass;

	fstream charFile;
	fstream currentChar;
	currentChar.open("currentChar.txt");
	charFile.open("charFile.txt", ios_base::app);

	if (charClass == 0) //choosing warrior class
	{
		charFile << charName << "," << "Warrior,100,120,0" << endl;
		currentChar << charName << ' ' << "Warrior" << ' ' << "100" << ' ' << "120" << ' ' << "0";
		cout << "Your character has the following characteristics: " << endl;
		cout << charName << "," << "Warrior,100,120,0" << endl;

	}
	else if (charClass == 1) //choosing mage class
	{
		charFile << charName << "," << "Mage,80,60,100" << endl;
		currentChar << charName << ' ' << "Mage" << ' ' << "80" << ' ' << "60" << ' ' << "100";
		cout << "Your character has the following characteristics: " << endl;
		cout << charName << "," << "Mage,80,60,100" << endl;
	}
	else if (charClass == 2) //choosing rogue class
	{
		charFile << charName << "," << "Rogue,60,80,50" << endl;
		currentChar << charName << ' ' << "Rogue" << ' ' << "60" << ' ' << "80" << ' ' << "50";
		cout << "Your character has the following characteristics: " << endl;
		cout << charName << "," << "Rogue,60,80,50" << endl;
	}
	charFile.close();
	currentChar.close();

	fstream currentChar4;
	currentChar4.open("currentChar.txt");

	//assigning character stats as global variables
	currentChar4 >> ::name;
	currentChar4 >> ::type;
	currentChar4 >> ::health;
	currentChar4 >> ::strength;
	currentChar4 >> ::magic;

	charFile.close();
}