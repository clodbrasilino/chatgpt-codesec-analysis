#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

long long next_bigger_number(long long n) {
    if (n < 0) {
        return -1;
    }

    int digits[20];
    int len = 0;
    long long temp = n;

    if (temp == 0) {
        digits[len++] = 0;
    } else {
        while (temp > 0) {
            digits[len++] = temp % 10;
            temp /= 10;
        }
    }

    int i = 1;
    while (i < len && digits[i] >= digits[i - 1]) {
        i++;
    }

    if (i == len) {
        return -1;
    }

    int j = 0;
    while (digits[j] <= digits[i]) {
        j++;
    }

    int swap = digits[i];
    digits[i] = digits[j];
    digits[j] = swap;

    int left = 0;
    int right = i - 1;
    while (left < right) {
        swap = digits[left];
        digits[left] = digits[right];
        digits[right] = swap;
        left++;
        right--;
    }

    unsigned long long result = 0;
    for (int k = len - 1; k >= 0; k--) {
        result = result * 10 + digits[k];
        if (result > (unsigned long long)9223372036854775807LL) {
            errno = ERANGE;
            return -1;
        }
    }

    return (long long)result;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return 1;
    }

    char *endptr;
    errno = 0;
    long long input = strtoll(argv[1], &endptr, 10);

    if (errno == ERANGE || *endptr != '\0' || endptr == argv[1]) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    long long result = next_bigger_number(input);

    if (result == -1) {
        if (errno == ERANGE) {
            fprintf(stderr, "Result out of range\n");
            return 1;
        }
        printf("-1\n");
    } else {
        printf("%lld\n", result);
    }

    return 0;
}