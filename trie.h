/*
 * trie.h
 *
 * Declaration of the trie class.
 * 
 * Author: Westly Bouchard
 */

#ifndef _TRIE_H
#define _TRIE_H

#include <string>
#include <vector>

using namespace std;

class trie {
public:
    trie();
    ~trie();
    void insert(const string &s);
    bool contains(const string &s);
    bool is_prefix(const string &s);
    void extend(const string &prefix, vector<string> &result);

private:

    class node {
        public:
            bool isValidEndpoint;

            node* children[26];

            node();

            ~node();
    };

    node* root;
    
    void resolvePrefix(const string& prefix, node* searchRoot, vector<string>& result);
};

#endif
