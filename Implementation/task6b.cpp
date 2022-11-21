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
 *   Task 6B of the programming project. Its time complexity is in order of m*n*k.
 *   Computes and return at most k transactions that are maximum for given stocks m and given days n.
 *
 *   @param  A vector<vector<int>> - a `m x n` stock where A[i][j] = Price of stock `i` at `jth` day 
 *   @param  m int                 - Number of Stocks
 *   @param  n int                 - Number of Days
 *   @param  k int                 - Max possible transactions
 *   @return   vector<transaction> - A vector of at most k transactions that yields max profit
 */
vector<transaction> Task6B(vector<vector<int>> &A, int m, int n, int k)
{
    // We will first create and initialize OPT array.
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

    // Iterate over OPT to build the solution
    // Iterate over row of OPT i.e. transactions k
    for(int i = 1; i < k+1; i++)
    {
        // For each day we will have a new diffSoFar vector that has m rows for each stock and each element is a tuple of {DiffSoFar, Buy date}
        vector<tuple<int, int>> diffSoFar(m, make_tuple(INT_MIN, 0));

        // Iterate over days i.e. n
        for(int j = 1; j < n; j++)
        {
            // If Transactions are greater than the days then OPT would just be the same as previous one.
            // You can not have more transactions than days i.e for 4 days max transactions(buy and sell) that can happen is 3.
            if(i > j)
            {
                OPT[i][j] = OPT[i-1][j];
                continue;
            }

            // Now our OPT has two choices
            // First is to pick profit from previous transaction i.e. no transactions on current day, we rest
            int maxProfit = get<0>(OPT[i][j-1]);

            // Second is that a transaction has occured on current day i.e. we sell on current day
            // But we need to figure out what transaction is that leads to max profit if we sell on current day.

            int stock = -1, buy = -1; // Varibles to keep track of buy index.
            for(int p = 0; p < m; p++)  // Iterate over m stocks
            {
                // current Difference stores the max profit that we will get if we buy on day l
                int diff = get<0>(OPT[i-1][j-1]) - A[p][j-1];   // Get current difference
                if(diff > get<0>(diffSoFar[p]))
                {
                    diffSoFar[p] = make_tuple(diff, j-1);       // Store the difference so we don't have to compute it over and over.
                }

                int profit = A[p][j] + get<0>(diffSoFar[p]);    // What is current profit if you sell today

                // If it is greater than the profit when we rest than update max profit
                if(maxProfit < profit)
                {
                    maxProfit = profit;
                    stock = p;
                    buy = get<1>(diffSoFar[p]);
                }
            }

            // Store the max profit and respective indices.
            OPT[i][j] = make_tuple(maxProfit, stock, buy);
        }
    }

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

    /**
      * This block of code was written for the comparison task.
      * It takes the file name as input and reads the input from that test case file.
      * It outputs the time taken by the code to run and the output of the test case.
      */

    // string name;
    // cout<<"Enter name: ";
    // cin>>name;
    // ifstream infile;
    // infile.open("../ComparisonTask/TestCasesPlot345/Task56/" + name + ".txt");
    // infile >> k >> m >> n;
    // cout<< "N : " << n << endl;
    // cout<< "M : " << m << endl;
    // cout<< "K : " << k << endl;
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
    // vector<transaction> transactions = Task6B(A, m, n, k);
    // t = clock() - t;
    // cout<<(float)t/CLOCKS_PER_SEC<<" seconds"<<endl;


    // Get the result of Task6A
    vector<transaction> transactions = Task6B(A, m, n, k);

    // Print the result
    for(auto t : transactions)
    {
        cout<<t.stock<<" "<<t.buy<<" "<<t.sell<<endl;
    }
    return 0;
}