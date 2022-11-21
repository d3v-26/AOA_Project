#include "tasks.h"

int totalProfit(vector<transaction> T)
{
    int profit = 0;             // Variable for keeping track of profit
    for(auto t : T)             // Iterating over all transactions and adding every profit to our profit variable
    {
        profit += t.profit;
    }
    return profit;              // Return the total profit.
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

void getMN(int *m, int *n)
{
    int m1, n1;
    cin >> m1;
    cin >> n1;
    *m = m1;
    *n = n1;
}

void getK(int *k)
{
    int k1;
    cin >> k1;
    *k = k1;
}

void getC(int *c)
{
    int c1;
    cin >> c1;
    *c = c1;
}

void getA(vector<vector<int>> &A, int m, int n)
{
    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < n; j++)
        {
            cin >> A[i][j];
        }
    }
}

void printSingleTransaction(transaction t)
{
    cout << t.stock << " " << t.buy << " " << t.sell << endl;
}

void printTransactions(vector<transaction> T)
{
    for(auto t : T)
    {
        printSingleTransaction(t);
    }
}

int main(int argv, char** argc)
{
    if(argv != 2)
    {
        cout << "Expected an argument" << endl;
    }
    else
    {
        string s = argc[1];
        int m, n, c, k;
        if(s == "1")
        {
            getMN(&m, &n);
            vector<vector<int>> A(m, vector<int>(n, 0));
            getA(A, m, n);
            transaction t = Task1(A, m, n);
            printSingleTransaction(t);
        }
        else if(s == "2")
        {
            getMN(&m, &n);
            vector<vector<int>> A(m, vector<int>(n, 0));
            getA(A, m, n);
            transaction t = Task2(A, m, n);
            printSingleTransaction(t);
        }
        else if(s == "3a")
        {
            getMN(&m, &n);
            vector<vector<int>> A(m, vector<int>(n, 0));
            getA(A, m, n);
            transaction t = Task3A(A, m, n);
            printSingleTransaction(t);
        }
        else if(s == "3b")
        {
            getMN(&m, &n);
            vector<vector<int>> A(m, vector<int>(n, 0));
            getA(A, m, n);
            transaction t = Task3B(A, m, n);
            printSingleTransaction(t);
        }
        else if(s == "4")
        {
            getK(&k);
            getMN(&m, &n);
            vector<vector<int>> A(m, vector<int>(n, 0));
            getA(A, m, n);
            vector<transaction> T = Task4(A, m, n, k);
            printTransactions(T);
        }
        else if(s == "5")
        {
            getK(&k);
            getMN(&m, &n);
            vector<vector<int>> A(m, vector<int>(n, 0));
            getA(A, m, n);
            vector<transaction> T = Task5(A, m, n, k);
            printTransactions(T);
        }
        else if(s == "6a")
        {
            getK(&k);
            getMN(&m, &n);
            vector<vector<int>> A(m, vector<int>(n, 0));
            getA(A, m, n);
            vector<transaction> T = Task6A(A, m, n, k);
            printTransactions(T);
        }
        else if(s == "6b")
        {
            getK(&k);
            getMN(&m, &n);
            vector<vector<int>> A(m, vector<int>(n, 0));
            getA(A, m, n);
            vector<transaction> T = Task6B(A, m, n, k);
            printTransactions(T);
        }
        else if(s == "7")
        {
            getC(&c);
            getMN(&m, &n);
            vector<vector<int>> A(m, vector<int>(n, 0));
            getA(A, m, n);
            vector<transaction> T = Task7(A, m, n, c);
            printTransactions(T);
        }
        else if(s == "8")
        {
            getC(&c);
            getMN(&m, &n);
            vector<vector<int>> A(m, vector<int>(n, 0));
            getA(A, m, n);
            vector<transaction> T = Task8(A, m, n, c);
            printTransactions(T);
        }
        else if(s == "9a")
        {
            getC(&c);
            getMN(&m, &n);
            vector<vector<int>> A(m, vector<int>(n, 0));
            getA(A, m, n);
            vector<transaction> T = Task9A(A, m, n, c);
            printTransactions(T);
        }
        else if(s == "9b")
        {
            getC(&c);
            getMN(&m, &n);
            vector<vector<int>> A(m, vector<int>(n, 0));
            getA(A, m, n);
            vector<transaction> T = Task9B(A, m, n, c);
            printTransactions(T);
        }
        else
        {
            cout << "Invalid Argument: "<< s<< endl;
        }
    }
    return 0;
}