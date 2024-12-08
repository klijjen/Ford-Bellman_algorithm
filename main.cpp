#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

struct edge {
    int a, b, cost; // Начальная вершина, конечная вершина, вес
};

int n, m, v, t; // Количество вершин, рёбер, начальная вершина, целевая вершина
vector<edge> e; // Список рёбер
const int INF = numeric_limits<int>::max(); 

void solve() {
    vector<int> d(n, INF); // Вектор минимальных расстояний
    vector<int> p(n, -1);  // Вектор предков для восстановления пути
    d[v] = 0; // Расстояние до начальной вершины равно 0

    for (;;) {
        bool any = false;
        for (int j = 0; j < m; ++j) {
            if (d[e[j].a] < INF) {
                if (d[e[j].b] > d[e[j].a] + e[j].cost) {
                    d[e[j].b] = d[e[j].a] + e[j].cost;
                    p[e[j].b] = e[j].a; // Обновляем предка для вершины
                    any = true;
                }
            }
        }
        if (!any) break;
    }

    // Проверка на достижимость целевой вершины
    if (d[t] == INF) {
        cout << "No path from " << v << " to " << t << ".\n";
    } else {
        // Восстановление пути
        vector<int> path;
        for (int cur = t; cur != -1; cur = p[cur])
            path.push_back(cur);
        reverse(path.begin(), path.end());

        // Вывод пути и его стоимости
        cout << "Path from " << v << " to " << t << ": ";
        for (size_t i = 0; i < path.size(); ++i)
            cout << path[i] << (i + 1 < path.size() ? " -> " : "");
        cout << "\nPath cost: " << d[t] << "\n";
    }
}

int main() {
    cout << "Введите количество вершин, рёбер, начальную вершину и целевую вершину:\n";
    cin >> n >> m >> v >> t;

    cout << "Введите рёбра графа в формате: начальная_вершина конечная_вершина вес\n";
    e.resize(m);
    for (int i = 0; i < m; ++i) {
        cin >> e[i].a >> e[i].b >> e[i].cost;
    }

    solve();

    return 0;
}
