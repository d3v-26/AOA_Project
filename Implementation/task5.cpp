#include <bits/stdc++.h>

using namespace std;

struct transaction { int stock, buy, sell, profit; };
auto dp(vector<vector<int>> &A, int m, int n, int k)
{

    tuple<int, int, int> **OPT = new tuple<int, int, int> *[k+1];

    for(int i = 0; i < k+1; i++)
    {
        OPT[i] = new tuple<int, int, int>[n];
        OPT[i][0] = make_tuple(0, -1, -1);
        if(i == 0)
        {
            for(int j = 0; j < n; j++)
            {
                OPT[i][j] = make_tuple(0, -1, -1);
            }
        }
    }

    for(int i = 1; i < k+1; i++)
    {
        //vector<tuple<int, int>> diffSoFar(m, make_tuple(INT_MIN, 0));
        for(int j = 1; j < n; j++)
        {
            if(i > j)
            {
                OPT[i][j] = OPT[i-1][j];
                continue;
            }
            int maxProfit = get<0>(OPT[i][j-1]);
            int stock = -1;
            int buy = -1;
            for(int p = 0; p < m; p++)
            {   

                // int diff = get<0>(OPT[i-1][j-1]) - A[p][j-1];
                // if(diff > get<0>(diffSoFar[p]))
                // {
                //     diffSoFar[p] = make_tuple(diff, j-1);
                // }
                // int profit = A[p][j] + get<0>(diffSoFar[p]);

                // if(maxProfit < profit)
                // {
                //     maxProfit = profit;
                //     stock = p;
                //     buy = get<1>(diffSoFar[p]);
                // }

                int diffSoFar = INT_MIN, index = 0;
                for(int l = 0; l < j; l++)
                {
                    int currentDiff = get<0>(OPT[i-1][l]) - A[p][l];
                    if( currentDiff > diffSoFar)
                    {
                        diffSoFar = currentDiff;
                        index = l;
                    }
                }

                int profit = A[p][j] + diffSoFar;

                if(maxProfit < profit)
                {
                    maxProfit = profit;
                    stock = p;
                    buy = index;
                }
            }
            OPT[i][j] = make_tuple(maxProfit, stock, buy);
        }
    }

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

    vector<transaction> transactions = dp(A, m, n, k);

    for(auto t : transactions)
    {
        cout<<t.stock<<" "<<t.buy<<" "<<t.sell<<endl;
    }
    return 0;
}