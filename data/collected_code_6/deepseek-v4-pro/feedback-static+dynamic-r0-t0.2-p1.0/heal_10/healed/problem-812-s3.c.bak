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
            tolower((unsigned char)input[i]) == 'r' && 
            tolower((unsigned char)input[i + 1]) == 'o' && 
            tolower((unsigned char)input[i + 2]) == 'a' && 
            tolower((unsigned char)input[i + 3]) == 'd') {
            
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
    const char *test4 = "road road ROAD";
    const char *test5 = NULL;

    char *result1 = abbreviate_road(test1);
    char *result2 = abbreviate_road(test2);
    char *result3 = abbreviate_road(test3);
    char *result4 = abbreviate_road(test4);
    char *result5 = abbreviate_road(test5);

    printf("Test 1: %s -> %s\n", test1, result1 ? result1 : "NULL");
    printf("Test 2: %s -> %s\n", test2, result2 ? result2 : "NULL");
    printf("Test 3: %s -> %s\n", test3, result3 ? result3 : "NULL");
    printf("Test 4: %s -> %s\n", test4, result4 ? result4 : "NULL");
    printf("Test 5: NULL -> %s\n", result5 ? result5 : "NULL");

    free(result1);
    free(result2);
    free(result3);
    free(result4);
    free(result5);

    return 0;
}