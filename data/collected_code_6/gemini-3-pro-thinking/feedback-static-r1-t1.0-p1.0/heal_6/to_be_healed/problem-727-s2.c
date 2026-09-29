#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int remove_non_alnum_regex(char *str) {
    regex_t regex;
    int comp_res;
    regmatch_t match;
    char *cursor;
    char *write_ptr;

    if (str == NULL) {
        return -1;
    }

    comp_res = regcomp(&regex, "[^a-zA-Z0-9]+", REG_EXTENDED);
    if (comp_res != 0) {
        return -1;
    }

    cursor = str;
    write_ptr = str;

    while (regexec(&regex, cursor, 1, &match, 0) == 0) {
        size_t len = match.rm_so;
        
        if (len > 0) {
            memmove(write_ptr, cursor, len);
            write_ptr += len;
        }

        if (match.rm_so == match.rm_eo) {
            if (*cursor == '\0') {
                break;
            }
            *write_ptr = *cursor;
            write_ptr++;
            cursor++;
        } else {
            cursor += match.rm_eo;
        }
    }

    while (*cursor != '\0') {
        *write_ptr = *cursor;
        write_ptr++;
        cursor++;
    }
    *write_ptr = '\0';

    regfree(&regex);
    return 0;
}

int main(void) {
    char *test_str;
    const char initial_str[] = "Hello, World! 123... Regex is fun:)";
    int res;
    size_t alloc_size;

    alloc_size = sizeof(initial_str);
    test_str = (char *)malloc(alloc_size);
    
    if (test_str == NULL) {
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(test_str, initial_str, alloc_size);

    res = remove_non_alnum_regex(test_str);
    if (res == 0) {
        printf("%s\n", test_str);
    }

    free(test_str);

    return (res == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}