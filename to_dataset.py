from datasets import Dataset

def get_games(file: str):
    with open(file, 'r') as file:
        content = file.read()
        print(content)