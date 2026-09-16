#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a;
    int b;
} Tuple;

int count_digits(int n) {
    if (n == 0) return 1;
    int count = 0;
    if (n < 0) n = -n;
    while (n > 0) {
        count++;
        n /= 10;
    }
    return count;
}

int total_digits(const void *x, const void *y) {
    const Tuple *t1 = (const Tuple *)x;
    const Tuple *t2 = (const Tuple *)y;
    int d1 = count_digits(t1->a) + count_digits(t1->b);
    int d2 = count_digits(t2->a) + count_digits(t2->b);
    return d1 - d2;
}

int main() {
    Tuple list[] = {{123, 4}, {5, 67}, {8, 9}, {12, 3456}};
    size_t len = sizeof(list) / sizeof(list[0]);
    
    qsort(list, len, sizeof(Tuple), total_digits);
    
    for (size_t i = 0; i < len; i++) {
        printf("(%d, %d)\n", list[i].a, list[i].b);
    }
    
    return 0;
}