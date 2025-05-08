import QtQuick 2.14
import QtQuick.Controls 2.14
/*
    // 本质是一个Row, 具备正常MouseArea的所有属性和信号
*/
Row {
    height: parent.height
    Component.onCompleted: {
        forceLayout();
        // for (var i = 0; i < this.children.length; i++) {
        //     this.children[i].x = this.children[i].mapToItem(this, 0, 0).x;
        // }
    }
}