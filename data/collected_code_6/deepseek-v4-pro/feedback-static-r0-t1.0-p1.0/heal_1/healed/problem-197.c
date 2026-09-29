#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int base;
    int exp;
} Tuple;

long long tuple_power(Tuple t) {
    long long result = 1;
    long long b = t.base;
    int e = t.exp;
    
    if (e < 0) {
        return 0;
    }
    
    if (b == 0 && e == 0) {
        return 1;
    }
    
    while (e > 0) {
        if (e & 1) {
            result *= b;
        }
        b *= b;
        e >>= 1;
    }
    
    return result;
}

void tuple_exponentiation(const Tuple *t1, const Tuple *t2, long long *result1, long long *result2) {
    if (t1 == NULL || t2 == NULL || result1 == NULL || result2 == NULL) {
        return;
    }
    
    *result1 = tuple_power(*t1);
    *result2 = tuple_power(*t2);
}

int main(void) {
    Tuple t1 = {2, 10};
    Tuple t2 = {3, 5};
    long long r1 = 0;
    long long r2 = 0;
    
    tuple_exponentiation(&t1, &t2, &r1, &r2);
    
    printf("%d^%d = %lld\n", t1.base, t1.exp, r1);
    printf("%d^%d = %lld\n", t2.base, t2.exp, r2);
    
    Tuple t3 = {5, 0};
    Tuple t4 = {0, 0};
    tuple_exponentiation(&t3, &t4, &r1, &r2);
    printf("%d^%d = %lld\n", t3.base, t3.exp, r1);
    printf("%d^%d = %lld\n", t4.base, t4.exp, r2);
    
    return 0;
}