#include <iostream>
#include <vector>

int seed;
int n_vertices;
int n_edges;
int edge_min;
int edge_max;

struct Edge {
    int v;
    double weight;
};

std::vector<std::vector<Edge>> adj_list;

void generateVertices()
{
    adj_list.resize(n_vertices);
}

double getRandomEdgeLength()
{
    double range = (edge_max - edge_min);
    return edge_min + (rand() / ((double)RAND_MAX / range));
}

void printGraph()
{
    std::cout << n_vertices << std::endl;

    for (int i = 0; i < n_vertices; i++) {
        for (auto &edge : adj_list[i]) {
            std::cout << i << ' ' << edge.v << ' ' << edge.weight << '\n';
        }
    }
}

bool doesEdgeExist(int edge_start, int edge_end)
{
    for (auto &edge : adj_list[edge_start]) {
        if (edge.v == edge_end) {
            return true;
        }
    }
    return false;
}

void addRandomEdges(int remaining_edges)
{
    for (; remaining_edges != 0; remaining_edges--) {
        int start, end;
        do {
            start = rand() % n_vertices;
            do {
                end = rand() % n_vertices;
            } while (start == end);
        } while (doesEdgeExist(start, end));

        double len = getRandomEdgeLength();
        adj_list[start].push_back({end, len});
    }
}

void readArgs(int argc, char **argv)
{
    argc--;
    argv++;
    if (argc != 5) {
        std::cerr
            << "usage: measure SEED N_VERTICES N_EDGES EDGE_MIN EDGE_MAX\n";
        exit(1);
    }

    seed = atoi(argv[0]);
    n_vertices = atoi(argv[1]);
    n_edges = atoi(argv[2]);
    edge_min = atoi(argv[3]);
    edge_max = atoi(argv[4]);
}

int main(int argc, char **argv)
{
    readArgs(argc, argv);
    srand(seed);
    generateVertices();
    addRandomEdges(n_edges);
    printGraph();
}
