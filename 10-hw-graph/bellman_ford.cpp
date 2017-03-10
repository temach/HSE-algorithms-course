/**
 * Artem Abramov 151
 * */
#include "bellman_ford.h"
#include <stdexcept>
#include <algorithm>

void BellmanFord::initialize(int** array, int n, int m, int startV) {
    if (this->initialized) {
        delete[] this->path;
        this->graph.clear();
    }
    for (int i=0; i < n; i++) {
        // each node's data
        this->graph.push_back(Edge{array[i][0]-1, array[i][1]-1, array[i][2]});
    }
    this->numEdges = n;
    this->numVertexes = m;
    this->start = startV-1;
    this->initialized = true;
    this->isNegative = false;
    this->minCost = 0;
}

bool BellmanFord::isInitialized() {
    return this->initialized;
}

void BellmanFord::solve() {
    using namespace std;
    if (! this->initialized) {
        throw logic_error("Not initialised");
    }

    int infty = 1000000000;
    vector<int> d(numVertexes, infty);
    d[start] = 0;
    vector<int> p(numVertexes, -1);
    int check = -1;

    // find all distances
    // WATCH OUT WITH i <=
    int i;
    for (i=0; i <= numVertexes - 1; i++) {
        check = -1;
        for (const auto& e : graph) {
            if (d[e.from] < infty) {
                int calc_cost = d[e.from] + e.cost;
                if (d[e.to] > calc_cost)
                {
                    check = e.to;
                    p[e.to] = e.from;
                    d[e.to] = std::max(-infty, calc_cost);
                }
            }
        }
    }

    // Prepare to pass data to Positive/Negative solve functions
    // I really think that this is a very _very_ stupid idea.
    // BUT!!
    // The homework requirement is that I must call
    // either NegativeSolve() or PositiveSolve() and they need DATA to work,
    // and how else can I pass this data if we can not change the header?!?!
    path = new vector<int>[2]();
    path[0] = d;
    path[1] = p;
    minCost = check;

    if (check == -1) {
        solvePositive();
    } else {
        solveNegative();
    }

}

void BellmanFord::solveNegative() {
    using namespace std;

    vector<int> d = this->path[0];
    vector<int> p = this->path[1];
    int check = minCost;
    minCost = 0;
    delete[] path;

    // graph has negative cycle
    // change variables
    this->isNegative = true;
    // find the cycle path
    int y = check;
    for (int i=0; i < numVertexes; i++) {
        y = p[y];
    }
    this->path = new vector<int>[1]();
    // get ready to travel back
    vector<int> cur;
    for (int j=y; ; j=p[j]) {
        cur.push_back(j);
        // stop when you reached the beginning
        if (j == y && cur.size() > 1) break;
    }
    reverse(cur.begin(), cur.end());
    // calculate circular path cost
    minCost = 0;
    for (int i=0; i < static_cast<int>(cur.size() - 1); i++) {
        int from  = cur[i];
        int to = cur[i+1];
        // find the edge
        for (const auto& e : graph) {
            if (e.from == from && e.to == to) {
                // add cost
                minCost += e.cost;
            }
        }
    }
    // add the first circular path you found as the result
    this->path[0] = cur;
}

void BellmanFord::solvePositive() {
    using namespace std;

    int infty = 1000000000;
    vector<int> d = this->path[0];
    vector<int> p = this->path[1];
    minCost = 0;
    delete[] path;

    // no negative cycles reacheable from start node
    path = new vector<int>[numVertexes]();
    // build all paths
    for (int vert=0; vert < numVertexes; vert++) {
        vector<int> cur{};
        if (d[vert] < infty && d[vert] != 0) {
            // fill vector if we must
            for (int j=vert; j!=-1; j=p[j]) {
                cur.push_back(j);
            }
            reverse(cur.begin(), cur.end());
        }
        path[vert] = cur;
    }
}

int BellmanFord::getCost() {
    return minCost;
}

std::vector<int>* BellmanFord::getPath() {
    using namespace std;
    vector<int>* ret = new vector<int>[numVertexes]();
    if (isNegative) {
        vector<int> back(path[0].begin(), path[0].end()-1);
        for (auto& e : back) e++;
        ret[0] = back;
    }
    else {
        for (int i=0; i < numVertexes; i++) {
            vector<int> back(path[i]);
            for (auto& e : back) e++;
            ret[i] = back;
        }
    }
    return ret;
}

BellmanFord::~BellmanFord() {
    delete[] path;
}

