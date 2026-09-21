## 1. Outcomes and rounds-to-detection-free (FINAL)
deepseek-v4-pro        dfs0= 1192 (40.8%) repaired= 1241 not_df= 489 | median rounds (repaired)=1, 1-round repairs=808
qwen-max               dfs0= 1284 (43.9%) repaired= 1293 not_df= 345 | median rounds (repaired)=1, 1-round repairs=882
glm-5.1                dfs0= 1020 (34.9%) repaired= 1560 not_df= 342 | median rounds (repaired)=2, 1-round repairs=623
kimi-k3                dfs0= 1382 (47.3%) repaired=  974 not_df= 566 | median rounds (repaired)=1, 1-round repairs=597
openai-gpt56-sol       dfs0= 1436 (49.1%) repaired=  921 not_df= 565 | median rounds (repaired)=2, 1-round repairs=305
claude-fable-5         dfs0= 1708 (58.5%) repaired=  911 not_df= 303 | median rounds (repaired)=1, 1-round repairs=605
gemini-3-pro           dfs0= 1812 (62.0%) repaired= 1054 not_df=  56 | median rounds (repaired)=1, 1-round repairs=796
TOTAL dfs0=9834 repaired=7954 not_df=2666 (n=20454)
rounds-to-detection-free distribution (repaired samples, all models): r1=4616, r2=1485, r3=633, r4=375, r5=252, r6=188, r7=125, r8=116, r9=99, r10=65

## 2. Channel comparison (unique model x basename, anywhere in chain)
deepseek-v4-pro        oracle=  9 AFL=142 both= 0 fuzz-only=142 oracle-only= 9
qwen-max               oracle= 19 AFL=171 both=12 fuzz-only=159 oracle-only= 7
glm-5.1                oracle=  3 AFL= 37 both= 0 fuzz-only= 37 oracle-only= 3
kimi-k3                oracle=  1 AFL=103 both= 0 fuzz-only=103 oracle-only= 1
openai-gpt56-sol       oracle=  1 AFL= 18 both= 0 fuzz-only= 18 oracle-only= 1
claude-fable-5         oracle=  0 AFL= 59 both= 0 fuzz-only= 59 oracle-only= 0
gemini-3-pro           oracle=  1 AFL= 78 both= 0 fuzz-only= 78 oracle-only= 1
TOTAL oracle=34 AFL=608 overlap=12 (1.9% of 630 detected programs) fuzz-only=596 (94.6%) oracle-only=22 (3.5%)

## 3. Fuzzable share at round 0
deepseek-v4-pro        fuzzable=856/2922 (29.3%)
qwen-max               fuzzable=793/2922 (27.1%)
glm-5.1                fuzzable=1117/2922 (38.2%)
kimi-k3                fuzzable=1140/2922 (39.0%)
openai-gpt56-sol       fuzzable=1807/2922 (61.8%)
claude-fable-5         fuzzable=1026/2922 (35.1%)
gemini-3-pro           fuzzable=631/2922 (21.6%)

## 4. Detection classes at round 0 (fuzz channel, attributed + signal-only)
   1087  signed integer overflow
     57  float->int conversion
     47  negation overflow
     21  left shift
     17  division by zero / FPE
      5  other: UBSan: variable length array bound evalu
      4  ASan: stack-overflow
      2  ASan: heap-buffer-overflow
      2  other: UBSan: shift exponent 64 is too large fo
      1  other: UBSan: shift exponent 1228654364 is too 
      1  other: UBSan: shift exponent 1535817954 is too 
      1  other: UBSan: shift exponent 444 is too large f
      1  other: UBSan: index -6 out of bounds for type '
      1  other: UBSan: index -4 out of bounds for type '
      1  other: UBSan: index -8 out of bounds for type '

## 5. Sanitizer-oracle classes (anywhere in chain, for complementarity)
      4  UBSan: signed integer overflow: 1139355592 + 1199545584 cann
      3  UBSan: variable length array bound evaluates to non-positive
      3  UBSan: left shift of 1 by 31 places cannot be represented in
      2  ASan: global-buffer-overflow
      2  ASan: stack-buffer-overflow
      2  ASan: BUS
      2  UBSan: signed integer overflow: 9223372036854775807 - -2 can
      2  UBSan: inf is outside the range of representable values of t
      2  UBSan: signed integer overflow: 46341 * 46341 cannot be repr
      2  UBSan: signed integer overflow: 1073741824 + 1139355592 cann
      2  UBSan: 3.48679e+09 is outside the range of representable val
      2  UBSan: signed integer overflow: -1275550393 * 32540576076138