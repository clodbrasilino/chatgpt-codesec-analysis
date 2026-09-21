#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_MATCHES 10
#define MAX_ERROR_MSG 256
#define MAX_MATCH_LEN 256

static void print_regex_error(int errcode, const regex_t *regex) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char err_buf[MAX_ERROR_MSG];
    err_buf[0] = '\0';
    regerror(errcode, regex, err_buf, MAX_ERROR_MSG);
    err_buf[MAX_ERROR_MSG - 1] = '\0';
    fprintf(stderr, "Regex error: %s\n", err_buf);
}

int search_literals(const char *input, const char *pattern, char matches[][MAX_MATCH_LEN], int max_matches) {
    regex_t regex;
    regmatch_t pmatch[1];
    int ret;
    int match_count = 0;
    const char *cursor;
    
    if (input == NULL || pattern == NULL || matches == NULL) {
        return -1;
    }
    
    if (max_matches <= 0 || max_matches > MAX_MATCHES) {
        return -1;
    }
    
    ret = regcomp(&regex, pattern, REG_EXTENDED | REG_ICASE);
    if (ret != 0) {
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char err_buf[MAX_ERROR_MSG];
        err_buf[0] = '\0';
        regerror(ret, &regex, err_buf, MAX_ERROR_MSG);
        err_buf[MAX_ERROR_MSG - 1] = '\0';
        fprintf(stderr, "Regex compilation failed: %s\n", err_buf);
        return -1;
    }
    
    cursor = input;
    
    while (match_count < max_matches && *cursor != '\0') {
        ret = regexec(&regex, cursor, 1, pmatch, 0);
        
        if (ret == REG_NOMATCH) {
            break;
        }
        
        if (ret != 0) {
            /* Possible weaknesses found:
             * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
             */
            char err_buf[MAX_ERROR_MSG];
            err_buf[0] = '\0';
            regerror(ret, &regex, err_buf, MAX_ERROR_MSG);
            err_buf[MAX_ERROR_MSG - 1] = '\0';
            fprintf(stderr, "Regex execution failed: %s\n", err_buf);
            regfree(&regex);
            return -1;
        }
        
        if (pmatch[0].rm_so == -1) {
            break;
        }
        
        if (pmatch[0].rm_eo <= pmatch[0].rm_so) {
            break;
        }
        
        int match_len = pmatch[0].rm_eo - pmatch[0].rm_so;
        
        if (match_len > 0) {
            size_t copy_len = (size_t)match_len;
            
            if (copy_len >= (size_t)MAX_MATCH_LEN) {
                copy_len = (size_t)MAX_MATCH_LEN - 1;
            }
            
            if (copy_len > 0) {
                const char *src = cursor + pmatch[0].rm_so;
                /* Possible weaknesses found:
                 * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
                 */
                size_t src_len = strlen(src);
                if (copy_len > src_len) {
                    copy_len = src_len;
                }
                if (copy_len > (size_t)(MAX_MATCH_LEN - 1)) {
                    copy_len = (size_t)(MAX_MATCH_LEN - 1);
                }
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(matches[match_count], src, copy_len);
                matches[match_count][copy_len] = '\0';
                match_count++;
            }
        }
        
        if (pmatch[0].rm_eo == 0) {
            cursor++;
        } else {
            cursor += pmatch[0].rm_eo;
        }
    }
    
    regfree(&regex);
    return match_count;
}

int main(void) {
    const char *text = "The quick brown fox jumps over the lazy dog. Quick fox, brown dog.";
    const char *pattern = "(quick|brown|fox|dog)";
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char matches[MAX_MATCHES][MAX_MATCH_LEN];
    
    memset(matches, 0, sizeof(matches));
    
    int found = search_literals(text, pattern, matches, MAX_MATCHES);
    
    if (found < 0) {
        fprintf(stderr, "Error occurred during search\n");
        return EXIT_FAILURE;
    }
    
    printf("Found %d matches:\n", found);
    for (int i = 0; i < found; i++) {
        matches[i][MAX_MATCH_LEN - 1] = '\0';
        printf("Match %d: %s\n", i + 1, matches[i]);
    }
    
    return EXIT_SUCCESS;
}