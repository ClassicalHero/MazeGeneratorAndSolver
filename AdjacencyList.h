#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include<stack>

using namespace std;

class Edge
{
public:
	int Vertex1;
	int Vertex2;
	bool weighted;
	double weight;
	Edge();//ctor
	Edge::Edge(int V1, int V2, double w);
};
class Graph
{
public:
	vector<vector<Edge>> edgeList;
	bool myDirected;
	bool myWeighted;
	int verticies;
	int edges;
	Graph(int n);
	void addEdge(Edge e);
	vector<Edge> getAdjacentList(int v);
	int getNumVerticies();
	int getNumEdges();
	bool isWeighted();
};

void pre_visit(int vertex);
void DFS(Graph x, int start);
void RDFS(Graph x, bool* visited, int start, int end, bool &finished, stack<int> &path);