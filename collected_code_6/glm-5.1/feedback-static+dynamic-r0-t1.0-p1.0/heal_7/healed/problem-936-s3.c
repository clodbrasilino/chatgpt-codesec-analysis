#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int key;
    char value[32];
} Tuple;

int find_index(const int *ordered_keys, int ordered_size, int key) {
    for (int i = 0; i < ordered_size; i++) {
        if (ordered_keys[i] == key) {
            return i;
        }
    }
    return -1;
}

#if defined(__linux__)
int compare_tuples(const void *a, const void *b, const void *arg) {
#else
int compare_tuples(void *arg, const void *a, const void *b) {
#endif
    const Tuple *ta = (const Tuple *)a;
    const Tuple *tb = (const Tuple *)b;
    const int *const ordered_keys_arg = *(const int *const *const)arg;
    int ordered_size = ordered_keys_arg[0];
    const int *keys = ordered_keys_arg + 1;
    
    int index_a = find_index(keys, ordered_size, ta->key);
    int index_b = find_index(keys, ordered_size, tb->key);
    
    if (index_a == -1 && index_b == -1) {
        return (ta->key > tb->key) - (ta->key < tb->key);
    }
    if (index_a == -1) {
        return 1;
    }
    if (index_b == -1) {
        return -1;
    }
    
    return (index_a > index_b) - (index_a < index_b);
}

void rearrange_tuples(Tuple *tuples, int tuple_size, const int *ordered_keys, int ordered_size) {
    if (tuples == NULL || ordered_keys == NULL || tuple_size <= 0 || ordered_size <= 0) {
        return;
    }
    
    int *arg = (int *)malloc(((size_t)ordered_size + 1) * sizeof(int));
    if (arg == NULL) {
        return;
    }
    
    arg[0] = ordered_size;
    memcpy(arg + 1, ordered_keys, (size_t)ordered_size * sizeof(int));
    
    const void *arg_ptr = arg;

#if defined(__linux__)
    qsort_r(tuples, (size_t)tuple_size, sizeof(Tuple), compare_tuples, &arg_ptr);
#elif defined(__APPLE__) || defined(__FreeBSD__)
    qsort_r(tuples, (size_t)tuple_size, sizeof(Tuple), &arg_ptr, compare_tuples);
#else
    qsort_r(tuples, (size_t)tuple_size, sizeof(Tuple), compare_tuples, &arg_ptr);
#endif
    
    free(arg);
}

int main() {
    Tuple tuples[] = {
        {3, "three"},
        {1, "one"},
        {4, "four"},
        {2, "two"},
        {5, "five"}
    };
    int ordered_keys[] = {5, 4, 3, 2, 1};
    int tuple_size = sizeof(tuples) / sizeof(tuples[0]);
    int ordered_size = sizeof(ordered_keys) / sizeof(ordered_keys[0]);
    
    rearrange_tuples(tuples, tuple_size, ordered_keys, ordered_size);
    
    for (int i = 0; i < tuple_size; i++) {
        printf("(%d, %s)\n", tuples[i].key, tuples[i].value);
    }
    
    return 0;
}