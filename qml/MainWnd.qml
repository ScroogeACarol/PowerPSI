import QtQuick
import QtQuick.Controls
import "qrc:/qml/common"
import Class.Data 1.0
import Class.Interface 1.0
import Class.ObjectPoint 1.0
import "mainWnd"

Window {
    id: window
    visible: true
    width: 1360
    height: 150 // 600
    title: qsTr("PowerPSI")
    Item {
        width: window.width
        height: window.height
        MouseArea /* 焦点重置 */ {
            anchors.fill: parent
            acceptedButtons: Qt.AllButtons
            hoverEnabled: true
            onPressed: (mouse) => handlePressed(mouse)
            function handlePressed(mouse) {
                parent.forceActiveFocus();
                mouse.accepted = false;
            }
        }
        Rectangle /* 背景 */ {
            anchors.fill: parent
            color: "#CCCCCC"
        }
        MainPane {}
    }
}