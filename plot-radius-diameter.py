import subprocess
import random
import math
import numpy as np
from matplotlib import pyplot as plt

def generate_connected_graph(seed, n_vertices, n_edges, edge_min, edge_max):
    cmd = f"build/generator-connected {seed} {n_vertices} {n_edges} {edge_min} {edge_max}"
    r = subprocess.run(cmd.split(), stdout=subprocess.PIPE)
    return r.stdout

def find_radius_diameter(graph):
    r = subprocess.run(["build/radius-diameter"], stdout=subprocess.PIPE, input=graph)
    l = r.stdout.decode().splitlines()
    return float(l[0]), float(l[1])

def calculate_avg(arr):
    avg = sum(arr) / len(arr)
    deviation = math.sqrt(sum([(x - avg)**2 for x in arr]) / (len(arr) - 1))
    return avg, deviation

def main():
    xs = []
    radiuses = []
    diameters = []
    radiuses_deviation = []
    diameters_deviation = []

    n_vertices = 30
    full_n_edges = n_vertices * (n_vertices - 1) // 2
    #for n_edges in range(n_vertices - 1, full_n_edges + 1):
    for x in [v / 100.0 for v in range(0, 100, 2)]:
        rs = []
        ds = []
        
        n_edges = int(n_vertices - 1 + (full_n_edges - n_vertices + 1) * x)
        #x = (n_edges - n_vertices + 1) / (n_vertices * (n_vertices - 1) // 2 - n_vertices + 1)
        print(f"{n_edges}/{full_n_edges}")
        for i in range(100):
            graph = generate_connected_graph(random.randrange(1, 1000000), n_vertices, n_edges, 1, 1)

            r, d = find_radius_diameter(graph)
            rs.append(r)
            ds.append(d)

        xs.append(x)
        r, r_d = calculate_avg(rs)
        d, d_d = calculate_avg(ds)
        radiuses.append(r)
        diameters.append(d)
        radiuses_deviation.append(r_d)
        diameters_deviation.append(d_d)

    plt.plot(xs, radiuses, label="radius")
    plt.plot(xs, diameters, label="diameter")
    plt.fill_between(xs, np.array(radiuses) - np.array(radiuses_deviation), np.array(radiuses) + np.array(radiuses_deviation), color=(0, 0, 0, 0.3))
    plt.fill_between(xs, np.array(diameters) - np.array(diameters_deviation), np.array(diameters) + np.array(diameters_deviation), color=(0, 0, 0, 0.3))
    plt.yscale("log", base=2)
    plt.legend()
    plt.savefig("radius-diameter.png")

if __name__ == "__main__":
    main()
