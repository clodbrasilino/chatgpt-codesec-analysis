#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *abbreviate_road(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = strlen(str);

    char *result = malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t i = 0;
    size_t j = 0;

    while (i < len) {
        if (i + 4 <= len && (i == 0 || str[i - 1] == ' ') &&
            tolower((unsigned char)str[i]) == 'r' &&
            tolower((unsigned char)str[i + 1]) == 'o' &&
            tolower((unsigned char)str[i + 2]) == 'a' &&
            tolower((unsigned char)str[i + 3]) == 'd' &&
            (str[i + 4] == ' ' || str[i + 4] == '\0')) {
            
            result[j++] = isupper((unsigned char)str[i]) ? 'R' : 'r';
            result[j++] = isupper((unsigned char)str[i + 2]) ? 'A' : 'a';
            result[j++] = '.';
            i += 4;
        } else {
            result[j++] = str[i++];
        }
    }

    result[j] = '\0';
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

    const char *input3 = NULL;
    char *res3 = abbreviate_road(input3);
    if (res3 == NULL) {
        printf("NULL input handled\n");
    } else {
        free(res3);
    }

    return 0;
}