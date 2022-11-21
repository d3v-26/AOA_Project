#include "tasks.h"

// using namespace std;

// /**
//  * Structure that describes a Transaction
//  * 
//  * @param stock  int - Index of the stock that corresponds to this Transaction.
//  * @param profit int - Profit of the Transaction.
//  * @param buy    int - Index of the `Day` that we `buy` the stock `stock`
//  * @param sell   int - Index of the `Day` that we `sell` the stock `stock`
//  */
// struct transaction
// {
//     int stock, profit, buy, sell;
// };

// /**
//  *   Function to Compare two given transactions.
//  *   Returns True if t1 has buy date less than t2 otherwise false.
//  *
//  *   @param   t1          transaction  - A single transaction
//  *   @param   t2          transaction  - A single transaction
//  * 
//  *   @returns             bool         - boolean variable answering if T1 comes before T2?
//  */
// bool compare(transaction t1, transaction t2)
// {
//     if(t1.buy <= t2.buy) return true;
//     else return false;
// }

// /**
//  *   Function to print all the given transactions
//  *
//  *   @param   T          vector<transaction>  - Vector containing any number of transactions
//  */
// void print(vector<transaction> T)
// {
//     for(auto t : T)
//     {
//         cout << t.stock << " " << t.profit << " " << t.buy << " " << t.sell << endl;
//     }
// }

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
vector<transaction> Task8(vector<vector<int>> &A, int m, int n, int c)
{
    // Varibles to keep track of solution and buy index
    vector<vector<int>> DP(m, vector<int> (n, 0));
    vector<vector<int>> Buy(m, vector<int> (n, 0));

    // Iterate over n days 
    for(int j = 1; j < n; j++)
    {
        // Iterate over m stocks
        // So we will build solution like its going from top to bottom and then to right.
        for(int i = 0; i < m; i++)
        {
            // Iterate till current day i.e. j
            for(int k = 0; k < j; k++)
            {
                // What is the current max profit?
                int current = DP[i][j];

                // For this we have three choices
                
                // If there is no transaction here than what is max profit if we rest
                int previousDayProfit = DP[i][j-1];

                // Also what is the previous stock's current max profit
                int previousStockProfit = i == 0 ? 0 : DP[i-1][j];

                // If we sell, calculate the profit for stock i i.e. price at day j - price at day k + max profit on day k-c-1 i.e. before cooldown
                int profitIfWeBuy = A[i][j] - A[i][k] + DP[m-1][max(0, k-c-1)];

                // Store the max of all three.
                DP[i][j] = max(current, max(previousDayProfit, max(previousStockProfit, profitIfWeBuy)));

                // Remember if we sell today store the Buy index for the stock
                if(current != DP[i][j])
                {
                    Buy[i][j] = k;
                }
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

    // Return the result
    return result;
}

// // Main method
// int main()
// {
//     /**
//      *  Get the inputs `k`, `m`, `n` & `A` which are specified as below:
//      *  k    - Line 1 consists of one integer k.
//      *  m, n - Line 2 consists of two integers m & n separated by one space character.
//      *  A    - Next m lines each contains of n integers (prices for n days) separated by a single space.
//      */
//     int m, n, c;
//     cin >> c >> m >> n;

//     vector<vector<int>> A(m, vector<int> (n, 0));
//     for (int i = 0; i < m; i++) 
//     {
//         for (int j = 0; j < n; j++) 
//         {
//             cin >> A[i][j];
//         }
//     }

//     // Get the result of Task8
//     vector<transaction> transactions = Task8(A, m, n, c);

//     // Print the result
//     for(auto t : transactions)
//     {
//         cout<<t.stock<<" "<<t.buy<<" "<<t.sell<<endl;
//     }
//     return 0;
// }
