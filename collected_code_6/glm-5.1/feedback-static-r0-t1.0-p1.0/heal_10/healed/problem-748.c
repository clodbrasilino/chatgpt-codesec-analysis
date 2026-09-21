#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *space_out_capitals(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    size_t str_len = strlen(str);
    size_t max_len = str_len * 2 + 1;
    char *result = malloc(max_len);
    if (result == NULL) {
        return NULL;
    }

    const char *p = str;
    char *out = result;
    size_t out_remaining = max_len;

    while (*p != '\0') {
        if (p != str && *p >= 'A' && *p <= 'Z') {
            if (out_remaining <= 1) {
                free(result);
                return NULL;
            }
            *out++ = ' ';
            out_remaining--;
        }

        if (out_remaining <= 1) {
            free(result);
            return NULL;
        }
        *out++ = *p++;
        out_remaining--;
    }

    *out = '\0';

    size_t final_len = strlen(result) + 1;
    char *shrunk = realloc(result, final_len);
    if (shrunk != NULL) {
        return shrunk;
    }
    return result;
}

int main(void) {
    char *res1 = space_out_capitals("HelloWorldExample");
    if (res1 != NULL) {
        printf("%s\n", res1);
        free(res1);
    }

    char *res2 = space_out_capitals("ThisIsATest");
    if (res2 != NULL) {
        printf("%s\n", res2);
        free(res2);
    }

    char *res3 = space_out_capitals("Already Spaced");
    if (res3 != NULL) {
        printf("%s\n", res3);
        free(res3);
    }

    char *res4 = space_out_capitals(NULL);
    if (res4 == NULL) {
        printf("NULL handled\n");
    }

    return 0;
}