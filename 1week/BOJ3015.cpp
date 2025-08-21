// 백준 문제 : 오아시스 재결합

#include <iostream>
#include <stack>

using namespace std;

struct e {int h, cnt;}; // h : 높이, cnt : 자신과 키가 같은 사람 수

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n; 
    cin >> n;

    stack<e> S;
    long long ans=0;

    while (n--) {
        int x; 
        cin >> x;
        int cnt = 1;

        while(!S.empty() && S.top().h <= x) { // 해당 조건과 반복문으로 무조건 감소하는 순서의 stack 만들수 있음
            // x = 새로 추가된 i번째 사람
            // t = i-1번째 사람
            // 이라고 할때

            ans += S.top().cnt; // t보다 크거나 같은 사람
            if (S.top().h == x) cnt += S.top().cnt;
            S.pop();
        }

        if(!S.empty()) ans++; // x앞에 x보다 큰 사람

        S.push({x, cnt}); 
    }
    cout << ans << "\n";
}