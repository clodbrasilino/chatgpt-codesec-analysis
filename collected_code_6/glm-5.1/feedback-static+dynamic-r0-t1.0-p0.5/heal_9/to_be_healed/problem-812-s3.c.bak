#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *abbreviate_road(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = strlen(str);
    if (len == 0) {
        char *result = malloc(1);
        if (result == NULL) {
            return NULL;
        }
        result[0] = '\0';
        return result;
    }

    char *result = malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t i = 0;
    size_t j = 0;

    while (i < len) {
        if (i + 4 <= len && (i == 0 || str[i - 1] == ' ') &&
            (tolower((unsigned char)str[i]) == 'r') &&
            (tolower((unsigned char)str[i + 1]) == 'o') &&
            (tolower((unsigned char)str[i + 2]) == 'a') &&
            (tolower((unsigned char)str[i + 3]) == 'd') &&
            (str[i + 4] == ' ' || str[i + 4] == '\0')) {
            
            result[j++] = (isupper((unsigned char)str[i])) ? 'R' : 'r';
            result[j++] = (isupper((unsigned char)str[i + 2])) ? 'A' : 'a';
            result[j++] = '.';
            i += 4;
        } else {
            result[j++] = str[i++];
        }
    }

    result[j] = '\0';

    char *shrunk = realloc(result, j + 1);
    if (shrunk != NULL) {
        result = shrunk;
    }

    return result;
}

int main(void) {
    char *res1 = abbreviate_road("Maple Road");
    if (res1 != NULL) {
        printf("%s\n", res1);
        free(res1);
    }

    char *res2 = abbreviate_road("Road to ruin");
    if (res2 != NULL) {
        printf("%s\n", res2);
        free(res2);
    }

    char *res3 = abbreviate_road("Broad Street");
    if (res3 != NULL) {
        printf("%s\n", res3);
        free(res3);
    }

    /* Possible weaknesses found:
     *  Assignment 'res4=abbreviate_road(NULL)', assigned value is 0
     *  Calling function 'abbreviate_road' returns 0
     */
    char *res4 = abbreviate_road(NULL);
    /* Possible weaknesses found:
     *  Condition 'res4!=NULL' is always false [knownConditionTrueFalse]
     *  Condition 'res4!=NULL' is always false
     */
    if (res4 != NULL) {
        printf("%s\n", res4);
        free(res4);
    } else {
        printf("NULL input handled\n");
    }

    return 0;
}