#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *replace_spaces(const char *str) {
    if (str == NULL) {
        return NULL;
    }
    
    size_t len = strlen(str);
    size_t space_count = 0;
    
    for (size_t i = 0; i < len; i++) {
        if (str[i] == ' ') {
            space_count++;
        }
    }
    
    size_t new_len = len + (space_count * 2) + 1;
    char *result = (char *)malloc(new_len);
    
    if (result == NULL) {
        return NULL;
    }
    
    size_t j = 0;
    for (size_t i = 0; i < len; i++) {
        if (str[i] == ' ') {
            result[j++] = '%';
            result[j++] = '2';
            result[j++] = '0';
        } else {
            result[j++] = str[i];
        }
    }
    
    result[j] = '\0';
    return result;
}

int main(void) {
    const char *test_cases[] = {
        "My Name is Dawood",
        "I am a Programmer",
        "I love Coding"
    };
    
    int num_tests = sizeof(test_cases) / sizeof(test_cases[0]);
    
    for (int t = 0; t < num_tests; t++) {
        const char *test_str = test_cases[t];
        char *replaced = replace_spaces(test_str);
        
        if (replaced != NULL) {
            printf("%s\n", replaced);
            free(replaced);
        } else {
            fprintf(stderr, "Memory allocation failed for test case %d\n", t);
            return 1;
        }
    }
    
    return 0;
}