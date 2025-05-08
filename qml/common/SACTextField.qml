import QtQuick 2.14
import QtQuick.Controls 2.14

Item {
    id: root
    property alias text_field: text_field
    property alias left_loader: left_loader
    property alias right_loader: right_loader
    width: parent.width
    height: parent.height
    Row {
        anchors.fill: parent
        Loader {
            id: left_loader
            width: 0
            height: parent.height
        }
        TextField {
            id: text_field
            width: parent.width - left_loader.width - right_loader.width
            height: parent.height
            x: left_loader.width
            background: null
            readOnly: false
            selectByMouse: true
            padding: 0
            leftPadding: 0
            rightPadding: 0
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: TextInput.AlignLeft
            wrapMode: TextEdit.NoWrap
            autoScroll: true
            maximumLength: -1
            echoMode: TextInput.Normal
            validator: null
            text: ""
            placeholderText: ""
            color: "black"
            selectedTextColor: "black"
            selectionColor: "gray"
            placeholderTextColor: "transparent"
            font.family: "Microsoft YaHei"
            font.pixelSize: 12
            Label /* placeholderText */ {
                visible: Qt.colorEqual("transparent", parent.placeholderTextColor) && parent.text.length == 0
                anchors.verticalCenter: parent.verticalCenter
                x: parent.leftPadding
                text: parent.placeholderText
                color: "gray"
                font.family: "Microsoft YaHei"
                font.pixelSize: parent.font.pixelSize
            }
        }
        Loader {
            id: right_loader
            width: 0
            height: parent.height
        }
    }
}