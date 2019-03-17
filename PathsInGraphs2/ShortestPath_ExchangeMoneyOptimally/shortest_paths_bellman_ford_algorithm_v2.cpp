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
const long MAX_LONG = std::numeric_limits<long>::max();
enum color { COLOR_GRAY,COLOR_RED,COLOR_BLUE};
struct Node {
	
	int numNodes;
	int numEdges;
	//vector<vector<int> > adj;
	
	//try to use a map for storgae so that we still get a key
	vector<vector<std::pair<int,long>>> adj_cost;
	//vector<vector<int> > cost;
	vector<long> dist;
	vector<vector<long>> dist_2d;
	vector<color> color_vec;
	vector<bool> negative_cycle_indices;
	vector<int> negative_cycle_index;
	
	vector<bool > IsVisited; //part of dfs
	//vector<bool > recursion; //part of tracking which current loop we are checking
	
	Node(int numNodes,int numEdges) {
		this->numNodes = numNodes;
		this->numEdges = numEdges;
		adj_cost.resize(this->numNodes);
		negative_cycle_indices.resize(this->numNodes);
		dist.resize(this->numNodes);
		dist_2d.resize(this->numNodes);
		for (int u=0;u<this->numNodes;u++) 
			dist_2d[u].resize(numNodes);
		
		IsVisited.resize(this->numNodes);
		//recursion.resize(this->numNodes);
		color_vec.resize(this->numNodes);
		//cost.resize(this->numNodes);
		/*for (int u=0;u<this->numNodes;u++) 
			for (int v=0;v<this->numEdges;v++)
				cost[u].push_back(-1);*/
		resetIsVisitedFlag();
		//resetRecursionFlag();
		resetDist();
		resetDist2d();
		resetNegCycleIndices();
	}
	//x,y is one-based - nodes
	//versus
	//array 0-based
	void addBiDirectionalLink(int x,int y,long w) {
		//adj[x-1].push_back(y-1);
		//adj[y-1].push_back(x-1);
		//cost[x-1][y-1] = w;
		//cost[y-1][x-1] = w;
		adj_cost[x-1].push_back(std::make_pair(y-1,w));
		dist_2d[x-1][y-1] = w;
		adj_cost[y-1].push_back(std::make_pair(x-1,w));
		dist_2d[y-1][x-1] = w;
	}
	void addUniDirectionalLink(int x,int y,long w) {
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
	long & getDist(int x) {
		return dist[x-1];
	}
	void setDist(int x, long value) {
		dist[x-1] = value;
	}
	
	//returns a reference to the location based on 1-based
	long & getDist2d(int u,int v) {
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
	void printDist(){
		std::cout << "printDist"<<std::endl;
		for (int i=1;i<=getNumNodes();i++) {
			std::cout << "dist(" << i<<")="<<getDist(i)<<std::endl;
			
			
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
	long getNextWeight(int x, int y) {
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
			dist[u] = MAX_LONG;
	    }
	}
	void resetNegCycleIndices(){
		for (int u=0;u<this->numNodes;u++) {
			negative_cycle_indices[u] = false;
	    }
	}
	void setNegCycleIndices(int x) {
		negative_cycle_indices[x-1] = true;
	}
	bool getNegCycleIndices(int x) {
		return  negative_cycle_indices[x-1];
	}
	void resetDist2d(){
		
		for (int u=0;u<this->numNodes;u++) 
			for (int v=0;v<this->numNodes;v++) {
				
				if (u==v) 
					dist_2d[u][v] = 0;
				else
					dist_2d[u][v] = MAX_LONG;
			}
	}
	int getIndexMinDist(){
		long MIN_NUM = MAX_LONG;
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
	
	//x is 1-based
	void dfs_collect_nodes(int x) {
		setIsVisited(x);
		setNegCycleIndices(x);
		negative_cycle_index.push_back(x);
		
	    //std::cout << "parent node="<< x << std::endl;
		//these nodes will be infinite
		for (int y=1; y <= getLinkedVectorSize(x);y++){
			int nextIndex = getNextIndex(x,y);
			//std::cout << "next node="<< nextIndex << std::endl;
			if (getIsVisited(nextIndex)) continue;
			//setIsVisited(nextIndex);
				
			//invoke dfs
			dfs_collect_nodes(nextIndex);
		}
	}
};

//The bellman ford algorithm will attempt to recompute dist(v) , based on dist(u), and cost(u,v)
//the key idea is to repeatedly update dist(v), should we find a lower value, effectively finding the min dist(v)
/*
void shortest_paths(vector<vector<int> > &adj, vector<vector<int> > &cost, int s, vector<long long> &distance, vector<int> &reachable, vector<int> &shortest) {
  //write your code here
}*/
void shortest_paths(Node & node, int s) {
  //write your code here
  //1.init the cost of all links to be equivalent to just the weight 
  //taken care by Node constructor during init of the nodes and links
  //otherwise set it to MAX
  
  //starting point is s
  //we will init dist(s) = 0
  node.getDist(s) = 0;
  
  //do one round based on the starting node
  /*
  for (int y=1; y <= node.getLinkedVectorSize(s);y++){
			int nextIndex = node.getNextIndex(s,y);
			std::cout << "next index from s=" << nextIndex << std::endl;
			std::cout << "path dist=" << node.getDist2d(s,nextIndex) << std::endl;
			node.getDist(nextIndex) = node.getDist2d(s,nextIndex);
  }*/
  
  //2.will need to go through all node links
  //i = start, j=end
  //due to the nature of accessing the nodes , we will do it directly
  
  //check node 4, and link 4,1
 //std::cout << "Node s=" <<  node.getDist(s) << std::endl;
  //check links connected to s
  /*for (int y=1; y <= node.getLinkedVectorSize(s);y++){
			int nextIndex = node.getNextIndex(s,y);
			std::cout << "link s to " << nextIndex << " =" << node.getDist2d(s,nextIndex) << std::endl;
  }*/
  
    for (int k=1;k<=node.getNumNodes()  ; k++) {
	for (int i=1;i<=node.getNumNodes()  ; i++) { //start
	  for (int j=1;j<=node.getNumNodes()  ; j++) { //end
		      if (i==j) continue;
		      //std::cout << "i=" << i << std::endl;
		      //std::cout << "j=" << j << std::endl;
		      //std::cout << "node.getDist(i)=" << node.getDist(i) << std::endl;
		      //std::cout << "node.getDist(j)=" << node.getDist(j) << std::endl;
		      //std::cout << "node.getDist2d(i,j)=" << node.getDist2d(i,j) << std::endl;
		      if (node.getDist(i) != MAX_LONG && node.getDist2d(i,j) != MAX_LONG) {
				if (node.getDist(i) + node.getDist2d(i,j) < node.getDist(j)) 
                        node.getDist(j) = node.getDist(i) + node.getDist2d(i,j);
			  }
	  }
	}
    }
	
    //second time to find nodes of which infinite arbitrage possible
    for (int i=1;i<=node.getNumNodes()  ; i++) { //start
	  for (int j=1;j<=node.getNumNodes()  ; j++) { //end
		      if (i==j) continue;
		      if (node.getDist(i) != MAX_LONG && node.getDist2d(i,j) != MAX_LONG) {
				if (node.getDist(i) + node.getDist2d(i,j) < node.getDist(j)) 
                        //negative_cycle_indices.push_back(i);
                        //negative_cycle_indices.push_back(j);
                        //do a bfs on node j
                       //node.negative_cycle_indices.push_back(j);
                        node.dfs_collect_nodes(j);
                        
                        
			  }
	  }
	}    
	
}

//couple with shortest paths, we will also need to check for negative cycles
//first we will just check for loops
//for each loop, we will check dist values remain , else it means that a nagative loop exists


/*
 * case 4 wrong
 * */
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
  int s;
  std::cin >> s;
  
 // node.printNode();
  
  shortest_paths(node,s);
  //node.printDist();
  /*
  std::cout<<"negative cycle index .." << std::endl;
  for (int i=0;i<node.negative_cycle_index.size(); i++)
  {
	  std::cout << node.negative_cycle_index[i] << std::endl;
  }*/
  
  for (int i = 1; i <= node.getNumNodes(); i++) {
	long dist = node.getDist(i);
	//std::cout << "node="<< i << std::endl;
	//std::cout << "dist="<< dist << std::endl;
	bool IsReach = ( (dist == MAX_LONG) ? false : true );
	//std::cout << "IsReach="<< IsReach << std::endl;
	bool IsNegCycle = node.getNegCycleIndices(i);
	//std::cout << "IsNegCycle="<< IsNegCycle << std::endl;
    if (!IsReach) {
      std::cout << "*\n";
    } else if (IsNegCycle) {
      std::cout << "-\n";
    } else {
      std::cout <<  dist << "\n";
    }
  }
}
