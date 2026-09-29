#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int first;
    int second;
} Tuple;

int count_digits(int num) {
    if (num == 0) return 1;
    int count = 0;
    if (num < 0) num = -num;
    while (num > 0) {
        count++;
        num /= 10;
    }
    return count;
}

int compare_tuples(const void *a, const void *b) {
    const Tuple *ta = (const Tuple *)a;
    const Tuple *tb = (const Tuple *)b;
    int total_a = count_digits(ta->first) + count_digits(ta->second);
    int total_b = count_digits(tb->first) + count_digits(tb->second);
    if (total_a < total_b) return -1;
    if (total_a > total_b) return 1;
    return 0;
}

void sort_tuple_list(Tuple *list, size_t size) {
    if (list == NULL || size == 0) return;
    qsort(list, size, sizeof(Tuple), compare_tuples);
}

int main(void) {
    Tuple list[] = {
        {120, 4},
        {-8, 90},
        {5, -600},
        {12, 3}
    };
    size_t size = sizeof(list) / sizeof(list[0]);

    for (size_t i = 0; i < size; i++) {
        printf("(%d, %d) ", list[i].first, list[i].second);
    }
    printf("\n");

    sort_tuple_list(list, size);

    for (size_t i = 0; i < size; i++) {
        printf("(%d, %d) ", list[i].first, list[i].second);
    }
    printf("\n");

    return 0;
}