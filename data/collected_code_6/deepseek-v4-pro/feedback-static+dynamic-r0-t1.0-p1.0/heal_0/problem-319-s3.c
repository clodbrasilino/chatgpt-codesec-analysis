#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int find_five_char_words(const char *input, char ***matches, int *match_count) {
    regex_t regex;
    regmatch_t pmatch[1];
    const char *pattern = "\\b[a-zA-Z]{5}\\b";
    int ret;
    int capacity = 10;
    int count = 0;
    char **result = NULL;
    const char *cursor = input;

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret) {
        return -1;
    }

    result = (char **)malloc(capacity * sizeof(char *));
    if (!result) {
        regfree(&regex);
        return -1;
    }

    while (regexec(&regex, cursor, 1, pmatch, 0) == 0) {
        if (count >= capacity) {
            capacity *= 2;
            char **temp = (char **)realloc(result, capacity * sizeof(char *));
            if (!temp) {
                for (int i = 0; i < count; i++) {
                    free(result[i]);
                }
                free(result);
                regfree(&regex);
                return -1;
            }
            result = temp;
        }
        
        int len = pmatch[0].rm_eo - pmatch[0].rm_so;
        result[count] = (char *)malloc((len + 1) * sizeof(char));
        if (!result[count]) {
            for (int i = 0; i < count; i++) {
                free(result[i]);
            }
            free(result);
            regfree(&regex);
            return -1;
        }
        
        strncpy(result[count], cursor + pmatch[0].rm_so, len);
        result[count][len] = '\0';
        count++;
        
        cursor += pmatch[0].rm_eo;
        if (*cursor == '\0') {
            break;
        }
    }

    regfree(&regex);
    
    *matches = result;
    *match_count = count;
    
    return 0;
}

void free_matches(char **matches, int count) {
    if (matches) {
        for (int i = 0; i < count; i++) {
            free(matches[i]);
        }
        free(matches);
    }
}

int main(void) {
    const char *text = "Hello world this is a test with words like apple trees house mouse happy";
    char **matches = NULL;
    int count = 0;
    
    if (find_five_char_words(text, &matches, &count) == 0) {
        printf("Found %d five-character words:\n", count);
        for (int i = 0; i < count; i++) {
            printf("%s\n", matches[i]);
        }
        free_matches(matches, count);
    } else {
        printf("Error processing string\n");
    }
    
    return 0;
}