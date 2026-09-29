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
        if (i + 3 < len && tolower((unsigned char)str[i]) == 'r' &&
            tolower((unsigned char)str[i + 1]) == 'o' &&
            tolower((unsigned char)str[i + 2]) == 'a' &&
            tolower((unsigned char)str[i + 3]) == 'd') {

            int is_prefix_word_end = (i == 0 || isspace((unsigned char)str[i - 1]) || ispunct((unsigned char)str[i - 1]));
            int is_suffix_word_end = (i + 4 == len || isspace((unsigned char)str[i + 4]) || ispunct((unsigned char)str[i + 4]));

            if (is_prefix_word_end && is_suffix_word_end) {
                result[j++] = str[i];
                result[j++] = str[i + 1];
                result[j++] = '.';
                i += 4;
                continue;
            }
        }
        result[j++] = str[i++];
    }

    result[j] = '\0';
    return result;
}

int main(void) {
    const char *input = "I walked down the long Road to find my way home.";
    char *output = abbreviate_road(input);

    if (output != NULL) {
        printf("%s\n", output);
        free(output);
    }

    return 0;
}