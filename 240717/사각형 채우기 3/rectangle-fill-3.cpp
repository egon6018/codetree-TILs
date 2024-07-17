#include <iostream>
#define MAX_N 1000
#define MOD 1000000007
using namespace std;

int n;
long long dp[MAX_N + 1];

int main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

    cin >> n;

    // 초기 조건 설정
    dp[0] = 1;
    dp[1] = 2;

    // 2 x i에서 2 x 1인 사각형으로 채우는 경우의 수가 2 x 1이랑 1 x 1 2개 이렇게 2가지이기 때문에
    // => dp[i-1] * 2
    // 2 x i에서 1 x 2인 사각형으로 채우는 경우의 수가 1 x 1 2개 + 1 x 2, 1 x 2 + 1 x 1 2개, 1 x 2 2개 이렇게 3가지이기 때문에
    // => dp[i-2] * 3
    // 나머지들도 비슷한 방법으로 2가지씩이므로 점화식이 아래와 같이 세워진다

    // 점화식: dp[i] = dp[i - 1] * 2 + dp[i - 2] * 3 +
    //         (dp[i - 3] + dp[i - 4] + dp[i - 5] + ... dp[0]) * 2
    for(int i = 2; i <= n; i++) {
        dp[i] = (dp[i - 1] * 2 + dp[i - 2] * 3) % MOD;
        for(int j = i - 3; j >= 0; j--) {
            dp[i] = (dp[i] + dp[j] * 2) % MOD;
        }
    }
    cout << dp[n];
    
    return 0;
}