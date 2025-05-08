import QtQuick
import QtQuick.Controls
import "qrc:/qml/common"
import Class.Data 1.0
import Class.Interface 1.0
import Class.ObjectPoint 1.0

Item {
    parent: ObjectPoint.time_axis_area_parent
    width: parent.width - this.x
    height: 60
    x: ObjectPoint.argument_area.width + 20
    MouseArea /* 捕捉滑轮事件 */ {
        anchors.fill: parent
        acceptedButtons: Qt.NoButton
        hoverEnabled: true
        onWheel: (wheel) => handleWheel(wheel)
        function handleWheel(wheel) {
            wheel.accepted = false;
            flickable.flick(wheel.angleDelta.y * 3, 0);
        }
        Flickable {
            id: flickable
            anchors.fill: parent
            contentWidth: column.width
            contentHeight: this.height
            flickableDirection: Flickable.HorizontalFlick
            clip: true
            Column {
                id: column
                width: childrenRect.width
                Item /* 月 */ {
                    width: children[0].width
                    height: 20
                    Row {
                        height: parent.height
                        Repeater {
                            model: Data.time_axis_by_month
                            delegate: Item {
                                width: index > 0 ? 70 * modelData.month_size : 70
                                height: 20
                                Rectangle {
                                    anchors.fill: parent
                                    color: "transparent"
                                    border.color: "black"
                                    border.width: 1
                                }
                                SACLabel {
                                    visible: index > 0
                                    anchors.verticalCenter: parent.verticalCenter
                                    x: get_x()
                                    text: "    " +  modelData.month_value + "    "
                                    function get_x() {
                                        if (index == 0) return 0;
                                        var l_x = modelData.day_index * 70;
                                        var r_x = l_x + parent.width - this.width;
                                        if (false) {
                                        } else if (flickable.contentX + flickable.width < l_x) {
                                            return 0;
                                        } else if (flickable.contentX + flickable.width >= l_x && flickable.contentX < (l_x + r_x - flickable.width) / 2) {
                                            return Math.max(0, flickable.contentX - l_x + flickable.width - this.width);
                                        } else if (flickable.contentX >= (l_x + r_x - flickable.width) / 2 && flickable.contentX + this.width < (l_x + r_x + flickable.width) / 2) {
                                            return (r_x - l_x) / 2;
                                        } else if (flickable.contentX + this.width >= (l_x + r_x + flickable.width ) / 2 && flickable.contentX - this.width < r_x) {
                                            return Math.min(parent.width - this.width, flickable.contentX - l_x);
                                        } else if (flickable.contentX - this.width >= r_x) {
                                            return parent.width - this.width;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                Item /* 周 */ {
                    width: children[0].width
                    height: 20
                    Row {
                        height: parent.height
                        Repeater {
                            model: Data.time_axis_by_week
                            delegate: Item {
                                width: 70 * 7
                                height: 20
                                Rectangle {
                                    anchors.fill: parent
                                    color: "transparent"
                                    border.color: "black"
                                    border.width: 1
                                }
                                SACLabel {
                                    anchors.centerIn: parent
                                    text: "Week " + modelData.week_number
                                }
                            }
                        }
                    }
                }
                Item /* 日 */ {
                    width: children[0].width
                    height: 20
                    Row {
                        height: parent.height
                        Repeater {
                            model: Data.time_axis_by_day
                            delegate: Item {
                                width: 70
                                height: 20
                                Rectangle {
                                    anchors.fill: parent
                                    color: "transparent"
                                    border.color: "black"
                                    border.width: 1
                                }
                                SACLabel {
                                    anchors.centerIn: parent
                                    text: modelData.day
                                }
                            }
                        }
                    }
                }
            }
            Component.onCompleted: {
                ObjectPoint.time_axis_flickable = this;
            }
            onContentXChanged: {
                Data.table_contentX = this.contentX;
            }
        }
    }
    Component.onCompleted: {
        ObjectPoint.time_axis_area = this;
    }
}