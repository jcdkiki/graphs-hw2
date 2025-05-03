#include <algorithm>
#include <iostream>
#include <vector>

struct Edge {
    int v;
    double weight;
};

int cur_col = 0;
std::vector<int> color;
std::vector<std::vector<Edge>> adj_list;

void dfs(int i)
{
    if (color[i] != -1)
        return;
    color[i] = cur_col;

    for (Edge &e : adj_list[i]) {
        dfs(e.v);
    }
}

int main()
{
    int n;
    std::cin >> n;
    adj_list.resize(n);
    color.resize(n, -1);

    int u, v;
    double weight;
    while (std::cin >> u >> v >> weight) {
        adj_list[u].push_back(Edge{v, weight});
    }

    for (int i = 0; i < n; i++) {
        if (color[i] == -1) {
            dfs(i);
            cur_col++;
        }
    }

    std::cout << cur_col << std::endl;

    return 0;
}
