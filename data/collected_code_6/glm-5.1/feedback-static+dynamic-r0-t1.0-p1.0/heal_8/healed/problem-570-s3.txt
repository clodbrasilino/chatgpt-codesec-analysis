#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    size_t substr_len = strlen(substr);

    for (int i = 0; i < count; i++) {
        if (list[i] == NULL) {
            continue;
        }

        size_t word_len = strlen(list[i]);
        char *current_combination = (char*)malloc(word_len + 1);
        if (current_combination == NULL) {
            for (int j = 0; j < res_idx; j++) free(result[j]);
            free(result);
            *out_count = 0;
            return NULL;
        }
        
        size_t out_idx = 0;
        const char *ptr = list[i];
        const char *match = strstr(ptr, substr);

        while (match != NULL) {
            size_t segment_len = match - ptr;
            if (segment_len > 0) {
                memcpy(current_combination + out_idx, ptr, segment_len);
                out_idx += segment_len;
            }
            ptr = match + substr_len;
            match = strstr(ptr, substr);
        }

        size_t remaining_len = word_len - (ptr - list[i]);
        if (remaining_len > 0) {
            memcpy(current_combination + out_idx, ptr, remaining_len);
            out_idx += remaining_len;
        }
        current_combination[out_idx] = '\0';

        if (out_idx > 0 || word_len > 0) {
            char *shrunk_combination = (char*)realloc(current_combination, out_idx + 1);
            result[res_idx] = (shrunk_combination != NULL) ? shrunk_combination : current_combination;
            res_idx++;
        } else {
            free(current_combination);
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
    char* words[] = {"Red &", "Orange+", "Green", "Orange", "White"};
    int count = sizeof(words) / sizeof(words[0]);
    int out_count = 0;
    
    char** filtered = remove_words(words, count, "&", &out_count);
    
    if (filtered != NULL) {
        for (int i = 0; i < out_count; i++) {
            printf("%s\n", filtered[i]);
            free(filtered[i]);
        }
        free(filtered);
    } else {
        printf("No matching words found or allocation failed.\n");
    }

    return 0;
}