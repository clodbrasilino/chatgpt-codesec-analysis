#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected ['exercises'], got ["Python","list","exercises","practice","solution"]
  *  test case 1 failed: expected ['Python'], got ["Python","list","exerci","practi","soluti"]
  *  test case 0 failed: expected ['practice', 'solution'], got ["Python","list","exercise","practice","solution"]
  */

char **extract_strings(char **input_list, int list_size, int extract_size, int *output_count) {
    /* Possible weaknesses found:
     *  Assuming that condition 'output_count==NULL' is not redundant
     */
    if (input_list == NULL || list_size <= 0 || extract_size <= 0 || output_count == NULL) {
        /* Possible weaknesses found:
         *  Either the condition 'output_count==NULL' is redundant or there is possible null pointer dereference: output_count. [nullPointerRedundantCheck]
         *  Null pointer dereference
         */
        *output_count = 0;
        return NULL;
    }

    char **result = (char **)malloc(list_size * sizeof(char *));
    if (result == NULL) {
        *output_count = 0;
        return NULL;
    }

    int count = 0;
    for (int i = 0; i < list_size; i++) {
        if (input_list[i] == NULL) {
            continue;
        }

        size_t len = strlen(input_list[i]);
        size_t copy_len = (len < (size_t)extract_size) ? len : (size_t)extract_size;

        result[count] = (char *)malloc((copy_len + 1) * sizeof(char));
        if (result[count] == NULL) {
            for (int j = 0; j < count; j++) {
                free(result[j]);
            }
            free(result);
            *output_count = 0;
            return NULL;
        }

        strncpy(result[count], input_list[i], copy_len);
        result[count][copy_len] = '\0';
        count++;
    }

    if (count == 0) {
        free(result);
        *output_count = 0;
        return NULL;
    }

    char **final_result = (char **)realloc(result, count * sizeof(char *));
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
    char *strings[] = {"Hello", "World", "C", "Programming", "Language"};
    int list_size = sizeof(strings) / sizeof(strings[0]);
    int extract_size = 4;
    int output_count = 0;

    char **extracted = extract_strings(strings, list_size, extract_size, &output_count);

    if (extracted != NULL) {
        for (int i = 0; i < output_count; i++) {
            printf("%s\n", extracted[i]);
            free(extracted[i]);
        }
        free(extracted);
    } else {
        printf("No strings extracted.\n");
    }

    return 0;
}