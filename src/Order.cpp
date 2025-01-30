#include<iostream>
#include "Order.h"


Order::Order(int oid,Location* src,Location* dst,double waitingTime)
{
    this->oid=oid;
    this->src=src;
    this->dst=dst;
    this->watingTime=watingTime;
}