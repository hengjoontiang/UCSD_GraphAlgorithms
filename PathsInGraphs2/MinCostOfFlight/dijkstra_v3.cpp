#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <limits>
#include <map>


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
	//vector<vector<int> > adj;
	
	//try to use a map for storgae so that we still get a key
	vector<vector<std::pair<int,int>>> adj_cost;
	//vector<vector<int> > cost;
	vector<int> dist;
	vector<color> color_vec;
	
	vector<bool > IsVisited; //part of dfs
	
	Node(int numNodes,int numEdges) {
		this->numNodes = numNodes;
		this->numEdges = numEdges;
		adj_cost.resize(this->numNodes);
		dist.resize(this->numNodes);
		for (int u=0;u<this->numNodes;u++) 
			dist[u] = MAX_INT;
		IsVisited.resize(this->numNodes);
		color_vec.resize(this->numNodes);
		//cost.resize(this->numNodes);
		/*for (int u=0;u<this->numNodes;u++) 
			for (int v=0;v<this->numEdges;v++)
				cost[u].push_back(-1);*/
		resetIsVisitedFlag();
		resetDist();
	}
	//x,y is one-based - nodes
	//versus
	//array 0-based
	void addBiDirectionalLink(int x,int y,int w) {
		//adj[x-1].push_back(y-1);
		//adj[y-1].push_back(x-1);
		//cost[x-1][y-1] = w;
		//cost[y-1][x-1] = w;
		adj_cost[x-1].push_back(std::make_pair(y-1,w));
		adj_cost[y-1].push_back(std::make_pair(x-1,w));
	}
	void addUniDirectionalLink(int x,int y,int w) {
		//adj[x-1].push_back(y-1);
		//cost[x-1][y-1] = w;
		//adj[y-1].push_back(x-1);
		//reverse_adj[y-1].push_back(x-1);
		//adj_cost[x-1].push_back(std::make_pair(y-1,w));
		adj_cost[x-1].push_back(std::make_pair(y-1,w));
	}
	
	int getLinkedVectorSize(int x) {
		return adj_cost[x-1].size();
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
	/*
	void setCost(int x,int y, int value) {
		cost[x-1][y-1] = value;
	}
	int getCost(int x,int y) {
		return cost[x-1][y-1];
	}
	//returns 1-based node traversal
	int getPair(int x,int y) {
		return adj[x-1][y-1]+1;
	}*/
	/*
	int getWeight(int x,int y) {
		return adj_cost[x-1].find(y-1)->second;
	}
	std::map getMap(int x) {
		return adj_cost[x-1];
	}*/
	
	void printNode(){
		std::cout << "printNode"<<std::endl;
		for (int i=0;i<adj_cost.size();i++) {
			std::cout << "curr index=" << i+1 ;
			for (int x=0; x < adj_cost[i].size();x++){
				int nextIndex = adj_cost[i][x].first;
				int weight = adj_cost[i][x].second;
				std::cout << " nextIndex=" << nextIndex + 1 << " weight=" << weight;
			}
			std::cout << std::endl;
		}
	}
	
	void sortNode(){//will need to define a custom function for pair
		//std::cout << "printNode"<<std::endl;
		for (int i=0;i<adj_cost.size();i++) {
			std::sort(adj_cost[i].begin(),adj_cost[i].end());
		}
	}
	std::pair<int,int> getPair(int x,int y) {
		return adj_cost[x-1][y-1];
	}
	
	int getNextIndex(int x, int y) {
		return getPair(x,y).first + 1;
	}
	int getNextWeight(int x, int y) {
		return getPair(x,y).second ;
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
	int getIndexMinDist(){
		int MIN_NUM = MAX_INT;
		int indexWifMinValue=-1;
		for (int u=1;u<= getNumNodes();u++){
			//std::cout << "u=" << u << std::endl;
			//std::cout << "MIN_NUM=" << MIN_NUM << std::endl;
			//std::cout << "dist[u]=" << dist[u] << std::endl;
			//pluck only from those nodes that are still not considered
			if (getIsVisited(u)) continue; 
			if (getDist(u)< MIN_NUM) {
				MIN_NUM = getDist(u);
				indexWifMinValue = u;
				
			}
		}
		return indexWifMinValue;
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
  //initialize s
  node.setDist(s,0);
  //std::cout << "init s wif dist=0" << std::endl;
  
  
  //node.setIsVisited(s);
  
  //1-based 
  for (int index=1; index <= node.getNumNodes(); index++) {	
	  //guaranteed first time, we will find s with dist=0
	  int indexwifMinDist = node.getIndexMinDist();
	  //std::cout << "indexwifMinDist=" << indexwifMinDist << std::endl;
	  if (indexwifMinDist == -1) break; //no more nodes left
	  
	  //set IsVisited
	  node.setIsVisited(indexwifMinDist);
	  
	  //we will check for nodes to update dist
	  //i) not visited, i.e IsVisited = false
	  //ii) nodes linked to indexwifMinDist 
	  for (int adj_index= 1; adj_index <=  node.getLinkedVectorSize(indexwifMinDist) ; adj_index++ ) {
		       //std::pair<int,int> currNodeWeightPair = node.getPair(indexwifMinDist,adj_index);
			   int nextIndex=node.getNextIndex(indexwifMinDist,adj_index);
			   int curr_weight = node.getNextWeight(indexwifMinDist,adj_index);
			   if (node.getIsVisited(nextIndex)) continue; 
			   
			   //do an update should the new found distance found being lower than existing
			   if (node.getDist(indexwifMinDist) +curr_weight < node.getDist(nextIndex)) {
				   node.setDist(nextIndex, node.getDist(indexwifMinDist) +curr_weight);
			   }
	   }
	  
  }
  
  return node.getDist(t)==MAX_INT?-1:node.getDist(t);
 
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
  
  
  //std::cout << "sort node "<< std::endl;
  node.sortNode();
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
