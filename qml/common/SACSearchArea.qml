import QtQuick 2.14
import QtQuick.Controls 2.14
/*
    width | height: 宽高, 可用anchors控制
    backgroundColor | backgroundHotColor | backgroundFocusColor | backgroundFocusErrorColor | backgroundNoFocusNoEmptyColor: 搜索框的背景颜色, 默认透明
    radius: 搜索框的圆角半径, 默认0
    isLeftUpRadius | isLeftDownRadius | isRightUpRadius | isRightDownRadius: 单独控制圆角属性对搜索框的每个角是否生效, 默认全部生效
    backgroundBorderWidth: 搜索框的边框宽度, 默认1
    backgroundBorderColor | backgroundBorderHotColor | backgroundBorderFocusColor | backgroundBorderFocusErrorColor | backgroundBorderNoFocusNoEmptyColor: 搜索框的边框颜色, 默认黑色, 错误时红色
    backgroundItem: 搜索框背景附加组件, 默认为空; 注意该组件的高和宽会被强制设置为搜索框的高和宽
    leftItem | rightItem: 搜索框左\右方的附加组件, 存在默认样式; 注意该组件的高会被强制设置为搜索框剩余的高
    isLeftItemCalculated | isRightItemCalculated: 搜索框左\右方的附件组件是否参与输入块的宽度分配中, 默认参与
    textLeftPadding | textRightPadding: 搜索框的文本左右内边距, 若左/右附加组件不为空且参与宽度分配, 则默认10, 否则默认0
    maximumLength: 搜索框的最大字符数限制, 默认无限制
    limitValidator: 搜索框的限制正则表达式, 禁止不匹配的输入且会立即触发ErrorColor, 需要填入一个RegExpValidator, 默认为空
    [只读]text: 搜索框的文字, 可通过该属性获取搜索框此时的文字
    textControl: 可通过该属性控制搜索框此时的文字, 此值改变会触发text同步改变
    textColor | textFocusColor | textFocusErrorColor | textNoFocusNoEmptyColor: 搜索框的文字颜色, 默认黑色
    placeholderText: 搜索框的提示文字, 默认为空
    placeholderTextColor: 搜索框的提示文字颜色, 默认灰色
    selectedTextColor | selectionColor: 搜索框选择块的颜色, 默认灰底黑字
    fontSize: 搜索框的文字大小, 默认12
    [只读]textFocus: 可通过该属性获取搜索框的编辑状态
    textFocusTrigger: 可通过该属性触发搜索框的textFocus, 此值改变且为真时会触发一次聚焦, 默认为false
    cancelFocusTrigger: 可通过该属性触发取消搜索框的textFocus, 此值改变且为真时会触发一次聚焦, 默认为false
    [只读]showHotColor: 可通过该属性获取搜索框是否在HotColor状态
    [只读]showErrorColor: 可通过该属性获取搜索框是否在ErrorColor状态
    errorColorTrigger: 可通过该属性触发搜索框的ErrorColor, 此值改变且为真时会触发一次ErrorColor状态, 默认为false
    [只读]afterIllegalInput: 可通过该属性获取搜索框最后一次输入的合法性
*/
Item {
    id: root
    width: parent.width
    height: parent.height
    property color backgroundColor: "transparent"
    property color backgroundHotColor: "transparent"
    property color backgroundFocusColor: "transparent"
    property color backgroundFocusErrorColor: "transparent"
    property color backgroundNoFocusNoEmptyColor: "transparent"
    property real radius: 0
    property bool isLeftUpRadius: true
    property bool isLeftDownRadius: true
    property bool isRightUpRadius: true
    property bool isRightDownRadius: true
    property int backgroundBorderWidth: 1
    property color backgroundBorderColor: "black"
    property color backgroundBorderHotColor: "transparent"
    property color backgroundBorderFocusColor: "transparent"
    property color backgroundBorderFocusErrorColor: "red"
    property color backgroundBorderNoFocusNoEmptyColor: "transparent"
    property var backgroundItem: null
    property var leftItem: null
    property bool isLeftItemCalculated: true
    property var rightItem: default_right_item
    property bool isRightItemCalculated: true
    property real textLeftPadding: 0 + (this.leftItem && isLeftItemCalculated) ? 0 : 10
    property real textRightPadding: 0 + (this.rightItem && isRightItemCalculated) ? 0 : 10
    property int maximumLength: -1
    property var limitValidator: null // RegExpValidator {regExp: //}
    property string text: ""
    property string textControl: ""
    property color textColor: "black"
    property color textFocusColor: "transparent"
    property color textFocusErrorColor: "transparent"
    property color textNoFocusNoEmptyColor: "transparent"
    property string placeholderText: ""
    property color placeholderTextColor: "black"
    property color selectedTextColor: "black"
    property color selectionColor: "gray"
    property int fontSize: 12
    property bool textFocus: false
    property bool textFocusTrigger: false
    property bool cancelFocusTrigger: false
    property bool afterIllegalInput: false
    property bool showHotColor: false
    property bool showErrorColor: false
    property bool errorColorTrigger: false
    Item {
        anchors.fill: parent
        SACButton /* 边框、背景 */ {
            anchors.fill: parent
            enabled: false
            backgroundColor: root.get_background_color()
            radius: root.radius
            backgroundBorderWidth: root.backgroundBorderWidth
            backgroundBorderColor: root.get_background_border_color()
            isLeftUpRadius: root.isLeftUpRadius
            isLeftDownRadius: root.isLeftDownRadius
            isRightUpRadius: root.isRightUpRadius
            isRightDownRadius: root.isRightDownRadius
            foregroundItem: root.backgroundItem
        }
        Item /* 左区、输入区、右区 */ {
            anchors.fill: parent
            Item /* 左区 */ {
                id: left_loader
                width: children[0].width
                height: parent.height
                x: root.isLeftItemCalculated ? 0 : (0 - this.width)
                Loader {
                    width: (root.leftItem) ? children[0].width : 0
                    height: parent.height
                    sourceComponent: root.leftItem
                }
            }
            Item {
                width: parent.width - (root.isLeftItemCalculated ? left_loader.width : 0) - (root.isRightItemCalculated ? right_loader.width : 0)
                height: parent.height
                x: root.isLeftItemCalculated ? left_loader.width : 0
                Loader /* 输入区 */ {
                    id: inputTextField
                    width: parent.width
                    height: parent.height
                    sourceComponent: textFieldItem
                }
            }
            Item /* 右区 */ {
                id: right_loader
                width: children[0].width
                height: parent.height
                x: root.isRightItemCalculated ? (root.width - this.width) : root.width
                Loader {
                    width: (root.rightItem) ? children[0].width : 0
                    height: parent.height
                    sourceComponent: root.rightItem
                }
            }
        }
        MouseArea {
            anchors.fill: parent
            visible: (!root.textFocus && root.text.length <= 0)
            acceptedButtons: Qt.LeftButton
            hoverEnabled: true
            cursorShape: this.visible ? Qt.PointingHandCursor : Qt.IBeamCursor
            onContainsMouseChanged: {
                root.showHotColor = containsMouse;
            }
            onPressed: {
                root.textFocusTrigger = true;
            }
        }
    }
    Component {
        id: textFieldItem
        Item {
            property alias textField: text_field
            TextField {
                id: text_field
                property int fieldsStart: -1
                property int fieldsEnd: -1
                anchors.fill: parent
                background: Item {
                    anchors.fill: parent
                    MouseArea {
                        id: leave_word_mousearea
                        anchors.fill: parent
                        acceptedButtons: Qt.RightButton
                        cursorShape: Qt.IBeamCursor
                        onClicked: {
                            if (mouse.button == Qt.RightButton) {
                                text_field.forceActiveFocus();
                                var point = mapToItem(leave_word_mousearea, mouse.x, mouse.y);
                                menu_bar_thirt.menu_bar_x = point.x;
                                menu_bar_thirt.menu_bar_y = point.y - 4;
                                menu_bar_thirt.open();
                            }
                        }
                        NonFixedMenuBarPopup {
                            id: menu_bar_thirt
                            menu_bar_parent: parent
                            menu_bar_data: ["全选", "剪切", "复制", "粘贴"]
                            menu_bar_width: 70
                            menu_bar_height: 93
                            onClick_menu_bar_dataChanged: {
                                if (click_menu_bar_data == "全选") {
                                    text_field.selectAll();
                                } else if (click_menu_bar_data == "剪切") {
                                    if (text_field.selectedText.length <= 0) {
                                        return;
                                    }
                                    text_field.select(text_field.fieldsStart, text_field.fieldsEnd);
                                    text_field.cut();
                                } else if (click_menu_bar_data == "复制") {
                                    if (text_field.selectedText.length <= 0) {
                                        return;
                                    }
                                    text_field.select(text_field.fieldsStart, text_field.fieldsEnd);
                                    text_field.copy();
                                } else if (click_menu_bar_data == "粘贴") {
                                    text_field.paste();
                                }
                            }
                            onVisibleChanged: {
                                if (!visible) {
                                    text_field.fieldsStart = -1;
                                    text_field.fieldsEnd = -1;
                                    leave_word_mousearea.cursorShape = Qt.IBeamCursor;
                                    return;
                                }
                                leave_word_mousearea.cursorShape = Qt.ArrowCursor;
                            }
                        }
                    }
                }
                selectByMouse: true
                padding: 0
                leftPadding: root.textLeftPadding
                rightPadding: root.textRightPadding
                verticalAlignment: Text.AlignVCenter
                wrapMode: TextEdit.NoWrap
                autoScroll: true
                maximumLength: root.maximumLength
                validator: null
                text: root.text
                placeholderText: root.placeholderText
                color: root.get_text_color()
                selectedTextColor: root.selectedTextColor
                selectionColor: root.selectionColor
                placeholderTextColor: root.placeholderTextColor
                font.family: "Microsoft YaHei"
                font.pixelSize: root.fontSize
                onTextChanged: {
                    root.afterIllegalInput = false;
                    root.showErrorColor = false;
                    if (root.limitValidator && !this.text.match(root.limitValidator.regExp)) {
                        root.textChanged();
                        root.afterIllegalInput = true;
                        root.showErrorColor = true;
                        return;
                    }
                    root.text = text;
                }
                onActiveFocusChanged: {
                    if (activeFocus) {
                        root.afterIllegalInput = false;
                        root.showErrorColor = false;
                    }
                    root.textFocus = activeFocus;
                }
                onSelectedTextChanged: {
                    text_field.fieldsStart = text_field.selectionStart;
                    text_field.fieldsEnd = text_field.selectionEnd;
                }
                onCursorPositionChanged: {
                    if (text_field.selectionStart == text_field.selectionEnd) {
                        text_field.fieldsStart = -1;
                        text_field.fieldsEnd = -1;
                    }
                }
            }
            Connections {
                target: root
                onTextFocusTriggerChanged: {
                    if (root.textFocusTrigger) {
                        root.textFocusTrigger = false;
                        text_field.forceActiveFocus();
                    }
                }
            }
            Connections {
                target: root
                onCancelFocusTriggerChanged: {
                    if (root.cancelFocusTrigger) {
                        root.cancelFocusTrigger = false;
                        text_field.focus = false;
                    }
                }
            }
        }
    }
    Component {
        id: default_right_item
        Item {
            width: this.height
            visible: root.text.length > 0
            SACButton {
                anchors.centerIn: parent
                text: "✕"
                textColor: "#A9B4BE"
                fontSize: Math.floor(this.width / 2)
                onClicked: {
                    root.text = "";
                    root.textChanged();
                    root.cancelFocusTrigger = true;
                }
            }
        }
    }
    onTextControlChanged: {
        root.text = root.textControl;
    }
    onErrorColorTriggerChanged: {
        if (root.errorColorTrigger) {
            root.errorColorTrigger = false;
            root.showErrorColor = true;
        }
    }
    function get_background_color() {
        var backgroundColor_ = root.backgroundColor;
        var backgroundHotColor_ = Qt.colorEqual("transparent", root.backgroundHotColor) ? backgroundColor_ : root.backgroundHotColor;
        var backgroundFocusColor_ = Qt.colorEqual("transparent", root.backgroundFocusColor) ? backgroundColor_ : root.backgroundFocusColor;
        var backgroundFocusErrorColor_ = Qt.colorEqual("transparent", root.backgroundFocusErrorColor) ? backgroundFocusColor_ : root.backgroundFocusErrorColor;
        var backgroundNoFocusNoEmptyColor_ = Qt.colorEqual("transparent", root.backgroundNoFocusNoEmptyColor) ? backgroundColor_ : root.backgroundNoFocusNoEmptyColor;
        if (root.textFocus && root.showErrorColor) {
            return backgroundFocusErrorColor_;
        }
        if (root.textFocus) {
            return backgroundFocusColor_;
        }
        if (!root.textFocus && root.showHotColor) {
            return backgroundHotColor_;
        }
        if (!root.textFocus && root.text.length > 0) {
            return backgroundNoFocusNoEmptyColor_;
        }
        return backgroundColor_;
    }
    function get_background_border_color() {
        var backgroundBorderColor_ = root.backgroundBorderColor;
        var backgroundBorderHotColor_ = Qt.colorEqual("transparent", root.backgroundBorderHotColor) ? backgroundBorderColor_ : root.backgroundBorderHotColor;
        var backgroundBorderFocusColor_ = Qt.colorEqual("transparent", root.backgroundBorderFocusColor) ? backgroundBorderColor_ : root.backgroundBorderFocusColor;
        var backgroundBorderFocusErrorColor_ = Qt.colorEqual("transparent", root.backgroundBorderFocusErrorColor) ? backgroundBorderFocusColor_ : root.backgroundBorderFocusErrorColor;
        var backgroundBorderNoFocusNoEmptyColor_ = Qt.colorEqual("transparent", root.backgroundBorderNoFocusNoEmptyColor) ? backgroundBorderColor_ : root.backgroundBorderNoFocusNoEmptyColor;
        if (root.textFocus && root.showErrorColor) {
            return backgroundBorderFocusErrorColor_;
        }
        if (root.textFocus) {
            return backgroundBorderFocusColor_;
        }
        if (!root.textFocus && root.showHotColor) {
            return backgroundBorderHotColor_;
        }
        if (!root.textFocus && root.text.length > 0) {
            return backgroundBorderNoFocusNoEmptyColor_;
        }
        return backgroundBorderColor_;
    }
    function get_text_color() {
        var textColor_ = root.textColor;
        var textFocusColor_ = Qt.colorEqual("transparent", root.textFocusColor) ? textColor_ : root.textFocusColor;
        var textFocusErrorColor_ = Qt.colorEqual("transparent", root.textFocusErrorColor) ? textFocusColor_ : root.textFocusErrorColor;
        var textNoFocusNoEmptyColor_ = Qt.colorEqual("transparent", root.textNoFocusNoEmptyColor) ? textColor_ : root.textNoFocusNoEmptyColor;
        if (root.textFocus && root.showErrorColor) {
            return textFocusErrorColor_;
        }
        if (root.textFocus) {
            return textFocusColor_;
        }
        if (!root.textFocus && root.text.length > 0) {
            return textNoFocusNoEmptyColor_;
        }
        return textColor_;
    }
    function cancelFocus() {
        inputTextField.item.textField.focus = false;
    }
}