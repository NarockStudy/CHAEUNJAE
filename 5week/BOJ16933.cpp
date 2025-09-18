// 백준 문제 : 벽 부수고 이동하기 3

#include <iostream>
#include <string>
#include <queue>
#include <tuple>

using namespace std;

int dy[4] = {1,0,-1,0}; // 하, 우, 상, 좌 순서
int dx[4] = {0,1,0,-1};
int N,M,K;
int board[1000][1000];
int dist[1000][1000][11][2]; // y, x, 벽 부순 횟수, 낮/밤 / 최단거리 보관, visited 용도로도 쓰임
queue<tuple<int,int,int,bool>> qu; // 상단 항목과 요소 동일

int bfs(){
    dist[0][0][0][0] = 1;
    qu.push({0,0,0,0});
    while(!qu.empty()){
        auto cur = qu.front(); qu.pop();
        int y = get<0>(cur);
        int x = get<1>(cur);
        int brokenNumber = get<2>(cur);
        int isNight = get<3>(cur);
        int curDist = dist[y][x][brokenNumber][isNight];

        if(y == N-1 && x == M-1){
            return curDist;
        }

        for(int i=0;i<4;i++){
            int cy = y + dy[i];
            int cx = x + dx[i];
            if(cy < 0 || cy >= N || cx < 0 || cx >= M) continue;

            if(board[cy][cx] == 0){ // 빈 칸
                if(dist[cy][cx][brokenNumber][!isNight] == 0){
                    dist[cy][cx][brokenNumber][!isNight] = curDist+1;
                    qu.push({cy,cx,brokenNumber,!isNight});
                }
            } else if(board[cy][cx] == 1){ // 벽
                if(brokenNumber < K){
                    if(isNight == 0){ // 낮이면 바로 부숨
                        if(dist[cy][cx][brokenNumber+1][!isNight] == 0){
                            dist[cy][cx][brokenNumber+1][!isNight] = curDist+1;
                            qu.push({cy,cx,brokenNumber+1,!isNight});
                        }
                    } else { // 밤이면 제자리 대기
                        if(dist[y][x][brokenNumber][!isNight] == 0){
                            dist[y][x][brokenNumber][!isNight] = curDist+1;
                            qu.push({y,x,brokenNumber,!isNight});
                        }
                    }
                }
            }
        }
    }
    return -1;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> M >> K;
    for(int i=0;i<N;i++){
        string str;
        cin >> str;
        for(int j=0;j<M;j++){
            board[i][j] = str[j]-'0';
            for(int z=0;z<K+1;z++){
                dist[i][j][z][0] = 0;
                dist[i][j][z][1] = 0;
            }
        }
    }

    int result = bfs();
    if(result != 0){
        cout << result << endl;
    } else {
        cout << -1 << endl;
    }

}