import QtQuick 2.14
import QtQuick.Controls 2.14
/*
    width | height: 宽高, 可用anchors控制
    scrollBarWidth: 滚动条的宽度, 默认8
    scrollBarAlwaysShow: 滚动条是否一直显示, 默认一直显示
    spacing: 间距, 默认0
    model: 数据模型
    delegate: 代理组件
*/
Item {
    id: root
    width: parent.width
    height: parent.height
    property int scrollBarWidth: 8
    property bool scrollBarAlwaysShow: true
    property real spacing: 0
    property var model: null
    property var delegate: null
    ScrollView {
        anchors.fill: parent
        clip: true
        ScrollBar.vertical.width: root.scrollBarWidth
        ScrollBar.vertical.policy: scrollBarAlwaysShow ? ScrollBar.AlwaysOn : ScrollBar.AsNeeded
        ScrollBar.horizontal.width: 0
        ScrollBar.horizontal.policy: ScrollBar.Off
        Column {
            width: parent.parent.parent.width
            ListView {
                width: parent.width
                height: this.contentHeight
                interactive: false
                spacing: root.spacing
                model: root.model
                delegate: root.delegate
            }
        }
    }
}