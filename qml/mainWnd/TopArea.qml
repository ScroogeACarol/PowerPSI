import QtQuick
import QtQuick.Controls
import "qrc:/qml/common"
import Class.Data 1.0
import Class.Interface 1.0
import Class.ObjectPoint 1.0

Item {
    width: parent.width
    height: children[0].height
    Column {
        width: parent.width
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        z: 1
        SACLabel {
            anchors.horizontalCenter: parent.horizontalCenter
            text: "PowerPSI"
            font.pixelSize: 36
            font.bold: true
        }
        Item /* 占位 */ {
            width: parent.width
            height: 4
        }
        SACLabel {
            anchors.horizontalCenter: parent.horizontalCenter
            text: "v0.6"
            font.pixelSize: 18
        }
        Item /* 占位 */ {
            width: parent.width
            height: 12
        }
        Component.onCompleted: {
            ObjectPoint.menu_bar_parent = this;
        }
    }
    Rectangle /*背景色*/ {
        anchors.fill: parent
        color: "#CCCCCC"
    }
    SACButton /* 中英按钮 */ {
        width: 40
        height: 30
        anchors.right: parent.right
        anchors.rightMargin: 30
        anchors.top: parent.top
        anchors.topMargin: 10
        text: "中/En"
        fontSize: 18
        onClicked: {
            this.text = this.text === "中/En" ? "En/中" : "中/En";
        }
    }
}