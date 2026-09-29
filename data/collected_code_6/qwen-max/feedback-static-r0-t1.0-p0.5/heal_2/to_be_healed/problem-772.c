#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'strlen'
  */

char* remove_k_length_words(const char *str, int k) {
    /* Possible weaknesses found:
     *  include the header <string.h> or explicitly provide a declaration for 'strlen'
     *  call to undeclared library function 'strlen' with type 'unsigned long (const char *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  implicit declaration of function 'strlen' [-Wimplicit-function-declaration]
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    char *result = (char*)malloc(len + 1);
    if (result == NULL) return NULL;
    char *write_ptr = result;
    const char *read_ptr = str;
    while (*read_ptr) {
        const char *start_word = read_ptr;
        while (*read_ptr && *read_ptr != ' ') read_ptr++;
        int word_len = (int)(read_ptr - start_word);
        if (word_len != k) {
            for (const char *p = start_word; p < read_ptr; p++) *write_ptr++ = *p;
        }
        if (*read_ptr) *write_ptr++ = *read_ptr++;
    }
    *write_ptr = '\0';
    return result;
}

int main() {
    const char str[] = "This is a test string with some words of different lengths";
    int k = 2;
    char *result = remove_k_length_words(str, k);
    if (result) {
        printf("%s\n", result);
        free(result);
    } else {
        printf("Memory allocation failed\n");
    }
    return 0;
}