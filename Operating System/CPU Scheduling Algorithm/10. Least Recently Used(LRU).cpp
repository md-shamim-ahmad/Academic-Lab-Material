#include <bits/stdc++.h>
using namespace std;

class LRUCache {
private:
    int capacity;
    unordered_map<int, pair<int, list<int>::iterator>> cache; // Map for key -> (value, iterator in the list)
    list<int> lruList; // List to maintain the order of keys based on their usage

public:
    LRUCache(int capacity) {
        this->capacity = capacity;
    }

    int get(int key) {
        if (cache.find(key) == cache.end()) {
            return -1; // Key not found
        }

        // Move the accessed key to the front
        lruList.erase(cache[key].second);
        lruList.push_front(key);
        cache[key].second = lruList.begin();

        return cache[key].first;
    }

    void put(int key, int value) {
        if (cache.find(key) != cache.end()) {
            // Update existing key
            lruList.erase(cache[key].second);
        } else if (cache.size() >= capacity) {
            // Remove the least recently used key
            int lruKey = lruList.back();
            lruList.pop_back();
            cache.erase(lruKey);
        }

        // Insert new key and update its usage
        lruList.push_front(key);
        cache[key] = make_pair(value, lruList.begin());
    }
};

int main() {
    LRUCache lruCache(3); // Create an LRU cache with capacity 3

    lruCache.put(1, 10);
    lruCache.put(2, 20);
    lruCache.put(3, 30);

    cout << lruCache.get(2) << endl; // Output: 20

    lruCache.put(4, 40);

    cout << lruCache.get(1) << endl; // Output: -1 (not found)
    cout << lruCache.get(3) << endl; // Output: 30

    return 0;
}
