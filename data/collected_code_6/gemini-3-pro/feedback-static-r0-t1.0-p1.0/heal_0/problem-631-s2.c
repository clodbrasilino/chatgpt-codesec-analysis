#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char* swap_space_underscore_regex(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    char *result = strdup(input);
    if (result == NULL) {
        return NULL;
    }

    regex_t regex;
    if (regcomp(&regex, "[ _]", REG_EXTENDED) != 0) {
        free(result);
        return NULL;
    }

    regmatch_t pmatch[1];
    char *cursor = result;

    while (regexec(&regex, cursor, 1, pmatch, 0) == 0) {
        if (pmatch[0].rm_so >= 0) {
            if (cursor[pmatch[0].rm_so] == ' ') {
                cursor[pmatch[0].rm_so] = '_';
            } else if (cursor[pmatch[0].rm_so] == '_') {
                cursor[pmatch[0].rm_so] = ' ';
            }
            cursor += pmatch[0].rm_eo;
        } else {
            break;
        }
    }

    regfree(&regex);
    return result;
}

int main(void) {
    const char *original = "Hello_World this is_a_test";
    
    char *modified = swap_space_underscore_regex(original);
    if (modified == NULL) {
        fprintf(stderr, "Error processing string.\n");
        return EXIT_FAILURE;
    }

    printf("%s\n", original);
    printf("%s\n", modified);

    free(modified);

    return EXIT_SUCCESS;
}