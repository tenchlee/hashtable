#include <stdint.h>
#include <iostream>
#include <assert.h>

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "hashmap.h"
#include "timer.h"


using namespace hm;
using namespace std;

typedef struct Key {
	uint32_t ip;
	uint32_t port;
}Key_t;

typedef int Value_t;

int main() {
	hashmap<Key_t, sizeof(Key_t), Value_t> h;
	Key_t k1;
	k1.ip = 1111;
	k1.port = 2222;

	Value_t *v = h[k1];
	assert(v==NULL);
	Value_t tv = 1;
	h.insert(&k1, &tv);
	v = h[k1];
	assert(v!=NULL);

	h.resize(10000);
	v = h[k1];
	assert(v!=NULL);

	h.clear();
	v = h[k1];
	assert(v==NULL);

#define TEST_COUNT 100000

	srand(time(NULL));
	Key_t key[TEST_COUNT];
	Value_t val[TEST_COUNT];
	int i = 0;
    for (i = 0; i < TEST_COUNT; i++) {
        key[i].ip = rand();
        key[i].port = rand();
    }
	for (i = 0; i < TEST_COUNT; i++) {
		val[i] = i;
	}
	struct timespec t1;
    struct timespec t2;

	t1 = snap_time();
	for (i = 0; i < TEST_COUNT; i++) {
		h.insert(&key[i], &val[i]);
	}
	t2 = snap_time();

	// test get
	for (i = 0; i < TEST_COUNT; i++) {
		v = h[key[i]];
		if (*v != val[i]) {
			cout << "index " << i << " error" << endl;
			cout << "get " << *v << "need " << val[i] << endl;
			assert(0);
		}
	}

	fprintf(stderr, "Insert %d keys took %.2f seconds\n", TEST_COUNT, get_elapsed(t1, t2));

	t1 = snap_time();
	for (i = 0; i < TEST_COUNT; i++) {
		h[key[i]];
	}
	t2 = snap_time();
	fprintf(stderr, "Get %d keys took %.2f seconds\n", TEST_COUNT, get_elapsed(t1, t2));

	//test remove

	h.remove(&key[10]);
	assert(h[key[10]] == NULL);



}
