// 백준 문제 : 별 찍기 - 11

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

vector<vector<char>> board(3*pow(2,10),vector<char>(6*pow(2,10),' ')); // 세로길이 3*2^10, 가로길이 6*2^10, 특정 인덱스 위치에 별을 기록

// n, 2^k, 시작 y좌표, 시작 x좌표
void saveStar(int n,int twoK,int y, int x){
    if(n == 3){
        for(int i=0;i<3;i++){
            for(int j=0;j<5;j++){
                if(i == 0 && (j == 0 || j == 1 || j == 3 || j == 4 || j == 5)){
                    
                } else if(i == 1 && (j == 0 || j == 2 || j == 4 || j == 5)) {

                } else {
                    board[y+i][x+j] = '*';
                }
            }
        }
        return;
    }

    // n을 2로 나눠가면서 삼각형 재귀적으로 찍기
    saveStar(n/2,twoK/2,y,x+3*twoK/2); // 삼각형 상단부
    saveStar(n/2,twoK/2,y+3*twoK/2,x); // 삼각형 좌측 하단부
    saveStar(n/2,twoK/2,y+3*twoK/2,x+3*twoK); // 삼각형 우측 하단부
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int N;
    cin >> N;

    int twoK= N / 3; // 2^k

    saveStar(N,twoK,0,0);

    for(int i=0;i<N;i++){
        for(int j=0;j<6*twoK;j++){
            cout << board[i][j];
        }
        cout << "\n";
    }
}