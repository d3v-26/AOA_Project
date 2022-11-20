#include <bits/stdc++.h>

using namespace std;

/**
 * Structure that describes a Transaction
 * 
 * @param stock  int - Index of the stock that corresponds to this Transaction.
 * @param profit int - Profit of the Transaction.
 * @param buy    int - Index of the `Day` that we `buy` the stock `stock`
 * @param sell   int - Index of the `Day` that we `sell` the stock `stock`
 */
struct transaction
{
    int stock, profit, buy, sell;
};

/**
 *   Function to Compare two given transactions.
 *   Returns True if t1 has buy date less than t2 otherwise false.
 *
 *   @param   t1          transaction  - A single transaction
 *   @param   t2          transaction  - A single transaction
 * 
 *   @returns             bool         - boolean variable answering if T1 comes before T2?
 */
bool compare(transaction t1, transaction t2)
{
    if(t1.buy <= t2.buy) return true;
    else return false;
}

/**
 *   Function to print all the given transactions
 *
 *   @param   T          vector<transaction>  - Vector containing any number of transactions
 */
void print(vector<transaction> T)
{
    for(auto t : T)
    {
        cout << t.stock << " " << t.profit << " " << t.buy << " " << t.sell << endl;
    }
}

void p(vector<vector<int>> A)
{
    for(int i = 0; i < A.size(); i++)
    {
        for(int j = 0; j < A[0].size(); j++)
        {
            cout << A[i][j] << " ";
        }
        cout << endl;
    }
}

/**
 *   Task 8 of the programming project. Its time complexity is in order of m*n^2.
 *   Computes and returns those transactions that yield max profit for given stocks m and given days n and given cooldown c.
 *
 *   @param  A vector<vector<int>> - a `m x n` stock where A[i][j] = Price of stock `i` at `jth` day 
 *   @param  m int                 - Number of Stocks
 *   @param  n int                 - Number of Days
 *   @param  c int                 - Cooldown
 *   @return   vector<transaction> - A vector of transactions that yields max profit
 */
vector<transaction> Task9B(vector<vector<int>> &A, int m, int n, int c)
{
    // Varibles to keep track of solution and buy index
    vector<vector<int>> DP(m, vector<int> (n, 0));
    vector<vector<int>> Buy(m, vector<int> (n, 0));
    vector<vector<int>> DiffSoFar(m, vector<int> (2, INT_MIN));

    // Iterate over n days 
    for(int j = 1; j < n; j++)
    {
        // Iterate over m stocks
        // So we will build solution like its going from top to bottom and then to right.
        for(int i = 0; i < m; i++)
        {
            int currentDiff = DP[m-1][max(0, j-c-2)] - A[i][j-1];
            if(currentDiff >= DiffSoFar[i][0])
            {
                DiffSoFar[i][0] = currentDiff;
                DiffSoFar[i][1] = j-1;
            }

            int current = DP[i][j];
            int previousDayProfit = DP[i][j-1];
            int previousStockProfit = i == 0 ? 0 : DP[i-1][j];
            int profitIfWeBuy = A[i][j] + DiffSoFar[i][0];

            DP[i][j] = max(current, max(previousDayProfit, max(previousStockProfit, profitIfWeBuy)));

            if(current != DP[i][j])
            {
                Buy[i][j] = DiffSoFar[i][1];
            }
        }
    }

    // This vector stores our result
    vector<transaction> result;

    // Let's backtrack
    // Start with max possible values of DP's indices
    int i = m-1, j = n-1;

    // While j is not 0, as we built solution top down i is allowed to be zero, i.e. when j hits 0 we will stop
    while(j > 0)
    {
        if(i == 0 && DP[i][j] == DP[i][j-1]) j--;       // If in base case & DP same as previous day update j
        else if(i > 0 && DP[i][j] == DP[i-1][j]) i--;   // If not in base case & DP same as stock above update i
        else if(DP[i][j] == DP[i][j-1]) j--;            // If DP same as previous day update j
        else
        {
            // Otherwise record the transaction
            result.push_back(transaction {i, A[i][j] - A[i][Buy[i][j]], Buy[i][j], j});

            // Update indices
            j = Buy[i][j] - c - 1;
            i = m - 1;
        }
    }

    // Sort the result in order of their buy date
    sort(result.begin(), result.end(), compare);
    p(DP);
    cout<<endl;
    p(Buy);
    // Return the result
    return result;
}

// Main method
int main()
{
    /**
     *  Get the inputs `k`, `m`, `n` & `A` which are specified as below:
     *  k    - Line 1 consists of one integer k.
     *  m, n - Line 2 consists of two integers m & n separated by one space character.
     *  A    - Next m lines each contains of n integers (prices for n days) separated by a single space.
     */
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

    // Get the result of Task8
    vector<transaction> transactions = Task9B(A, m, n, c);

    // Print the result
    for(auto t : transactions)
    {
        cout<<t.stock<<" "<<t.buy<<" "<<t.sell<<endl;
    }
    return 0;
}

