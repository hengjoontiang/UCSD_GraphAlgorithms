#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <queue>

/*
 * Kruskal 
 * 0. T is the tree we are constructing and U the remaining set of nodes
 * 1. Sort the edges in ascending length
 * 2. Pick the shortest edge from nodeset U, and check that it does not form a loop in T, by checking the nodes of which the the link belonged to, then remove it from nodeset U
 * 3. Repeat steps 1 and2 till U is empty
 * */
using std::vector;
using std::queue;
using std::pair;
using std::sort;
using std::priority_queue;

const double MAX_DOUBLE = std::numeric_limits<double>::max();

struct Node {
	int numNodes;
	vector<int> nodeSet;
	struct NodePoint {
		int nodeNum;
		int parent; // for linking
		int x_coord,y_coord;
		//double  dist;
		//vector<int> linkNodes;
		bool InQueue;
		
	};
	struct Edge {
		
		int startPointIndex;
		int endPointIndex;
		double dist;
		bool InTree;
		Edge(int spIndex,int epIndex) {
			this->startPointIndex =  spIndex;
			this->endPointIndex =  epIndex;
		}
		
		
	};
	//priority queue based on the bool operator
	struct compare {
		//to return based on ascending sequence
	bool operator()(const Edge & a,const Edge & b) {
		return a.dist > b.dist;
	}
	} mycompare;
	
	//priority_queue<NodePoint, vector<NodePoint >,compare> pq_np;
	vector<NodePoint> vec_np;
	vector<Edge> vec_edge;
	
	/*
	int getGreatGrandParent(int nodepointNum) {
			if (nodepointNum == -1) return -1;
			int currnodepointNum = nodepointNum;
			
			int newnodepointNum = vec_np[currnodepointNum].parent;
			if (newnodepointNum == -1) return currnodepointNum;
			
			
			return getGreatGrandParent(newnodepointNum);
		}
	*/
	bool IsSameNodeSet(int startPointIndex, int endPointIndex) {
			//check startPoint and end point
			
			return nodeSet[startPointIndex] == nodeSet[endPointIndex] ;
	}
	
	void addNodePoint(int nodeNum,NodePoint np) {
		//note that vector position is indicative of nodeNum
		vec_np[nodeNum] = np;
	}
	void addEdge(Edge newEdge) {
		//note that vector position is indicative of nodeNum
		vec_edge.push_back(newEdge);
	}
	
	void createEdges() {
		//go through the edges, and create the edge vector
		//construct a triangle, to avoid overlap
		for (int u=0;u< getNumNodes();u++){
			for (int v=u;v< getNumNodes();v++){
				if (u == v) continue; //no edge for the same point
				//NodePoint start = vec_np[u];
				//NodePoint end = vec_np[v];
				double dist = getDistanceBetweenNodePoints(vec_np[u],vec_np[v]);
				Edge edge(u,v);
				edge.startPointIndex = u;
				edge.endPointIndex = v;
				edge.dist = dist;
				edge.InTree = false;
				addEdge(edge);
			}
		}
	}
	
	void printEdges() {
		for (int u=0;u< vec_edge.size();u++){
			std::cout << "Edge index=" << u << std::endl;
			std::cout << "Edge sp=" << vec_edge[u].startPointIndex << std::endl;
			std::cout << "Edge ep=" << vec_edge[u].endPointIndex << std::endl;
			std::cout << "Edge dist=" << vec_edge[u].dist << std::endl;
			std::cout << "Edge InTree=" << vec_edge[u].InTree << std::endl;
		}
	}
	void printNodePoints() {
		for (int u=0;u< vec_np.size();u++){
			std::cout << "Node index=" << u << std::endl;
			std::cout << "Node parent=" << vec_np[u].parent << std::endl;
			std::cout << "Node InQueue=" << vec_np[u].InQueue << std::endl;
			
		}
	}
	void printNodeSet(){
		for (int u=0;u< nodeSet.size();u++){
			std::cout << "Node index=" << u << std::endl;
			std::cout << "nodeSet[u]=" << nodeSet[u] << std::endl;
		}
	}
	//vector<vector<int> > adj;
	
	//try to use a map for storgae so that we still get a key
	vector<vector<std::pair<int,int>>> adj_cost;
	//vector<vector<int> > cost;
	vector<double> dist;//the dist vector that tallies with the edge index
	
	
	vector<bool > IsVisited; //part of dfs
	
	Node(int numNodes) {
		this->numNodes = numNodes;
		vec_np.resize(this->numNodes);
		
		nodeSet.resize(this->numNodes);
		//dist.resize(this->numNodes);
		
		IsVisited.resize(this->numNodes);
		
		resetIsVisitedFlag();
		//resetDist();
		resetNodeSet();
	}
	
	
	//returns 1-based nodeNum check to see if visited
	bool getIsVisited(int nodeNum){
		return IsVisited[nodeNum];
	}
	
	void setIsVisited(int nodeNum){
		IsVisited[nodeNum] = true;
	}
	double getEdgeDist(int x) {
		return dist[x];
	}
	void setEdgeDist(int x, double value) {
		dist[x] = value;
	}
	void setIsEdgeVisited(int edgeNum){
		vec_edge[edgeNum].InTree = true;
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
	void resetNodeSet(){
		for (int u=0;u<this->numNodes;u++) {
			nodeSet[u] = u;
	    }
	}
	void mergeNodes(int a, int b) {
		//std::cout <<"a=" <<a << std::endl;
		//std::cout <<"b=" <<b << std::endl;
		//std::cout << "Before merging.." << std::endl;
		//std::cout <<"nodeSet[a]=" <<nodeSet[a] << std::endl;
		//std::cout <<"nodeSet[b]=" <<nodeSet[b] << std::endl;
		
		
		int min_value = std::min(nodeSet[a],nodeSet[b]);
		
		int nodeValueToSearch = min_value == nodeSet[a] ? nodeSet[b] : nodeSet[a] ;
		//search through nodeSet for all nodes 
		for (int u = 0; u <  nodeSet.size(); u++){
			if (nodeSet[u] == nodeValueToSearch ) {
				nodeSet[u] = min_value;
			}
		}
		
		
		
		
		//std::cout << "After merging.." << std::endl;
		//std::cout <<"nodeSet[a]=" <<nodeSet[a] << std::endl;
		//std::cout <<"nodeSet[b]=" <<nodeSet[b] << std::endl;
	}
	int getEdgeMinDist(){
	    double MIN_NUM = MAX_DOUBLE; 
		int indexWifMinValue=-1;
		for (int u=0;u< vec_edge.size();u++){
			//std::cout << "u=" << u << std::endl;
			//std::cout << "MIN_NUM=" << MIN_NUM << std::endl;
			//std::cout << "dist[u]=" << dist[u] << std::endl;
			//pluck only from those nodes that are still not considered
			//std::cout << "check InTree "<< vec_edge[u].InTree << std::endl;
			if (vec_edge[u].InTree) continue; 
			//first check if start point and endpoint of the edge picked is from the same side, discard if so
			
			//retrieve the starting point and ending point of the dge
			int startPointIndex = vec_edge[u].startPointIndex;
			int endPointIndex = vec_edge[u].endPointIndex;
			//std::cout << "check startPointIndex "<< startPointIndex << std::endl;
			//std::cout << "check endPointIndex "<< endPointIndex << std::endl;
			
			if (IsSameNodeSet(startPointIndex,endPointIndex)) continue;
			//std::cout << "vec_edge[" << u << "].dist=" << vec_edge[u].dist << std::endl;
			if (vec_edge[u].dist< MIN_NUM) {
				MIN_NUM = vec_edge[u].dist;
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
	//2 clusters, 1 edge
	//3 clusters, 2 edges
	//..
	double getDist(int numClusters) {
		int numEdges = numClusters - 1;
		//we first sort the edges by dist
		std::sort(vec_edge.begin(), vec_edge.end(),mycompare);
		
		int wantedIndex=-1;
		int count = 0;
		for (int u=0;u< vec_edge.size();u++) {
			
			
			if (vec_edge[u].InTree) {
				//std::cout << "vec_edge["<< u<< "].dist="<< vec_edge[u].dist <<std::endl;
				//std::cout << "vec_edge["<< u<< "].InTree="<< vec_edge[u].InTree <<std::endl;
				//look for the smallest dist that is InTree
				wantedIndex = u;
				count++;
				//break;
				if (count > numEdges - 1) break;
			}
		}
		
		
		//retrieve the smallest distance
		
		return vec_edge[wantedIndex].dist;
	}
};

double minimum_distance(Node & node) {
  double result = 0.;
  //write your code here
  //do 1 round for each node
  //it will consists of a tree chained up by n nodes, with some nodes isolated if they are not connected
  for (size_t i = 0; i < node.getNumNodes(); i++) {
	    //std::cout << "i=" <<i << std::endl;
		//retrieve the min dist edge that is in U
		int indexEdgeMinDistFromU = node.getEdgeMinDist();
		
		//check when the index == 8
		//if (indexEdgeMinDistFromU == 8) {
			//std::cout << "edge index="<< indexEdgeMinDistFromU<< std::endl;
			//std::cout << "edge InTree="<< node.vec_edge[indexEdgeMinDistFromU].InTree<< std::endl;
			//std::cout << "edge sp="<< node.vec_edge[indexEdgeMinDistFromU].startPointIndex<< std::endl;
			//std::cout << "edge ep="<< node.vec_edge[indexEdgeMinDistFromU].endPointIndex<< std::endl;
			//std::cout << "edge dist="<< node.vec_edge[indexEdgeMinDistFromU].dist<< std::endl;
			
			//check if they have the sam parent
			//std::cout << "nodeSet[sp]=" << node.nodeSet[node.vec_edge[indexEdgeMinDistFromU].startPointIndex] << std::endl;
			//std::cout << "nodeSet[ep]=" << node.nodeSet[node.vec_edge[indexEdgeMinDistFromU].endPointIndex] << std::endl;
			
			//lets check node 3 and node 2
			//std::cout << "nodeSet[2]=" << node.nodeSet[2] << std::endl;//0
			//std::cout << "nodeSet[3]=" << node.nodeSet[3] << std::endl;//0
			//std::cout << "nodeSet[4]=" << node.nodeSet[4] << std::endl;//4
		//}
		
		
		
		if (indexEdgeMinDistFromU == -1) break; //didnt manage to find
		//std::cout << "indexEdgeMinDistFromU=" <<indexEdgeMinDistFromU << std::endl;
		node.vec_edge[indexEdgeMinDistFromU].InTree = true;
		double dist = node.vec_edge[indexEdgeMinDistFromU].dist;
		
		//set up the parent
		//retrieve the start and end point
		int ep = node.vec_edge[indexEdgeMinDistFromU].endPointIndex;
		int sp = node.vec_edge[indexEdgeMinDistFromU].startPointIndex;
		//since there is no direction
		//we will follow the convention in which the smaller number flows down to bigger number
		//i.e we will set the parent to be smaller number
		node.vec_np[ep].parent = sp;
		node.mergeNodes(sp,ep);
		
		//first time shud get sp
		//std::cout << "getGreatGrandParent=" << node.getGreatGrandParent(ep) << std::endl;
		//std::cout << "sp=" << sp << std::endl;
		//std::cout << "ep=" << ep << std::endl;
	    //std::cout << "dist=" << dist << std::endl;
		
		
		//so now we shud get greatgrandparent of node 2 and node 0 to be the same ~ equal ok
		//std::cout << "getGreatGrandParent(sp)=" << node.getGreatGrandParent(sp) << std::endl;
		//std::cout << "getGreatGrandParent(ep)=" << node.getGreatGrandParent(ep) << std::endl;
		
		//break;
		
		
		result += dist;
		
  }
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
    //node.distVec[i] = MAX_LONG;
    //np.dist = node.distVec[i];
    np.InQueue = false;
    np.parent = -1;
    node.addNodePoint(i,np);
  }
  node.createEdges();
  //node.printEdges();
  
  
  //do simulation
  int k;
  std::cin >> k;
  
  minimum_distance(node) ;
  std::cout << std::setprecision(10) << node.getDist(k)<< std::endl;
  //node.printNodePoints();
  //node.printNodeSet();
}
