#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <stdint.h>

char* replace_with_colon(const char* str) {
    if (str == NULL || str[0] == '\0') {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);

    regex_t regex;
    if (regcomp(&regex, "[ ,.]", REG_EXTENDED) != 0) {
        return NULL;
    }

    size_t max_len = len + 1;
    
    char* result = (char*)malloc(max_len);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    regmatch_t match;
    size_t src_offset = 0;
    size_t dest_offset = 0;

    while (src_offset < len) {
        if (regexec(&regex, str + src_offset, 1, &match, 0) == 0) {
            if (match.rm_so > 0) {
                size_t chunk_len = (size_t)match.rm_so;
                if (dest_offset + chunk_len < max_len) {
                    /* Possible weaknesses found:
                     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                     */
                    memcpy(result + dest_offset, str + src_offset, chunk_len);
                    dest_offset += chunk_len;
                } else {
                    dest_offset = max_len - 1;
                    break;
                }
            }
            if (dest_offset + 1 < max_len) {
                result[dest_offset++] = ':';
            } else {
                break;
            }
            src_offset += match.rm_eo;
        } else {
            size_t remaining = len - src_offset;
            if (dest_offset + remaining < max_len) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result + dest_offset, str + src_offset, remaining);
                dest_offset += remaining;
            } else {
                size_t safe_remaining = max_len - dest_offset - 1;
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result + dest_offset, str + src_offset, safe_remaining);
                dest_offset += safe_remaining;
            }
            src_offset += remaining;
        }
    }

    if (dest_offset < max_len) {
        result[dest_offset] = '\0';
    } else {
        result[max_len - 1] = '\0';
    }

    regfree(&regex);
    return result;
}

int main(void) {
    const char* input = "Hello world, this.is a test";
    char* output = replace_with_colon(input);
    
    if (output != NULL) {
        printf("%s\n", output);
        free(output);
    }
    
    return 0;
}