#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected ['practice', 'solution'], got ["Python","list","exercise","practice","solution"]
  *  test case 2 failed: expected ['exercises'], got ["Python","list","exercises","practice","solution"]
  *  test case 1 failed: expected ['Python'], got ["Python","list","exerci","practi","soluti"]
  */

char **extract_strings(char **input_list, int list_size, int extract_size, int *output_count) {
    if (input_list == NULL || list_size <= 0 || extract_size <= 0 || output_count == NULL) {
        if (output_count != NULL) {
            *output_count = 0;
        }
        return NULL;
    }

    char **result = (char **)malloc((size_t)list_size * sizeof(char *));
    if (result == NULL) {
        *output_count = 0;
        return NULL;
    }

    int count = 0;
    for (int i = 0; i < list_size; i++) {
        if (input_list[i] == NULL) {
            continue;
        }

        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len = strlen(input_list[i]);
        size_t copy_len = (len < (size_t)extract_size) ? len : (size_t)extract_size;

        result[count] = (char *)malloc(copy_len + 1);
        if (result[count] == NULL) {
            for (int j = 0; j < count; j++) {
                free(result[j]);
            }
            free(result);
            *output_count = 0;
            return NULL;
        }

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result[count], input_list[i], copy_len);
        result[count][copy_len] = '\0';
        count++;
    }

    if (count == 0) {
        free(result);
        *output_count = 0;
        return NULL;
    }

    char **final_result = (char **)realloc(result, (size_t)count * sizeof(char *));
    if (final_result == NULL) {
        for (int j = 0; j < count; j++) {
            free(result[j]);
        }
        free(result);
        *output_count = 0;
        return NULL;
    }

    *output_count = count;
    return final_result;
}

int main(void) {
    char *strings[] = {"Python", "list", "exercise", "practice", "solution"};
    int list_size = sizeof(strings) / sizeof(strings[0]);
    int extract_size = 8;
    int output_count = 0;

    char **extracted = extract_strings(strings, list_size, extract_size, &output_count);

    if (extracted != NULL) {
        printf("[");
        for (int i = 0; i < output_count; i++) {
            printf("'%s'", extracted[i]);
            if (i < output_count - 1) {
                printf(", ");
            }
            free(extracted[i]);
        }
        printf("]\n");
        free(extracted);
    } else {
        printf("[]\n");
    }

    return 0;
}