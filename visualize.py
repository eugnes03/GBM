import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("data/paths.csv")  
time = df.iloc[:, 0]

paths = df.iloc[:, 1:]

plt.figure()

for col in paths.columns:
    plt.plot(time, paths[col], label=col)

plt.xlabel("Time")
plt.ylabel("Value")
plt.title("Paths over Time")

plt.legend()

plt.show()
