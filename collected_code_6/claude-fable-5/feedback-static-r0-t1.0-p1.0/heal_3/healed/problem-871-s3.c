#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_INPUT_LEN 4096

static int safe_copy(char *dest, size_t dest_size, size_t dest_offset,
                     const char *src, size_t src_len)
{
    if (dest == NULL || src == NULL) {
        return -1;
    }
    if (dest_offset > dest_size) {
        return -1;
    }
    if (src_len > dest_size - dest_offset) {
        return -1;
    }
    memcpy(dest + dest_offset, src, src_len);
    return 0;
}

int are_rotations(const char *s1, const char *s2)
{
    size_t len1;
    size_t len2;
    size_t temp_size;
    char *temp;
    int result;

    if (s1 == NULL || s2 == NULL) {
        return 0;
    }

    len1 = strnlen(s1, MAX_INPUT_LEN + 1);
    len2 = strnlen(s2, MAX_INPUT_LEN + 1);

    if (len1 > MAX_INPUT_LEN || len2 > MAX_INPUT_LEN) {
        return -1;
    }

    if (len1 != len2) {
        return 0;
    }

    if (len1 == 0) {
        return 1;
    }

    if (len1 > (SIZE_MAX - 1) / 2) {
        return -1;
    }

    temp_size = (2 * len1) + 1;
    temp = malloc(temp_size);
    if (temp == NULL) {
        return -1;
    }

    if (safe_copy(temp, temp_size, 0, s1, len1) != 0) {
        free(temp);
        return -1;
    }

    if (safe_copy(temp, temp_size, len1, s1, len1) != 0) {
        free(temp);
        return -1;
    }

    temp[temp_size - 1] = '\0';

    result = (strstr(temp, s2) != NULL) ? 1 : 0;

    free(temp);
    return result;
}

int main(void)
{
    const char *str1 = "ABCDE";
    const char *str2 = "CDEAB";
    const char *str3 = "ABDCE";
    int res;

    res = are_rotations(str1, str2);
    if (res < 0) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    if (res == 1) {
        printf("\"%s\" and \"%s\" are rotations of each other\n", str1, str2);
    } else {
        printf("\"%s\" and \"%s\" are not rotations of each other\n", str1, str2);
    }

    res = are_rotations(str1, str3);
    if (res < 0) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    if (res == 1) {
        printf("\"%s\" and \"%s\" are rotations of each other\n", str1, str3);
    } else {
        printf("\"%s\" and \"%s\" are not rotations of each other\n", str1, str3);
    }

    return EXIT_SUCCESS;
}