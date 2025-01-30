#include<iostream>
#include<vector>
#include"Location.h"
#include"Order.h"
#include"Graph.h"
#include "GPSHelper.h"
using namespace std;

int main()
{
    vector<vector<double>> locs = {
    {28.7041, 77.1025}, // # Location A (New Delhi)
    {28.5355, 77.3910}, // # Location B (Noida)
    {28.6139, 77.2090}, // # Location C (Connaught Place, New Delhi)
    {28.5355, 77.2770}, // # Location D (Greater Noida)
    {28.4595, 77.0266}  // # Location E (Gurugram)
    };
    vector<int> loctypes={0,-1,1,-1,1};
    vector<int> ordSrcs={-1,-1,1,-1,3}; // indicates source of order -1 if restaurant or starting point
    vector<double> waitingTimes={0,23,0,45,0}; // valid only for restaurant Location

    vector<Location*> locations;
    vector<Node<double>*> nodes;
    vector<Order*> orders;

    for(int i=0;i<locs.size();i++)
    {
        vector<double> loc=locs[i];
        double lat=loc[0];
        double lon=loc[1];
        Location* location=new Location(lat,lon);
        locations.push_back(location);
        Node<double>* node=new Node(i,loctypes[i],waitingTimes[i],ordSrcs[i]);
        nodes.push_back(node);
    }

    int o=0;
    for(int i=1;i<locations.size();i=i+2)
    {
        Location* src=locations[i];
        Location* dst=locations[i+1];
        double waitingTime=waitingTimes[i];
        Order* order=new Order(o,src,dst,waitingTime);
        o++;
        orders.push_back(order);
    }

    vector<vector<double>> distanceMatrix=GPSHelper::getDistaceMatrix(locations);
    vector<vector<double>> times=GPSHelper::getTimeMatrix(distanceMatrix);

    Graph<double> g(nodes,times);
    Pair<double> res=g.tsp();
    cout<<"Final Cost: "<<res.cost<<endl;
    cout<<"Final Path:"<<res.path<<endl;

    


    return 0;

}