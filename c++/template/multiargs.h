
#ifndef _MULTIARGS_H_
#define _MULTIARGS_H_

namespace multiargs {
    template<typename To, typename From>
    To lexical_cast(From& f) {
        return f;
    }

    template<typename To, typename From>
    class CTest {
        public:
            CTest() {

            }
    };
}

#endif
