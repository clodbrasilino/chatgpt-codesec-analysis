#!/bin/bash

python3 sanitize_llm_outputs_into_sources.py $1 && \
./diagnose_code.sh $1 && \
python3 data_preprocessing_healed_code.py $1