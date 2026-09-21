#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* abbreviate_road(const char* input) {
    if (input == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t input_len = strlen(input);
    
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

    while (i < input_len) {
        if (strncmp(&input[i], target, target_len) == 0 &&
            (i == 0 || input[i - 1] == ' ' || input[i - 1] == '\t' || input[i - 1] == '\n') &&
            (i + target_len == input_len || input[i + target_len] == ' ' || 
             input[i + target_len] == '\t' || input[i + target_len] == '\n')) {
            
            /* Possible weaknesses found:
             * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
             */
            strncpy(&result[j], replacement, replacement_len);
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