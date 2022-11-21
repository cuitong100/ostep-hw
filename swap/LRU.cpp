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



class LRUCache {
public:
    struct Node {
        int key, val;
        Node *left, *right;
        Node(int _key, int _val): key(_key), val(_val), left(NULL), right(NULL) {}
    }*L, *R;
    unordered_map<int, Node*> hash;
    int n;

    void remove(Node* p) {
        p->right->left = p->left;
        p->left->right = p->right;
    }

    void insert(Node* p) {
        p->right = L->right;
        p->left = L;
        L->right->left = p;
        L->right = p;
    }

    LRUCache(int capacity) {
        n = capacity;
        L = new Node(-1, -1), R = new Node(-1, -1);
        L->right = R, R->left = L;
    }

    int get(int key) {
        if (hash.count(key) == 0) return -1;
        auto p = hash[key];
        remove(p);
        insert(p);
        return p->val;
    }

    void put(int key, int value) {
        if (hash.count(key)) {
            auto p = hash[key];
            p->val = value;
            remove(p);
            insert(p);
        } else {
            if (hash.size() == n) {
                auto p = R->left;
                remove(p);
                hash.erase(p->key);
                delete p;
            }
            auto p = new Node(key, value);
            hash[key] = p;
            insert(p);
        }
    }
};


int main(){
    LRUCache *lRUCache = new LRUCache(3);
    lRUCache->put(1, 1);
    lRUCache->put(2, 2);    
    int get1 = lRUCache->get(1);    // return 1
    printf("get1 should be 1: %d\n", get1);
    lRUCache->put(3, 3); // LRU key was 2, evicts key 2, cache is {1=1, 3=3}
    int get2 = lRUCache->get(2);    // returns -1 (not found)
    printf("get2 should be -1: %d\n", get2);
    lRUCache->put(4, 4); // LRU key was 1, evicts key 1, cache is {4=4, 3=3}
    int get3 = lRUCache->get(1);    // return -1 (not found)
    int get4 = lRUCache->get(3);    // return 3
    int get5 = lRUCache->get(4);    // return 4
    printf("get3, get4, get5 should be -1, 3, 4 : %d, %d, %d", get3, get4, get5);
    return 0;
}

