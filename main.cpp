#include "main.h"

QtCommonClass* QtCommonClass::m_class_object = nullptr;
ObjectPoint* ObjectPoint::m_class_object = nullptr;

int main(int argc, char *argv[]) {
    // QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    new QtCommonClass();
    { /* 全局数据层 */
        qDebug() << "加载全局数据层：";
        new ApiClient();
        qDebug() << "ApiClient::m_class_object" << ApiClient::m_class_object;
        new Data();
        qDebug() << "Data::m_class_object" << Data::m_class_object;
        new Interface();
        qDebug() << "Interface::m_class_object" << Interface::m_class_object;
        new ObjectPoint();
        qDebug() << "ObjectPoint::m_class_object" << ObjectPoint::m_class_object;
        Interface::m_class_object->Init();
        Data::m_class_object->Init();
    }
    { /* 界面层 */
        qDebug() << "加载界面层：";
        new MainWnd();
        qDebug() << "MainWnd::m_class_object" << MainWnd::m_class_object;
        qDebug() << "MainWnd::m_qml_object" << MainWnd::m_class_object->m_qml_object;
        new MenuBar();
        qDebug() << "MenuBar::m_class_object" << MenuBar::m_class_object;
        qDebug() << "MenuBar::m_qml_object" << MenuBar::m_class_object->m_qml_object;
        // new ArgumentArea();
        // qDebug() << "ArgumentArea::m_class_object" << ArgumentArea::m_class_object;
        // qDebug() << "ArgumentArea::m_qml_object" << ArgumentArea::m_class_object->m_qml_object;
        // new TimeAxisArea();
        // qDebug() << "TimeAxisArea::m_class_object" << TimeAxisArea::m_class_object;
        // qDebug() << "TimeAxisArea::m_qml_object" << TimeAxisArea::m_class_object->m_qml_object;
        // new EditableArea();
        // qDebug() << "EditableArea::m_class_object" << EditableArea::m_class_object;
        // qDebug() << "EditableArea::m_qml_object" << EditableArea::m_class_object->m_qml_object;
    }

    qDebug() << "\n\n\n开始运行：";
    return app.exec();
}
