#include "client.h"

Client::Client()
{

}

Client::Client(QVector<int> cycle, int n) {
    this->cycle = cycle;
    this->isomorphicGraph.resize(n);
}

void vec_shuffle(QVector<int> &vec){
    int index1, index2;
    for(int i = 0; i < qPow(vec.size(), 2); i++){
        index1 = QRandomGenerator::global()->bounded(vec.size());
        index2 = QRandomGenerator::global()->bounded(vec.size());
        qSwap(vec[index1], vec[index2]);
    }
}

void Client::generateIsomorphicGraph() {

    QVector<QVector<int>> helperGraph(graph);
    QVector<int> shuffledVertices(vertices);

    isomorphicCycle.resize(cycle.size());

    qDebug() << vertices;
    qDebug() << endl;
    qDebug() << "Перестановка вершин:";
    qDebug() << endl;
    vec_shuffle(shuffledVertices);

    for (int i = 0; i < shuffledVertices.size(); i++) {
        vertexMatching1[i + 1] = shuffledVertices[i];
        vertexMatching2[shuffledVertices[i]] = i + 1;
    }
    qDebug() << shuffledVertices;

    for (int i = 0; i < graph.size(); i++) {
        for (int j = 0; j < graph[i].size(); j++) {
            helperGraph[i][j] = vertexMatching1[helperGraph[i][j]];
        }
    }
    for (int i = 0; i < shuffledVertices.size(); i++) {
        isomorphicGraph[vertexMatching1[i + 1] - 1] = helperGraph[i];
    }
    qDebug() << endl;
    qDebug() << "Изоморфный граф: ";
    for (int i = 0; i < isomorphicGraph.size(); i++) {
            qDebug() << isomorphicGraph[i];
    }
    qDebug() << endl;
    qDebug() << "Изоморфный цикл: ";

    for (int i = 0; i < cycle.size(); i++) {
        isomorphicCycle[i] = vertexMatching1[cycle[i]];
    }
    qDebug() << isomorphicCycle;
}

void Client::setData(QVector<QVector<int> > g, QVector<int> vert)
{
    graph = g;
    vertices = vert;
}

QVector<int> Client::getCycle() {
    return isomorphicCycle;
}

QVector<QVector<int> > Client::getIsomorphicGraph() {
    return isomorphicGraph;
}

QMap<int, int> Client::getVertexMatching1() {
    return vertexMatching1;
}

QMap<int, int> Client::getVertexMatching2() {
    return vertexMatching2;
}
