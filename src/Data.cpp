#include "Data.h"

Data* Data::m_class_object = nullptr;

void Data::Init() {

    // 使用当前时间作为随机种子
    std::srand(static_cast<unsigned int>(std::time(0)));

    { /* 生成参数头 */
        this->m_argument_head_axis.append({
            {"c_x", 0},
            {"c_width", 60},
            {"c_y", 0},
            {"value", "区域"}
        });
        this->m_argument_head_axis.append({
            {"c_x", 60},
            {"c_width", 60},
            {"c_y", 0},
            {"value", "国家"}
        });
        this->m_argument_head_axis.append({
            {"c_x", 120},
            {"c_width", 60},
            {"c_y", 0},
            {"value", "渠道类型"}
        });
        this->m_argument_head_axis.append({
            {"c_x", 180},
            {"c_width", 60},
            {"c_y", 0},
            {"value", "渠道"}
        });
        this->m_argument_head_axis.append({
            {"c_x", 240},
            {"c_width", 60},
            {"c_y", 0},
            {"value", "下游渠道"}
        });
        this->m_argument_head_axis.append({
            {"c_x", 300},
            {"c_width", 60},
            {"c_y", 0},
            {"value", "机型"}
        });
        this->m_argument_head_axis.append({
            {"c_x", 360},
            {"c_width", 60},
            {"c_y", 0},
            {"value", "产品代码"}
        });
        this->m_argument_head_axis.append({
            {"c_x", 420},
            {"c_width", 60},
            {"c_y", 0},
            {"value", "商品名"}
        });
        this->m_argument_head_axis.append({
            {"c_x", 480},
            {"c_width", 60},
            {"c_y", 0},
            {"value", "内存"}
        });
        this->m_argument_head_axis.append({
            {"c_x", 20 + 540},
            {"c_width", 60},
            {"c_y", 0},
            {"value", "颜色"}
        });
        this->m_argument_head_axis.append({
            {"c_x", 20 + 600},
            {"c_width", 60},
            {"c_y", 0},
            {"value", "EAN"}
        });
        this->m_argument_head_axis.append({
            {"c_x", 20 + 660},
            {"c_width", 60},
            {"c_y", 0},
            {"value", "ID"}
        });
        this->m_argument_head_axis.append({
            {"c_x", 20 + 720},
            {"c_width", 60},
            {"c_y", 0},
            {"value", "SKU"}
        });
        this->m_argument_head_axis.append({
            {"c_x", 40 + 780},
            {"c_width", 100},
            {"c_y", 0},
            {"value", "PSI TYPE"}
        });
    }

    { /* 生成时间轴 */
        QList<QString> first_week_date_for_year = {
            "2018-12-31",
            "2019-12-30",
            "2021-01-04",
            "2022-01-03",
            "2023-01-02",
            "2024-01-01",
            "2024-12-30",
            "2025-12-29",
            "2027-01-04",
            "2028-01-03"
        };
        QList<QMap<QString, QVariant>> time_axis_by_day = {};
        QList<QMap<QString, QVariant>> time_axis_by_week = {};
        QList<QMap<QString, QVariant>> time_axis_by_month = {};
        QDate date = QDate::fromString("2018-12-30", "yyyy-MM-dd");
        int week_number = -1;
        int day_index = -1;
        while (true) {
            { /* 控制循环 */
                date = date.addDays(1);
                day_index++;
                if (date == QDate::fromString("2029-01-01", "yyyy-MM-dd")) break;
            }
            QMap<QString, QVariant> map = {
                {"date", date.toString("yyyy-MM-dd")},
                {"year", date.year()},
                {"month", date.month()},
                {"day", date.day()},
                {"week_day", date.dayOfWeek()},
                {"month_value", ""},
                {"week_number", 0},
                {"month_size", 0},
                {"day_index", day_index},
                {"is_locked", false}
            };
            { /* 计算month_value和month_size */
                switch (date.month()) {
                    case 1: {
                        map["month_value"] = "January " + QString::number(date.year());
                        map["month_size"] = 31;
                        break;
                    }
                    case 2: {
                        map["month_value"] = "February " + QString::number(date.year());
                        map["month_size"] = date.year() % 4 == 0 ? 29 : 28;
                        break;
                    }
                    case 3: {
                        map["month_value"] = "March " + QString::number(date.year());
                        map["month_size"] = 31;
                        break;
                    }
                    case 4: {
                        map["month_value"] = "April " + QString::number(date.year());
                        map["month_size"] = 30;
                        break;
                    }
                    case 5: {
                        map["month_value"] = "May " + QString::number(date.year());
                        map["month_size"] = 31;
                        break;
                    }
                    case 6: {
                        map["month_value"] = "June " + QString::number(date.year());
                        map["month_size"] = 30;
                        break;
                    }
                    case 7: {
                        map["month_value"] = "July " + QString::number(date.year());
                        map["month_size"] = 31;
                        break;
                    }
                    case 8: {
                        map["month_value"] = "August " + QString::number(date.year());
                        map["month_size"] = 31;
                        break;
                    }
                    case 9: {
                        map["month_value"] = "September " + QString::number(date.year());
                        map["month_size"] = 30;
                        break;
                    }
                    case 10: {
                        map["month_value"] = "October " + QString::number(date.year());
                        map["month_size"] = 31;
                        break;
                    }
                    case 11: {
                        map["month_value"] = "November " + QString::number(date.year());
                        map["month_size"] = 30;
                        break;
                    }
                    case 12: {
                        map["month_value"] = "December " + QString::number(date.year());
                        map["month_size"] = 31;
                        break;
                    }
                }
            }
            { /* 计算week_number */
                if (first_week_date_for_year.contains(date.toString("yyyy-MM-dd"))) {
                    week_number = 0;
                }
                if (date.dayOfWeek() == 1) {
                    week_number++;
                }
                map["week_number"] = week_number;
            }
            time_axis_by_day.append(map);
            if (time_axis_by_week.isEmpty() || time_axis_by_week.last()["week_number"] != map["week_number"]) {
                time_axis_by_week.append(map);
            }
            if (time_axis_by_month.isEmpty() || time_axis_by_month.last()["month"] != map["month"]) {
                time_axis_by_month.append(map);
            }
        }
        this->m_time_axis_by_day = time_axis_by_day;
        this->m_time_axis_by_week = time_axis_by_week;
        this->m_time_axis_by_month = time_axis_by_month;
        this->m_edit_area_width = time_axis_by_day.size() * 70;

        qDebug() << "时间轴共" << this->m_time_axis_by_day.size() << "天";
    }

    // { /* 从数据库获取 */
    //     { /* 伪造客户信息 */
    //         QMap<QString, QVariant> map1 = {
    //             {"ID", "1"},
    //             {"Region", "欧洲"},
    //             {"Country", "西班牙"},
    //             {"ChannelType", "公开市场"},
    //             {"Channel", "INGRAM MICRO SLU"},
    //             {"ChannelID", "37749"},
    //             {"SubChannel", "A"},
    //             {"VersionType", "欧规"}
    //         };
    //         QMap<QString, QVariant> map2 = {
    //             {"ID", "2"},
    //             {"Region", "欧洲"},
    //             {"Country", "西班牙"},
    //             {"ChannelType", "公开市场"},
    //             {"Channel", "INGRAM MICRO SLU"},
    //             {"ChannelID", "37749"},
    //             {"SubChannel", "B"},
    //             {"VersionType", "欧规"}
    //         };
    //         QMap<QString, QVariant> map3 = {
    //             {"ID", "3"},
    //             {"Region", "欧洲"},
    //             {"Country", "意大利"},
    //             {"ChannelType", "公开市场"},
    //             {"Channel", "INGRAM MICRO S.R.L."},
    //             {"ChannelID", "418079"},
    //             {"SubChannel", ""},
    //             {"VersionType", "欧规"}
    //         };
    //         QMap<QString, QVariant> map4 = {
    //             {"ID", "4"},
    //             {"Region", "亚洲"},
    //             {"Country", "支那"},
    //             {"ChannelType", "电商"},
    //             {"Channel", "SAC"},
    //             {"ChannelID", "666666"},
    //             {"SubChannel", ""},
    //             {"VersionType", "SAC版"}
    //         };
    //         this->m_raw_arr_t_customer_from_database = {map1, map2, map3, map4};
    //     }
    //     { /* 伪造产品信息 */
    //         QMap<QString, QVariant> map1 = {
    //             {"ID", "37648"},
    //             {"Model", "Redmi Note 13"},
    //             {"ProductCode", "K7TN"},
    //             {"CommercialName", "Redmi Note 13 8+256"},
    //             {"RAMROM", "8+256"},
    //             {"Color", "黑色"},
    //             {"EAN", "6934177767291"},
    //             {"SKU", "MZBOALUEW"},
    //             {"VersionType", "欧规"}
    //         };
    //         QMap<QString, QVariant> map2 = {
    //             {"ID", "37647"},
    //             {"Model", "Redmi Note 13"},
    //             {"ProductCode", "K7TN"},
    //             {"CommercialName", "Redmi Note 13 8+256"},
    //             {"RAMROM", "8+256"},
    //             {"Color", "白色"},
    //             {"EAN", "6934177767290"},
    //             {"SKU", "MZBOALUEV"},
    //             {"VersionType", "欧规"}
    //         };
    //         QMap<QString, QVariant> map3 = {
    //             {"ID", "37646"},
    //             {"Model", "Redmi Note 13"},
    //             {"ProductCode", "K7TN"},
    //             {"CommercialName", "Redmi Note 13 4+128"},
    //             {"RAMROM", "4+128"},
    //             {"Color", "白色"},
    //             {"EAN", "6934177767289"},
    //             {"SKU", "MZBOALUEU"},
    //             {"VersionType", "欧规"}
    //         };
    //         QMap<QString, QVariant> map4 = {
    //             {"ID", "32011"},
    //             {"Model", "Redmi Note 10"},
    //             {"ProductCode", "K7A"},
    //             {"CommercialName", "Redmi Note 10 4+128"},
    //             {"RAMROM", "4+128"},
    //             {"Color", "白色"},
    //             {"EAN", "6934177736186"},
    //             {"SKU", "MZBO8PYEN"},
    //             {"VersionType", "欧规"}
    //         };
    //         QMap<QString, QVariant> map5 = {
    //             {"ID", "32009"},
    //             {"Model", "Redmi Note 10"},
    //             {"ProductCode", "K7A"},
    //             {"CommercialName", "Redmi Note 10 4+128"},
    //             {"RAMROM", "4+128"},
    //             {"Color", "锖色"},
    //             {"EAN", "6934177736193"},
    //             {"SKU", "MZBO8PYWN"},
    //             {"VersionType", "欧规"}
    //         };
    //         QMap<QString, QVariant> map6 = {
    //             {"ID", "66666"},
    //             {"Model", "SAC X66"},
    //             {"ProductCode", "SAC"},
    //             {"CommercialName", "SAC X20 16+1T"},
    //             {"RAMROM", "16+1T"},
    //             {"Color", "心华色"},
    //             {"EAN", "6666666666666"},
    //             {"SKU", "SACSACSAC"},
    //             {"VersionType", "SAC版"}
    //         };
    //         this->m_raw_arr_t_product_from_database = {map1, map2, map3, map4, map5, map6};
    //     }
    //     Interface::m_class_object->m_parse_customer_and_product_from_map();
    //     qDebug() << "时间轴共" << this->m_time_axis_by_day.size() << "天";
    //     qDebug() << "解析完成，共得到" << Data::m_class_object->m_block_map.size() << "组产品，共生成" << this->m_line_list.size() << "行数据";
    //     // Interface::m_class_object->m_parse_psi_data();
    // }

}