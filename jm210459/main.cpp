#include<iostream>
#include "graf.h"
#include<fstream>
#include<string>

int main() {
	while (true) {
		Graf graph;

		cout << "Unesite 'graf1' ili 'graf2' ili 'mojgraf'" << endl;
		string graf;
		cin >> graf;
		if (graf != "graf1" && graf != "graf2" && graf != "mojgraf") {
			cout << "NEPRAVILNO UNET ZAHTEV!" << endl;
			break;
		}
		if (graf == "graf1") {
			fstream reader;
			reader.open("graf1.txt", ios::in);
			int numNodes, numEdges;
			reader >> numNodes;
			reader >> numEdges;

			int i = 0;
			while (i < numNodes) {
				string node;
				reader >> node;
				graph.addNode(node);
				i++;
			}
			int j = 0;
			while (j < numEdges) {
				string node1;
				string node2;
				double w;
				reader >> node1 >> node2 >> w;
				graph.addEdge(node1, node2, w);
				j++;
			}
			reader.close();
		}
		else if (graf == "graf2") {
			fstream reader;
			reader.open("graf2.txt", ios::in);

			int numNodes, numEdges;
			reader >> numNodes;
			reader >> numEdges;

			int i = 0;
			while (i < numNodes) {
				string node;
				reader >> node;
				graph.addNode(node);
				i++;
			}
			int j = 0;
			while (j < numEdges) {
				string node1;
				string node2;
				double w;
				reader >> node1 >> node2 >> w;
				graph.addEdge(node1, node2, w);
				j++;
			}
			reader.close();
		}

		while (true) {

			cout << "Moguce su sledece operacije nad grafom(unesite odredjen broj operacije):\n";
			cout << "\t'1' --> Ispis grafa\n";
			cout << "\t'2' --> Dodavanje cvora u graf\n";
			cout << "\t'3' --> Izbacivanje cvora iz grafa\n";
			cout << "\t'4' --> Dodavanje grane izmedju dva cvora grafa\n";
			cout << "\t'5' --> Izbacivanje grane izmedju dva cvora grafa\n";
			cout << "\t'6' --> Nalazenje k najslicnijih reci zadatoj reci\n";
			cout << "\t'7' --> Nalazenje najkraceg puta od pocetne do krajnje reci\n";
			cout << "\t'8' --> Nalazenje svih reci koje su jako povezane sa zadatom recju\n";

			int in;
			cin >> in;

			switch (in) {
			case 1: cout << graph; break;
			case 2: {
				string node;
				cout << "Unesite rec: ";
				cin >> node;
				graph.addNode(node);
				break;
			}
			case 3: {
				string node;
				cout << "Unesite rec: ";
				cin >> node;
				graph.deleteNode(node);
				break;
			}
			case 4: {
				string node1, node2;
				double weight;
				cout << "Unesite prvu rec: ";
				cin >> node1;
				cout << "Unesite drugu rec: ";
				cin >> node2;
				cout << "Unesite slicnost: ";
				cin >> weight;
				graph.addEdge(node1, node2, weight);
				break;
			}
			case 5: {
				string node1, node2;
				double weight;
				cout << "Unesite prvu rec: ";
				cin >> node1;
				cout << "Unesite drugu rec: ";
				cin >> node2;
				graph.deleteEdge(node1, node2);
				break;
			}
			case 6: {
				cout << "Unesite rec: ";
				string node;
				cin >> node;
				cout << "Unesite koliko najslicnijih reci zelite: ";
				int k;
				cin >> k;
				graph.kMaxDistances(node, k);
				break;
			}
			case 7: {
				cout << "Unesite pocetnu rec: ";
				string node1;
				cin >> node1;
				cout << "Unesite krajnju rec: ";
				string node2;
				cin >> node2;
				graph.shortestPath(node1, node2);
				break;
			}
			case 8: {
				string node;
				cout << "Unesite pocetnu rec: ";
				cin >> node;
				graph.conn_comp(node);
				break;
			}
			default: {
				cout << "Niste uneli tacan broj";
				break;
			}
			}
			cout << endl<<"AKO ZELITE DA PREKINETE OBRADU NAD GRAFOM NAPISITE 'da'\n";
			string wantMore;
			cin >> wantMore;
			if (wantMore == "da") break;

		}
		cout << "AKO ZELITE DA PREKINETE PROGRAM NAPISITE 'da'\n";
		string next;
		cin >> next;
		if (next == "da") break;
	}
}