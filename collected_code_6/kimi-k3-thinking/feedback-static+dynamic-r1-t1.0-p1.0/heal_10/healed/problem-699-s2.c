#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 1024
#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
#define RESULT_BUF_SIZE 32

static char *make_string_result(const char *msg)
{
    size_t len;
    char *result;

    if (msg == NULL) {
        return NULL;
    }

    len = strnlen(msg, (size_t)MAX_STR_LEN);
    result = malloc(len + 1);
    if (result != NULL) {
        memcpy(result, msg, len);
        result[len] = '\0';
    }
    return result;
}

static char *make_count_result(size_t count)
{
    char *result = malloc((size_t)RESULT_BUF_SIZE);
    if (result != NULL) {
        snprintf(result, (size_t)RESULT_BUF_SIZE, "%zu", count);
    }
    return result;
}

char *min_swaps(const char *s1, const char *s2)
{
    size_t i;
    size_t len1;
    size_t len2;
    size_t count10 = 0;
    size_t count01 = 0;

    if (s1 == NULL || s2 == NULL) {
        return make_string_result("Not Possible");
    }

    len1 = strnlen(s1, (size_t)MAX_STR_LEN + 1);
    len2 = strnlen(s2, (size_t)MAX_STR_LEN + 1);

    if (len1 > (size_t)MAX_STR_LEN || len2 > (size_t)MAX_STR_LEN) {
        return make_string_result("Not Possible");
    }

    if (len1 != len2) {
        return make_string_result("Not Possible");
    }

    for (i = 0; i < len1; i++) {
        if ((s1[i] != '0' && s1[i] != '1') ||
            (s2[i] != '0' && s2[i] != '1')) {
            return make_string_result("Not Possible");
        }
        if (s1[i] == '1' && s2[i] == '0') {
            count10++;
        } else if (s1[i] == '0' && s2[i] == '1') {
            count01++;
        }
    }

    if (count10 != count01) {
        return make_string_result("Not Possible");
    }

    return make_count_result(count10);
}

int main(void)
{
    char *str1;
    char *str2;

    str1 = malloc((size_t)MAX_STR_LEN + 1);
    if (str1 == NULL) {
        return 1;
    }

    str2 = malloc((size_t)MAX_STR_LEN + 1);
    if (str2 == NULL) {
        free(str1);
        return 1;
    }

    while (scanf("%" TOSTRING(MAX_STR_LEN) "s %" TOSTRING(MAX_STR_LEN) "s",
                 str1, str2) == 2) {
        char *result;

        str1[MAX_STR_LEN] = '\0';
        str2[MAX_STR_LEN] = '\0';

        result = min_swaps(str1, str2);
        if (result == NULL) {
            break;
        }
        printf("%s\n", result);
        free(result);
    }

    free(str1);
    free(str2);

    return 0;
}