#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *abbreviate_road(const char *str) {
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
            (str[i] == 'r' || str[i] == 'R') &&
            (str[i + 1] == 'o' || str[i + 1] == 'O') &&
            (str[i + 2] == 'a' || str[i + 2] == 'A') &&
            (str[i + 3] == 'd' || str[i + 3] == 'D') &&
            (str[i + 4] == ' ' || str[i + 4] == '\0')) {
            
            result[j++] = (str[i] == 'R') ? 'R' : 'r';
            result[j++] = (str[i + 2] == 'A') ? 'A' : 'a';
            result[j++] = '.';
            i += 5;
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
     *  Calling function 'abbreviate_road' returns 0
     *  Assignment 'res4=abbreviate_road(NULL)', assigned value is 0
     *  Variable 'res4' can be declared as pointer to const [constVariablePointer]
     */
    char *res4 = abbreviate_road(NULL);
    /* Possible weaknesses found:
     *  Condition 'res4==NULL' is always true [knownConditionTrueFalse]
     *  Condition 'res4==NULL' is always true
     */
    if (res4 == NULL) {
        printf("Handled NULL input safely\n");
    }

    return 0;
}