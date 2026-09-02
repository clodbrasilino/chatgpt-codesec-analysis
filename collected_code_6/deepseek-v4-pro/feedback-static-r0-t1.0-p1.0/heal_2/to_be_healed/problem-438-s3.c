#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

typedef struct PairNode {
    Tuple tuple;
    struct PairNode *next;
} PairNode;

typedef struct {
    PairNode **buckets;
    int size;
} HashSet;

static unsigned int hash_tuple(Tuple t, int size) {
    unsigned int a = (unsigned int)t.first * 2654435761u;
    unsigned int b = (unsigned int)t.second * 2246822519u;
    return (a ^ b) % (unsigned int)size;
}

static HashSet *hashset_create(int size) {
    HashSet *set = (HashSet *)malloc(sizeof(HashSet));
    if (set == NULL) {
        return NULL;
    }
    set->buckets = (PairNode **)calloc((size_t)size, sizeof(PairNode *));
    if (set->buckets == NULL) {
        free(set);
        return NULL;
    }
    set->size = size;
    return set;
}

static int hashset_insert(HashSet *set, Tuple t) {
    unsigned int index = hash_tuple(t, set->size);
    PairNode *current = set->buckets[index];
    while (current != NULL) {
        if (current->tuple.first == t.first && current->tuple.second == t.second) {
            return 0;
        }
        current = current->next;
    }
    PairNode *node = (PairNode *)malloc(sizeof(PairNode));
    if (node == NULL) {
        return -1;
    }
    node->tuple = t;
    node->next = set->buckets[index];
    set->buckets[index] = node;
    return 1;
}

static int hashset_contains(const HashSet *set, Tuple t) {
    unsigned int index = hash_tuple(t, set->size);
    PairNode *current = set->buckets[index];
    while (current != NULL) {
        if (current->tuple.first == t.first && current->tuple.second == t.second) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

static void hashset_destroy(HashSet *set) {
    if (set == NULL) {
        return;
    }
    for (int i = 0; i < set->size; i++) {
        PairNode *current = set->buckets[i];
        while (current != NULL) {
            PairNode *next = current->next;
            free(current);
            current = next;
        }
    }
    free(set->buckets);
    free(set);
}

int count_bidirectional_pairs(const Tuple *tuples, int tuple_count) {
    if (tuples == NULL || tuple_count <= 0) {
        return 0;
    }
    int set_size = tuple_count * 2 + 1;
    HashSet *set = hashset_create(set_size);
    if (set == NULL) {
        return 0;
    }
    int count = 0;
    HashSet *seen_pairs = hashset_create(set_size);
    if (seen_pairs == NULL) {
        hashset_destroy(set);
        return 0;
    }
    for (int i = 0; i < tuple_count; i++) {
        hashset_insert(set, tuples[i]);
    }
    for (int i = 0; i < tuple_count; i++) {
        Tuple current = tuples[i];
        Tuple reversed;
        reversed.first = current.second;
        reversed.second = current.first;
        if (current.first != current.second && hashset_contains(set, reversed)) {
            Tuple canonical;
            if (current.first < current.second) {
                canonical.first = current.first;
                canonical.second = current.second;
            } else {
                canonical.first = current.second;
                canonical.second = current.first;
            }
            int inserted = hashset_insert(seen_pairs, canonical);
            if (inserted == 1) {
                count++;
            }
        }
    }
    hashset_destroy(set);
    hashset_destroy(seen_pairs);
    return count;
}

int main(void) {
    /* Possible weaknesses found:
     *  Variable 'tuples' can be declared as const array [constVariable]
     */
    Tuple tuples[] = {
        {1, 2},
        {2, 1},
        {3, 4},
        {1, 2},
        {4, 3},
        {5, 6}
    };
    int count = count_bidirectional_pairs(tuples, 6);
    printf("%d\n", count);
    return 0;
}