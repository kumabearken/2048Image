#pragma once

class Board {
public:
	int x;
	int y;
	int score = 0;
	int Tar;
	bool paused = true;
	bool bUp, bDown, bLeft, bRight = false;
	Tile* array = new Tile[1];
	Tile* testB = new Tile[1];
	Board(int x, int y): x(x), y(y), Tar(11) {
		//this->x = x;
		//this->y = y;
		array = new Tile[x * y];
		for (int i = 0; i < x * y; ++i) {
			array[i].value = 0;
			array[i].xPos = i % x;
			array[i].yPos = i / x;
			array[i].age = true;
		}
	}
	~Board() { delete[] array; }

	void PrintBoard(HDC &hdc, HDC &imageDC);
	void PrepBoard();
	void AddTile();
	string Arrows();
	void ResetAge();
	bool Move(string dir);
	bool Lose();
	void Reassign(int tArr[]);
	bool Compare(int sArr[]);
	bool Full();
	bool Win();
};



void Board::PrintBoard(HDC &hdc, HDC &imageDC) {
	int count = 0;
	for (int i = 0; i < y; ++i) {
		for (int j = 0; j < x; ++j) {
			BitBlt(hdc, 64*(j) , 32+(64*(i)), 64, 64, imageDC, 0, 64 * (array[count].value), SRCCOPY);
			++count;
		}
	}
}



void Board::PrepBoard() {
	int created = 0;
	while (created != 2) {
		AddTile();
		++created;
	}
}



void Board::AddTile() {
	srand(time(NULL));
	bool added = false;
	while (!added) {
		int evenOrOdd = rand() % 10;
		int ranInt = rand() % (x * y);
		if (evenOrOdd) {
			if (array[ranInt].value == 0) {
				array[ranInt].value = 1;
				array[ranInt].age = true;
				added = true;
			}
		}
		else { //odd
			if (array[ranInt].value == 0) {
				array[ranInt].value = 2;
				array[ranInt].age = true;
				added = true;
			}
		}
	}
}



string Board::Arrows() {

	char input;

	bool go = true;

	bool pause;

	string direction;

	while (go) {

		cin.get(input);

		switch (input) {

		case '8':

			if (!bUp) {

				direction = U;

				go = false;

			}

			break;

		case '2':

			if (!bDown) {

				direction = D;

				go = false;

			}

			break;

		case '4':

			if (!bLeft) {

				direction = L;

				go = false;

			}

			break;

		case '6':

			if (!bRight) {

				direction = R;

				go = false;

			}

			break;

		case 'q':

			pause = true;

			go = false;

			break;

		default:

			break;

		}

	}

	if (pause) { return "pause"; }

	return direction;

}



void Board::ResetAge() {

	for (int i = 0; i < x * y; ++i) {

		array[i].age = true;

	}

}



bool Board::Move(string dir) {

	int * temp = new int[x*y];

	for (int i = 0; i < x*y; ++i) {

		temp[i] = array[i].value;

	}

	paused = true;

	bool resQuit = true;

	if (dir == U) {
		for (int i = 0; i < x*y; ++i) {
			score += array->Upd(array, x, y, i);
		}
	}
	else if (dir == D) {
		for (int i = x * y - 1; i >= 0; --i) {
			score += array->Downd(array, x, y, i);
		}
	}
	else if (dir == L) {
		for (int i = 0; i < x*y; ++i) {
			score += array->Leftd(array, x, y, i);
		}
	}
	else if (dir == R) {
		for (int i = x * y - 1; i >= 0; --i) {
			score += array->Rightd(array, x, y, i);
		}
	}/*
	else if (dir == "pause") {
		char resOrQuit;
		cout << "You are paused!\n"
			<< "Enter 'p' to resume\n"
			<< "Enter 'q' to quit\n";
		cin >> resOrQuit;
		if (resOrQuit == 'q') { resQuit = false; }
		paused = false;
	}
	else { cout << "NOT VALID\n"; }*/

	if (!Compare(temp)) {
		AddTile();
	}
	ResetAge();
	return resQuit;
}



bool Board::Lose() {

	bool same = false;

	int currentScore = score;

	int * temp = new int[x*y];

	for (int i = 0; i < x*y; ++i) {

		temp[i] = array[i].value;

	}

	Move(U);

	bUp = Compare(temp);

	Reassign(temp);

	Move(D);

	bDown = Compare(temp);

	Reassign(temp);

	Move(L);

	bLeft = Compare(temp);

	Reassign(temp);

	Move(R);

	bRight = Compare(temp);

	Reassign(temp);

	score = currentScore;

	if (bUp && bDown && bLeft && bRight) { same = true; };

	return same;

}



void Board::Reassign(int tArr[]) {

	for (int i = 0; i < x*y; ++i) {

		array[i].value = tArr[i];

	}

}



bool Board::Compare(int sArr[]) {

	bool equivalent = true;

	for (int i = 0; i < x*y; ++i) {

		if (sArr[i] != array[i].value) {

			equivalent = false;

		}

	}

	return equivalent;

}

bool Board::Full() {
	bool full = true;
	for (int i = 0; i < x*y; ++i) {
		if (array[i].value == 0) {
			full = false;
		}
	}
	return full;
}

bool Board::Win() {
	bool Check = false;
	for (int i = 0; i < x*y; ++i) {
		if (array[i].value == Tar) {
			Check = true;
			Tar++;
		}
	}
	return Check;
}