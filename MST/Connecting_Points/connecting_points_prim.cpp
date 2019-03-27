#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <queue>
/*
 * To enusre that the node dist is being updated, we either
 * use 
 * 1. a reference to the nodes for the priority queue
 * OR
 * 2. use a vector to store the dist, i.e dist vector, then we will pass a reference into the node
 * 
 * */
using std::vector;
using std::queue;
using std::pair;
using std::sort;
using std::priority_queue;
/*
 * 
 * This algorithm is very similar to dijstrstra's algorithm
 * 
 * for all u belongs to V:
 * 		cost[u]<-- INF, parent[u] <-- nil
 * pick any initial vertext u0
 * cost[u0] = 0
 * PrioQ <-- MakeQueue(V) { priority is cost }
 * while PrioQ is not empty:
 * 	v <-- ExtractMin(PrioQ)
 *  for all {v,z} belonging to E:
 * 		if z belonging to PrioQ and cost[z] > w(v,z) :
 * 			cost[z] <-- w(v,z), parent[z] <-- v
 * 			ChangePriority(PrioQ,z,cost[z]) //by popping and pushing back the same element
 * */
const long MAX_LONG = std::numeric_limits<long>::max();



struct Node {
	struct NodePoint {
		int nodeNum;
		int parent; // for linking
		int x_coord,y_coord;
		double  dist;
		//vector<int> linkNodes;
		bool InQueue;
		
	};
	
	vector<double>  distVec;
	//priority queue based on the bool operator
	struct compare {
		//to return based on ascending sequence
	bool operator()(const NodePoint & a,const NodePoint & b) {
		return a.dist > b.dist;
	}
	};
	int numNodes;
	priority_queue<NodePoint, vector<NodePoint >,compare> pq_np;
	vector<NodePoint> vec_np;
	
	Node(int numNodes) {
		this->numNodes = numNodes;
		vec_np.resize(numNodes);
		distVec.resize(numNodes);
	}
	void addNodePoint(int nodeNum,NodePoint np) {
		//note that vector position is indicative of nodeNum
		vec_np[nodeNum] = np;
	}
	void printNodePoints() {
		for (int u=0;u<numNodes;u++) {
			NodePoint np = vec_np[u];
			std::cout << "nodeNum=" << np.nodeNum << std::endl;
			std::cout << "parent=" << np.parent << std::endl;
			std::cout << "x_coord=" << np.x_coord << std::endl;
			std::cout << "y_coord=" << np.y_coord << std::endl;
			std::cout << "dist=" << np.dist << std::endl;
			std::cout << "InQueue=" << np.InQueue << std::endl;
		}
	}
	//x,y is one-based - nodes
	//versus
	//array 0-based
	void addBiDirectionalLink(int x,int y) {
		
	}
	void addUniDirectionalLink(int x,int y) {
		
	}
	double getDistanceBetweenNodePoints(NodePoint & a, NodePoint & b) {
		int x_src, y_src, x_dst,y_dst;
		x_src = a.x_coord,y_src = a.y_coord;
		x_dst = b.x_coord,y_dst = b.y_coord;
		return sqrt((x_src - x_dst)*(x_src-x_dst) + (y_src-y_dst)*(y_src-y_dst));
	}
	
	int getNumNodes() {
		return numNodes;
	}
	
};
double minimum_distance(Node & node) {
  double result = 0.;
  //1. set initial vertex to be zero; node zero-based
  node.vec_np[0].dist = 0;
  node.vec_np[0].parent = -1 ;// no parent
  node.vec_np[0].InQueue = true;
  //node.vec_np[1].dist = 10;
  
  //2.add all nodes into the queue
  //for (int u=0;u<node.numNodes;u++)
  node.pq_np.push(node.vec_np[0]);
  
  //3. iterate through the pq till empty sorted by dist
  while (! node.pq_np.empty()) {
	  Node::NodePoint v = node.pq_np.top();
	  node.pq_np.pop();
	  
	  std::cout << "v nodeNum=" << v.nodeNum << std::endl;
	  std::cout << "v dist=" << v.dist << std::endl;
	  
	  result += v.dist;
	  //4. based on v 
	  //5. fetch {v,z} , f z belonging to PrioQ and cost[z] > w(v,z) :
  	  //	cost[z] <-- w(v,z), parent[z] <-- v
      
	  for (int z_index=0;z_index<node.numNodes;z_index++){
			//node.pq_np.push(node.vec_np[u]);
			//skip itself
			if (v.nodeNum == z_index) continue;
			Node::NodePoint z = node.vec_np[z_index];
			std::cout << "Details of z:" << std::endl;
			std::cout << "z_index=" << z_index  << std::endl;
			std::cout << "z.dist=" << z.dist  << std::endl;
			std::cout << "z.InQueue =" << z.InQueue  << std::endl;
			std::cout << "z.x_coord =" << z.x_coord  << std::endl;
			std::cout << "z.y_coord =" << z.y_coord  << std::endl;
			double weight_v_z = node.getDistanceBetweenNodePoints(v,z);
			if (z.dist > weight_v_z) {
				z.dist = weight_v_z;
				z.parent  = v.nodeNum;
			}
			//push the potential candidates into the queue
			//if it is not already in the queue
			if (!z.InQueue ){
				z.InQueue = true;
				node.pq_np.push(z);
			}
	  }
	  //6.refresh all nodes into the queue
	  //start refresh
	  //this is especially to cater for elements which are already in the queue
	  Node::NodePoint dummy = node.pq_np.top();
	  node.pq_np.pop();
	  node.pq_np.push(dummy);
	  //end refresh
	  
	  
	  
	  
  }
  
  
  //write your code here
  return result;
} 

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
    node.distVec[i] = MAX_LONG;
    np.dist = node.distVec[i];
    np.InQueue = false;
    np.parent = -1;
    node.addNodePoint(i,np);
  }
  //node.printNodePoints();
  std::cout << std::setprecision(10) << minimum_distance(node) << std::endl;
}
