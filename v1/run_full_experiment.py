from collect_code import collect_generated_code
from collect_code import collect_healed_code
from sanitize_llm_outputs_into_sources import sanitize_llm_outputs_into_sources
from generate_commented_weak_code import generate_commented_weak_code
from diagnose_code import diagnose_code
from os import listdir


def run_experiment(folder: str):
    current_healing_round = 0
    generation_path = get_unhealed_path(folder, current_healing_round)
    collect_generated_code(generation_path)
    sanitize_llm_outputs_into_sources(generation_path)
    diagnose_code(generation_path)
    current_healing_round += 1
    unhealed_path = get_unhealed_path(folder, current_healing_round)
    generate_commented_weak_code(generation_path, unhealed_path)
    unhealed_files_list = listdir(unhealed_path)
    if len(unhealed_files_list) == 0:
        print(f"No more files to be healed in healing round {current_healing_round}.")
    while len(unhealed_files_list) > 0:
        print(f"Number of unhealed files: {len(unhealed_files_list)}")
        print(f"Unhealed files: {len(unhealed_files_list)}")
        print(f"Sending to LLM for healing round {current_healing_round}...")
        healed_path = get_healed_path(folder, current_healing_round)
        collect_healed_code(unhealed_path, healed_path)
        print(f"Sanitizing LLM outputs into C sources for healing round {current_healing_round}...")
        sanitize_llm_outputs_into_sources(healed_path)
        print(f"Analyzing sources for healing round {current_healing_round}...")
        diagnose_code(healed_path)
        current_healing_round += 1
        unhealed_path = get_unhealed_path(folder, current_healing_round)
        print(f"Generating commented sources for healing round {current_healing_round}...")
        generate_commented_weak_code(healed_path, unhealed_path)
        unhealed_files_list = listdir(unhealed_path)
        if len(unhealed_files_list) == 0:
            print(f"No more files to be healed in healing round {current_healing_round}.")


def get_unhealed_path(path: str, healing_round: int) -> str:
    if healing_round == 0:
        return f"./{path}/heal_{healing_round}/"
    return f"./{path}/heal_{healing_round}/to_be_healed/"


def get_healed_path(path: str, healing_round: int) -> str:
    return f"./{path}/heal_{healing_round}/healed/"


if __name__ == "__main__":
    # run_experiment(sys.argv[1])
    run_experiment("../collected_code_4/round2/")
