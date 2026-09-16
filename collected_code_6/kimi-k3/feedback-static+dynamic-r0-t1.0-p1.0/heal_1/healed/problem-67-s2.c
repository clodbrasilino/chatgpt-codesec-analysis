#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DIGITS 100

typedef struct {
    unsigned long long digits[MAX_DIGITS];
    int size;
} BigInt;

void bigint_init(BigInt *num) {
    memset(num->digits, 0, sizeof(num->digits));
    num->size = 1;
}

void bigint_add(BigInt *result, const BigInt *a, const BigInt *b) {
    BigInt temp;
    bigint_init(&temp);
    
    int max_size = (a->size > b->size) ? a->size : b->size;
    unsigned long long carry = 0;
    
    for (int i = 0; i < max_size || carry; i++) {
        unsigned long long sum = carry;
        if (i < a->size) sum += a->digits[i];
        if (i < b->size) sum += b->digits[i];
        
        temp.digits[i] = sum % 1000000000000000000ULL;
        carry = sum / 1000000000000000000ULL;
        temp.size = i + 1;
    }
    
    *result = temp;
}

void bigint_print(const BigInt *num) {
    printf("%llu", num->digits[num->size - 1]);
    for (int i = num->size - 2; i >= 0; i--) {
        printf("%018llu", num->digits[i]);
    }
}

void bell_number(int n, BigInt *result) {
    if (n < 0) {
        bigint_init(result);
        return;
    }
    
    BigInt **bell_triangle = (BigInt **)malloc((size_t)(n + 1) * sizeof(BigInt *));
    if (bell_triangle == NULL) {
        bigint_init(result);
        return;
    }
    
    for (int i = 0; i <= n; i++) {
        bell_triangle[i] = (BigInt *)malloc((size_t)(n + 1) * sizeof(BigInt));
        if (bell_triangle[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(bell_triangle[j]);
            }
            free(bell_triangle);
            bigint_init(result);
            return;
        }
        for (int j = 0; j <= n; j++) {
            bigint_init(&bell_triangle[i][j]);
        }
    }
    
    bell_triangle[0][0].digits[0] = 1;
    
    for (int i = 1; i <= n; i++) {
        bell_triangle[i][0] = bell_triangle[i - 1][i - 1];
        for (int j = 1; j <= i; j++) {
            bigint_add(&bell_triangle[i][j], &bell_triangle[i - 1][j - 1], &bell_triangle[i][j - 1]);
        }
    }
    
    *result = bell_triangle[n][0];
    
    for (int i = 0; i <= n; i++) {
        free(bell_triangle[i]);
    }
    free(bell_triangle);
}

int main(void) {
    int n;
    
    if (scanf("%d", &n) != 1) {
        return 1;
    }
    
    if (n < 0) {
        return 1;
    }
    
    BigInt result;
    bell_number(n, &result);
    bigint_print(&result);
    printf("\n");
    
    return 0;
}