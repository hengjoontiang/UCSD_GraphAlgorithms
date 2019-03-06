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
};
//use Node
int reach(Node &node, int x, int y) {
  //write your code here
  //start from destination
  bool hasRoute = false;
  
  
  
  //std::cout << "x=" << x<< std::endl;
  //std::cout << "y=" << y<< std::endl;
  //std::cout << "adj[x].size()=" << node.getLinkedVectorSize(x) << std::endl;
  //IsVisited[x] = true;
  //use 1-based node traversal
  for (int adj_index= 1; adj_index <=  node.getLinkedVectorSize(x) ; adj_index++ ) {
	  int nextIndex = node.getPair(x,adj_index);
	  if (node.getIsVisited(nextIndex)) continue;
	  
	  node.setIsVisited(nextIndex);
	  //std::cout << "nextIndex=" << nextIndex << std::endl;
	  
	  
	  if (nextIndex == y ) { //found
	    
		return 1;
	  }
	  else {
		//since we can reach nextIndex, now we will proceed to check if there is a link between nextIndex and y
		//std::cout << "nextIndex=" << nextIndex << std::endl;
	    hasRoute=reach(node,nextIndex, y);
	    if (hasRoute ) return 1;
	  }
  }
  
  
  return 0;
}
//once the node has already been checked, we should not check further
int reach(vector<bool> &IsVisited,vector<vector<int> > &adj, int x, int y) {
  //write your code here
  //start from destination
  bool hasRoute = false;
  bool IsReach = false;
  
  
  //std::cout << "x=" << x<< std::endl;
  //std::cout << "y=" << y<< std::endl;
  //std::cout << "adj[x].size()=" << adj[x].size() << std::endl;
  IsVisited[x] = true;
  for (int adj_index= 0; adj_index < adj[x].size() ; adj_index++ ) {
	  int nextIndex = adj[x][adj_index];
	  if (IsVisited[nextIndex] ) continue;
	  
	  IsVisited[nextIndex] = true;
	  //std::cout << "nextIndex=" << nextIndex << std::endl;
	  
	  
	  if (nextIndex == y ) { //found
	    
		return 1;
	  }
	  else {
		//since we can reach nextIndex, now we will proceed to check if there is a link between nextIndex and y
		//std::cout << "nextIndex=" << nextIndex << std::endl;
	    hasRoute=reach(IsVisited,adj,nextIndex, y);
	    if (hasRoute ) return 1;
	  }
  }
  
  
  return 0;
}
int main_body() {
  size_t n, m;
  std::cin >> n >> m;
  Node node(n);
  //vector<vector<int> > adj(n, vector<int>());
  //vector<bool> IsVisited(n);
  /*for (size_t i = 0; i < n; i++) {
	  IsVisited[i] = false;
  }*/
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
  
  int x, y;
  std::cin >> x >> y;
  std::cout << reach(node, x, y) << std::endl;;
  //std::cout << reach(IsVisited,adj, x, y) << std::endl;;
}
int main_body_bak() {
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  vector<bool> IsVisited(n);
  for (size_t i = 0; i < n; i++) {
	  IsVisited[i] = false;
  }
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x].push_back(y);
    adj[y].push_back(x);
  }
  int x, y;
  std::cin >> x >> y;
  //std::cout << reach(IsVisited,adj, x, y) << std::endl;;
  std::cout << reach(IsVisited,adj, x, y) << std::endl;;
}
void check_adj_vector() {
	size_t n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }
  
  //print out the adjacency vector
  //1-based
  std::cout << "adj.size()= " << adj.size()  << std::endl;
  for (int adj_index = 1; adj_index <= adj.size() ; adj_index++) {
	  std::cout << "adj_index-1= " << adj_index -1 << std::endl;
	  for (int adj_sub_index = 1; adj_sub_index <= adj[adj_index-1].size() ; adj_sub_index++) {
		  std::cout << "adj[adj_index-1].size() = " << adj[adj_index-1].size()   << std::endl;
		  std::cout << "adj_sub_index-1= " << adj_sub_index -1 << std::endl;
		  std::cout << "adj[adj_index-1][adj_sub_index-1] =" << adj[adj_index-1][adj_sub_index-1] << std::endl;
	  }
  }
}
int main_test() {
	check_adj_vector();
}

int main() {
	main_body();
}
