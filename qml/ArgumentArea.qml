import QtQuick
import QtQuick.Controls
import "qrc:/qml/common"
import Class.Data 1.0
import Class.Interface 1.0
import Class.ObjectPoint 1.0

Item {
    parent: ObjectPoint.argument_area_parent
    width: 60 * 9 + 20 + 60 * 4 + 20 + 100
    height: parent.height
    Column {
        width: parent.width
        spacing: 20
        Item {
            width: parent.width
            height: 60
            Repeater {
                model: Data.argument_head_axis
                delegate: Item {
                    width: modelData.c_width
                    height: parent.height
                    x: modelData.c_x
                    y: modelData.c_y
                    Rectangle {
                        visible: parent.width >= 60
                        anchors.fill: parent
                        color: "transparent"
                        border.color: "black"
                        border.width: 1
                    }
                    SACLabel {
                        width: parent.width
                        anchors.centerIn: parent
                        text: modelData.value
                        horizontalAlignment: Text.AlignHCenter
                        elide: Text.ElideMiddle
                        font.pixelSize: 12
                        font.bold: true
                    }
                }
            }
        }
        Flickable {
            id: flickable
            width: parent.width
            height: parent.parent.height - this.y
            contentWidth: this.width
            contentHeight: Data.edit_area_height
            flickableDirection: Flickable.VerticalFlick
            clip: true
            Item {
                width: flickable.width
                height: flickable.contentHeight
                x: 0
                y: 0
                Repeater {
                    model: Data.y_axis
                    delegate: Item {
                        width: modelData.c_width
                        height: 20
                        x: modelData.c_x
                        y: modelData.c_y
                        Rectangle {
                            visible: parent.width >= 60
                            anchors.fill: parent
                            color: "transparent"
                            border.width: 1
                            border.color: "black"
                        }
                        SACLabel {
                            width: parent.width
                            anchors.centerIn: parent
                            text: modelData.value
                            horizontalAlignment: Text.AlignHCenter
                            elide: Text.ElideMiddle
                            font.pixelSize: 10
                        }
                    }
                }
            }
            Component.onCompleted: {
                ObjectPoint.argument_flickable = this;
            }
            onContentYChanged: {
                Data.table_contentY = this.contentY;
            }
        }
    }
    Component.onCompleted: {
        ObjectPoint.argument_area = this;
    }
}