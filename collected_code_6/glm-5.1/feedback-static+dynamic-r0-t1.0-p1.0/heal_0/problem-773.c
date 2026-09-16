#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int occurrence;
    int *positions;
} SubstringInfo;

SubstringInfo find_substrings(const char *str, const char *sub) {
    SubstringInfo info;
    info.occurrence = 0;
    info.positions = NULL;

    if (str == NULL || sub == NULL) {
        return info;
    }

    size_t str_len = strlen(str);
    size_t sub_len = strlen(sub);

    if (sub_len == 0 || sub_len > str_len) {
        return info;
    }

    int capacity = 10;
    info.positions = (int *)malloc(capacity * sizeof(int));
    if (info.positions == NULL) {
        info.occurrence = 0;
        return info;
    }

    for (size_t i = 0; i <= str_len - sub_len; i++) {
        if (strncmp(str + i, sub, sub_len) == 0) {
            if (info.occurrence >= capacity) {
                capacity *= 2;
                int *temp = (int *)realloc(info.positions, capacity * sizeof(int));
                if (temp == NULL) {
                    free(info.positions);
                    info.positions = NULL;
                    info.occurrence = 0;
                    return info;
                }
                info.positions = temp;
            }
            info.positions[info.occurrence] = (int)i;
            info.occurrence++;
            i += sub_len - 1;
        }
    }

    if (info.occurrence == 0) {
        free(info.positions);
        info.positions = NULL;
    } else {
        int *temp = (int *)realloc(info.positions, info.occurrence * sizeof(int));
        if (temp != NULL) {
            info.positions = temp;
        }
    }

    return info;
}

int main(void) {
    const char *str = "thisthisthis";
    const char *sub = "this";

    SubstringInfo info = find_substrings(str, sub);

    printf("Occurrence: %d\n", info.occurrence);
    for (int i = 0; i < info.occurrence; i++) {
        printf("Position: %d\n", info.positions[i]);
    }

    free(info.positions);

    return 0;
}