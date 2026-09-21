#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_MATCHES 100

void find_words(const char *str) {
    regex_t regex;
    regmatch_t matches[1];
    const char *pattern = "\\b[a-zA-Z]{3,5}\\b";
    int ret;
    char *copy;
    size_t len;
    int count = 0;
    size_t offset = 0;

    if (str == NULL) {
        fprintf(stderr, "Invalid input string\n");
        return;
    }

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char error_buffer[256];
        regerror(ret, &regex, error_buffer, sizeof(error_buffer));
        fprintf(stderr, "Regex compilation failed: %s\n", error_buffer);
        return;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(str);
    copy = (char *)malloc(len + 1);
    if (copy == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        regfree(&regex);
        return;
    }
    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(copy, str);

    printf("Words with 3, 4, or 5 characters:\n");

    while (offset < len && count < MAX_MATCHES) {
        ret = regexec(&regex, copy + offset, 1, matches, 0);
        
        if (ret == REG_NOMATCH) {
            break;
        } else if (ret != 0) {
            /* Possible weaknesses found:
             * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
             */
            char error_buffer[256];
            regerror(ret, &regex, error_buffer, sizeof(error_buffer));
            fprintf(stderr, "Regex execution failed: %s\n", error_buffer);
            break;
        }

        if (matches[0].rm_so != -1) {
            size_t word_len = matches[0].rm_eo - matches[0].rm_so;
            /* Possible weaknesses found:
             * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
             */
            char word[256];
            
            if (word_len < sizeof(word)) {
                /* Possible weaknesses found:
                 * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
                 */
                strncpy(word, copy + offset + matches[0].rm_so, word_len);
                word[word_len] = '\0';
                printf("%s\n", word);
                count++;
            }
            
            offset += matches[0].rm_eo;
        } else {
            break;
        }
    }

    if (count == 0) {
        printf("No matching words found.\n");
    }

    free(copy);
    regfree(&regex);
}

int main(void) {
    const char *test_string = "The quick brown fox jumps over the lazy dog near the river bank";
    
    find_words(test_string);
    
    return 0;
}