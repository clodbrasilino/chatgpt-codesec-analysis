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

    size_t len = 0;
    while (input[len] != '\0') {
        len++;
    }
    
    size_t out_capacity = len + 128;
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
            
            for (size_t j = 0; j < num_len; j++) {
                num_str[j] = input[start + j];
            }
            num_str[num_len] = '\0';
            
            long long val = strtoll(num_str, NULL, 10);
            free(num_str);
            
            /* Possible weaknesses found:
             * UBSan: signed integer overflow: 9223372036854775807 + 88 cannot be represented in type 'long long' (AFL crash: id:000005,sig:06,src:000023,time:57568,execs:32164,op:havoc,rep:3)
             * UBSan: signed integer overflow: 9223372036854775807 + 257 cannot be represented in type 'long long' (AFL crash: id:000004,sig:06,src:000016,time:56856,execs:31781,op:havoc,rep:4)
             * UBSan: signed integer overflow: 9223372036854775807 + 87 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000023,time:23685,execs:13678,op:havoc,rep:2)
             * UBSan: signed integer overflow: 9223372036854775807 + 1 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000025,time:25016,execs:14406,op:havoc,rep:8)
             * UBSan: signed integer overflow: 9223372036854775807 + 66 cannot be represented in type 'long long' (AFL crash: id:000003,sig:06,src:000037,time:44441,execs:24945,op:havoc,rep:15)
             * UBSan: signed integer overflow: 9223372036854775807 + 6 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:22437,execs:12980,op:havoc,rep:2)
             */
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
            
            snprintf(result + buf_idx, out_capacity - buf_idx, "%lld", val);
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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input_line[4096];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char k_line[1024];
    
    if (!fgets(input_line, sizeof(input_line), stdin)) {
        return 0;
    }
    input_line[strcspn(input_line, "\r\n")] = '\0';

    int k;
    if (fgets(k_line, sizeof(k_line), stdin)) {
        k_line[strcspn(k_line, "\r\n")] = '\0';
        if (sscanf(k_line, "%d", &k) != 1) {
            if (sscanf(input_line, "%d", &k) == 1) {
                /* Possible weaknesses found:
                 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
                 */
                char temp[4096];
                /* Possible weaknesses found:
                 * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
                 */
                strcpy(temp, input_line);
                /* Possible weaknesses found:
                 * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
                 */
                strcpy(input_line, k_line);
                /* Possible weaknesses found:
                 * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
                 */
                strcpy(k_line, temp);
            }
        }
    } else {
        char *last_space = strrchr(input_line, ' ');
        if (last_space) {
            k = (int)strtol(last_space + 1, NULL, 10);
            *last_space = '\0';
        } else {
            return 0;
        }
    }

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
    
    return 0;
}