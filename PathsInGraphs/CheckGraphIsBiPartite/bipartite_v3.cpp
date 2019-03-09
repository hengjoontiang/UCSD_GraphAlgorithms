#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <limits>


using std::vector;
using std::queue;
using std::pair;
using std::sort;


const long MAX_INT = std::numeric_limits<int>::max();
enum color { COLOR_GRAY,COLOR_RED,COLOR_BLUE};
struct Node {
	
	int numNodes;
	vector<vector<int> > adj;
	vector<int> dist;
	vector<color> color_vec;
	
	vector<bool > IsVisited; //part of dfs
	
	Node(int numNodes) {
		this->numNodes = numNodes;
		adj.resize(this->numNodes);
		dist.resize(this->numNodes);
		
		IsVisited.resize(this->numNodes);
		color_vec.resize(this->numNodes);
		resetIsVisitedFlag();
		
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
	
};


/*
 * Algorithm to check if a graph is Bipartite:
One approach is to check whether the graph is 2-colorable or not using backtracking algorithm m coloring problem.
Following is a simple algorithm to find out whether a given graph is Birpartite or not using Breadth First Search (BFS).
1. Assign RED color to the source vertex (putting into set U).
2. Color all the neighbors with BLUE color (putting into set V).
3. Color all neighbor’s neighbor with RED color (putting into set U).
4. This way, assign color to all vertices such that it satisfies all the constraints of m way coloring problem where m = 2.
5. While assigning colors, if we find a neighbor which is colored with same color as current vertex, then the graph cannot be colored with 2 vertices (or graph is not Bipartite) 
*/
int bipartite(Node & node) {
  int result = 1;
  //write your code here
  //write your code here
  int nodeSize = node.getNumNodes();
  
  
  std::queue<int> bfs_queue;
  
  
  for (int node_index= 1; node_index <=  node.getNumNodes() ; node_index++ ) { 
	  
	  if (node.getIsVisited(node_index) ) continue;
	  //place the starting node into the queue
      //find the min node
      node.setColor(node_index,COLOR_BLUE);
      bfs_queue.push(node_index);
      node.setIsVisited(node_index);
  
  
	  //start processing the queue
      while (!bfs_queue.empty()) {
		int current_index = bfs_queue.front();
	    bfs_queue.pop();
	  
	    //std::cout <<" current_index=" << current_index << std::endl;
	    //std::cout << "color current_index= "<< node.getColor(current_index)  << std::endl;
	  
	    //process the immediate child nodes of current_index
	    //std::cout << "node.getLinkedVectorSize(current_index)=" << node.getLinkedVectorSize(current_index) << std::endl;
	    for (int adj_index= 1; adj_index <=  node.getLinkedVectorSize(current_index) ; adj_index++ ) {
			int nextIndex = node.getPair(current_index,adj_index);
			//std::cout << "child index= " << nextIndex << std::endl;
			
			//std::cout << "color child_index= "<< node.getColor(nextIndex)  << std::endl;
	  
	  
			//use dist[current_index]==INF to check if itas already been visited
			if (node.getColor(nextIndex) == COLOR_GRAY) { //no color -> not processed as yet
				
				//enquing
				//std::cout << "enquing.."<<std::endl;
				//std::cout << "current_index=" << current_index << std::endl;
				//std::cout << "dist[current_index]="<< dist[current_index] << std::endl;
				//std::cout << "nextIndex=" << nextIndex << std::endl;
				bfs_queue.push(nextIndex);
				//dist[nextIndex] = dist[current_index] +1;
				color opp_color = (node.getColor(current_index)== COLOR_BLUE ? COLOR_RED : COLOR_BLUE);
				node.setColor(nextIndex,opp_color);
				node.setIsVisited(nextIndex);//avoid top level
			}else { //since there is already a color, we check the color of the child node vs the color of parent node
				//std::cout << "already an existing color "<< std::endl;
				if (node.getColor(current_index)== node.getColor(nextIndex) ){
					return result=0;
				}
			}
        }//for (int adj_index= 1; adj_index <=  node.getLinkedVectorSize(current_index) ; adj_index++ ) {
  
  
	    
	  
   }//while (!bfs_queue.empty()) {
  
  
   }//for (int node_index= 1; node_index <=  node.getNumNodes(node_index) ; node_index++ ) { 
  return result;
}
int bipartite_test_wo_for_loop(Node & node) {
  int result = 1;
  //write your code here
  //write your code here
  int nodeSize = node.getNumNodes();
  
  
  std::queue<int> bfs_queue;
  
  
  for (int node_index= 1; node_index <=  1 ; node_index++ ) { 
	  
	  if (node.getIsVisited(node_index) ) continue;
	  //place the starting node into the queue
      //find the min node
      node.setColor(node_index,COLOR_BLUE);
      bfs_queue.push(node_index);
      node.setIsVisited(node_index);
  
  
	  //start processing the queue
      while (!bfs_queue.empty()) {
		int current_index = bfs_queue.front();
	    bfs_queue.pop();
	  
	    //std::cout <<" current_index=" << current_index << std::endl;
	    //std::cout << "color current_index= "<< node.getColor(current_index)  << std::endl;
	  
	    //process the immediate child nodes of current_index
	    //std::cout << "node.getLinkedVectorSize(current_index)=" << node.getLinkedVectorSize(current_index) << std::endl;
	    for (int adj_index= 1; adj_index <=  node.getLinkedVectorSize(current_index) ; adj_index++ ) {
			int nextIndex = node.getPair(current_index,adj_index);
			//std::cout << "child index= " << nextIndex << std::endl;
			
			//std::cout << "color child_index= "<< node.getColor(nextIndex)  << std::endl;
	  
	  
			//use dist[current_index]==INF to check if itas already been visited
			if (node.getColor(nextIndex) == COLOR_GRAY) { //no color -> not processed as yet
				
				//enquing
				//std::cout << "enquing.."<<std::endl;
				//std::cout << "current_index=" << current_index << std::endl;
				//std::cout << "dist[current_index]="<< dist[current_index] << std::endl;
				//std::cout << "nextIndex=" << nextIndex << std::endl;
				bfs_queue.push(nextIndex);
				//dist[nextIndex] = dist[current_index] +1;
				color opp_color = (node.getColor(current_index)== COLOR_BLUE ? COLOR_RED : COLOR_BLUE);
				node.setColor(nextIndex,opp_color);
				node.setIsVisited(nextIndex);//avoid top level
			}else { //since there is already a color, we check the color of the child node vs the color of parent node
				//std::cout << "already an existing color "<< std::endl;
				if (node.getColor(current_index)== node.getColor(nextIndex) ){
					return result=0;
				}
			}
        }//for (int adj_index= 1; adj_index <=  node.getLinkedVectorSize(current_index) ; adj_index++ ) {
  
  
	    
	  
   }//while (!bfs_queue.empty()) {
  
  
   }//for (int node_index= 1; node_index <=  node.getNumNodes(node_index) ; node_index++ ) { 
  return result;
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
    
    //important we we use bipartite for bipartitle 
    node.addBiDirectionalLink(x,y);
  }
  //check nodeValues
  
  node.sortNode();
  std::cout << bipartite(node);
}
