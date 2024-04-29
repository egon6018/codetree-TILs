#include <iostream>
#include <algorithm>
#include <tuple>
#include <queue>
#define MAX_N 10000
#define MAX_T 10000
using namespace std;

int n;
pair<int, int> bombs[MAX_N];
priority_queue<int> pq;

int getTime(int bomb_idx) { // 해당 폭탄의 시간
    int time_limit;
    tie(time_limit, ignore) = bombs[bomb_idx];
    return time_limit;
}

int getScore(int bomb_idx) { // 해당 폭탄 해체시 점수얻기
    int score;
    tie(ignore, score) = bombs[bomb_idx];
    return score;
}

int main() {  
    cin >> n;

    for(int i = 0; i < n; i++) {
        int score, time_limit;
        cin >> score >> time_limit;
        
        // 시간 기준으로 정렬
        bombs[i] = make_pair(time_limit, score);
    }
    
    sort(bombs, bombs + n); // 오름차순
        
    int bomb_idx = n - 1;
    int ans = 0;

    for(int t = MAX_T; t >= 1; t--) { 
        while(bomb_idx >= 0 && getTime(bomb_idx) >= t) {
            pq.push(getScore(bomb_idx));
            bomb_idx--;
        }

        // 현재 시간에 해체 가능한 폭탄이 존재한다면
        // 그 중 가장 높은 점수를 얻을 수 있는 폭탄을 해체
        if(!pq.empty()) {
            ans += pq.top();
            pq.pop();
        }
    }

    cout << ans;
    return 0;
}