import QtQuick 2.14
/*
    width | height: 宽高, 可用anchors控制
	contentWidth | contentHeight: 滚动条的内容宽高, 默认与宽高相同
    backgroundColor: 滚动条的背景颜色, 默认透明
    backgroundRadius: 滚动条的背景圆角半径, 默认0
    backgroundBorderWidth: 滚动条的边框宽度, 默认1
    backgroundBorderColor: 滚动条的边框颜色, 默认黑色
	foregroundColor: 滚动条滑块的颜色, 默认透明
	foregroundRadius: 滚动条滑块的圆角半径, 默认0
	foregroundBorderWidth: 滚动条滑块的边框宽度, 默认1
	foregroundBorderColor: 滚动条滑块的边框颜色, 默认黑色
	[只读]scrollX | scrollY: 滚动条的当前位置
	scrollXControl | scrollYControl: 可通过该属性控制滚动条的滚动位置，不可绑定
*/
Item {
	id: root
	width: 0
	height: 0
	property var contentWidth: this.width
	property var contentHeight: this.height
	property var backgroundColor: "transparent"
	property var backgroundRadius: 0
	property var backgroundBorderWidth: 1
	property var backgroundBorderColor: "black"
	property var foregroundColor: "transparent"
	property var foregroundRadius: 0
	property var foregroundBorderWidth: 1
	property var foregroundBorderColor: "black"
	property var scrollX: 0
	property var scrollY: 0
	property var scrollXControl: 0
	property var scrollYControl: 0
	Rectangle /* 滚动条范围 */ {
		anchors.fill: parent
		color: root.backgroundColor
		border.width: root.backgroundBorderWidth
		border.color: root.backgroundBorderColor
		radius: root.backgroundRadius
		Rectangle /* 滚动条滑块 */ {
			id: slider
			width: parent.width * (parent.width >= root.contentWidth ? 1 : parent.width / root.contentWidth)
			height: parent.height * (parent.height >= root.contentHeight ? 1 : parent.height / root.contentHeight)
			x: 0
			y: 0
			color: root.foregroundColor
			border.width: root.foregroundBorderWidth
			border.color: root.foregroundBorderColor
			radius: root.foregroundRadius
			onXChanged: {
				root.scrollX = this.x;
			}
			onYChanged: {
				root.scrollY = this.y;
			}
		}
		MouseArea {
			anchors.fill: parent
			acceptedButtons: Qt.LeftButton
			cursorShape: this.enabled ? Qt.PointingHandCursor : Qt.ArrowCursor
			onPressed: {
				var tmp_x = (mouse.x - slider.width / 2);
				var tmp_y = (mouse.y - slider.height / 2);
				(tmp_x > root.width - slider.width) && (tmp_x = root.width - slider.width);
				(tmp_x < 0) && (tmp_x = 0);
				(tmp_y > root.height - slider.height) && (tmp_y = root.height - slider.height);
				(tmp_y < 0) && (tmp_y = 0);
				slider.x = tmp_x;
				slider.y = tmp_y;
			}
			onPositionChanged: {
				var tmp_x = (mouse.x - slider.width / 2);
				var tmp_y = (mouse.y - slider.height / 2);
				(tmp_x > root.width - slider.width) && (tmp_x = root.width - slider.width);
				(tmp_x < 0) && (tmp_x = 0);
				(tmp_y > root.height - slider.height) && (tmp_y = root.height - slider.height);
				(tmp_y < 0) && (tmp_y = 0);
				slider.x = tmp_x;
				slider.y = tmp_y;
			}
			onWheel: {
				wheel.accepted = false;
			}
		}
	}
	onScrollXControlChanged: {
		var tmp_x = root.scrollXControl;
		(tmp_x > root.width - slider.width) && (tmp_x = root.width - slider.width);
		(tmp_x < 0) && (tmp_x = 0);
		slider.x = tmp_x;
	}
	onScrollYControlChanged: {
		var tmp_y = root.scrollYControl;
		(tmp_y > root.height - slider.height) && (tmp_y = root.height - slider.height);
		(tmp_y < 0) && (tmp_y = 0);
		slider.y = tmp_y;
	}
}