// 백준 문제 : 히스토그램에서 가장 큰 직사각형

#include <iostream>
#include <stack>
#include <utility>
#include <algorithm>

using namespace std;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while(t != 0){
        int his[t];
        for(int i=0;i<t;i++){
            cin >> his[i];
        }

        stack<pair<int, int>> S; // {높이, 스택에 최초 저장된 높이의 인덱스}
        long long ans = 0;
        for(int i=0;i<t;i++) {
            int idx = i;
            // 스택의 top 요소가 현재 높이보다 크거나 같을 경우 pop하면서 넓이 계산을 계속 반복
            while(!S.empty() && S.top().first >= his[i]) { 
                ans = max(ans, 1LL * (i - S.top().second) * S.top().first);
                
                // 스택의 최초 인덱스를 기록
                idx = S.top().second;
                S.pop();
            }
            S.push({his[i],idx}); 
        }

        // 마지막 스택에 처리되지 않은 요소도 최대값 비교 
        while(!S.empty()){
            ans = max(ans, 1LL * (t - S.top().second) * S.top().first);
            S.pop();
        }

        cout << ans << "\n";

        cin >> t;
    }
}