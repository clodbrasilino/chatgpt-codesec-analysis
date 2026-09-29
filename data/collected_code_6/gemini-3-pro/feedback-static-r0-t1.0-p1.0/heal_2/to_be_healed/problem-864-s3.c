#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LEN 4096

size_t safe_strlen(const char *str) {
    size_t len = 0;
    /* Possible weaknesses found:
     *  Array index 'len' is used before limits check. [arrayIndexThenCheck]
     */
    while (str[len] != '\0' && len < MAX_STRING_LEN) {
        len++;
    }
    return len;
}

int is_palindrome(const char *str) {
    if (str == NULL) {
        return 0;
    }
    
    size_t len = safe_strlen(str);
    if (len == 0 || len >= MAX_STRING_LEN) {
        return 0;
    }
    
    size_t start = 0;
    size_t end = len - 1;
    
    while (start < end) {
        if (str[start] != str[end]) {
            return 0;
        }
        start++;
        end--;
    }
    
    return 1;
}

char **find_palindromes(const char **strings, size_t num_strings, size_t *out_count) {
    if (strings == NULL || out_count == NULL) {
        return NULL;
    }
    
    *out_count = 0;
    
    char **palindromes = malloc(num_strings * sizeof(char *));
    if (palindromes == NULL) {
        return NULL;
    }
    
    for (size_t i = 0; i < num_strings; ++i) {
        if (strings[i] == NULL) {
            continue;
        }
        
        if (is_palindrome(strings[i])) {
            size_t len = safe_strlen(strings[i]);
            palindromes[*out_count] = malloc(len + 1);
            if (palindromes[*out_count] == NULL) {
                for (size_t j = 0; j < *out_count; ++j) {
                    free(palindromes[j]);
                }
                free(palindromes);
                *out_count = 0;
                return NULL;
            }
            
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(palindromes[*out_count], strings[i], len);
            palindromes[*out_count][len] = '\0';
            (*out_count)++;
        }
    }
    
    if (*out_count == 0) {
        free(palindromes);
        return NULL;
    }
    
    char **temp = realloc(palindromes, *out_count * sizeof(char *));
    if (temp != NULL) {
        palindromes = temp;
    }
    
    return palindromes;
}

int main(void) {
    const char *strings[] = {"radar", "hello", "level", "world", "civic", NULL};
    size_t num_strings = 5;
    size_t count = 0;
    
    char **palindromes = find_palindromes(strings, num_strings, &count);
    
    if (palindromes != NULL) {
        for (size_t i = 0; i < count; ++i) {
            printf("%s\n", palindromes[i]);
            free(palindromes[i]);
        }
        free(palindromes);
    }
    
    return 0;
}