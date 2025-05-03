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

std::vector<int> generateRandomPruferCode()
{
    std::vector<int> prufer_code(n_vertices - 2);
    for (int i = 0; i < prufer_code.size(); i++) {
        prufer_code[i] = rand() % n_vertices;
    }

    return prufer_code;
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

void generateRandomTree()
{
    std::vector<int> prufer = generateRandomPruferCode();
    std::vector<bool> used(n_vertices, false);

    std::vector<int> count(n_vertices);
    for (auto &vertex : prufer) {
        count[vertex]++;
    }

    for (int &u : prufer) {
        for (int v = 0; v < n_vertices; v++) {
            if (!used[v] && count[v] == 0) {
                double len = getRandomEdgeLength();
                adj_list[u].push_back(Edge{v, len});
                adj_list[v].push_back(Edge{u, len});

                used[v] = true;
                count[u]--;
                break;
            }
        }
    }

    std::vector<int> vertices;
    for (int i = 0; i < n_vertices; i++) {
        if (!used[i])
            vertices.push_back(i);
    }

    double edge_len = getRandomEdgeLength();
    adj_list[vertices[0]].push_back({vertices[1], edge_len});
    adj_list[vertices[1]].push_back({vertices[0], edge_len});
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
    while (remaining_edges--) {
        int start, end;
        do {
            start = rand() % n_vertices;
            do {
                end = rand() % n_vertices;
            } while (start == end);
        } while (doesEdgeExist(start, end));

        double len = getRandomEdgeLength();
        adj_list[start].push_back({end, len});
        adj_list[end].push_back({start, len});
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

    if (n_edges < n_vertices - 1) {
        std::cerr << "error: can only generate connected graphs\n";
        exit(1);
    }
}

int main(int argc, char **argv)
{
    readArgs(argc, argv);
    srand(seed);
    generateVertices();
    generateRandomTree();

    addRandomEdges(n_edges - n_vertices + 1);
    printGraph();
}
