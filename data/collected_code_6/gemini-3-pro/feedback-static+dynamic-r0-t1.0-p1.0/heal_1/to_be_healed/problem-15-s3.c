#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char** split_string_at_lowercase(const char* str, int* out_count) {
    if (!str || !out_count) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int length = strlen(str);
    int max_parts = length + 1;
    char** result = (char**)calloc(max_parts, sizeof(char*));
    if (!result) {
        return NULL;
    }

    int count = 0;
    int start = 0;

    for (int i = 0; i <= length; i++) {
        if (islower((unsigned char)str[i]) || str[i] == '\0') {
            if (i > start || str[i] == '\0') {
                int part_len = i - start;
                result[count] = (char*)malloc((part_len + 1) * sizeof(char));
                if (!result[count]) {
                    for (int j = 0; j < count; j++) {
                        free(result[j]);
                    }
                    free(result);
                    return NULL;
                }
                /* Possible weaknesses found:
                 * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
                 */
                strncpy(result[count], str + start, part_len);
                result[count][part_len] = '\0';
                count++;
            }
            start = i + 1;
        }
    }

    *out_count = count;
    return result;
}

int main(void) {
    const char* test_str = "HELLOwWORLDtTEST";
    int count = 0;
    
    char** parts = split_string_at_lowercase(test_str, &count);
    
    if (parts) {
        for (int i = 0; i < count; i++) {
            printf("Part %d: %s\n", i, parts[i]);
            free(parts[i]); 
        }
        free(parts);
    } else {
        printf("Failed to split string or empty result.\n");
    }

    return 0;
}