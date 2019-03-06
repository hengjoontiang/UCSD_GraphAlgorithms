#include <iostream>
#include <vector>
#include <algorithm>
using std::vector;
using std::pair;
using std::sort;
struct Node {
	int numNodes;
	vector<vector<int> > adj;
	vector<bool > IsVisited;
	Node(int numNodes) {
		this->numNodes = numNodes;
		adj.resize(this->numNodes);
		/*for (int i=0;i<adj,size();i++) {
			adj[i] = 
		}*/
		IsVisited.resize(this->numNodes);
	}
	//x,y is one-based - nodes
	//versus
	//array 0-based
	void addPair(int x,int y) {
		adj[x-1].push_back(y-1);
		adj[y-1].push_back(x-1);
	}
	int getLinkedVectorSize(int x) {
		return adj[x-1].size();
	}
	//returns 1-based nodeNum check to see if visited
	bool getIsVisited(int nodeNum){
		return IsVisited[nodeNum-1];
	}
	void setIsVisited(int nodeNum){
		IsVisited[nodeNum-1] = true;
	}
	//returns 1-based node traversal
	int getPair(int x,int y) {
		return adj[x-1][y-1]+1;
	}
	void printNode(){
		std::cout << "printNode"<<std::endl;
		for (int i=0;i<adj.size();i++) {
			std::cout <<"row "<< i << " ";
			for (int j=0;j<adj[i].size();j++) {
				std::cout << adj[i][j] << " ";
			}
			std::cout <<std::endl;
		}
	}
	void sortNode(){
		//std::cout << "printNode"<<std::endl;
		for (int i=0;i<adj.size();i++) {
			std::sort(adj[i].begin(),adj[i].end());
		}
	}
	int getNumNodes() {
		return numNodes;
	}
};
void dfsutil(Node &node, int x) {
	for (int adj_index= 1; adj_index <=  node.getLinkedVectorSize(x) ; adj_index++ ) {
	  int nextIndex = node.getPair(x,adj_index);
	  if (node.getIsVisited(nextIndex)) continue;
	  
	  node.setIsVisited(nextIndex);
	  
	  //continue traversal
	  dfsutil(node,nextIndex);
  }
}
int number_of_components(Node &node) {
  int res = 0;
  //1-based node traversal 
  for (int index = 1; index <= node.getNumNodes() ; index++ ){
  //write your code here
  
  
	  //check if current node has been visited
	  if (node.getIsVisited(index)) continue;
	  
	  //add the number of components
	  res++;
	  
	  //continue traversal of child nodes for the current node
	  dfsutil(node,index);
  }
  
  return res;
}
int number_of_components_bak(vector<vector<int> > &adj) {
  int res = 0;
  //write your code here
  return res;
}

int main() {
  size_t n, m;
  std::cin >> n >> m;
  Node node(n);
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    //adj[x].push_back(y);
    //adj[y].push_back(x);
    node.addPair(x,y);
  }
  //check nodeValues
  //node.printNode();
  node.sortNode();
  
  std::cout << number_of_components(node);
}
