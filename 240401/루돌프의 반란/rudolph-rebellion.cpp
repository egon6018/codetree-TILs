#include <iostream>
#include <utility>
#include <tuple>
#define MAX_N 50
#define MAX_P 30
using namespace std;

int N,M,P,C,D; // N: 격자크기, M: 게임 턴 수, P: 산타 몇명

int board[MAX_N+1][MAX_N+1]; // 좌상단:(1,1)
pair<int,int> ru; // 루돌프 현재 위치<행,열>
pair<int,int> santa[MAX_P+1]; // 각 번호별 산타의 위치<행,열>
bool is_exist[MAX_P+1]; // 산타가 탈락했는가 안했는가
int scores[MAX_P+1]; // 각 산타가 얻은 최종 점수
int cant_move[MAX_P+1]; // 루돌프랑 충돌해서 산타가 얼마나 기절하는지

int dr[4]={-1,0,1,0}; // 북,동,남,서 순으로 우선순위
int dc[4]={0,1,0,-1}; // 북,동,남,서
bool inRange(int cur_r, int cur_c){
    return (cur_r>0) && (cur_r<=N) && (cur_c>0) && (cur_c<=N);
}

void input(){
    cin >> N >> M >> P >> C >> D;
    
    cin >> ru.first >> ru.second; // 루돌프 초기위치
    board[ru.first][ru.second] = -1; // 루돌프는 -1로 표시

    for(int i=0;i<P;i++){
        int p;
        cin >> p; // 산타번호
        cin >> santa[p].first >> santa[p].second; // 산타 초기위치
        board[santa[p].first][santa[p].second] = p; // 산타는 번호로 표시
        is_exist[p] = true; // 산타가 아직 존재한다는 뜻
    }
}

void pro(){
    for(int turn=1;turn<=M;turn++){
        // 루돌프가 한번 움직이고, 1번산타부터 P번산타까지 순서대로 움직인다.

        int nearest_r = 10000, nearest_c = 10000; // 가장 가까운 산타의 위치
        int nearest_santa = 0; // 가장 가까운 산타의 번호


        // 루돌프
        // 가장 가까운 산타가 2명이상이면 r좌표가 큰 산타한테, r이 동일하면 c좌표가 큰 산타한테
        // 1. 살아있는 산타 중 루돌프에 가장 가까운 산타 찾기
        for(int i=1;i<=P;i++){
            if(!is_exist[i]){ // 산타가 탈락되어있으면 pass
                continue;
            }

            pair<int, pair<int, int>> currentBest = { 
                (nearest_r - ru.first) * (nearest_r - ru.first) + (nearest_c - ru.second) * (nearest_c - ru.second), 
                {-nearest_r, -nearest_c}
            };
            pair<int, pair<int, int>> currentValue = {
                (santa[i].first - ru.first) * (santa[i].first - ru.first) + (santa[i].second - ru.second) * (santa[i].second - ru.second), 
                {-santa[i].first, -santa[i].second}
            };

            if(currentValue < currentBest){
                nearest_r = santa[i].first;
                nearest_c = santa[i].second;
                nearest_santa = i;
            }
        }

        // 2. 가장 가까운 산타의 방향으로 루돌프가 1칸 이동
        if(nearest_santa){ // 가장 가까운 산타를 찾았다면
            int temp_r, temp_c; // 루돌프가 이동할꺼니까 원래 있던 위치를 다시 0으로 원상복구 시키려고 위치저장
            tie(temp_r,temp_c) = ru;

            int ru_move_r = 0, ru_move_c = 0;
            if(nearest_r > ru.first) ru_move_r = 1;
            else if(nearest_r < ru.first) ru_move_r = -1;
            if(nearest_c > ru.second) ru_move_c = 1;
            else if(nearest_c < ru.second) ru_move_c = -1;

            ru.first += ru_move_r;
            ru.second += ru_move_c;
            board[temp_r][temp_c] = 0; // 원상복구(루돌프가 이제 이곳에 위치하지 않으니까 -1일 필요가 없음)

            // 산타와 루돌프가 같은 칸에 있으면 충돌!
            // 루돌프가 움직여서 충돌 -> 산타는 C만큼 점수 획득, 루돌프가 이동해온 방향으로 C칸만큼 밀려남
            if(ru.first == nearest_r && ru.second == nearest_c){
                int first_r = nearest_r + ru_move_r * C;
                int first_c = nearest_c + ru_move_c * C;

                int last_r = first_r;
                int last_c = first_c;

                // 산타는 루돌프와 충돌하고 나면 1번 턴 기절 
                cant_move[nearest_santa] = turn + 1;

                // 상호작용
                // 만약 착지하게 되는 칸에 다른 산타가 있다면 그 산타는 1칸 해당 방향으로 밀려난다. 만약 또 있다면 계속 연쇄적으로 반복
                while(inRange(last_r,last_c) && board[last_r][last_c]){
                    last_r += ru_move_r;
                    last_c += ru_move_c;
                }

                // 연쇄적으로 충돌이 일어나서 가장 마지막에 밀려난 산타부터 이동
                while(!(last_r==first_r && last_c==first_c)){
                    int before_r = last_r - ru_move_r;
                    int before_c = last_c - ru_move_c;

                    if(!inRange(before_r, before_c)) {
                        // 원래 위치부터 격자 벗어나있으면 말이 안되니까(?)
                        break;
                    }

                    int santa_num = board[before_r][before_c];

                    if(!inRange(last_r, last_c)){ // 이동했는데 격자 벗어나면 탈락
                        is_exist[santa_num] = false;
                    }
                    else{
                        // board판에 산타 번호 update
                        board[last_r][last_c] = board[before_r][before_c]; 
                        // 산타 위치 update
                        santa[santa_num] = {last_r, last_c};
                    }

                    last_r = before_r;
                    last_c = before_c;
                }

                // 루돌프와 충돌한 산타
                scores[nearest_santa] += C; // C점 획득
                santa[nearest_santa] = {first_r,first_c};
                if(inRange(first_r, first_c)){
                    board[first_r][first_c] = nearest_santa;
                }
                else{ // 격자를 벗어났으면 탈락
                    is_exist[nearest_santa] = false;
                }
            }
        }
        // board판에 루돌프 위치 update
        board[ru.first][ru.second] = -1; 

        // 산타 
        // 3. 각 산타들은 루돌프와 가장 가까운 방향으로 1칸 이동
        for(int i=1;i<=P;i++){
            if(!is_exist[i] || cant_move[i] >= turn){ 
                // 이미 탈락했거나 기절한 상태
                continue;
            }

            int minDist = (santa[i].first - ru.first) * (santa[i].first - ru.first) 
                            + (santa[i].second - ru.second) * (santa[i].second - ru.second);
            int moveDir = -1;

            for(int dir=0;dir<4;dir++){ // 북,동,남,서 순으로 이동
                int next_r = santa[i].first + dr[dir];
                int next_c = santa[i].second + dc[dir];

                if(!inRange(next_r, next_c) || board[next_r][next_c]){
                    // 격자를 벗어났거나, 그 자리에 다른 산타가 있으면 안됨
                    continue;
                }

                int dist = (next_r - ru.first) * (next_r - ru.first) 
                            + (next_c - ru.second) * (next_c - ru.second);

                if(dist < minDist){
                    minDist = dist;
                    moveDir = dir;
                }
            }

            if(moveDir != -1){ // 움직일 수 있는 방향이 있었다는 뜻
                int next_r = santa[i].first + dr[moveDir];
                int next_c = santa[i].second + dc[moveDir];

                // 산타의 이동으로 루돌프와 충돌했을때 
                if(next_r==ru.first && next_c==ru.second){
                    cant_move[i] = turn + 1; // 산타는 루돌프와 충돌했으니까 기절

                    // 산타는 자신이 이동해온 반대 방향으로 D칸 밀려난다
                    int santa_move_r = -dr[moveDir];
                    int santa_move_c = -dc[moveDir];
                    int first_r = next_r + santa_move_r * D;
                    int first_c = next_c + santa_move_r * D;
                    int last_r = first_r;
                    int last_c = first_c;

                    if(D == 1){ // ??
                        scores[i] += D;
                    }
                    else{ // 만약 이동한 위치에도 산타가 있다면, 연쇄적으로 충돌
                        while(inRange(last_r, last_c) && board[last_r][last_c]){
                            last_r += santa_move_r;
                            last_c += santa_move_c;
                        }
                        
                        // 연쇄적으로 충돌이 일어나서 가장 마지막에 밀려난 산타부터 이동
                        while(!(last_r==first_r && last_c==first_c)){
                            int before_r = last_r - santa_move_r;
                            int before_c = last_c - santa_move_c;

                            if(!inRange(before_r,before_c)) { 
                                // 원래 위치부터 격자 벗어나있으면 말이 안되니까(?)
                                break;
                            }

                            int santa_num = board[before_r][before_c];

                            if(!inRange(last_r,last_c)){ // 밀려났는데 격자 벗어나면 탈락
                                is_exist[santa_num] = false;
                            }
                            else{
                                // board판에 산타 번호 update
                                board[last_r][last_c] = board[before_r][before_c];
                                // 산타 위치 update
                                santa[santa_num] = {last_r,last_c};
                            }

                            last_r = before_r;
                            last_c = before_c;
                        }

                        // 산타의 이동으로 루돌프와 충돌하면 D점 획득
                        scores[i] += D;
                        // board판에 원래 있던 위치에는 산타 없어지니까 0으로 update
                        board[santa[i].first][santa[i].second] = 0;
                        // 산타 위치 update
                        santa[i] = {first_r, first_c};
                        if(inRange(first_r, first_c)){
                            board[first_r][first_c] = i;
                        }
                        else{ // 격자 벗어나면 해당 산타 탈락
                            is_exist[i] = false;
                        }
                    }
                }
                else{ // 루돌프랑 충돌 안했으면
                    // board판에 산타 번호 update. 이제 그 위치에 산타 없으니까 0으로
                    board[santa[i].first][santa[i].second] = 0;
                    // 산타 위치 update
                    santa[i] = {next_r,next_c};
                    // board의 새로운 위치에 산타 번호 update
                    board[next_r][next_c] = i;
                }
            }
        }

        // 매 턴 이후, 아직 탈락하지 않은 산타들에게는 1점씩 추가로 부여
        for(int i=1;i<=P;i++){
            if(is_exist[i]){
                scores[i]++;
            }
        }
    }

    // 각 산타가 얻은 최종 점수 출력
    for(int i=1;i<=P;i++){
        cout << scores[i] << " ";
    }
}

int main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

    input();
    pro();

    return 0;
}