#include <iostream>
#include <fstream>
#include <algorithm>
#include <limits>

using namespace std;

const int MAXN = 100;
const int INF = numeric_limits<int>::max();

int main() {
    ifstream fin("input.txt");
    int n, m;
    fin >> n >> m;

    // ініціалізуємо матрицю відстаней
    int dist[MAXN][MAXN];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                dist[i][j] = 0;
            }
            else {
                dist[i][j] = INF;
            }
        }
    }

    // зчитуємо ребра та їх ваги
    for (int i = 0; i < m; i++) {
        int u, v, w;
        fin >> u >> v >> w;
        dist[u - 1][v - 1] = w;
        dist[v - 1][u - 1] = w;
    }

    // запускаємо алгоритм Флойда-Уоршелла
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }

    // виводимо матрицю відстаней
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (dist[i][j] == INF) {
                cout << "INF ";
            }
            else {
                cout << dist[i][j] << " ";
            }
        }
        cout << endl;
    }

    // запит користувача на знаходження найкоротшого маршруту
    int start, end;
    cout << "Enter start and end vertices: ";
    cin >> start >> end;

    // знаходимо найкоротший маршрут за допомогою алгоритму Дейкстри
    int prev[MAXN];
    int dist_start[MAXN];
    bool visited[MAXN];

    for (int i = 0; i < n; i++) {
        prev[i] = -1;
        dist_start[i] = INF;
        visited[i] = false;

    }

    dist_start[start - 1] = 0;

    for (int i = 0; i < n; i++) {
        int v = -1;
        for (int j = 0; j < n; j++) {
            if (!visited[j] && (v == -1 || dist_start[j] < dist_start[v])) {
                v = j;
            }
        }

        if (dist_start[v] == INF) {
            break;
        }

        visited[v] = true;

        for (int j = 0; j < n; j++) {
            if (dist_start[v] + dist[v][j] < dist_start[j]) {
                dist_start[j] = dist_start[v] + dist[v][j];
                prev[j] = v;
            }
        }
    }

    // виводимо найкоротший маршрут
    if (dist_start[end - 1] == INF) {
        cout << "No path found." << endl;
    }
    else {
        cout << "Shortest path: ";
        int v = end - 1;
        while (v != -1) {
            cout << v + 1 << " ";
            v = prev[v];
        }
        cout << endl;
        cout << "Length of the shortest path: " << dist_start[end - 1] << endl;
    }

    return 0;
}