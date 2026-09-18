import tqdm
import time

vector = []
for i in range(1, 100):
    vector.append(1)

progress = tqdm.tqdm(len(vector))

for i in range(1, len(vector)):
    progress.update()
    print(progress.n)
    time.sleep(1)
