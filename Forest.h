#include <iostream>
using namespace std;

class Forest
{
public:
	Forest(int n);//ctor
	void wunion(int node1, int node2);
	int pcfind(int leaf);
	void printArray();
	//int Find(int leaf);
private:
	int parent[40];
	int els;
};