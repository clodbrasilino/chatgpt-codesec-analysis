#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/* Possible weaknesses found:
 *  Parameter 'num' can be declared as pointer to const [constParameterPointer]
 */
int* multiply_by_single_digit(int* num, int len, int digit, int* result_len) {
    int carry = 0;
    int* result = (int*)malloc((len + 1) * sizeof(int));
    if (result == NULL) {
        *result_len = 0;
        return NULL;
    }
    
    for (int i = 0; i < len; i++) {
        int product = num[i] * digit + carry;
        result[i] = product % 10;
        carry = product / 10;
    }
    
    if (carry > 0) {
        result[len] = carry;
        *result_len = len + 1;
    } else {
        *result_len = len;
    }
    
    return result;
}

/* Possible weaknesses found:
 *  Parameter 'num2' can be declared as pointer to const [constParameterPointer]
 */
int* multiply_numbers(int* num1, int len1, int* num2, int len2, int* result_len) {
    int* result = (int*)calloc(len1 + len2, sizeof(int));
    if (result == NULL) {
        *result_len = 0;
        return NULL;
    }
    
    for (int i = 0; i < len2; i++) {
        int carry = 0;
        int inner_len;
        int* temp = multiply_by_single_digit(num1, len1, num2[i], &inner_len);
        if (temp == NULL) {
            free(result);
            *result_len = 0;
            return NULL;
        }
        
        for (int j = 0; j < inner_len; j++) {
            int sum = result[i + j] + temp[j] + carry;
            result[i + j] = sum % 10;
            carry = sum / 10;
        }
        
        int pos = i + inner_len;
        while (carry > 0) {
            int sum = result[pos] + carry;
            result[pos] = sum % 10;
            carry = sum / 10;
            pos++;
        }
        
        free(temp);
    }
    
    *result_len = len1 + len2;
    while (*result_len > 1 && result[*result_len - 1] == 0) {
        (*result_len)--;
    }
    
    return result;
}

int* power_digits(int base, int exponent, int* result_len) {
    if (exponent == 0) {
        int* result = (int*)malloc(sizeof(int));
        if (result == NULL) {
            *result_len = 0;
            return NULL;
        }
        result[0] = 1;
        *result_len = 1;
        return result;
    }
    
    int base_len = 0;
    int temp_base = base;
    if (temp_base == 0) {
        base_len = 1;
    } else {
        while (temp_base > 0) {
            base_len++;
            temp_base /= 10;
        }
    }
    
    int* base_digits = (int*)malloc(base_len * sizeof(int));
    if (base_digits == NULL) {
        *result_len = 0;
        return NULL;
    }
    
    temp_base = base;
    for (int i = 0; i < base_len; i++) {
        base_digits[i] = temp_base % 10;
        temp_base /= 10;
    }
    
    int* result = (int*)malloc(sizeof(int));
    if (result == NULL) {
        free(base_digits);
        *result_len = 0;
        return NULL;
    }
    result[0] = 1;
    *result_len = 1;
    
    for (int i = 0; i < exponent; i++) {
        int new_len;
        int* temp_result = multiply_numbers(result, *result_len, base_digits, base_len, &new_len);
        if (temp_result == NULL) {
            free(result);
            free(base_digits);
            *result_len = 0;
            return NULL;
        }
        free(result);
        result = temp_result;
        *result_len = new_len;
    }
    
    free(base_digits);
    return result;
}

int sum_of_digits(int base, int exponent) {
    int len;
    int* digits = power_digits(base, exponent, &len);
    
    if (digits == NULL) {
        return -1;
    }
    
    int sum = 0;
    for (int i = 0; i < len; i++) {
        sum += digits[i];
    }
    
    free(digits);
    return sum;
}

int main(void) {
    int base = 2;
    int exponent = 15;
    int result = sum_of_digits(base, exponent);
    
    if (result != -1) {
        printf("%d\n", result);
        return 0;
    }
    
    return 1;
}