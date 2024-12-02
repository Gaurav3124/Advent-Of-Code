#include <bits/stdc++.h>
using namespace std;

int getTotalAbsoluteDiff(vector<int>& list1, vector<int>& list2) {
    sort(list1.begin(), list1.end());
    sort(list2.begin(), list2.end());

    long ans=0;
    for(long i=0;i<list1.size();i++){
        ans += abs(list1[i]-list2[i]);
    }
    return ans;
}

int getTotalAppearanceMultiple(vector<int>& list1, unordered_map<int,int>& mp2) {
    int ans=0;
    for(int i=0;i<list1.size();i++){
        if(mp2.find(list1[i])!= mp2.end()){
            ans += mp2[list1[i]] * list1[i];
        }
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
    ifstream file("2024/input_01.txt");
    if (!file.is_open()) {cout << "problem with opening file." << endl; return -1;}
    else cout << "filed open successfully" << endl;

    vector<int> list1;
    vector<int> list2;
    unordered_map<int,int> mp2;
    int a,b;
    while(file >> a >> b) {
        list1.push_back(a);
        list2.push_back(b);
        mp2[b]++;
    }
    
    if(list1.empty()) cout << "list1 empty";

    file.close();

    cout << "part 1 Answer : " << getTotalAbsoluteDiff(list1, list2) << endl;
    cout << "part 2 Answer : " << getTotalAppearanceMultiple(list1, mp2) << endl;
}