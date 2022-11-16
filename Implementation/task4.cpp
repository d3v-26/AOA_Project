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

vector<transaction> chooseK(vector<transaction> T, vector<transaction> R, int index, int k)
{
    if(k < 0 || index > T.size()-1){
        return R;
    } 
    transaction current = T[index];
    
    bool isCompatible = true;
    for(auto r : R)
    {
        if( !((current.buy >= r.sell) || (current.sell <= r.buy)))
        {
            isCompatible = false;
            break;
        }
    }

    if(isCompatible)
    {
        vector<transaction> R1 = R;
        R1.push_back(current);
        
        vector<transaction> T1 = chooseK(T, R1, index+1, k-1);
        int T1profit = totalProfit(T1);

        vector<transaction> T2 = chooseK(T, R, index+1, k);
        int T2profit = totalProfit(T2);

        if(T1profit > T2profit)
        {  
            return T1;
        }
        else
        {
            return T2;
        }

    }
    else
    {
        return chooseK(T, R, index+1, k);
    }
}

vector<transaction> BruteForce(vector<vector<int>> A, int m, int n, int k)
{
    // First compute all possible transactions
    
    vector<transaction> transactions;
    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < n; j++)
        {
            for(int l = j + 1; l < n; l++)
            {
                int currentProfit = A[i][l] - A[i][j];
                transactions.push_back(transaction {i, currentProfit, j, l});                    
            }
        }
    }

    // Now pick atmost k transactions with max profit
    // i.e. try all nCk pairs
    vector<transaction> R;
    vector<transaction> result = chooseK(transactions, R, 0, k);

    sort(result.begin(), result.end(), compare);

    return result;
}

int main() {
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

    vector<transaction> result = BruteForce(A, m, n, k);

    for(auto r : result)
    {
        cout<<r.stock<<" "<<r.buy<<" "<<r.sell<<endl;
    }

    return 0;
}