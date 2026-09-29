#include <stdio.h>
#include <stdlib.h>

static int reverse_string(char *string, size_t capacity)
{
    size_t length = 0;
    size_t left;
    size_t right;

    if (string == NULL || capacity == 0) {
        return -1;
    }

    while (length < capacity && string[length] != '\0') {
        ++length;
    }

    if (length == capacity) {
        return -1;
    }

    if (length < 2) {
        return 0;
    }

    left = 0;
    right = length - 1;

    while (left < right) {
        char temp = string[left];
        string[left] = string[right];
        string[right] = temp;
        ++left;
        --right;
    }

    return 0;
}

static int reverse_strings(char *strings[], const size_t capacities[],
                           size_t count)
{
    size_t i;

    if (count != 0 && (strings == NULL || capacities == NULL)) {
        return -1;
    }

    for (i = 0; i < count; ++i) {
        if (reverse_string(strings[i], capacities[i]) != 0) {
            return -1;
        }
    }

    return 0;
}

int main(void)
{
    char first[] = "hello";
    char second[] = "world";
    char third[] = "C programming";
    char *strings[] = {first, second, third};
    const size_t capacities[] = {
        sizeof(first),
        sizeof(second),
        sizeof(third)
    };
    const size_t count = sizeof(strings) / sizeof(strings[0]);
    size_t i;

    if (reverse_strings(strings, capacities, count) != 0) {
        fputs("Failed to reverse strings.\n", stderr);
        return EXIT_FAILURE;
    }

    for (i = 0; i < count; ++i) {
        if (puts(strings[i]) == EOF) {
            fputs("Failed to write output.\n", stderr);
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}