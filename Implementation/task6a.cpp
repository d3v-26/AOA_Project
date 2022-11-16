
#include <bits/stdc++.h>

using namespace std;

struct transaction { int stock, buy, sell, profit; };
vector<transaction> dp(vector<vector<int>> &A, int m, int n, int k)
{

    tuple<int, int, int> **OPT = new tuple<int, int, int> *[k+1];   //new three dimensional array => opt[k+1][][]

    for(int i = 0; i < k+1; i++)
    {
        OPT[i] = new tuple<int, int, int>[n];     // opt[k+1][n][]
        OPT[i][0] = make_tuple(0, -1, -1);       // opt[k+1][n][0] = [0,-1,-1]
        if(i == 0)
        {
            for(int j = 0; j < n; j++) 
            {
                OPT[i][j] = make_tuple(0, -1, -1);    //initalize the edges in matrix as zero 
            }
        }
    }

    for(int i = 1; i < k+1; i++)
    {
        vector<tuple<int, int>> diffSoFar(m, make_tuple(INT_MIN, 0));
        for(int j = 1; j < n; j++)
        {
            if(i > j)
            {
                OPT[i][j] = OPT[i-1][j];
                continue;
            }
            int maxProfit = get<0>(OPT[i][j-1]);
            int stock = -1;
            int buyDay = -1;
            for(int p = 0; p < m; p++)
            {
                                                               //here i = transactions, j = days, p= stocks
                int diff = get<0>(OPT[i-1][j-1]) - A[p][j-1];  //buying stock p at day j and doing i th transaction
                if(diff > get<0>(diffSoFar[p]))                //comparing profit for stock p with greatest profit earned by other stocks
                {
                    diffSoFar[p] = make_tuple(diff, j-1);        
                }
                int profit = A[p][j] + get<0>(diffSoFar[p]);   //calculating profit made by doing transaction to already calculated profit for stock p at day j 
                if(maxProfit < profit)
                {
                    maxProfit = profit;
                    stock = p;
                    buyDay = get<1>(diffSoFar[p]);
                }
            }
            OPT[i][j] = make_tuple(maxProfit, stock, buyDay);   // adding maximum profit earned by doing transaction with stock p on particular day
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
            auto buyDay = get<2>(current);
            result.push_back(transaction {stock, buyDay, j, A[stock][j] - A[stock][buyDay]});
            i--;
            j = buyDay;
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
