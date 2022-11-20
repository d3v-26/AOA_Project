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
 *   Function to print the OPT of given problem
 *
 *   @param   OPT   tuple<int, int, int>**  - 2D Array whose each element is tuple
 *   @param   k     int                     - Number of transactions
 *   @param   n     int                     - Number of days
 */
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

/**
 *   DPMemoizationk is a function that recursively computes max profit of given m stock, n days and k transactions.
 *   This function populates OPT, and DifferenceSoFar arrays so that we can back track solution and still have complexity of Algorithm in order of m*n*k.
 *   This function returns a tuple that has max profit on its 0th tuple.
 *
 *   @param  A          vector<vector<int>>    - a `m x n` stock where A[i][j] = Price of stock `i` at `jth` day 
 *   @param  OPT        tuple<int, int, int>** - A 2D array of OPT where each element is a tuple of {Max profit, Stock and Buy date}
 *   @param  diffSoFar  tuple<int, int>**      - A 2D array of diffSoFar such that each element is a tuple of {Max difference till date, day index}
 *   @param  T          int                    - Current transaction index 
 *   @param  D          int                    - Current Day index
 *   @return            tuple<int, int, int>   - A tuple that has Max profit at its zeroth tuple.
 */
tuple<int, int, int>  DPMemoizationk(vector<vector<int>> A, tuple<int, int, int> **OPT, tuple<int,int> **diffSoFar, int T, int D)
{
    // If current OPT i.e. OPT[T][D] is already computed then return it.
    if(get<1>(OPT[T][D]) != -1) return OPT[T][D];

    // If T or D is in base case i.e. T = 0 or D = 0 init OPT with tuple of {0, 0, 0}
    if(T <= 0 || D <= 0)
    {
        OPT[T][D] = make_tuple(0, 0, 0);
        return OPT[T][D];
    }

    // If T > D i.e. Transactions greater than days we need to return previous transaction value which is obvious
    if(T > D)
    {
        OPT[T][D] =  DPMemoizationk(A, OPT, diffSoFar, T-1, D);
    }
    else
    {
        // Now we have two choices we rest or we sell
        // Max profit if we rest today
        tuple<int, int, int> maxIfNoTransaction =  DPMemoizationk(A, OPT, diffSoFar, T, D-1);
        
        // Max profit if we sell today
        int maxProfit = get<0>(maxIfNoTransaction);
        int stock = get<1>(maxIfNoTransaction);
        int buy = get<2>(maxIfNoTransaction);

        int maxIfTransaction = get<0>( DPMemoizationk(A, OPT, diffSoFar, T-1, D-1));

        // But we still need to figure out what day we buyed and what stock did we buy
        // DiffSoFar array takes care of this for us we just compute current difference and see if it max than previous, if yes then just update it
        // So we will iterate over the stocks and, each of which has a row in DiffSoFar, and see if we have max profit if we sell today.
        for(int i = 0; i < A.size(); i++)
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
        
        // Get the max profit if we rest or sell and store the result and their indices.
        OPT[T][D] = make_tuple(maxProfit, stock, buy);
    }

    // Return the computed max profit.
    return OPT[T][D];
}

/**
 *   Task 6A of the programming project. Its time complexity is in order of m*n*k.
 *   Computes and return at most k transactions that are maximum for given stocks m and given days n.
 *
 *   @param  A vector<vector<int>> - a `m x n` stock where A[i][j] = Price of stock `i` at `jth` day 
 *   @param  m int                 - Number of Stocks
 *   @param  n int                 - Number of Days
 *   @param  k int                 - Max possible transactions
 *   @return   vector<transaction> - A vector of at most k transactions that yields max profit
 */
vector<transaction> Task6A(vector<vector<int>> A, int m, int n, int k)
{
    // We will first create and initialize both OPT and DiffSoFar arrays.
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

    // Call to compute OPT and get max profit
    // We don't print the max profit that why we have not used it here.
    DPMemoizationk(A, OPT, diffSoFar, k, n-1);
    
    //print(OPT, k+1, n);
    
    // This vector stores our result
    vector<transaction> result;

    // Now we need to backtrack the OPT that we built.
    int i = k, j = n-1; // Variables to keep track of current indices.

    while(i != 0 || j != 0)                                         // While they are not zero
    {
        auto current = OPT[i][j];                                   // Get current max profit
        if(i == 0) j--;                                             
        else if(j == 0) i--;
        else if(get<0>(OPT[i][j]) == get<0>(OPT[i][j-1])) j--;      // if max profit is fetched from previous day update the indice of day
        else
        {
            // if a transaction has occured on current day, push that transaction into our result vector
            auto profit = get<0>(current);
            auto stock = get<1>(current);
            auto buy = get<2>(current);
            result.push_back(transaction {stock, A[stock][j] - A[stock][buy], buy, j});
            
            // update the indices i.e. day to the day on which we buy and transaction to one less transaction
            j = buy;
            i--;
        }
    }

    // As we are building our result vector in reverse order of days, we will reverse it to send transactions in order of their buy date
    reverse(result.begin(), result.end());
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

    // Get the result of Task6A
    vector<transaction> transactions = Task6A(A, m, n, k);

    // Print the result
    for(auto t : transactions)
    {
        cout<<t.stock<<" "<<t.buy<<" "<<t.sell<<endl;
    }
    return 0;
}