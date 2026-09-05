#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected ['Red', '', 'Green', 'Orange', 'White'], got ["Red color","Orange#","Green"]
  *  test case 2 failed: expected ['Red &', 'Orange+', 'Green', 'Orange', 'White'], got ["Red &"]
  *  test case 1 failed: expected ['Red', '', 'Green', 'Orange', 'White'], got ["Red &","Orange+","Green"]
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

    for (int i = 0; i < count; i++) {
        if (list[i] == NULL) {
            continue;
        }

        if (strstr(list[i], substr) == NULL) {
            size_t word_len = strlen(list[i]);
            result[res_idx] = (char*)malloc(word_len + 1);
            if (result[res_idx] == NULL) {
                for (int j = 0; j < res_idx; j++) free(result[j]);
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

void print_list(char** list, int count) {
    printf("[");
    for (int i = 0; i < count; i++) {
        printf("'%s'", list[i]);
        if (i < count - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

int main(void) {
    {
        char* words[] = {"Red color", "Red &", "Red", "", "Green", "Orange#", "Orange+", "Orange", "White"};
        int count = sizeof(words) / sizeof(words[0]);
        int out_count = 0;
        char** filtered = remove_words(words, count, "color", &out_count);
        print_list(filtered, out_count);
        if (filtered != NULL) {
            for (int i = 0; i < out_count; i++) free(filtered[i]);
            free(filtered);
        }
    }

    {
        char* words[] = {"Red color", "Red &", "Red", "", "Green", "Orange#", "Orange+", "Orange", "White"};
        int count = sizeof(words) / sizeof(words[0]);
        int out_count = 0;
        char** filtered = remove_words(words, count, " &", &out_count);
        print_list(filtered, out_count);
        if (filtered != NULL) {
            for (int i = 0; i < out_count; i++) free(filtered[i]);
            free(filtered);
        }
    }

    {
        char* words[] = {"Red color", "Red &", "Red", "", "Green", "Orange#", "Orange+", "Orange", "White"};
        int count = sizeof(words) / sizeof(words[0]);
        int out_count = 0;
        char** filtered = remove_words(words, count, "#", &out_count);
        print_list(filtered, out_count);
        if (filtered != NULL) {
            for (int i = 0; i < out_count; i++) free(filtered[i]);
            free(filtered);
        }
    }

    return 0;
}