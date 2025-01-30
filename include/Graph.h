#pragma once
#include<iostream>
using namespace std;

template<typename T>
class Node
{
    public:
        static const int TYPEORDERSRC=-1;
        static const int TYPEORDERDEST=1;
        static const int TYPESTART=0;
        int id;
        int type;
        T wtCost;//waitingCost
        int orderSrc;
        // Node(int id,int type, T wtCost, int orderSrc);
        // template <typename T>
        Node(int id,int type, T wtCost, int orderSrc)
        {
            this->id=id;
            this->type=type;
            this->wtCost=wtCost;
            this->orderSrc=orderSrc;
        }
};


template<typename T>
class Pair
{
    public:
        T cost;
        string path;
        Pair(T cost, string path);
};


template<typename T>
class Graph
{
    vector<vector<T>> weights;
    vector<Node<T>*> nodes;
    int TOTAL_NODES;
    int ALL_VISITED;
     
    public:
        // Graph(vector<Node<T>*>& nodes,vector<vector<T>>& weights);
        // template <typename T>
        Graph(vector<Node<T>*>& nodes,vector<vector<T>>& weights)
        {
            this->nodes=nodes;
            this->weights=weights;
            TOTAL_NODES=nodes.size();
            ALL_VISITED=(1<<TOTAL_NODES)-1;

        }
        Pair<T> minimumCost(int node,int visited,string pathSoFar,T costSoFar);
        bool isOrderSource(int i);
        bool isOrderDest(int i);
        bool isStart(int i);
        int getOrderSrc(int i);
        T getWaitingCost(int i);
        static bool notVisited(int node ,int visited);
        Pair<T> tsp();

};