#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
    ifstream file("input_01.txt");
    if (!file.is_open()) {cout << "problem with opening file." << endl; return -1;}
    else cout << "filed open successfully" << endl;

    vector<long> list1;
    vector<long> list2;
    unordered_map<int,int> mp2;
    int a,b;
    while(file >> a >> b) {
        list1.push_back(a);
        list2.push_back(b);
        mp2[b]++;
    }
    
    if(list1.empty()) cout << "list1 empty";
    

    long ans=0;
    for(long i=0;i<list1.size();i++){
        if(mp2.find(list1[i])!= mp2.end()){
            ans += mp2[list1[i]] * list1[i];
        }
    }

    cout << ans;
}