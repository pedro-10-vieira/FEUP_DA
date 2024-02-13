#include <list>
#include "../data_structures/Graph.h"
#include "stack"
using namespace std;

template <typename T>
list<list<T>> sccTarjan( Graph<T>* g) {
    list<list<T>> res;
    stack<T> s;
    int i = 1;
    for (Vertex<T>* v : g->getVertexSet()) {
        v->setVisited(false);
        v->setNum(0);
        v->setLow(0);
    }
    for (Vertex<T>* v : g->getVertexSet()) {
        if (v->getNum() == 0) {
            dfs_scc(g, v, s, res, i);
        }
    }
    return res;
}

template <typename T>
void dfs_scc(Graph<T> *g, Vertex<T> *v, stack<T> &s, list<list<T>> &l, int &i){
    v->setLow(i);
    v->setNum(i);
    i++;
    s.push(v->getInfo());
    v->setVisited(true);
    for (auto e : v->getAdj()) {
        auto w = e.getDest();
        if (w->getNum() == 0) {
            dfs_scc(g, w, s, l, i);
            v->setLow(min(v->getLow(), w->getLow()));
        } else if (w->isVisited()) {
            v->setLow(min(v->getLow(), w->getNum()));
        }
    }
    if (v->getLow() == v->getNum()) {
        list<T> comp;
        T w;
        do {
            w = s.top();
            s.pop();
            comp.push_back(w);
        } while (w != v->getInfo());
        l.push_back(comp);
    }
}