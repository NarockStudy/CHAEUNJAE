// 백준 문제 : 오큰수

#include <iostream>
#include <stack>
#include <utility> // pair

using namespace std;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    int a[n];
    for(int i=0;i<n;i++){
        cin >> a[i];
    }

    int ans[n];
    for(int i=0;i<n;i++){
        ans[i] = -1;
    }
    stack<pair<int,int> > s; // {값, 인덱스}
    
    for(int i=0;i<n;i++){

        // stack에 순서대로 {값, 인덱스}를 push하다가

        // 오큰수를 발견하면
        // stack을 pop하면서 저장해놓은 인덱스로 오큰수 기록을 반복
        // stack top에 있는 수가 오큰수보다 크거나 같으면 반복 종료 

        while(!s.empty() && s.top().first < a[i]){ 
            ans[s.top().second] = a[i];
            s.pop();
        }
        s.push({a[i],i});
    }

    for(const int& ansi:ans){
        cout << ansi << " ";
    }
    cout << "\n";
}