#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <stdint.h>
#include <errno.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected ['Flutter', '484', 'is', '77', '129', 'Magnificent', '45'], got <no output>
  *  test case 0 failed: expected ['MSM', '240', 'is', '104', '129', 'best', '10'], got <no output>
  *  test case 1 failed: expected ['Dart', '368', 'is', '100', '181', 'Super', '18'], got <no output>
  */

char *increment_numeric_values(const char *str, int k) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = strnlen(str, SIZE_MAX);
    if (len == 0) {
        char *empty = malloc(1);
        if (empty != NULL) {
            empty[0] = '\0';
        }
        return empty;
    }

    if (len > SIZE_MAX / 12) {
        return NULL;
    }

    size_t max_size = len * 12 + 1;
    char *result = malloc(max_size);
    if (result == NULL) {
        return NULL;
    }

    size_t i = 0;
    size_t j = 0;

    while (i < len) {
        if (isdigit((unsigned char)str[i])) {
            size_t start = i;
            while (i < len && isdigit((unsigned char)str[i])) {
                i++;
            }

            size_t num_len = i - start;
            if (num_len > 10) {
                free(result);
                return NULL;
            }

            /* Possible weaknesses found:
             * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
             */
            char num_str[12];
            if (num_len >= sizeof(num_str)) {
                free(result);
                return NULL;
            }

            if (num_len > 0 && num_len < sizeof(num_str)) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(num_str, str + start, num_len);
                num_str[num_len] = '\0';
            } else {
                free(result);
                return NULL;
            }

            char *endptr;
            errno = 0;
            long num = strtol(num_str, &endptr, 10);
            if (errno != 0 || *endptr != '\0' || num < 0 || num > INT_MAX) {
                free(result);
                return NULL;
            }

            long new_num = num + k;
            if (new_num < 0 || new_num > INT_MAX) {
                free(result);
                return NULL;
            }

            int written = snprintf(result + j, max_size - j, "%ld", new_num);
            if (written < 0 || (size_t)written >= max_size - j) {
                free(result);
                return NULL;
            }
            j += (size_t)written;
        } else {
            if (j >= max_size - 1) {
                free(result);
                return NULL;
            }
            result[j++] = str[i++];
        }
    }

    result[j] = '\0';
    return result;
}

int main(void) {
    const char *test_strings[] = {
        "MSM 240 is 104 129 best 10",
        "Dart 368 is 100 181 Super 18",
        "Flutter 484 is 77 129 Magnificent 45"
    };
    int k = 0;
    size_t num_tests = sizeof(test_strings) / sizeof(test_strings[0]);

    for (size_t i = 0; i < num_tests; i++) {
        char *result = increment_numeric_values(test_strings[i], k);
        if (result != NULL) {
            printf("%s\n", result);
            free(result);
        }
    }

    return 0;
}