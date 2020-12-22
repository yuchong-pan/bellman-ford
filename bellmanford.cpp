#include <algorithm>
#include <climits>
#include <cstdio>
#include <utility>
#include <vector>

using namespace std;

const int N = 100 + 5;
const int INFTY = INT_MAX;

int d[N][N];
vector<pair<int, int>> e[N];

void bellmanford(int n, int s)
{
    for (int k = 0; k <= n; k++)
    {
        for (int i = 1; i <= n; i++)
        {
            d[k][i] = INFTY;
        }
    }
    d[0][s] = 0;
    for (int k = 1; k <= n; k++)
    {
        for (int i = 1; i <= n; i++)
        {
            d[k][i] = d[k - 1][i];
        }
        for (int i = 1; i <= n; i++)
        {
            for (auto e : e[i])
            {
                if (d[k][i] + e.second < d[k][e.first])
                {
                    d[k][e.first] = d[k][i] + e.second;
                }
            }
        }
    }
}

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++)
    {
        int u, v, c;
        scanf("%d%d%d", &u, &v, &c);
        e[u].push_back(make_pair(v, c));
    }
    int s;
    scanf("%d", &s);

    bellmanford(n, s);

    for (int k = 0; k <= n; k++)
    {
        for (int i = 1; i <= n; i++)
        {
            printf("\td[%d][%d] = ", k, i);
            if (d[k][i] == INFTY)
            {
                printf("INFTY");
            }
            else
            {
                printf("%d", d[k][i]);
            }   
        }
        puts("");
    }

    double mu = 1e30;

    for (int j = 1; j <= n; j++)
    {
        double nu = -1e30;
        for (int k = 0; k <= n - 1; k++)
        {
            nu = max(nu, 1. * (d[n][j] - d[k][j]) / (n - k));
        }

        mu = min(mu, nu);
    }

    printf("%0.6lf\n", mu);

    return 0;
}