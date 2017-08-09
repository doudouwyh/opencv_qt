#include "nehewidget.h"

#include <QDebug>
#include <QString>

Window::~Window()
{
    makeCurrent();
    teardownGL();
}

void Window::initializeGL()
{
    // 初始化 OpenGL 后端
    initializeOpenGLFunctions();
    printContextInformation();

    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
}

void Window::resizeGL(int width, int height)
{
    // 未做处理
}

void Window::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
}

// 回收资源
void Window::teardownGL()
{
}

// 打印相关信息，调试用
void Window::printContextInformation()
{
    QString glType;
    QString glVersion;
    QString glProfile;

    // 获取版本信息
    glType = (context()->isOpenGLES()) ? "OpenGL ES" : "OpenGL";
    glVersion = reinterpret_cast<const char*>(glGetString(GL_VERSION));

    // 获取 Profile 信息
#define CASE(c) case QSurfaceFormat::c: glProfile = #c; break
    switch (format().profile())
    {
        CASE(NoProfile);
        CASE(CoreProfile);
        CASE(CompatibilityProfile);
    }
#undef CASE

    qDebug() << qPrintable(glType) << qPrintable(glVersion) << "(" << qPrintable(glProfile) << ")";
}

