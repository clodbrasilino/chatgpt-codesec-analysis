#include <stdio.h>
#include <string.h>

char *replace_chars(char *str, size_t size) {
    if (str == NULL || size == 0) {
        return str;
    }
    
    for (size_t i = 0; i < size - 1 && str[i] != '\0'; i++) {
        if (str[i] == ' ' || str[i] == ',' || str[i] == '.') {
            str[i] = ':';
        }
    }
    str[size - 1] = '\0';
    return str;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char text[100];
    const char source[] = "Hello, world. This is a test";
    /* Possible weaknesses found:
     *  Assignment 'source_len=strlen(source)', assigned value is 28
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t source_len = strlen(source);
    size_t dest_size = sizeof(text);
    
    /* Possible weaknesses found:
     *  Condition 'source_len>=dest_size' is always false [knownConditionTrueFalse]
     *  Condition 'source_len>=dest_size' is always false
     */
    if (source_len >= dest_size) {
        /* Possible weaknesses found:
         *  Buffer is accessed out of bounds: source [bufferAccessOutOfBounds]
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(text, source, dest_size - 1);
        text[dest_size - 1] = '\0';
    } else {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(text, source, source_len + 1);
    }
    
    printf("Original: %s\n", text);
    replace_chars(text, sizeof(text));
    printf("Modified: %s\n", text);
    
    return 0;
}