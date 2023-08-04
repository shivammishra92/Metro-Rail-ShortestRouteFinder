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

    void shortestDistDijkstra(int src, int dest,int n, unordered_map<int,pair<string,string>>stations_mapping) {
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
        cout << "Shortest Distance of "<< stations_mapping[src].first << " station from "<<stations_mapping[dest].first<<" stations is:"<<dist[dest] <<"km" << endl;
		
        cout << "Shortest Distance of "<< stations_mapping[src].first << " station from all other stations is:" << endl;
        cout<<endl;
		for(int i=1; i<n; i++) {
			cout <<"Shortest Distance of " << stations_mapping[src].first << " from "<< stations_mapping[i].first <<" is-> " << dist[i]<<"km" <<endl;
		}
        cout << endl;
		
	}

};

int main() {
	MetroRouteGraph g;
	g.addEdge(1,2,3,1);
    g.addEdge(1,4,12,1);
    g.addEdge(2,4,10,1);
    g.addEdge(2,3,10,1);
    g.addEdge(3,4,5,1);
    g.addEdge(1,2,1,1);

    //<(node,(station name,its code))>
	unordered_map<int,pair<string,string>>stations_mapping; 
    stations_mapping[1] = {"Gopal Nagar","GN"};
    stations_mapping[2] = {"Yashoda Nagar","YN"};
    stations_mapping[3] = {"Mall Road","MR"};
    stations_mapping[4] = {"IIT Kanpur","IITKNP"};


	unordered_map<string,int>codeToNode;
	for(int i=1;i<=4;i++){
		codeToNode[stations_mapping[i].second] = i;
	}


    cout<<endl;
    cout<<"***************************WELCOME TO KANPUR METRO***************************"<<endl;
    cout<<"Below are the Metro Stations with their Codes:"<<endl;
	cout<<endl;
        for(int i=1;i<=4;i++){
			cout<<stations_mapping[i].first << " --- " <<stations_mapping[i].second<<endl;
		}

    cout<<endl;
    cout<<"Enter the Source Station code:"<<endl;
	string src;
	cin>>src;
	cout<<"Enter the Destination Station code:"<<endl;
	string dest;
	cin>>dest; 

	int s = codeToNode[src];
	int d = codeToNode[dest];
	g.shortestDistDijkstra(s,d,5,stations_mapping);		
    
	//g.printAdjList();
	
	//g.shortestDistDijkstra(4,5,stations_mapping);

	return 0;
}
