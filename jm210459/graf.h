#ifndef _graf_h_
#define _graf_h_
#include<iostream>
#include<string>
using namespace std;

class Graf {

public:

	
	Graf(int lenght = 5);
	Graf(const Graf& g) = delete;
	Graf& operator=(const Graf& g) = delete;
	Graf(Graf&& g) = delete;
	Graf& operator=(Graf&& g) = delete;

	~Graf();

	void addNode(string n);
	void addEdge(string node1, string node2, double weight);

	void deleteEdge(string node1, string node2);
	void deleteNode(string node);

	void kMaxDistances(string node, int k);
	void shortestPath(string node1,string node2);

	friend ostream& operator<<(ostream& os, const Graf& g);

	void conn_comp(string start);
	double** transpose(double** matrix);
	bool* bfs(string start, double** matrix);


private:
	
	double** matrix= nullptr;
	
	string *nodes = nullptr;
	
	int numOfNodes = 0;
	int maxNumOfNodes = 0;

	void clear();
	void extend();
	
	int findIndex(string node)const;	
	bool nodeExists(string node) const;

};


#endif 
