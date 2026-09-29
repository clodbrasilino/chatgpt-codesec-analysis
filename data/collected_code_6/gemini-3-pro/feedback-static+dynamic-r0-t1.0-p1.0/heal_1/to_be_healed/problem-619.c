#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* extract_numbers(const char* input) {
    if (input == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(input);
    char* result = (char*)malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; i < len; ++i) {
        if (isdigit((unsigned char)input[i])) {
            result[j++] = input[i];
        }
    }
    result[j] = '\0';

    return result;
}

int main(void) {
    const char* test_string = "Hello123World456!";
    
    char* extracted = extract_numbers(test_string);
    if (extracted != NULL) {
        printf("%s\n", extracted);
        free(extracted);
    }

    return 0;
}