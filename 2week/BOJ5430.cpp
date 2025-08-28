// 백준 문제 : AC

#include <iostream>
#include <deque>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

deque<int> split(const string& str, char delimiter) {
    deque<int> result;
    stringstream ss(str);
    string token;

    while (getline(ss, token, delimiter)) {
        result.push_back(stoi(token));
    }

    return result;
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);

    int T;
    cin >> T;

    for(int tt=0;tt<T;tt++){
        string p;
        cin >> p;

        int n;
        cin >> n;

        // 스플릿해서 원소 덱에 담기
        string arr;
        cin >> arr;
        arr.replace(arr.find('['),1,"");
        arr.replace(arr.find(']'),1,"");
        deque<int> numArr = split(arr,',');

        bool isRev = false; // 뒤집혀 있는지 여부
        bool isError = false;
        for(auto i:p){
            if(i == 'R'){
                // 실제로 뒤집지않고 뒤집힘 여부를 기록하고 있다가 마지막에만 적용
                isRev = !isRev;
            } else {
                if(numArr.empty()){
                    isError = true;
                    break;
                } else {
                    // 뒤집힘 여부에 따라 앞에서 pop, 뒤에서 pop할지 결정
                    if(!isRev) numArr.pop_front();
                    else numArr.pop_back();
                }
            }
        }

        if(isError == true){
            cout << "error\n";
            continue;
        }

        // 마지막 실제 뒤집기 적용 및 출력
        if(isRev) reverse(numArr.begin(),numArr.end());
        cout << "[";
        for(int i=0;i<numArr.size();i++){
            if(i == numArr.size()-1){
                cout << numArr[i];
            } else {
                cout << numArr[i] << ",";
            }
        }
        cout << "]\n";
    }
}