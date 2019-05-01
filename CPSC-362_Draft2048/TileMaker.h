#pragma once
class TileMaker
{
	int value;
	int weight;
	Tile* TileList = new Tile[1];
	TileMaker(int size)
	{
		TileList = new Tile[size];
	}
	void Add(int index, int val, int wgt, int x, int y);
};

void TileMaker::Add(int index, int val, int wgt, int x, int y)
{
	TileMaker::value = val;
	TileMaker::weight = wgt;
	TileList[index].value = val;
}

class TileMakerShadow : public TileMaker
{

};