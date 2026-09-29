#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
 /* Possible weaknesses found:
  *  include '<ctype.h>' or provide a declaration of 'tolower'
  */

bool is_vowel(char c) {
    /* Possible weaknesses found:
     *  implicit declaration of function 'tolower' [-Wimplicit-function-declaration]
     *  include the header <ctype.h> or explicitly provide a declaration for 'tolower'
     *  call to undeclared library function 'tolower' with type 'int (int)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
    c = (char)tolower((unsigned char)c);
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
}

char* reverse_vowels(const char* s) {
    if (s == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(s);
    char* result = (char*)malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(result, s);

    if (len == 0) {
        return result;
    }

    size_t left = 0;
    size_t right = len - 1;

    while (left < right) {
        while (left < right && !is_vowel(result[left])) {
            left++;
        }
        while (left < right && !is_vowel(result[right])) {
            right--;
        }

        if (left < right) {
            char temp = result[left];
            result[left] = result[right];
            result[right] = temp;
            left++;
            right--;
        }
    }

    return result;
}

int main(void) {
    const char* test_str = "hello world";
    char* reversed = reverse_vowels(test_str);
    
    if (reversed != NULL) {
        printf("Original: %s\n", test_str);
        printf("Reversed: %s\n", reversed);
        free(reversed);
    } else {
        fprintf(stderr, "Memory allocation failed or input was NULL.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}