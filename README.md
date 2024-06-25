
# Buy and Sell Stocks


### Problem Statement
- We are given an array of price predictions for `m` stocks for `n` consecutive days. The price of stock `i` for day `j` is 
    ```bash
    A[i][j] for i = 1,...,m & j = 1,...,n.
    ```
- You are tasked with finding the maximum possible profit by buying and selling stocks. The predicted price on any day will always be a non-negative integer. You can hold only one share of one stock at a time. 
- You are allowed to buy a stock on the same day you sell another stock. More formally,

#### Problem 1
- Given a matrix `A` of `m × n` integers (non-negative) representing the predicted prices of m stocks for `n` days, find a single transaction (buy and sell) that gives maximum profit.

#### Problem 2
- Given a matrix `A` of `m × n` integers (non-negative) representing the predicted prices of m stocks for `n` days and an integer `k` (positive), find a sequence of at most `k` transactions that gives maximum profit. [Hint:- Try to solve for `k = 2` first and then expand that solution.]

#### Problem 3
- Given a matrix `A` of `m × n` integers (non-negative) representing the predicted prices of `m` stocks for `n` days and an integer `c` (positive), find the maximum profit with no restriction on number of transactions. However, you cannot buy any stock for `c` days after selling any stock. If you sell a stock at day `i`, you are not allowed to buy any stock until day `i+c+1`
## Tasks

#### Implement following algorithms


| Algorithm | Time Complexity     | Description                |
| :-------- | :------- | :------------------------- |
| `1` | `O(m*(n^2))` | **Required**. Brute Force for problem I |
| `2` | `O(m*n)` | **Required**. Greedy for problem I |
| `3` | `O(m*n)` | **Required**. Dynamic Programming for problem I |
| `4` | `O(m*(n^(2k)))` | **Required**. Brute Force for problem II |
| `5` | `O(m*(n^2)*k)` | **Required**. Dynamic Programming for problem II |
| `6` | `O(m*n*k)` | **Required**. Dynamic Programming for problem II |
| `7` | `O(m*(2^n))` | **Bonus**. Brute Force for problem III |
| `8` | `O(m*(n^2))` | **Bonus**. Dynamic Programming for problem III |
| `9` | `O(m*n)` | **Bonus**. Dynamic Programming for problem III |


### Problem and Solution
- Problem pdf: [`COT5405ProgrammingAssignmentFall2022.pdf`](https://github.com/d3v-26/AOA_Project/blob/main/COT5405ProgrammingAssignmentFall2022.pdf)
- Solution pdf: [`AOA_FINAL_REPORT.pdf`](https://github.com/d3v-26/AOA_Project/blob/main/AOA_FINAL_REPORT.pdf)

### Implementation

  1. Clone the repository:

  ```bash
    git clone https://github.com/d3v-26/AOA_Project.git
    cd AOA_Project
  ```

2. Find Design and input requirements of each problem here: [`AOA_FINAL_REPORT.pdf`](https://github.com/d3v-26/AOA_Project/blob/main/AOA_FINAL_REPORT.pdf)

3. Run the application using the following steps:

  ```bash
    cd ScriptForThunderServer
    g++ <FILE_TO_RUN>.cpp
  ```
4. Refer to `makefile` for any custom automated inputs.

### Authors

- [Dev Patel](https://www.github.com/d3v-26)
- [Dharmam Savani](https://github.com/s-dharmam)
- [Chintan Acharya](https://github.com/chintan-27)


