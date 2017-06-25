//
//  main.cpp
//  TravellingSalesmanV1
//
//  Created by Pranay Shoroff on 6/25/17.
//  Copyright © 2017 Pranay Shoroff. All rights reserved.

#include <iostream>
#include <set>

using namespace std;

int ** dists; //Matrix of distances from x to y
int n; //Total number of verticies

const int ORIGIN = 0;

//Functions Declarations:
int costFind(set<int> S, int i, int** dists);
int dist(int x, int y, int** dists);
int minCost(set<int> costs);

//Main project flow
int main(int argc, const char * argv[]) {
    
    //Setting up the distances lookup matrix
    printf("Enter number of destinations:\n");
    cin >> n;
    //Initializing dists
    dists = new int *[n];
    for(int i = 0; i < n; i++){
        dists[i] = new int[n];
    }
    for(int i = 0; i < n; i++){
        printf("Start row %d distances:\n", i);
        for(int j = 0; j < n; j++){
            cin >> dists[i][j];
        }
    }
    
    //Initializing set of verticies
    set<int> S;
    for(int i = 0; i < n; i++){
        S.insert(i);
    }
    int minCost = costFind(S, ORIGIN, dists);
    printf("Minimum cost is %d\n", minCost);
    return 0;
}

//Finds the minimum cost to visit all verticies in set S, from 0RIGIN to i
int costFind(set<int> S, int i, int** dists){
    //outofbounds check
    if (S.size() < 2) return -1;
    
    //Set remains as {ORIGIN, i} if functionality is proper
    if (S.size() == 2){
        //printf("dist %d %d: %d\n",0, i, dist(ORIGIN, i, dists));
        return dist(ORIGIN, i, dists);
    } else {
        set<int> costs;
        set<int> t_s = S;
        if (i != ORIGIN) //Must retain 0 (origin) inside set at all times
            t_s.erase(i); // S - {i} necessary to slim down set, but maintain original for distance calculations
        for (set<int>::iterator j=S.begin(); j != S.end(); j++){
            if (*j != ORIGIN && *j != i){
                //printf("Before: i=%d j=%d\n", i, *j);
                int cost = costFind(t_s, *j, dists); //Recursive call to find cheapest
                int currDist = dist(*j, i, dists); //current sunk cost distance
                //printf("it:%d cost:%d currDist:%d\n", *j, cost, currDist);
                costs.insert(cost + currDist); //Insertion into subcosts set
            }
        }
        //printf("min:%d\n", minCost(costs));
        return minCost(costs); //Return the lowest subcost

    }
}


//Returns the appropriate distance from x to y as found in the distance matrix
//Returns -1 if indices are out of bounds
int dist(int x, int y, int** dists){
    if (x >= n || y >= n || x < 0 || y < 0) return -1;
    return dists[x][y];
}

//Finds the minimum value in a set of costs
int minCost(set<int> costs){
    set<int>::iterator it = costs.begin();
    int min = *it;
    for(it = costs.begin(); it != costs.end(); it++){
        if (*it < min){
            min = *it;
        }
    }
    return min;
}
