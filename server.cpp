#include "server.h"

Server::Server(QVector<QVector<int> > g, QVector<int> vert)
{
    graph = g;
    vertices = vert;
}

Server::Server()
{

}

bool Server::checkGraphsEqual(QVector<QVector<int>> graph1, QVector<QVector<int>> graph2) {
    for (int i = 0; i < graph1.size(); i++) {
        for (int j = 0; j < graph1[i].size(); j++) {
            if (graph1[i][j] != graph2[i][j]) {
                return false;
            }
        }
    }
    return true;
}

bool Server::checkIsomorphism() {
    QVector<QVector<int>> helperGraph(isomorphicGraph.size());
    for (int i = 0; i < isomorphicGraph.size(); i++) {
        helperGraph[i] = isomorphicGraph[vertexMatching1[i + 1] - 1];
    }
    QVector<QVector<int>> decodedGraph(helperGraph);
    qDebug() << "Ответ:";
    for (int i = 0; i < helperGraph.size(); i++) {
        for (int j = 0; j < helperGraph[i].size(); j++) {
            decodedGraph[i][j] = vertexMatching2[decodedGraph[i][j]];
        }
    }
    if (checkGraphsEqual(graph, decodedGraph)) {
        qDebug() << "Графы изоморфны" << endl;
        return true;
    }
    else {
        return false;
    }
}

bool Server::checkCycle(QVector<int> cycle) {
    bool flag;
    QVector<int> verts;
    verts.push_back(cycle[0]);
    for (int i = 0, k = cycle[0]-1; i < cycle.size() - 1; i++) {
        flag = true;
        for (int j = 0; j < isomorphicGraph[k].size(); j++) {
            if (isomorphicGraph[k][j] == cycle[i + 1]) {
                if(verts.indexOf(cycle[i + 1]) == -1){
                    verts.push_back(cycle[i + 1]);
                }
                k = cycle[i + 1] - 1;
                flag = false;
                break;
            }
        }
        if (flag) {
            return false;
        }
    }
    qDebug() << "Ответ:";
    if (verts.size() == vertices.size()) {
        qDebug() << "Это действительно гамильтонов цикл" << endl;
        return true;
    }
    else {
        return false;
    }
}

void Server::setIsomorphicGraph(QVector<QVector<int> > graph) {
    isomorphicGraph = graph;
}

void Server::setVertexMatching1(QMap<int, int> map) {
    vertexMatching1 = map;
}

void Server::setVertexMatching2(QMap<int, int> map) {
    vertexMatching2 = map;
}
