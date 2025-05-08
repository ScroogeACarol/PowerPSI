#include "TimeAxisArea.h"

TimeAxisArea* TimeAxisArea::m_class_object = nullptr;

TimeAxisArea::TimeAxisArea() {
    qDebug() << "TimeAxisArea::TimeAxisArea()";
    this->m_class_object = this;
    { /* TimeAxisArea.qml */
        QQmlComponent component(&(QtCommonClass::m_class_object->engine), QUrl(QStringLiteral("qrc:/qml/TimeAxisArea.qml")));
        if (component.status() != QQmlComponent::Status::Ready) {
            qDebug() << component.status() << component.errorString();
            return;
        }
        this->m_qml_object = component.create();
        if (! this->m_qml_object) {
            qDebug() << "TimeAxisArea::TimeAxisArea() failed";
            return;
        }
    }
};

TimeAxisArea::~TimeAxisArea() {
    qDebug() << "TimeAxisArea::~TimeAxisArea()";
};