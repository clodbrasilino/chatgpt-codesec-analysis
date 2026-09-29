#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DIGITS 1000

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char digits[MAX_DIGITS];
    int length;
} BigInt;

void bigint_init(BigInt *num) {
    if (num == NULL) {
        return;
    }
    memset(num->digits, 0, MAX_DIGITS);
    num->length = 1;
}

void bigint_set_ull(BigInt *num, unsigned long long val) {
    if (num == NULL) {
        return;
    }
    bigint_init(num);
    num->length = 0;
    
    if (val == 0) {
        num->digits[0] = 0;
        num->length = 1;
        return;
    }
    
    while (val > 0 && num->length < MAX_DIGITS) {
        num->digits[num->length++] = (unsigned char)(val % 10);
        val /= 10;
    }
}

void bigint_add(const BigInt *a, const BigInt *b, BigInt *result) {
    if (a == NULL || b == NULL || result == NULL) {
        return;
    }
    if (a->length > MAX_DIGITS || b->length > MAX_DIGITS) {
        return;
    }
    
    int max_len = a->length > b->length ? a->length : b->length;
    int carry = 0;
    int i;
    
    bigint_init(result);
    result->length = 0;
    
    for (i = 0; (i < max_len || carry) && i < MAX_DIGITS; i++) {
        int digit_a = (i < a->length) ? a->digits[i] : 0;
        int digit_b = (i < b->length) ? b->digits[i] : 0;
        int sum = digit_a + digit_b + carry;
        
        if (result->length < MAX_DIGITS) {
            result->digits[result->length++] = (unsigned char)(sum % 10);
            carry = sum / 10;
        }
    }
}

void bigint_copy(BigInt *dest, const BigInt *src) {
    if (dest == NULL || src == NULL) {
        return;
    }
    if (dest == src) {
        return;
    }
    if (src->length <= 0 || src->length > MAX_DIGITS) {
        return;
    }
    
    size_t copy_size = (size_t)src->length;
    if (copy_size > (size_t)MAX_DIGITS) {
        return;
    }
    if (copy_size > (size_t)(MAX_DIGITS - 0)) {
        return;
    }
    
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(dest->digits, src->digits, copy_size);
    dest->length = src->length;
}

void bigint_print(const BigInt *num) {
    if (num == NULL) {
        return;
    }
    if (num->length <= 0 || num->length > MAX_DIGITS) {
        return;
    }
    for (int i = num->length - 1; i >= 0; i--) {
        printf("%d", num->digits[i]);
    }
}

void bell_number(int n, BigInt *result) {
    if (result == NULL) {
        return;
    }
    
    if (n < 0 || n >= MAX_DIGITS) {
        bigint_set_ull(result, 0);
        return;
    }
    if (n == 0) {
        bigint_set_ull(result, 1);
        return;
    }
    
    BigInt *bell = (BigInt *)calloc((size_t)(n + 1), sizeof(BigInt));
    if (!bell) {
        bigint_set_ull(result, 0);
        return;
    }
    
    for (int i = 0; i <= n; i++) {
        bigint_init(&bell[i]);
    }
    
    bigint_set_ull(&bell[0], 1);
    
    for (int i = 1; i <= n; i++) {
        BigInt prev;
        bigint_init(&prev);
        bigint_copy(&prev, &bell[0]);
        bigint_copy(&bell[0], &bell[i - 1]);
        
        for (int j = 1; j <= i; j++) {
            BigInt temp;
            bigint_init(&temp);
            bigint_copy(&temp, &bell[j]);
            bigint_add(&prev, &bell[j - 1], &bell[j]);
            bigint_copy(&prev, &temp);
        }
    }
    
    bigint_copy(result, &bell[n]);
    free(bell);
}

int main(void) {
    int n;
    printf("Enter n: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    if (n < 0) {
        fprintf(stderr, "n must be non-negative\n");
        return 1;
    }
    
    BigInt result;
    bigint_init(&result);
    
    bell_number(n, &result);
    
    printf("Bell number B_%d = ", n);
    bigint_print(&result);
    printf("\n");
    
    return 0;
}