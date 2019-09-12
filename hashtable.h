#ifndef __HASHTABLE_H
#define __HASHTABLE_H

template<class Key, class Value>
class hashtable {

public:
    hashtable() {
        table = new entry*[capacity];
        for (int i=0; i<capacity; ++i) {
            table[i] = nullptr;
        }
    }
    ~hashtable() {
        for (int i=0; i<capacity; ++i) {
            entry* p = table[i];
            while (p != nullptr) {
                entry* tmp = p;
                p = p->next;
                delete tmp;
            }
        }
        delete []table;
    }

private: 
    static const int DEFAULT_INIT_CAPACITY = 8;
    static constexpr float LOAD_FACTOR = 0.75;

    struct entry {
        Key key;
        Value value;
        entry* next;
        entry() : next(nullptr) {}
        entry(Key k, Value v, entry* n) : key(k), value(v), next(n) {}
    };

    entry** table;
    int capacity = DEFAULT_INIT_CAPACITY;
    int size = 0;
    int used = 0;

public:
    void put(Key k, Value v) {
        int index = hash(k);
        if (table[index] == nullptr) {
            table[index] = new entry;
        }

        entry* p = table[index];
        if (p->next == nullptr) {
            p->next = new entry(k, v, nullptr);
            size++;
            used++;
            if (used >= capacity * LOAD_FACTOR) {
                resize();
            }
        } else {
            do {
                p = p->next;
                if (p->key == k) {
                    p->value = v;
                    return;
                }
            } while (p->next != nullptr);
            entry* tmp = table[index]->next;
            table[index]->next = new entry(k, v, tmp);
            size++;
        }
    }

    void remove(Key k) {
        int index = hash(k);
        entry* p = table[index];
        if (p == nullptr || p->next == nullptr)
            return;

        entry* prev;
        do {
            prev = p;
            p = p->next;
            if (p->key == k) {
                prev->next = p->next;
                delete p;
                size--;
                return;
            }
        } while (p->next != nullptr);
    }

    Value* get(Key k) {
        int index = hash(k);
        entry* p = table[index];
        if (p == nullptr || p->next == nullptr)
            return nullptr;
        while (p->next != nullptr) {
            p = p->next;
            if (k == p->key) {
                return &(p->value);
            }
        }
        return nullptr;
    }
    

private:
    int hash(Key k) {
        int h;
        return ((h = k) ^ (h >> 16)) % capacity;
    }

    void resize() {
        entry** oldTable = table;
        table = new entry*[capacity * 2];
        used = 0;
        for (int i=0; i<capacity; ++i) {
            if (oldTable[i] == nullptr || oldTable[i]->next == nullptr)
                continue;
            entry* p = oldTable[i];
            while (p->next != nullptr) {
                p = p->next;
                int index = hash(p->key);
                if (table[index] == nullptr) {
                    used++;
                    table[index] = new entry;
                }
                table[index]->next = new entry(p->key, p->value, table[index]->next);
            }
        }
        capacity *= 2;
    }
};

#endif