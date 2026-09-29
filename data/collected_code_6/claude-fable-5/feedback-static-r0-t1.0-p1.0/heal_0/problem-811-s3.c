#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int first;
    int second;
} Tuple;

bool are_lists_identical(const Tuple *list1, size_t len1, const Tuple *list2, size_t len2)
{
    if (len1 != len2) {
        return false;
    }

    if (len1 == 0) {
        return true;
    }

    if (list1 == NULL || list2 == NULL) {
        return false;
    }

    for (size_t i = 0; i < len1; i++) {
        if (list1[i].first != list2[i].first || list1[i].second != list2[i].second) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    Tuple list_a[] = { {1, 2}, {3, 4}, {5, 6} };
    Tuple list_b[] = { {1, 2}, {3, 4}, {5, 6} };
    Tuple list_c[] = { {1, 2}, {3, 4}, {7, 8} };
    Tuple list_d[] = { {1, 2}, {3, 4} };

    size_t len_a = sizeof(list_a) / sizeof(list_a[0]);
    size_t len_b = sizeof(list_b) / sizeof(list_b[0]);
    size_t len_c = sizeof(list_c) / sizeof(list_c[0]);
    size_t len_d = sizeof(list_d) / sizeof(list_d[0]);

    if (are_lists_identical(list_a, len_a, list_b, len_b)) {
        printf("List A and List B are identical\n");
    } else {
        printf("List A and List B are not identical\n");
    }

    if (are_lists_identical(list_a, len_a, list_c, len_c)) {
        printf("List A and List C are identical\n");
    } else {
        printf("List A and List C are not identical\n");
    }

    if (are_lists_identical(list_a, len_a, list_d, len_d)) {
        printf("List A and List D are identical\n");
    } else {
        printf("List A and List D are not identical\n");
    }

    return EXIT_SUCCESS;
}