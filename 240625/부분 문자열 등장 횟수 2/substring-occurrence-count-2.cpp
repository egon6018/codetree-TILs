#include <iostream>
#include <string>
#define MAX_len 100000
using namespace std;


int t_len, p_len;
int q;
string text, pattern;

// failure function
// f[i] : pattern에서 
//        [1, i]로 이루어진 문자열 중
//        접두사와 접미사가 일치하는 최장 길이 (단, 자기자신은 제외)
int f[MAX_len+1];

void kmp() {
    cin >> text >> q;

    while(q--){
        cin >> pattern;

        t_len = (int)text.size();
        p_len = (int)pattern.size();

        // 문자열1번부터 사용하기 위해
        text = "#"+text;
        pattern = "#"+pattern;

        // failure function
        f[0] = -1;
        for(int i=1;i<=p_len;i++){
            int j = f[i-1];

            while(j>=0 && pattern[j+1]!=pattern[i]){
                j = f[j];
            }

            f[i] = j+1;
        }

        // 문자열일치 확인
        int ans = 0;
        int j = 0;
        for(int i=1;i<=t_len;i++){
            while(j>=0 && pattern[j+1]!=text[i]){
                j = f[j];
            }

            j++;

            if(j == p_len){ // pattern 끝까지 왔으면
                ans++;
                j = f[j];
            }
        }

        cout << ans << "\n";
    }
}

int main(){
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

    kmp();

    return 0;
}