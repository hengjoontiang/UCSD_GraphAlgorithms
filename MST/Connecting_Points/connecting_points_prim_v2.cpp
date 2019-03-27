#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <queue>


using std::vector;
using std::queue;
using std::pair;
using std::sort;
using std::priority_queue;

const double MAX_DOUBLE = std::numeric_limits<double>::max();

struct Node {
	struct NodePoint {
		int nodeNum;
		int parent; // for linking
		int x_coord,y_coord;
		//double  dist;
		//vector<int> linkNodes;
		bool InQueue;
		
	};
	vector<NodePoint> vec_np;
	int numNodes;
	void addNodePoint(int nodeNum,NodePoint np) {
		//note that vector position is indicative of nodeNum
		vec_np[nodeNum] = np;
	}
	//vector<vector<int> > adj;
	
	//try to use a map for storgae so that we still get a key
	vector<vector<std::pair<int,int>>> adj_cost;
	//vector<vector<int> > cost;
	vector<double> dist;
	
	
	vector<bool > IsVisited; //part of dfs
	
	Node(int numNodes) {
		this->numNodes = numNodes;
		vec_np.resize(this->numNodes);
		
		dist.resize(this->numNodes);
		
		IsVisited.resize(this->numNodes);
		
		resetIsVisitedFlag();
		resetDist();
	}
	
	
	//returns 1-based nodeNum check to see if visited
	bool getIsVisited(int nodeNum){
		return IsVisited[nodeNum];
	}
	
	void setIsVisited(int nodeNum){
		IsVisited[nodeNum] = true;
	}
	double getDist(int x) {
		return dist[x];
	}
	void setDist(int x, double value) {
		dist[x] = value;
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
			dist[u] = MAX_DOUBLE;
	    }
	}
	int getIndexMinDist(){
	    double MIN_NUM = MAX_DOUBLE; 
		int indexWifMinValue=-1;
		for (int u=0;u< getNumNodes();u++){
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
	double getDistanceBetweenNodePoints(NodePoint & a, NodePoint & b) {
		int x_src, y_src, x_dst,y_dst;
		x_src = a.x_coord,y_src = a.y_coord;
		x_dst = b.x_coord,y_dst = b.y_coord;
		return sqrt((x_src - x_dst)*(x_src-x_dst) + (y_src-y_dst)*(y_src-y_dst));
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
double minimum_distance(Node & node) {
  //initialize s
  node.setDist(0,0);
  //std::cout << "init s wif dist=0" << std::endl;
  
  
  //node.setIsVisited(s);
  
  //1-based 
  for (int index=0; index < node.getNumNodes(); index++) {	
  //while (true){
	  //guaranteed first time, we will find s with dist=0
	  int indexwifMinDist = node.getIndexMinDist();
	  //std::cout << "indexwifMinDist=" << indexwifMinDist << std::endl;
	  if (indexwifMinDist == -1) break; //no more nodes left
	  
	  //set IsVisited
	  node.setIsVisited(indexwifMinDist);
	  
	  //we will check for nodes to update dist
	  //i) not visited, i.e IsVisited = false
	  //ii) nodes linked to indexwifMinDist 
	  for (int subindex=0; subindex < node.getNumNodes(); subindex++) {	
			   if (subindex == indexwifMinDist) continue; //skip if we are taking about the same node
		       
			   
			   if (node.getIsVisited(subindex)) continue; 
			   //std::cout << "subindex=" << subindex << std::endl;
			   double curr_weight = node.getDistanceBetweenNodePoints(node.vec_np[indexwifMinDist],node.vec_np[subindex]);
			   //std::cout << "curr_weight=" << curr_weight << std::endl;
			   
			   //do an update should the new found distance found being lower than existing
			   if (curr_weight < node.getDist(subindex)) {
				   node.setDist(subindex, curr_weight);
			   }
	   }
	  
  }
  double result = 0;
  for (int subindex=0; subindex < node.getNumNodes(); subindex++) {	
	  //std::cout << "node.getDist(" << subindex << ")=" << node.getDist(subindex) << std::endl;
	  result += node.getDist(subindex);
  }
  return result;
 
}
double minimum_distance_test(Node & node) {
  //initialize s
  node.setDist(0,0);
  std::cout << "init s wif dist=0" << std::endl;
  
  
  //node.setIsVisited(s);
  
  //1-based 
  for (int index=0; index < 2; index++) {	
	  std::cout << "index=" << index << std::endl;
	  //guaranteed first time, we will find s with dist=0
	  int indexwifMinDist = node.getIndexMinDist();
	  std::cout << "indexwifMinDist=" << indexwifMinDist << std::endl;
	  if (indexwifMinDist == -1) break; //no more nodes left
	  
	  //set IsVisited
	  node.setIsVisited(indexwifMinDist);
	  
	  //we will check for nodes to update dist
	  //i) not visited, i.e IsVisited = false
	  //ii) nodes linked to indexwifMinDist 
	  for (int subindex=0; subindex < node.getNumNodes(); subindex++) {	
			   if (subindex == indexwifMinDist) continue; //skip if we are taking about the same node
		       
			   
			   if (node.getIsVisited(subindex)) continue;
			   std::cout << "subindex=" << subindex << std::endl; 
			   double curr_weight = node.getDistanceBetweenNodePoints(node.vec_np[indexwifMinDist],node.vec_np[subindex]);
			   std::cout << "curr_weight=" << curr_weight << std::endl;
			   
			   //do an update should the new found distance found being lower than existing
			   if (curr_weight < node.getDist(subindex)) {
				   node.setDist(subindex, curr_weight);
			   }
	   }
	   
	   for (int subindex=0; subindex < node.getNumNodes(); subindex++) {	
			std::cout << "node.getDist(" << subindex << ")=" << node.getDist(subindex) << std::endl;
	   }
  
	  
  }
  //int indexwifMinDist = node.getIndexMinDist();
  
  double result = 0;
  std::cout<< "Computing result.." << std::endl;
  for (int subindex=0; subindex < node.getNumNodes(); subindex++) {	
	  std::cout << "node.getDist(" << subindex << ")=" << node.getDist(subindex) << std::endl;
	  result += node.getDist(subindex);
  }
  return result;
 
}
//incorrect #7/21
int main() {
 
  
  
  size_t n;
  std::cin >> n ;
  Node node(n);
  for (size_t i = 0; i < n; i++) {
    int x, y;
    std::cin >> x >> y ;
    //adj[x].push_back(y);
    //adj[y].push_back(x);
    //node.addUniDirectionalLink(x,y);
    //node.setCost(x,y,w);
    Node::NodePoint np;
    np.nodeNum = i;
    np.x_coord = x;
    np.y_coord = y;
    //node.distVec[i] = MAX_LONG;
    //np.dist = node.distVec[i];
    np.InQueue = false;
    np.parent = -1;
    node.addNodePoint(i,np);
  }
  
  
   //node.printNodePoints();
  std::cout << std::setprecision(10) << minimum_distance(node) << std::endl;
}
