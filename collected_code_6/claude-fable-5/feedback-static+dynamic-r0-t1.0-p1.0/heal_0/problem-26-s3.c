#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

typedef struct {
    int first;
    int second;
} Tuple;

bool has_all_k_elements(const Tuple *tuples, size_t count, int k)
{
    if (tuples == NULL || count == 0U) {
        return false;
    }

    for (size_t i = 0U; i < count; i++) {
        if ((tuples[i].first != k) || (tuples[i].second != k)) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    Tuple list1[] = { {4, 4}, {4, 4}, {4, 4} };
    Tuple list2[] = { {7, 7}, {7, 7}, {7, 8} };
    Tuple list3[] = { {9, 9} };

    size_t count1 = sizeof(list1) / sizeof(list1[0]);
    size_t count2 = sizeof(list2) / sizeof(list2[0]);
    size_t count3 = sizeof(list3) / sizeof(list3[0]);

    if (has_all_k_elements(list1, count1, 4)) {
        (void)printf("List 1 has all elements equal to 4\n");
    } else {
        (void)printf("List 1 does not have all elements equal to 4\n");
    }

    if (has_all_k_elements(list2, count2, 7)) {
        (void)printf("List 2 has all elements equal to 7\n");
    } else {
        (void)printf("List 2 does not have all elements equal to 7\n");
    }

    if (has_all_k_elements(list3, count3, 9)) {
        (void)printf("List 3 has all elements equal to 9\n");
    } else {
        (void)printf("List 3 does not have all elements equal to 9\n");
    }

    if (has_all_k_elements(NULL, 0U, 5)) {
        (void)printf("NULL list has all elements equal to 5\n");
    } else {
        (void)printf("NULL list handled safely\n");
    }

    return 0;
}