#include <iostream>
#include<unordered_map>
#include<map>
#include<list>
#include<queue>
#include<stack>
#include<algorithm>
#include<set>
#include<limits.h>
#include<string>
#include<bits/stdc++.h>
using namespace std;

class MetroRouteGraph {
	public:
    
	unordered_map<int, list<pair<int,int> > > adjList;

	void addEdge(int u, int v, int wt, bool direction) {
		//direction = 1 -> undirected graph
		//direction => 0 -> directed graph;
		adjList[u].push_back({v,wt});
		if(direction == 1) {
			adjList[v].push_back({u,wt});
		}
	}

	void printAdjList() {
		for(auto i: adjList) {
			cout << i.first <<"-> ";
			for(auto j: i.second) {
				cout << "(" << j.first<<", "<<j.second<<"), ";
			}
			cout << endl;
		}
	}

    void shortestDistDijkstra(int src, int n, unordered_map<int,string>stations_mapping) {
		vector<int> dist(n,INT_MAX);
		set<pair<int,int> > st;
		//intiial steps
		dist[src] = 0;
		st.insert(make_pair(0,src));

		while(!st.empty() ) {
			//fetch the smallest or first eklement from set
			auto topElement = *(st.begin());
			int nodeDistance = topElement.first;
			int node = topElement.second;

			//pop from set
			st.erase(st.begin());

				//neighbour traverse
			for(auto nbr: adjList[node]) {
				if(nodeDistance + nbr.second < dist[nbr.first]) {
					//mujhe distance update krna h 
					//finding entry in set
					auto result = st.find(make_pair(dist[nbr.first], nbr.first));
					//if found, then remove
					if(result != st.end()) {
						st.erase(result);
					}
					//updation in dist array and set
					dist[nbr.first] = nodeDistance + nbr.second;
					st.insert(make_pair(dist[nbr.first], nbr.first));
				}
			}
			
		}

		//cout << "printing ans:" << endl;
        cout << "Shortest Distance of "<< stations_mapping[src] << " station from all other stations is:" << endl;
        cout<<endl;
		for(int i=1; i<n; i++) {
			cout <<"Shortest Distance of " << stations_mapping[src] << " from "<< stations_mapping[i] <<" is-> " << dist[i] <<endl;
		}
        cout << endl;
		
	}

};

int main() {
	MetroRouteGraph g;
    cout<<"WELCOME TO KANPUR METRO"<<endl;

    g.addEdge(1,2,3,1);
    g.addEdge(1,4,12,1);
    g.addEdge(2,4,10,1);
    g.addEdge(2,3,10,1);
    g.addEdge(3,4,5,1);
    g.addEdge(1,2,1,1);
    
    unordered_map<int,string>stations_mapping;
    stations_mapping[1] = "Gopal Nagar";
    stations_mapping[2] = "Yashoda Nagar";
    stations_mapping[3] = "Mall Road";
    stations_mapping[4] = "IIT Kanpur";


	//g.printAdjList();
	
	g.shortestDistDijkstra(4,5,stations_mapping);

	return 0;
}
