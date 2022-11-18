#include <bits/stdc++.h>

using namespace std;

struct transaction
{
    int stock, profit, buy, sell;
};

int totalProfit(vector<transaction> T)
{
    int profit = 0;
    for(auto t : T)
    {
        profit += t.profit;
    }
    return profit;
}

void print(vector<transaction> T)
{
    for(auto t : T)
    {
        cout << t.stock << " " << t.profit << " " << t.buy << " " << t.sell << endl;
    }
}

bool compare(transaction t1, transaction t2)
{
    if(t1.buy <= t2.buy) return true;
    else return false;
}

vector<transaction> BruteForce2n(vector<vector<int>> A, int current, int S, int D, bool buy, int c)
{
    if(current >= A[0].size())
    {
        vector<transaction> T;
        return T;
    }

    if(buy)
    {
        // Here we can buy stock
        // What is the max profit if we don't buy a stock on current day?
        vector<transaction> T = BruteForce2n(A, current+1, -1, -1, buy, c);

        // What is the max profit if we do buy a stock on current day?
        vector<transaction> C;   
        for(int i = 0; i < A.size(); i++)
        {
            vector<transaction> T1 = BruteForce2n(A, current+1, i, current, false, c);
            if(totalProfit(C) < totalProfit(T1))
            {
                C = T1;
            }
        }

        // Return the max profit of the two
        if(totalProfit(C) > totalProfit(T)) return C;
        return T;
    }
    else
    {
        // Here a stock is already bought, so we have two choices either sell a stock or we don't
        // What is the max profit if we don't sell the bought stock on current day?
        vector<transaction> T = BruteForce2n(A, current+1, S, D, false, c);

        // What is the max profit if we do sell the bought stock on current day?
        vector<transaction> C = BruteForce2n(A, current+c+1, -1, -1, true, c);
        
        // A transaction has occured so we do need to add the said transaction to the result C
        C.push_back(transaction {S, A[S][current] - A[S][D], D, current});

        if(totalProfit(T) > totalProfit(C)) return T;
        return C;
    }
    
}

vector<transaction> Task7(vector<vector<int>> A, int m, int n, int c)
{
    vector<transaction> result = BruteForce2n(A, 0, -1, -1, true, c);
    sort(result.begin(), result.end(), compare);
    return result;
}

int main() {
    int m, n, c;
    cin >> c >> m >> n;

    vector<vector<int>> A(m, vector<int> (n, 0));
    for (int i = 0; i < m; i++) 
    {
        for (int j = 0; j < n; j++) 
        {
            cin >> A[i][j];
        }
    }

    vector<transaction> result = Task7(A, m, n, c);

    for(auto r : result)
    {
        cout<<r.stock<<" "<<r.buy<<" "<<r.sell<<endl;
    }

    return 0;
}