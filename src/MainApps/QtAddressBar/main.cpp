#include "MainWindow.h"
#include "NoFocusRectStyle.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    NoFocusRectStyle *style = new NoFocusRectStyle(app.style());
    app.setStyle(style);

    MainWindow w;
    w.show();

    return app.exec();
}
