#ifndef __LRUCACHE__
#define __LRUCACHE__
#include<unordered_map>
using std::unordered_map;

struct LinkedNode{
    int key, value;
    struct LinkedNode *prev, *next;
    LinkedNode() : key(0), value(0), prev(nullptr), next(nullptr){}
    LinkedNode(int key, int value) : key(key), value(value), prev(nullptr), next(nullptr) {}
};

class LRUCache
{
private:
    unordered_map<int, LinkedNode*> _cache;
    LinkedNode *_head, *_tail;
    int _size;
    int _capacity;
    void move_to_head(LinkedNode *node){
        node->prev->next = node->next;
        node->next->prev = node->prev;
        node->prev = _head;
        node->next = _head->next;
        _head->next = node;
    }
    LinkedNode *remove_tail(){
        LinkedNode *last = _tail->prev;
        last->prev->next = _tail;
        _tail->prev = last->prev;
        return last;
    }
public:
    LRUCache(int capacity) : _capacity(capacity), _size(0){
        _head = new LinkedNode();
        _tail = new LinkedNode();
        _head->next = _tail;
        _tail->prev = _head;
    }
    int get(int key){
        if(!_cache.count(key)){
            return -1;
        }
        LinkedNode *node = _cache[key];
        move_to_head(node);
        return node->value;
    }
    void put(int key, int value){
        if(!_cache.count(key)){
            LinkedNode *node = new LinkedNode(key,value);
            _cache[key] = node;
            node->prev = _head;
            node->next = _head->next;
            _head->next = node;
            _size++;
        }
        if(_size > _capacity){
            LinkedNode *removed = remove_tail();
            _cache.erase(removed->key);
            delete removed;
            _size--;
        }

    }
    ~LRUCache(){
       LinkedNode *p = _head, *q=p->next;
       while(q){
           delete p;
           p = q;
           q = p->next;
       } 
       delete p;
    }
};


#endif