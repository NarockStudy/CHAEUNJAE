// 백준 문제 : 별 찍기

#include <iostream>

using namespace std;

char board[6561][6561]; // 6561 = 3^8 = N의 최대값

// 너비, 시작 x좌표, 시작 y좌표
void printStar(int width,int x, int y){
    if(width == 3){
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                if(i == 1 && j == 1){

                } else {
                    board[x+i][y+j] = '*';
                }
            }
        }
    } else {
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                if(i == 1 && j == 1){
                    continue;
                } else {
                    printStar(width/3,x+i*width/3,y+j*width/3);
                }
            }
        }
    }
    
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    int N;
    cin >> N;

    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            board[i][j] = ' '; 
        }
    }

    printStar(N,0,0);

    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            cout << board[i][j];
        }
        cout << "\n";
    }
}