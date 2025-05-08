#include "MainWnd.h"

MainWnd* MainWnd::m_class_object = nullptr;

MainWnd::MainWnd() {
    qDebug() << "MainWnd::MainWnd()";
    this->m_class_object = this;
    { /* MainWnd.qml */
        QQmlComponent component(&(QtCommonClass::m_class_object->engine), QUrl(QStringLiteral("qrc:/qml/MainWnd.qml")));
        if (component.status() != QQmlComponent::Status::Ready) {
            qDebug() << component.status() << component.errorString();
            return;
        }
        this->m_qml_object = component.create();
        if (! this->m_qml_object) {
            qDebug() << "MainWnd::MainWnd() failed";
            return;
        }
    }
};

MainWnd::~MainWnd() {
    qDebug() << "MainWnd::~MainWnd()";
};