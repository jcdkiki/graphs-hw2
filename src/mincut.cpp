#include <algorithm>
#include <iostream>
#include <vector>

struct Edge {
    int u;
    int v;
    double weight;
};

double mincut(int n, std::vector<Edge> edges)
{
    while (n > 2) {
        int idx = rand() % edges.size();

        for (auto &e : edges) {
            if (e.u == edges[idx].u)
                e.u = edges[idx].v;
            if (e.v == edges[idx].u)
                e.v = edges[idx].v;
        }

        edges.erase(edges.begin() + idx);
        edges.erase(
            std::remove_if(edges.begin(), edges.end(),
                           [](const Edge &edge) { return edge.u == edge.v; }),
            edges.end());

        n--;
    }

    double res = 0;
    for (auto &e : edges) {
        res += e.weight;
    }

    return res;
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        std::cout << "specify seed\n";
        return 1;
    }

    srand(atoi(argv[1]));

    int n;
    std::cin >> n;
    std::vector<Edge> edges;

    int u, v;
    double weight;
    while (std::cin >> u >> v >> weight) {
        edges.push_back(Edge{u, v, weight});
    }

    double best = 10000000.0;
    for (int i = 0; i < n * n; i++) {
        double res = mincut(n, edges);
        best = std::min(best, res);
    }

    std::cout << best << std::endl;

    return 0;
}
