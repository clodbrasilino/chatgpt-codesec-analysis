#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected ['Flutter', '484', 'is', '77', '129', 'Magnificent', '45'], got <no output>
  *  test case 1 failed: expected ['Dart', '368', 'is', '100', '181', 'Super', '18'], got <no output>
  *  test case 0 failed: expected ['MSM', '240', 'is', '104', '129', 'best', '10'], got <no output>
  */

char* increment_numeric_values(const char* input, int k) {
    if (input == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(input);
    size_t out_len = len * 2 + 1;
    char* result = (char*)malloc(out_len);
    if (result == NULL) {
        return NULL;
    }

    size_t i = 0;
    size_t j = 0;

    while (i < len) {
        if (isdigit((unsigned char)input[i])) {
            long long num = 0;
            while (i < len && isdigit((unsigned char)input[i])) {
                num = num * 10 + (input[i] - '0');
                i++;
            }
            
            num += k;
            
            /* Possible weaknesses found:
             * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
             */
            char temp[32];
            int written = snprintf(temp, sizeof(temp), "%lld", num);
            if (written > 0 && j + (size_t)written < out_len) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result + j, temp, written);
                j += written;
            }
        } else {
            if (j < out_len - 1) {
                result[j++] = input[i++];
            } else {
                i++;
            }
        }
    }

    result[j] = '\0';
    return result;
}

int main() {
    const char* str = "The 2 apples cost 15 dollars, and 3 oranges cost 20 dollars.";
    int k = 5;

    char* new_str = increment_numeric_values(str, k);
    if (new_str != NULL) {
        printf("Original: %s\n", str);
        printf("Modified: %s\n", new_str);
        free(new_str);
    } else {
        fprintf(stderr, "Memory allocation failed or invalid input.\n");
        return 1;
    }

    return 0;
}