#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *abbreviate_road(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = strlen(str);

    if (len < 4) {
        char *result = malloc(len + 1);
        if (result == NULL) {
            return NULL;
        }
        memcpy(result, str, len + 1);
        return result;
    }

    char *lower = malloc(len + 1);
    if (lower == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < len; i++) {
        lower[i] = tolower((unsigned char)str[i]);
    }
    lower[len] = '\0';

    size_t count = 0;
    for (size_t i = 0; i <= len - 4; i++) {
        if ((i == 0 || lower[i - 1] == ' ') &&
            lower[i] == 'r' && lower[i + 1] == 'o' &&
            lower[i + 2] == 'a' && lower[i + 3] == 'd' &&
            (lower[i + 4] == ' ' || lower[i + 4] == '\0')) {
            count++;
        }
    }

    size_t result_len = len - (count * 2) + 1;
    char *result = malloc(result_len);
    if (result == NULL) {
        free(lower);
        return NULL;
    }

    size_t i = 0;
    size_t j = 0;

    while (i < len) {
        if (i <= len - 4 &&
            (i == 0 || lower[i - 1] == ' ') &&
            lower[i] == 'r' && lower[i + 1] == 'o' &&
            lower[i + 2] == 'a' && lower[i + 3] == 'd' &&
            (lower[i + 4] == ' ' || lower[i + 4] == '\0')) {
            
            result[j++] = (str[i] == 'R') ? 'R' : 'r';
            result[j++] = (str[i + 2] == 'A') ? 'A' : 'a';
            result[j++] = '.';
            i += 4;
        } else {
            result[j++] = str[i++];
        }
    }

    result[j] = '\0';
    free(lower);
    return result;
}

int main(void) {
    char *res1 = abbreviate_road("Maple Road");
    if (res1 != NULL) {
        printf("%s\n", res1);
        free(res1);
    }

    char *res2 = abbreviate_road("Roadside and Road");
    if (res2 != NULL) {
        printf("%s\n", res2);
        free(res2);
    }

    const char *res3 = abbreviate_road(NULL);
    if (res3 == NULL) {
        printf("NULL input handled\n");
    }

    return 0;
}