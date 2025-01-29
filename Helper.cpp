// C++ program to find the shortest possible route
// that visits every city exactly once and returns to
// the starting point using memoization and bitmasking

#include <bits/stdc++.h>
using namespace std;

class Pair
{
    public:
    int cost;
    string path;
    
    Pair(int cost,string path)
    {
        this->cost=cost;
        this->path=path;
    }

}
 

Pair totalCost(int mask, int pos, int n, vector<vector<int>> &cost) 
{
  
    // Base case: if all cities are visited, return the 
   // cost to return to the starting city (0)
    if (mask == (1 << n) - 1) {
        Pair p=Pair(0,to_string(pos));
        return p;
    }

    Pair ans=Pair(INT_MAX,"");

    // int ans = INT_MAX;

    // Try visiting every city that has not been visited yet
    for (int i = 0; i < n; i++)
     {
        if ((mask & (1 << i)) == 0) {
          
            // If city i is not visited, visit it and update the mask
            Pair pair=totalCost((mask | (1 << i)), i, n, cost);
            if(ans.cost>cost[pos][i]+pair.cost)
            {
                ans=pair;
                ans.path=to_string(pos)+ans.path;
            }
//            ans = min(ans, cost[pos][i] + pair.cost);
        }
    }

    return ans;
}
 
int tsp(vector<vector<int>> &cost) {
    int n = cost.size();
  
  // Start from city 0, and only city 0 is visited initially (mask = 1)
    return totalCost(1, 0, n, cost);  
}

int main() {
   
    vector<vector<int>> cost = {{0, 10, 15, 20}, 
                                {10, 0, 35, 25}, 
                                {15, 35, 0, 30}, 
                                {20, 25, 30, 0}};
 
    int res = tsp(cost);
    cout << res << endl;

    return 0;
}