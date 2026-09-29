#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 1024

int min_swaps(const char *s1, const char *s2, long *result)
{
    size_t len1;
    size_t len2;
    size_t i;
    long count10 = 0;
    long count01 = 0;

    if (s1 == NULL || s2 == NULL || result == NULL) {
        return -1;
    }

    len1 = strnlen(s1, MAX_LEN);
    len2 = strnlen(s2, MAX_LEN);

    if (len1 >= MAX_LEN || len2 >= MAX_LEN) {
        return -1;
    }

    if (len1 != len2) {
        return -1;
    }

    for (i = 0; i < len1; i++) {
        if ((s1[i] != '0' && s1[i] != '1') ||
            (s2[i] != '0' && s2[i] != '1')) {
            return -1;
        }
        if (s1[i] == '1' && s2[i] == '0') {
            count10++;
        } else if (s1[i] == '0' && s2[i] == '1') {
            count01++;
        }
    }

    if (count10 != count01) {
        return -1;
    }

    *result = count10;
    return 0;
}

static int read_line(char *buffer, size_t size)
{
    size_t len;

    if (buffer == NULL || size == 0) {
        return -1;
    }

    if (fgets(buffer, (int)size, stdin) == NULL) {
        return -1;
    }

    buffer[size - 1] = '\0';

    len = strnlen(buffer, size);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }

    return 0;
}

int main(void)
{
    char str1[MAX_LEN] = {0};
    char str2[MAX_LEN] = {0};
    long swaps = 0;

    printf("Enter first binary string: ");
    if (read_line(str1, sizeof(str1)) != 0) {
        fprintf(stderr, "Error reading first string\n");
        return EXIT_FAILURE;
    }

    printf("Enter second binary string: ");
    if (read_line(str2, sizeof(str2)) != 0) {
        fprintf(stderr, "Error reading second string\n");
        return EXIT_FAILURE;
    }

    if (min_swaps(str1, str2, &swaps) != 0) {
        fprintf(stderr, "Conversion not possible or invalid input\n");
        return EXIT_FAILURE;
    }

    printf("Minimum number of swaps: %ld\n", swaps);

    return EXIT_SUCCESS;
}