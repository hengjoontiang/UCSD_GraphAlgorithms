#include <iostream>
#include <vector>
#include <algorithm>
using std::vector;
using std::pair;
using std::sort;

//modified by Joon Tiang 20190307 to accomodate unidrectional links and bidirectional links
//modified by Joon Tiang to include recursion vector<bool>
//this is to differentiate from IsVisited used for dfs traversal
//the recursion vector will record the current path for which we are checking for loops
//However SCC is more than cyclic, it needs to be cyclic, plus other conditions
//i.e cyclic definitely is SCC
struct Node {
	int numNodes;
	vector<vector<int> > adj;
	//differentiate between isVisited vs recursion
	//IsVisited refers to the actual visit of a node
	vector<bool > IsVisited; //part of dfs
	//recursion refers to the actual parent node being check for loop
	//based on child nodes, to check if it is currently under consideration
	vector<bool > recursion; //part of tracking which current loop we are checking
	Node(int numNodes) {
		this->numNodes = numNodes;
		adj.resize(this->numNodes);
		/*for (int i=0;i<adj,size();i++) {
			adj[i] = 
		}*/
		IsVisited.resize(this->numNodes);
		recursion.resize(this->numNodes);
		resetIsVisitedFlag();
		resetRecursionFlag();
	}
	//x,y is one-based - nodes
	//versus
	//array 0-based
	void addBiDirectionalLink(int x,int y) {
		adj[x-1].push_back(y-1);
		adj[y-1].push_back(x-1);
	}
	void addUniDirectionalLink(int x,int y) {
		adj[x-1].push_back(y-1);
		//adj[y-1].push_back(x-1);
	}
	int getLinkedVectorSize(int x) {
		return adj[x-1].size();
	}
	//returns 1-based nodeNum check to see if visited
	bool getIsVisited(int nodeNum){
		return IsVisited[nodeNum-1];
	}
	bool getRecursion(int nodeNum){
		return recursion[nodeNum-1];
	}
	void setIsVisited(int nodeNum){
		IsVisited[nodeNum-1] = true;
	}
	void setRecursion(int nodeNum){
		recursion[nodeNum-1] = true;
	}
	
	void resetCursion(int nodeNum) {
		recursion[nodeNum-1] = false;
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
	void resetRecursionFlag(){
		for (int u=0;u<this->numNodes;u++) {
			recursion[u] = false;
	    }
	}
	void resetIsVisitedFlag(){
		for (int u=0;u<this->numNodes;u++) {
			IsVisited[u] = false;
	    }
	}
};
int IsCyclicUtil(Node &node, int x) {
	int res = 0;
	//std::cout << "parent=" << x << std::endl;
	for (int adj_index= 1; adj_index <=  node.getLinkedVectorSize(x) ; adj_index++ ) {
	  int nextIndex = node.getPair(x,adj_index);
	  //std::cout << "child index= " << nextIndex << std::endl;
	  if (node.getRecursion(nextIndex)) res=1; //part of check of loop back
	  if (node.getIsVisited(nextIndex)) continue; //part of dfs
	  
	  node.setIsVisited(nextIndex);
	  node.setRecursion(nextIndex);
	  
	  //continue traversal
	  res = IsCyclicUtil(node,nextIndex);
	  
	  //if (res== 1) return res=1;
	  
	  node.resetCursion(nextIndex);
     }
     return res;
}
int number_of_strongly_connected_components(Node & node) {
  int result = 0;
  
  //1-based node traversal 
  for (int index = 1; index <= node.getNumNodes() ; index++ ){
  //write your code here
  
      //std::cout << "parent node=" << index << std::endl;
	  //check if current node has been visited
	  if (node.getIsVisited(index)) continue;
	  
	  
	  node.setIsVisited(index);
	  node.setRecursion(index);
	  
	  //continue traversal of child nodes for the current node
	  int res= IsCyclicUtil(node,index);
	  //if (res == 1) result++;
	  result++;
	  
	  //the node for the particular route
	  node.resetCursion(index);
  }
  
  
  return result;
}
//it is akin to finding the loops ; except that we do not stop upon finding a loop, 
//instead we will persist until all loops have been found
//the number of loops , including  standalones, amounts to the number of sccs

/*
 * Check case
 * 4 3
 * 1 2
 * 3 2
 * 4 3
 * 
 * our output:3
 * correct output:
 * 4
 * */
int main() {
  size_t n, m;
  std::cin >> n >> m;
  Node node(n);
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    //adj[x].push_back(y);
    //adj[y].push_back(x);
    node.addUniDirectionalLink(x,y);
  }
  //check nodeValues
  
  node.sortNode();
  //node.printNode();
  
  int numSCC = number_of_strongly_connected_components(node);
  std::cout << numSCC;
}
