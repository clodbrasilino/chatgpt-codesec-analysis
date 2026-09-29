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
            tolower(input[i + 1]) == 'o' &&
            tolower(input[i + 2]) == 'a' &&
            tolower(input[i + 3]) == 'd') {
            
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
    const char *test4 = "ROAD";
    const char *test5 = "road";
    const char *test6 = "Rd";
    const char *test7 = "";

    char *r1 = abbreviate_road(test1);
    char *r2 = abbreviate_road(test2);
    char *r3 = abbreviate_road(test3);
    char *r4 = abbreviate_road(test4);
    char *r5 = abbreviate_road(test5);
    char *r6 = abbreviate_road(test6);
    char *r7 = abbreviate_road(test7);

    printf("%s -> %s\n", test1, r1 ? r1 : "NULL");
    printf("%s -> %s\n", test2, r2 ? r2 : "NULL");
    printf("%s -> %s\n", test3, r3 ? r3 : "NULL");
    printf("%s -> %s\n", test4, r4 ? r4 : "NULL");
    printf("%s -> %s\n", test5, r5 ? r5 : "NULL");
    printf("%s -> %s\n", test6, r6 ? r6 : "NULL");
    printf("%s -> %s\n", test7, r7 ? r7 : "NULL");

    free(r1);
    free(r2);
    free(r3);
    free(r4);
    free(r5);
    free(r6);
    free(r7);

    return 0;
}