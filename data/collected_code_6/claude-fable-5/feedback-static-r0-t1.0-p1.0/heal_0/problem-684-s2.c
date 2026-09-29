#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned long long count_char_in_repeated_string(const char *str, char target, unsigned long long total_length)
{
    size_t len;
    unsigned long long count_per_copy;
    unsigned long long full_copies;
    unsigned long long remainder;
    unsigned long long total;
    size_t i;

    if (str == NULL) {
        return 0ULL;
    }

    len = strlen(str);
    if (len == 0U || total_length == 0ULL) {
        return 0ULL;
    }

    count_per_copy = 0ULL;
    for (i = 0U; i < len; i++) {
        if (str[i] == target) {
            count_per_copy++;
        }
    }

    full_copies = total_length / (unsigned long long)len;
    remainder = total_length % (unsigned long long)len;

    total = full_copies * count_per_copy;
    for (i = 0U; i < (size_t)remainder; i++) {
        if (str[i] == target) {
            total++;
        }
    }

    return total;
}

int main(void)
{
    const char *base = "abcac";
    char target = 'a';
    unsigned long long total_length = 10ULL;
    unsigned long long result;

    result = count_char_in_repeated_string(base, target, total_length);

    if (printf("Occurrences of '%c' in the first %llu characters: %llu\n",
               target, total_length, result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}