import QtQml 2.12
import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

Item {
	property var color: "#EE82EE"
	property var outsideColor: "#EE82EE"
	width: 0
	height: 0
	z: 999
	visible: true
	Rectangle /* 边框 */ {
		width: parent.parent.width
		height: parent.parent.height
		color: "transparent"
		border.color: parent.color
		border.width: 1
	}
	Rectangle /* 框外框（超范围边框） */ {
		width: parent.parent.width + 2
		height: parent.parent.height + 2
		x: -1
		y: -1
		color: "transparent"
		border.color: parent.outsideColor
		border.width: 1
	}
	Timer {
		interval: 3000
		repeat: true
		running: true
		onTriggered: {
			parent.visible = !parent.visible;
		}
	}
}