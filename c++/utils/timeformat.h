
#ifndef _TIME_FORMAT_H_
#define _TIME_FORMAT_H_

#include <iostream>
#include <sstream> // stringstream
#include <string>
#include <iomanip>

#include <time.h>

namespace NP_timeformat {

    static std::string getNowStr()
    {
        time_t now = time(0);
        tm *ltm = localtime(&now);
        std::stringstream ss;
        ss << std::setfill('0') << std::setw(4) << 1900 + ltm->tm_year << "-" << std::setw(2) << 1 + ltm->tm_mon << "-" << std::setw(2) << ltm->tm_mday;
        ss << " ";
        ss << std::setfill('0') << std::setw(2) << ltm->tm_hour << ":" << std::setw(2) << ltm->tm_min << ":" << std::setw(2) << ltm->tm_sec;
        return ss.str();
    }

    class CTest {
        public:
            CTest() {
                std::string now = getNowStr();
                std::cout<<"now: "<<now<<std::endl;
            }
    };
}


#endif
