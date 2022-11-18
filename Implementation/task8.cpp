#include <bits/stdc++.h>

using namespace std;

bool sortbysec(const tuple<int, int, int>& a, 
               const tuple<int, int, int>& b)
{
    return (get<1>(a) < get<1>(b));
}

void print( vector<tuple<int, int, int>>  OPT)
{
    sort(OPT.begin(), OPT.end(), sortbysec);
    for(int i = 0; i < OPT.size(); i++)
    {
       
        cout<< get<0>(OPT[i]) << " " <<get<1>(OPT[i]) << " " << get<2>(OPT[i]) << endl;
        
    }
    
}

void opt(vector<vector<int>> &A,  vector<vector<int>> &DP, vector<vector<int>> &buy, int M, int N, int C)
{
    for(int j=1; j<N; j++)
    {
        for(int i=0; i<M;i ++)
        {
            
            for(int k=0; k<j; k++)
            {
                if(i==0)
                {
                    int temp=DP[i][j];
                    DP[i][j]=max (  max(DP[i][j],DP[i][j-1]) , A[i][j]-A[i][k]+DP[M-1][max(0,k-C-1)] );
                    if(temp!=DP[i][j]){
                        buy[i][j]=k;
                    }
                }
                else{
                    int temp=DP[i][j];
                    DP[i][j]=max ( max ( max(DP[i][j],DP[i][j-1]), DP[i-1][j] ) , A[i][j]-A[i][k]+DP[M-1][max(0,k-C-1)] );
                    if(temp!=DP[i][j]){
                        buy[i][j]=k;
                    }
                }
            }
        }
    }
    
    
    vector<tuple<int, int, int>> result;

    int i=M-1,j=N-1;
    while(j > 0)
    {
        if(i==0 && DP[i][j]==DP[i][j-1])
        {
            j-=1;
        }
        else if(i>0 && DP[i][j]==DP[i-1][j])
        {
            i=i-1;
        }
        else if(DP[i][j]==DP[i][j-1])
        {
            j=j-1;
        }
        else{
            result.emplace_back(i, buy[i][j], j);
            j=buy[i][j]-C-1;
            i=M-1;
        }
    }
    print(result);
 
}


int main()
{
    int c, n, m; 
    cin >>c>> m >> n;
    
    vector<vector<int>> A(m, vector<int> (n, 0));
    vector<vector<int>> DP(m, vector<int> (n, 0));
    vector<vector<int>> Buy(m, vector<int> (n, 0));
    for (int i = 0; i < m; i++) 
    {
        for (int j = 0; j < n; j++) 
        {
            cin >> A[i][j];
        }
    }
    
    
    opt(A,DP,Buy,m,n,c);
    

    
}



