#include <iostream>
#define MAX_N 1000
#define MOD 10007
using namespace std;

int n;
int dp[MAX_N + 1];

int main() {    
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
    cin >> n;

    // 초기 조건 설정
    dp[0] = 1;
    dp[1] = 1;

    // 2 x i 크기의 사각형을 1 x 2, 2 x 1 크기의 사각형들로 채우는 방법
    // 2 x 1크기의 사각형의 경우 세로로 하나 붙이니까 가로는 i-1이 됨 
    // => 2 x (i-1)크기의 벽돌을 채우는 경우의 수와 같아짐 => dp[i-1]
    // 1 x 2크기의 사각형의 경우 가로로 2개 붙이니까 가로는 i-2가 됨 
    // => 2 x (i-2)크기의 벽돌을 채우는 경우의 수와 같아짐 => dp[i-2]

    // 점화식: dp[i] = dp[i - 1] + dp[i - 2] (i>=2)
    for(int i = 2; i <= n; i++) {
        dp[i] = (dp[i - 1] + dp[i - 2]) % MOD;
    }
    cout << dp[n];
    
    return 0;
}