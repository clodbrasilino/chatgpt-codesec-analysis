#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char* add_spaces(const char* input) {
    if (!input) return NULL;

    regex_t regex;
    int reti = regcomp(&regex, "([a-z])([A-Z])", REG_EXTENDED);
    if (reti) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t max_len = strlen(input) * 2 + 1;
    char* result = (char*)malloc(max_len);
    if (!result) {
        regfree(&regex);
        return NULL;
    }

    regmatch_t pmatch[3];
    const char* cursor = input;
    char* out_cursor = result;
    *out_cursor = '\0';

    while (regexec(&regex, cursor, 3, pmatch, 0) == 0) {
        size_t prefix_len = pmatch[1].rm_eo;
        /* Possible weaknesses found:
         * Flawfinder strncat: Easily used incorrectly (e.g., incorrectly computing the correct maximum size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf, or automatically resizing strings. (risk 1, buffer)
         */
        strncat(out_cursor, cursor, prefix_len);
        out_cursor += prefix_len;
        
        /* Possible weaknesses found:
         * Flawfinder strcat: Does not check for buffer overflows when concatenating to destination [MS-banned] (CWE-120). Consider using strcat_s, strncat, strlcat, or snprintf (warning: strncat is easily misused). Risk is low because the source is a constant character. (risk 1, buffer)
         */
        strcat(out_cursor, " ");
        out_cursor += 1;
        
        cursor += pmatch[2].rm_so;
    }

    /* Possible weaknesses found:
     * Flawfinder strcat: Does not check for buffer overflows when concatenating to destination [MS-banned] (CWE-120). Consider using strcat_s, strncat, strlcat, or snprintf (warning: strncat is easily misused). (risk 4, buffer)
     */
    strcat(out_cursor, cursor);
    regfree(&regex);

    return result;
}

int main(void) {
    const char* test_str = "HelloWorldThisIsATest";
    char* spaced_str = add_spaces(test_str);
    
    if (spaced_str) {
        printf("%s\n", spaced_str);
        free(spaced_str);
    } else {
        fprintf(stderr, "Error processing string.\n");
        return 1;
    }

    return 0;
}