import QtQuick 2.14
import QtQuick.Controls 2.14

Item {
    id: root_item
    property double left_top_width: 0
    property double left_top_height: 0
    property double right_bottom_width: 0
    property double right_bottom_height: 0
    property alias source: center_image.source
    property alias color: center_rect.color
    property alias left_top_image: left_top_image
    property alias right_top_image: right_top_image
    property alias left_bottom_image: left_bottom_image
    property alias right_bottom_image: right_bottom_image
    property alias left_image: left_image
    property alias right_image: right_image
    property alias top_image: top_image
    property alias bottom_image: bottom_image
    property alias center_image: center_image
    property alias center_rect: center_rect
    property double radius: 0
    property var background_color: "transparent"
    property double background_border_width: 0
    property var background_border_color: "transparent"
    Rectangle {
        id: left_top_rect
        width: root_item.left_top_width
        height: root_item.left_top_height
        anchors.left: parent.left
        anchors.top: parent.top
        radius: root_item.radius
        color: root_item.background_color
        border.width: root_item.background_border_width
        border.color: root_item.background_border_color
        Image {
            id: left_top_image
            anchors.fill: parent
        }
    }
    Rectangle {
        id: right_top_rect
        width: root_item.right_bottom_width
        height: root_item.left_top_height
        anchors.right: parent.right
        anchors.top: parent.top
        radius: root_item.radius
        color: root_item.background_color
        border.width: root_item.background_border_width
        border.color: root_item.background_border_color
        Image {
            id: right_top_image
            anchors.fill: parent
        }
    }
    Rectangle {
        id: left_bottom_rect
        width: root_item.left_top_width
        height: root_item.right_bottom_height
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        radius: root_item.radius
        color: root_item.background_color
        border.width: root_item.background_border_width
        border.color: root_item.background_border_color
        Image {
            id: left_bottom_image
            anchors.fill: parent
        }
    }
    Rectangle {
        id: right_bottom_rect
        width: root_item.right_bottom_width
        height: root_item.right_bottom_height
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        radius: root_item.radius
        color: root_item.background_color
        border.width: root_item.background_border_width
        border.color: root_item.background_border_color
        Image {
            id: right_bottom_image
            anchors.fill: parent
        }
    }
    Rectangle {
        id: left_rect
        width: root_item.left_top_width
        anchors.left: parent.left
        anchors.top: top_rect.bottom
        anchors.bottom: bottom_rect.top
        radius: root_item.radius
        color: root_item.background_color
        border.width: root_item.background_border_width
        border.color: root_item.background_border_color
        Image {
            id: left_image
            anchors.fill: parent
        }
    }
    Rectangle {
        id: right_rect
        width: root_item.right_bottom_width
        anchors.right: parent.right
        anchors.top: top_rect.bottom
        anchors.bottom: bottom_rect.top
        radius: root_item.radius
        color: root_item.background_color
        border.width: root_item.background_border_width
        border.color: root_item.background_border_color
        Image {
            id: right_image
            anchors.fill: parent
        }
    }
    Rectangle {
        id: top_rect
        height: root_item.left_top_height
        anchors.left: left_top_rect.right
        anchors.right: right_top_rect.left
        anchors.top: parent.top
        radius: root_item.radius
        color: root_item.background_color
        border.width: root_item.background_border_width
        border.color: root_item.background_border_color
        Image {
            id: top_image
            anchors.fill: parent
        }
    }
    Rectangle {
        id: bottom_rect
        height: root_item.right_bottom_height
        anchors.left: left_bottom_rect.right
        anchors.right: right_bottom_rect.left
        anchors.bottom: parent.bottom
        radius: root_item.radius
        color: root_item.background_color
        border.width: root_item.background_border_width
        border.color: root_item.background_border_color
        Image {
            id: bottom_image
            anchors.fill: parent
        }
    }
    Rectangle {
        id: center_rect
        anchors.left: left_rect.right
        anchors.right: right_rect.left
        anchors.top: top_rect.bottom
        anchors.bottom: bottom_rect.top
        radius: root_item.radius
        color: root_item.background_color
        border.width: 0
        border.color: root_item.background_border_color
        Image {
            id: center_image
            anchors.fill: parent
        }
    }
}