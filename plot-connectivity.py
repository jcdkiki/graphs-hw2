import subprocess
import random
import math
import numpy as np
from matplotlib import pyplot as plt

def generate_graph(seed, n_vertices, n_edges, edge_min, edge_max):
    cmd = f"build/generator {seed} {n_vertices} {n_edges} {edge_min} {edge_max}"
    r = subprocess.run(cmd.split(), stdout=subprocess.PIPE)
    return r.stdout

def find_n_comp(graph):
    r = subprocess.run(["build/connectivity"], stdout=subprocess.PIPE, input=graph)
    return float(r.stdout.decode())

def calculate_avg(arr):
    avg = sum(arr) / len(arr)
    deviation = math.sqrt(sum([(x - avg)**2 for x in arr]) / (len(arr) - 1))
    return avg, deviation

def main():
    xs = []
    ncomps = []
    ncomps_deviation = []
    cyclomatics = []
    cyclomatics_deviation = []
    
    n_vertices = 100
    full_n_edges = n_vertices * (n_vertices - 1) // 2
    for x in [v / 100.0 for v in range(0, 100, 2)]:
        ncs = []
        cycs = []

        n_edges = int(n_vertices - 1 + (full_n_edges - n_vertices + 1) * x)
        print(f"{n_edges}/{full_n_edges}")
        for i in range(100):
            graph = generate_graph(random.randrange(1, 1000000), n_vertices, n_edges, 1, 1)

            n_comp = find_n_comp(graph)
            ncs.append(n_comp)
            cycs.append(n_edges - n_vertices + n_comp)
            
        xs.append(x)
        nc, nc_d = calculate_avg(ncs)
        cyc, cyc_d = calculate_avg(cycs)
        ncomps.append(nc)
        ncomps_deviation.append(nc_d)
        cyclomatics.append(cyc)
        cyclomatics_deviation.append(cyc_d)

    plt.plot(xs, ncomps, label="число компонент связности")
    plt.fill_between(xs, np.array(ncomps) - np.array(ncomps_deviation), np.array(ncomps) + np.array(ncomps_deviation), color=(0, 0, 0, 0.3))
    plt.legend()
    plt.savefig("ncomps.png")

    plt.cla()
    plt.plot(xs, cyclomatics, label="цикломатическое число")
    plt.fill_between(xs, np.array(cyclomatics) - np.array(cyclomatics_deviation), np.array(cyclomatics) + np.array(cyclomatics_deviation), color=(0, 0, 0, 0.3))
    plt.legend()
    plt.savefig("cyclomatics.png")

if __name__ == "__main__":
    main()
