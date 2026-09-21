#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>

#define CHAR_SET_SIZE 256
#define MAX_INPUT_SIZE 256

bool are_permutations(const char *str1, const char *str2, size_t max_len)
{
    int count[CHAR_SET_SIZE] = {0};
    size_t len1, len2, i;

    if (str1 == NULL || str2 == NULL) {
        return false;
    }

    len1 = strnlen(str1, max_len);
    len2 = strnlen(str2, max_len);

    if (len1 != len2) {
        return false;
    }

    for (i = 0; i < len1; i++) {
        count[(unsigned char)str1[i]]++;
        count[(unsigned char)str2[i]]--;
    }

    for (i = 0; i < CHAR_SET_SIZE; i++) {
        if (count[i] != 0) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    char str1[MAX_INPUT_SIZE + 1];
    char str2[MAX_INPUT_SIZE + 1];
    int result;
    size_t len;

    if (fgets(str1, sizeof(str1), stdin) == NULL) {
        return EXIT_FAILURE;
    }
    if (fgets(str2, sizeof(str2), stdin) == NULL) {
        return EXIT_FAILURE;
    }

    len = strcspn(str1, "\n");
    if (len < sizeof(str1)) {
        str1[len] = '\0';
    }

    len = strcspn(str2, "\n");
    if (len < sizeof(str2)) {
        str2[len] = '\0';
    }

    result = are_permutations(str1, str2, sizeof(str1));

    if (result) {
        printf("The strings are permutations of each other.\n");
    } else {
        printf("The strings are not permutations of each other.\n");
    }

    return EXIT_SUCCESS;
}