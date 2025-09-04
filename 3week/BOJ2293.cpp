// 백준 문제 : 동전 1

#include <iostream>

using namespace std;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n,k;
    cin >> n >> k;

    int arr[n]; // 동전 값 배열
    for(int i=0;i<n;i++){
        cin >> arr[i];
    }

    int d[k+1]; // 0부터 k까지 해당 수를 만드려면 필요한 경우의 수 배열
    for(int i=1;i<=k;i++){
        d[i] = 0;
    }
    d[0] = 1;

    for(int i=0;i<n;i++){
        for(int j=arr[i];j<=k;j++){
            d[j] += d[j - arr[i]]; // j를 만들기 위한 경우의 수 += (j-해당 동전값)의 경우의 수
            // 이를 통해 d[j]에 d[j-arr[i]]에 동전 하나를 추가한 경우의 수를 종합 가능 
        }
    }
    cout << d[k] << "\n";

}