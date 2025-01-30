#include<iostream>
#include<vector>
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
        Node(int id,int type,T wtCost,int orderSrc)
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
        Pair(T cost, string path)
        {
            this->cost=cost;
            this->path=path;
        }
};

template<typename T>
class Graph
{
    vector<vector<T>> weights;
    vector<Node<T>*> nodes;
    int TOTAL_NODES;
    int ALL_VISITED;
     
    public:
        Graph(vector<Node<T>*>& nodes,vector<vector<T>>& weights)
        {
            this->nodes=nodes;
            this->weights=weights;
            TOTAL_NODES=nodes.size();
            ALL_VISITED=(1<<TOTAL_NODES)-1;

        }

        Pair<T> minimumCost(int node,int visited,string pathSoFar,int costSoFar)
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
                if((isOrderDest(neighbor)) && (notVisited(orderSrc,visited))) {continue;}

                int waitingCost=0;

                if(isOrderSource(node) && getWaitingCost(node)>costSoFar)
                {
                    waitingCost=getWaitingCost(node);
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


        bool isOrderSource(int i)
        {
            return (nodes[i]->type)==Node<T>::TYPEORDERSRC;
        }
        bool isOrderDest(int i)
        {
            return (nodes[i]->type)==Node<T>::TYPEORDERDEST;
        }
        bool isStart(int i)
        {
            return (nodes[i]->type)==Node<T>::TYPESTART;
        }

        int getOrderSrc(int i)
        {
            return (nodes[i]->orderSrc);
        }

        T getWaitingCost(int i)
        {
            return (nodes[i]->wtCost);
        }

        static bool notVisited(int node ,int visited)
        {
            int bit=1<<node;
            if(bit&visited==0){return true;}
            return false;
        }

    Pair<T> tsp() 
    {
        cout<<"Hello";
        
  // Start from city 0, and only city 0 is visited initially (mask = 1)
    Pair<T> p=  minimumCost(0,1,"0",0) ;
    return p;
    }

};




int main()
{
    cout<<"Starting Program..."<<endl;
    vector<int> loctypes ={-1,-1,1,1};
    vector<int> waits={23,15,0,0};
    vector<int> orderSrces={-1,-1,0,1};

    vector<Node<int>*> nodeVector;


    for(int i=0;i<4;i++)
    {
        int t=loctypes[i];
        int wt=waits[i];
        int os=orderSrces[i];
        Node<int>* nd=new Node(i,t,wt,os);
        nodeVector.push_back(nd);
    }
    
    vector<vector<int>> cost = {{0, 10, 15, 20}, 
                                {10, 0, 35, 25}, 
                                {15, 35, 0, 30}, 
                                {20, 25, 30, 0}};

    

    Graph<int> g(nodeVector,cost) ;

    cout<<"initialized"<<endl;

    Pair<int> res=g.tsp();

    cout << res.cost << "final"<<endl;
    cout << res.path << endl;
    
    return 0;
}