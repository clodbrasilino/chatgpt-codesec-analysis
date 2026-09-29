#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

static int is_hex_string(const char *str) {
    if (str == NULL || *str == '\0') {
        return 0;
    }
    
    const char *p = str;
    
    if (p[0] == '0' && (p[1] == 'x' || p[1] == 'X')) {
        p += 2;
        if (*p == '\0') {
            return 0;
        }
    }
    
    while (*p != '\0') {
        if (!isxdigit((unsigned char)*p)) {
            return 0;
        }
        p++;
    }
    
    return 1;
}

static long long parse_hex_value(const char *str) {
    if (str == NULL) {
        return 0;
    }
    
    const char *p = str;
    if (p[0] == '0' && (p[1] == 'x' || p[1] == 'X')) {
        p += 2;
    }
    
    char *endptr = NULL;
    long long value = strtoll(p, &endptr, 16);
    
    if (endptr == p || *endptr != '\0') {
        return 0;
    }
    
    return value;
}

long long count_hex_numbers_in_range(const char *start_str, const char *end_str) {
    if (start_str == NULL || end_str == NULL) {
        return -1;
    }
    
    if (!is_hex_string(start_str) || !is_hex_string(end_str)) {
        return -1;
    }
    
    long long start_val = parse_hex_value(start_str);
    long long end_val = parse_hex_value(end_str);
    
    if (start_val > end_val) {
        long long temp = start_val;
        start_val = end_val;
        end_val = temp;
    }
    
    if (start_val < 0 || end_val < 0) {
        return -1;
    }
    
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 9223372036854775807 + 1 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000017,time:27309,execs:16016,op:havoc,rep:2)
     */
    return end_val - start_val + 1;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000001,sig:06,src:000016,time:32233,execs:19034,op:havoc,rep:2; likely memory-safety defect
  */

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char start_input[64];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char end_input[64];
    
    printf("Enter start hex value: ");
    if (fgets(start_input, sizeof(start_input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(start_input);
    if (len > 0 && start_input[len - 1] == '\n') {
        start_input[len - 1] = '\0';
    }
    
    printf("Enter end hex value: ");
    if (fgets(end_input, sizeof(end_input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(end_input);
    if (len > 0 && end_input[len - 1] == '\n') {
        end_input[len - 1] = '\0';
    }
    
    long long count = count_hex_numbers_in_range(start_input, end_input);
    
    if (count < 0) {
        fprintf(stderr, "Invalid input values\n");
        return 1;
    }
    
    printf("Count of hex numbers in range: %lld\n", count);
    
    return 0;
}