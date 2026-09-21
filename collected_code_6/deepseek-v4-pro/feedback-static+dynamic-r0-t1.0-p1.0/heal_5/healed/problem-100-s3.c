#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

static int all_nines(const char *num, int len) {
    int i;
    for (i = 0; i < len; i++) {
        if (num[i] != '9') return 0;
    }
    return 1;
}

static void generate_next_palindrome(const char *num, int len) {
    int i, j;
    int left_smaller;
    char *result;
    size_t result_size;

    if (all_nines(num, len)) {
        result_size = (size_t)len + 2;
        result = (char *)malloc(result_size);
        if (!result) exit(1);
        result[0] = '1';
        for (i = 1; i < len; i++) result[i] = '0';
        result[len] = '1';
        result[len + 1] = '\0';
        printf("%s\n", result);
        free(result);
        return;
    }

    result_size = (size_t)len + 1;
    result = (char *)malloc(result_size);
    if (!result) exit(1);
    if (len > 0) {
        memcpy(result, num, (size_t)len);
    }
    result[len] = '\0';

    i = len / 2;
    j = i;

    if (len % 2 == 0) i--;

    while (i >= 0 && result[i] == result[j]) {
        i--;
        j++;
    }

    left_smaller = 0;
    if (i < 0 || result[i] < result[j]) left_smaller = 1;

    while (i >= 0) {
        result[j] = result[i];
        i--;
        j++;
    }

    if (left_smaller) {
        int carry = 1;
        i = len / 2;

        if (len % 2 == 0) i--;

        while (i >= 0 && carry) {
            if (result[i] == '9') {
                result[i] = '0';
                carry = 1;
            } else {
                result[i]++;
                carry = 0;
            }
            i--;
        }
    }

    for (i = 0, j = len - 1; i < j; i++, j--) {
        result[j] = result[i];
    }

    printf("%s\n", result);
    free(result);
}

int main(void) {
    char input[1024];
    int len;
    size_t input_len;

    if (fgets(input, sizeof(input), stdin) == NULL) return 1;

    input[sizeof(input) - 1] = '\0';
    input_len = strlen(input);
    len = (int)input_len;

    while (len > 0 && (input[len - 1] == '\n' || input[len - 1] == '\r')) {
        input[--len] = '\0';
    }

    if (len == 0) return 1;

    generate_next_palindrome(input, len);

    return 0;
}