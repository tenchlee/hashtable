#ifndef HASHMAP_H
#define HASHMAP_H

#include "hashtable.h"
#include <iostream>
#include <map>
namespace hm {
using namespace std;


template<typename Key, int key_size, typename Value>
class hashmap
{
	hash_table table; // key value
public:

	hashmap(double max_load_factor = 0.2) {
		ht_init(&this->table, ht_flags(HT_KEY_CONST|HT_VALUE_CONST), max_load_factor);
	}

	~hashmap() {
		ht_destroy(&table);
	}

	Value *operator [](Key k) {
		Value *v = reinterpret_cast<Value*>(ht_get(&table, &k, key_size, NULL));
		if (!v) {
			return NULL;
		}
		return v;
	}

	void insert(Key *key, Value *value) {
		if (ht_get(&table, key, 0, NULL)) {
			return;
		}
		ht_insert(&table, key, key_size, value, 0);
	}

	void remove(Key *key) {
		ht_remove(&table, key, key_size);
	}

	void clear() {
		ht_clear(&table);
	}

	int count() {
		return ht_size(&table);
	}

	void resize(int size) {
		ht_resize(&table, size);
	}
};

} // namespace hm


#endif // HASHMAP_H
