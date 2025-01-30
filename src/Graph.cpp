#include<iostream>
#include<vector>
#include"Graph.h"
using namespace std;



template <typename T>
Pair<T>::Pair(T cost, string path)
{
    this->cost=cost;
    this->path=path;
}




template <typename T>
Pair<T> Graph<T>::minimumCost(int node,int visited,string pathSoFar,T costSoFar)
{
    cout<<"Node:"<<node<<" PathSoFar:"<<pathSoFar<<" CostSoFar:"<<costSoFar<<endl;
    if(visited==ALL_VISITED)
    {
        T cost=0;
        string path=pathSoFar;
        Pair<T> p=Pair(cost,path);
        return p;
    }

    T cost=INT_MAX;
    string path="";
    T waitingCost=0;
    if(isOrderSource(node) && getWaitingCost(node)>costSoFar )
    {
        waitingCost=getWaitingCost(node);
    }
    for(int neighbor=0;neighbor<TOTAL_NODES;neighbor++)
    {
        int neighborState=1<<neighbor;
        int orderSrc=getOrderSrc(neighbor);// -1 if invalid
        if((isOrderDest(neighbor)) && (notVisited(orderSrc,visited))) {continue;} // skip as OrderDest is being visited before Order Src

        int waitingCost=0;

        if(isOrderSource(node) && getWaitingCost(node)>costSoFar) // if waiting cost > timeSpentSoFar
        {
            waitingCost=getWaitingCost(node)-costSoFar;
        }
        
        if((visited & neighborState)==0) // neighbor not visited
        {
            T costToNeighbor=weights[node][neighbor];

            Pair<T> p=minimumCost(neighbor,(visited|neighborState),pathSoFar+":"+to_string(neighbor),costSoFar+waitingCost+costToNeighbor);
            T c=waitingCost+costToNeighbor+p.cost;
            string pth=p.path;
            if(c<cost)
            {
                cost=c;
                path=pth;
            }
        }
    }
    Pair<T> p=Pair(cost,path);
    return p;
}

template <typename T>
bool Graph<T>::isOrderSource(int i)
{
    return (nodes[i]->type)==Node<T>::TYPEORDERSRC;
}

template <typename T>
bool Graph<T>::isOrderDest(int i)
{
    return (nodes[i]->type)==Node<T>::TYPEORDERDEST;
}

template <typename T>
bool Graph<T>::isStart(int i)
{
    return (nodes[i]->type)==Node<T>::TYPESTART;
}

template <typename T>
int Graph<T>::getOrderSrc(int i)
{
    return (nodes[i]->orderSrc);
}

template <typename T>
T Graph<T>::getWaitingCost(int i)
{
    return (nodes[i]->wtCost);
}

template <typename T>
bool Graph<T>::notVisited(int node ,int visited)
{
    int nodestate=1<<node;
    if((nodestate & visited)==0)
    {
        return true;
    }
    return false;
}

template <typename T>
Pair<T> Graph<T>::tsp() 
{
    // Start from city 0, and only city 0 is visited initially (mask = 1)
    Pair<T> p=  minimumCost(0,1,"0",0) ;
    return p;
}

template class Graph<double>;
template class Pair<double>;
template class Node<double>;

// int main()
// {
//     cout<<"Starting Program..."<<endl;
//     vector<int> loctypes ={-1,-1,1,1};
//     vector<int> waits={23,15,0,0};
//     vector<int> orderSrces={-1,-1,0,1};

//     vector<Node<int>*> nodeVector;


//     for(int i=0;i<4;i++)
//     {
//         int t=loctypes[i];
//         int wt=waits[i];
//         int os=orderSrces[i];
//         Node<int>* nd=new Node(i,t,wt,os);
//         nodeVector.push_back(nd);
//     }
    
//     vector<vector<int>> cost = {{0, 10, 15, 20}, 
//                                 {10, 0, 35, 25}, 
//                                 {15, 35, 0, 30}, 
//                                 {20, 25, 30, 0}};

    

//     Graph<int> g(nodeVector,cost) ;

//     cout<<"initialized"<<endl;

//     Pair<int> res=g.tsp();

//     cout << res.cost << "final"<<endl;
//     cout << res.path << endl;
    
//     return 0;
// }