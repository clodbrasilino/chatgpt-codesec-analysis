#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* abbreviate_road(const char* input) {
    if (input == NULL) {
        return NULL;
    }

    size_t input_len = 0;
    while (input[input_len] != '\0') {
        input_len++;
    }

    char* result = (char*)malloc(input_len + 1);
    if (result == NULL) {
        return NULL;
    }

    const char target[] = "road";
    const char replacement[] = "rd.";
    size_t target_len = sizeof(target) - 1;
    size_t replacement_len = sizeof(replacement) - 1;

    size_t i = 0;
    size_t j = 0;
    size_t current_capacity = input_len;

    while (i < input_len) {
        if (strncmp(&input[i], target, target_len) == 0 &&
            (i == 0 || input[i - 1] == ' ' || input[i - 1] == '\t' || input[i - 1] == '\n') &&
            (i + target_len == input_len || input[i + target_len] == ' ' || input[i + target_len] == '\t' || input[i + target_len] == '\n')) {
            
            size_t new_len = input_len - target_len + replacement_len;
            if (new_len > current_capacity) {
                char* temp = (char*)realloc(result, new_len + 1);
                if (temp == NULL) {
                    free(result);
                    return NULL;
                }
                result = temp;
                current_capacity = new_len;
            }

            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(&result[j], replacement, replacement_len);
            j += replacement_len;
            i += target_len;
            input_len = new_len;
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