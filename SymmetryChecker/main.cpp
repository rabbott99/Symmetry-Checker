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
							 { 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0 },
							 { 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0 },
							 { 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0 },
							 { 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1 },
							 { 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0 },
							 { 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0 },
							 { 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1 },
							 { 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0 } };

int checkSymmetry(int * graph, int nodes);

int main(){
	cout << "CheckSymmetry(8 node optimal) = " << checkSymmetry(&optimal8node[0][0], 16) << "\n";
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
			for (int j = 0; j < 3; j++){
				int u = (nodes / 2 + x + (nodes / 2 + x - neighbors.at(j)) - 1) % nodes;
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