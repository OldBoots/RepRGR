#include "server.h"
#include "client.h"
#include <QCoreApplication>
#include <QDebug>
#include <QVector>
#include <QFile>
#include <QRandomGenerator>
#include <QTextCodec>

void vec_range(QVector<int> &vec, int num)
{
    for (int i = 0; i < vec.size(); i++) {
        vec[i] = num++;
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
#ifdef Q_OS_WIN32
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("IBM 866"));
#endif
    // Чтение из фала
    QFile file(":/file.txt");
    int firstVertex = 0;
    int secondVertex = 0;
    int cycleVertex = 0;

    int verticesCount = 0;
    int edgeCount = 0;

    QVector<int> cycle;
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug("Error open file");
    }
    QTextStream in(&file);
    QString line;
    // Читаем кол-во вершин и ребер
    verticesCount = in.readLine().toInt();
    edgeCount = in.readLine().toInt();
    qDebug() << verticesCount << edgeCount;
    QVector<QVector<int>> graph(verticesCount);
    QVector<int> vertices(verticesCount);
    // Переписываем граф
    for (int i = 0; i < edgeCount; i++) {
        firstVertex = in.readLine().toInt();
        secondVertex = in.readLine().toInt();
        graph[firstVertex - 1].push_back(secondVertex);
        graph[secondVertex - 1].push_back(firstVertex);
    }
    // Переписываем цикл
    while (!in.atEnd()) {
        cycleVertex = in.readLine().toInt();
        cycle.push_back(cycleVertex);
    }
    file.close();
    // Инициализируем вектор вершин
    vec_range(vertices, 1);
    // Выводим полученные данные
    qDebug() << "Исходный граф: " << endl;
    for (int i = 0; i < graph.size(); i++) {
        qDebug() << i << ")" << graph[i];
    }
    qDebug() << "Исходный гамильтонов цикл: " << endl;
    qDebug() << cycle;
    qDebug() << "_________________________________________________" << endl;

    Client client(cycle, vertices.size());
    client.setData(graph, vertices);
    Server serv(graph, vertices);
    for (int i = 0; i < 40; i++) {
        qDebug() << "Проверка №" << i + 1 << endl;

        client.generateIsomorphicGraph();
        serv.setIsomorphicGraph(client.getIsomorphicGraph());
        qDebug() << endl;
        qDebug() << "Вопрос: ";
        if (QRandomGenerator::global()->bounded(0, 2)) {
            qDebug() << "Предоставь цикл" << endl;
            if (!serv.checkCycle(client.getCycle())) {
                qDebug() << "Предоставлен не гамильтонов цикл" << endl;
                return -1;
            }
        }
        else {
            qDebug() << "Докажи изоморфность графа" << endl;
            serv.setVertexMatching1(client.getVertexMatching1());
            serv.setVertexMatching2(client.getVertexMatching2());
            if (!serv.checkIsomorphism()) {
                qDebug() << "Графы не изоморфны" << endl;
                return -1;
            }
        }
        qDebug() << "_________________________________________________" << endl;
    }

    qDebug() << "Все проверки пройдены успешно" << endl;

    return a.exec();
}
