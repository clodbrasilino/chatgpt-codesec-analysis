#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a;
    int b;
} Tuple;

int count_digits(int n) {
    if (n == 0) return 1;
    int count = 0;
    long val = n;
    if (val < 0) val = -val;
    while (val > 0) {
        count++;
        val /= 10;
    }
    return count;
}

int compare_tuples(const void *p, const void *q) {
    const Tuple *t1 = (const Tuple *)p;
    const Tuple *t2 = (const Tuple *)q;
    int sum1 = count_digits(t1->a) + count_digits(t1->b);
    int sum2 = count_digits(t2->a) + count_digits(t2->b);
    if (sum1 < sum2) return -1;
    if (sum1 > sum2) return 1;
    return 0;
}

void sort_tuple_list(Tuple *list, size_t size) {
    if (list != NULL && size > 0) {
        qsort(list, size, sizeof(Tuple), compare_tuples);
    }
}

int main(void) {
    Tuple list[] = {{123, 4}, {-56, 7890}, {1, 22}, {0, -5}};
    size_t size = sizeof(list) / sizeof(list[0]);

    sort_tuple_list(list, size);

    for (size_t i = 0; i < size; i++) {
        printf("(%d, %d)\n", list[i].a, list[i].b);
    }

    return 0;
}