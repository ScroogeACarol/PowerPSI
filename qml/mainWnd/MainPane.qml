import QtQuick
import QtQuick.Controls
import "qrc:/qml/common"
import Class.Data 1.0
import Class.Interface 1.0
import Class.ObjectPoint 1.0

Item {
    anchors.fill: parent
    anchors.margins: 20
    Column {
        width: parent.width
        spacing: 20
        TopArea {}
        Item /* 表格区域 */ {
            width: parent.width
            height: parent.parent.height - this.y
            Component.onCompleted: {
                ObjectPoint.argument_area_parent = this;
                ObjectPoint.time_axis_area_parent = this;
                ObjectPoint.editable_area_parent = this;
            }
        }
    }
}