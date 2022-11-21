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
 *   @param   T vector<transaction>  - Vector containing any number of transactions
 */
void print(vector<transaction> T)
{
    for(auto t : T)
    {
        cout << t.stock << " " << t.profit << " " << t.buy << " " << t.sell << endl;
    }
}

/**
 *   DP Memoization MN implementation of ALG9A. Its time complexity is in order of m*n.
 *   Computes and returns those transactions that yield max profit for given stocks m and given days n and given cooldown c.
 *
 *   @param  A          vector<vector<int>>& - a `m x n` stock where A[i][j] = Price of stock `i` at `jth` day 
 *   @param  DiffSoFar  vector<vector<int>>& - a `m x n` where DiffSoFar[i][j] = Max profit if we buy at jth day for ith stock
 *   @param  DP         vector<vector<int>>& - a `m x n` Where DP is max profit of ith index & jth day
 *   @param  Buy        vector<vector<int>>& - a `m x n` Where Buy[i][j] = index of where we bought the stock that resulted in profit of DP[i][j]
 *   @param  M          int                  - Index of current Stock
 *   @param  N          int                  - Index of current Day
 *   @param  c          int                  - Cooldown
 *   @return            vector<transaction>  - A vector of transactions that yields max profit
 */
int DPMemoizationMN(vector<vector<int>> &A, vector<vector<int>> &DiffSoFar, vector<vector<int>> &DP, vector<vector<int>> &Buy, int M, int N, int c)
{
    // Get dimensions of A
    int m = A.size();
    int n = A[0].size();

    // Base case when Day is 0 we store 0 at DP[M][N]
    if(N <= 0)
    {
        DP[M][N] = 0;
        return DP[M][N];
    }

    // Again we have three choices
    int current = DP[M][N];

    // What is previous day's profit?
    int previousDayProfit = DP[M][N-1] == 0 ? DPMemoizationMN(A, DiffSoFar, DP, Buy, M, N-1, c) : DP[M][N-1];
    
    // What is previous stock's profit?
    int previousStockProfit = M <= 0 ? 0 : DP[M-1][N] == 0 ? DPMemoizationMN(A, DiffSoFar, DP, Buy, M-1, N, c) : DP[M-1][N];
    
    // What is profit if we buy? i.e. A[M][N] - A[M][N-1] + profit at (day - 1) - (c + 1) i.e. before cooldown
    int profitIfWeBuy = DP[m-1][max(0, N-c-2)] == 0 ? DPMemoizationMN(A, DiffSoFar, DP, Buy, m-1, max(0, N-c-2), c) : DP[m-1][max(0, N-c-2)];
    
    // Get current difference i.e. profit if we buy today
    int currentDiff = profitIfWeBuy - A[M][N-1];

    // If it is max that what is encountered store it and it's index.
    if(currentDiff >= DiffSoFar[M][0])
    {
        DiffSoFar[M][0] = currentDiff;
        DiffSoFar[M][1] = N-1;
    }

    // Our solution is max of all those cases.
    DP[M][N] = max(previousDayProfit, max(previousStockProfit, A[M][N] + DiffSoFar[M][0]));

    // If we did buy then store the index in Buy
    if(current != DP[M][N])
    {
        Buy[M][N] = DiffSoFar[M][1];
    }
    
    // Return the profit.
    return DP[M][N];
}

/**
 *   Task 9A of the programming project. Its time complexity is in order of m*n.
 *   Computes and returns those transactions that yield max profit for given stocks m and given days n and given cooldown c.
 *
 *   @param  A vector<vector<int>> - a `m x n` stock where A[i][j] = Price of stock `i` at `jth` day 
 *   @param  m int                 - Number of Stocks
 *   @param  n int                 - Number of Days
 *   @param  c int                 - Cooldown
 *   @return   vector<transaction> - A vector of transactions that yields max profit
 */
vector<transaction> Task9A(vector<vector<int>> &A, int m, int n, int c)
{
    // Varibles to keep track of solution and buy index
    vector<vector<int>> DP(m, vector<int> (n, 0));
    vector<vector<int>> DiffSoFar(m, vector<int> (2, INT_MIN));
    vector<vector<int>> Buy(m, vector<int> (n, 0));

    // Call the Algorithm that populates DP and Buy
    DPMemoizationMN(A, DiffSoFar, DP, Buy, m-1, n-1, c);
    
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

    //Return the result
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

    /**
      * This block of code was written for the comparison task.
      * It takes the file name as input and reads the input from that test case file.
      * It outputs the time taken by the code to run and the output of the test case.
      */

    // string name;
    // cout<<"Enter name: ";
    // cin>>name;
    // ifstream infile;
    // infile.open("../ComparisonTask/TestCasesPlot67/Task89/" + name + ".txt");
    // infile >> c >> m >> n;
    // cout<< "N : " << n << endl;
    // cout<< "M : " << m << endl;
    // cout<< "C : " << c << endl;
    // vector<vector<int>> A(m, vector<int> (n, 0));
    // for (int i = 0; i < m; i++) 
    // {
    //     for (int j = 0; j < n; j++) 
    //     {
    //         infile >> A[i][j];
    //     }
    // }
    // clock_t t;
    // t = clock();
    // vector<transaction> transactions = Task9A(A, m, n, c);
    // t = clock() - t;
    // cout<<(float)t/CLOCKS_PER_SEC<<" seconds"<<endl;

    // Get the result of Task9A
    vector<transaction> transactions = Task9A(A, m, n, c);

    // Print the result
    for(auto t : transactions)
    {
        cout<<t.stock<<" "<<t.buy<<" "<<t.sell<<endl;
    }
    return 0;
}
