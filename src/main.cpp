#include <QApplication>
#include <QQmlApplicationEngine>

int main(int argc, char *argv[]) {
    // init application with graph engine
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/ui/main.qml"))); 

    return app.exec();
}