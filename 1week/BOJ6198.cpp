// 백준 문제 : 옥상 정원 꾸미기

#include <iostream>
#include <stack>

using namespace std;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    stack<int> s;

    int n;
    cin >> n;

    long long result = 0;
    for (int i = 0; i < n; i++)
    {
        int temp;
        cin >> temp; // 입력받으면서 진행

        while (!s.empty() && s.top() <= temp) 
        {
            // 현재 건물보다 높이가 크거나 같은 건물 temp가 나타나면
            // temp보다 큰 건물이 나타날때까지 
            // 보는 방향 역방향의 건물들 벤치마킹수 다 더하기
            s.pop();
            result += s.size();
            // cout << "result : " << result << "\n";
        }

        s.push(temp);
    }
    while (!s.empty())
    {
        // 마지막으로 더 높은 건물을 만나지 못한 건물들 벤치마킹수 다 더하기
        s.pop();
        result += s.size();
    }
    cout << result << "\n";
}