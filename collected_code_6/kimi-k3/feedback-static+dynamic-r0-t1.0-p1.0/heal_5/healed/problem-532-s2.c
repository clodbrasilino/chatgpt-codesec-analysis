#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define CHAR_SET_SIZE 256
#define BUFFER_SIZE 256

bool are_permutations(const char *str1, const char *str2)
{
    int count[CHAR_SET_SIZE] = {0};
    size_t len1, len2, i;

    if (str1 == NULL || str2 == NULL) {
        return false;
    }

    len1 = strnlen(str1, BUFFER_SIZE);
    len2 = strnlen(str2, BUFFER_SIZE);

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
    char *str1 = NULL;
    char *str2 = NULL;
    size_t size1 = 0;
    size_t size2 = 0;
    ssize_t len1, len2;
    int result;

    len1 = getline(&str1, &size1, stdin);
    if (len1 == -1) {
        free(str1);
        return EXIT_FAILURE;
    }

    len2 = getline(&str2, &size2, stdin);
    if (len2 == -1) {
        free(str1);
        free(str2);
        return EXIT_FAILURE;
    }

    if (len1 > 0 && str1[len1 - 1] == '\n') {
        str1[len1 - 1] = '\0';
        len1--;
    }
    if (len2 > 0 && str2[len2 - 1] == '\n') {
        str2[len2 - 1] = '\0';
        len2--;
    }

    result = are_permutations(str1, str2);

    if (result) {
        printf("The strings are permutations of each other.\n");
    } else {
        printf("The strings are not permutations of each other.\n");
    }

    free(str1);
    free(str2);

    return EXIT_SUCCESS;
}