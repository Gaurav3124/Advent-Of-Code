#include <bits/stdc++.h>
using namespace std;


// setting global variables
ifstream file("/Users/gauravshah/Developer/Advent of Code/2024/input_04.txt");

vector<pair<int, int>> movements = {
    {1, 0}, { -1, 0}, {0, 1}, {0, -1}, {1,1}, {-1,1}, {1,-1}, {-1,-1}
};

string s;
vector<vector<char>> v;
string word = "XMAS";
int m,n;

int part1(queue<pair<int,int>>& q){
    int total =0;
    int level =0;
    while(!q.empty()){
        int size = q.size();
        for(int i=0;i<size;i++){
            auto p = q.front();
            q.pop();
            for(auto movement : movements){
                int x = p.first;
				int y = p.second;
                //cout << ">> " << x << " " << y << endl;
                level = 1;
                x += movement.first;
                y += movement.second;
				for (;x >= 0 && x < m && y >= 0 && y < n && level<4;) {
					if (v[x][y] == word[level]) {
                        //cout << ">> >> " << x << " " << y << endl;
						level++;
                        x += movement.first;
                        y += movement.second;
					} else break;
				}
                if(level == 4) {
                    total +=1;
                }
			}
        }
    }
    return total;
}

int part2(queue<pair<int,int>>& q){
    int total=0;

    auto checkDiagonal1 = [&] (int x, int y) {
        unordered_map<char,int> mp{{'M',1}, {'S',1}};
        if(mp.find(v[x-1][y-1])!=mp.end()) {
            mp.erase(v[x-1][y-1]);
        }
        if(mp.find(v[x+1][y+1])!=mp.end()) {
            mp.erase(v[x+1][y+1]);
        }

        if(mp.size()==0) return true;
        return false;
    };

    auto checkDiagonal2 = [&] (int x, int y) {
        unordered_map<char,int> mp{{'M',1}, {'S',1}};
        if(mp.find(v[x+1][y-1])!=mp.end()) {
            mp.erase(v[x+1][y-1]);
        }
        if(mp.find(v[x-1][y+1])!=mp.end()) {
            mp.erase(v[x-1][y+1]);
        }

        if(mp.size()==0) return true;
        return false;
    };

    while(!q.empty()) {
        int size = q.size();
        for(int i=0;i<size;i++){
            auto p = q.front();
            q.pop();
            int x = p.first;
            int y = p.second;
            if(x>0 && x<n-1 && y>0 && y<m-1 && checkDiagonal1(x,y) && checkDiagonal2(x,y)){
                total += 1;
            }
        }
    }
    return total;
}

int main() {
    if(!file.is_open()) {
        cout << "error opening file";
        return 1;
    }

    while(getline(file,s)) {
        vector<char> c;
        stringstream ss(s);
        char ch;
        while(ss >> ch) {
            c.push_back(ch);
        }
        v.push_back(c);
    }

    m = v.size();
    n = v[0].size();
    queue<pair<int,int>> q;
    queue<pair<int,int>> q2;
    //cout << m << " " << n <<endl;

    for(int i = 0; i<m; i++){
        for(int j=0;j < n ;j++){
            if(v[i][j] == word[0]){
                q.push({i,j});
            }
            if(v[i][j] == 'A'){
                q2.push({i,j});
            }
        }
    }

    std::cout << "answer for part 1 : " << part1(q) << endl;
    std::cout << "answer for part 2 : " << part2(q2) << endl;
    return 1;
}