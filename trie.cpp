/*
 * trie.cpp
 *
 * Method definitions for the trie class.
 *
 * Author: Westly Bouchard
 */

#include "trie.h"

trie::trie() {
    root = new node();
}

trie::~trie() {
    delete root;
}

trie::node::node() {
    isValidEndpoint = false;
    for (int i = 0; i < 26; i++) children[i] = nullptr;
}

trie::node::~node() {
    for (int i = 0; i < 26; i++) {
        if (children[i] != nullptr) delete children[i];
    }
}

void trie::resolvePrefix(const string& prefix, node* searchRoot, vector<string>& result) {
    // If root is marked as a valid terminator, then the prefix is itself a result
    if (searchRoot->isValidEndpoint) result.push_back(prefix);

    // Now have to recursively search the children
    for (int i = 0; i < 26; i++) {
        if (searchRoot->children[i] != nullptr) {
            string nonConstPrefix = prefix;
            nonConstPrefix.push_back(i + 97);
            resolvePrefix(nonConstPrefix, searchRoot->children[i], result);
        }
    }
}

void trie::extend(const string& prefix, vector<string>& result) {
    // Find node that represents the prefix
    size_t position = 0;
    node* prefixRoot = root;

    while (position < prefix.size()) {
        // If we don't find the entire prefix in the tree then we just return without doing anything else
        if (prefixRoot->children[prefix.at(position) - 97] == nullptr) return;
        prefixRoot = prefixRoot->children[prefix.at(position) - 97];
        position++;
    }

    // At this point we should have a node representing the start of where we want to search
    // I'm thinking now we do some recursive magic.
    resolvePrefix(prefix, prefixRoot, result);
}

void trie::insert(const string& s) {
    size_t position = 0;

    node* currentNode = root;

    while (position < s.size()) {
        if (currentNode->children[s.at(position) - 97] == nullptr) {
            currentNode->children[s.at(position) - 97] = new node();
        }

        currentNode = currentNode->children[s.at(position) - 97]; 
        position++;
    }

    currentNode->isValidEndpoint = true;
}

bool trie::contains(const string& s) {
    size_t position = 0;

    node* currentNode = root;

    while (position < s.size()) {
        if (currentNode->children[s.at(position) - 97] == nullptr) return false;
        currentNode = currentNode->children[s.at(position) - 97];
        position++;
    }

    if (currentNode->isValidEndpoint) return true;
    return false;
}

bool trie::is_prefix(const string& s) {
     size_t position = 0;

    node* currentNode = root;

    while (position < s.size()) {
        if (currentNode->children[s.at(position) - 97] == nullptr) return false;
        currentNode = currentNode->children[s.at(position) - 97];
        position++;
    }

    return true;
}
