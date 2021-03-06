#include <iostream>
#include <vector>
#include <unordered_map> 
#include <algorithm>
using namespace std;

void findShortestPath(vector<vector<int>> graph,std::unordered_map<int,std::pair<int,int>> &table,vector<std::pair<int,int>> checked,vector<std::pair<int,int>> &unchecked){
    //Base case

    if(unchecked.size() <1){
        return;//
    }

    //Sort unvisited list by distance from source. 
    
    auto currentitem = unchecked.back();

    for(auto it = unchecked.begin(); it < unchecked.end(); ++it){
        if((*it).second < currentitem.second){
            currentitem = (*it); // set current item to smallest distance from source
        }
    }


    //Remove item we won't look at it again
    auto i = 0;
    auto counter = 0;
    for(auto it = unchecked.begin(); it < unchecked.end(); ++it){
        if((*it).first == currentitem.first){
            counter = i;
        }
        ++i;
    }


    unchecked.erase(unchecked.begin()+counter);

    //Get neighbors of current item

    auto const row = graph[currentitem.first];

    vector<int> neighbors;

    counter = 0;
    for(auto it = row.begin(); it < row.end(); ++it){
        if(counter != currentitem.first && (*it) >0){
            neighbors.push_back(counter);
        }
        ++counter;
    }

    //if neighbors not in checked and not in unchecked put them in unchecked

    for(auto it = neighbors.begin(); it < neighbors.end(); ++it){
        bool found = false;
        for(auto jit = unchecked.begin(); jit < unchecked.end(); ++jit){
            if((*jit).first == (*it)){
                found = true;
                break;
            }
        }
        
        for(auto jit = checked.begin(); jit < checked.end(); ++jit){
            if((*jit).first == (*it)){
                            found = true;
                            break;
              }
        }

        if(!found  ){

            unchecked.push_back({(*it),table[(*it)].second});
        }
    }


    //if distance from current item to each neighbor is less than the neighbor's items's distance, update distance to shorter value

    for(auto it = neighbors.begin(); it < neighbors.end(); ++it){
        auto newdistance =  graph[currentitem.first][(*it)] + table[currentitem.first].first;
        if(newdistance < table[(*it)].first){ //This is what makes it a "Greedy Algorithm"
            table[(*it)].first = newdistance;
            table[(*it)].second = currentitem.first; //Update previous

            
        }
    }

    //Put current item in visited list remove it from unvisted list.
    checked.push_back(currentitem);

    //Update sizes. They have have changed for both
    for(auto it = checked.begin(); it < checked.end(); ++it){
        (*it).second = table[(*it).first].first;
    }
    for(auto it = unchecked.begin(); it < unchecked.end(); ++it){
        (*it).second = table[(*it).first].first;
    }


    // Recurse to finish
     findShortestPath(graph,table,checked,unchecked);
}

int main(){
    cout<<"dijkstra's algorithm"<<endl;


    vector<vector<int>> graph{
        {0,6,0,1,0},//0
        {6,0,5,2,2},//1
        {0,5,0,0,5},//2
        {1,2,0,0,1},//3
        {0,2,5,1,0}//4
    };
    /* |Vertex - shortest distance from start - previous vertex |*/
    std::unordered_map<int,std::pair<int,int>> table;
    table.insert({0,{0,0}});
    table.insert({1,{INT32_MAX,1}});
    table.insert({2,{INT32_MAX,2}});
    table.insert({3,{INT32_MAX,3}});
    table.insert({4,{INT32_MAX,4}});

    vector<std::pair<int,int>> checked{};
    vector<std::pair<int,int>> unchecked {{0,0}};

    findShortestPath(graph,table,checked,unchecked);

    cout<<"printing table"<<endl;

    for(int i = 0; i < 5; ++i){
        cout<<"cell "<<i <<":distance from source "<<table[i].first<<" prev:"<<table[i].second<<endl;
    }

}