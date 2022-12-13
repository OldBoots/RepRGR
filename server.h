#ifndef SERVER_H
#define SERVER_H

#include <QVector>
#include <QMap>
#include <QDebug>

class Server
{
public:
    Server(QVector<QVector<int>> g, QVector<int> vert);
    Server();
private:
    QMap<int, int> vertexMatching1;
    QMap<int, int> vertexMatching2;
    QVector<QVector<int>> graph;
    QVector<int> vertices;
public:
    QVector<QVector<int>> isomorphicGraph;
    bool checkGraphsEqual(QVector<QVector<int>> graph1, QVector<QVector<int>> graph2);
    bool checkIsomorphism();
    bool checkCycle(QVector<int> cycle);
    void setIsomorphicGraph(QVector<QVector<int>> graph);
    void setVertexMatching1(QMap<int, int> map);
    void setVertexMatching2(QMap<int, int> map);
};


#endif // SERVER_H
