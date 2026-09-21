#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected ['MSM', '240', 'is', '104', '129', 'best', '10'], got <no output>
  *  test case 1 failed: expected ['Dart', '368', 'is', '100', '181', 'Super', '18'], got <no output>
  *  test case 2 failed: expected ['Flutter', '484', 'is', '77', '129', 'Magnificent', '45'], got <no output>
  */

char* increment_numeric_values(const char* input, int k) {
    if (!input) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(input);
    size_t out_capacity = len + 1;
    char* result = malloc(out_capacity);
    if (!result) {
        return NULL;
    }

    size_t buf_idx = 0;
    size_t i = 0;
    while (i < len) {
        if (isdigit((unsigned char)input[i]) || (input[i] == '-' && i + 1 < len && isdigit((unsigned char)input[i+1]))) {
            size_t start = i;
            if (input[i] == '-') i++;
            while (i < len && isdigit((unsigned char)input[i])) {
                i++;
            }
            
            size_t num_len = i - start;
            char* num_str = malloc(num_len + 1);
            if (!num_str) {
                free(result);
                return NULL;
            }
            
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(num_str, input + start, num_len);
            num_str[num_len] = '\0';
            
            long long val = strtoll(num_str, NULL, 10);
            free(num_str);
            
            val += k;
            
            int needed = snprintf(NULL, 0, "%lld", val);
            if (needed < 0) {
                free(result);
                return NULL;
            }
            
            if (buf_idx + needed >= out_capacity) {
                out_capacity = buf_idx + needed + (len - i) + 64;
                char* temp = realloc(result, out_capacity);
                if (!temp) {
                    free(result);
                    return NULL;
                }
                result = temp;
            }
            
            /* Possible weaknesses found:
             * Flawfinder sprintf: Does not check for buffer overflows (CWE-120). Use sprintf_s, snprintf, or vsnprintf. Risk is low because the source has a constant maximum length. (risk 2, buffer)
             */
            sprintf(result + buf_idx, "%lld", val);
            buf_idx += needed;
        } else {
            if (buf_idx + 1 >= out_capacity) {
                out_capacity += 64;
                char* temp = realloc(result, out_capacity);
                if (!temp) {
                    free(result);
                    return NULL;
                }
                result = temp;
            }
            result[buf_idx++] = input[i++];
        }
    }
    
    result[buf_idx] = '\0';
    return result;
}

int main(void) {
    char *input_line = NULL;
    size_t len = 0;
    
    if (getline(&input_line, &len, stdin) == -1) {
        free(input_line);
        return 0;
    }

    int k;
    char *k_line = NULL;
    size_t k_len = 0;

    if (getline(&k_line, &k_len, stdin) != -1) {
        if (sscanf(k_line, "%d", &k) != 1) {
            if (sscanf(input_line, "%d", &k) == 1) {
                char *temp = input_line;
                input_line = k_line;
                k_line = temp;
            }
        }
    } else {
        char *last_space = strrchr(input_line, ' ');
        if (last_space) {
            /* Possible weaknesses found:
             * Flawfinder atoi: Unless checked, the resulting number can exceed the expected range (CWE-190). If source untrusted, check both minimum and maximum, even if the input had no minus sign (large numbers can roll over into negative number; consider saving to an unsigned value if that is intended). (risk 2, integer)
             */
            k = atoi(last_space + 1);
            *last_space = '\0';
        } else {
            free(input_line);
            return 0;
        }
    }

    input_line[strcspn(input_line, "\r\n")] = '\0';
    
    char* output = increment_numeric_values(input_line, k);
    if (output) {
        printf("[");
        int first = 1;
        char* token = strtok(output, " ");
        while (token) {
            if (!first) printf(", ");
            printf("'%s'", token);
            first = 0;
            token = strtok(NULL, " ");
        }
        printf("]\n");
        free(output);
    }
    
    free(input_line);
    if (k_line) free(k_line);
    
    return 0;
}