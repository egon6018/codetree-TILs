#include <iostream>
#include <queue>
using namespace std;

#define MAX_N 30
#define MAX_L 40

int L, N, Q; // LXL, N명의 기사, Q개의 왕의명령
int info[MAX_L+1][MAX_L+1];
int bef_k[MAX_N+1]; // 기사가 가지고 있는 초기체력
int r[MAX_N+1], c[MAX_N+1], h[MAX_N+1], w[MAX_N+1], k[MAX_N+1]; // (r,c)부터 (r+h, c+w) 초기체력:k
int next_r[MAX_N+1], next_c[MAX_N+1]; // 다음위치
int damage[MAX_N+1]; // 데미지
bool is_moved[MAX_N+1];

int dr[4]={-1,0,1,0}; // 북,동,남,서
int dc[4]={0,1,0,-1}; // 북,동,남,서

bool canMove(int idx, int dir) { // 움직임 시도 
    for(int i = 1; i <= N; i++) { // 초기화
        damage[i] = 0;
        is_moved[i] = false;
        next_r[i] = r[i];
        next_c[i] = c[i];
    }

    queue<int> q;
    q.push(idx);
    is_moved[idx] = true;

    while(!q.empty()) {
        int cur_idx = q.front(); q.pop();

        // 기사를 현재위치+이동하려는방향으로 1칸이동
        next_r[cur_idx] += dr[dir]; 
        next_c[cur_idx] += dc[dir]; 
       
        if(next_r[cur_idx] < 1 || next_c[cur_idx] < 1 || next_r[cur_idx] + h[cur_idx] - 1 > L || next_c[cur_idx] + w[cur_idx] - 1 > L){
            // 격자를 벗어나면
            return false;
        }

        // 대상 조각이 다른 조각이나 장애물과 충돌하는지 검사합니다.
        for(int i = next_r[cur_idx]; i <= next_r[cur_idx] + h[cur_idx] - 1; i++) {
            for(int j = next_c[cur_idx]; j <= next_c[cur_idx] + w[cur_idx] - 1; j++) {
                // 0:빈칸, 1:함정, 2:벽
                if(info[i][j] == 1){ // 함정이면 데미지입음
                    damage[cur_idx]++;
                }
                if(info[i][j] == 2){ // 벽이면 못감
                    return false;
                }
            }
        }

        for(int i = 1; i <= N; i++) { // 다른 기사와 충돌하게되면, 같이 이동
            if(is_moved[i] || k[i] <= 0) {
                continue;
            }
            if(r[i] > next_r[cur_idx] + h[cur_idx] - 1 || next_r[cur_idx] > r[i] + h[i] - 1) {
                continue;
            }
            if(c[i] > next_c[cur_idx] + w[cur_idx] - 1 || next_c[cur_idx] > c[i] + w[i] - 1) {
                continue;
            }

            is_moved[i] = true;
            q.push(i);
        }
    }

    damage[idx] = 0;
    return true;
}

void MoveKnight(int idx, int dir) { // 기사 왕의 명령대로 이동
    if(k[idx] <= 0) { // 만약 idx번째 기사의 체력이 없다면
        return;
    }

    if(canMove(idx, dir)) { // 이동이 가능하면
        for(int i = 1; i <= N; i++) {
            // 위치 업데이트
            r[i] = next_r[i];
            c[i] = next_c[i];

            // 체력 업데이트
            k[i] -= damage[i];
        }
    }
}

void input(){
    cin >> L >> N >> Q;
    
    for(int i=1;i<=L;i++){
        for(int j=1;j<=L;j++){
            cin >> info[i][j]; 
        }
    }

    for(int i=1;i<=N;i++){
        cin >> r[i] >> c[i] >> h[i] >> w[i] >> k[i];         
        bef_k[i]=k[i]; // 기사 체력
    }

    while(Q--){
        int i, d;
        cin >> i >> d; // i번 기사가 방향 d로 가라
        MoveKnight(i,d);
    }
}

int main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);      
    input();

    // 결과를 계산하고 출력합니다.
    long long ans = 0;
    for(int i = 1; i <= N; i++) {        
        if(k[i]) { // 생존한 기사들이 받은 총 데미지
            ans += (bef_k[i] - k[i]);
        }
    }

    cout << ans;
    return 0;
}