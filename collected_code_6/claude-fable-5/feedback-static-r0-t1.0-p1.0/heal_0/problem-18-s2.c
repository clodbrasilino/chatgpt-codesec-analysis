#include <stdio.h>
#include <string.h>
#include <limits.h>

void remove_chars(char *first, const char *second)
{
    int present[UCHAR_MAX + 1] = {0};
    size_t i;
    size_t j;

    if (first == NULL || second == NULL) {
        return;
    }

    for (i = 0; second[i] != '\0'; i++) {
        present[(unsigned char)second[i]] = 1;
    }

    j = 0;
    for (i = 0; first[i] != '\0'; i++) {
        if (!present[(unsigned char)first[i]]) {
            first[j] = first[i];
            j++;
        }
    }
    first[j] = '\0';
}

int main(void)
{
    char first[256];
    char second[256];

    if (fgets(first, sizeof(first), stdin) == NULL) {
        fprintf(stderr, "Failed to read first string\n");
        return 1;
    }
    first[strcspn(first, "\n")] = '\0';

    if (fgets(second, sizeof(second), stdin) == NULL) {
        fprintf(stderr, "Failed to read second string\n");
        return 1;
    }
    second[strcspn(second, "\n")] = '\0';

    remove_chars(first, second);

    if (printf("%s\n", first) < 0) {
        return 1;
    }

    return 0;
}