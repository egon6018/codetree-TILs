#include <iostream>
#include <string>
#define MAX_len 100000
using namespace std;

int t_len, p_len;
string text, pattern;

// failure function
// f[i] : pattern에서 인덱스1~i까지 접두사와 접미사가 일치하는 최장길이(자기자신 제외)
int f[MAX_len+1]; 


void input() {
    cin >> text >> pattern;

    t_len = (int)text.size();
    p_len = (int)pattern.size();
}

void kmp() {
    // 인덱스 1번부터 사용하기 위해
    text = "#"+text;
    pattern = "#"+pattern;

    // failure function 계산
    f[0]=-1;
    for(int i=1;i<=p_len;i++){

        int j = f[i-1];

        while(j>=0 && pattern[j+1]!=pattern[i]){
            j = f[j];
        }

        f[i] = j+1;
    }

    // 한 문자씩 비교하며 패턴문자열과 일치하는 순간을 찾는다
    int ans = 0;
    int j = 0;
    for(int i=1;i<=t_len;i++){

        while(j>=0 && pattern[j+1]!=text[i]){
            j = f[j];
        }

        j++;

        if(j == p_len){ // pattern의 끝까지 왔다는 것은 전부 일치했다는 뜻이니까
            ans++;
            j = f[j];
        }
    }

    cout << ans;
}

int main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

    input();
    kmp();

    return 0;
}