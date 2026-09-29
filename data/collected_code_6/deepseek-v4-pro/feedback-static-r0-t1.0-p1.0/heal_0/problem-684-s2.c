#include <stdio.h>
#include <string.h>
#include <stdlib.h>

long count_occurrences(const char *str, char ch, long n) {
    if (str == NULL || n < 0 || str[0] == '\0') {
        return 0;
    }

    size_t len = strlen(str);
    long full_repeats = n / (long)len;
    size_t remainder = n % (long)len;
    long count = 0;

    for (size_t i = 0; i < len; i++) {
        if (str[i] == ch) {
            count++;
        }
    }

    long total = count * full_repeats;

    for (size_t i = 0; i < remainder; i++) {
        if (str[i] == ch) {
            total++;
        }
    }

    return total;
}

int main(void) {
    char input[256];
    char ch;
    long n;

    if (scanf("%255s %c %ld", input, &ch, &n) != 3) {
        return 1;
    }

    long result = count_occurrences(input, ch, n);
    printf("%ld\n", result);

    return 0;
}