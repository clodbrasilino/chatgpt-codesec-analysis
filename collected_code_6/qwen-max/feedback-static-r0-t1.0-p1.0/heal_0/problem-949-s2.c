#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int a;
    int b;
} Tuple;

int count_digits(int n) {
    int count = 0;
    if (n == 0) return 1;
    n = abs(n);
    while (n > 0) {
        count++;
        n /= 10;
    }
    return count;
}

int total_digits(Tuple t) {
    return count_digits(t.a) + count_digits(t.b);
}

int compare(const void *a, const void *b) {
    Tuple *t1 = (Tuple *)a;
    Tuple *t2 = (Tuple *)b;
    int diff = total_digits(*t1) - total_digits(*t2);
    if (diff != 0) {
        return diff;
    }
    return t1->a - t2->a;
}

void print_tuples(Tuple *tuples, int size) {
    for (int i = 0; i < size; i++) {
        printf("(%d, %d) ", tuples[i].a, tuples[i].b);
    }
    printf("\n");
}

int main() {
    Tuple tuples[] = {{34, 100}, {7, 8}, {90, 3}, {50, 20}};
    int size = sizeof(tuples) / sizeof(tuples[0]);
    
    qsort(tuples, size, sizeof(Tuple), compare);
    
    print_tuples(tuples, size);
    
    return 0;
}