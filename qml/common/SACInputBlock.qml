import QtQuick 2.14
import QtQuick.Controls 2.14
/*
    width | height: 宽高, 可用anchors控制
    usingMultyLineInput: 是否使用多行输入框, 默认使用单行输入框
    usingRichText: 是否使用富文本, 仅对多行输入框有效, 默认不使用
    isScrollable: 是否允许滚动, 仅对多行输入框有效, 默认允许
    backgroundColor | backgroundHotColor | backgroundFocusColor | backgroundErrorColor | backgroundMatchedColor | backgroundDisabledColor: 输入框的背景颜色, 默认透明
    radius: 输入框的圆角半径, 默认0
    isLeftUpRadius | isLeftDownRadius | isRightUpRadius | isRightDownRadius: 单独控制圆角属性对输入框的每个角是否生效, 默认全部生效
    borderWidth: 输入框的边框宽度, 默认1
    borderColor | borderHotColor | borderFocusColor | borderErrorColor | borderMatchedColor | borderDisabledColor: 输入框的边框颜色, 默认灰色, 聚焦时黑色, 错误时红色, 完全匹配时绿色
    topItem | bottomItem: 输入框上\下方的附加组件, 默认为空; 注意该组件的宽会被强制设置为输入块的宽
    isTopItemCalculated | isBottomItemCalculated: 输入框上\下方的附件组件是否参与输入块的高度分配中, 默认不参与
    leftItem | rightItem: 输入框左\右方的附加组件, 默认为空; 注意该组件的高会被强制设置为输入框剩余的高
    isLeftItemCalculated | isRightItemCalculated: 输入框左\右方的附件组件是否参与输入块的宽度分配中, 默认不参与
    middleItem: 输入框前景附加组件, 默认为空; 注意该组件的高和宽会被强制设置为输入框剩余的高和宽
    textLeftPadding | textRightPadding: 输入框的文本左右内边距, 默认10
    textTopPadding | textBottomPadding: 输入框的文本上下内边距, 仅对多行输入框有效, 默认4
    scrollBarVWidth: 输入框的垂直滚动条宽度, 仅对多行输入框有效, 默认6
    textVerticalAlignment: 用于使文字垂直与输入框、偏上或是偏下，参数有Text.AlignTop、Text.AlignBottom，默认参数为Text.AlignVCenter
    isReadOnly: 输入框是否只读, 默认非只读
    maximumLength: 输入框的最大字符数限制, 仅对单行输入框有效, 默认无限制
    echoMode: 输入框的显示模式, 默认正常显示, 主要是密码框存在使用需要
    horizontalAlignment: 输入框的水平对齐方式, 1-左对齐 | 2-居中 | 3-右对齐, 默认左对齐
    limitValidator: 输入框的限制正则表达式, 禁止不匹配的输入且会立即触发ErrorColor, 匹配的输入会触发MatchColor, 需要填入一个RegExpValidator, 默认为空
    matchedValidator: 输入框的匹配正则表达式, 匹配的输入会触发MatchColor, 需要填入一个RegExpValidator, 默认为空
    [只读]text: 输入框的文字, 可通过该属性获取输入框此时的文字, 对使用富文本的多行输入框无效 
    [只读]richText: 可通过该属性获取输入框此时的富文本文字, 仅对使用富文本的多行输入框有效
    textControl: 可通过该属性控制输入框此时的文字, 此值改变会触发text同步改变
    [只读]textContentHeight: 可通过该属性获取输入框此时的文字高度, 仅对使用富文本的多行输入框有效
    textColor | textHotColor | textFocusColor | textErrorColor | textMatchedColor | textDisabledColor: 输入框的文字颜色, 默认黑色
    placeholderText: 输入框的提示文字, 默认为空
    placeholderTextColor: 输入框的提示文字颜色, 默认灰色
    selectedTextColor | selectionColor: 输入框选择块的颜色, 默认灰底黑字
    fontSize: 输入框的文字大小, 默认12
    [只读]textFocus: 可通过该属性获取输入框的编辑状态
    [只读]showHotColor: 可通过该属性获取输入框是否在HotColor状态
    [只读]showMatchedColor: 可通过该属性获取输入框是否在MatchedColor状态
    [只读]showErrorColor: 可通过该属性获取输入框是否在ErrorColor状态
    errorColorTrigger: 可通过该属性触发输入框的ErrorColor, 此值改变且为真时会触发一次ErrorColor状态, 默认为false
    [只读]afterIllegalInput: 可通过该属性获取输入框最后一次输入的合法性
    textWrapMode: 参数有TextEdit.NoWrap 、TextEdit.WordWrap 、TextEdit.WrapAnywhere、TextEdit.Wrap
*/
Item {
    id: root
    width: parent.width
    height: parent.height
    property bool usingMultyLineInput: false
    property bool usingRichText: false
    property bool isScrollable: true
    property color backgroundColor: "transparent"
    property color backgroundHotColor: "transparent"
    property color backgroundFocusColor: "transparent"
    property color backgroundErrorColor: "transparent"
    property color backgroundMatchedColor: "transparent"
    property color backgroundDisabledColor: "transparent"
    property real radius: 0
    property bool isLeftUpRadius: true
    property bool isLeftDownRadius: true
    property bool isRightUpRadius: true
    property bool isRightDownRadius: true
    property int borderWidth: 1
    property color borderColor: "black"
    property color borderHotColor: "transparent"
    property color borderFocusColor: "transparent"
    property color borderErrorColor: "red"
    property color borderMatchedColor: "green"
    property color borderDisabledColor: "transparent"
    property var topItem: null
    property bool isTopItemCalculated: false
    property var bottomItem: null
    property bool isBottomItemCalculated: false
    property var leftItem: null
    property bool isLeftItemCalculated: false
    property var rightItem: null
    property bool isRightItemCalculated: false
    property var middleItem: null
    property real textLeftPadding: 10
    property real textRightPadding: 10
    property real textTopPadding: 4
    property real textBottomPadding: 4
    property real scrollBarVWidth: 6
    property var textVerticalAlignment: Text.AlignVCenter
    property bool isReadOnly: false
    property int maximumLength: -1
    property var echoMode: TextInput.Normal
    property int horizontalAlignment: 1
    property var limitValidator: null // RegExpValidator {regExp: //}
    property var matchedValidator: null // RegExpValidator {regExp: //}
    property string text: ""
    property string richText: ""
    property string textControl: ""
    property real textContentHeight: 0
    property color textColor: "black"
    property color textHotColor: "transparent"
    property color textFocusColor: "transparent"
    property color textErrorColor: "transparent"
    property color textMatchedColor: "transparent"
    property color textDisabledColor: "transparent"
    property string placeholderText: ""
    property color placeholderTextColor: "gray"
    property color selectedTextColor: "black"
    property color selectionColor: "gray"
    property int fontSize: 12
    property bool textFocus: false
    property bool showHotColor: false
    property bool showMatchedColor: false
    property bool showErrorColor: false
    property bool errorColorTrigger: false
    property bool afterIllegalInput: false
    property var textWrapMode: TextEdit.NoWrap

    Item {
        anchors.fill: parent
        Item /* 上区 */ {
            id: top_loader
            width: parent.width
            height: children[0].height
            y: root.isTopItemCalculated ? 0 : (0 - this.height)
            Loader {
                width: parent.width
                height: (root.topItem) ? children[0].height : 0
                sourceComponent: root.topItem
            }
        }
        Item /* 左区、输入框、前景区、右区 */ {
            width: parent.width
            height: parent.height - (root.isTopItemCalculated ? top_loader.height : 0) - (root.isBottomItemCalculated ? bottom_loader.height : 0)
            y: root.isTopItemCalculated ? top_loader.height : 0
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
                Loader /* 输入框 */ {
                    width: parent.width
                    height: parent.height
                    sourceComponent: (!root.usingMultyLineInput) ? text_field_item : (root.isScrollable) ? scrollable_text_area_item : non_scrollable_text_area_item
                }
                Loader /* 前景区 */ {
                    width: parent.width
                    height: parent.height
                    sourceComponent: root.middleItem
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
        Item /* 下区 */ {
            id: bottom_loader
            width: parent.width
            height: children[0].height
            y: root.isBottomItemCalculated ? (root.height - this.height) : root.height
            Loader {
                width: parent.width
                height: (root.bottomItem) ? children[0].height : 0
                sourceComponent: root.bottomItem
            }
        }
    }
    Component {
        id: text_field_item
        Item {
            SACRectangle {
                anchors.fill: parent
                color: get_background_color()
                radius: root.radius
                isLeftUpRadius: root.isLeftUpRadius
                isLeftDownRadius: root.isLeftDownRadius
                isRightUpRadius: root.isRightUpRadius
                isRightDownRadius: root.isRightDownRadius
                borderWidth: root.borderWidth
                borderColor: get_border_color()
                TextField {
                    id: first_text_field
                    anchors.fill: parent
                    property int fieldsStart: -1
                    property int fieldsEnd: -1
                    background: null
                    readOnly: root.isReadOnly
                    selectByMouse: true
                    padding: 0//root.textTopPadding
                    leftPadding: root.textLeftPadding
                    rightPadding: root.textRightPadding
                    verticalAlignment: root.textVerticalAlignment
                    horizontalAlignment: (root.horizontalAlignment == 1) ? TextInput.AlignLeft : (root.horizontalAlignment == 2) ? TextInput.AlignHCenter : TextInput.AlignRight
                    wrapMode: root.textWrapMode
                    autoScroll: true
                    maximumLength: root.maximumLength
                    echoMode: root.echoMode
                    validator: null
                    text: root.text
                    placeholderText: root.placeholderText
                    color: get_text_color()
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
                        if (root.matchedValidator) {
                            root.showMatchedColor = this.text.match(root.matchedValidator.regExp);
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
                    onHoveredChanged: {
                        root.showHotColor = hovered;
                    }
                    onSelectedTextChanged: {
                        first_text_field.fieldsStart = first_text_field.selectionStart;
                        first_text_field.fieldsEnd = first_text_field.selectionEnd;
                    }
                    onCursorPositionChanged: {
                        if (first_text_field.selectionStart == first_text_field.selectionEnd) {
                            first_text_field.fieldsStart = -1;
                            first_text_field.fieldsEnd = -1;
                        }
                    }
                }
            }
        }
    }
    Component {
        id: scrollable_text_area_item
        Item {
            SACRectangle {
                anchors.fill: parent
                color: get_background_color()
                radius: root.radius
                isLeftUpRadius: root.isLeftUpRadius
                isLeftDownRadius: root.isLeftDownRadius
                isRightUpRadius: root.isRightUpRadius
                isRightDownRadius: root.isRightDownRadius
                borderWidth: root.borderWidth
                borderColor: get_border_color()
                ScrollView {
                    id: scroll
                    anchors.fill: parent
                    clip: true
                    ScrollBar.vertical.width: root.scrollBarVWidth
                    ScrollBar.horizontal.width: 0
                    TextArea {
                        id: second_text_area
                        property int fieldsStart: -1
                        property int fieldsEnd: -1
                        property int clickStart: 0
                        background: null
                        width: parent.width
                        readOnly: root.isReadOnly
                        selectByKeyboard: true
                        selectByMouse: true
                        leftPadding: root.textLeftPadding
                        rightPadding: root.textRightPadding
                        topPadding: root.textTopPadding
                        bottomPadding: root.textBottomPadding
                        verticalAlignment: root.textVerticalAlignment
                        horizontalAlignment: (root.horizontalAlignment == 1) ? TextEdit.AlignLeft : (root.horizontalAlignment == 2) ? TextEdit.AlignHCenter : TextEdit.AlignRight
                        wrapMode: root.textWrapMode
                        textFormat: (root.usingRichText) ? Text.RichText : Text.PlainText
                        text: root.text
                        placeholderText: root.placeholderText
                        color: get_text_color()
                        selectedTextColor: root.selectedTextColor
                        selectionColor: root.selectionColor
                        placeholderTextColor: root.placeholderTextColor
                        font.family: "Microsoft YaHei"
                        font.pixelSize: root.fontSize
                        onTextChanged: {
                            if (root.usingRichText) {
                                root.richText = text;
                                return;
                            }
                            root.afterIllegalInput = false;
                            root.showErrorColor = false;
                            if (root.limitValidator && !this.text.match(root.limitValidator.regExp)) {
                                var cursorPosition_ = this.cursorPosition - (this.text.length - root.text.length);
                                root.textChanged();
                                this.cursorPosition = cursorPosition_;
                                root.afterIllegalInput = true;
                                root.showErrorColor = true;
                                return;
                            }
                            if (root.matchedValidator) {
                                root.showMatchedColor = this.text.match(root.matchedValidator.regExp);
                            }
                            root.text = text;
                        }
                        onActiveFocusChanged: {
                            if (activeFocus) {
                                root.afterIllegalInput = false;
                                root.showErrorColor = false;
                            } else {
                                select(0, 0);
                            }
                            root.textFocus = activeFocus;
                        }
                        onHoveredChanged: {
                            root.showHotColor = hovered;
                        }
                        onHeightChanged: {
                            root.textContentHeight = height;
                        }
                        onSelectedTextChanged: {
                            second_text_area.fieldsStart = second_text_area.selectionStart;
                            second_text_area.fieldsEnd = second_text_area.selectionEnd;
                            second_text_area.clickStart = second_text_area.selectionStart;
                        }
                    }
                }
            }
        }
    }
    Component {
        id: non_scrollable_text_area_item
        Item {
            SACRectangle {
                anchors.fill: parent
                color: get_background_color()
                radius: root.radius
                isLeftUpRadius: root.isLeftUpRadius
                isLeftDownRadius: root.isLeftDownRadius
                isRightUpRadius: root.isRightUpRadius
                isRightDownRadius: root.isRightDownRadius
                borderWidth: root.borderWidth
                borderColor: get_border_color()
                TextArea {
                    id: third_text_area
                    width: parent.width
                    property int fieldsStart: 0
                    property int fieldsEnd: 0
                    background: null
                    readOnly: root.isReadOnly
                    selectByKeyboard: true
                    selectByMouse: true
                    leftPadding: root.textLeftPadding
                    rightPadding: root.textRightPadding
                    topPadding: root.textTopPadding
                    bottomPadding: root.textBottomPadding
                    verticalAlignment: root.textVerticalAlignment
                    horizontalAlignment: (root.horizontalAlignment == 1) ? TextEdit.AlignLeft : (root.horizontalAlignment == 2) ? TextEdit.AlignHCenter : TextEdit.AlignRight
                    wrapMode: root.textWrapMode
                    textFormat: (root.usingRichText) ? Text.RichText : Text.PlainText
                    text: root.text
                    placeholderText: root.placeholderText
                    color: get_text_color()
                    selectedTextColor: root.selectedTextColor
                    selectionColor: root.selectionColor
                    placeholderTextColor: root.placeholderTextColor
                    font.family: "Microsoft YaHei"
                    font.pixelSize: root.fontSize
                    onTextChanged: {
                        if (root.usingRichText) {
                            root.richText = text;
                            return;
                        }
                        root.afterIllegalInput = false;
                        root.showErrorColor = false;
                        if (root.limitValidator && !this.text.match(root.limitValidator.regExp)) {
                            var cursorPosition_ = this.cursorPosition - (this.text.length - root.text.length);
                            root.textChanged();
                            this.cursorPosition = cursorPosition_;
                            root.afterIllegalInput = true;
                            root.showErrorColor = true;
                            return;
                        }
                        if (root.matchedValidator) {
                            root.showMatchedColor = this.text.match(root.matchedValidator.regExp);
                        }
                        root.text = text;
                    }
                    onActiveFocusChanged: {
                        if (activeFocus) {
                            root.afterIllegalInput = false;
                            root.showErrorColor = false;
                        } else {
                            select(0, 0);
                        }
                        root.textFocus = activeFocus;
                    }
                    onHoveredChanged: {
                        root.showHotColor = hovered;
                    }
                    onHeightChanged: {
                        root.textContentHeight = height;
                    }
                    onSelectedTextChanged: {
                        third_text_area.fieldsStart = third_text_area.selectionStart;
                        third_text_area.fieldsEnd = third_text_area.selectionEnd;
                    }
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
        var backgroundHotColor_ = Qt.colorEqual("transparent", root.backgroundHotColor) ? root.backgroundColor : root.backgroundHotColor;
        var backgroundFocusColor_ = Qt.colorEqual("transparent", root.backgroundFocusColor) ? root.backgroundColor : root.backgroundFocusColor;
        var backgroundErrorColor_ = Qt.colorEqual("transparent", root.backgroundErrorColor) ? root.backgroundColor : root.backgroundErrorColor;
        var backgroundMatchedColor_ = Qt.colorEqual("transparent", root.backgroundMatchedColor) ? root.backgroundColor : root.backgroundMatchedColor;
        var backgroundDisabledColor_ = Qt.colorEqual("transparent", root.backgroundDisabledColor) ? root.backgroundColor : root.backgroundDisabledColor;
        if (root.isReadOnly) {
            return backgroundDisabledColor_;
        }
        if (root.showErrorColor) {
            return backgroundErrorColor_;
        }
        if (root.showMatchedColor) {
            return backgroundMatchedColor_;
        }
        if (textFocus) {
            return backgroundFocusColor_;
        }
        if (root.showHotColor) {
            return backgroundHotColor_;
        }
        return backgroundColor_;
    }
    function get_border_color() {
        var borderColor_ = root.borderColor;
        var borderHotColor_ = Qt.colorEqual("transparent", root.borderHotColor) ? root.borderColor : root.borderHotColor;
        var borderFocusColor_ = Qt.colorEqual("transparent", root.borderFocusColor) ? root.borderColor : root.borderFocusColor;
        var borderErrorColor_ = Qt.colorEqual("transparent", root.borderErrorColor) ? root.borderColor : root.borderErrorColor;
        var borderMatchedColor_ = Qt.colorEqual("transparent", root.borderMatchedColor) ? root.borderColor : root.borderMatchedColor;
        var borderDisabledColor_ = Qt.colorEqual("transparent", root.borderDisabledColor) ? root.borderColor : root.borderDisabledColor;
        if (root.isReadOnly) {
            return borderDisabledColor_;
        }
        if (root.showErrorColor) {
            return borderErrorColor_;
        }
        if (root.showMatchedColor) {
            return borderMatchedColor_;
        }
        if (textFocus) {
            return borderFocusColor_;
        }
        if (root.showHotColor) {
            return borderHotColor_;
        }
        return borderColor_;
    }
    function get_text_color() {
        var textColor_ = root.textColor;
        var textHotColor_ = Qt.colorEqual("transparent", root.textHotColor) ? root.textColor : root.textHotColor;
        var textFocusColor_ = Qt.colorEqual("transparent", root.textFocusColor) ? root.textColor : root.textFocusColor;
        var textErrorColor_ = Qt.colorEqual("transparent", root.textErrorColor) ? root.textColor : root.textErrorColor;
        var textMatchedColor_ = Qt.colorEqual("transparent", root.textMatchedColor) ? root.textColor : root.textMatchedColor;
        var textDisabledColor_ = Qt.colorEqual("transparent", root.textDisabledColor) ? root.textColor : root.textDisabledColor;
        if (root.isReadOnly) {
            return textDisabledColor_;
        }
        if (root.showErrorColor) {
            return textErrorColor_;
        }
        if (root.showMatchedColor) {
            return textMatchedColor_;
        }
        if (textFocus) {
            return textFocusColor_;
        }
        if (root.showHotColor) {
            return textHotColor_;
        }
        return textColor_;
    }
}