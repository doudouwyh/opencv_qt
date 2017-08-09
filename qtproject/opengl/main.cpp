#include "mainwindow.h"
#include "nehewidget.h"
#include <QApplication>

#include <QMessageBox>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

      // 设置 OpenGL 信息
      // 注意：必须在show()之前设置信息
      QSurfaceFormat format;
      format.setRenderableType(QSurfaceFormat::OpenGL);
      format.setProfile(QSurfaceFormat::CoreProfile);
      format.setVersion(3,3);

      Window window;
      window.setFormat(format);
      window.resize(QSize(800, 600));
      window.show();

      return app.exec();
}
