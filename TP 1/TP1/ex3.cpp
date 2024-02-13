#include "../data_structures/Graph.h"
#include "stack"
using namespace std;

// Helper function to reverse the edges of a directed graph
template <typename T>
void aux_reverseGraphEdges(Graph<T>* g) {
    Graph<T> copy;
    for (Vertex<T>* v : g->getVertexSet()) {
        copy.addVertex(v->getInfo());
    }
    for (Vertex<T>* v : g->getVertexSet()) {
        for (Edge<T> e : v->getAdj()) {
            copy.addEdge(e.getDest()->getInfo(), v->getInfo(), e.getWeight());
        }
    }
    for (Vertex<T>* v : g->getVertexSet()) {
        for (Edge<T> e : v->getAdj()) {
            g->removeEdge(v->getInfo(), e.getDest()->getInfo());
        }
    }
    for (Vertex<T>* v : copy.getVertexSet()) {
        for (Edge<T> e : v->getAdj()) {
            g->addEdge(v->getInfo(), e.getDest()->getInfo(), e.getWeight());
        }
    }
}

// Kosaraju-Sharir algorithm to find strongly connected components
template <typename T>
vector<vector<T>> SCCkosaraju(Graph<T>* g)  {
    vector<vector<T>> sccs;
    stack<Vertex<T> *> vertexStack;
    for (auto v : g->getVertexSet()) {
        v->setVisited(false);
    }
    for (auto v : g->getVertexSet()) {
        if (!v->isVisited()) {
            firstDFSKosarajuSharir(v, &vertexStack);
        }
    }
    aux_reverseGraphEdges(g);
    for (auto v : g->getVertexSet()) {
        v->setVisited(false);
    }
    while (!vertexStack.empty()) {
        auto v = vertexStack.top();
        vertexStack.pop();
        if (!v->isVisited()) {
            vector<T> res;
            secondDFSKosarajuSharir(v, res);
            sccs.push_back(res);
        }
    }
    return sccs;
}

// First depth-first search in Kosaraju-Sharir algorithm
template <typename T>
void firstDFSKosarajuSharir(Vertex<T> *v, stack<Vertex <T> *> *vertexStack)  {
    v->setVisited(true);
    for (auto & e : v->getAdj()) {
        auto w = e.getDest();
        if (!w->isVisited()) {
            firstDFSKosarajuSharir(w, vertexStack);
        }
    }
    vertexStack->push(v);
}

// Second depth-first search in Kosaraju-Sharir algorithm
template <typename T>
void secondDFSKosarajuSharir(Vertex<T> *v, std::vector<int> & res)  {
    v->setVisited(true);
    res.push_back(v->getInfo());
    for (auto & e : v->getAdj()) {
        auto w = e.getDest();
        if (!w->isVisited()) {
            secondDFSKosarajuSharir(w, res);
        }
    }
}
