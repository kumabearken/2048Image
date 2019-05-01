#include <iostream>
#include <time.h>
#include <stdio.h>
#include <fstream>
 
using namespace std;

//definetions
#define U  "UP"
#define D  "DOWN"
#define L  "LEFT"
#define R  "RIGHT"

// function prototypes
void Menu();
void Play();
void HighScore();

//Classes
class Tile
{
public:
	int xPos = 0;
	int yPos = 0;
	string value = "0";
	bool age = false;
	Tile(string value, int xPos, int yPos, bool age)
	{
		this->value = value;
		this->xPos = xPos;
		this->yPos = yPos;
		this->age = age;
	}
	Tile()
	{
		xPos = 0;
		yPos = 0;
		value = "0";
		age = false;
	}
};

class Board
{
public:
	int x;
	int y;
	Tile* array = new Tile[1];
	Tile* testB = new Tile[1];
	Board(int x, int y)
	{
		this->x = x;
		this->y = y;
		array = new Tile[x*y];
		for (int i = 0; i < x * y; ++i)
		{
			array[i].value = "0";
			array[i].xPos = i%x;
			array[i].yPos = i/y;
			array[i].age = true;
		}
	}
	~Board()
	{
		delete [] array;
	}
	void PrintBoard()
	{
		int count = 0;
		for (int i = 0; i < y; ++i)
		{
			for (int j = 0; j < x; ++j)
			{
				cout << array[count].value;
				//cout << array[count].xPos;
				//cout << array[count].yPos;
				//cout << array[count].age;
				cout << " ";
				++count;	
			}
			cout << endl;
		}	
	}
	void PrepBoard()
	{	
		int created = 0;

		while(created != 2)
		{
			AddTile();
			++created;	
		}
	}
	void AddTile()
	{
		srand(time(NULL));
		bool added = false;
		while(!added)
		{
			int evenOrOdd = rand() % 2;
			int ranInt = rand() % (x * y);
			//even
			if(evenOrOdd)
			{	
				if(array[ranInt].value == "0")
				{
					array[ranInt].value = "1";
					array[ranInt].age = true;
					added = true;
				}
			}
			//odd
			else
			{	
				if(array[ranInt].value == "0")
				{
					array[ranInt].value = "2";
					array[ranInt].age = true;
					added = true;
				}
			}
		}	
	}
	void MergeTile(int t1, int t2)
	{
		// conditions value must be ==
		//	both age must be true
		if((array[t1].value == array[t2].value)
			&& (array[t1].age == true)
			&& (array[t2].age == true))
		{
			int temp = stoi(array[t1].value);
			++temp;
			array[t1].value = to_string(temp);
			array[t2].value = to_string(0);
			array[t1].age = false;
		}
	}
	string Arrows()
	{
		char input;
		bool go=true;
		string direction;
		while(go)
		{
			cin.get(input);
			switch (input)
			{
				case '8':
					direction = U;
					go = false;
					break;
				case '2':
					direction = D;
					go =  false;
					break;
				case '4':
					direction = L;
					go =  false;
					break;
				case '6':
					direction = R;
					go =  false;
					break;
				default:
					break;
			}
		}
		return direction;
	}
	void ResetAge()
	{
		for (int i = 0; i < x * y; ++i)
		{
			array[i].age = true;
		}
	}
	void Move(string dir)
	{		
		if (dir == U)
		{
			Up();
		}
		else if (dir == D)
		{
			Down();
		}
		else if(dir == L)
		{
			Left();
		}
		else if(dir == R)
		{
			Right();
		}
		else 
			cout << "NOT VALID\n";
		ResetAge();
	}
	void Up()
	{
		bool action = true;
		while(action)
		{
			action = false;
			for (int i = 0; i <x*y; ++i)
			{
				//bound check
				if(i+x >= x*y)
				{

				}
				//tests if both 0
				else if (array[i].value =="0" && array[i+x].value == "0")
				{

				}
				// tests age
				else if (array[i].age==false ||  array[i+x].age == false)
				{

				}
				//if same and other tests pass
				else if (array[i].value == array[i+x].value)
				{
					MergeTile(i,i+x);
					action=true;
				}
				// if tile can move
				else if ((array[i].value == "0") && (array[i+x].value!="0"))
				{
					Swap(i,i+x);
					action=true;
				}
				// unmovable
				else
				{

				}
			}
		}
	}
	void Down()
	{
		bool action = true;
		while(action)
		{
			action = false;
			for (int i = x * y - 1; i > 0; --i)
			{
				//bound check
				if(i-x < 0)
				{

				}
				else if (array[i].value =="0" && array[i-x].value == "0")
				{

				}
				else if (array[i].age==false ||  array[i-x].age == false)
				{

				}
				else if (array[i].value == array[i-x].value)
				{
					MergeTile(i,i-x);
					action=true;
				}
				else if ((array[i].value == "0") && (array[i-x].value!="0"))
				{
					Swap(i,i-x);
					action=true;
				}
				else
				{

				}
			}
		}
	}
	void Left()
	{
		bool action = true;
		while(action)
		{
			action = false;
			for (int i = 0; i <x*y; ++i)
			{
				//bound check
				if(i%x==(x-1))
				{

				}
				else if (array[i].value =="0" && array[i+1].value == "0")
				{

				}
				else if (array[i].age==false ||  array[i+1].age == false)
				{

				}
				else if (array[i].value == array[i+1].value)
				{
					MergeTile(i,i+1);
					action=true;
				}
				else if ((array[i].value == "0") && (array[i+1].value!="0"))
				{
					Swap(i,i+1);
					action=true;
				}
				else
				{

				}
			}
		}
	}
	void Right()
	{
		bool action = true;
		while(action)
		{
			action = false;
			for (int i = x*y-1; i >= 0; --i)
			{
				//bound check
				if(i%x==0)
				{
				}
				else if (array[i].value =="0" && array[i-1].value == "0")
				{
				}
				else if (array[i].age==false ||  array[i-1].age == false)
				{
				}
				else if (array[i].value == array[i-1].value)
				{
					MergeTile(i,i-1);
					action=true;
				}
				else if ((array[i].value == "0") && (array[i-1].value!="0"))
				{
					Swap(i,i-1);
					action=true;
				}
				else
				{
				}
			}
		}
	}
	void Swap(int first,int second)
	{
		array[first].value = array[second].value;
		array[second].value = "0";
	}
	bool Lose()
	{
		bool same = true;
		string * temp = new string[x*y];
		for (int i = 0; i<x*y; ++i)
		{
			temp[i]=array[i].value;
		}
		if(same)
		{
			Move(U);
			same = Compare(temp);
			Reassign(temp);
		}	
		if (same)
		{
			Move(D);
			same = Compare(temp);
			Reassign(temp);
		}
		if(same)
		{
			Move(L);
			same = Compare(temp);
			Reassign(temp);
		}	
		if (same)
		{
			Move(R);
			same = Compare(temp);
			Reassign(temp);
		}
		return same;
	}
	void Reassign(string tArr[])
	{
		for (int i =0; i <x*y; ++i)
		{
			array[i].value=tArr[i];
		}
	}
	bool Compare(string sArr[])
	{
		bool equivalent = true;
		for (int i = 0; i<x*y; ++i)
		{
			if (sArr[i]!=array[i].value)
			{
				equivalent=false;
			}
		}

		return equivalent;
	}
	bool Full()
	{
		bool full = true;
		for (int i =0; i<x*y; ++i)
		{
			if(array[i].value == "0")
			{
				full = false;
			}
		}
		return full;
	}
};

int main()
{

	bool functioning = true;
	char user;
	while (functioning)
	{
		Menu();
		cin.get(user);
		switch (user)
		{
			case 'p':
				Play();
				break;
			case 'h':
			HighScore();
				break;
			case 'q':
				functioning=false;
				break;
			default:
				cout << "Invalid Input\n";
		}
	}
	
	cout << "Okay Bye Bye";
	//pause
	cin.clear();
	fflush(stdin);
	cin.ignore();
	cin.get();

	return 0;
}

void Menu()
{
	cout << "Hey, welcome to a really lousy version of 2048\n"
	<<"If you want to play input (p)\n"
	<<"If you want to check out the highscores input (h)\n"
	<<"If you want to exit input (q)\n";
}
void Play()
{
	int sizeX;
	int sizeY;
	bool run = true;

	cout << "Enter size of array as X space Y:";
	cin >> sizeX >> sizeY;
	Board game(sizeX,sizeY);
	
	game.PrepBoard();
	game.PrintBoard();
	cout<< endl;
	while(run)
	{
		if(game.Lose())
		{
			run =false;
			cout << "Aww you lost\n";
			cin.ignore();
			cin.get();
		}
		else
		{
			game.Move(game.Arrows());
			// need this test or else game will loop forever and crash
			if(!game.Full())
			{
				game.AddTile();
			}
			game.PrintBoard();
			cout << endl;
		}
	}
}
void HighScore()
{

}
