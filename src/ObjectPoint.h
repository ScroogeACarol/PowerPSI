#pragma once
#include "main.h"

class ObjectPoint;

class ObjectPoint : public QObject {
    Q_OBJECT
    public:
        ObjectPoint(QObject* parent = nullptr) {
            ObjectPoint::m_class_object = this;
            qmlRegisterSingletonType<ObjectPoint>("Class.ObjectPoint", 1, 0, "ObjectPoint",
                [](QQmlEngine *engine, QJSEngine *scriptEngine) -> QObject * {
                    Q_UNUSED(engine)
                    Q_UNUSED(scriptEngine)
                    return ObjectPoint::m_class_object;
                }
            );
        };
        ~ObjectPoint() {};
        static ObjectPoint* m_class_object;
    public:
        QObject* m_menu_bar_parent = nullptr;
        QObject* m_argument_area_parent = nullptr;
        QObject* m_argument_area = nullptr;
        QObject* m_argument_flickable = nullptr;
        QObject* m_time_axis_area_parent = nullptr;
        QObject* m_time_axis_area = nullptr;
        QObject* m_time_axis_flickable = nullptr;
        QObject* m_editable_area_parent = nullptr;
        signals:
        void m_menu_bar_parentChanged();
        void m_argument_area_parentChanged();
        void m_argument_flickableChanged();
        void m_argument_areaChanged();
        void m_time_axis_area_parentChanged();
        void m_time_axis_areaChanged();
        void m_time_axis_flickableChanged();
        void m_editable_area_parentChanged();
        public:
        Q_PROPERTY(QObject* menu_bar_parent MEMBER m_menu_bar_parent NOTIFY m_menu_bar_parentChanged);
        Q_PROPERTY(QObject* argument_area_parent MEMBER m_argument_area_parent NOTIFY m_argument_area_parentChanged);
        Q_PROPERTY(QObject* argument_area MEMBER m_argument_area NOTIFY m_argument_areaChanged);
        Q_PROPERTY(QObject* argument_flickable MEMBER m_argument_flickable NOTIFY m_argument_flickableChanged);
        Q_PROPERTY(QObject* time_axis_area_parent MEMBER m_time_axis_area_parent NOTIFY m_time_axis_area_parentChanged);
        Q_PROPERTY(QObject* time_axis_area MEMBER m_time_axis_area NOTIFY m_time_axis_areaChanged);
        Q_PROPERTY(QObject* time_axis_flickable MEMBER m_time_axis_flickable NOTIFY m_time_axis_flickableChanged);
        Q_PROPERTY(QObject* editable_area_parent MEMBER m_editable_area_parent NOTIFY m_editable_area_parentChanged);

};