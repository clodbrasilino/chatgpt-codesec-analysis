#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct List {
    int *data;
    size_t size;
} List;

bool are_lists_equal(List a, List b) {
    if (a.size != b.size) return false;
    for (size_t i = 0; i < a.size; i++) {
        if (a.data[i] != b.data[i]) return false;
    }
    return true;
}

int count_unique_lists(List *lists, size_t list_count) {
    int unique_count = 0;
    for (size_t i = 0; i < list_count; i++) {
        bool is_unique = true;
        for (size_t j = 0; j < i; j++) {
            if (are_lists_equal(lists[i], lists[j])) {
                is_unique = false;
                break;
            }
        }
        if (is_unique) {
            unique_count++;
        }
    }
    return unique_count;
}

int main(void) {
    List lists[] = {
        { (int[2]){1, 2}, 2 },
        { (int[2]){3, 4}, 2 },
        { (int[2]){1, 2}, 2 },
        { (int[3]){5, 6, 7}, 3 }
    };
    
    size_t list_count = sizeof(lists) / sizeof(lists[0]);
    
    int unique_count = count_unique_lists(lists, list_count);
    
    printf("Number of unique lists: %d\n", unique_count);
    
    return 0;
}