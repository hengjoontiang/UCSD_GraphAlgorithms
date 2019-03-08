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

//use Kosaraju algorithm
/*
1) Create an empty stack ‘S’ and do DFS traversal of a graph. In DFS traversal, after calling recursive DFS for adjacent vertices of a vertex, push the vertex to stack. In the above graph, if we start DFS from vertex 0, we get vertices in stack as 1, 2, 4, 3, 0.
2) Reverse directions of all arcs to obtain the transpose graph.
* //when reversed, SCC remain joined, however the various components becomes separated from each other
3) One by one pop a vertex from S while S is not empty. Let the popped vertex be ‘v’. Take v as source and do DFS (call DFSUtil(v)). The DFS starting from v prints strongly connected component of v. In the above example, we process vertices in order 0, 3, 4, 2, 1 (One by one popped from stack).
* //the topo order indciates the order of accessing the nodes for each SCC
* 
 * */
struct Node {
	int numNodes;
	vector<vector<int> > adj;
	vector<vector<int> > reverse_adj;
	//differentiate between isVisited vs recursion
	//IsVisited refers to the actual visit of a node
	vector<bool > IsVisited; //part of dfs
	vector<bool > IsReverseVisited; //part of dfs
	//recursion refers to the actual parent node being check for loop
	//based on child nodes, to check if it is currently under consideration
	vector<bool > recursion; //part of tracking which current loop we are checking
	Node(int numNodes) {
		this->numNodes = numNodes;
		adj.resize(this->numNodes);
		reverse_adj.resize(this->numNodes);
		/*for (int i=0;i<adj,size();i++) {
			adj[i] = 
		}*/
		IsVisited.resize(this->numNodes);
		IsReverseVisited.resize(this->numNodes);
		recursion.resize(this->numNodes);
		resetIsVisitedFlag();
		resetIsReverseVisitedFlag();
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
		reverse_adj[y-1].push_back(x-1);
	}
	int getLinkedVectorSize(int x) {
		return adj[x-1].size();
	}
	int getReverseLinkedVectorSize(int x) {
		return reverse_adj[x-1].size();
	}
	//returns 1-based nodeNum check to see if visited
	bool getIsVisited(int nodeNum){
		return IsVisited[nodeNum-1];
	}
	bool getIsReverseVisited(int nodeNum){
		return IsReverseVisited[nodeNum-1];
	}
	bool getRecursion(int nodeNum){
		return recursion[nodeNum-1];
	}
	void setIsVisited(int nodeNum){
		IsVisited[nodeNum-1] = true;
	}
	void setIsReverseVisited(int nodeNum){
		IsReverseVisited[nodeNum-1] = true;
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
	int getReversePair(int x,int y) {
		return reverse_adj[x-1][y-1]+1;
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
	void resetIsReverseVisitedFlag(){
		for (int u=0;u<this->numNodes;u++) {
			IsReverseVisited[u] = false;
	    }
	}
};
void dfs(Node & node,vector<int> &order, int x) {
  
	//std::cout << "parent=" << x << std::endl;
	for (int adj_index= 1; adj_index <=  node.getLinkedVectorSize(x) ; adj_index++ ) {
	  int nextIndex = node.getPair(x,adj_index);
	  //std::cout << "child index= " << nextIndex << std::endl;
	  
	  if (node.getIsVisited(nextIndex)) continue; //part of dfs
	  
	  node.setIsVisited(nextIndex);
	  
	  
	  //continue traversal
	  dfs(node,order,nextIndex);
	  
	  order.push_back(nextIndex);
     }
     
}   
void dfs_reverse(Node & node,int x) {
  
	//std::cout << "parent=" << x << std::endl;
	for (int adj_index= 1; adj_index <=  node.getReverseLinkedVectorSize(x) ; adj_index++ ) {
	  int nextIndex = node.getReversePair(x,adj_index);
	  //std::cout << "child index= " << nextIndex << std::endl;
	  
	  if (node.getIsReverseVisited(nextIndex)) continue; //part of dfs
	  
	  node.setIsReverseVisited(nextIndex);
	  
	  
	  //continue traversal
	  dfs_reverse(node,nextIndex);
	  
	  //order.push_back(nextIndex);
     }
     
}       

vector<int> toposort(Node & node) {
  vector<int> used(node.getNumNodes(), 0);
  vector<int> order;
  //write your code here
  
  for (int index = 1; index <= node.getNumNodes() ; index++ ){
  //write your code here
  
      //std::cout << "parent node=" << index << std::endl;
	  //check if current node has been visited
	  if (node.getIsVisited(index)) continue;
	  
	  
	  node.setIsVisited(index);
	  
	  
	  //continue traversal of child nodes for the current node
	  dfs(node,order, index);
	  
	  order.push_back(index);
  }
  std::reverse(order.begin(), order.end()); //since we are not using the stack, we will reverse it
  return order;
}

int number_of_strongly_connected_components(Node & node) {
  int result = 0;
  
  //1.do a toposort to obtain the vector
  vector<int> order = toposort(node);
  
  //2. reverse the links
  //note that on inception, it has already been created
  
  //3. do dfs on reverse graph based on the topo order 
  for (size_t i = 0; i < order.size(); i++) {
    //std::cout << order[i]<< " ";
    if (node.getIsReverseVisited(order[i])) continue;
    dfs_reverse(node,order[i]);
    result++;
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
