#include <iostream>
#include <vector>
using namespace std;

int optimal8node[16][16] = { { 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1 },
							 { 1, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0 },
							 { 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0 },
							 { 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 },
							 { 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0 },
							 { 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0 },
							 { 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0 },
							 { 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1 },
							 { 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0 },
							 { 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0 },
							 { 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0 },
							 { 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1 },
							 { 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0 },
							 { 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0 },
							 { 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1 },
							 { 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0 } };

int checkSymmetry(int * graph, int nodes);
int checkNodeSplittingSymmetry(int * graph, int nodes);

int main(){
	cout << "CheckSymmetry(8 node optimal) = " << checkSymmetry(&optimal8node[0][0], 16) << "\n";
	cout << "CheckNodeSplittingSymmetries() = " << checkNodeSplittingSymmetry(&optimal8node[0][0], 16) << "\n";
	getchar();
	return 0;
}

int checkSymmetry(int * graph, int nodes){
	int counter = 0;
	vector<int> neighbors;
	int symmetries = 0;
	bool nonSymmetryFound = false;
	for (int x = 0; x < nodes / 2; x++){
		for (int i = x; i < nodes / 2 + x; i++){
			neighbors.clear();
			for (int n = 0; n < nodes; n++){
				if (graph[nodes * i + n]) neighbors.push_back(n);
			}
			//v is the node opposite to
			int v = (nodes/2 + x + (nodes/2 + x - i) - 1) % nodes;
			nonSymmetryFound = false;
			for (vector<int>::iterator j = neighbors.begin(); j != neighbors.end(); j++){
				int u = (nodes / 2 + x + (nodes / 2 + x - *j) - 1) % nodes;
				if (graph[u + v * nodes] != 1){
					nonSymmetryFound = true;
					break; 
				}
			}
			if (nonSymmetryFound) break;
		}
		if(nonSymmetryFound == false) symmetries++;
	}
	return symmetries;
}

int checkNodeSplittingSymmetry(int * graph, int nodes){
	int symmetries = 0;
	for (int x = 0; x < nodes / 2; x++){
		bool nonSymmetryFound = false;
		int y = (x + nodes / 2) % nodes;
		vector<int> neighbors;
		for (int i = 0; i < nodes; i++){
			if (graph[nodes * i + x]) neighbors.push_back(i);
		}
		while (neighbors.size() > 0){
			int n = neighbors.back();
			bool finished = true;
			for (vector<int>::iterator i = neighbors.begin(); i != neighbors.end(); i++){
				if (*i = n){
					finished = false;
					neighbors.erase(i);
					break;
				}
			}
			if (finished){
				nonSymmetryFound = true;
				break;
			}
		}
		while (neighbors.size() > 0){
			int n = neighbors.back();
			bool finished = true;
			for (vector<int>::iterator i = neighbors.begin(); i != neighbors.end(); i++){
				if (*i = n){
					finished = false;
					neighbors.erase(i);
					break;
				}
			}
			if (finished){
				nonSymmetryFound = true;
				break;
			}
		}
		for (int i = 0; i < nodes; i++){
			if (graph[nodes * i + y]) neighbors.push_back(i);
		}
		//in the case that the two nodes are symmetric to each other
		if (!nonSymmetryFound){
			//remove the nodes and search the remaining graph for symmetry
			int * trimmedGraph = (int*)malloc((nodes - 2)*(nodes - 2)*sizeof(int));
			int k = 0;
			for (int i = 0; i < nodes; i++){
				for (int j = 0; j < nodes; j++){
					if (i != x && i != y &&
						j != x && j != y) trimmedGraph[k++] = graph[nodes * i + j];
				}
			}
			if (checkSymmetry(trimmedGraph, nodes - 2)) symmetries++;
		}
	}
	return symmetries;
}