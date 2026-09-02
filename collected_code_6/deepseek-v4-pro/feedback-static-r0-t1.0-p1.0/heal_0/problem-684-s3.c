#include <stdio.h>
#include <string.h>
#include <stddef.h>

long count_char_in_repeated_string(const char *str, char ch, long n) {
    size_t len = strlen(str);
    if (len == 0 || n <= 0) {
        return 0;
    }

    long full_repeats = n / (long)len;
    long remainder = n % (long)len;

    long count_in_one = 0;
    for (size_t i = 0; i < len; i++) {
        if (str[i] == ch) {
            count_in_one++;
        }
    }

    long total = full_repeats * count_in_one;

    for (long i = 0; i < remainder; i++) {
        if (str[i] == ch) {
            total++;
        }
    }

    return total;
}

int main(void) {
    const char *s = "aba";
    char target = 'a';
    long n = 10;

    long result = count_char_in_repeated_string(s, target, n);
    printf("%ld\n", result);

    return 0;
}