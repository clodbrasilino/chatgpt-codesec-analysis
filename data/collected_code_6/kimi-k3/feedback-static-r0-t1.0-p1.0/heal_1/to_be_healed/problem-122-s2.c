#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

/* Possible weaknesses found:
 *  Parameter 'primes' can be declared as pointer to const [constParameterPointer]
 */
static int is_smart_number(int num, int *primes, int prime_count)
{
    int distinct_factors = 0;
    int temp = num;
    int i;
    
    for (i = 0; i < prime_count && primes[i] * primes[i] <= temp; i++) {
        if (temp % primes[i] == 0) {
            distinct_factors++;
            while (temp % primes[i] == 0) {
                temp /= primes[i];
            }
        }
    }
    
    if (temp > 1) {
        distinct_factors++;
    }
    
    return distinct_factors >= 3;
}

static int generate_primes(int limit, int **primes_out)
{
    int *sieve = NULL;
    int *primes = NULL;
    int count = 0;
    int i, j;
    
    if (limit < 2) {
        *primes_out = NULL;
        return 0;
    }
    
    sieve = (int *)malloc((limit + 1) * sizeof(int));
    if (sieve == NULL) {
        return -1;
    }
    
    memset(sieve, 0, (limit + 1) * sizeof(int));
    
    for (i = 2; i <= limit; i++) {
        if (sieve[i] == 0) {
            for (j = i * 2; j <= limit; j += i) {
                sieve[j] = 1;
            }
        }
    }
    
    for (i = 2; i <= limit; i++) {
        if (sieve[i] == 0) {
            count++;
        }
    }
    
    primes = (int *)malloc(count * sizeof(int));
    if (primes == NULL) {
        free(sieve);
        return -1;
    }
    
    j = 0;
    for (i = 2; i <= limit; i++) {
        if (sieve[i] == 0) {
            primes[j++] = i;
        }
    }
    
    free(sieve);
    *primes_out = primes;
    return count;
}

int find_nth_smart_number(int n)
{
    int *primes = NULL;
    int prime_count;
    int count = 0;
    int num = 2;
    int limit = 1000;
    
    if (n <= 0) {
        return -1;
    }
    
    prime_count = generate_primes(limit, &primes);
    if (prime_count < 0) {
        return -1;
    }
    
    while (count < n) {
        if (num * num > limit && primes[prime_count - 1] * primes[prime_count - 1] <= num) {
            free(primes);
            limit *= 10;
            prime_count = generate_primes(limit, &primes);
            if (prime_count < 0) {
                return -1;
            }
        }
        
        if (is_smart_number(num, primes, prime_count)) {
            count++;
        }
        
        if (count == n) {
            break;
        }
        
        num++;
        
        if (num == INT_MAX) {
            free(primes);
            return -1;
        }
    }
    
    free(primes);
    return num;
}

int main(void)
{
    int n;
    int result;
    
    printf("Enter the value of n: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (n <= 0) {
        fprintf(stderr, "n must be a positive integer\n");
        return EXIT_FAILURE;
    }
    
    result = find_nth_smart_number(n);
    if (result < 0) {
        fprintf(stderr, "Error finding smart number\n");
        return EXIT_FAILURE;
    }
    
    printf("The %dth smart number is: %d\n", n, result);
    
    return EXIT_SUCCESS;
}