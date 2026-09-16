#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **filter_strings(char *strings[], int count, char *remove_char, int *new_count) {
    char **filtered = malloc(count * sizeof(char *));
    if (filtered == NULL) {
        *new_count = 0;
        return NULL;
    }
    int j = 0;
    for (int i = 0; i < count; i++) {
        if (strstr(strings[i], remove_char) == NULL) {
            filtered[j] = strings[i];
            j++;
        }
    }
    *new_count = j;
    /* Possible weaknesses found:
     *  Common realloc mistake: 'filtered' nulled but not freed upon failure [memleakOnRealloc]
     */
    filtered = realloc(filtered, j * sizeof(char *));
    return filtered;
}

int main() {
    char *list[] = {"apple", "banana", "cherry", "date", "elderberry"};
    int count = 5;
    int new_count;
    char *remove_char = "a";

    char **filtered_list = filter_strings(list, count, remove_char, &new_count);
    if (filtered_list == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    for (int i = 0; i < new_count; i++) {
        printf("%s\n", filtered_list[i]);
    }

    free(filtered_list);

    return 0;
}