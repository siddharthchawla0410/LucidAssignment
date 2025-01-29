#include<iostream>
#include <vector>

using namespace std;

class Pair
{
    public:
        int time;
        string path;

        Pair(int time,string path)
        {
            this->time=time;
            this->path=path;
        }
};

bool isDest(int node, vector<int> &order)
{
    if(order[node]!=-1){return true;}
    return false;
}



int orderedFrom (int node, vector<int> &order)
{return order[node];}

bool notVisited(int node,int visited)
{
    int bit=1<<node;
    if(bit&visited==0){return true;}
    return false;
}

Pair totalCost(int visited,int node, int n, string pathsofar,vector<vector<int>> &graph,vector<int> &order)
{
    cout<<"Node:"<<node<<" :PathSoFar:"<<pathsofar<<" Visited:"<<visited<<endl;
    int ALL_VISITED=(1 << n) - 1;
       if (visited == ALL_VISITED ) 
       {
        int time=0;
        string path=pathsofar;
        Pair p=Pair(time,path);
        return p; 
       }

        int time=INT_MAX;
        string path="";
         for (int neighbor = 0; neighbor < n; neighbor++)
         {
            int neighborbit=1<<neighbor;
            if( (isDest(neighbor,order)) && (notVisited(orderedFrom(neighbor,order),visited)) ){continue;}
            if((visited & neighborbit) ==0) // not visited
            {
                cout<<"processing neighbor"<<endl;
                Pair p=totalCost((visited | neighborbit), neighbor, n, pathsofar+":"+to_string(neighbor),graph,order);
                int t=graph[node][neighbor]+p.time;
                string pth=p.path;
                if(t<time)
                {
                    time=t;
                    path=pth;
                }
            }
         }

         Pair p=Pair(time,path);

         return p;
}

Pair tsp(vector<vector<int>> &graph,vector<int> &order) {
    int n = graph.size();
  
  // Start from city 0, and only city 0 is visited initially (mask = 1)
    Pair p= totalCost(1, 0, n,to_string(0),graph,order);  
    return p;
}



int main()
{

    vector<int> order ={-1,-1,0,1};
    
    vector<vector<int>> cost = {{0, 10, 15, 20}, 
                                {10, 0, 35, 25}, 
                                {15, 35, 0, 30}, 
                                {20, 25, 30, 0}};
 
    Pair res=tsp(cost,order);
    cout << res.time << "final"<<endl;
    cout << res.path << endl;
    

    return 0;

}