#ifndef CLIENT_H
#define CLIENT_H

#include <QDebug>
#include <QVector>
#include <QMap>
#include <QtMath>
#include <QRandomGenerator>

class Client
{
public:
    Client();
    Client(QVector<int> cycle, int n);
private:
    QVector<QVector<int>> isomorphicGraph;
    QVector<int> isomorphicCycle;
    QMap<int, int> vertexMatching1;
    QMap<int, int> vertexMatching2;
    QVector<int> cycle;
    QVector<QVector<int>> graph;
    QVector<int> vertices;
public:
    void generateIsomorphicGraph();
    void setData(QVector<QVector<int>> g, QVector<int> vert);
    QVector<int> getCycle();
    QVector<QVector<int>> getIsomorphicGraph();
    QMap<int, int> getVertexMatching1();
    QMap<int, int> getVertexMatching2();
};

#endif // CLIENT_H
