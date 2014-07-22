#include <iostream>
#include <vector>
using namespace std;

#define NODES 16

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

int checkSymmetry(int * graph);

int main(){
	cout << "CheckSymmetry(8 node optimal) = " << checkSymmetry(&optimal8node[0][0]) << "\n";
	getchar();
	return 0;
}

int checkSymmetry(int * graph){
	int counter = 0;
	vector<int> neighbors;
	int symmetries = 0;
	bool nonSymmetryFound = false;
	for (int x = 0; x < NODES / 2; x++){
		for (int i = x; i < NODES / 2 + x; i++){
			neighbors.clear();
			for (int n = 0; n < NODES; n++){
				if (graph[NODES * i + n]) neighbors.push_back(n);
			}
			//v is the node opposite to
			int v = (NODES/2 + x + (NODES/2 + x - i) - 1) % NODES;
			nonSymmetryFound = false;
			for (int j = 0; j < 3; j++){
				int u = (NODES / 2 + x + (NODES / 2 + x - neighbors.at(j)) - 1) % NODES;
				if (graph[u + v * NODES] != 1){
					counter++;
					nonSymmetryFound = true;
					break; 
				}
			}
			if (nonSymmetryFound) break;
		}
		if(nonSymmetryFound == false) symmetries++;
	}
	cout << "Counter = " << counter << "\n";
	return symmetries;
}