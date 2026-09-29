#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void move_numbers_to_string(const char *input, char *output, size_t output_size) {
    size_t i, j = 0;
    
    if (input == NULL || output == NULL || output_size == 0) {
        return;
    }
    
    for (i = 0; input[i] != '\0' && j < output_size - 1; i++) {
        if (isdigit((unsigned char)input[i])) {
            output[j++] = input[i];
        }
    }
    
    output[j] = '\0';
}

int main(void) {
    /* Possible weaknesses found:
     *  Assignment 'test_string="abc123def456ghi789"', assigned value is "abc123def456ghi789"
     */
    const char *test_string = "abc123def456ghi789";
    char *result = NULL;
    size_t len;
    
    /* Possible weaknesses found:
     *  Condition 'test_string==NULL' is always false [knownConditionTrueFalse]
     *  Condition 'test_string==NULL' is always false
     */
    if (test_string == NULL) {
        return 1;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(test_string);
    result = (char *)malloc(len + 1);
    
    if (result == NULL) {
        return 1;
    }
    
    move_numbers_to_string(test_string, result, len + 1);
    printf("Original string: %s\n", test_string);
    printf("Numbers extracted: %s\n", result);
    
    free(result);
    
    return 0;
}