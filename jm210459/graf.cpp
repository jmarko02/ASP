#include "graf.h"
#include "queue.h"
#include<iomanip>


Graf::Graf(int lenght)
{
	nodes = new string[lenght];
	matrix = new double* [lenght];
	for (int i = 0; i < lenght; i++) {
		matrix[i] = new double[lenght];
		for (int j = 0; j < lenght; j++) {
			if (i == j) matrix[i][j] = 1;
			else matrix[i][j] = 0;
		}
	}
	maxNumOfNodes = lenght;
	numOfNodes = 0;
}

Graf::~Graf()
{
	clear();
}

void Graf::addNode(string word)
{
	if (nodeExists(word) == true) {
		cout << "Cvor " << word << " vec postoji u grafu" << endl;
		return;
	}
	if (numOfNodes == maxNumOfNodes) {
		extend();
	}
	nodes[numOfNodes++] = word;
}

void Graf::addEdge(string node1, string node2, double weight)
{
	if (weight >= 1 || weight <= 0) {
		cout << "Nemoguce dodati ivicu"<<endl;
		return;
	}
	int firstWordIndex = findIndex(node1);

	int secondWordIndex = findIndex(node2);

	if (firstWordIndex == -1 || secondWordIndex == -1) {
		cout << " Ne postoji takva ivica"<<endl;
		return;
	}
	matrix[firstWordIndex][secondWordIndex] = weight;
}

void Graf::deleteEdge(string node1, string node2)
{
	if (nodeExists(node1) == false || nodeExists(node2) == false) {
		cout <<"Cvor "<< node1 << " ili " << node2 << " ne postoji u grafu" << endl;
		return;
	}
	int firstWordIndex = findIndex(node1);
	
	int secondWordIndex = findIndex(node2);

	if (firstWordIndex == -1 || secondWordIndex == -1) {
		cout << " Ne postoji takva ivica" << endl;
		return;
	}
	matrix[firstWordIndex][secondWordIndex] = 0;
}

void Graf::deleteNode(string node)
{
	if (nodeExists(node) == false) {
		cout  << "Cvor " <<  node << " ne postoji u grafu" << endl;
		return;
	}
	int wordIndex = findIndex(node);

	for (int i = 0; i < numOfNodes; i++) {
		for (int j = 0; j < numOfNodes; j++) {
			if (i < wordIndex && j>wordIndex) {
				matrix[i][j - 1] = matrix[i][j];
			}
			else if (j<wordIndex && i>wordIndex) {
				matrix[i - 1][j] = matrix[i][j];
			}
			else if (j>wordIndex && i> wordIndex){
				matrix[i - 1][j - 1] = matrix[i][j];
			}
		}
	}

	for (int i = 0; i < numOfNodes; i++) {
		if (i > wordIndex) {
			nodes[i - 1] = nodes[i];
		}
	}
	numOfNodes--;
}



void Graf::clear()
{
	for (int i = 0; i < maxNumOfNodes; i++) {
		delete[] matrix[i];
	}
	delete[] matrix;
	matrix = nullptr;
	delete[] nodes;
}

void Graf::extend()
{
	string* tempNodes = new string[2 * maxNumOfNodes];

	double** tempMatrix = new double*[2 * maxNumOfNodes];
	for (int i = 0; i < 2*maxNumOfNodes; i++) {
		
		if (i < maxNumOfNodes) {
			tempNodes[i] = nodes[i];
		}

		tempMatrix[i] = new double[maxNumOfNodes * 2];
		for (int j = 0; j < 2*maxNumOfNodes; j++) {
			if (j < maxNumOfNodes && i<maxNumOfNodes) {
				tempMatrix[i][j] = matrix[i][j];
			}
			else if (i == j) {
				tempMatrix[i][j] = 1;

			}
			else tempMatrix[i][j] = 0;
		}
	}
	
	clear();
	maxNumOfNodes = 2 * maxNumOfNodes;
	matrix = tempMatrix;
	nodes = tempNodes;
}

int Graf::findIndex(string node) const
{
	int wordIndex = -1;
	for (int i = 0; i < numOfNodes; i++) {
		if (nodes[i] == node) {
			wordIndex = i;
			break;
		}
	}
	return wordIndex;
}

bool Graf::nodeExists(string node) const
{
	for (int i = 0; i < numOfNodes; i++) {
		if (nodes[i] == node) return true;
	}
	return false;
}

ostream& operator<<(ostream& os, const Graf& g)
{
	if (g.numOfNodes == 0) {
		return os << "Graf je prazan" << endl;
	}

	os << setw(16) << setfill(' ') << " ";
	for (int j = 0; j < g.numOfNodes * 7; j++) {
		os << "-";
	}
	os << endl;

	for (int i = 0; i < g.numOfNodes; i++) {

		os << left << setw(16) << setfill(' ') << g.nodes[i];
		os << "|";
		for (int j = 0; j < g.numOfNodes; j++) {

			os << fixed << setprecision(2) << g.matrix[i][j] << " | ";
		}

		os << endl;
		os << setw(16) << setfill(' ') << " ";
		for (int j = 0; j < g.numOfNodes * 7; j++) {

			os << "-";
		}
		os << endl;
	}
	return os;
}

void Graf::kMaxDistances(string node, int k)
{
	if (nodeExists(node) == false) {
		cout <<"Cvor " << node << " ne postoji u grafu" << endl;
		return;
	}
	double* distances = new double[numOfNodes];
	bool* done = new bool[numOfNodes];

	int sourceIndex = findIndex(node);

	for (int i = 0; i < numOfNodes; i++) {
		distances[i] = -1;
		done[i] = false;
	}


	distances[sourceIndex] = 1;

	for (int i = 0; i < numOfNodes; i++) {

		double max = -1;
		int index;
		for (int j = 0; j < numOfNodes; j++) {
			if (distances[j] >= max && !done[j]) {
				max = distances[j];
				index = j;
			}
		}

		done[index] = true;

		for (int j = 0; j < numOfNodes; j++) {
			if (!done[j] && distances[index] * matrix[index][j] > distances[j]) {
				distances[j] = distances[index] * matrix[index][j];

			}
		}
	}

	int numberOfDistances = 0;
	for (int i = 0; i < numOfNodes; i++) {
		if (distances[i] != 0 && distances[i] != 1) numberOfDistances++;
	}
	
	int j = 0;
	while(k > 0 && j < numOfNodes-1 && j < numberOfDistances) {
		double max = -1;
		int index;
		for (int i = 0; i < numOfNodes; i++) {
			if (distances[i] == 1) continue;
			if (max < distances[i]) {
				max = distances[i];
				index = i;
			}
		}
		
		cout <<left << setw(15) << setfill(' ') << nodes[index] << max << " " << endl;
		distances[index] = 0;
		j++;
		k--;
	}
	cout << endl;

	delete[] distances;
	delete[] done;
}




void Graf::conn_comp(string start) {
	if (nodeExists(start) == false) {
		cout << "Cvor" << start << " ne postoji u grafu" << endl;
		return;
	}
	int index = findIndex(start);

	bool* first = bfs(start, matrix);

	double** tMatrix = transpose(matrix);
	bool* second = bfs(start, tMatrix);

	cout << endl;
	for (int i = 0; i < numOfNodes; i++) {
		if (first[i] == 1 && second[i] == 1) {
			cout << nodes[i] << " ";
		}
	}
	cout << endl;

}

bool* Graf::bfs(string start, double** matrix) {
	int currentIndex = findIndex(start);

	Queue queue;
	queue.ins(currentIndex);

	bool* visit = new bool[numOfNodes];
	for (int i = 0; i < numOfNodes; i++) visit[i] = false;

	visit[currentIndex] = true;

	while (!queue.isEmpty()) {
		for (int i = 0; i < numOfNodes; i++) {
			if (matrix[currentIndex][i] > 0.00 && matrix[currentIndex][i] < 1.00 && visit[i] == false) {
				queue.ins(i);
				visit[i] = true;
			}
		}

		queue.del();
		currentIndex = queue.front();
	}

	return visit;
}

double** Graf::transpose(double** matrix) {
	double** tMatrix = new double* [numOfNodes];

	for (int i = 0; i < numOfNodes;i++) {
		tMatrix[i] = new double[numOfNodes];
	}

	for (int i = 0; i < numOfNodes;i++) {
		for (int j = 0; j < numOfNodes;j++) {
			tMatrix[i][j] = matrix[j][i];
		}
	}

	return tMatrix;
}

void Graf::shortestPath(string node1, string node2)
{
	if (nodeExists(node1) == false || nodeExists(node2) == false) {
		cout <<"Cvor " <<  node1 << " ili " << node2 << " ne postoji u grafu" << endl;
		return;
	}
	double* distances = new double[numOfNodes];
	bool* done = new bool[numOfNodes];
	int* parents = new int[numOfNodes];

	int sourceIndex = findIndex(node1);

	for (int i = 0; i < numOfNodes; i++) {
		distances[i] = 0;
		done[i] = false;
		parents[i] = -1;
	}

	distances[sourceIndex] = 1;
	parents[sourceIndex] = sourceIndex;

	for (int i = 0; i < numOfNodes; i++) {

		double max = -1;
		int index = -1;
		for (int j = 0; j < numOfNodes; j++) {
			if (distances[j] >= max && !done[j]) {
				max = distances[j];
				index = j;

			}
		}
		done[index] = true;

		for (int j = 0; j < numOfNodes; j++) {
			 
			if (!done[j] && distances[index] * matrix[index][j] > distances[j]) {

				distances[j] = distances[index] * matrix[index][j];
				parents[j] = index;
			}
		}
	}

	int destinationIndex = findIndex(node2);
	
	string* predecessors = new string[numOfNodes];
	for (int i = 0; i < numOfNodes; i++) {
		predecessors[i] = "";
	}
	predecessors[0] = nodes[destinationIndex];

	int j = 1;
	while (destinationIndex != sourceIndex && j < numOfNodes) {
		
		if (parents[destinationIndex] == -1) {
			cout << "Nema puta izmedju ta dva cvora" << endl;
			return;
		}
		destinationIndex = parents[destinationIndex];
		predecessors[j] = nodes[destinationIndex];
		j++;
	}
	

	for (int i = numOfNodes-1; i >= 0; i--) {
		if (predecessors[i] == "") continue;
		if (i != 0) {
			int index1 = findIndex(predecessors[i]);
			int index2 = findIndex(predecessors[i - 1]);
			cout << predecessors[i] << "-";
			cout << "(" << matrix[index1][index2] << ")->";
		}
		else {
			cout << predecessors[i];
		}
	}
	cout << endl;

	delete[] distances;
	delete[] done;
	delete[] parents;
	delete[] predecessors;
}


 