#include <iostream>
#include <cmath>
#include <algorithm>
#define MAX_n 20
using namespace std;

int n,m; // n x n, m:금 1개의 가격
int grid[MAX_n][MAX_n];

// 마름모 중심의 위치:(a,b), 임의의 위치:(c,d)라고 했을때
// |c-a| + |d-b| <= K이면 마름모에 포함! 


void input(){
    cin >> n >> m;

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin >> grid[i][j];
        }
    }
}

int getCost(int k){
    return k*k + (k+1)*(k+1);
}

int getGold(int row, int col, int k){
    int gold_cnt=0;

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(abs(row-i)+abs(col-j) <= k){
                gold_cnt += grid[i][j]; // 해당 칸에 금이 있으면
            }
        }
    }

    return gold_cnt;
}

void pro(){
    int max_gold = 0;

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            for(int k=0;k<=2*(n-1);k++){
                // n*n에서 우측하단(n-1*n-1)이 중심일때, 좌측상단(0,0)까지
                // 마름모 안에 들어오도록 하려면 k의 최대값은 2*(n-1)
                // 2*2->2, 3*3->4, 4*4->6 
                int gold_cnt = getGold(i,j,k);

                // 최대 금의 개수 구하기
                if(gold_cnt * m >= getCost(k)){
                    max_gold = max(max_gold, gold_cnt);
                }
            }
        }
    }

    cout << max_gold;
}

int main() {    
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

    input();
    pro();

    return 0;
}