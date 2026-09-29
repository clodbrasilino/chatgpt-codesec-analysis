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
    
    size_t result_len = 0;
    result[result_len++] = '[';
    result[result_len] = '\0';
    
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
            if (result_len + 3 >= cap) {
                cap *= 2;
                /* Possible weaknesses found:
                 *  Common realloc mistake: 'result' nulled but not freed upon failure [memleakOnRealloc]
                 */
                result = (char*)realloc(result, cap);
            }
            result[result_len++] = ',';
            result[result_len++] = ' ';
            result[result_len] = '\0';
        } else {
            first = 0;
        }
        
        if (is_num) {
            long long num = 0;
            for (const char* q = start; q < p; q++) {
                num = num * 10 + (*q - '0');
            }
            
            if (result_len + 128 >= cap) {
                cap = cap * 2 + 128;
                /* Possible weaknesses found:
                 *  Common realloc mistake: 'result' nulled but not freed upon failure [memleakOnRealloc]
                 */
                result = (char*)realloc(result, cap);
            }
            
            int written = snprintf(result + result_len, cap - result_len, "'%lld'", num + k);
            if (written > 0 && (size_t)written < cap - result_len) {
                result_len += written;
            }
        } else {
            size_t word_len = p - start;
            if (result_len + word_len + 3 >= cap) {
                cap = cap * 2 + word_len + 3;
                /* Possible weaknesses found:
                 *  Common realloc mistake: 'result' nulled but not freed upon failure [memleakOnRealloc]
                 */
                result = (char*)realloc(result, cap);
            }
            result[result_len++] = '\'';
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + result_len, start, word_len);
            result_len += word_len;
            result[result_len++] = '\'';
            result[result_len] = '\0';
        }
    }
    
    if (result_len + 2 >= cap) {
        cap += 2;
        /* Possible weaknesses found:
         *  Common realloc mistake: 'result' nulled but not freed upon failure [memleakOnRealloc]
         */
        result = (char*)realloc(result, cap);
    }
    result[result_len++] = ']';
    result[result_len] = '\0';
    
    return result;
}

int main(void) {
    size_t buf_size = 10000;
    char* buffer = (char*)malloc(buf_size);
    if (!buffer) return 1;
    
    if (!fgets(buffer, buf_size, stdin)) {
        free(buffer);
        return 0;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(buffer);
    while (len > 0 && (buffer[len-1] == '\r' || buffer[len-1] == '\n')) {
        buffer[--len] = '\0';
    }

    char* k_buf = (char*)malloc(buf_size);
    if (!k_buf) {
        free(buffer);
        return 1;
    }
    
    long k = 0;
    if (fgets(k_buf, buf_size, stdin)) {
        k = strtol(k_buf, NULL, 10);
    }

    char* new_str = increment_numeric_values(buffer, (int)k);
    if (new_str) {
        printf("%s\n", new_str);
        free(new_str);
    }

    free(buffer);
    free(k_buf);
    return 0;
}