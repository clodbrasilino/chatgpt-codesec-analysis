#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <limits.h>

static void swap(char *a, char *b) {
    char temp = *a;
    *a = *b;
    *b = temp;
}

static void permute(char *str, int left, int right) {
    if (left == right) {
        printf("%s\n", str);
        return;
    }

    for (int i = left; i <= right; i++) {
        swap(&str[left], &str[i]);
        permute(str, left + 1, right);
        swap(&str[left], &str[i]);
    }
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[256] = {0};

    if (fgets(input, (int)sizeof(input), stdin) == NULL) {
        return 1;
    }

    size_t len = strnlen(input, sizeof(input));
    if (len >= sizeof(input)) {
        return 1;
    }

    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
        len--;
    }

    if (len == 0) {
        return 0;
    }

    if (len > (size_t)INT_MAX) {
        return 1;
    }

    for (size_t i = 0; i < len; i++) {
        if ((unsigned char)input[i] > 127) {
            return 1;
        }
    }

    permute(input, 0, (int)(len - 1));

    return 0;
}