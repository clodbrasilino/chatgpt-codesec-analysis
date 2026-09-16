# Dynamic-Analysis Findings — Raw Samples (Data Audit)

**Source:** `collected_code_6/*/*/heal_N/*.asan.txt` and `*.test.txt` — the exact reports the pipeline parses
(`comment_inject.extract_standard_messages`) into healing feedback.

**Sanitizer setup:** every sample is compiled as a single TU (generated code + test driver, `main` renamed) with `/usr/bin/clang -fsanitize=address,undefined -g -O1`, executed under a 5s timeout + 512MB address-space cap. Findings are attributed back to the problem source by frame (file stem match).

**AFL++ (fuzz channel):** DISABLED in all cells (`fuzz=false`) — **no `.fuzz.txt` outputs exist anywhere in the dataset**. The AFL++ 5.02c infrastructure is built and validated but was never turned on for the sweeps (60s/file budget would dominate wall-clock). Raw sanitizer console output is not persisted; the parsed one-line-per-finding reports below are the canonical artifacts, and compiled sanitizer binaries are archived under `artifacts/…/build/prog`.

**Prevalence:** 456 non-empty `.asan.txt` reports across the dataset. Finding-type census (first 200 reports): ASan heap 20, stack 18, global 3, attempting-free/double-free 57, SEGV 3; UBSan signed-overflow 19, misaligned load 10, null-pointer load 3, VLA bound 3, shifts 5.


---

## ASan heap-buffer-overflow

**problem-457** (`deepseek-v4-pro`)

**Report (`.asan.txt`):**
```
problem-457.c:25:0:high:ASan: heap-buffer-overflow
```
**Source (lines 21–27, findings marked `>>>`):**
```c
  21             return result;
  22         }
  23     
  24         for (int i = 0; i < m; i++) {
  25 >>>         if (target_freq[sublist_arr[i]] == 0) {
  26                 required++;
  27             }
```

---

## ASan stack-buffer-overflow

**problem-593-s2** (`deepseek-v4-pro`)

**Report (`.asan.txt`):**
```
problem-593-s2.c:34:0:high:ASan: stack-buffer-overflow
```
**Source (lines 30–36, findings marked `>>>`):**
```c
  30     
  31             token = strtok_r(NULL, ".", &saveptr);
  32         }
  33     
  34 >>>     strncpy(ip, result, 15);
  35         ip[15] = '\0';
  36     }
```

---

## ASan global-buffer-overflow

**problem-315-s2** (`deepseek-v4-pro`)

**Report (`.asan.txt`):**
```
problem-315-s2.c:41:0:high:ASan: global-buffer-overflow
```
**Source (lines 37–43, findings marked `>>>`):**
```c
  37         if (max_len >= result_size) {
  38             max_len = result_size - 1;
  39         }
  40     
  41 >>>     memcpy(result, str + max_start, max_len);
  42         result[max_len] = '\0';
  43     
```

---

## ASan heap-use-after-free

**problem-829** (`qwen-max`)

**Report (`.asan.txt`):**
```
problem-829.c:42:0:high:ASan: heap-use-after-free
```
**Source (lines 38–44, findings marked `>>>`):**
```c
  38             if (counts[i].count > 0) {
  39                 secondFrequentCount++;
  40                 if (secondFrequentCount == 2) {
  41                     free(counts);
  42 >>>                 return counts[i].str;
  43                 }
  44             }
```

---

## ASan SEGV + UBSan null store

**problem-539** (`deepseek-v4-pro`)

**Report (`.asan.txt`):**
```
problem-539.c:49:0:high:ASan: SEGV
problem-539.c:49:26:medium:UBSan: member access within null pointer of type 'Node' (aka 'struct Node')
problem-539.c:49:26:medium:UBSan: store to null pointer of type 'int'
```
**Source (lines 45–51, findings marked `>>>`):**
```c
  45     }
  46     
  47     void map_power(int *bases, int size, Node **result) {
  48         if (result == NULL || bases == NULL || size <= 0) {
  49 >>>         return;
  50         }
  51         
```

---

## UBSan signed integer overflow

**problem-675-s3** (`qwen-max`)

**Report (`.asan.txt`):**
```
problem-675-s3.c:4:17:medium:UBSan: signed integer overflow: 1199547824 + 1073741824 cannot be represented in type 'int'
```
**Source (lines 1–6, findings marked `>>>`):**
```c
   1     #include <stdio.h>
   2     
   3     int add_with_condition(int a, int b, int low, int high) {
   4 >>>     int sum = a + b;
   5         if (sum > low && sum < high) {
   6             return 20;
```

---

## UBSan load of null pointer

**problem-154-s3** (`qwen-max`)

**Report (`.asan.txt`):**
```
problem-154-s3.c:16:27:medium:UBSan: load of null pointer of type 'int *'
```
**Source (lines 12–18, findings marked `>>>`):**
```c
  12         int **result = extract_elements(matrix, rows, cols, step);
  13     
  14         for (int i = 0; i < rows; ++i) {
  15             for (int j = 0; j < cols / step; ++j) {
  16 >>>             printf("%d ", result[i][j]);
  17             }
  18             printf("\n");
```

---

## UBSan shift exponent too large

**problem-884** (`qwen-max`)

**Report (`.asan.txt`):**
```
problem-884.c:5:30:medium:UBSan: shift exponent 60189993 is too large for 32-bit type 'unsigned int'
problem-884.c:5:57:medium:UBSan: shift exponent 1139355592 is too large for 32-bit type 'unsigned int'
```
**Source (lines 1–7, findings marked `>>>`):**
```c
   1     #include <stdio.h>
   2     #include <stdbool.h>
   3     
   4     bool checkBitsInRange(unsigned int num, unsigned int start, unsigned int end) {
   5 >>>     unsigned int mask = ((1U << (end - start + 1)) - 1) << start;
   6         return (num & mask) == mask;
   7     }
```

---

## UBSan left shift overflow

**problem-302** (`qwen-max`)

**Report (`.asan.txt`):**
```
problem-302.c:7:22:medium:UBSan: left shift of 1 by 31 places cannot be represented in type 'int'
```
**Source (lines 3–9, findings marked `>>>`):**
```c
   3     
   4     int find_most_significant_set_bit(unsigned int num) {
   5         int msb = -1;
   6         for (int i = 31; i >= 0; --i) {
   7 >>>         if (num & (1 << i)) {
   8                 msb = i;
   9                 break;
```

---

## Test-case failure (the `T` channel, bonus signal)

**problem-102-s2.test.txt** — report:
```
problem-102-s2.c:4:0: error: test case 0 failed: expected 'PythonProgram', got python_rogram
problem-102-s2.c:4:0: error: test case 1 failed: expected 'PythonLanguage', got python_anguage
problem-102-s2.c:4:0: error: test case 2 failed: expected 'ProgrammingLanguage', got programming_anguage
```

**Passing sample for contrast (`problem-971.test.txt`):**
```
problem-971.c:0:0: info: all 3 test cases passed
```
