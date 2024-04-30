#include <iostream>
#include <algorithm>
#define MAX_n 100000
using namespace std;

int n,m;
int points[MAX_n];

// target보다 큰 최초의 위치
int upperbound(int target){
    int left=0, right=n-1;
    int min_idx = n;

    while(left<=right){
        int mid = (left+right)/2;
        if(points[mid] > target){
            right = mid - 1;
            min_idx = min(min_idx, mid);
        }
        else{
            left = mid + 1;
        }
    }

    return min_idx;
}

// target보다 같거나 큰 최초의 위치
int lowerbound(int target){
    int left=0, right=n-1;
    int min_idx = n;

    while(left<=right){
        int mid = (left+right)/2;
        if(points[mid] >= target){
            right = mid - 1;
            min_idx = min(min_idx,mid);
        }
        else{
            left = mid + 1;
        }
    }

    return min_idx;
}

void input(){
    cin >> n >> m;
    for(int i=0;i<n;i++){
        cin >> points[i];
    }    
}

void pro(){
    sort(points, points+n);

    for(int i=0;i<m;i++){
        int s,e; // 각 선분의 시작점과 끝점
        cin >> s >> e;

        int count = upperbound(e) - lowerbound(s);
        cout << count << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

    input();
    pro();

    return 0;
}