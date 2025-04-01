#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

std::vector<std::vector<double>> adj_mat;

static constexpr double BIG_NUM = 1000000000.0;

int main()
{
    int n;
    std::cin >> n;
    adj_mat.resize(n, std::vector<double>(n, BIG_NUM));
    
    int u, v;
    double weight;
    while (std::cin >> u >> v >> weight) {
        adj_mat[u][v] = weight;
    }

    for (int k=0; k<n; ++k)
        for (int i=0; i<n; ++i)
            for (int j=0; j<n; ++j)
                adj_mat[i][j] = std::min(adj_mat[i][j], adj_mat[i][k] + adj_mat[k][j]);

    double diameter = 0;
    std::vector<double> ext(n, 0);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (adj_mat[i][j] != BIG_NUM) {
                ext[i] = std::max(ext[i], adj_mat[i][j]);
                diameter = std::max(diameter, adj_mat[i][j]);
            }
        }
    }
    
    std::cout << *std::min_element(ext.begin(), ext.end()) << '\n';
    std::cout << diameter << '\n';

    return 0;
}
