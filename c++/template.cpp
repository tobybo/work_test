// #include <iostream>
//
// using namespace std;
//
// template<typename T, bool flag = false, typename B>
// void func(int a) {
//     T b = 5;
//     cout<<a + b<<endl;
// }
//
// int main()
// {
//     func<int, true, int>(3);
//     return 0;
// }

// #include <iostream>
// #include <utility>
//
// template <typename T, std::size_t... Indices>
// void print_elements(const T& container, std::index_sequence<Indices...>)
// {
//     ((std::cout << container[Indices] << " "), ...);
// }
//
// int main()
// {
//     int arr[] = {1, 2, 3, 4, 5};
//     print_elements(arr, std::make_index_sequence<5>{});
//     return 0;
// }

#include <iostream>
#include <type_traits>

using namespace std;

namespace spec {
    template <typename T>
        class test {
            public:
            test() {
                cout<<"this is commontest"<<endl;
            }
        };

    template <typename T>
        class test<T*> {
            public:
            test() {
                cout<<"this is pointest"<<endl;
            }
        };

    template <typename T>
        class other {
            public:
            other() {
                cout<<"this is commonother"<<endl;
            }
        };

    template <typename T>
        class other2 {
            public:
            other2() {
                cout<<"this is commonother2"<<endl;
            }
        };

    template <>
        class test<other<int>> {
            public:
            test() {
                cout<<"this is othertest"<<endl;
            }
        };

    template <typename... Args>
        struct all {
            all() {
                cout<<"this is firstall"<<endl;
            }
        };

    template <typename T, typename... Args>
        struct all<T, Args...> {
            all() {
                cout<<"this is secondall"<<endl;
            }
        };

    // template<typename Condition, typename Then, typename Else>
    //     using condition = std::conditional_t<Condition::value, Then, Else>;

    template <typename R = int, bool should_pop = false, typename T>
        void fill(T&& a) {
            if (should_pop) {
                cout<<"this is func fill, a: "<<a<<endl;
            }
        }
}


int main()
{
    spec::test<spec::other2<int>> test;
    spec::test<spec::other<int>> test2;
    spec::test<int> test3;
    spec::test<int*> test4;

    spec::all<int> all1;
    spec::all<int, int> all2;
    spec::all<int, int, int> all3;
    spec::all<> all4;

    // cout<<spec::condition<true, false>::value<<endl; //invalid

    spec::fill<float, true>(5);
    return 0;
}


