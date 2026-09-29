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
    
    size_t new_len = len + (space_count * 2);
    char *result = (char *)malloc(new_len + 1);
    
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
    
    for (int i = 0; i < 3; i++) {
        char *replaced = replace_spaces(test_cases[i]);
        if (replaced != NULL) {
            printf("%s\n", replaced);
            free(replaced);
        }
    }
    
    return 0;
}