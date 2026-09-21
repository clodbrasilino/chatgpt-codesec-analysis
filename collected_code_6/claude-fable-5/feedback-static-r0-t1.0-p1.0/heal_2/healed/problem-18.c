#include <stdio.h>
#include <string.h>
#include <limits.h>

#define BUF_SIZE 256

int remove_chars(char *str, const char *mask)
{
    int present[UCHAR_MAX + 1] = {0};
    size_t i;
    size_t j;

    if (str == NULL || mask == NULL) {
        return -1;
    }

    for (i = 0; mask[i] != '\0'; i++) {
        present[(unsigned char)mask[i]] = 1;
    }

    j = 0;
    for (i = 0; str[i] != '\0'; i++) {
        if (!present[(unsigned char)str[i]]) {
            str[j] = str[i];
            j++;
        }
    }
    str[j] = '\0';

    return 0;
}

int main(void)
{
    char first[BUF_SIZE];
    char second[BUF_SIZE];

    printf("Enter first string: ");
    if (fgets(first, sizeof(first), stdin) == NULL) {
        fprintf(stderr, "Error reading first string\n");
        return 1;
    }
    first[strcspn(first, "\n")] = '\0';

    printf("Enter second string: ");
    if (fgets(second, sizeof(second), stdin) == NULL) {
        fprintf(stderr, "Error reading second string\n");
        return 1;
    }
    second[strcspn(second, "\n")] = '\0';

    if (remove_chars(first, second) != 0) {
        fprintf(stderr, "Error processing strings\n");
        return 1;
    }

    printf("Result: %s\n", first);

    return 0;
}