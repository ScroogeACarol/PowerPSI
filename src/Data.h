#pragma once
#include "main.h"

class Data;

class Data : public QObject {
    Q_OBJECT
    public:
        Data(QObject* parent = nullptr) {
            Data::m_class_object = this;
            qmlRegisterSingletonType<Data>("Class.Data", 1, 0, "Data",
                [](QQmlEngine *engine, QJSEngine *scriptEngine) -> QObject * {
                    Q_UNUSED(engine)
                    Q_UNUSED(scriptEngine)
                    return Data::m_class_object;
                }
            );
        };
        ~Data() {};
        static Data* m_class_object;
    public:
        void Init();
    public: /* 原始数据 */
        QList<QMap<QString, QVariant>> m_raw_arr_t_customer_from_database = {};
        QList<QMap<QString, QVariant>> m_raw_arr_t_product_from_database = {};
    public: /* 中间数据 */
        QList<QMap<QString, QVariant>> m_arr_t_customer = {};
        QList<QMap<QString, QVariant>> m_arr_t_product = {};
        QList<QMap<QString, QVariant>> m_customer_and_product_list = {};
        QList<QMap<QString, QVariant>> m_line_list = {}; // m_line_list[region|country|channel_type|channel|sub_channel|model|product_code|commercial_name|RAM_ROM|color|EAN|ID|SKU|version_type|product_info|block_info|psi_type|line_info|c_y]
        QMap<QString, QList<int>> m_block_map = {}; // m_block_map[block_info]，目前仅用于打印块的数量以供Debug
        QMap<QString, QMap<QString, QVariant>> m_psi_data = {}; // m_psi_data[line_info][date]
        QMap<QString, QMap<QString, QVariant>> m_append_data = {}; // m_append_data[line_info][date]
    public: /* 显示字段 */
        QList<QMap<QString, QVariant>> m_argument_head_axis = {};
        QList<QMap<QString, QVariant>> m_time_axis_by_day = {};
        QList<QMap<QString, QVariant>> m_time_axis_by_week = {};
        QList<QMap<QString, QVariant>> m_time_axis_by_month = {};
        QList<QMap<QString, QVariant>> m_y_axis = {};
        int m_edit_area_width = 0;
        int m_edit_area_height = 0;
        QList<QMap<QString, QVariant>> m_cell_list = {}; // m_cell_list[c_x|c_y|c_width|c_height|value]
        double m_table_contentX = 0;
        double m_table_contentY = 0;
        signals:
        void m_argument_head_axisChanged();
        void m_time_axis_by_dayChanged();
        void m_time_axis_by_weekChanged();
        void m_time_axis_by_monthChanged();
        void m_y_axisChanged();
        void m_edit_area_widthChanged();
        void m_edit_area_heightChanged();
        void m_cell_listChanged();
        void m_table_contentXChanged();
        void m_table_contentYChanged();
        public:
        Q_PROPERTY(QList<QMap<QString, QVariant>> argument_head_axis MEMBER m_argument_head_axis NOTIFY m_argument_head_axisChanged);
        Q_PROPERTY(QList<QMap<QString, QVariant>> time_axis_by_day MEMBER m_time_axis_by_day NOTIFY m_time_axis_by_dayChanged);
        Q_PROPERTY(QList<QMap<QString, QVariant>> time_axis_by_week MEMBER m_time_axis_by_week NOTIFY m_time_axis_by_weekChanged);
        Q_PROPERTY(QList<QMap<QString, QVariant>> time_axis_by_month MEMBER m_time_axis_by_month NOTIFY m_time_axis_by_monthChanged);
        Q_PROPERTY(QList<QMap<QString, QVariant>> y_axis MEMBER m_y_axis NOTIFY m_y_axisChanged);
        Q_PROPERTY(int edit_area_width MEMBER m_edit_area_width NOTIFY m_edit_area_widthChanged);
        Q_PROPERTY(int edit_area_height MEMBER m_edit_area_height NOTIFY m_edit_area_heightChanged);
        Q_PROPERTY(QList<QMap<QString, QVariant>> cell_list MEMBER m_cell_list NOTIFY m_cell_listChanged);
        Q_PROPERTY(double table_contentX MEMBER m_table_contentX NOTIFY m_table_contentXChanged);
        Q_PROPERTY(double table_contentY MEMBER m_table_contentY NOTIFY m_table_contentYChanged); 

};