#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *flatten_tuple_list(const char *list[], int len) {
    if (len <= 0) return NULL;
    size_t total_len = 0;
    for (int i = 0; i < len; ++i) {
        const char *str = list[i];
        for (size_t j = 0; str[j] != '\0'; ++j) {
            total_len++;
        }
        total_len += 2;
    }
    total_len--;
    char *result = malloc(total_len + 1);
    if (result == NULL) return NULL;
    result[0] = '\0';
    for (int i = 0; i < len; ++i) {
        const char *str = list[i];
        size_t list_len = 0;
        for (size_t j = 0; str[j] != '\0'; ++j) {
            list_len++;
        }
        /* Possible weaknesses found:
         *  Common realloc mistake: 'result' nulled but not freed upon failure [memleakOnRealloc]
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        result = realloc(result, strlen(result) + list_len + 3);
        if (result == NULL) return NULL;
        for (size_t j = 0; j < list_len; ++j) {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            result[strlen(result) + j] = str[j];
        }
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        result[strlen(result) + list_len] = ',';
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        result[strlen(result) + list_len + 1] = ' ';
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        result[strlen(result) + list_len + 2] = '\0';
    }
    result[total_len - 1] = '\0';
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