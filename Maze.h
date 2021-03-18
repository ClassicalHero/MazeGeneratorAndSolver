#include"Forest.h"
#include<vector>
class Maze
{
public:
	struct wall
	{
		int cell1;
		int cell2;
		bool up;
	};
	void CreateWalls(int N);
	void RandPerm();
	void UpDownWalls();
	void PrintMaze();
	~Maze();
	Maze(int x);//ctor
	Forest * grid;
	vector<wall> Walls;
};


