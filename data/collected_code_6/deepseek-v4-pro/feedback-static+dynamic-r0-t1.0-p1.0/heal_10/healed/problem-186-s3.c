#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_MATCHES 10
#define MAX_ERROR_MSG 256
#define MAX_MATCH_LEN 256

static void print_regex_error(int errcode, const regex_t *regex) {
    char err_buf[MAX_ERROR_MSG];
    memset(err_buf, 0, sizeof(err_buf));
    regerror(errcode, regex, err_buf, sizeof(err_buf) - 1);
    err_buf[sizeof(err_buf) - 1] = '\0';
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
        char err_buf[MAX_ERROR_MSG];
        memset(err_buf, 0, sizeof(err_buf));
        regerror(ret, &regex, err_buf, sizeof(err_buf) - 1);
        err_buf[sizeof(err_buf) - 1] = '\0';
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
            char err_buf[MAX_ERROR_MSG];
            memset(err_buf, 0, sizeof(err_buf));
            regerror(ret, &regex, err_buf, sizeof(err_buf) - 1);
            err_buf[sizeof(err_buf) - 1] = '\0';
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
            size_t remaining_len;
            const char *src = cursor + pmatch[0].rm_so;
            
            remaining_len = strlen(cursor) - (size_t)pmatch[0].rm_so;
            
            if (copy_len > remaining_len) {
                copy_len = remaining_len;
            }
            
            if (copy_len > (size_t)(MAX_MATCH_LEN - 1)) {
                copy_len = (size_t)(MAX_MATCH_LEN - 1);
            }
            
            if (copy_len > 0) {
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
    char matches[MAX_MATCHES][MAX_MATCH_LEN];
    int found;
    int i;
    
    memset(matches, 0, sizeof(matches));
    
    found = search_literals(text, pattern, matches, MAX_MATCHES);
    
    if (found < 0) {
        fprintf(stderr, "Error occurred during search\n");
        return EXIT_FAILURE;
    }
    
    printf("Found %d matches:\n", found);
    for (i = 0; i < found; i++) {
        matches[i][MAX_MATCH_LEN - 1] = '\0';
        printf("Match %d: %s\n", i + 1, matches[i]);
    }
    
    return EXIT_SUCCESS;
}