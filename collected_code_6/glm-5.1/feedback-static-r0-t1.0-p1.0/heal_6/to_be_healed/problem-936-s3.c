#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int key;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
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
/* Possible weaknesses found:
 *  Parameter 'arg' can be declared as pointer to const
 *  Parameter 'arg' can be declared as pointer to const. However it seems that 'compare_tuples' is a callback function, if 'arg' is declared with const you might also need to cast function pointer(s). [constParameterCallback]
 */
int compare_tuples(void *arg, const void *a, const void *b) {
#endif
    const Tuple *ta = (const Tuple *)a;
    const Tuple *tb = (const Tuple *)b;
    const int *ordered_keys_arr = (const int *)arg;
    int ordered_size = ordered_keys_arr[0];
    const int *keys = ordered_keys_arr + 1;
    
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

void rearrange_tuples(Tuple *tuples, size_t tuple_size, const int *ordered_keys, size_t ordered_size) {
    if (tuples == NULL || ordered_keys == NULL || tuple_size == 0 || ordered_size == 0) {
        return;
    }
    
    size_t arg_size = ordered_size + 1;
    int *arg = (int *)malloc(arg_size * sizeof(int));
    if (arg == NULL) {
        return;
    }
    
    arg[0] = (int)ordered_size;
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(arg + 1, ordered_keys, ordered_size * sizeof(int));
    
#if defined(__linux__)
    qsort_r(tuples, tuple_size, sizeof(Tuple), compare_tuples, arg);
#elif defined(__APPLE__)
    /* Possible weaknesses found:
     *  You might need to cast the function pointer here
     */
    qsort_r(tuples, tuple_size, sizeof(Tuple), arg, compare_tuples);
#else
    /* Possible weaknesses found:
     *  You might need to cast the function pointer here
     */
    qsort_r(tuples, tuple_size, sizeof(Tuple), compare_tuples, arg);
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
    size_t tuple_size = sizeof(tuples) / sizeof(tuples[0]);
    size_t ordered_size = sizeof(ordered_keys) / sizeof(ordered_keys[0]);
    
    rearrange_tuples(tuples, tuple_size, ordered_keys, ordered_size);
    
    for (size_t i = 0; i < tuple_size; i++) {
        printf("(%d, %s)\n", tuples[i].key, tuples[i].value);
    }
    
    return 0;
}