#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void sort_string(char *str) {
    int length = strlen(str);
    for (int i = 0; i < length - 1; i++) {
        for (int j = i + 1; j < length; j++) {
            if (str[i] > str[j]) {
                char temp = str[i];
                str[i] = str[j];
                str[j] = temp;
            }
        }
    }
}

int are_anagrams(const char *str1, const char *str2) {
    if (strlen(str1) != strlen(str2)) {
        return 0;
    }

    char *copy1 = strdup(str1);
    if (!copy1) return 0;
    
    char *copy2 = strdup(str2);
    if (!copy2) {
        free(copy1);
        return 0;
    }

    sort_string(copy1);
    sort_string(copy2);

    int result = strcmp(copy1, copy2) == 0;

    free(copy1);
    free(copy2);

    return result;
}

char **find_anagrams(const char *target, const char **list, int list_size, int *out_count) {
    if (!target || !list || !out_count) {
        if (out_count) *out_count = 0;
        return NULL;
    }

    char **result = malloc(sizeof(char *) * list_size);
    if (!result) {
        *out_count = 0;
        return NULL;
    }

    int count = 0;
    for (int i = 0; i < list_size; i++) {
        if (list[i] && are_anagrams(target, list[i])) {
            result[count] = strdup(list[i]);
            if (result[count]) {
                count++;
            }
        }
    }

    *out_count = count;
    return result;
}

int main(void) {
    const char *target = "listen";
    const char *list[] = {"enlist", "google", "inlets", "banana", "silent"};
    int list_size = sizeof(list) / sizeof(list[0]);
    int out_count = 0;

    char **anagrams = find_anagrams(target, list, list_size, &out_count);

    if (anagrams) {
        for (int i = 0; i < out_count; i++) {
            printf("%s\n", anagrams[i]);
            free(anagrams[i]); 
        }
        free(anagrams);
    }

    return 0;
}