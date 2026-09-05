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
        if (i + 3 < len && tolower((unsigned char)str[i]) == 'r' &&
            tolower((unsigned char)str[i + 1]) == 'o' &&
            tolower((unsigned char)str[i + 2]) == 'a' &&
            tolower((unsigned char)str[i + 3]) == 'd') {
            
            int is_prefix_word = (i > 0 && isalpha((unsigned char)str[i - 1]));
            int is_suffix_word = (i + 4 < len && isalpha((unsigned char)str[i + 4]));

            if (!is_prefix_word && !is_suffix_word) {
                result[j++] = 'r';
                result[j++] = 'd';
                result[j++] = '.';
                i += 4;
                continue;
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
    const char *input = "I walked down the long Road to find the crossroad.";
    char *output = abbreviate_road(input);
    
    if (output != NULL) {
        printf("Input:  %s\n", input);
        printf("Output: %s\n", output);
        free(output);
    } else {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    return 0;
}