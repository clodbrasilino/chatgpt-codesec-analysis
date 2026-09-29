#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_MATCHES 10
#define MAX_ERROR_MSG 256

int search_literals(const char *input, const char *pattern, char matches[][MAX_ERROR_MSG], int max_matches) {
    regex_t regex;
    regmatch_t pmatch[MAX_MATCHES];
    int ret;
    int match_count = 0;
    const char *cursor = input;
    
    if (input == NULL || pattern == NULL || matches == NULL || max_matches <= 0 || max_matches > MAX_MATCHES) {
        return -1;
    }
    
    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char err_buf[MAX_ERROR_MSG] = {0};
        regerror(ret, &regex, err_buf, sizeof(err_buf));
        fprintf(stderr, "Regex compilation failed: %s\n", err_buf);
        return -1;
    }
    
    /* Possible weaknesses found:
     *  Assuming that condition 'match_count<max_matches' is not redundant
     */
    while (match_count < max_matches && *cursor != '\0') {
        ret = regexec(&regex, cursor, MAX_MATCHES, pmatch, 0);
        
        if (ret == REG_NOMATCH) {
            break;
        }
        else if (ret != 0) {
            /* Possible weaknesses found:
             * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
             */
            char err_buf[MAX_ERROR_MSG] = {0};
            regerror(ret, &regex, err_buf, sizeof(err_buf));
            fprintf(stderr, "Regex execution failed: %s\n", err_buf);
            regfree(&regex);
            return -1;
        }
        
        /* Possible weaknesses found:
         *  Assuming condition is false
         */
        if (pmatch[0].rm_so == -1) {
            break;
        }
        
        int match_len = pmatch[0].rm_eo - pmatch[0].rm_so;
        if (match_len > 0) {
            size_t copy_len = (size_t)match_len;
            if (copy_len >= (size_t)MAX_ERROR_MSG) {
                copy_len = (size_t)MAX_ERROR_MSG - 1;
            }
            if (copy_len > 0) {
                /* Possible weaknesses found:
                 *  Condition 'match_count<max_matches' is always true [knownConditionTrueFalse]
                 *  Condition 'match_count<max_matches' is always true
                 */
                if (match_count < max_matches) {
                    /* Possible weaknesses found:
                     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                     */
                    memcpy(matches[match_count], cursor + pmatch[0].rm_so, copy_len);
                    matches[match_count][copy_len] = '\0';
                    match_count++;
                }
            }
        }
        
        cursor += pmatch[0].rm_eo;
        
        if (pmatch[0].rm_eo == 0) {
            cursor++;
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
    char matches[MAX_MATCHES][MAX_ERROR_MSG];
    
    memset(matches, 0, sizeof(matches));
    
    int found = search_literals(text, pattern, matches, MAX_MATCHES);
    
    if (found < 0) {
        fprintf(stderr, "Error occurred during search\n");
        return EXIT_FAILURE;
    }
    
    printf("Found %d matches:\n", found);
    for (int i = 0; i < found && i < MAX_MATCHES; i++) {
        matches[i][MAX_ERROR_MSG - 1] = '\0';
        printf("Match %d: %s\n", i + 1, matches[i]);
    }
    
    return EXIT_SUCCESS;
}