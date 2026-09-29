#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected ['Red', '', 'Green', 'Orange', 'White'], got ["Red color","Orange#","Green"]
  *  test case 1 failed: expected ['Red', '', 'Green', 'Orange', 'White'], got null
  *  test case 2 failed: expected ['Red &', 'Orange+', 'Green', 'Orange', 'White'], got ["Red &"]
  */

char** remove_words(char** list, int count, const char* substr, int* out_count) {
    if (list == NULL || substr == NULL || out_count == NULL || count <= 0) {
        if (out_count) *out_count = 0;
        return NULL;
    }

    char** result = (char**)malloc(count * sizeof(char*));
    if (result == NULL) {
        *out_count = 0;
        return NULL;
    }

    int res_idx = 0;
    size_t sub_len = strlen(substr);

    for (int i = 0; i < count; i++) {
        if (list[i] == NULL || list[i][0] == '\0') {
            continue;
        }

        if (strstr(list[i], substr) == NULL) {
            size_t word_len = strlen(list[i]);
            result[res_idx] = (char*)malloc(word_len + 1);
            if (result[res_idx] == NULL) {
                for (int j = 0; j < res_idx; j++) {
                    free(result[j]);
                }
                free(result);
                *out_count = 0;
                return NULL;
            }
            memcpy(result[res_idx], list[i], word_len + 1);
            res_idx++;
        }
    }

    if (res_idx == 0) {
        free(result);
        *out_count = 0;
        return NULL;
    }

    char** shrunk_result = (char**)realloc(result, res_idx * sizeof(char*));
    if (shrunk_result == NULL) {
        *out_count = res_idx;
        return result;
    }

    *out_count = res_idx;
    return shrunk_result;
}

int main(void) {
    char* test0[] = {"Red color", "Orange#", "Green", "Orange", "White"};
    int count0 = sizeof(test0) / sizeof(test0[0]);
    int out_count0 = 0;
    char** filtered0 = remove_words(test0, count0, "color", &out_count0);
    if (filtered0 != NULL) {
        for (int i = 0; i < out_count0; i++) {
            printf("%s\n", filtered0[i]);
            free(filtered0[i]);
        }
        free(filtered0);
    }
    
    char* test1[] = {"Red &", "Orange+", "Green", "Orange", "White"};
    int count1 = sizeof(test1) / sizeof(test1[0]);
    int out_count1 = 0;
    char** filtered1 = remove_words(test1, count1, "&", &out_count1);
    if (filtered1 != NULL) {
        for (int i = 0; i < out_count1; i++) {
            printf("%s\n", filtered1[i]);
            free(filtered1[i]);
        }
        free(filtered1);
    }

    return 0;
}