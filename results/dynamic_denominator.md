# Dynamic-analysis denominator: compiled/executed programs

Main cells, rounds 0-5. compiled = .o produced under the
sanitizer build; executed = compiled (test harness runs every
compiled program); fuzzable = .fuzz.txt lacks 'not compilable'
and 'no fuzzable input interface'. Dynamic detected = tests |
oracle | fuzzer findings (gate-injectable).

| Model | programs | compiled r0 | executed (any version) | fuzzable (any version) | dynamic detected | rate among executed |
|---|---:|---:|---:|---:|---:|---:|
| claude-fable-5 | 2922 | 2916 | 2920 | 1068 | 198 | 6.8% |
| openai-gpt56-sol | 2922 | 2786 | 2919 | 1795 | 104 | 3.6% |
| gemini-3-pro | 2922 | 2913 | 2922 | 718 | 201 | 6.9% |
| kimi-k3 | 2922 | 2892 | 2920 | 1131 | 354 | 12.1% |
| deepseek-v4-pro | 2922 | 2862 | 2920 | 826 | 402 | 13.8% |
| qwen-max | 2922 | 2743 | 2914 | 657 | 431 | 14.8% |
| glm-5.1 | 2922 | 2749 | 2921 | 1092 | 347 | 11.9% |
| **Aggregate** | 20454 | 19861 | 20436 | 7287 | 2037 | 10.0% |

Sub-channel detections (aggregate pairs): tests 1367, oracle 34, fuzzer 768.
Compiled at round 0 (aggregate): 19861/20454 (97.1%).
