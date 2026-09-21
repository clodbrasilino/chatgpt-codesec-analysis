#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_INPUT_LEN 1048576

char** split_at_uppercase(const char* input, int* count) {
    if (!input || !count) return NULL;
    
    *count = 0;
    
    size_t len = 0;
    while (len < MAX_INPUT_LEN && input[len] != '\0') {
        len++;
    }
    
    if (len == 0 || len == MAX_INPUT_LEN) return NULL;

    regex_t regex;
    if (regcomp(&regex, "[A-Z]", REG_EXTENDED) != 0) {
        return NULL;
    }

    size_t capacity = 10;
    char** result = malloc(capacity * sizeof(char*));
    if (!result) {
        regfree(&regex);
        return NULL;
    }

    regmatch_t match;
    const char* cursor = input;
    size_t prev_pos = 0;
    
    if (regexec(&regex, cursor, 1, &match, 0) == 0) {
        if (match.rm_so == 0) {
            cursor += 1;
            prev_pos = 1;
        }
    }

    while (regexec(&regex, cursor, 1, &match, 0) == 0) {
        size_t match_pos = (cursor - input) + match.rm_so;
        
        if ((size_t)*count >= capacity) {
            capacity *= 2;
            char** new_result = realloc(result, capacity * sizeof(char*));
            if (!new_result) {
                for (int i = 0; i < *count; i++) free(result[i]);
                free(result);
                regfree(&regex);
                *count = 0;
                return NULL;
            }
            result = new_result;
        }

        size_t part_len = match_pos - prev_pos;
        size_t dest_size = part_len + 1;
        result[*count] = malloc(dest_size * sizeof(char));
        if (!result[*count]) {
            for (int i = 0; i < *count; i++) free(result[i]);
            free(result);
            regfree(&regex);
            *count = 0;
            return NULL;
        }
        
        if (part_len > 0) {
            for (size_t i = 0; i < part_len; i++) {
                result[*count][i] = input[prev_pos + i];
            }
        }
        result[*count][part_len] = '\0';
        (*count)++;
        
        cursor = input + match_pos + 1;
        prev_pos = match_pos;
    }

    size_t part_len = len - prev_pos;
    if ((size_t)*count >= capacity) {
        char** new_result = realloc(result, (*count + 1) * sizeof(char*));
        if (!new_result) {
            for (int i = 0; i < *count; i++) free(result[i]);
            free(result);
            regfree(&regex);
            *count = 0;
            return NULL;
        }
        result = new_result;
    }

    size_t dest_size = part_len + 1;
    result[*count] = malloc(dest_size * sizeof(char));
    if (!result[*count]) {
        for (int i = 0; i < *count; i++) free(result[i]);
        free(result);
        regfree(&regex);
        *count = 0;
        return NULL;
    }

    if (part_len > 0) {
        for (size_t i = 0; i < part_len; i++) {
            result[*count][i] = input[prev_pos + i];
        }
    }
    result[*count][part_len] = '\0';
    (*count)++;

    regfree(&regex);
    return result;
}

int main(void) {
    const char* test_str = "SplitThisStringAtUppercase";
    int count = 0;
    
    char** parts = split_at_uppercase(test_str, &count);
    
    if (parts) {
        for (int i = 0; i < count; i++) {
            printf("%s\n", parts[i]);
            free(parts[i]);
        }
        free(parts);
    }
    
    return 0;
}