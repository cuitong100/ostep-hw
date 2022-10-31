#include <iostream>
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
#include <cstring>
#include <unordered_map>
#include <queue>


class FIFOCache {
public:

    int n;
    deque<int> queue;
    int get(int value){
        auto t = find(queue.begin(), queue.end(), value);
        if (t == queue.end()){
            return -1;
        }else {
            return value;
        }
    }

    FIFOCache(int capacity) {
        n = capacity;
    }

    void put(int value) {
        if (queue.size() < n) {
            if (get(value) == -1) {
                queue.push_back(value);
            }
        } else {
            queue.pop_front();
            queue.push_back(value);
        }
    }
};



int main(){
    FIFOCache* fifocache = new FIFOCache(2);
    fifocache->put(1);
    fifocache->put(2);
    int r1 = fifocache->get(1);
    printf("r1 should be 1: %d\n", r1);
    fifocache->put(3);
    int r2 = fifocache->get(1);
    printf("r2 should be -1: %d\n", r2);
    fifocache->put(4);
    int r3 = fifocache->get(2);
    int r4 = fifocache->get(3);
    int r5 = fifocache->get(4);
    printf("r3,r4,r5 should be -1, 3, 4: %d %d %d\n", r3, r4, r5);

    return 0;
}

