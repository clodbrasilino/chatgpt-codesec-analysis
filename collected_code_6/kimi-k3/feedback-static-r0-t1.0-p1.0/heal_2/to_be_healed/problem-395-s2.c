#include <stdio.h>
#include <string.h>
#include <limits.h>

#define ALPHABET_SIZE 256

char find_first_non_repeated(const char *str, size_t max_len)
{
    int char_count[ALPHABET_SIZE] = {0};
    size_t len;
    size_t i;
    
    if (str == NULL) {
        return '\0';
    }
    
    len = strnlen(str, max_len);
    
    for (i = 0; i < len; i++) {
        char_count[(unsigned char)str[i]]++;
    }
    
    for (i = 0; i < len; i++) {
        if (char_count[(unsigned char)str[i]] == 1) {
            return str[i];
        }
    }
    
    return '\0';
}

int main(void)
{
    const char *test_string = "programming";
    char result;
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    result = find_first_non_repeated(test_string, strlen(test_string) + 1);
    
    if (result != '\0') {
        printf("First non-repeated character: %c\n", result);
    } else {
        printf("No non-repeated character found\n");
    }
    
    return 0;
}