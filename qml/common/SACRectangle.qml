import QtQuick 2.14
import QtQuick.Controls 2.14
/*
    width | height: 宽高, 可用anchors控制
    color: 填充颜色, 默认透明, 修改后会自动重绘
    radius: 圆角半径, 默认无圆角
    borderWidth: 边框宽度, 默认无边框
    borderColor: 边框颜色, 默认透明, 修改后会自动重绘
    isLeftUpRadius | isLeftDownRadius | isRightUpRadius | isRightDownRadius: 单独控制圆角属性对每个角是否生效, 默认全部生效
*/
Item {
    // TODO: 改为4个圆角数值单独控制未做
    id: root
    width: parent.width
    height: parent.width
    property color color: "transparent"
    property real radius: 0
    property int borderWidth: 0
    property color borderColor: "transparent"
    property bool isLeftUpRadius: true
    property bool isLeftDownRadius: true
    property bool isRightUpRadius: true
    property bool isRightDownRadius: true
    property var repaint: binding_for_repaint()
    Canvas /* 填充 */ {
        id: canvas_fill
        anchors.fill: parent
        anchors.margins: Math.floor(root.borderWidth / 4)
        contextType: "2d"
        onPaint: {
            var context = getContext("2d");
            if (root.width <= 0 || root.height <= 0) {
                return;
            }
            context.clearRect(0, 0, this.width, this.height);
            if (Qt.colorEqual("transparent", root.color)) {
                return;
            }
            var rootRadius = Math.min(root.radius, Math.min(this.width, this.height));
            context.fillStyle = root.color;
            context.beginPath();
            context.moveTo(rootRadius, 0);
            context.lineTo(this.width - rootRadius, 0);
            if (root.isRightUpRadius) {
                context.arc(this.width - rootRadius, rootRadius, rootRadius, 1.5 * Math.PI, 0 * Math.PI, false);
            } else {
                context.lineTo(this.width, 0);
                context.lineTo(this.width, rootRadius);
            }
            context.lineTo(this.width, this.height - rootRadius);
            if (root.isRightDownRadius) {
                context.arc(this.width - rootRadius, this.height - rootRadius, rootRadius, 0 * Math.PI, 0.5 * Math.PI, false);
            } else {
                context.lineTo(this.width, this.height);
                context.lineTo(this.width - rootRadius, this.height);
            }
            context.lineTo(rootRadius, this.height);
            if (root.isLeftDownRadius) {
                context.arc(rootRadius, this.height - rootRadius, rootRadius, 0.5 * Math.PI, 1 * Math.PI, false);
            } else {
                context.lineTo(0, this.height);
                context.lineTo(0, this.height - rootRadius);
            }
            context.lineTo(0, rootRadius);
            if (root.isLeftUpRadius) {
                context.arc(rootRadius, rootRadius, rootRadius, 1 * Math.PI, 1.5 * Math.PI, false);
            } else {
                context.lineTo(0, 0);
                context.lineTo(rootRadius, 0);
            }
            context.fill();
        }
    }
    Canvas /* 边框 */ {
        id: canvas_border
        anchors.fill: parent
        contextType: "2d"
        onPaint: {
            var context = getContext("2d");
            if (root.width <= 0 || root.height <= 0) {
                return;
            }
            context.clearRect(0, 0, this.width, this.height);
            if (Qt.colorEqual("transparent", root.borderColor) || root.borderWidth <= 0) {
                return;
            }
            var rootRadius = Math.min(root.radius, Math.min(this.width, this.height));
            context.strokeStyle = root.borderColor;
            context.beginPath();
            context.lineWidth = 2 * root.borderWidth;
            context.moveTo(0, 0);
            if (!root.isLeftUpRadius) {
                context.lineTo(rootRadius, 0);
            } else {
                context.moveTo(rootRadius, 0);
            }
            context.lineTo(this.width - rootRadius, 0);
            if (!root.isRightUpRadius) {
                context.lineTo(this.width, 0);
                context.lineTo(this.width, rootRadius);
            } else {
                context.moveTo(this.width, rootRadius);
            }
            context.lineTo(this.width, this.height - rootRadius);
            if (!root.isRightDownRadius) {
                context.lineTo(this.width, this.height);
                context.lineTo(this.width - rootRadius, this.height);
            } else {
                context.moveTo(this.width - rootRadius, this.height);
            }
            context.lineTo(rootRadius, this.height);
            if (!root.isLeftDownRadius) {
                context.lineTo(0, this.height);
                context.lineTo(0, this.height - rootRadius);
            } else {
                context.moveTo(0, this.height - rootRadius);
            }
            context.moveTo(0, this.height - rootRadius);
            context.lineTo(0, rootRadius);
            if (!root.isLeftUpRadius) {
                context.lineTo(0, 0);
            }
            context.stroke();
        }
    }
    Canvas /* 圆角 */ {
        id: canvas_radius
        anchors.fill: parent
        contextType: "2d"
        onPaint: {
            var context = getContext("2d");
            if (root.width <= 0 || root.height <= 0) {
                return;
            }
            context.clearRect(0, 0, this.width, this.height);
            if (Qt.colorEqual("transparent", root.borderColor) || root.borderWidth <= 0) {
                return;
            }
            var rootRadius = Math.min(root.radius, Math.min(this.width, this.height));
            context.strokeStyle = root.borderColor;
            context.beginPath();
            context.lineWidth = root.borderWidth;
            context.moveTo(this.width - rootRadius, 0);
            if (root.isRightUpRadius) {
                context.arc(this.width - rootRadius - root.borderWidth / 2, rootRadius + root.borderWidth / 2, rootRadius, 1.5 * Math.PI, 0 * Math.PI, false);
            }
            context.moveTo(this.width, this.height - rootRadius);
            if (root.isRightDownRadius) {
                context.arc(this.width - rootRadius - root.borderWidth / 2, this.height - rootRadius - root.borderWidth / 2, rootRadius, 0 * Math.PI, 0.5 * Math.PI, false);
            }
            context.moveTo(rootRadius, this.height);
            if (root.isLeftDownRadius) {
                context.arc(rootRadius + root.borderWidth / 2, this.height - rootRadius - root.borderWidth / 2, rootRadius, 0.5 * Math.PI, 1 * Math.PI, false);
            }
            context.moveTo(0, rootRadius);
            if (root.isLeftUpRadius) {
                context.arc(rootRadius + root.borderWidth / 2, rootRadius + root.borderWidth / 2, rootRadius, 1 * Math.PI, 1.5 * Math.PI, false);
            }
            context.stroke();
        }
    }
    function binding_for_repaint() {
        this.width;
        this.height;
        this.color;
        this.radius;
        this.borderWidth;
        this.borderColor;
        this.isLeftUpRadius;
        this.isLeftDownRadius;
        this.isRightUpRadius;
        this.isRightDownRadius;
        canvas_fill.requestPaint();
        canvas_border.requestPaint();
        canvas_radius.requestPaint();
        return true;
    }
}