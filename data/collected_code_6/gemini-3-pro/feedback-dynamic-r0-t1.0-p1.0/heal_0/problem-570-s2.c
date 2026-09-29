#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void filter_strings(char ***list, int *count, const char *target) {
    if (!list || !*list || !count || !target) {
        return;
    }

    int current_count = *count;
    int keep_count = 0;
    
    char **filtered_list = malloc(current_count * sizeof(char *));
    if (!filtered_list) {
        return;
    }

    for (int i = 0; i < current_count; ++i) {
        if ((*list)[i] != NULL) {
            if (strstr((*list)[i], target) == NULL) {
                filtered_list[keep_count] = (*list)[i];
                keep_count++;
            } else {
                free((*list)[i]);
            }
        }
    }

    *list = realloc(filtered_list, (keep_count > 0 ? keep_count : 1) * sizeof(char *));
    if (!*list && keep_count > 0) {
        *list = filtered_list; 
    } else if (!*list && keep_count == 0) {
        free(filtered_list);
        *list = NULL;
    }
    
    *count = keep_count;
}

int main(void) {
    int count = 5;
    char **string_list = malloc(count * sizeof(char *));
    if (!string_list) {
        return 1;
    }

    string_list[0] = strdup("apple");
    string_list[1] = strdup("banana");
    string_list[2] = strdup("cherry");
    string_list[3] = strdup("date");
    string_list[4] = strdup("elderberry");

    for (int i = 0; i < count; ++i) {
        if (!string_list[i]) {
            for (int j = 0; j < i; ++j) {
                free(string_list[j]);
            }
            free(string_list);
            return 1;
        }
    }

    const char *target = "an";

    filter_strings(&string_list, &count, target);

    for (int i = 0; i < count; ++i) {
        if (string_list[i]) {
            printf("%s\n", string_list[i]);
            free(string_list[i]);
        }
    }

    free(string_list);

    return 0;
}