import QtQuick
import QtQuick.Controls
import "qrc:/qml/common"
import Class.Data 1.0
import Class.Interface 1.0
import Class.ObjectPoint 1.0

Item {
    parent: ObjectPoint.editable_area_parent
    width: parent.width - this.x
    height: parent.height - this.y
    x: ObjectPoint.argument_area.width + 20
    y: ObjectPoint.time_axis_area.height + 20
    MouseArea /* 捕捉滑轮事件 */ {
        anchors.fill: parent
        acceptedButtons: Qt.NoButton
        hoverEnabled: true
        onWheel: (wheel) => handleWheel(wheel)
        function handleWheel(wheel) {
            wheel.accepted = false;
            flickable.flick(wheel.angleDelta.x * 6, wheel.angleDelta.y * 6);
            ObjectPoint.argument_flickable.flick(0, wheel.angleDelta.y * 6);
            ObjectPoint.time_axis_flickable.flick(wheel.angleDelta.x * 6, 0);
        }
        Flickable {
            id: flickable
            anchors.fill: parent
            contentWidth: Data.edit_area_width
            contentHeight: Data.edit_area_height
            contentX: Data.table_contentX
            contentY: Data.table_contentY
            interactive: false
            clip: true
            Item {
                width: flickable.contentWidth
                height: flickable.contentHeight
                Repeater {
                    model: Data.cell_list
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
        }
    }
}