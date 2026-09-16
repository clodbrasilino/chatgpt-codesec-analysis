#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_TUPLE_SIZE 10

struct Tuple {
    int elements[MAX_TUPLE_SIZE];
    size_t size;
};

static bool check_k_elements(const struct Tuple *tuples, size_t count, int k)
{
    if (tuples == NULL) {
        return false;
    }

    for (size_t i = 0; i < count; i++) {
        if (tuples[i].size > MAX_TUPLE_SIZE) {
            return false;
        }
        for (size_t j = 0; j < tuples[i].size; j++) {
            if (tuples[i].elements[j] != k) {
                return false;
            }
        }
    }

    return true;
}

int main(void)
{
    struct Tuple list1[] = {
        { {4, 4}, 2 },
        { {4, 4, 4}, 3 },
        { {4, 4}, 2 },
        { {4, 4, 4, 4}, 4 },
        { {4}, 1 }
    };
    size_t count1 = sizeof(list1) / sizeof(list1[0]);

    struct Tuple list2[] = {
        { {7, 7, 7}, 3 },
        { {7, 7}, 2 }
    };
    size_t count2 = sizeof(list2) / sizeof(list2[0]);

    struct Tuple list3[] = {
        { {9, 9}, 2 },
        { {9, 2, 9}, 3 }
    };
    size_t count3 = sizeof(list3) / sizeof(list3[0]);

    if (check_k_elements(list1, count1, 4)) {
        printf("List 1: all elements are 4\n");
    } else {
        printf("List 1: not all elements are 4\n");
    }

    if (check_k_elements(list2, count2, 7)) {
        printf("List 2: all elements are 7\n");
    } else {
        printf("List 2: not all elements are 7\n");
    }

    if (check_k_elements(list3, count3, 9)) {
        printf("List 3: all elements are 9\n");
    } else {
        printf("List 3: not all elements are 9\n");
    }

    return EXIT_SUCCESS;
}