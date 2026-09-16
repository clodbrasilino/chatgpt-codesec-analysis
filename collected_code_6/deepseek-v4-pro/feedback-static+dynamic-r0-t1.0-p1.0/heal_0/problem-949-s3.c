#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

int countDigits(int num) {
    if (num == 0) return 1;
    int count = 0;
    if (num < 0) num = -num;
    while (num > 0) {
        count++;
        num /= 10;
    }
    return count;
}

int totalDigits(const Tuple *t) {
    return countDigits(t->first) + countDigits(t->second);
}

int compareTuples(const void *a, const void *b) {
    const Tuple *ta = (const Tuple *)a;
    const Tuple *tb = (const Tuple *)b;
    int digitsA = totalDigits(ta);
    int digitsB = totalDigits(tb);
    return digitsA - digitsB;
}

void sortTuples(Tuple *tuples, size_t size) {
    qsort(tuples, size, sizeof(Tuple), compareTuples);
}

int main(void) {
    Tuple list[] = {
        {123, 45},
        {1, 2},
        {4567, 8},
        {90, 123},
        {0, 5},
        {-12, 345}
    };
    size_t size = sizeof(list) / sizeof(list[0]);

    sortTuples(list, size);

    for (size_t i = 0; i < size; i++) {
        printf("(%d, %d) -> %d digits\n", list[i].first, list[i].second, totalDigits(&list[i]));
    }

    return 0;
}