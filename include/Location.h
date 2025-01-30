#pragma once

class Location
{
    public:   
        double latitude;
        double longitude;
        Location(double latitude,double longitude);
        Location(Location& obj)
        {
            this->latitude=obj.latitude;
            this->longitude=obj.longitude;
        }
};
