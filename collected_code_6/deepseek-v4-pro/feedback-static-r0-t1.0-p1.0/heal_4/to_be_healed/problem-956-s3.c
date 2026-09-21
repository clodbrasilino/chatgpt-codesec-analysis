#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char **split_at_uppercase(const char *str, int *count) {
    if (str == NULL) {
        if (count != NULL) {
            *count = 0;
        }
        return NULL;
    }
    if (count == NULL) {
        return NULL;
    }
    
    *count = 0;
    
    regex_t regex;
    regmatch_t matches[2];
    int ret;
    
    ret = regcomp(&regex, "[A-Z]", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }
    
    size_t len = strnlen(str, 4096);
    if (len == 4096 && str[4095] != '\0') {
        regfree(&regex);
        return NULL;
    }
    
    int *positions = malloc((len + 1) * sizeof(int));
    if (positions == NULL) {
        regfree(&regex);
        return NULL;
    }
    
    int pos_count = 0;
    const char *p = str;
    size_t offset = 0;
    
    while (offset < len) {
        ret = regexec(&regex, p, 2, matches, 0);
        if (ret == 0) {
            if ((size_t)(offset + matches[0].rm_so) < len) {
                positions[pos_count++] = (int)(offset + matches[0].rm_so);
            }
            p += matches[0].rm_eo;
            offset += matches[0].rm_eo;
        } else {
            break;
        }
    }
    
    char **result = malloc((pos_count + 2) * sizeof(char *));
    if (result == NULL) {
        free(positions);
        regfree(&regex);
        return NULL;
    }
    
    int result_count = 0;
    
    if (pos_count == 0) {
        result[0] = malloc(len + 1);
        if (result[0] == NULL) {
            free(result);
            free(positions);
            regfree(&regex);
            return NULL;
        }
        if (len > 0) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result[0], str, len);
        }
        result[0][len] = '\0';
        result_count = 1;
    } else {
        int start = 0;
        int i;
        for (i = 0; i < pos_count; i++) {
            if (positions[i] > start) {
                int segment_len = positions[i] - start;
                result[result_count] = malloc((size_t)segment_len + 1);
                if (result[result_count] == NULL) {
                    int j;
                    for (j = 0; j < result_count; j++) {
                        free(result[j]);
                    }
                    free(result);
                    free(positions);
                    regfree(&regex);
                    return NULL;
                }
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result[result_count], str + start, (size_t)segment_len);
                result[result_count][segment_len] = '\0';
                result_count++;
            }
            start = positions[i];
        }
        
        if (start < (int)len) {
            int segment_len = (int)(len - (size_t)start);
            result[result_count] = malloc((size_t)segment_len + 1);
            if (result[result_count] == NULL) {
                int j;
                for (j = 0; j < result_count; j++) {
                    free(result[j]);
                }
                free(result);
                free(positions);
                regfree(&regex);
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result[result_count], str + start, (size_t)segment_len);
            result[result_count][segment_len] = '\0';
            result_count++;
        }
    }
    
    result[result_count] = NULL;
    *count = result_count;
    
    free(positions);
    regfree(&regex);
    return result;
}

void free_split_result(char **result) {
    if (result == NULL) return;
    
    int i;
    for (i = 0; result[i] != NULL; i++) {
        free(result[i]);
    }
    free(result);
}

int main(void) {
    const char *test_string = "helloWorldThisIsATest";
    int count;
    
    char **parts = split_at_uppercase(test_string, &count);
    
    if (parts != NULL) {
        printf("Split result:\n");
        int i;
        for (i = 0; i < count; i++) {
            printf("%s\n", parts[i]);
        }
        free_split_result(parts);
    } else {
        printf("Failed to split string\n");
    }
    
    return 0;
}