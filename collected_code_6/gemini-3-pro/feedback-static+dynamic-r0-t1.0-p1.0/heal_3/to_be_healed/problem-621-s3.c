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
                /* Possible weaknesses found:
                 * UBSan: signed integer overflow: 3333333333333333333 * 10 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000000,time:758,execs:434,op:havoc,rep:3)
                 * UBSan: signed integer overflow: 999999999999999999 * 10 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000000,time:9846,execs:5473,op:havoc,rep:3)
                 * UBSan: signed integer overflow: 1222222222222222222 * 10 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000001,time:23175,execs:12970,op:havoc,rep:1)
                 */
                num = num * 10 + (input[i] - '0');
                i++;
            }
            
            num += k;
            
            /* Possible weaknesses found:
             * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
             */
            char temp[64];
            int written = snprintf(temp, sizeof(temp), "%lld", num);
            if (written > 0) {
                if (j + (size_t)written >= out_len) {
                    out_len = j + (size_t)written + len + 1;
                    char* new_result = (char*)realloc(result, out_len);
                    if (new_result == NULL) {
                        free(result);
                        return NULL;
                    }
                    result = new_result;
                }
                for (int k_idx = 0; k_idx < written; k_idx++) {
                    result[j + k_idx] = temp[k_idx];
                }
                j += written;
            }
        } else {
            if (j >= out_len - 1) {
                out_len *= 2;
                char* new_result = (char*)realloc(result, out_len);
                if (new_result == NULL) {
                    free(result);
                    return NULL;
                }
                result = new_result;
            }
            result[j++] = input[i++];
        }
    }

    result[j] = '\0';
    return result;
}

int main() {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[4096];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char k_buf[64];
    int k = 0;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(buffer);
    while (len > 0 && (buffer[len-1] == '\r' || buffer[len-1] == '\n')) {
        buffer[len-1] = '\0';
        len--;
    }

    if (fgets(k_buf, sizeof(k_buf), stdin) != NULL) {
        /* Possible weaknesses found:
         * Flawfinder atoi: Unless checked, the resulting number can exceed the expected range (CWE-190). If source untrusted, check both minimum and maximum, even if the input had no minus sign (large numbers can roll over into negative number; consider saving to an unsigned value if that is intended). (risk 2, integer)
         */
        k = atoi(k_buf);
    }

    char* new_str = increment_numeric_values(buffer, k);
    if (new_str != NULL) {
        printf("%s\n", new_str);
        free(new_str);
    }

    return 0;
}