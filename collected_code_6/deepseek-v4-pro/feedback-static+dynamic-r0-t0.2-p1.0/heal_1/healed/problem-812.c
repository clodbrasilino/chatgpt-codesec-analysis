#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

char *abbreviate_road(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    size_t len = strlen(input);
    char *result = malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t i = 0, j = 0;
    while (i < len) {
        if (i + 3 < len && 
            tolower(input[i]) == 'r' && 
            tolower(input[i+1]) == 'o' && 
            tolower(input[i+2]) == 'a' && 
            tolower(input[i+3]) == 'd') {
            result[j++] = 'r';
            result[j++] = 'd';
            result[j++] = '.';
            i += 4;
        } else {
            result[j++] = input[i++];
        }
    }
    result[j] = '\0';
    return result;
}

int main(void) {
    const char *test1 = "123 Main Road";
    const char *test2 = "Road to nowhere";
    const char *test3 = "Broadway";
    const char *test4 = "road";
    const char *test5 = "ROAD";
    const char *test6 = "Rd.";
    const char *test7 = NULL;

    char *result1 = abbreviate_road(test1);
    char *result2 = abbreviate_road(test2);
    char *result3 = abbreviate_road(test3);
    char *result4 = abbreviate_road(test4);
    char *result5 = abbreviate_road(test5);
    char *result6 = abbreviate_road(test6);
    char *result7 = abbreviate_road(test7);

    if (test1 != NULL) {
        printf("%s -> %s\n", test1, result1 ? result1 : "(null)");
    } else {
        printf("(null) -> %s\n", result1 ? result1 : "(null)");
    }
    if (test2 != NULL) {
        printf("%s -> %s\n", test2, result2 ? result2 : "(null)");
    } else {
        printf("(null) -> %s\n", result2 ? result2 : "(null)");
    }
    if (test3 != NULL) {
        printf("%s -> %s\n", test3, result3 ? result3 : "(null)");
    } else {
        printf("(null) -> %s\n", result3 ? result3 : "(null)");
    }
    if (test4 != NULL) {
        printf("%s -> %s\n", test4, result4 ? result4 : "(null)");
    } else {
        printf("(null) -> %s\n", result4 ? result4 : "(null)");
    }
    if (test5 != NULL) {
        printf("%s -> %s\n", test5, result5 ? result5 : "(null)");
    } else {
        printf("(null) -> %s\n", result5 ? result5 : "(null)");
    }
    if (test6 != NULL) {
        printf("%s -> %s\n", test6, result6 ? result6 : "(null)");
    } else {
        printf("(null) -> %s\n", result6 ? result6 : "(null)");
    }
    if (test7 != NULL) {
        printf("%s -> %s\n", test7, result7 ? result7 : "(null)");
    } else {
        printf("(null) -> %s\n", result7 ? result7 : "(null)");
    }

    free(result1);
    free(result2);
    free(result3);
    free(result4);
    free(result5);
    free(result6);
    free(result7);

    return 0;
}