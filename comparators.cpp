#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp>

// Remove GCC optimizer for codechef
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

using namespace std;
using namespace __gnu_pbds;

#define IOS ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define pb push_back
#define endl "\n"
#define int long long
#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>
#define mod 1000000007

const int INF = 5e18 + 8;
const double PI = acos(-1);

struct Comparator {

    int a;
    Comparator() {} // important empty constructor required
    Comparator(int a) : a(a) {}
    // Needed for sort() function
    bool operator<(const Comparator &c) {
        return a > c.a;
    }
    // Needed for priority_queue
    // const keywork is important
    bool operator()(const Comparator &c1, const Comparator &c2) {
        return c1.a > c2.a;
    }
};

class AutocompleteSystem {
public:
    
    struct Sentence {
        string sentence;
        int times;
        Sentence() {}
        Sentence(string sentence, int times) : sentence(sentence), times(times) {}
        bool operator()(const Sentence &s1, const Sentence &s2) {
            if (s1.times != s2.times) return s1.times > s2.times;
            return s1.sentence < s2.sentence;
        }      
    };
    
    set<Sentence, Sentence> order;
    map<string, Sentence> mapping;
    
    AutocompleteSystem(vector<string>& sentences, vector<int>& times) {
        for (int i = 0; i < sentences.size(); i++) {
            Sentence sentence(sentences[i], times[i]);
            mapping[sentences[i]] = sentence;
            order.insert(sentence);
        }    
    }
    
    string currSentence = "";
    vector<string> input(char c) {
        if (c == '#') {
            if (mapping.find(currSentence) == mapping.end()) {
                Sentence sentence(currSentence, 1);
                mapping[currSentence] = sentence;
                order.insert(sentence);
            } else {
                order.erase(mapping[currSentence]);
                mapping[currSentence].times++;
                order.insert(mapping[currSentence]);
            }
            currSentence = "";
            return vector<string>();
        }
        currSentence += c;
        int cnt = 3;
        vector<string> res;
        for (Sentence s : order) {
            if (cnt == 0) break;
            if (isPrefix(currSentence, s.sentence)) {
                cnt--;
                res.push_back(s.sentence);
            }
        }
        return res;
    }
    
    bool isPrefix(string &a, string &b) {
        if (a.size() > b.size()) return false;
        for (int i = 0; i < a.size(); i++) {
            if (a[i] != b[i]) return false;
        }
        return true;
    }
};

class PairComparator {
public:
    bool operator()(const pair<int, int> &p1, const pair<int, int> &p2) const {
        // Note '==' for comparison instead of '!='
        if (p1.second == p2.second) return p1.first < p1.first;
        return p1.second < p2.second;
    }
};

int32_t main()
{
    IOS;
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    priority_queue<Comparator, vector<Comparator>, Comparator> pq;

    pq.push(Comparator(1));
    pq.push(Comparator(3));
    pq.push(Comparator(2));
    
    while (!pq.empty()) {
        cout << pq.top().a << endl;
        pq.pop();
    }


    vector<Comparator> v;
    v.push_back(Comparator(1));
    v.push_back(Comparator(3));
    v.push_back(Comparator(2));
    sort(v.begin(), v.end());
    for (Comparator c : v) {
        cout << c.a << " ";
    }
    cout << endl;

    set<Comparator, Comparator> s;
    s.insert(Comparator(1));
    s.insert(Comparator(3));
    s.insert(Comparator(2));
    for (Comparator e : s) {
        cout << e.a << endl;
    }
    vector<string> sentences{"hey"};
    vector<int> times{3};
    for (string s : AutocompleteSystem(sentences, times).input('h')) {
        cout << s << endl;
    }

    
    priority_queue<pair<int, int>, vector<pair<int, int>>, PairComparator> pq2;
    pq2.push({1, 2});

    set<pair<int, int>, PairComparator> s2;
    s2.insert({1, 2});
    s2.insert({1, 2});
    s2.insert({2, 1});
    cout << s2.size() << endl;
    return 0;
}