
#ifndef _multiset_h_
#define _multiset_h_

#include <iostream>
#include <set>

namespace NP_multiset {
    using namespace std;
    class CTest {
        private:
            void caseEraseItor() {
                int my_ints[] = {1,2,2,3,4,5};
                multiset<int> my_set(my_ints, my_ints + 6);
                cout<<"------------ pre set -----------"<<endl;
                for (auto &v : my_set) {
                    cout<<v<<endl;
                }
                cout<<"--------------------------------"<<endl;
                auto itor = my_set.find(2);
                if (itor != my_set.end()) {
                    my_set.erase(itor);
                }
                cout<<"------------ later set -----------"<<endl;
                for (auto &v : my_set) {
                    cout<<v<<endl;
                }
                cout<<"--------------------------------"<<endl;
            }
        public:
            CTest() {
                caseEraseItor();
            }
    };
};

#endif
