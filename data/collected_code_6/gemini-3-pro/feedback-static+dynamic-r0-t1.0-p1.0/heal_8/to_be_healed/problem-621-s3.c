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
    if (!input) return NULL;
    size_t cap = 10000;
    char* result = (char*)malloc(cap);
    if (!result) return NULL;
    
    result[0] = '[';
    result[1] = '\0';
    size_t result_len = 1;
    
    const char* p = input;
    int first = 1;
    
    while (*p) {
        while (*p && isspace((unsigned char)*p)) p++;
        if (!*p) break;
        
        const char* start = p;
        while (*p && !isspace((unsigned char)*p)) p++;
        
        int is_num = 1;
        for (const char* q = start; q < p; q++) {
            if (!isdigit((unsigned char)*q)) {
                is_num = 0;
                break;
            }
        }
        
        if (!first) {
            /* Possible weaknesses found:
             * Flawfinder strcat: Does not check for buffer overflows when concatenating to destination [MS-banned] (CWE-120). Consider using strcat_s, strncat, strlcat, or snprintf (warning: strncat is easily misused). Risk is low because the source is a constant string. (risk 2, buffer)
             */
            strcat(result, ", ");
            result_len += 2;
        } else {
            first = 0;
        }
        
        if (is_num) {
            long long num = 0;
            for (const char* q = start; q < p; q++) {
                num = num * 10 + (*q - '0');
            }
            /* Possible weaknesses found:
             * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
             */
            char buf[128];
            snprintf(buf, sizeof(buf), "'%lld'", num + k);
            /* Possible weaknesses found:
             * Flawfinder strcat: Does not check for buffer overflows when concatenating to destination [MS-banned] (CWE-120). Consider using strcat_s, strncat, strlcat, or snprintf (warning: strncat is easily misused). (risk 4, buffer)
             */
            strcat(result, buf);
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            result_len += strlen(buf);
        } else {
            result[result_len++] = '\'';
            for (const char* q = start; q < p; q++) {
                result[result_len++] = *q;
            }
            result[result_len++] = '\'';
            result[result_len] = '\0';
        }
    }
    /* Possible weaknesses found:
     * Flawfinder strcat: Does not check for buffer overflows when concatenating to destination [MS-banned] (CWE-120). Consider using strcat_s, strncat, strlcat, or snprintf (warning: strncat is easily misused). Risk is low because the source is a constant character. (risk 1, buffer)
     */
    strcat(result, "]");
    return result;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[8192];
    if (!fgets(buffer, sizeof(buffer), stdin)) {
        return 0;
    }
    
    size_t len = 0;
    while (buffer[len] != '\0') {
        len++;
    }
    while (len > 0 && (buffer[len-1] == '\r' || buffer[len-1] == '\n')) {
        buffer[--len] = '\0';
    }

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char k_buf[256];
    long k = 0;
    if (fgets(k_buf, sizeof(k_buf), stdin)) {
        k = strtol(k_buf, NULL, 10);
    }

    char* new_str = increment_numeric_values(buffer, (int)k);
    if (new_str) {
        printf("%s\n", new_str);
        free(new_str);
    }

    return 0;
}