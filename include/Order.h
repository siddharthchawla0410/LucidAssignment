#pragma once
#include "Location.h"
class Order
{
    private:
        int oid;
        Location* src;
        Location* dst;
        double watingTime;
    public:   
        Order(int oid,Location* src,Location* dst,double waitingTime);
};