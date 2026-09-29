#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** extract_strings(const char* const strings[], size_t num_strings, size_t size, size_t* out_num_strings) {
    if (strings == NULL || num_strings == 0 || size == 0) {
        *out_num_strings = 0;
        return NULL;
    }

    char** result = (char**)malloc(num_strings * sizeof(char*));
    if (result == NULL) {
        *out_num_strings = 0;
        return NULL;
    }

    for (size_t i = 0; i < num_strings; ++i) {
        if (strings[i] != NULL) {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t str_len = strlen(strings[i]);
            if (str_len >= size) {
                result[i] = (char*)malloc((size + 1) * sizeof(char));
                if (result[i] == NULL) {
                    *out_num_strings = 0;
                    for (size_t j = 0; j < i; ++j) {
                        free(result[j]);
                    }
                    free(result);
                    return NULL;
                }
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result[i], strings[i], size);
                result[i][size] = '\0';
            } else {
                result[i] = (char*)malloc((str_len + 1) * sizeof(char));
                if (result[i] == NULL) {
                    *out_num_strings = 0;
                    for (size_t j = 0; j < i; ++j) {
                        free(result[j]);
                    }
                    free(result);
                    return NULL;
                }
                /* Possible weaknesses found:
                 * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
                 */
                strcpy(result[i], strings[i]);
            }
        } else {
            *out_num_strings = 0;
            for (size_t j = 0; j < i; ++j) {
                free(result[j]);
            }
            free(result);
            return NULL;
        }
    }

    *out_num_strings = num_strings;
    return result;
}

int main() {
    const char* const input_strings[] = {"hello", "world", "stackoverflow", "C", "Programming"};
    size_t num_input_strings = sizeof(input_strings) / sizeof(input_strings[0]);
    size_t size = 5;
    size_t num_output_strings;

    char** output_strings = extract_strings(input_strings, num_input_strings, size, &num_output_strings);

    if (output_strings != NULL) {
        for (size_t i = 0; i < num_output_strings; ++i) {
            printf("%s\n", output_strings[i]);
            free(output_strings[i]);
        }
        free(output_strings);
    }

    return 0;
}