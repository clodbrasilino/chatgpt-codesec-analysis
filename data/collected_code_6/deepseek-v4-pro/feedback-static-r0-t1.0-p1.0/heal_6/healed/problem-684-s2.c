#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>

long count_occurrences(const char *str, char ch, long n) {
    if (str == NULL || n <= 0) {
        return 0;
    }

    size_t len = strnlen(str, 255);
    if (len == 0) {
        return 0;
    }

    if (n > INT64_MAX / 256) {
        return -1;
    }

    long full_repeats = n / (long)len;
    size_t remainder = n % (long)len;
    long count = 0;

    for (size_t i = 0; i < len; i++) {
        if (str[i] == ch) {
            count++;
        }
    }

    if (count > 0 && full_repeats > LONG_MAX / count) {
        return -1;
    }

    long total = count * full_repeats;

    for (size_t i = 0; i < remainder; i++) {
        if (str[i] == ch) {
            if (total == LONG_MAX) {
                return -1;
            }
            total++;
        }
    }

    return total;
}

int main(void) {
    char input[320];
    char word[256];
    char ch;
    long n;

    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 1;
    }

    size_t len = strnlen(input, sizeof(input));
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
        len--;
    } else {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }

    if (len >= sizeof(input) - 1) {
        return 1;
    }

    int matches = sscanf(input, "%255s %c %ld", word, &ch, &n);
    if (matches != 3) {
        return 1;
    }

    if (n <= 0 || n > 1000000000L) {
        return 1;
    }

    size_t word_len = strnlen(word, sizeof(word));
    if (word_len >= sizeof(word)) {
        return 1;
    }

    long result = count_occurrences(word, ch, n);
    if (result < 0) {
        return 1;
    }

    printf("%ld\n", result);

    return 0;
}