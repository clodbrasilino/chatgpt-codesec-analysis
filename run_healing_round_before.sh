#!/bin/bash

./create_healing_round_folder_structure.sh $1
python3 generate_commented_weak_code.py $1