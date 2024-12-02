#include <bits/stdc++.h>
using namespace std;


bool checkArraySafety(vector<int>& arr) {
    int n = arr.size();

    if(n==1) return true;
    if(n==2) return (abs(arr[0]-arr[1])<=3 && arr[0]!=arr[1]);
    

    for(int i = 1; i<n-1; i++){
        int l = arr[i]-arr[i-1];
        int r = arr[i+1]-arr[i];
        if(l!=0 && r!=0 && abs(l)<=3 && abs(r)<=3 && l*r>0) continue;
        else return false;
    }

    return true;
}

bool checkAlteredArraySafety(vector<int>& arr) {
    int n = arr.size();
    vector<int> subArr;
    for (size_t i = 0; i < n; ++i){
        subArr = vector<int>(arr.begin(), arr.begin()+i);
        subArr.insert(subArr.end(), arr.begin()+i+1, arr.end());
        if(checkArraySafety(subArr)) return true;
    }
    return false;
}


int main() {
    ifstream file("2024/input_02.txt");

    if(!file.is_open()) {
        cout << "error during opening file";
        return 1;
    }

    vector< vector<int> > arrays;
    string line;
    long part1Answer=0;
    long part2Answer=0;

    while(getline(file,line)){
        stringstream ss(line);
        int x;
        vector<int> arr;
        while(ss >> x){
            arr.push_back(x);
        }
        arrays.push_back(arr);
    }
    for(auto arr : arrays) {
        if(checkArraySafety(arr)) {
            part1Answer++;
            part2Answer++;
        } else if(checkAlteredArraySafety(arr)) {
            part2Answer++;
        }
        
    }
    file.close();
    cout << "part 1 Answer : " << part1Answer << endl;
    cout << "part 2 Answer : " << part2Answer << endl;

    return 0;
}