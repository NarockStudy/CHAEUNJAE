// 백준 문제 : 줄 세우기

#include <iostream>
#include <algorithm>

using namespace std;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    int N;
    cin >> N;

    int dp[N+1];
    fill(dp,dp+N+1,0);

    int minusSt = 0;
    for(int i=0;i<N;i++){
        int studentNum;
        cin >> studentNum;
        dp[studentNum] = dp[studentNum-1] + 1; // 증가하는 학생 수를 기록
        minusSt = max(minusSt, dp[studentNum]);
    }

    cout << N - minusSt << "\n";
}