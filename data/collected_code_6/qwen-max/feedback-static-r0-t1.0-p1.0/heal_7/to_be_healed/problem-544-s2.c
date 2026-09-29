#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *flatten_tuple_list(const char *list[], int len) {
    if (len <= 0) return NULL;
    size_t total_len = 0;
    for (int i = 0; i < len; ++i) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t list_len = strlen(list[i]);
        if (list[i][list_len - 1] != '\0') return NULL;
        total_len += list_len + 2;
    }
    total_len--;
    char *result = (char *)malloc(total_len + 1);
    if (result == NULL) return NULL;
    result[0] = '\0';
    for (int i = 0; i < len; ++i) {
        /* Possible weaknesses found:
         *  Variable 'list_len' is assigned a value that is never used. [unreadVariable]
         *  Value stored to 'list_len' during its initialization is never read [deadcode.DeadStores]
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t list_len = strlen(list[i]);
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        if (snprintf(result + strlen(result), total_len - strlen(result) + 1, "%s", list[i]) < 0) return NULL;
        if (i < len - 1) {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            if (snprintf(result + strlen(result), total_len - strlen(result) + 1, ", ") < 0) return NULL;
        }
    }
    return result;
}

int main() {
    const char *tuple_list[] = {"one", "two", "three"};
    int len = 3;
    char *flat_string = flatten_tuple_list(tuple_list, len);
    if (flat_string != NULL) {
        printf("%s\n", flat_string);
        free(flat_string);
    } else {
        printf("Failed to create flat string\n");
    }
    return 0;
}