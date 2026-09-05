#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

void swap(char *a, char *b) {
    char temp = *a;
    *a = *b;
    *b = temp;
}

void reverse(char *str, int start, int end) {
    while (start < end) {
        swap(&str[start], &str[end]);
        start++;
        end--;
    }
}

int next_bigger_number(int n) {
    if (n < 0) {
        return -1;
    }

    char *digits = (char *)malloc(32 * sizeof(char));
    if (digits == NULL) {
        return -1;
    }

    int len = snprintf(digits, 32, "%d", n);
    if (len <= 1) {
        free(digits);
        return -1;
    }

    int i = len - 2;
    while (i >= 0 && digits[i] >= digits[i + 1]) {
        i--;
    }

    if (i < 0) {
        free(digits);
        return -1;
    }

    int j = len - 1;
    while (digits[j] <= digits[i]) {
        j--;
    }

    swap(&digits[i], &digits[j]);
    reverse(digits, i + 1, len - 1);

    long long result = 0;
    for (int k = 0; k < len; k++) {
        result = result * 10 + (digits[k] - '0');
    }

    free(digits);

    if (result > INT_MAX) {
        return 0;
    }

    return (int)result;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <integer>\n", argv[0]);
        return 1;
    }

    char *endptr;
    long val = strtol(argv[1], &endptr, 10);
    if (*endptr != '\0' || val < INT_MIN || val > INT_MAX) {
        fprintf(stderr, "Invalid integer argument\n");
        return 1;
    }

    int input = (int)val;
    int result = next_bigger_number(input);

    if (result == -1) {
        printf("-1\n");
    } else if (result == 0 && input != 0) {
        printf("Overflow\n");
    } else {
        printf("%d\n", result);
    }

    return 0;
}