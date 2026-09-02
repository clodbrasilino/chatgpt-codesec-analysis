#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a;
    int b;
} Tuple;

int countDigits(int n) {
    int count = 0;
    if (n <= 0) count++;
    while (n) {
        count++;
        n /= 10;
    }
    return count;
}

int totalDigits(Tuple t) {
    return countDigits(t.a) + countDigits(t.b);
}

int compareTuples(const void *t1, const void *t2) {
    int digits1 = totalDigits(*(Tuple *)t1);
    int digits2 = totalDigits(*(Tuple *)t2);
    return digits1 - digits2;
}

void sortTuples(Tuple *tuples, int size) {
    qsort(tuples, size, sizeof(Tuple), compareTuples);
}

int main() {
    Tuple tuples[] = {{123, 456}, {789, 10}, {11, 22}, {3, 4}};
    int size = sizeof(tuples) / sizeof(tuples[0]);

    sortTuples(tuples, size);

    for (int i = 0; i < size; ++i) {
        printf("(%d, %d) ", tuples[i].a, tuples[i].b);
    }

    return 0;
}