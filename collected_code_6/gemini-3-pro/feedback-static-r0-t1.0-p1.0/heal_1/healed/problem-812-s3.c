#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 8192

char* abbreviate_road(const char* input) {
    if (input == NULL) {
        return NULL;
    }

    size_t input_len = 0;
    while (input_len < MAX_STR_LEN && input[input_len] != '\0') {
        input_len++;
    }

    if (input_len == MAX_STR_LEN && input[MAX_STR_LEN - 1] != '\0') {
        return NULL; 
    }

    char* result = (char*)malloc(input_len + 1);
    if (result == NULL) {
        return NULL;
    }

    const char* target = "road";
    const char* replacement = "rd.";
    
    size_t target_len = 0;
    while (target[target_len] != '\0') {
        target_len++;
    }
    
    size_t replacement_len = 0;
    while (replacement[replacement_len] != '\0') {
        replacement_len++;
    }

    size_t i = 0;
    size_t j = 0;

    while (i < input_len) {
        if ((input_len - i >= target_len) &&
            strncmp(&input[i], target, target_len) == 0 &&
            (i == 0 || input[i - 1] == ' ' || input[i - 1] == '\t' || input[i - 1] == '\n') &&
            (i + target_len == input_len || input[i + target_len] == ' ' || input[i + target_len] == '\t' || input[i + target_len] == '\n')) {
            
            snprintf(&result[j], input_len + 1 - j, "%s", replacement);
            j += replacement_len;
            i += target_len;
        } else {
            result[j++] = input[i++];
        }
    }

    result[j] = '\0';
    return result;
}

int main(void) {
    const char* test_strings[] = {
        "The road is long.",
        "A road.",
        "Abbey road",
        "Broad street",
        "roadway",
        "Cross the road carefully.",
        NULL
    };

    for (int i = 0; test_strings[i] != NULL; ++i) {
        char* abbreviated = abbreviate_road(test_strings[i]);
        if (abbreviated != NULL) {
            printf("Original: %s\nAbbreviated: %s\n\n", test_strings[i], abbreviated);
            free(abbreviated);
        } else {
            printf("Memory allocation failed for string: %s\n", test_strings[i]);
        }
    }

    return 0;
}