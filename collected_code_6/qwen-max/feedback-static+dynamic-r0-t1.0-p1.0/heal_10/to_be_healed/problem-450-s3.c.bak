#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected ['Python'], got <no output>
  *  test case 0 failed: expected ['practice', 'solution'], got <no output>
  *  test case 2 failed: expected ['exercises'], got <no output>
  */

char** extract_strings(const char* const strings[], size_t num_strings, size_t size, size_t* out_num_strings) {
    *out_num_strings = 0;
    if (strings == NULL || num_strings == 0 || size == 0) return NULL;

    char** result = (char**)malloc(num_strings * sizeof(char*));
    if (result == NULL) return NULL;

    size_t count = 0;
    for (size_t i = 0; i < num_strings; ++i) {
        if (strings[i] != NULL) {
            size_t str_len = strlen(strings[i]);
            size_t alloc_size = (str_len < size) ? str_len + 1 : size;

            result[count] = (char*)malloc(alloc_size * sizeof(char));
            if (result[count] == NULL) {
                for (size_t j = 0; j < count; ++j) {
                    free(result[j]);
                }
                free(result);
                return NULL;
            }

            if (str_len >= size) {
                strncpy(result[count], strings[i], size - 1);
                result[count][size - 1] = '\0';
            } else {
                strcpy(result[count], strings[i]);
            }
            ++count;
        }
    }

    *out_num_strings = count;
    return result;
}

int main() {
    const char* const input_strings[] = {"practice", "solution", "exercises", "Python", "C"};
    size_t num_input_strings = sizeof(input_strings) / sizeof(input_strings[0]);
    size_t size = 7;
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