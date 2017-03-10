/**
 * The current assessment is to implement algorithm to find all the strongly connected components in an oriented graph.
 * Chapter 22.5 of Cormen's Introduction to algorithms can be useful in the completing of this task.
 *
 * The only file that you need to upload for the assessment is SCCSolver.cpp - your
 * implementation for current header file.
 *
*/

#include "SCCSolver.h"
#include <stdexcept>

/* -----------------------------------------------------------------------------*/
/**
 *  @defgroup public_vertice Public functions of the Vertice class
 *  @{
 */

/**
 * A class representing a vertice of a graph used for Deep First Search (DFS)
 */

/**
 * Constructor
 * @param id an identifyer of the vertice
 */
Vertice::Vertice(int id) {
    Vertice::id = id;
}

/**
 * Set the original values to all the fields axcept id.
 * @post discovered_step == -1; finished_step == -1; passed == false;
 */
void Vertice::refresh() {
    Vertice::discovered_step = -1;
    Vertice::finished_step = -1;
    Vertice::passed = false;
}

/**
 * A static comparator that you will need for the implementation of SCCSolver.
 * Try to understand how it should work yourself
 * For more inpormation about c++ comparators see documentation for std::sort function
 * @param v1 first vertice
 * @param v2 second vertice
 */
bool Vertice::compare(Vertice* v1, Vertice* v2) {
    return v1->finished_step > v2->finished_step;
}

/** @} */ // end doxygroup

/* -----------------------------------------------------------------------------*/
/**
 *  @defgroup public_scc Public functions of the SCCSolver class.
 *  @{
 */


/**
 * Initialization method
 * Note that it can be called multiple times so don't forget about memory deallocation
 * Also, the pointer to the array shuold not be shared between the object of SCCSolver and the exterior program.
 * @param adjList an ARRAY of vectors: adjacency list of a graph
 * @param n number of vertives in graph
 * @post initialized == true; solved == false;
 */
void SCCSolver::initialize(std::vector<int>* adjList, int n) {
    using namespace std;
    if (adjacencyList != nullptr) {
        delete[] adjacencyList;
    }
    if (vertPool.size() > 0) {
        for (auto &vptr : vertPool) {
            delete vptr;
        }
        vertPool.clear();
    }
    nVertices = n;
    adjacencyList = new vector<int>[n];
    for (int i=0; i<n; i++) {
        // init new vector from old and save to array
        adjacencyList[i] = vector<int>(adjList[i]);
    }
    buildPool();
    solved = false;
    initialized = true;
}


/**
 * Main solving method.
 * @pre initialize == true;
 * @throws logic_error if called before initialization
 */
void SCCSolver::solve() {
    using namespace std;
    if (! initialized) {
        throw logic_error("Not initialised!");
    }
    // 1) DFS(G), to compute finish_step for all
    runDFS();
    // 2) G' = transpose G
    vector<int>* forward = adjacencyList;
    vector<int>* backward = reverseAdjacencyList(forward, nVertices);
    adjacencyList = backward;
    delete[] forward;
    // 3) DFS(G'), but consider vertices sorted by decreasing finish_step
    sortPool();
    result = runDFS();
    // 4) Read back results
    solved = true;
}

/**
 * Reverse all edges in the graph.
 * @param adjList initial adjacency list
 * @param n |V|
 * @return adjacency list of the reversed graph
 */
std::vector<int>* SCCSolver::reverseAdjacencyList(std::vector<int>* adjList, int n) {
    using namespace std;
    vector<int>* trans = new vector<int>[n];
    for (int vertex=0; vertex < n; vertex++) {
        // make empty for adjacent vertices
        trans[vertex] = vector<int>();
        // search within each and add to this one
        for (int vert = 0; vert < n; vert++) {
            // check if the adj_vertices contain this vertex
            for (const auto& adj_vertex : adjList[vert]) {
                if (adj_vertex == vertex) {
                    // if so then add it
                    trans[vertex].push_back(vert);
                }
            }
        }
    }
    return trans;
}


/**
 * receive a vector of vectors where each vectos is a set representing a strongly connected component
 * @return set of SCC's
 * @throws logic_error if called before solving
 */
std::vector<std::vector<int>> SCCSolver::getResult() {
    using namespace std;
    if (! solved) {
        throw logic_error("Not solved!");
    }
    return result;
}

/**
 * @return true if the problem for a given graph is solved; otherwise false
 */
bool SCCSolver::isSolved() {
    return solved;
}

/**
 * @return true if the object was initialized; otherwise false
 */
bool SCCSolver::isInitialized() {
    return initialized;
}

/**
 * Destructor, don't forget to free all the allocated memory.
 *
 * This function was defined in the header. Not sure if we should implement it or not.
 */
SCCSolver::~SCCSolver() {
    if (adjacencyList != nullptr) {
        delete[] adjacencyList;
    }
    if (vertPool.size() > 0) {
        for (auto &vptr : vertPool) {
            delete vptr;
        }
        vertPool.clear();
    }
}

/** @} */ // end doxygroup

/* -----------------------------------------------------------------------------*/
/**
 *  @defgroup private_scc Private functions of the SCCSolver class.
 *  @{
 */


/**
 * Fill the vertPool with all the vertices from a graph
 * This method has nothing to do with the edges of the graph.
 * @pre adjacencyList is initialized
 * @post vertPool is initialized
 */
void SCCSolver::buildPool() {
    using namespace std;
    // since vertPool is class member, it lives beyound this function
    vertPool = vector<Vertice*>();
    for (int i=0; i<nVertices; i++) {
        vertPool.push_back(new Vertice(i));
    }
}

/**
 * run DFS on the given graph using the adjacencyList and vertPool
 * @return a vector of vectors, where each of them represents a "tree" built during the DFS
 * @pre adjacencyList and vertPool are initialized
 * @post result is initialized
 */
std::vector<std::vector<int>> SCCSolver::runDFS() {
    using namespace std;
    refreshPool();
    int count=0;
    vector<vector<int>> forest;
    for (const auto& vptr : vertPool) {
        if (vptr->discovered_step<0) {
            vector<int> tree = vector<int>();
            // this vptr is the new root-node of the tree
            tree.push_back(vptr->id);
            // get other nodes of the tree
            DFSVisit(vptr, count, tree);
            forest.push_back(tree);
        }
    }
    return forest;
}

/**
 * recursive method to run DFS starting from the given vertice
 * @param v vertice
 * @param step step counter
 * @param tree a set of vertites of the tree tree of the given DFS
 * (eventually one of the elements of runDFS return value)
 * @pre adjacencyList and vertPool are initialized
 */
void SCCSolver::DFSVisit(Vertice* v, int& step, std::vector<int>& tree) {
    v->passed = true;
    v->discovered_step = ++step;
    for (const auto& adj_v_id : adjacencyList[v->id]) {
        // check adjacent vertices
        Vertice* vptr = getVertice(adj_v_id);
        if (vptr->discovered_step<0) {
            tree.push_back(adj_v_id);
            DFSVisit(vptr, step, tree);
        }
    }
    v->finished_step = ++step;
}

/**
 * sorts a vectorPool by v.finished_step
 * @pre vertPool is initialized
 * @post vectorPool is sorted
 */
void SCCSolver::sortPool() {
    // sort large at start, small at end
    for (int i=0; i<nVertices; i++) {
        for (int k=0; k<nVertices-1; k++) {
            if (! Vertice::compare(vertPool[k], vertPool[k+1])) {
                Vertice* tmp = vertPool[k];
                vertPool[k] = vertPool[k+1];
                vertPool[k+1] = tmp;
            }
        }
    }
}

/**
 * refresh each vertice in the vertPool
 * @pre vertPool is initialized
 * @post vectorPool is refreshed
 */
void SCCSolver::refreshPool() {
    for (const auto& vptr : vertPool) {
        vptr->refresh();
    }
}

/**
 * receive a pointer to a Vertice from vertPool with a given id
 * @param id
 * @return Vertice v: v.id == id
 * @pre vertPool is initialized
 */
Vertice* SCCSolver::getVertice(int id) {
    for (const auto& vptr : vertPool) {
        if (vptr->id == id) return vptr;
    }
    return nullptr;
}


/** @} */ // end doxygroup

