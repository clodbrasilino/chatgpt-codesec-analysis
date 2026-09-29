#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected ['Flutter', '484', 'is', '77', '129', 'Magnificent', '45'], got <no output>
  *  test case 1 failed: expected ['Dart', '368', 'is', '100', '181', 'Super', '18'], got <no output>
  *  test case 0 failed: expected ['MSM', '240', 'is', '104', '129', 'best', '10'], got <no output>
  */

char* increment_numeric_values(const char* str, int k) {
    if (str == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    size_t new_len = len * 2 + 1;
    char* result = (char*)malloc(new_len);
    if (result == NULL) {
        return NULL;
    }

    size_t res_idx = 0;
    size_t i = 0;

    while (i < len) {
        if (isdigit((unsigned char)str[i])) {
            long val = 0;
            /* Possible weaknesses found:
             *  Value stored to 'start' during its initialization is never read [deadcode.DeadStores]
             *  Variable 'start' is assigned a value that is never used. [unreadVariable]
             */
            size_t start = i;
            while (i < len && isdigit((unsigned char)str[i])) {
                val = val * 10 + (str[i] - '0');
                i++;
            }
            val += k;
            
            /* Possible weaknesses found:
             * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
             */
            char num_str[32];
            int written = snprintf(num_str, sizeof(num_str), "%ld", val);
            if (written > 0 && (size_t)written < sizeof(num_str)) {
                if (res_idx + written >= new_len) {
                    new_len = (res_idx + written) * 2 + 1;
                    char* temp = (char*)realloc(result, new_len);
                    if (temp == NULL) {
                        free(result);
                        return NULL;
                    }
                    result = temp;
                }
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result + res_idx, num_str, written);
                res_idx += written;
            }
        } else {
            if (res_idx + 1 >= new_len) {
                new_len = new_len * 2 + 1;
                char* temp = (char*)realloc(result, new_len);
                if (temp == NULL) {
                    free(result);
                    return NULL;
                }
                result = temp;
            }
            result[res_idx++] = str[i++];
        }
    }

    result[res_idx] = '\0';
    return result;
}

int main(void) {
    const char* input = "There are 5 apples and 12 oranges.";
    int k = 3;

    char* output = increment_numeric_values(input, k);
    if (output != NULL) {
        printf("Original: %s\n", input);
        printf("Modified: %s\n", output);
        free(output);
    } else {
        printf("Memory allocation failed or invalid input.\n");
    }

    return EXIT_SUCCESS;
}