#ifndef MYCLASS_H
#define MYCLASS_H

#include <iostream>

class myclass {
    private:
        int x, z;
    public:
        myclass(int _x, int _z) {
            this->x = _x;
            this->z = _z;
        }
    public:
        int find_road() {
            std::cout<<"hello myclass"<<std::endl;
            return this->x + this->z;
        }
};

int api_find_road(int x, int z);

#endif
