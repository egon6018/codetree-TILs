#include <iostream>
#include <queue>
#include <utility>
#include <tuple>
#define MAX_L 40
#define MAX_N 30
using namespace std;

// int L,N,Q;
// int board[MAX_L+1][MAX_L+1];
// int r[MAX_N+1], c[MAX_N+1], h[MAX_N+1], w[MAX_N+1], k[MAX_N+1];

// bool is_alive[MAX_N+1]; // 기사들이 살아있는지
// int power[MAX_N+1]; // 기사들의 체력

// int dr[4]={1,0,-1,0}; // 북,동,남,서
// int dc[4]={0,1,0,-1}; // 북,동,남,서
// bool inRange(int cur_r, int cur_c){
//     return (cur_r>0) && (cur_r<=L) && (cur_c>0) && (cur_c<=L);
// }

// void move_up(int i, int d){
//     int first_r, first_c; // 해당 기사의 첫번째 위치 찾기
//     for(int row=1;row<=L;row++){
//         for(int col=1;col<=L;col++){
//             if(board[row][col] == i){
//                 first_r = row;
//                 first_c = col;
//             }
//         }
//     }
// }

// void move_down(int i, int d){
//     int last_r, last_c; // 해당 기사의 마지막 칸의 위치 찾기
//     for(int row=1;row<=L;row++){
//         for(int col=1;col<=L;col++){
//             if(board[row][col] == i){
//                 last_r = row;
//                 last_c = col;
//             }
//         }
//     }
// }


// void input(){
//     cin >> L >> N >> Q;
//     for(int i=1;i<=L;i++){
//         for(int j=1;j<=L;j++){
//             cin >> board[i][j]; // 0:빈칸, 1:함정, 2:벽
//         }        
//     }

//     for(int i=1;i<=N;i++){        
//         cin >> r[i] >> c[i] >> h[i] >> w[i] >> k[i]; 
//         // 기사의 처음위치:(r,c), 세로:h, 가로:w, 초기체력:k

//         power[i] = k[i];


//         // board에 기사 표시를 기사 번호로 해야겠다.
//         // for(int row = r;row<r+h;row++){
//         //     for(int col=c;col<c+w;col++){
//         //         board[row][col] = i;
//         //     }
//         // }
//         // is_alive[i] = true;
//         // power[i] = k;
//     }

//     while(Q--){ // 명령
//         int i,d;
//         cin >> i >> d; // i번 기사에게 방향d로 한칸 이동해라
//         // 북,동,남,서 순서로
//         // 근데 이미 사라진 기사 번호가 주어질 수도 있음

//         move(i,d);
//     }
// }



int l, n, q;
int info[MAX_L+1][MAX_L+1];
int bef_k[MAX_N+1];
int r[MAX_N+1], c[MAX_N+1], h[MAX_N+1], w[MAX_N+1], k[MAX_N+1];
int nr[MAX_N+1], nc[MAX_N+1];
int dmg[MAX_N+1];
bool is_moved[MAX_N+1];

int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};

// 움직임을 시도해봅니다.
bool TryMovement(int idx, int dir) {
    // 초기화 작업입니다.
    for(int i = 1; i <= n; i++) {
        dmg[i] = 0;
        is_moved[i] = false;
        nr[i] = r[i];
        nc[i] = c[i];
    }

    queue<int> q;

    q.push(idx);
    is_moved[idx] = true;

    while(!q.empty()) {
        int x = q.front(); q.pop();

        nr[x] += dx[dir];
        nc[x] += dy[dir];

        // 경계를 벗어나는지 체크합니다.
        if(nr[x] < 1 || nc[x] < 1 || nr[x] + h[x] - 1 > l || nc[x] + w[x] - 1 > l)
            return false;

        // 대상 조각이 다른 조각이나 장애물과 충돌하는지 검사합니다.
        for(int i = nr[x]; i <= nr[x] + h[x] - 1; i++) {
            for(int j = nc[x]; j <= nc[x] + w[x] - 1; j++) {
                if(info[i][j] == 1) 
                    dmg[x]++;
                if(info[i][j] == 2)
                    return false;
            }
        }

        // 다른 조각과 충돌하는 경우, 해당 조각도 같이 이동합니다.
        for(int i = 1; i <= n; i++) {
            if(is_moved[i] || k[i] <= 0) 
                continue;
            if(r[i] > nr[x] + h[x] - 1 || nr[x] > r[i] + h[i] - 1) 
                continue;
            if(c[i] > nc[x] + w[x] - 1 || nc[x] > c[i] + w[i] - 1) 
                continue;

            is_moved[i] = true;
            q.push(i);
        }
    }

    dmg[idx] = 0;
    return true;
}

// 특정 조각을 지정된 방향으로 이동시키는 함수입니다.
void MovePiece(int idx, int dir) {
    if(k[idx] <= 0) 
        return;

    // 이동이 가능한 경우, 실제 위치와 체력을 업데이트합니다.
    if(TryMovement(idx, dir)) {
        for(int i = 1; i <= n; i++) {
            r[i] = nr[i];
            c[i] = nc[i];
            k[i] -= dmg[i];
        }
    }
}

void input(){
    cin >> l >> n >> q;
    for(int i = 1; i <= l; i++)
        for(int j = 1; j <= l; j++)
            cin >> info[i][j];
    for(int i = 1; i <= n; i++) {
        cin >> r[i] >> c[i] >> h[i] >> w[i] >> k[i];
        bef_k[i] = k[i];
    }
    for(int i = 1; i <= q; i++) {
        int idx, dir;
        cin >> idx >> dir;
        MovePiece(idx, dir);
    }
}

void pro(){
    long long ans = 0;
    for(int i = 1; i <= n; i++) {
        if(k[i] > 0) {
            ans += bef_k[i] - k[i];
        }
    }

    cout << ans;
}


int main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

    input();
    pro();

    return 0;
}