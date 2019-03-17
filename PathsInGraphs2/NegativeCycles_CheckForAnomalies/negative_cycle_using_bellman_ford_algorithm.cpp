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

//const int MAX_INT = std::numeric_limits<int>::max();
//cannot use max(), else wlll overflow when added
const int MAX_INT = 9999;
enum color { COLOR_GRAY,COLOR_RED,COLOR_BLUE};
struct Node {
	
	int numNodes;
	int numEdges;
	//vector<vector<int> > adj;
	
	//try to use a map for storgae so that we still get a key
	vector<vector<std::pair<int,int>>> adj_cost;
	//vector<vector<int> > cost;
	vector<int> dist;
	vector<vector<int>> dist_2d;
	vector<color> color_vec;
	
	vector<bool > IsVisited; //part of dfs
	
	Node(int numNodes,int numEdges) {
		this->numNodes = numNodes;
		this->numEdges = numEdges;
		adj_cost.resize(this->numNodes);
		dist.resize(this->numNodes);
		dist_2d.resize(this->numNodes);
		for (int u=0;u<this->numNodes;u++) 
			dist_2d[u].resize(numNodes);
		
		IsVisited.resize(this->numNodes);
		color_vec.resize(this->numNodes);
		//cost.resize(this->numNodes);
		/*for (int u=0;u<this->numNodes;u++) 
			for (int v=0;v<this->numEdges;v++)
				cost[u].push_back(-1);*/
		resetIsVisitedFlag();
		resetDist();
		resetDist2d();
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
		dist_2d[x-1][y-1] = w;
		adj_cost[y-1].push_back(std::make_pair(x-1,w));
		dist_2d[y-1][x-1] = w;
	}
	void addUniDirectionalLink(int x,int y,int w) {
		//adj[x-1].push_back(y-1);
		//cost[x-1][y-1] = w;
		//adj[y-1].push_back(x-1);
		//reverse_adj[y-1].push_back(x-1);
		//adj_cost[x-1].push_back(std::make_pair(y-1,w));
		adj_cost[x-1].push_back(std::make_pair(y-1,w));
		dist_2d[x-1][y-1] = w;
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
	
	//returns a reference to the location based on 1-based
	int & getDist2d(int u,int v) {
		return  dist_2d[u-1][v-1];
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
	void printDist2d(){
		std::cout << "printDist2d"<<std::endl;
		for (int i=1;i<=getNumNodes();i++) {
			std::cout << "curr index=" << i;
			for (int j=1;j<=getNumNodes();j++) {
				std::cout << " dist2d(=" << i << ")(" << j << ")=" << getDist2d(i,j);
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
	int getNumEdges() {
		return numEdges;
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
	void resetDist2d(){
		
		for (int u=0;u<this->numNodes;u++) 
			for (int v=0;v<this->numNodes;v++) {
				
				if (u==v) 
					dist_2d[u][v] = 0;
				else
					dist_2d[u][v] = MAX_INT;
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


int negative_cycle(Node & node) {
  //1.init the cost of all links to be equivalent to just the weight 
  //taken care by Node constructor during init of the nodes and links
  //otherwise set it to MAX
  
  //2.will need to go through all node links
  //i = start, k = intermediate ,j=end
  //due to the nature of accessing the nodes , we will do it directly
  for (int k=1;k<=node.getNumNodes()  ; k++) { //intermediate
	for (int i=1;i<=node.getNumNodes()  ; i++) { //start
	  for (int j=1;j<=node.getNumNodes()  ; j++) { //end
		      
			  if (node.getDist2d(i,k) + node.getDist2d(k,j) < node.getDist2d(i,j)) 
                        node.getDist2d(i,j) = node.getDist2d(i,k) + node.getDist2d(k,j);
			  
	  }
	}
  }

  for (int i=1;i<=node.getNumNodes()  ; i++) { //start
	  
        if (node.getDist2d(i,i) < 0)   
            return 1; 
  }
  //write your code here
  return 0;
}
/*
Check incorrect case
* Input:                                                                                                              
    10 9                                                                                                                
    1 2 1                                                                                                               
    5 6 1                                                                                                               
    6 7 1                                                                                                               
    8 9 1                                                                                                               
    9 10 1                                                                                                              
    3 4 1                                                                                                               
    7 8 1                                                                                                               
    4 5 1                                                                                                               
    2 3 1                                                                                                               
                                                                                                                        
                                                                                                                        
    Your output:                                                                                                        
    0                                                                                                                   
    Correct output:                                                                                                     
    0

*/
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
  //node.sortNode();
  //node.printNode();
  //prior
  //std::cout << "Dist2d prior "<< std::endl;
  
  //node.printDist2d();
  
  std::cout << negative_cycle(node);
  //prior
  //std::cout << "Dist2d after "<< std::endl;
  
  //node.printDist2d();
}
