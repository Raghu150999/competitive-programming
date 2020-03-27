#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp>

// Remove GCC optimizer for codechef
#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;
using namespace __gnu_pbds;

#define IOS ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define pb push_back
#define endl "\n"
#define int long long
#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>

const int INF = 1e16;
const double PI = acos(-1);
const int N = 1e6 + 7;
int mod = 1e9 + 7;

struct Node
{
    int end;
    Node* child[26];
};

class Trie
{
public:
    Node *root;
    int ans = 0, k;
    Trie(int k)
    {
        root = createNode();
        this->k = k;
    }
    Node *createNode()
    {
        Node *ptr = new Node;
        ptr->end = 0;
        for(int i = 0; i < 26; i++)
            ptr->child[i] = NULL;
        return ptr;
    }
    void insert(string &str)
    {
        insertUtil(root, str, 0);
    }
    void insertUtil(Node *root, string &str, int pos)
    {
        if(pos == str.size())
        {
            root->end++;
            return;
        }
        int x = str[pos] - 'A';
        if(!root->child[x])
            root->child[x] = createNode();
        insertUtil(root->child[x], str, pos+1);
    }
    int find_ans(Node *root, int dis)
    {
        int sum = root->end;
        for(int i = 0; i < 26; i++)
        {
            if(root->child[i])
            {
                sum += find_ans(root->child[i], dis+1);
            }
        }
        if(sum >= k)
        {
            ans += dis * (sum / k);
            sum %= k;
        }
        return sum;
    }
    int compute_ans()
    {
        find_ans(root, 0);
        return ans;
    }
};

int32_t main()
{
    IOS;
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    
    int t;
    cin >> t;
    for(int s = 1; s <= t; s++)
    {
        int n, k;
        cin >> n >> k;
        Trie trie(k);
        for(int i = 1; i <= n; i++)
        {
            string str;
            cin >> str;
            trie.insert(str);
        }
        cout << "Case #" << s << ": " << trie.compute_ans() << endl;
    }
    return 0;
}