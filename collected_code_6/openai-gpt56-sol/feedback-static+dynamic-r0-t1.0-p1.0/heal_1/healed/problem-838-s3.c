#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

static int minimum_swaps(const char *first, const char *second, size_t length)
{
    size_t mismatches_01 = 0;
    size_t mismatches_10 = 0;

    for (size_t i = 0; i < length; ++i) {
        if ((first[i] != '0' && first[i] != '1') ||
            (second[i] != '0' && second[i] != '1')) {
            return -1;
        }

        if (first[i] == '0' && second[i] == '1') {
            ++mismatches_01;
        } else if (first[i] == '1' && second[i] == '0') {
            ++mismatches_10;
        }
    }

    if (mismatches_01 != mismatches_10 || mismatches_01 > (size_t)INT_MAX) {
        return -1;
    }

    return (int)mismatches_01;
}

static int read_line(char *buffer, size_t capacity)
{
    size_t length;

    if (capacity == 0 || fgets(buffer, capacity, stdin) == NULL) {
        return 0;
    }

    length = strcspn(buffer, "\r\n");

    if (buffer[length] == '\0') {
        if (!feof(stdin)) {
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF) {
            }
            return 0;
        }
    } else {
        buffer[length] = '\0';
    }

    return 1;
}

int main(void)
{
    enum { CAPACITY = 1024 };
    char first[CAPACITY];
    char second[CAPACITY];
    size_t first_length;
    size_t second_length;

    if (!read_line(first, sizeof first) ||
        !read_line(second, sizeof second)) {
        return EXIT_FAILURE;
    }

    first_length = strnlen(first, sizeof first);
    second_length = strnlen(second, sizeof second);

    if (first_length == sizeof first || second_length == sizeof second) {
        return EXIT_FAILURE;
    }

    if (first_length != second_length) {
        puts("-1");
        return EXIT_SUCCESS;
    }

    printf("%d\n", minimum_swaps(first, second, first_length));
    return EXIT_SUCCESS;
}