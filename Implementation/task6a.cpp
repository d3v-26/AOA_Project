#include <bits/stdc++.h>

using namespace std;

struct transaction { int stock, buy, sell, profit; };
tuple<int, int, int> **OPT;

void print(tuple<int, int, int> **OPT, int k, int n)
{
    for(int i = 0; i < k; i++)
    {
        for(int j = 0; j < n; j++)
        {
            cout<< "OPT["<<i<<"]["<<j<<"] = " << get<0>(OPT[i][j]) << " " << get<1>(OPT[i][j]) << " " << get<2>(OPT[i][j]) << endl;
        }
    }
}

tuple<int, int, int> rec(vector<vector<int>> A, tuple<int, int, int> **OPT, tuple<int,int> **diffSoFar, int T, int D, int m)
{
    if(get<1>(OPT[T][D]) != -1) return OPT[T][D];
    if(T <= 0 || D <= 0)
    {
        OPT[T][D] = make_tuple(0, 0, 0);
        return OPT[T][D];
    }

    if(T > D)
    {
        OPT[T][D] = rec(A, OPT, diffSoFar, T-1, D, m);
    }
    else
    {
        tuple<int, int, int> maxIfNoTransaction = rec(A, OPT, diffSoFar, T, D-1, m);
        int maxProfit = get<0>(maxIfNoTransaction);
        int stock = get<1>(maxIfNoTransaction);
        int buy = get<2>(maxIfNoTransaction);

        int maxIfTransaction = get<0>(rec(A, OPT, diffSoFar, T-1, D-1, m));

        for(int i = 0; i < m; i++)
        {
            int diff = maxIfTransaction - A[i][D-1];
            if( diff > get<0>(diffSoFar[T][i]))
            {
                diffSoFar[T][i] = make_tuple(diff, D-1);
            }

            int profit = A[i][D] + get<0>(diffSoFar[T][i]);
            if(maxProfit < profit)
            {
                maxProfit = profit;
                stock = i;
                buy = get<1>(diffSoFar[T][i]);
            }
        }
        OPT[T][D] = make_tuple(maxProfit, stock, buy);
    }
    return OPT[T][D];
}
vector<transaction> dp(vector<vector<int>> A, int m, int n, int k)
{
    tuple<int, int, int> **OPT = new tuple<int, int, int> *[k+1];

    for(int i = 0; i < k+1; i++)
    {
        OPT[i] = new tuple<int, int, int>[n];
        for(int j = 0; j < n; j++)
        {
            OPT[i][j] = make_tuple(0, -1, -1);
        }
    }

    tuple<int, int> **diffSoFar = new tuple<int, int> *[k+1];
    for(int i = 0; i < k+1; i++)
    {
        diffSoFar[i] = new tuple<int, int> [m];
        for(int j = 0; j < m; j++)
        {
            diffSoFar[i][j] = make_tuple(INT_MIN, 0);
        }
    }

    rec(A, OPT, diffSoFar, k, n-1, m);
    //print(OPT, k+1, n);
    vector<transaction> result;

    int i = k;
    int j = n-1;

    while(i!=0 || j!=0)
    {
        auto current = OPT[i][j];
        if(i == 0) j--;
        else if(j == 0) i--;
        else if(get<0>(OPT[i][j]) == get<0>(OPT[i][j-1])) j--;
        else
        {
            auto profit = get<0>(current);
            auto stock = get<1>(current);
            auto buy = get<2>(current);
            result.push_back(transaction {stock, buy, j, A[stock][j] - A[stock][buy]});
            i--;
            j = buy;
        }
    }

    reverse(result.begin(), result.end());
    return result;
}

int main()
{
    int m, n, k;
    cin >> k >> m >> n;

    vector<vector<int>> A(m, vector<int> (n, 0));
    for (int i = 0; i < m; i++) 
    {
        for (int j = 0; j < n; j++) 
        {
            cin >> A[i][j];
        }
    }
    //dp(A, m, n, k);
    vector<transaction> transactions = dp(A, m, n, k);

    for(auto t : transactions)
    {
        cout<<t.stock<<" "<<t.buy<<" "<<t.sell<<endl;
    }
    return 0;
}