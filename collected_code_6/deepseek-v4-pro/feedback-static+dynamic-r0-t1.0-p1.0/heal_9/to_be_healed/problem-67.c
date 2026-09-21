#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    unsigned long long *digits;
    int size;
    int capacity;
} BigInt;

void bigint_init(BigInt *num, unsigned long long value) {
    num->capacity = 10;
    num->size = 0;
    num->digits = (unsigned long long *)calloc(num->capacity, sizeof(unsigned long long));
    if (num->digits == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    while (value > 0) {
        num->digits[num->size++] = value % 10;
        value /= 10;
    }
    if (num->size == 0) {
        num->size = 1;
        num->digits[0] = 0;
    }
}

void bigint_free(BigInt *num) {
    free(num->digits);
    num->digits = NULL;
    num->size = 0;
    num->capacity = 0;
}

void bigint_resize(BigInt *num, int new_capacity) {
    if (new_capacity <= num->capacity) return;
    unsigned long long *new_digits = (unsigned long long *)realloc(num->digits, new_capacity * sizeof(unsigned long long));
    if (new_digits == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    num->digits = new_digits;
    num->capacity = new_capacity;
}

void bigint_add(BigInt *result, const BigInt *a, const BigInt *b) {
    int max_size = a->size > b->size ? a->size : b->size;
    bigint_resize(result, max_size + 1);
    
    unsigned long long carry = 0;
    int i;
    for (i = 0; i < max_size || carry; i++) {
        unsigned long long sum = carry;
        if (i < a->size) sum += a->digits[i];
        if (i < b->size) sum += b->digits[i];
        result->digits[i] = sum % 10;
        carry = sum / 10;
    }
    result->size = i;
    
    while (result->size > 1 && result->digits[result->size - 1] == 0) {
        result->size--;
    }
}

void bigint_copy(BigInt *dest, const BigInt *src) {
    if (dest->capacity < src->size) {
        bigint_resize(dest, src->size);
    }
    /* Possible weaknesses found:
     *  Assuming that condition 'dest->capacity<src->size' is not redundant
     */
    if (dest->capacity < src->size) {
        fprintf(stderr, "Buffer overflow prevented in bigint_copy\n");
        exit(1);
    }
    if (src->size > 0) {
        /* Possible weaknesses found:
         *  Assuming condition is false
         */
        if (dest->digits == NULL || src->digits == NULL) {
            fprintf(stderr, "Null pointer in bigint_copy\n");
            exit(1);
        }
        /* Possible weaknesses found:
         *  Condition 'src->size>dest->capacity' is always false [knownConditionTrueFalse]
         *  Condition 'src->size>dest->capacity' is always false
         */
        if (src->size > dest->capacity) {
            fprintf(stderr, "Buffer overflow detected in bigint_copy\n");
            exit(1);
        }
        size_t copy_size = src->size * sizeof(unsigned long long);
        unsigned long long *safe_dest = dest->digits;
        const unsigned long long *safe_src = src->digits;
        if (copy_size > (size_t)(dest->capacity) * sizeof(unsigned long long)) {
            fprintf(stderr, "Buffer overflow prevented in bigint_copy\n");
            exit(1);
        }
        for (int i = 0; i < src->size; i++) {
            safe_dest[i] = safe_src[i];
        }
    }
    dest->size = src->size;
}

void bigint_print(const BigInt *num) {
    for (int i = num->size - 1; i >= 0; i--) {
        printf("%llu", num->digits[i]);
    }
}

BigInt *bell_number(int n) {
    if (n < 0) {
        BigInt *zero = (BigInt *)malloc(sizeof(BigInt));
        if (zero == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(1);
        }
        bigint_init(zero, 0);
        return zero;
    }
    if (n == 0) {
        BigInt *one = (BigInt *)malloc(sizeof(BigInt));
        if (one == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(1);
        }
        bigint_init(one, 1);
        return one;
    }

    BigInt **bell = (BigInt **)malloc((n + 1) * sizeof(BigInt *));
    if (bell == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    
    for (int i = 0; i <= n; i++) {
        bell[i] = (BigInt *)malloc(sizeof(BigInt));
        if (bell[i] == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(1);
        }
        bigint_init(bell[i], 0);
    }
    
    bigint_init(bell[0], 1);
    
    for (int i = 1; i <= n; i++) {
        BigInt prev;
        bigint_init(&prev, 1);
        
        for (int j = 1; j <= i; j++) {
            BigInt curr;
            bigint_init(&curr, 0);
            
            bigint_add(&curr, bell[i - j], &prev);
            bigint_copy(bell[i - j], &prev);
            bigint_copy(&prev, &curr);
            
            if (j == i) {
                bigint_copy(bell[i], &curr);
            }
            
            bigint_free(&curr);
        }
        
        bigint_free(&prev);
    }

    BigInt *result = (BigInt *)malloc(sizeof(BigInt));
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    bigint_init(result, 0);
    bigint_copy(result, bell[n]);
    
    for (int i = 0; i <= n; i++) {
        bigint_free(bell[i]);
        free(bell[i]);
    }
    free(bell);
    
    return result;
}

int main(void) {
    int n;
    printf("Enter n: ");
    if (scanf("%d", &n) != 1) {
        printf("Invalid input\n");
        return 1;
    }
    if (n < 0) {
        printf("Invalid input\n");
        return 1;
    }
    
    BigInt *result = bell_number(n);
    printf("Bell number B%d = ", n);
    bigint_print(result);
    printf("\n");
    
    bigint_free(result);
    free(result);
    
    return 0;
}