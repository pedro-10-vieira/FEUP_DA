#include <iostream>
#include "../data_structures/Graph.h"

using namespace std;
template <typename T>

/****************** toposort ********************/
/*
 * Performs a topological sorting of the vertices of a graph.
 * Returns a vector with the contents of the vertices by topological order.
 * If the graph has cycles, returns an empty vector.
 * Follows the algorithm described in theoretical classes.
 */
vector<T> topsort(const Graph<T>* g) {
    Graph<T> copy = *g;
    if (!isDAG(g)) {
        return vector<T>();
    }
    vector<T> res;
    queue<Vertex<T>*> v_queue;
    for (Vertex<T>* v : copy.getVertexSet()) {
        v->setIndegree(0);
    }
    for (Vertex<T>* v : copy.getVertexSet()) {
        for (Edge<T> edge : v->getAdj()) {
            Vertex<T>* e = edge.getDest();
            T value = e->getIndegree();
            e->setIndegree(value + 1);
        }
    }
    for (Vertex<T>* v : copy.getVertexSet()) {
        if (v->getIndegree() == 0) {
            v_queue.push(v);
        }
    }
    while (!v_queue.empty()) {
        auto u = v_queue.front();
        auto adj = u->getAdj();
        for (Edge<T> edge : adj) {
            auto v = edge.getDest();
//            copy.removeEdge(u->getInfo(), v->getInfo());
            auto value = v->getIndegree();
            v->setIndegree(value - 1);
            if (v->getIndegree() == 0) {
                v_queue.push(v);
            }
        }
        v_queue.pop();
        res.push_back(u->getInfo());
//        copy.removeVertex(u->getInfo());
    }
    return res;
}