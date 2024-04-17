from collect_code_2 import collect_generated_code
from collect_healed_code import collect_generated_healed_code
from sanitize_llm_outputs_into_sources import sanitize_llm_outputs_into_sources
from generate_commented_weak_code import generate_commented_weak_code
from diagnose_code import diagnose_code
from os import listdir


def run_collected_code_3_experiment(sample_round: int):
    current_round = sample_round
    current_healing_round = 0
    collect_generated_code(get_unhealed_path(current_round, current_healing_round))
    current_healing_round += 1
    unhealed_path = get_unhealed_path(current_round, current_healing_round)
    unhealed_files_list = listdir(unhealed_path)
    if len(unhealed_files_list) == 0:
        print(f"No more files to be healed in round {current_round}, healing round {current_healing_round}.")
    while len(unhealed_files_list) > 0:
        print(f"Number of unhealed files: {len(unhealed_files_list)}")
        print(f"Unhealed files: {len(unhealed_files_list)}")
        print(f"Sending to LLM for round {current_round}, healing round {current_healing_round}...")
        healed_path = get_healed_path(current_round, current_healing_round)
        collect_generated_healed_code(unhealed_path, healed_path)
        print(
            f"Sanitizing LLM outputs into C sources for round {current_round}, healing round {current_healing_round}..."
        )
        sanitize_llm_outputs_into_sources(healed_path)
        print(f"Analyzing sources for round {current_round}, healing round {current_healing_round}...")
        diagnose_code(healed_path)
        current_healing_round += 1
        unhealed_path = get_unhealed_path(current_round, current_healing_round)
        print(f"Generating commented sources for round {current_round}, healing round {current_healing_round}...")
        generate_commented_weak_code(healed_path, unhealed_path)
        unhealed_files_list = listdir(unhealed_path)
        if len(unhealed_files_list) == 0:
            print(f"No more files to be healed in round {current_round}, healing round {current_healing_round}.")


def get_unhealed_path(round: int, healing_round: int) -> str:
    if healing_round == 0:
        return f"./collected_code_3/round{round}/heal_{healing_round}/"
    return f"./collected_code_3/round{round}/heal_{healing_round}/to_be_healed/"


def get_healed_path(round: int, healing_round: int) -> str:
    return f"./collected_code_3/round{round}/heal_{healing_round}/healed/"


if __name__ == "__main__":
    run_collected_code_3_experiment(4)
