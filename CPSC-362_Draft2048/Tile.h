#pragma once

class Tile {

public:
	int xPos = 0;
	int yPos = 0;
	int value = 0;
	bool age = false;

	Tile(int value, int xPos, int yPos, bool age) {
		this->value = value;
		this->xPos = xPos;
		this->yPos = yPos;
		this->age = age;
	}

	Tile() {
		xPos = 0;
		yPos = 0;
		value = 0;
		age = false;
	}

	int Upd(Tile* manip, int bX, int bY, int ind);
	int Downd(Tile* manip, int bX, int bY, int ind);
	int Leftd(Tile* manip, int bX, int bY, int ind);
	int Rightd(Tile* manip, int bX, int bY, int ind);
	int Merge(Tile* a, Tile* b);
	void Collide(Tile* a, Tile* b);
};


int Tile::Upd(Tile* manip, int bX, int bY, int ind) {
	int row = manip[ind].yPos;
	int col = manip[ind].xPos;
	int moveScore = 0;
	int state = manip[ind].value;
	if (row == 0) {
		return moveScore;
	}
	else if (state == 0) {
		return moveScore;
	}
	else if (state != 0) {
		for (int i = row - 1; i >= 0; --i) {
			if ((manip[i*bX + col].value == state) && (manip[i*bX + col].age == false)) {
				Collide(&manip[(i + 1)*bX + col], &manip[row*bX + col]);
				break;
			}
			else if (manip[i*bX + col].value == state) {
				moveScore += Merge(&manip[i*bX + col], &manip[row*bX + col]);
				break;
			}
			else if ((manip[i*bX + col].value != manip[row*bX + col].value) && (manip[i*bX + col].value != 0) && (i < row)) {
				Collide(&manip[(i + 1)*bX + col], &manip[row*bX + col]);
				break;
			}
			else if (i == 0) {
				Collide(&manip[i*bX + col], &manip[row*bX + col]);
				break;
			}
			else {
				//do something?
			}
		}
	}
	else {
		return moveScore;
	}
	return moveScore;
}



int Tile::Downd(Tile* manip, int bX, int bY, int ind) {
	int row = manip[ind].yPos;
	int col = manip[ind].xPos;
	int state = manip[ind].value;
	int moveScore = 0;
	if (row == bY - 1) {
		return moveScore;
	}
	else if (state == 0) {
		return moveScore;
	}
	else if (state != 0) {
		for (int i = row + 1; i < bY; ++i) {
			if ((manip[i*bX + col].value == state) && (manip[i*bX + col].age == false)) {
				Collide(&manip[(i - 1)*bX + col], &manip[row*bX + col]);
				break;
			}
			else if (manip[(i*bX) + col].value == state) {
				moveScore += Merge(&manip[i*bX + col], &manip[row*bX + col]);
				break;
			}
			else if ((manip[i*bX + col].value != manip[row*bX + col].value) && (manip[i*bX + col].value != 0) && (i > row)) {
				Collide(&manip[(i - 1)*bX + col], &manip[row*bX + col]);
				break;
			}
			else if (i == bY - 1) {
				Collide(&manip[i*bX + col], &manip[row*bX + col]);
				break;
			}
			else {
				//do something?
			}
		}
	}
	else {
		return moveScore;
	}
	return moveScore;
}



int Tile::Leftd(Tile* manip, int bX, int bY, int ind) {
	int row = manip[ind].yPos;
	int col = manip[ind].xPos;
	int state = manip[ind].value;
	int moveScore = 0;
	if (col == 0) {
		return moveScore;
	}
	else if (state == 0) {
		return moveScore;
	}
	else if (state != 0) {
		for (int i = col - 1; i >= 0; --i) {
			if ((manip[row*bX + i].value == state) && (manip[row*bX + i].age == false)) {
				Collide(&manip[row*bX + i + 1], &manip[row*bX + col]);
				break;
			}
			else if (manip[row*bX + i].value == state) {
				moveScore += Merge(&manip[row*bX + i], &manip[row*bX + col]);
				break;
			}
			else if ((manip[row*bX + i].value != state)
				&& (manip[row*bX + i].value != 0) && (i < col)) {
				Collide(&manip[row*bX + i + 1], &manip[row*bX + col]);
				break;
			}
			else if (i == 0) {
				Collide(&manip[row*bX + i], &manip[row*bX + col]);
				break;
			}
			else {
				//do something?
			}
		}
	}
	else {
		return moveScore;
	}
	return moveScore;
}

int Tile::Rightd(Tile* manip, int bX, int bY, int ind) {
	int row = manip[ind].yPos;
	int col = manip[ind].xPos;
	int state = manip[ind].value;
	int moveScore = 0;
	if (col == bX - 1) {
		return moveScore;
	}
	else if (state == 0) {
		return moveScore;
	}
	else if (state != 0) {
		for (int i = col + 1; i < bX; ++i) {
			if ((manip[row*bX + i].value == state) && (manip[row*bX + i].age == false)) {
				Collide(&manip[row*bX + i - 1], &manip[row*bX + col]);
				break;
			}
			else if (manip[row*bX + i].value == state) {
				moveScore += Merge(&manip[row*bX + i], &manip[row*bX + col]);
				break;
			}
			else if ((manip[row*bX + i].value != state)
				&& (manip[row*bX + i].value != 0) && (i > col)) {
				Collide(&manip[row*bX + i - 1], &manip[row*bX + col]);
				break;
			}
			else if (i == bX - 1) {
				Collide(&manip[row*bX + i], &manip[row*bX + col]);
				break;
			}
			else {
				//do something
			}
		}
	}
	else {
		return moveScore;
	}
	return moveScore;
}



int Tile::Merge(Tile* a, Tile* b) {
	if ((a->age == true) && (b->age == true)) {
		int tmp = a->value;
		++tmp;
		a->value = tmp;
		b->value = 0;
		a->age = false;
		return pow(2,tmp);
	}
	return 0;
}



void Tile::Collide(Tile* a, Tile* b) {
	//if a = b then by storing b then writing b then writing a with the stored value nothing happens.
	//writing b to a then 0 to b would delete blanks when a = b
	int tmp = b->value;
	b->value = 0;
	a->value = tmp;
}