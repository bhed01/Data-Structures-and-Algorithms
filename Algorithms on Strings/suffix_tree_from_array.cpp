/**
 * Program to implement an algorithm of constructing suffix tree form suffix
 * array.
 * @file suffix_tree_from_array.cpp
 * @author Bhed Kumar Kushwaha
 * @version 1.0
 **/
#include <algorithm>
#include <cstdio>
#include <map>
#include <string>
#include <utility>
#include <vector>

using std::make_pair;
using std::map;
using std::pair;
using std::string;
using std::vector;

struct Edge {
    int node;
    int start;
    int end;

    Edge(int node_, int start_, int end_)
        : node(node_), start(start_), end(end_) {}
    Edge(const Edge& e) : node(e.node), start(e.start), end(e.end) {}
};

/**
 * and LCP array lcp_array. Return the tree as a mapping from a node ID
 * to the vector of all outgoing edges of the corresponding node. The edges in
 * the vector must be sorted in the ascending order by the first character of
 * the edge label. Root must have node ID = 0, and all other node IDs must be
 * different nonnegative integers.
 * For example, if text = "ACACAA$", an edge with label "$" from root to a node
 * with ID 1 must be represented by Edge(1, 6, 7). This edge must be present in
 * the vector tree[0] (corresponding to the root node), and it should be the
 * first edge in the vector (because it has the smallest first character of all
 * edges outgoing from the root).
 **/
map<int, vector<Edge> > SuffixTreeFromSuffixArray(
    const vector<int>& suffix_array, const vector<int>& lcp_array,
    const string& text) {
    map<int, vector<Edge> > tree;
    int v{1};
    tree[0].push_back(Edge(v++, suffix_array[0], text.size()));
    int cur{};
    int depth{};
    for (int i{}; i < (int)suffix_array.size() - 1; i++) {
        int offset{};
        if (lcp_array[i] == 0) {
            cur   = 0;
            depth = 0;
            tree[cur].push_back(Edge(v++, suffix_array[i + 1], text.size()));
        } else {
            if (lcp_array[i] == depth) {
                tree[cur].push_back(
                    Edge(v++, suffix_array[i + 1] + depth, text.size()));
            } else {
                depth                = lcp_array[i];
                tree[cur].back().end = suffix_array[i] + depth;
                cur                  = tree[cur].back().node;
                tree[cur].push_back(
                    Edge(v++, suffix_array[i] + depth, text.size()));
                tree[cur].push_back(
                    Edge(v++, suffix_array[i + 1] + depth, text.size()));
            }
        }
    }
    return tree;
}

int main() {
    char buffer[200001];
    scanf("%s", buffer);
    string text = buffer;
    vector<int> suffix_array(text.length());
    for (int i = 0; i < text.length(); ++i) {
        scanf("%d", &suffix_array[i]);
    }
    vector<int> lcp_array(text.length() - 1);
    for (int i = 0; i + 1 < text.length(); ++i) {
        scanf("%d", &lcp_array[i]);
    }
    map<int, vector<Edge> > tree =
        SuffixTreeFromSuffixArray(suffix_array, lcp_array, text);
    printf("%s\n", buffer);

    vector<pair<int, int> > stack(1, make_pair(0, 0));
    while (!stack.empty()) {
        pair<int, int> p = stack.back();
        stack.pop_back();
        int node       = p.first;
        int edge_index = p.second;
        if (!tree.count(node)) {
            continue;
        }
        const vector<Edge>& edges = tree[node];
        if (edge_index + 1 < edges.size()) {
            stack.push_back(make_pair(node, edge_index + 1));
        }
        printf("%d %d\n", edges[edge_index].start, edges[edge_index].end);
        stack.push_back(make_pair(edges[edge_index].node, 0));
    }
    return 0;
}
