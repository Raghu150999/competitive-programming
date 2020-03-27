#include<bits/stdc++.h>

using namespace std;

struct TrieNode
{
    int word;
    TrieNode *next[26];
    TrieNode(int word = 0) : word(word)
    {
        for(int i = 0; i < 26; i++)
            next[i] = NULL;
    }
};

struct Trie
{
    TrieNode *root;
    Trie()
    {
        root = new TrieNode(); // Dummy node
    }
    void insert(string &s)
    {
        int len = s.size();
        insertUtil(root, s, len);
    }
    void insertUtil(TrieNode *root, string &s, int len)
    {
        if(len == 0)
            return;
        int x = s[len-1] - 'a';
        int word = len == 1 ? 1 : 0;
        if(!root->next[x])
            root->next[x] = new TrieNode();
        root->next[x]->word += word;
        insertUtil(root->next[x], s, len-1);
    }
    int getCount(string &s)
    {
        int len = s.size();
        int res = getCountUtil(root, s, len);
        return res;
    }
    int getCountUtil(TrieNode* root, string &s, int len)
    {
        if(root == NULL)
            return 0;
        if(len == 0)
            return root->word;
        int x = s[len-1] - 'a';
        return getCountUtil(root->next[x], s, len-1);
    }
};