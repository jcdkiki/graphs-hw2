import subprocess
import random
import math
import numpy as np
from matplotlib import pyplot as plt

def generate_connected_graph(seed, n_vertices, n_edges, edge_min, edge_max):
    cmd = f"build/generator-connected {seed} {n_vertices} {n_edges} {edge_min} {edge_max}"
    r = subprocess.run(cmd.split(), stdout=subprocess.PIPE)
    return r.stdout

def find_mincut(graph):
    r = subprocess.run(["build/mincut", f"{random.randrange(1, 100000)}"], stdout=subprocess.PIPE, input=graph)
    return float(r.stdout.decode())

def calculate_avg(arr):
    avg = sum(arr) / len(arr)
    deviation = math.sqrt(sum([(x - avg)**2 for x in arr]) / (len(arr) - 1))
    return avg, deviation

def main():
    xs = []
    mincuts = []
    mincuts_deviation = []
    
    n_vertices = 30
    full_n_edges = n_vertices * (n_vertices - 1) // 2
    for x in [v / 100.0 for v in range(0, 100, 2)]:
        ms = []
        
        n_edges = int(n_vertices - 1 + (full_n_edges - n_vertices + 1) * x)
        print(f"{n_edges}/{full_n_edges}")
        for i in range(10):
            graph = generate_connected_graph(random.randrange(1, 1000000), n_vertices, n_edges, 1, 1)

            mincut = find_mincut(graph)
            ms.append(mincut)
            
        xs.append(x)
        m, m_d = calculate_avg(ms)
        mincuts.append(m)
        mincuts_deviation.append(m_d)

    plt.plot(xs, mincuts, label="mincut")
    plt.fill_between(xs, np.array(mincuts) - np.array(mincuts_deviation), np.array(mincuts) + np.array(mincuts_deviation), color=(0, 0, 0, 0.3))
    plt.legend()
    plt.savefig("mincuts.png")

if __name__ == "__main__":
    main()
