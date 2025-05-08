import QtQuick
import QtQuick.Controls
import "qrc:/qml/common"
import Class.Data 1.0
import Class.Interface 1.0
import Class.ObjectPoint 1.0

Item {
    parent: ObjectPoint.menu_bar_parent
    width: children[0].width
    height: 40
    anchors.horizontalCenter: parent.horizontalCenter
    Row {
        height: parent.height
        spacing: 40
        Repeater {
            model: ["初始化读取data", "导入IN_PSI_SO.xlsx", "导入IN_PSI_ST.xlsx", "自动计算最后一周", "导出psi_data_out.xlsx", "记忆并保存data"]
            delegate: Item {
                width: 140
                height: parent.height
                SACButton {
                    backgroundColor: "#DDDDDD"
                    backgroundBorderWidth: 1
                    backgroundBorderColor:"black"
                    text: modelData
                    fontSize: 12
                    textColor: "black"
                    onClicked: {
                        switch (index) {
                            case 0: {
                                Interface.m_parse_customer_and_product_from_excel();
                                Interface.m_parse_psi_data_from_excel();
                                console.log("初始化读取data完成");
                                break;
                            }
                            case 1: {
                                Interface.m_parse_so_data_from_excel();
                                console.log("导入IN_PSI_SO.xlsx完成");
                                break;
                            }
                            case 2: {
                                Interface.m_parse_st_data_from_excel();
                                console.log("导入IN_PSI_ST.xlsx完成");
                                break;
                            }
                            case 3: {
                                Interface.m_calculate_psi_data();
                                console.log("自动计算最后一周完成");
                                break;
                            }
                            case 4: {
                                Interface.m_export_psi_data_to_excel();
                                console.log("导出psi_data_out.xlsx完成");
                                break;
                            }
                            case 5: {
                                Interface.m_save_psi_data();
                                console.log("记忆并保存data完成");
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
}