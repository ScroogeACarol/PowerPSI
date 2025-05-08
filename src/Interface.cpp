#include "Interface.h"

const bool IS_TESTING = true; // 测试模式
const QString TEST_ROOT_DIR = "C:/Users/ScroogeACarol/Desktop/Workspace/PowerPSI/"; // 测试模式下的根目录

Interface* Interface::m_class_object = nullptr;
static QList<QList<QString>> read_excel(QString target);
static bool write_excel(QString target, QList<QList<QString>> write_list_list);
static void append_psi_data();
static QDate parse_excel_date(const QString& date_str);

void Interface::Init() {
    // 连接 ApiClient 的 responseReceived 信号到 Data 类的 onApiResponseReceived 槽
    connect(ApiClient::m_class_object, &ApiClient::responseReceived, this, &Interface::onApiResponseReceived);
}

void Interface::m_parse_customer_and_product_from_map() {
    qDebug() << "Interface::m_parse_customer_and_product_from_map()";

    { /* m_raw_arr_t_customer_from_database -> m_arr_t_customer */
        QList<QMap<QString, QVariant>>& raw_list_list = Data::m_class_object->m_raw_arr_t_customer_from_database;
        QList<QMap<QString, QVariant>> customer_list = {};
        for (auto it1_map : raw_list_list) {
            customer_list.append({
                {"ID", it1_map["ID"].toString()},
                {"region", it1_map["Region"].toString()},
                {"country", it1_map["Country"].toString()},
                {"channel_type", it1_map["ChannelType"].toString()},
                {"channel", it1_map["Channel"].toString()},
                {"sub_channel", it1_map["SubChannel"].toString()},
                {"version_type", it1_map["VersionType"].toString()}
            });
        }
        Data::m_class_object->m_arr_t_customer = customer_list;
    }

    { /* m_raw_arr_t_product_from_database -> m_arr_t_product */
        QList<QMap<QString, QVariant>>& raw_list_list = Data::m_class_object->m_raw_arr_t_product_from_database;
        QList<QMap<QString, QVariant>> product_list = {};
        for (auto it1_map : raw_list_list) {
            product_list.append({
                {"model", it1_map["Model"]},
                {"product_code", it1_map["ProductCode"]},
                {"commercial_name", it1_map["CommercialName"]},
                {"RAM_ROM", it1_map["RAMROM"]},
                {"color", it1_map["Color"]},
                {"EAN", it1_map["EAN"]},
                {"ID", it1_map["ID"]},
                {"SKU", it1_map["SKU"]},
                {"version_type", it1_map["VersionType"]},
                {"product_info", it1_map["ProductCode"].toString() + it1_map["RAMROM"].toString()}
            });
        }
        std::sort(product_list.begin(), product_list.end(), [](QMap<QString, QVariant> a, QMap<QString, QVariant> b) {
            if (false) {
            } else if (a["product_info"].toString() != b["product_info"].toString()) {
                return a["product_info"].toString() < b["product_info"].toString();
            } else if (a["ID"].toInt() != b["ID"].toInt()) {
                return a["ID"].toInt() < b["ID"].toInt();
            }
            qWarning() << "SACError: 存在完全相同的产品";
            return true; // 不交换
        });
        Data::m_class_object->m_arr_t_product = product_list;
    }

    { /* m_arr_t_customer + m_arr_t_product = m_customer_and_product_list */
        QList<QMap<QString, QVariant>> customer_and_product_list = {};
        QMap<QString, QList<int>> block_map = {};
        for (auto it1_map : Data::m_class_object->m_arr_t_customer) {
            for (auto it2_map : Data::m_class_object->m_arr_t_product) {
                if (it1_map["version_type"].toString() != it2_map["version_type"].toString()) continue;
                customer_and_product_list.append({
                    {"region", it1_map["region"]},
                    {"country", it1_map["country"]},
                    {"channel_type", it1_map["channel_type"]},
                    {"channel", it1_map["channel"]},
                    {"sub_channel", it1_map["sub_channel"]},
                    {"model", it2_map["model"]},
                    {"product_code", it2_map["product_code"]},
                    {"commercial_name", it2_map["commercial_name"]},
                    {"RAM_ROM", it2_map["RAM_ROM"]},
                    {"color", it2_map["color"]},
                    {"EAN", it2_map["EAN"]},
                    {"ID", it2_map["ID"]},
                    {"SKU", it2_map["SKU"]},
                    {"version_type", it2_map["version_type"]},
                    {"product_info", it2_map["product_info"]},
                    {"block_info", it1_map["channel"].toString() + it1_map["sub_channel"].toString() + it2_map["product_info"].toString()}
                });
                block_map[customer_and_product_list.last()["block_info"].toString()] = {};
            }
        }
        Data::m_class_object->m_customer_and_product_list = customer_and_product_list;
        Data::m_class_object->m_block_map = block_map;
    }

    { /* m_customer_and_product_list -> m_line_list */
        QList<QMap<QString, QVariant>>& a_list = Data::m_class_object->m_customer_and_product_list;
        QList<QMap<QString, QVariant>> b_list = {};
        QList<QMap<QString, QVariant>> c_list = {};
        QList<QString> psi_type_1 = {"P(Total)", "S(Total)", "I(Total)", "DOS(Total)"};
        QList<QString> psi_type_2 = {"P", "S", "I", "DOS"};
        QList<QString> psi_type_3 = {"回传库存", "促销价", "前返", "单台促销投入", "促销总投入", "总投入", "Flyer", "店内A4", "单台绑赠", "绑赠总投入", "免息分期费率", "免息分期总投入", "单台店员激励", "店员激励总投入", "单台以旧换新投入", "以旧换新总投入", "单台TV广告投入", "TV广告总投入", "税", "开盘价", "开盘前返", "TP", "Promo_TP", "总收入", "代理商点位", "代理商单台利润", "授权成本", "单台操盘费生成", "操盘费总生成", "后返", "总后返", "单台平均后返", "损益"};
        int y = 0;
        for (int it1 = 0; it1 < a_list.size(); it1++) {
            { /* 同组产品前加入Total */
                if (it1 == 0 || a_list[it1]["block_info"] != a_list[it1 - 1]["block_info"]) {
                    b_list.append(a_list[it1]);
                    b_list.last()["color"] = "Total";
                    b_list.last()["EAN"] = "Total";
                    b_list.last()["ID"] = "Total";
                    b_list.last()["SKU"] = "Total";
                    for (auto it2 : psi_type_1) {
                        c_list.append(b_list.last());
                        c_list.last()["psi_type"] = it2;
                        c_list.last()["line_info"] = b_list.last()["block_info"].toString() + b_list.last()["SKU"].toString() + it2;
                        y += 20;
                        c_list.last()["c_y"] = y;
                    }
                }
            }
            { /* 每个产品 */
                b_list.append(a_list[it1]);
                for (auto it2 : psi_type_2) {
                    c_list.append(b_list.last());
                    c_list.last()["psi_type"] = it2;
                    c_list.last()["line_info"] = b_list.last()["block_info"].toString() + b_list.last()["SKU"].toString() + it2;
                    y += 20;
                    c_list.last()["c_y"] = y;
                }
            }
            { /* 同组产品后加入Total */
                if (it1 == a_list.size() - 1 || a_list[it1]["block_info"] != a_list[it1 + 1]["block_info"]) {
                    b_list.append(a_list[it1]);
                    b_list.last()["color"] = "Total";
                    b_list.last()["EAN"] = "Total";
                    b_list.last()["ID"] = "Total";
                    b_list.last()["SKU"] = "Total";
                    for (auto it2 : psi_type_3) {
                        c_list.append(b_list.last());
                        c_list.last()["psi_type"] = it2;
                        c_list.last()["line_info"] = b_list.last()["block_info"].toString() + b_list.last()["SKU"].toString() + it2;
                        y += 20;
                        c_list.last()["c_y"] = y;
                    }
                    y += 20;
                }
            }
        }
        Data::m_class_object->m_line_list = c_list;
        Data::m_class_object->m_edit_area_height = y;
    }

    { /* m_line_list -> m_y_axis */
        QList<QMap<QString, QVariant>> table_info = {};
        QList<QMap<QString, QVariant>> y_axis = {};
        QList<QString> map_keys = {"region", "country", "channel_type", "channel", "sub_channel", "model", "product_code", "commercial_name", "RAM_ROM", "color", "EAN", "ID", "SKU", "psi_type"};
        for (auto it1_map : Data::m_class_object->m_line_list) {
            int x = 0;
            for (auto it2 : map_keys) {
                y_axis.append({
                    {"c_x", x},
                    {"c_width", it2 != "psi_type" ? 60 : 100},
                    {"c_y", it1_map["c_y"]},
                    {"value", it1_map[it2]}
                });
                x += 60;
                if (it2 == "RAM_ROM") x += 20;
                if (it2 == "SKU") x += 20;
                if (it2 == "psi_type") x = 0;
            }
        }
        Data::m_class_object->m_y_axis = y_axis;
    }
}

void Interface::m_parse_customer_and_product_from_excel() {
    qDebug() << "Interface::m_parse_customer_and_product_from_excel()";

    { /* m_raw_arr_t_customer_from_excel -> m_raw_arr_t_customer_from_database */
        QList<QMap<QString, QVariant>> raw_arr_t_customer = {};
        QList<QList<QString>> raw_list_list = read_excel((IS_TESTING ? TEST_ROOT_DIR : "") + "data/customer.xlsx");
        if (raw_list_list.isEmpty() || raw_list_list.size() < 2) {
            qWarning() << "SACError: 读取客户信息失败";
            return;
        }
        QMap<int, QString> head_map = {};
        for (int it1 = 0; it1 < raw_list_list[0].size(); it1++) {
            if (false) {
            } else if (raw_list_list[0][it1] == "区域") {
                head_map[it1] = "Region";
            } else if (raw_list_list[0][it1] == "国家") {
                head_map[it1] = "Country";
            } else if (raw_list_list[0][it1] == "渠道类型") {
                head_map[it1] = "ChannelType";
            } else if (raw_list_list[0][it1] == "渠道") {
                head_map[it1] = "Channel";
            } else if (raw_list_list[0][it1] == "下游渠道") {
                head_map[it1] = "SubChannel";
            } else if (raw_list_list[0][it1] == "流通版本") {
                head_map[it1] = "VersionType";
            }
        }
        for (int it1 = 1; it1 < raw_list_list.size(); it1++) {
            QMap<QString, QVariant> map = {};
            for (int it2 = 0; it2 < raw_list_list[it1].size(); it2++) {
                if (!head_map.contains(it2)) continue;
                map[head_map[it2]] = raw_list_list[it1][it2];
            }
            raw_arr_t_customer.append(map);
        }
        Data::m_class_object->m_raw_arr_t_customer_from_database = raw_arr_t_customer;
    }

    { /* m_raw_arr_t_product_from_excel -> m_raw_arr_t_product_from_database */
        QList<QMap<QString, QVariant>> raw_arr_t_product = {};
        QList<QList<QString>> raw_list_list = read_excel((IS_TESTING ? TEST_ROOT_DIR : "") + "data/product.xlsx");
        if (raw_list_list.isEmpty() || raw_list_list.size() < 2) {
            qWarning() << "SACError: 读取产品信息失败";
            return;
        }
        QMap<int, QString> head_map = {};
        for (int it1 = 0; it1 < raw_list_list[1].size(); it1++) {
            if (false) {
            } else if (raw_list_list[0][it1] == "机型") {
                head_map[it1] = "Model";
            } else if (raw_list_list[0][it1] == "产品代码") {
                head_map[it1] = "ProductCode";
            } else if (raw_list_list[0][it1] == "商品名") {
                head_map[it1] = "CommercialName";
            } else if (raw_list_list[0][it1] == "内存") {
                head_map[it1] = "RAMROM";
            } else if (raw_list_list[0][it1] == "颜色") {
                head_map[it1] = "Color";
            } else if (raw_list_list[0][it1] == "EAN") {
                head_map[it1] = "EAN";
            } else if (raw_list_list[0][it1] == "ID") {
                head_map[it1] = "ID";
            } else if (raw_list_list[0][it1] == "SKU") {
                head_map[it1] = "SKU";
            } else if (raw_list_list[0][it1] == "版本") {
                head_map[it1] = "VersionType";
            }
        }
        for (int it1 = 1; it1 < raw_list_list.size(); it1++) {
            QMap<QString, QVariant> map = {};
            for (int it2 = 0; it2 < raw_list_list[it1].size(); it2++) {
                if (!head_map.contains(it2)) continue;
                map[head_map[it2]] = raw_list_list[it1][it2];
            }
            raw_arr_t_product.append(map);
        }
        Data::m_class_object->m_raw_arr_t_product_from_database = raw_arr_t_product;
    }

    this->m_parse_customer_and_product_from_map();
    qDebug() << "解析完成，共得到" << Data::m_class_object->m_block_map.size() << "组产品，共生成" << Data::m_class_object->m_line_list.size() << "行数据";
}

void Interface::m_parse_psi_data_from_excel() {
    qDebug() << "Interface::m_parse_psi_data_from_excel()";

    { /* psi_data.xlsx -> m_append_data */
        QMap<QString, QMap<QString, QVariant>> append_data = {};
        QList<QList<QString>> raw_list_list = read_excel((IS_TESTING ? TEST_ROOT_DIR : "") + "data/psi_data.xlsx");
        if (raw_list_list.isEmpty() || raw_list_list.size() < 2) {
            qWarning() << "SACError: 读取PSI数据失败";
            return;
        }
        QMap<int, QString> raw_head_map = {};
        for (int it1 = 14; it1 < raw_list_list[0].size(); it1++) {
            if (raw_list_list[0][it1].isEmpty()) continue;
            if (!QVariant(raw_list_list[0][it1]).toDate().isValid()) continue;
            raw_head_map[it1] = QVariant(raw_list_list[0][it1]).toDate().toString("yyyy-MM-dd");
        }
        if (raw_head_map.isEmpty()) {
            qWarning() << "SACError: 读取PSI数据的时间轴失败";
            return;
        }
        { /* 时间轴上锁 */
            QDate last_day = QDate::fromString("2018-12-30", "yyyy-MM-dd");
            for (int it1 = raw_list_list[1].size() - 1; it1 >= 14; it1--) {
                if (raw_list_list[1][it1] == "Locked") {
                    Data::m_class_object->m_time_axis_by_day[it1 - 14]["is_locked"] = true;
                } else {
                    Data::m_class_object->m_time_axis_by_day[it1 - 14]["is_locked"] = false;
                }
            }
        }
        for (int it1 = 2; it1 < raw_list_list.size(); it1++) {
            if (raw_list_list[it1].size() < 14) continue;
            QString line_info = "";
            { /* 解析表格前14列计算line_info */
                line_info += raw_list_list[it1][3]; // 渠道
                line_info += raw_list_list[it1][4]; // 下游渠道
                line_info += raw_list_list[it1][6]; // 产品代码
                line_info += raw_list_list[it1][8]; // 内存
                line_info += raw_list_list[it1][12]; // SKU
                line_info += raw_list_list[it1][13]; // PSI TYPE
            }
            QMap<QString, QVariant> tmp_map = {};
            for (int it2 = 14; it2 < raw_list_list[it1].size(); it2++) {
                QString date = raw_head_map[it2];
                tmp_map[date] = raw_list_list[it1][it2];
            }
            append_data[line_info] = tmp_map;
        }
        Data::m_class_object->m_append_data = append_data;
    }

    append_psi_data();

    // { /* m_cell_list暂时只放出14天的数据 */
    //     QList<QMap<QString, QVariant>> cell_list = {};
    //     for (auto it1_map : Data::m_class_object->m_cell_list) {
    //         if (it1_map["c_x"].toInt() < 14 * 70) {
    //             cell_list.append(it1_map);
    //         }
    //     }
    //     Data::m_class_object->m_cell_list = cell_list;
    // }
}

void Interface::m_parse_so_data_from_excel() {
    qDebug() << "Interface::m_parse_so_data_from_excel()";

    { /* IN_PSI_SO.xlsx -> m_append_data */
        QMap<QString, QMap<QString, QVariant>> append_data = {};
        QList<QList<QString>> raw_list_list = read_excel((IS_TESTING ? TEST_ROOT_DIR : "") + "IN_PSI_SO.xlsx");
        if (raw_list_list.isEmpty() || raw_list_list.size() < 2) {
            qWarning() << "SACError: 读取PSI数据失败";
            return;
        }
        { /* 检查表头 */
            if (
                raw_list_list[0][0] != "SKU" ||
                raw_list_list[0][1] != "EAN" ||
                raw_list_list[0][2] != "Category" ||
                raw_list_list[0][3] != "Channel" ||
                raw_list_list[0][4] != "Product_Name" ||
                raw_list_list[0][5] != "Project_Code" ||
                raw_list_list[0][6] != "Color" ||
                raw_list_list[0][7] != "RAM+ROM(g)" ||
                raw_list_list[0][8] != "Year" ||
                raw_list_list[0][9] != "Quarter" ||
                raw_list_list[0][10] != "Month" ||
                raw_list_list[0][11] != "Week" ||
                raw_list_list[0][12] != "Date" ||
                raw_list_list[0][13] != "SO" ||
                raw_list_list[0][14] != "Stock" ||
                raw_list_list[0][15] != "KA" ||
                raw_list_list[0][16] != "Client"
            ) {
                qWarning() << "SACError: 表格格式错误";
                return;
            }
        }
        for (int it1 = 1; it1 < raw_list_list.size(); it1++) {
            QString line_info = "";
            { /* 解析表格计算line_info */
                line_info += raw_list_list[it1][15]; // 渠道(KA)
                line_info += raw_list_list[it1][16]; // 下游渠道(Client)
                line_info += raw_list_list[it1][5]; // 产品代码(Project_Code)
                line_info += raw_list_list[it1][7]; // 内存(RAM+ROM(g))
                line_info += raw_list_list[it1][0]; // SKU
                line_info += "S"; // PSI TYPE
            }
            QList<double> default_day_weight = {0, 0.14, 0.14, 0.14, 0.14, 0.15, 0.15, 0.14};
            QList<QString> date_list = {};
            QList<double> day_weight = {};
            { /* 解析表格计算date */
                QDate date = parse_excel_date(raw_list_list[it1][12]);
                if (!date.isValid()) continue;
                QString week_str = raw_list_list[it1][11];
                int week = week_str.toInt();
                for (auto it2_map : Data::m_class_object->m_time_axis_by_day) {
                    QDate it2_date = QDate::fromString(it2_map["date"].toString(), "yyyy-MM-dd");
                    if (qAbs(date.daysTo(it2_date)) <= 7 && it2_map["week_number"].toInt() == week) {
                        date_list.append(it2_map["date"].toString());
                        day_weight.append(default_day_weight[it2_map["week_day"].toInt()]);
                    }
                }
            }
            int sell_out = raw_list_list[it1][13].toInt();
            { /* 计算append_data */
                QMap<QString, QVariant> tmp_map = {};
                for (int it2 = 0; it2 < date_list.size(); it2++) {
                    tmp_map[date_list[it2]] = sell_out * day_weight[it2];
                }
                append_data[line_info] = tmp_map;
            }
        }
        Data::m_class_object->m_append_data = append_data;
    }

    append_psi_data();
}

void Interface::m_parse_st_data_from_excel() {
    qDebug() << "Interface::m_parse_st_data_from_excel()";

    { /* IN_PSI_ST.xlsx -> m_append_data */
        QMap<QString, QMap<QString, QVariant>> append_data = {};
        QList<QList<QString>> raw_list_list = read_excel((IS_TESTING ? TEST_ROOT_DIR : "") + "IN_PSI_ST.xlsx");
        if (raw_list_list.isEmpty() || raw_list_list.size() < 2) {
            qWarning() << "SACError: 读取PSI数据失败";
            return;
        }
        { /* 检查表头 */
            if (
                raw_list_list[0][0] != "SKU" ||
                raw_list_list[0][1] != "Product_Name" ||
                raw_list_list[0][2] != "Project_Code" ||
                raw_list_list[0][3] != "Color" ||
                raw_list_list[0][4] != "RAM-ROM(g)" ||
                raw_list_list[0][5] != "Distributor" ||
                raw_list_list[0][6] != "Channel" ||
                raw_list_list[0][7] != "KA" ||
                raw_list_list[0][8] != "Client" ||
                raw_list_list[0][9] != "Year" ||
                raw_list_list[0][10] != "Quarter" ||
                raw_list_list[0][11] != "Month" ||
                raw_list_list[0][12] != "Week" ||
                raw_list_list[0][13] != "Date" ||
                raw_list_list[0][14] != "ST"
            ) {
                qWarning() << "SACError: 表格格式错误";
                return;
            }
        }
        for (int it1 = 1; it1 < raw_list_list.size(); it1++) {
            QString line_info = "";
            { /* 解析表格计算line_info */
                line_info += raw_list_list[it1][7]; // 渠道(KA)
                line_info += raw_list_list[it1][8]; // 下游渠道(Client)
                line_info += raw_list_list[it1][2]; // 产品代码(Project_Code)
                line_info += raw_list_list[it1][4]; // 内存(RAM+ROM(g))
                line_info += raw_list_list[it1][0]; // SKU
                line_info += "P"; // PSI TYPE
            }
            QList<double> default_day_weight = {0, 0.14, 0.14, 0.14, 0.14, 0.15, 0.15, 0.14};
            QList<QString> date_list = {};
            QList<double> day_weight = {};
            { /* 解析表格计算date */
                QDate date = parse_excel_date(raw_list_list[it1][13]);
                if (!date.isValid()) continue;
                QString week_str = raw_list_list[it1][12];
                int week = week_str.toInt();
                for (auto it2_map : Data::m_class_object->m_time_axis_by_day) {
                    QDate it2_date = QDate::fromString(it2_map["date"].toString(), "yyyy-MM-dd");
                    if (qAbs(date.daysTo(it2_date)) <= 7 && it2_map["week_number"].toInt() == week) {
                        date_list.append(it2_map["date"].toString());
                        day_weight.append(default_day_weight[it2_map["week_day"].toInt()]);
                    }
                }
            }
            int stock_transfer = raw_list_list[it1][14].toInt();
            { /* 计算append_data */
                QMap<QString, QVariant> tmp_map = {};
                for (int it2 = 0; it2 < date_list.size(); it2++) {
                    tmp_map[date_list[it2]] = stock_transfer * day_weight[it2];
                }
                append_data[line_info] = tmp_map;
            }
        }
        Data::m_class_object->m_append_data = append_data;
    }

    append_psi_data();
}

void Interface::m_calculate_psi_data() {
    qDebug() << "Interface::m_calculate_psi_data()";
    QList<QString> date_list = {};
    { /* 计算psi_data */
        QMap<QString, QMap<QString, QVariant>> append_data = {};
        QMap<QString, QMap<QString, QVariant>> psi_data = Data::m_class_object->m_psi_data;
        int calculate_week_number = -1;
        for (int it1 = 0; it1 < Data::m_class_object->m_time_axis_by_day.size(); it1++) {
            auto it1_map = Data::m_class_object->m_time_axis_by_day[it1];
            if (calculate_week_number != -1 && it1_map["week_number"].toInt() != calculate_week_number) break;
            if (it1_map["is_locked"].toBool()) continue;
            QString it_date = it1_map["date"].toString();
            for (int it2 = 0; it2 < Data::m_class_object->m_line_list.size(); it2++) {
                if (Data::m_class_object->m_line_list[it2]["psi_type"] != "P(Total)") continue;
                QString block_info = Data::m_class_object->m_line_list[it2]["block_info"].toString();
                int start_index = it2, end_index = it2, product_count = 0;
                { /* 计算end_index和product_count */
                    while (++end_index < Data::m_class_object->m_line_list.size()) {
                        if (Data::m_class_object->m_line_list[end_index]["block_info"] != block_info) break;
                        if (Data::m_class_object->m_line_list[end_index]["psi_type"] == "P") product_count++;
                    }
                    end_index--;
                }
                QString p_total, s_total, i_total, dos_total, claim_inventory, promo_price, front_margin, unit_price_contribution, price_contribution, TTL_contribution, flyer, instore_A4, bundle, bundle_investment, tasso_zero, tasso_zero_investment, clerk_incentive, clerk_incentive_total_investment, trade_in, trade_in_investment, TV_campaign, TV_campaign_investment, tax, RRP, RRP_front_margin, TP, promo_TP, revuenue, distributor_margin, distributor_margin_value, landed, CDF, TTL_CDF, back_margin, TTL_back_margin, back_margin_value, PnL;
                { /* 计算单独颜色的p、s、i、dos */
                    for (int it3 = start_index; it3 <= end_index; it3++) {
                        if (Data::m_class_object->m_line_list[it3]["psi_type"] != "P") continue;
                        QString line_info_prefix = block_info + Data::m_class_object->m_line_list[it3]["SKU"].toString();
                        QString p, s, i, dos;
                        { /* 获取p */
                            p = psi_data[line_info_prefix + "P"][it_date].toString();
                        }
                        { /* 获取s */
                            s = psi_data[line_info_prefix + "S"][it_date].toString();
                        }
                        { /* 计算i */
                            QDate date = QDate::fromString(it_date, "yyyy-MM-dd");
                            QDate last_date = date.addDays(-1);
                            if (last_date < QDate::fromString("2018-12-31", "yyyy-MM-dd")) {
                                last_date = QDate::fromString("2018-12-31", "yyyy-MM-dd");
                            }
                            QString last_date_str = last_date.toString("yyyy-MM-dd");
                            double last_i = 0;
                            if (append_data.contains(line_info_prefix + "I") && append_data[line_info_prefix + "I"].contains(last_date.toString())) {
                                last_i = append_data[line_info_prefix + "I"][last_date_str].toDouble();
                            } else {
                                last_i = psi_data[line_info_prefix + "I"][last_date_str].toDouble();
                            }
                            if (!(p.isEmpty() || s.isEmpty())) {
                                i = QString::number(last_i + p.toDouble() - s.toDouble());
                            }
                        }
                        { /* 计算dos */
                            QDate date = QDate::fromString(it_date, "yyyy-MM-dd");
                            double sum_s = 0;
                            for (int it4 = 1; it4 <= 28; it4++) {
                                QDate tmp_date = date.addDays(0 - it4);
                                if (tmp_date < QDate::fromString("2018-12-31", "yyyy-MM-dd")) {
                                    tmp_date = QDate::fromString("2018-12-31", "yyyy-MM-dd");
                                }
                                QString tmp_date_str = tmp_date.toString("yyyy-MM-dd");
                                if (append_data.contains(line_info_prefix + "S") && append_data[line_info_prefix + "S"].contains(tmp_date_str)) {
                                    sum_s += append_data[line_info_prefix + "S"][tmp_date_str].toDouble();
                                } else {
                                    sum_s += psi_data[line_info_prefix + "S"][tmp_date_str].toDouble();
                                }
                            }
                            if (!(i.isEmpty() || sum_s == 0)) {
                                dos = QString::number(i.toDouble() / (sum_s / 28));
                            }
                        }
                        append_data[line_info_prefix + "P"][it_date] = p;
                        append_data[line_info_prefix + "S"][it_date] = s;
                        append_data[line_info_prefix + "I"][it_date] = i;
                        append_data[line_info_prefix + "DOS"][it_date] = dos;
                        { /* 计算total */
                            if (!(p.isEmpty())) {
                                p_total = QString::number(p_total.toDouble() + p.toDouble());
                            }
                            if (!(s.isEmpty())) {
                                s_total = QString::number(s_total.toDouble() + s.toDouble());
                            }
                            if (!(i.isEmpty())) {
                                i_total = QString::number(i_total.toDouble() + i.toDouble());
                            }
                        }
                    }
                }
                if (p_total.isEmpty() || s_total.isEmpty()) continue;
                Data::m_class_object->m_time_axis_by_day[it1]["is_locked"] = true;
                calculate_week_number = Data::m_class_object->m_time_axis_by_day[it1]["week_number"].toInt();
                { /* 储存p_total、s_total、i_total，计算dos_total */
                    append_data[block_info + "TotalP(Total)"][it_date] = p_total;
                    append_data[block_info + "TotalS(Total)"][it_date] = s_total;
                    append_data[block_info + "TotalI(Total)"][it_date] = i_total;
                    if (!(p_total.isEmpty() || s_total.isEmpty() || i_total.isEmpty())) {
                        // DOS = I / ( 过去28天S的和 / 28 )
                        QDate date = QDate::fromString(it_date, "yyyy-MM-dd");
                        double sum_s = 0;
                        for (int it4 = 1; it4 <= 28; it4++) {
                            QDate tmp_date = date.addDays(0 - it4);
                            if (tmp_date < QDate::fromString("2018-12-31", "yyyy-MM-dd")) {
                                tmp_date = QDate::fromString("2018-12-31", "yyyy-MM-dd");
                            }
                            QString tmp_date_str = tmp_date.toString("yyyy-MM-dd");
                            if (append_data.contains(block_info + "TotalS(Total)") && append_data[block_info + "TotalS(Total)"].contains(tmp_date_str)) {
                                sum_s += append_data[block_info + "TotalS(Total)"][tmp_date_str].toDouble();
                            } else {
                                sum_s += psi_data[block_info + "TotalS(Total)"][tmp_date_str].toDouble();
                            }
                        }
                        if (!(sum_s == 0)) {
                            dos_total = QString::number(i_total.toDouble() / (sum_s / 28));
                        }
                        append_data[block_info + "TotalDOS(Total)"][it_date] = dos_total;
                    }
                }
                { /* 计算需要上传录入、手动输入的值 */
                    claim_inventory = psi_data[block_info + "Total回传库存"][it_date].toString();
                    promo_price = psi_data[block_info + "Total促销价"][it_date].toString();
                    front_margin = psi_data[block_info + "Total前返"][it_date].toString();
                    flyer = psi_data[block_info + "TotalFlyer"][it_date].toString();
                    instore_A4 = psi_data[block_info + "Total店内A4"][it_date].toString();
                    bundle = psi_data[block_info + "Total单台绑赠"][it_date].toString();
                    tasso_zero = psi_data[block_info + "Total免息分期费率"][it_date].toString();
                    clerk_incentive = psi_data[block_info + "Total单台店员激励"][it_date].toString();
                    trade_in = psi_data[block_info + "Total单台以旧换新投入"][it_date].toString();
                    TV_campaign_investment = psi_data[block_info + "TotalTV广告总投入"][it_date].toString();
                    tax = psi_data[block_info + "Total税"][it_date].toString();
                    RRP = psi_data[block_info + "Total开盘价"][it_date].toString();
                    RRP_front_margin = psi_data[block_info + "Total开盘前返"][it_date].toString();
                    distributor_margin = psi_data[block_info + "Total代理商点位"][it_date].toString();
                    landed = psi_data[block_info + "Total授权成本"][it_date].toString();
                    back_margin = psi_data[block_info + "Total后返"][it_date].toString();
                }
                { /* 公式计算 */
                    if (!(RRP.isEmpty() || RRP_front_margin.isEmpty() || tax.isEmpty())) {
                        // 采购价 = 开盘价 / (1+税) * (1-开盘前返)
                        TP = QString::number(RRP.toDouble() / (1 + tax.toDouble()) * (1 - RRP_front_margin.toDouble()));
                        append_data[block_info + "TotalTP"][it_date] = TP;
                    }
                    if (!(promo_price.isEmpty() || front_margin.isEmpty() || tax.isEmpty())) {
                        // 虚拟采购价 = 促销价 / (1+税) * (1-前返)
                        promo_TP = QString::number(promo_price.toDouble() / (1 + tax.toDouble()) * (1 - front_margin.toDouble()));
                        append_data[block_info + "TotalPromo_TP"][it_date] = promo_TP;
                    }
                    if (!(TP.isEmpty() || promo_TP.isEmpty())) {
                        // 单台促销投入 = 采购价 - 虚拟采购价
                        unit_price_contribution = QString::number(TP.toDouble() - promo_TP.toDouble());
                        append_data[block_info + "Total单台促销投入"][it_date] = unit_price_contribution;
                    }
                    if (!(unit_price_contribution.isEmpty() || s_total.isEmpty())) {
                        // 促销总投入 = 单台促销投入 * S
                        price_contribution = QString::number(unit_price_contribution.toDouble() * s_total.toDouble());
                        append_data[block_info + "Total促销总投入"][it_date] = price_contribution;
                    }
                    if (!(bundle.isEmpty() || s_total.isEmpty())) {
                        // 绑赠总投入 = 单台绑赠 * S
                        bundle_investment = QString::number(bundle.toDouble() * s_total.toDouble());
                        append_data[block_info + "Total绑赠总投入"][it_date] = bundle_investment;
                    }
                    if (!(promo_price.isEmpty() || tasso_zero.isEmpty() || s_total.isEmpty())) {
                        // 免息分期总投入 = 促销价 * 免息分期费率 * S
                        tasso_zero_investment = QString::number(promo_price.toDouble() * tasso_zero.toDouble() * s_total.toDouble());
                        append_data[block_info + "Total免息分期总投入"][it_date] = tasso_zero_investment;
                    }
                    if (!(clerk_incentive.isEmpty() || s_total.isEmpty())) {
                        // 店员激励总投入 = 单台店员激励 * S
                        clerk_incentive_total_investment = QString::number(clerk_incentive.toDouble() * s_total.toDouble());
                        append_data[block_info + "Total店员激励总投入"][it_date] = clerk_incentive_total_investment;
                    }
                    if (!(trade_in.isEmpty() || s_total.isEmpty())) {
                        // 以旧换新总投入 = 单台以旧换新投入 * S
                        trade_in_investment = QString::number(trade_in.toDouble() * s_total.toDouble());
                        append_data[block_info + "Total以旧换新总投入"][it_date] = trade_in_investment;
                    }
                    if (!(TV_campaign_investment.isEmpty() || s_total.isEmpty())) {
                        // 单台TV广告投入 = TV广告总投入 / S
                        TV_campaign = QString::number(TV_campaign_investment.toDouble() / s_total.toDouble());
                        append_data[block_info + "Total单台TV广告投入"][it_date] = TV_campaign;
                    }
                    if (!(price_contribution.isEmpty())) {
                        // 总投入 = 促销总投入 + 绑赠总投入 + 免息分期总投入 + 店员激励总投入 + 以旧换新总投入 + TV广告总投入
                        TTL_contribution = QString::number(price_contribution.toDouble() + bundle_investment.toDouble() + tasso_zero_investment.toDouble() + clerk_incentive_total_investment.toDouble() + trade_in_investment.toDouble() + TV_campaign_investment.toDouble());
                        append_data[block_info + "Total总投入"][it_date] = TTL_contribution;
                    }
                    if (!(TP.isEmpty() || p_total.isEmpty())) {
                        // 总收入 = 采购价 * P
                        revuenue = QString::number(TP.toDouble() * p_total.toDouble());
                        append_data[block_info + "Total总收入"][it_date] = revuenue;
                    }
                    if (!(TP.isEmpty() || distributor_margin.isEmpty())) {
                        // 代理商单台利润 = 采购价 * 代理商点位
                        distributor_margin_value = QString::number(TP.toDouble() * distributor_margin.toDouble());
                        append_data[block_info + "Total代理商单台利润"][it_date] = distributor_margin_value;
                    }
                    if (!(TP.isEmpty() || distributor_margin_value.isEmpty() || landed.isEmpty())) {
                        // 单台操盘费生成 = 采购价 - 代理商单台利润 - 授权成本
                        CDF = QString::number(TP.toDouble() - distributor_margin_value.toDouble() - landed.toDouble());
                        append_data[block_info + "Total单台操盘费生成"][it_date] = CDF;
                    }
                    if (!(CDF.isEmpty() || p_total.isEmpty())) {
                        // 操盘费总生成 = 单台操盘费生成 * P = 总收入 - 代理商总利润 - 总授权成本
                        TTL_CDF = QString::number(CDF.toDouble() * p_total.toDouble());
                        // TTL_CDF = QString::number(revuenue.toDouble() - distributor_margin_value.toDouble() - landed.toDouble());
                        append_data[block_info + "Total操盘费总生成"][it_date] = TTL_CDF;
                    }
                    if (!(revuenue.isEmpty() || TTL_contribution.isEmpty() || back_margin.isEmpty())) {
                        // 总后返 = ( 总收入 - 总投入 ) * 后返
                        TTL_back_margin = QString::number((revuenue.toDouble() - TTL_contribution.toDouble()) * back_margin.toDouble());
                        append_data[block_info + "Total总后返"][it_date] = TTL_back_margin;
                    }
                    if (!(TTL_back_margin.isEmpty() || s_total.isEmpty())) {
                        // 单台平均后返 = 总后返 / S
                        back_margin_value = QString::number(TTL_back_margin.toDouble() / s_total.toDouble());
                        append_data[block_info + "Total单台平均后返"][it_date] = back_margin_value;
                    }
                    if (!(revuenue.isEmpty() || distributor_margin_value.isEmpty() || landed.isEmpty() || TTL_contribution.isEmpty() || TTL_back_margin.isEmpty())) {
                        // 损益 = 总收入 - 代理商总利润 - 总授权成本 - 总投入 - 总后返
                        PnL = QString::number(revuenue.toDouble() - distributor_margin_value.toDouble() - landed.toDouble() - TTL_contribution.toDouble() - TTL_back_margin.toDouble());
                        append_data[block_info + "Total损益"][it_date] = PnL;
                    }
                }
            }
        }
        Data::m_class_object->m_append_data = append_data;
    }
    append_psi_data();
}

void Interface::m_export_psi_data_to_excel() {
    qDebug() << "Interface::m_export_psi_data_to_excel()";

    { /* 伪造psi_data.xlsx */
        QList<QList<QString>> write_list_list = {};
        { /* 伪造表头行 */
            QList<QString> one_list = {"区域", "国家", "渠道类型", "渠道", "下游渠道", "机型", "产品代码", "商品名", "内存", "颜色", "EAN", "ID", "SKU", "PSI TYPE"};
            for (auto it1_map: Data::m_class_object->m_time_axis_by_day) {
                one_list.append(it1_map["date"].toString());
            }
            write_list_list.append(one_list);
        }
        { /* 伪造Locked行 */
            QList<QString> one_list = {"区域", "国家", "渠道类型", "渠道", "下游渠道", "机型", "产品代码", "商品名", "内存", "颜色", "EAN", "ID", "SKU", "PSI TYPE"};
            for (auto it1_map: Data::m_class_object->m_time_axis_by_day) {
                if (it1_map["is_locked"].toBool()) {
                    one_list.append("Locked");
                } else {
                    one_list.append("");
                }
            }
            write_list_list.append(one_list);
        }
        { /* 伪造表体n行 */
            for (int it1 = 0; it1 < Data::m_class_object->m_line_list.size(); it1++) {
                QList<QString> line_list = {};
                auto it1_map = Data::m_class_object->m_line_list[it1];
                line_list.append(it1_map["region"].toString());
                line_list.append(it1_map["country"].toString());
                line_list.append(it1_map["channel_type"].toString());
                line_list.append(it1_map["channel"].toString());
                line_list.append(it1_map["sub_channel"].toString());
                line_list.append(it1_map["model"].toString());
                line_list.append(it1_map["product_code"].toString());
                line_list.append(it1_map["commercial_name"].toString());
                line_list.append(it1_map["RAM_ROM"].toString());
                line_list.append(it1_map["color"].toString());
                line_list.append(it1_map["EAN"].toString());
                line_list.append(it1_map["ID"].toString());
                line_list.append(it1_map["SKU"].toString());
                line_list.append(it1_map["psi_type"].toString());
                QMap<QString, QVariant> it2_map = Data::m_class_object->m_psi_data[it1_map["line_info"].toString()];
                for (auto it2 = it2_map.begin(); it2 != it2_map.end(); ++it2) {
                    line_list.append(it2.value().toString());
                }
                write_list_list.append(line_list);
            }
        }
        write_excel((IS_TESTING ? TEST_ROOT_DIR : "") + "psi_data_out.xlsx", write_list_list);
    }
}

void Interface::m_save_psi_data() {
    qDebug() << "Interface::m_save_psi_data()";

    { /* 伪造psi_data.xlsx */
        QList<QList<QString>> write_list_list = {};
        { /* 伪造表头行 */
            QList<QString> one_list = {"区域", "国家", "渠道类型", "渠道", "下游渠道", "机型", "产品代码", "商品名", "内存", "颜色", "EAN", "ID", "SKU", "PSI TYPE"};
            for (auto it1_map: Data::m_class_object->m_time_axis_by_day) {
                one_list.append(it1_map["date"].toString());
            }
            write_list_list.append(one_list);
        }
        { /* 伪造Locked行 */
            QList<QString> one_list = {"区域", "国家", "渠道类型", "渠道", "下游渠道", "机型", "产品代码", "商品名", "内存", "颜色", "EAN", "ID", "SKU", "PSI TYPE"};
            for (auto it1_map: Data::m_class_object->m_time_axis_by_day) {
                if (it1_map["is_locked"].toBool()) {
                    one_list.append("Locked");
                } else {
                    one_list.append("");
                }
            }
            write_list_list.append(one_list);
        }
        { /* 伪造表体n行 */
            for (int it1 = 0; it1 < Data::m_class_object->m_line_list.size(); it1++) {
                QList<QString> line_list = {};
                auto it1_map = Data::m_class_object->m_line_list[it1];
                line_list.append(it1_map["region"].toString());
                line_list.append(it1_map["country"].toString());
                line_list.append(it1_map["channel_type"].toString());
                line_list.append(it1_map["channel"].toString());
                line_list.append(it1_map["sub_channel"].toString());
                line_list.append(it1_map["model"].toString());
                line_list.append(it1_map["product_code"].toString());
                line_list.append(it1_map["commercial_name"].toString());
                line_list.append(it1_map["RAM_ROM"].toString());
                line_list.append(it1_map["color"].toString());
                line_list.append(it1_map["EAN"].toString());
                line_list.append(it1_map["ID"].toString());
                line_list.append(it1_map["SKU"].toString());
                line_list.append(it1_map["psi_type"].toString());
                QMap<QString, QVariant> it2_map = Data::m_class_object->m_psi_data[it1_map["line_info"].toString()];
                for (auto it2 = it2_map.begin(); it2 != it2_map.end(); ++it2) {
                    line_list.append(it2.value().toString());
                }
                write_list_list.append(line_list);
            }
        }
        write_excel((IS_TESTING ? TEST_ROOT_DIR : "") + "data/psi_data.xlsx", write_list_list);
    }
}



void Interface::onApiResponseReceived(QNetworkReply *reply, const QVariantMap &responseData) {
    if (!reply) {
        qWarning() << "SACError: Received response is null";
        return;
    }
    
    // 打印接收到的响应数据
    QString requestId = reply->property("requestId").toString();
    qDebug() << "Request ID:" << requestId;
    qDebug() << "Received responseData:" << responseData;

    if (false) {
    } else {
        qWarning() << "SACError: Unknown request type: " << requestId;
    }

    reply->deleteLater(); // 确保回复处理完毕后删除 QNetworkReply 对象, 防止内存泄漏
}

QList<QList<QString>> read_excel(QString target) {
    qDebug() << "read_excel()";
    if (target.isEmpty()) {
        qWarning() << "SACError: 未指定文件路径";
        return {};
    }
    if (!QFile::exists(target)) {
        qWarning() << "SACError: 文件不存在";
        return {};
    }
    QString file = QDir::toNativeSeparators(target);
    QString absolutePath = QDir::toNativeSeparators(QDir::current().absoluteFilePath(file));
    qDebug() << "文件路径:" << absolutePath;

    // 打开Excel进程、获取工作簿、工作表、单元格
    QAxObject* myExcel = new QAxObject("Excel.application");
    if (!myExcel) {
        qWarning() << "SACError: 无法创建Excel进程";
        return {};
    }
    myExcel->setProperty("DisplayAlerts", false); // 不显示警告
    QAxObject* workBooks = myExcel->querySubObject("WorkBooks"); // 获取工作簿集合
    // workBooks->dynamicCall("Open(const QString&)", absolutePath);
    QVariant opened = workBooks->dynamicCall("Open(const QString&, QVariant, QVariant)", absolutePath, QVariant(false), QVariant(true)); // 第二个参数表示不更新链接，第三个参数表示以只读方式打开文件
    if (!opened.isValid()) {
        qWarning() << "SACError: 无法打开文件";
        return {};
    }
    QAxObject* workBook = myExcel->querySubObject("ActiveWorkBook"); // 获取当前工作簿
    QAxObject* mySheets = workBook->querySubObject("Sheets"); // 获取工作表集合
    QAxObject* sheet = mySheets->querySubObject("Item(int)", 1); // 获取第一个工作表
    QAxObject* range = sheet->querySubObject("UsedRange"); // 获取使用范围
    int count_row = range->querySubObject("Rows")->dynamicCall("Count").toUInt(); // 获取行数
    int count_col = range->querySubObject("Columns")->dynamicCall("Count").toUInt(); // 获取列数
    qDebug() << "行数:" << count_row << "列数:" << count_col;

    QList<QList<QString>> table = {};
    { /* 准备数据 */
        QVariant result = range->dynamicCall("Value");
        QList<QVariant> result_list = result.toList();
        for (int it1 = 0; it1 < count_row; it1++) {
            QList<QString> line = {};
            QList<QVariant> row = result_list[it1].toList();
            for (int it2 = 0; it2 < count_col; it2++) {
                line.append(row[it2].toString());
            }
            table.append(line);
        }
    }

    // 关闭工作簿、结束进程
    workBook->dynamicCall("Close()"); // 关闭工作簿
    myExcel->dynamicCall("Quit()"); // 退出Excel进程

    return table;
}

bool write_excel(QString target, QList<QList<QString>> write_list_list) {
    qDebug() << "write_excel()";
    if (target.isEmpty()) {
        qWarning() << "SACError: 未指定文件路径";
        return false;
    }
    // if (QFile::exists(target)) {
    //     qWarning() << "SACError: 文件已存在";
    //     return false;
    // }
    if (write_list_list.isEmpty() || write_list_list[0].isEmpty()) {
        qWarning() << "SACError: 写入内容为空";
        return false;
    }
    QString file = QDir::toNativeSeparators(target);
    QString absolutePath = QDir::toNativeSeparators(QDir::current().absoluteFilePath(file));
    qDebug() << "文件路径:" << absolutePath;

    // 打开Excel进程，获取工作簿集合
    QAxObject* myExcell = new QAxObject("Excel.application"); // 创建Excel进程
    myExcell->setProperty("DisplayAlerts", false); // 不显示警告
    QAxObject* workbooks = myExcell->querySubObject("WorkBooks"); // 获取工作簿集合
    workbooks->dynamicCall("Add"); // 新建工作簿
    QAxObject* workbook = myExcell->querySubObject("ActiveWorkBook"); // 获取当前工作簿
    QAxObject* sheets = workbook->querySubObject("Sheets"); // 获取工作表集合
    QAxObject* sheet = sheets->querySubObject("Item(int)", 1); // 获取第一个工作表
    sheet->setProperty("Name", "Sheet 1"); // 设置工作表名称
    QAxObject* range = sheet->querySubObject("Range(const QString&)", "A1"); // 获取使用范围并指定起始单元格

    QVariant varData = {};
    { /* 准备数据 */
        QVariantList varRows = {};
        for (const QList<QString>& row : write_list_list) {
            QVariantList varRow;
            for (const QString& cell : row) {
                varRow << cell;
            }
            varRows << QVariant(varRow);
        }
        varData = QVariant(varRows);
    }
    range->querySubObject("Resize(int,int)", write_list_list.size(), write_list_list[0].size())->setProperty("Value", varData);
    qDebug() << "已填写" << write_list_list.size() << "行" << write_list_list[0].size() << "列";

    // 保存工作簿、关闭工作簿、结束进程
    workbook->dynamicCall("SaveAs(QString)", absolutePath); // 保存工作簿
    qDebug() << "已保存到" << absolutePath;
    workbook->dynamicCall("Close()"); // 关闭工作簿
    qDebug() << "已关闭工作簿";
    myExcell->dynamicCall("Quit()"); // 退出Excel进程
    return true;
}

void append_psi_data() {
    qDebug() << "append_psi_data()";

    { /* m_append_data -> m_psi_data */
        auto &psi_data = Data::m_class_object->m_psi_data;
        const auto &append_data = Data::m_class_object->m_append_data;
        
        for (auto it1 = append_data.begin(); it1 != append_data.end(); it1++) {
            const QString &append_line_info = it1.key();
            
            if (!psi_data.contains(append_line_info)) {
                psi_data[append_line_info] = {};
            }
            
            auto &psi_data_line = psi_data[append_line_info];
            for (auto it2 = it1.value().begin(); it2 != it1.value().end(); it2++) {
                psi_data_line[it2.key()] = it2.value();
            }
        }
    }

    // { /* m_psi_data -> m_cell_list */ 有bug不能放出
    //     QList<QMap<QString, QVariant>> cell_list;
    //     const auto &m_psi_data = Data::m_class_object->m_psi_data;
    //     const auto &line_list = Data::m_class_object->m_line_list;
    //     const auto &time_axis_by_day = Data::m_class_object->m_time_axis_by_day;

    //     for (const auto &it1_map : line_list) {
    //         const QString &line_info = it1_map["line_info"].toString();
    //         for (const auto &it2_map : time_axis_by_day) {
    //             const QString &date = it2_map["date"].toString();
    //             QString value;
    //             if (m_psi_data.contains(line_info) && m_psi_data[line_info].contains(date)) {
    //                 value = m_psi_data[line_info][date].toString();
    //             }
    //             cell_list.append({
    //                 {"c_y", it1_map["c_y"]},
    //                 {"c_x", it2_map["day_index"].toInt() * 70},
    //                 {"c_width", 70},
    //                 {"c_height", 20},
    //                 {"value", value}
    //             });
    //         }
    //     }
    //     Data::m_class_object->m_cell_list = cell_list;
    // }

    // { /* m_append_data -> m_psi_data */
    //     auto psi_data = Data::m_class_object->m_psi_data;
    //     for (auto it1 = Data::m_class_object->m_append_data.begin(); it1 != Data::m_class_object->m_append_data.end(); it1++) {
    //         QString append_line_info = it1.key();
    //         if (!psi_data.contains(append_line_info)) psi_data[append_line_info] = {};
    //         for (auto it2 = it1.value().begin(); it2 != it1.value().end(); it2++) {
    //             psi_data[append_line_info][it2.key()] = it2.value();
    //         }
    //     }
    //     Data::m_class_object->m_psi_data = psi_data;
    // }

    // { /* m_psi_data -> m_cell_list */
    //     QList<QMap<QString, QVariant>> cell_list = {};
    //     auto &m_psi_data = Data::m_class_object->m_psi_data;
    //     for (auto it1_map : Data::m_class_object->m_line_list) {
    //         for (auto it2_map : Data::m_class_object->m_time_axis_by_day) {
    //             QString line_info = it1_map["line_info"].toString();
    //             QString date = it2_map["date"].toString();
    //             QString value = "";
    //             if (m_psi_data.contains(line_info) && m_psi_data[line_info].contains(date)) {
    //                 value = m_psi_data[line_info][date].toString();
    //             }
    //             cell_list.append({
    //                 {"c_y", it1_map["c_y"]},
    //                 {"c_x", it2_map["day_index"].toInt() * 70},
    //                 {"c_width", 70},
    //                 {"c_height", 20},
    //                 {"value", value}
    //             });
    //         }
    //     }
    //     Data::m_class_object->m_cell_list = cell_list;
    // }
}

QDate parse_excel_date(const QString& date_str) {
    // 定义可能的日期格式
    QStringList date_formats = {
        "yyyy-MM-dd",
        "yyyy/MM/dd",
        "yyyy-MM-ddTHH:mm:ss.zzz",
        "yyyy-MM-ddTHH:mm:ss",
        "yyyy/MM/ddTHH:mm:ss.zzz",
        "yyyy/MM/ddTHH:mm:ss"
    };

    // 尝试使用每种格式进行解析
    for (const QString& format : date_formats) {
        QDateTime dateTime = QDateTime::fromString(date_str, format);
        if (dateTime.isValid()) {
            return dateTime.date();
        }
    }

    // 如果所有格式都无法解析，返回一个无效的 QDate
    return QDate();
}