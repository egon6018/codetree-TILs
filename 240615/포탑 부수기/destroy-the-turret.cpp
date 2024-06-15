#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <utility>
#include <tuple>
#define MAX_N 10
using namespace std;

int N,M,K; // NxM, K번의 턴
struct Turret{ // 포탑turret을 구조체로
    int row;
    int col;
    int recent;
    int power;
};

vector<Turret> live_turret; // 살아있는 포탑들 관리
int board[MAX_N][MAX_N]; // 처음 입력값에 있던 포탑들이 가진 힘
int recent_do[MAX_N][MAX_N]; // 언제(최근에) 공격에 참여했는지
int turn; // 진행하는 turn이 몇번째인지

bool is_attack[MAX_N][MAX_N]; // 공격과 무관했는지 안했는지 
bool visited[MAX_N][MAX_N]; // 레이저공격할때 방문했는가 안했는가

// 레이저공격할때 가장강한포탑으로 가기까지의 과정중에 있었던 애들한테도 공격하기 위해 역추적
int back_r[MAX_N][MAX_N]; 
int back_c[MAX_N][MAX_N];

// 우,하,좌,상의 우선순위대로 움직인다
int dr[4]={0,1,0,-1}; // 동,남,서,북
int dc[4]={1,0,-1,0}; // 동,남,서,북

// 포탄공격은 공격대상의 주위8개도 같이 피해를 입기 때문
// 1 2 3
// 4 5 6
// 7 8 9   라고 할때
// 5, 4, 6, 2, 1, 3, 8, 7, 9 순으로
int dr2[9] = {0, 0, 0, -1, -1, -1, 1, 1, 1};
int dc2[9] = {0, -1, 1, 0, -1, 1, 0, -1, 1};


void init() { // turn 진행하기 전, 전처리과정
    turn++;

    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){ 
            // 새로운 turn이니까
            visited[i][j] = false; // 방문기록 리셋
            is_attack[i][j] = false; // 공격진행과정에 참여했는가 리셋
        }
    }
}

bool cmp(Turret a, Turret b) { // 공격자 선정 -> 가장 약한 포탑
    if(a.power != b.power) { // 1. 공격력이 가장 낮은 포탑부터
        return a.power < b.power;
    }
    if(a.recent != b.recent) { // 2. 최근에 공격한 포탑부터
        return a.recent > b.recent;
    }
    if(a.row + a.col != b.row + b.col) { // 3. 행과 열의 합이 가장 큰 포탑부터
        return a.row + a.col > b.row + b.col;
    }
    return a.col > b.col; // 4. 열값이 가장 큰 포탑부터
}

void pickAttacker() { // 공격자 선정    
    sort(live_turret.begin(), live_turret.end(), cmp); // 가장 약한 포탑순으로 정렬

    Turret weak_turret = live_turret[0]; // 가장 약한 포탑 뽑기
    
    // 가장 약한 포탑의 위치
    int weak_r = weak_turret.row;
    int weak_c = weak_turret.col;

    // update
    board[weak_r][weak_c] += (N + M); // N+M만큼 공격력 증가시키기
    recent_do[weak_r][weak_c] = turn; // 몇번째 turn에 공격했는지
    weak_turret.power = board[weak_r][weak_c];
    weak_turret.recent = recent_do[weak_r][weak_c];
    is_attack[weak_r][weak_c] = true; // 공격진행과정에 참여하니까

    live_turret[0] = weak_turret; // update시킨거 반영
}

bool laserAttack() { // 레이저공격
    Turret weak_turret = live_turret[0]; // 공격자로 선정된 가장 약한 포탑
    int attacker_r = weak_turret.row;
    int attacker_c = weak_turret.col;
    int attacker_p = weak_turret.power;

    // 위에서 약한 포탑순으로 정렬해놨기 때문에 벡터 가장 뒤에 있는 애가 가장 강한 포탑임
    Turret strong_turret = live_turret[(int)live_turret.size()-1]; // 공격당하는 애로 선정된 가장 강한 포탑
    int attacked_r = strong_turret.row;
    int attacked_c = strong_turret.col;

    // 레이저공격은 공격자의 위치에서 공격대상포탑까지 최단경로로 공격 -> BFS
    queue<pair<int, int>> q;
    // 공격자의 위치부터시작
    visited[attacker_r][attacker_c] = true;
    q.push({attacker_r, attacker_c});

    bool can_attack = false; // 가장 강한 포탑에게 도달 가능한가

    while(!q.empty()) {
        int cur_r, cur_c;
        tie(cur_r, cur_c) = q.front(); 
        q.pop();

        if(cur_r == attacked_r && cur_c == attacked_c) { // 만약 가장 강한 포탑의 위치까지 왔으면
            can_attack = true; // 공격했다는 거니까 종료
            break;
        }
        
        for(int dir = 0; dir < 4; dir++) {
            // 만약 끝에 있는데 한번더 오른쪽으로 가야하는경우 (2,4)->(2,1)이 되어야하니까
            int next_r = (cur_r + dr[dir] + N) % N;
            int next_c = (cur_c + dc[dir] + M) % M;
            
            if(visited[next_r][next_c]){ // 이미 방문했으면 pass
                continue;
            }
        
            if(!board[next_r][next_c]){ // 부서진포탑이 있는 위치는 지날 수 없으니까
                continue;
            }

            visited[next_r][next_c] = true;
            back_r[next_r][next_c] = cur_r;
            back_c[next_r][next_c] = cur_c;
            q.push({next_r, next_c});
        }
    }
    
    if(can_attack) { // 가장 강한 포탑한테 도달했으면, 공격진행!        
        board[attacked_r][attacked_c] -= attacker_p; // 공격자의 공격력만큼 피해입힘
        if(board[attacked_r][attacked_c] < 0){ // 만약 공격을 당해서 뺐는데, 음수가 된다면
            board[attacked_r][attacked_c] = 0; // 0으로 고치기
        }
        is_attack[attacked_r][attacked_c] = true; // 공격진행과정에 참여했으니까        
        
        // 공격대상을 제외한 레이저경로에 있는 포탑들도 모두 공격을 받게 됨 (공격력/2 만큼)
        // -> 기존의 경로를 역추적
        int cur_r = back_r[attacked_r][attacked_c];
        int cur_c = back_c[attacked_r][attacked_c];

        while(!(cur_r == attacker_r && cur_c == attacker_c)) { // 다시 시작위치인 공격자위치로 오기전까지 진행
            board[cur_r][cur_c] -= (attacker_p / 2); // 공격력의 나누기2만큼 피해입힘
            if(board[cur_r][cur_c] < 0){ // 만약 공격을 당해서 뺐는데, 음수가 된다면 
                board[cur_r][cur_c] = 0; // 0으로 고치기
            }
            is_attack[cur_r][cur_c] = true; // 공격진행과정에 참여했으니까

            int next_r = back_r[cur_r][cur_c];
            int next_c = back_c[cur_r][cur_c];

            cur_r = next_r;
            cur_c = next_c;
        }
    }
    
    return can_attack; // 레이저공격 성공했냐 안했냐
}

void bombAttack() { // 포탄공격
    Turret weak_turret = live_turret[0]; // 공격자로 선정된 가장 약한 포탑
    int attacker_r = weak_turret.row;
    int attacker_c = weak_turret.col;
    int attacker_p = weak_turret.power;

    // 위에서 약한 포탑순으로 정렬해놨기 때문에 벡터 가장 뒤에 있는 애가 가장 강한 포탑임
    Turret strong_turret = live_turret[(int)live_turret.size()-1]; // 공격당하는 애로 선정된 가장 강한 포탑
    int attacked_r = strong_turret.row;
    int attacked_c = strong_turret.col;  
    
    for(int dir = 0; dir < 9; dir++) { 
        // 공격대상의 주위8개 방향에 있는 포탑들도 모두 탐색해야하니까 
        // 3*3 탐색
        int next_r = (attacked_r + dr2[dir] + N) % N;
        int next_c = (attacked_c + dc2[dir] + M) % M;

        if(next_r == attacker_r && next_c == attacker_c) { // 만약 공격자 자기자신이면 pass
            continue;
        }
        
        if(next_r == attacked_r && next_c == attacked_c) { // 공격대상인 가장 강한 포탑이면 power만큼 공격
            board[next_r][next_c] -= attacker_p;
            if(board[next_r][next_c] < 0) { // 만약 공격받아서 음수가 된다면
                board[next_r][next_c] = 0; // 0으로
            }
            is_attack[next_r][next_c] = true; // 공격 진행 과정에 참여했으니까
        }        
        else { // 그 외는 pow/2만큼 공격
            board[next_r][next_c] -= (attacker_p/2);
            if(board[next_r][next_c] < 0) {
                board[next_r][next_c] = 0;
            }
            is_attack[next_r][next_c] = true;
        }
    }
}

// 공격에 관여하지 않은 모든 살아있는 포탑의 힘을 1 증가시킵니다.
void others() {
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            if(is_attack[i][j]) { // 공격진행과정에 참여했다면 pass
                continue;
            }
            if(!board[i][j]) { // 공격력이 0이라면 pass
                continue;
            }
            board[i][j]++; // 공격력 1씩 증가
        }
    }
}

void input(){
    cin >> N >> M >> K;

    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            cin >> board[i][j];
        }
    }

    while(K--){        
        live_turret.clear(); // 일단 살아있는 포탑들만 넣어놓는 칸 초기화

        for(int i = 0; i < N; i++){
            for(int j = 0; j < M; j++){
                if(board[i][j]) { // 이미 공격력이 0이라면 그냥 pass
                    Turret new_turret; // 새로운 포탑

                    new_turret.row = i;
                    new_turret.col = j;
                    new_turret.recent = recent_do[i][j];
                    new_turret.power = board[i][j];

                    live_turret.push_back(new_turret); // 살아있다는 의미로 포탑들 넣어주기
                }
            }
        }
        
        if(live_turret.size() <= 1) { // 만약 살아있는 포탑이 1개이하라면
            break; // 그냥 바로 종료
        }
        
        init(); // 턴 진행하기 전에 전처리
    
        pickAttacker(); // 가장 약한 포탑을 뽑아서 공격자로 선정
        
        bool is_laser = laserAttack(); // 레이저공격        
        if(!is_laser){ // 레이저공격을 못했다면
            bombAttack(); // 포탄공격 
        }
        
        others(); // 공격진행과정에 참여하지 않은 애들 중 살아있는 포탑들은 공격력 1씩 증가
    }
}

void pro(){ // K번의 turn 종료후, 살아있는 포탑 중 가장 강한 포탑의 공격력이 ans    
    int ans=0;
    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            ans = max(ans, board[i][j]);
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