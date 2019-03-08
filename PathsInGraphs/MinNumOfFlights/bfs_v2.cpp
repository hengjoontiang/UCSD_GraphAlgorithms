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

struct Node {
	int numNodes;
	vector<vector<int> > adj;
	vector<int> dist;
	
	vector<bool > IsVisited; //part of dfs
	
	Node(int numNodes) {
		this->numNodes = numNodes;
		adj.resize(this->numNodes);
		dist.resize(this->numNodes);
		
		IsVisited.resize(this->numNodes);
		
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
 * BFS(G,A)
 * for all u belonging to V
 * 	dist[u] = INF
 * 
 * dist[A] = 0 //starting node
 * Q.push_back(A);
 * 
 * while Q is not empty:
 * 		u = Dequeue(Q)
 * 		for all (u,v) belong to outgoing from u
 * 			if dist[v] = INF //not processed yet
 * 				Enqueue(Q,v)
 * 				dist[v] = dist[u] +1
 * */
int distance(Node & node, int s, int t) {
  //write your code here
  int nodeSize = node.getNumNodes();
  //std::cout << "nodeSize=" << nodeSize << std::endl;
  vector<int> dist(nodeSize);
  //init the distance vector
  for (int i=1;i<=nodeSize;i++) {
			//dist[i] = MAX_INT;
			node.setDist(i,MAX_INT);
  }
  
  //start with s
  //dist[s] = 0;
  node.setDist(s,0);
  
  std::queue<int> bfs_queue;
  
  //place the starting node into the queue
  bfs_queue.push(s);
  
  
  //start processing the queue
  while (!bfs_queue.empty()) {
	  int current_index = bfs_queue.front();
	  
	  
	  //std::cout <<" current_index=" << current_index << std::endl;
	  
	  //process the immediate child nodes of current_index
	 //std::cout << "node.getLinkedVectorSize(current_index)=" << node.getLinkedVectorSize(current_index) << std::endl;
	  for (int adj_index= 1; adj_index <=  node.getLinkedVectorSize(current_index) ; adj_index++ ) {
			int nextIndex = node.getPair(current_index,adj_index);
			//std::cout << "child index= " << nextIndex << std::endl;
	  
			//use dist[current_index]==INF to check if itas already been visited
			if (node.getDist(nextIndex) == MAX_INT) { //part of dfs
				
				//enquing
				//std::cout << "enquing.."<<std::endl;
				//std::cout << "current_index=" << current_index << std::endl;
				//std::cout << "dist[current_index]="<< dist[current_index] << std::endl;
				//std::cout << "nextIndex=" << nextIndex << std::endl;
				bfs_queue.push(nextIndex);
				//dist[nextIndex] = dist[current_index] +1;
				node.setDist(nextIndex, node.getDist(current_index) +1);
				
				if (nextIndex == t) return node.getDist(nextIndex);
			}
     }
  
  
	  bfs_queue.pop();
	  
  }
  return -1; //dist[t];
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
    node.addBiDirectionalLink(x,y);
  }
  //check nodeValues
  
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
