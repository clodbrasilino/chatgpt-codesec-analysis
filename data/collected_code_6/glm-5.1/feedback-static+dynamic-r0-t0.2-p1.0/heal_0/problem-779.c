#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *data;
    size_t len;
} List;

int list_equal(const List *a, const List *b) {
    if (a->len != b->len) {
        return 0;
    }
    for (size_t i = 0; i < a->len; i++) {
        if (a->data[i] != b->data[i]) {
            return 0;
        }
    }
    return 1;
}

size_t count_unique_lists(List *lists, size_t count) {
    if (count == 0) {
        return 0;
    }
    
    int *seen = (int *)malloc(count * sizeof(int));
    if (seen == NULL) {
        return 0;
    }
    
    for (size_t i = 0; i < count; i++) {
        seen[i] = 0;
    }
    
    size_t unique_count = 0;
    
    for (size_t i = 0; i < count; i++) {
        if (seen[i] == 0) {
            unique_count++;
            for (size_t j = i + 1; j < count; j++) {
                if (seen[j] == 0 && list_equal(&lists[i], &lists[j])) {
                    seen[j] = 1;
                }
            }
        }
    }
    
    free(seen);
    return unique_count;
}

int main(void) {
    int a1[] = {1, 2, 3};
    int a2[] = {4, 5};
    int a3[] = {1, 2, 3};
    int a4[] = {7};
    int a5[] = {4, 5};
    
    List lists[5];
    
    lists[0].data = a1;
    lists[0].len = 3;
    
    lists[1].data = a2;
    lists[1].len = 2;
    
    lists[2].data = a3;
    lists[2].len = 3;
    
    lists[3].data = a4;
    lists[3].len = 1;
    
    lists[4].data = a5;
    lists[4].len = 2;
    
    size_t unique = count_unique_lists(lists, 5);
    printf("%zu\n", unique);
    
    return 0;
}