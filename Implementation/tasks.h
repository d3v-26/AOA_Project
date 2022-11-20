#ifndef TASKS_H
#define TASKS_H
#include <bits/stdc++.h>
struct transaction
{
    std::int stock, profit, buy, sell;
};
transaction Task1(vector<vector<int>> A, int m, int n);
transaction Task2(vector<vector<int>> A, int m, int n);
transaction Task3A(vector<vector<int>> A, int m, int n);
transaction Task3B(vector<vector<int>> A, int m, int n);
vector<transaction> Task4(vector<vector<int>> A, int m, int n, int k);
vector<transaction> Task5(vector<vector<int>> &A, int m, int n, int k);
vector<transaction> Task6A(vector<vector<int>> A, int m, int n, int k);
vector<transaction> Task6B(vector<vector<int>> &A, int m, int n, int k);
vector<transaction> Task7(vector<vector<int>> A, int m, int n, int c);
vector<transaction> Task8(vector<vector<int>> &A, int m, int n, int c);
vector<transaction> Task9A(vector<vector<int>> &A, int m, int n, int c);
vector<transaction> Task9B(vector<vector<int>> &A, int m, int n, int c);
#endif