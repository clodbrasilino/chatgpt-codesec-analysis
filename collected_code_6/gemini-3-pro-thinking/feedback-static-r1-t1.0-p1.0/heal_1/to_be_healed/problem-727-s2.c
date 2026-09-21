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
    size_t remaining;

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

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    remaining = strlen(cursor);
    if (remaining > 0) {
        memmove(write_ptr, cursor, remaining);
        write_ptr += remaining;
    }
    *write_ptr = '\0';

    regfree(&regex);
    return 0;
}

int main(void) {
    char *test_str;
    const char *initial_str = "Hello, World! 123... Regex is fun:)";
    int res;
    size_t alloc_size;

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    alloc_size = strlen(initial_str) + 1;
    test_str = (char *)malloc(alloc_size);
    
    if (test_str == NULL) {
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
    strncpy(test_str, initial_str, alloc_size);

    res = remove_non_alnum_regex(test_str);
    if (res == 0) {
        printf("%s\n", test_str);
    }

    free(test_str);

    return (res == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}