#include <iostream>
#define MAX_N 1000
#define MOD 10007
using namespace std;

int n;
int dp[MAX_N + 1];

int main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

    cin >> n;

    // 초기 조건 설정: 2계단 혹은 3계단 단위로만 올라갈 수 있음
    dp[0] = 1;
    dp[1] = 0;
    dp[2] = 1; 
    dp[3] = 1;

    // 점화식: dp[i] = dp[i - 2] + dp[i - 3] (i>=4)
    // dp[i]: i번째 층에 도달하기 위한 서로 다른 가지 수
    // i번째에 도달하기 직전의 선택지는 2계단을 올라오거나 3계단을 올라오거나
    for(int i = 4; i <= n; i++) {
        dp[i] = (dp[i - 2] + dp[i - 3]) % MOD;
    }
    cout << dp[n];
    
    return 0;
}