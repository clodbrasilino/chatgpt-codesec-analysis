#if defined(__unix__) || defined(__linux__) || defined(__APPLE__)
#define _POSIX_C_SOURCE 200809L
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_STR_LEN 4096

bool areRotations(const char *str1, const char *str2) {
    if (str1 == NULL || str2 == NULL) {
        return false;
    }

    size_t len1 = strnlen(str1, MAX_STR_LEN);
    size_t len2 = strnlen(str2, MAX_STR_LEN);

    if (len1 != len2 || len1 == MAX_STR_LEN || len2 == MAX_STR_LEN) {
        return false;
    }

    if (len1 == 0) {
        return true;
    }

    size_t concat_len = len1 * 2 + 1;
    char *temp = (char *)malloc(concat_len);
    if (temp == NULL) {
        return false;
    }

    snprintf(temp, concat_len, "%s%s", str1, str1);

    bool is_rotation = (strstr(temp, str2) != NULL);

    free(temp);

    return is_rotation;
}

int main(void) {
    char *str1 = (char *)malloc(MAX_STR_LEN * sizeof(char));
    char *str2 = (char *)malloc(MAX_STR_LEN * sizeof(char));

    if (str1 == NULL || str2 == NULL) {
        free(str1);
        free(str2);
        return 1;
    }

    str1[0] = '\0';
    str2[0] = '\0';

    char *buffer = NULL;
    size_t bufsize = 0;

    if (getline(&buffer, &bufsize, stdin) != -1) {
        char *token1 = strtok(buffer, " \t\r\n");
        char *token2 = strtok(NULL, " \t\r\n");

        if (token1 != NULL && token2 != NULL) {
            snprintf(str1, MAX_STR_LEN, "%s", token1);
            snprintf(str2, MAX_STR_LEN, "%s", token2);

            if (areRotations(str1, str2)) {
                printf("True\n");
            } else {
                printf("False\n");
            }
        }
    }

    free(buffer);
    free(str1);
    free(str2);

    return 0;
}