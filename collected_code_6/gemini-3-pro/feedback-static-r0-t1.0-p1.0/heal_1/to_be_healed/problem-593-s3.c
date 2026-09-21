#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* remove_leading_zeroes(const char* ip) {
    if (ip == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(ip);
    if (len == 0 || len > 15) {
        return NULL;
    }

    char* result = (char*)malloc(16);
    if (result == NULL) {
        return NULL;
    }

    const char* ptr = ip;
    char* res_ptr = result;
    /* Possible weaknesses found:
     *  Variable 'first_digit' is assigned a value that is never used. [unreadVariable]
     */
    int first_digit = 1;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char temp[4] = {0};
    int temp_idx = 0;
    int dot_count = 0;

    while (*ptr != '\0') {
        if (*ptr == '.') {
            if (temp_idx == 0) {
                free(result);
                return NULL;
            }
            temp[temp_idx] = '\0';
            
            /* Possible weaknesses found:
             * Flawfinder atoi: Unless checked, the resulting number can exceed the expected range (CWE-190). If source untrusted, check both minimum and maximum, even if the input had no minus sign (large numbers can roll over into negative number; consider saving to an unsigned value if that is intended). (risk 2, integer)
             */
            int val = atoi(temp);
            if (val > 255) {
                free(result);
                return NULL;
            }
            
            /* Possible weaknesses found:
             * Flawfinder sprintf: Does not check for buffer overflows (CWE-120). Use sprintf_s, snprintf, or vsnprintf. Risk is low because the source has a constant maximum length. (risk 2, buffer)
             */
            res_ptr += sprintf(res_ptr, "%d.", val);
            temp_idx = 0;
            dot_count++;
        } else if (*ptr >= '0' && *ptr <= '9') {
            if (temp_idx < 3) {
                temp[temp_idx++] = *ptr;
            } else {
                free(result);
                return NULL;
            }
        } else {
            free(result);
            return NULL;
        }
        ptr++;
    }

    if (temp_idx == 0 || dot_count != 3) {
        free(result);
        return NULL;
    }
    
    temp[temp_idx] = '\0';
    /* Possible weaknesses found:
     * Flawfinder atoi: Unless checked, the resulting number can exceed the expected range (CWE-190). If source untrusted, check both minimum and maximum, even if the input had no minus sign (large numbers can roll over into negative number; consider saving to an unsigned value if that is intended). (risk 2, integer)
     */
    int val = atoi(temp);
    if (val > 255) {
        free(result);
        return NULL;
    }
    
    /* Possible weaknesses found:
     * Flawfinder sprintf: Does not check for buffer overflows (CWE-120). Use sprintf_s, snprintf, or vsnprintf. Risk is low because the source has a constant maximum length. (risk 2, buffer)
     */
    sprintf(res_ptr, "%d", val);

    return result;
}

int main(void) {
    const char* ip1 = "192.168.001.001";
    char* clean_ip1 = remove_leading_zeroes(ip1);
    if (clean_ip1 != NULL) {
        printf("%s\n", clean_ip1);
        free(clean_ip1);
    }

    const char* ip2 = "010.000.025.105";
    char* clean_ip2 = remove_leading_zeroes(ip2);
    if (clean_ip2 != NULL) {
        printf("%s\n", clean_ip2);
        free(clean_ip2);
    }

    return 0;
}