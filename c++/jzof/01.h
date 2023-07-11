#ifndef _O1_H_
#define _01_H_

#include <vector>

class CQueue {

private:
    const int max_size = 10000;
    std::vector<int> *data;
    int tail = 0;
    int head = 0;
    int len = 0;

public:
    CQueue() {
        this->data = new std::vector<int>(max_size);
    }
    ~CQueue() {
        delete this->data;
        this->data = NULL;
    }

    void appendTail(int value) {
        (*(this->data))[this->tail++] = value;
        this->tail %= max_size;
    }

    int deleteHead() {
        if (this->head == this->tail) {
            return -1;
        }
        int value = (*(this->data))[this->head++];
        this->head %= max_size;
        return value;
    }
};

/**
 * Your CQueue object will be instantiated and called as such:
 * CQueue* obj = new CQueue();
 * obj->appendTail(value);
 * int param_2 = obj->deleteHead();
 */

#endif
