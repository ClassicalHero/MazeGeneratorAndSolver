#include"AdjacencyList.h"
#include"Maze.h"

int main()
{
	int numVert;
	cout << "Enter an integer for square maze: ";
	cin >> numVert;
	Maze map(numVert);
	Graph maze(numVert*numVert);
	Edge temp;
	map.PrintMaze();
	for (int i = 0; i < map.Walls.size(); i++)
	{
		if (!map.Walls[i].up)
		{
			temp.Vertex1 = map.Walls[i].cell1;
			temp.Vertex2 = map.Walls[i].cell2;
			maze.addEdge(temp);
		}
	}
	DFS(maze, 0);
	system("pause");
}

Graph::Graph(int n)
{
	verticies = n;
	edges = 0;

	edgeList = vector<vector<Edge>>(n, vector<Edge>());
}
void Graph::addEdge(Edge e)
{
		edgeList[e.Vertex1].push_back(e);
		edgeList[e.Vertex2].push_back(e);
		edges++;
}
vector<Edge> Graph::getAdjacentList(int v)
{
	return edgeList[v];
}



int Graph::getNumEdges()
{
	return edges;
}
int Graph::getNumVerticies()
{
	return verticies;
}
bool Graph::isWeighted()
{
	return myWeighted;
}

Edge::Edge()
{
	Vertex1 = 0;
	Vertex2 = 0;
	weighted = 0;
	weight = 0;
}
Edge::Edge(int V1, int V2, double w)
{
	Vertex1 = V1;
	Vertex2 = V2;
	weight = w;
}

void DFS(Graph x, int start)
{
	bool * visited = new bool[x.getNumVerticies()];
	for (int i = 0; i < x.getNumVerticies(); i++)
	{
		visited[i] = false;
	}
	int end = x.getNumVerticies() - 1;
	bool finished = false;
	stack<int> path;
	RDFS(x, visited, start, end, finished, path);
	cout << "\nThis is the solution path:" << endl;
	while (!path.empty())
	{
		cout << "Vert: " << path.top() << endl;
		path.pop();
	}
}
void RDFS(Graph x, bool* visited, int start, int end, bool &finished, stack<int> &path)
{
	if (!finished)
	{
		pre_visit(start);
		int vert;
		vector<Edge> temp = x.getAdjacentList(start);
		visited[start] = true;
		for (int i = 0; i < temp.size() && finished != true; i++)
		{
			vert = temp[i].Vertex2;
			if (vert == end)
			{
				finished = true;
				pre_visit(end);
				path.push(end);
			}
			if (!visited[vert])
			{
				RDFS(x, visited, vert, end, finished, path);
			}
			else
			{
				vert = temp[i].Vertex1;
				if (vert == end)
				{
					finished = true;
					pre_visit(end);
					path.push(end);
				}
				if (!visited[vert])
				{
					RDFS(x, visited, vert, end, finished, path);
				}
			}
		}
		if (finished == true)
		{
			path.push(start);
		}
	}
}

void pre_visit(int vertex)
{
	cout << "Vertex: " << vertex << " ";
}


Maze::Maze(int N)
{
	grid = new Forest(N*N);
	CreateWalls(N);
	RandPerm();
	UpDownWalls();

}

void Maze::CreateWalls(int N)
{
	//N is the size of the maze without squaring
	wall temp;
	for (temp.cell1 = 0; temp.cell1 < N*N - 1; temp.cell1++)
	{
		temp.up = true;
		temp.cell2 = temp.cell1 + 1;
		if (temp.cell2 % N != 0)
			Walls.push_back(temp);

		temp.cell2 = temp.cell1 + N;
		if (temp.cell2 < N*N)
			Walls.push_back(temp);
	}
}

void Maze::RandPerm()
{
	int r;
	for (int i = 0; i < Walls.size(); i++)
	{
		r = rand() % (i + 1);
		swap(Walls[i], Walls[r]);
	}
}

void Maze::UpDownWalls()
{
	wall temp;
	for (int i = 0; i < Walls.size(); i++)
	{
		temp = Walls[i];
		if (grid->pcfind(temp.cell1) != grid->pcfind(temp.cell2))
		{
			Walls[i].up = false;
			grid->wunion(temp.cell1, temp.cell2);
		}
	}
}

void Maze::PrintMaze()
{
	for (int i = 0; i < Walls.size(); i++)
	{
		cout << "(" << Walls[i].cell1 << ", " << Walls[i].cell2 << ") - ";
		if (Walls[i].up == true)
		{
			cout << "UP" << endl;
		}
		else
		{
			cout << "DOWN" << endl;
		}
	}
}

Maze::~Maze()
{
	delete grid;
}


Forest::Forest(int n)
{
	for (int i = 0; i < n; i++)
	{
		parent[i] = -1;
	}
	els = n;
}


int Forest::pcfind(int leaf)
{
	if (parent[leaf] < 0)
	{
		return leaf;
	}
	return parent[leaf] = pcfind(parent[leaf]);
}

void Forest::wunion(int node1, int node2)
{
	int root1 = pcfind(node1);
	int root2 = pcfind(node2);
	if (root1 < root2)
	{
		parent[root1] = parent[root2] + parent[root1];
		parent[root2] = root1;
	}
	else
	{
		parent[root2] = parent[root2] + parent[root1];
		parent[root1] = root2;
	}
}

void Forest::printArray()
{
	cout << "Parents Array: ";
	for (int i = 0; i < els; i++)
	{
		cout << parent[i] << ", ";
	}
	cout << endl;
}