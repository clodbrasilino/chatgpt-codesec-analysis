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

    size_t i = 0, j = 0;
    while (i < len) {
        if (tolower((unsigned char)str[i]) == 'r') {
            size_t remaining = len - i;
            if (remaining >= 4) {
                if (tolower((unsigned char)str[i + 1]) == 'o' &&
                    tolower((unsigned char)str[i + 2]) == 'a' &&
                    tolower((unsigned char)str[i + 3]) == 'd') {
                    result[j++] = str[i];
                    result[j++] = toupper((unsigned char)str[i + 1]) == 'O' ? 'D' : 'd';
                    result[j++] = '.';
                    i += 4;
                    continue;
                }
            }
        }
        result[j++] = str[i++];
    }
    result[j] = '\0';

    char *shrunk = realloc(result, j + 1);
    if (shrunk != NULL) {
        result = shrunk;
    }

    return result;
}

int main(void) {
    char *s1 = abbreviate_road("I walked down the Road");
    if (s1 != NULL) {
        printf("%s\n", s1);
        free(s1);
    }

    char *s2 = abbreviate_road("road ahead");
    if (s2 != NULL) {
        printf("%s\n", s2);
        free(s2);
    }

    /* Possible weaknesses found:
     *  Assignment 's3=abbreviate_road(NULL)', assigned value is 0
     *  Calling function 'abbreviate_road' returns 0
     */
    char *s3 = abbreviate_road(NULL);
    /* Possible weaknesses found:
     *  Condition 's3==NULL' is always true
     *  Condition 's3==NULL' is always true [knownConditionTrueFalse]
     */
    if (s3 == NULL) {
        printf("NULL input handled\n");
        return 0;
    }
    
    printf("%s\n", s3);
    free(s3);

    return 0;
}