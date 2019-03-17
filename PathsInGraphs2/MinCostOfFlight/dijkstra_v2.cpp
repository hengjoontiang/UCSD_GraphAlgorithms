#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <limits>


using std::vector;
using std::queue;
using std::pair;
using std::sort;
using std::priority_queue;

const long MAX_INT = std::numeric_limits<int>::max();
enum color { COLOR_GRAY,COLOR_RED,COLOR_BLUE};
struct Node {
	
	int numNodes;
	int numEdges;
	vector<vector<int> > adj;
	vector<vector<int> > cost;
	vector<int> dist;
	vector<color> color_vec;
	
	vector<bool > IsVisited; //part of dfs
	
	Node(int numNodes,int numEdges) {
		this->numNodes = numNodes;
		this->numEdges = numEdges;
		adj.resize(this->numNodes);
		dist.resize(this->numNodes);
		for (int u=0;u<this->numNodes;u++) 
			dist[u] = MAX_INT;
		IsVisited.resize(this->numNodes);
		color_vec.resize(this->numNodes);
		cost.resize(this->numNodes);
		for (int u=0;u<this->numNodes;u++) 
			for (int v=0;v<this->numEdges;v++)
				cost[u].push_back(-1);
		resetIsVisitedFlag();
		resetDist();
	}
	//x,y is one-based - nodes
	//versus
	//array 0-based
	void addBiDirectionalLink(int x,int y,int w) {
		adj[x-1].push_back(y-1);
		adj[y-1].push_back(x-1);
		cost[x-1][y-1] = w;
		cost[y-1][x-1] = w;
	}
	void addUniDirectionalLink(int x,int y,int w) {
		adj[x-1].push_back(y-1);
		cost[x-1][y-1] = w;
		//adj[y-1].push_back(x-1);
		//reverse_adj[y-1].push_back(x-1);
	}
	
	int getLinkedVectorSize(int x) {
		return adj[x-1].size();
	}
	color getColor(int nodeNum){
		return color_vec[nodeNum-1];
	}
	void setColor(int nodeNum,color nodeColor) {
		color_vec[nodeNum-1] = nodeColor;
	}
	//returns 1-based nodeNum check to see if visited
	bool getIsVisited(int nodeNum){
		return IsVisited[nodeNum-1];
	}
	
	void setIsVisited(int nodeNum){
		IsVisited[nodeNum-1] = true;
	}
	int getDist(int x) {
		return dist[x-1];
	}
	void setDist(int x, int value) {
		dist[x-1] = value;
	}
	
	void setCost(int x,int y, int value) {
		cost[x-1][y-1] = value;
	}
	int getCost(int x,int y) {
		return cost[x-1][y-1];
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
	
	void resetIsVisitedFlag(){
		for (int u=0;u<this->numNodes;u++) {
			IsVisited[u] = false;
	    }
	}
	void resetDist(){
		for (int u=0;u<this->numNodes;u++) {
			dist[u] = MAX_INT;
	    }
	}
	
};
/*
 * Algorithm
1) Create a set sptSet (shortest path tree set) that keeps track of vertices included in shortest path tree, i.e., whose minimum distance from source is calculated and finalized. Initially, this set is empty.
2) Assign a distance value to all vertices in the input graph. Initialize all distance values as INFINITE. Assign distance value as 0 for the source vertex so that it is picked first.
3) While sptSet doesn’t include all vertices
….a) Pick a vertex u which is not there in sptSet and has minimum distance value.
….b) Include u to sptSet.
….c) Update distance value of all adjacent vertices of u. To update the distance values, iterate through all adjacent vertices. For every adjacent vertex v, if sum of distance value of u (from source) and weight of edge u-v, is less than the distance value of v, then update the distance value of v.
 * */
 //note that the algorithm gives the distance from s to all other nodes
 //after which we will just return the shortest distance from s to t
int distance(Node & node, int s, int t) {
  int dist = 0;
  //write your code here
  //write your code here
  int nodeSize = node.getNumNodes();
  
  //set distance to s itself to be zero
  node.setDist(s,0);
  
  std::queue<int> bfs_queue;
  
  bfs_queue.push(s);
  //node.setIsVisited(s);
  
  
  //start processing the queue
  while (!bfs_queue.empty()) {
		int current_index = bfs_queue.front();
	    bfs_queue.pop();
	    node.setIsVisited(current_index);
	    //std::cout <<" current_index=" << current_index << std::endl;
	    //std::cout << "color current_index= "<< node.getColor(current_index)  << std::endl;
	  
	    //process the immediate child nodes of current_index
	    //std::cout << "node.getLinkedVectorSize(current_index)=" << node.getLinkedVectorSize(current_index) << std::endl;
	    
	    
	    
	    for (int adj_index= 1; adj_index <=  node.getLinkedVectorSize(current_index) ; adj_index++ ) {
			int nextIndex = node.getPair(current_index,adj_index);
			//std::cout << "child index= " << nextIndex << std::endl;
			
			//std::cout << "color child_index= "<< node.getColor(nextIndex)  << std::endl;
	  
	  
			//use dist[current_index]==INF to check if itas already been visited
			if (!node.getIsVisited(nextIndex)) { //no color -> not processed as yet
				
				//enquing
				//std::cout << "enquing.."<<std::endl;
				//std::cout << "current_index=" << current_index << std::endl;
				//std::cout << "dist[current_index]="<< dist[current_index] << std::endl;
				//std::cout << "nextIndex=" << nextIndex << std::endl;
				bfs_queue.push(nextIndex);
				//dist[nextIndex] = dist[current_index] +1;
				
				//node.setIsVisited(nextIndex);//avoid top level
			}
			
			//regardless we will need to update the dist
			int prevDist = node.getDist(nextIndex);
			int currDist = node.getDist(current_index) + node.getCost(current_index,nextIndex);
			int minCostDist = std::min(prevDist,currDist);
			node.setDist(nextIndex,minCostDist);
        }//for (int adj_index= 1; adj_index <=  node.getLinkedVectorSize(current_index) ; adj_index++ ) {
  
  
	    
	  
  }//while (!bfs_queue.empty()) {
  
  
  //revised the distance to -1 should it remain at max
  return node.getDist(t)==MAX_INT?-1:node.getDist(t);
  //write your code her
 
}
//incorrect #7/21
int main() {
 
  
  
  size_t n, m;
  std::cin >> n >> m;
  Node node(n,m);
  for (size_t i = 0; i < m; i++) {
    int x, y, w;
    std::cin >> x >> y >> w;
    //adj[x].push_back(y);
    //adj[y].push_back(x);
    node.addUniDirectionalLink(x,y,w);
    //node.setCost(x,y,w);
  }
  
  
  
  //node.sortNode();
  //node.printNode();
  /*
   int current_index = 2;
   for (int adj_index= 1; adj_index <=  node.getLinkedVectorSize(current_index) ; adj_index++ ) {
			int nextIndex = node.getPair(current_index,adj_index);
			std::cout << "child index= " << nextIndex << std::endl;
	  
			
     }
  */
  
  
  int s, t;
  std::cin >> s >> t;
  int dist = distance(node, s, t);
  std::cout << dist;
}
