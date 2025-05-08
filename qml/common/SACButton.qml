import QtQuick 2.14
import QtQuick.Controls 2.14
import Qt5Compat.GraphicalEffects
// import QtGraphicalEffects 1.12
/*
    // 本质是一个MouseArea, 具备正常MouseArea的所有属性和信号
    width | height: 宽高, 可用anchors控制
    backgroundColor | backgroundHotColor | backgroundPressedColor | backgroundDisabledColor: 背景颜色, 默认透明
    radius: 圆角, 默认无圆角
    backgroundBorderWidth: 边框宽度, 默认无边框
    backgroundBorderColor | backgroundBorderHotColor | backgroundBorderPressedColor | backgroundBorderDisabledColor: 边框颜色, 默认透明
    isLeftUpRadius | isLeftDownRadius | isRightUpRadius | isRightDownRadius: 单独控制圆角属性对每个角是否生效, 默认全部生效
    backgroundImage | backgroundHotImage: 背景图片, 默认无背景图片
    backgroundDefaultImage: 默认背景图片, 默认无默认背景图片
    isBackgroundImageDesaturated | backgroundHotImageDesaturated: 背景图片是否变灰, 默认不变灰
    foregroundItem: 前景附加组件, 默认为空; 注意该组件的高和宽会被强制设置为按钮的高和宽, 且该组件不会超出按钮边界(忽略圆角)
    text: 按钮居中文本
    [只读]textContentWidth: 文本内容宽度
    textColor | textHotColor | textPressedColor | textDisabledColor: 文本颜色, 默认黑色
    fontSize: 文本的文字大小, 默认12
    imageLoadingDebugOutput: 图片加载失败时的打印输出, 建议填写使用该控件的文件路径，以便排查问题
*/
MouseArea {
    // TODO: 鼠标变形未做
    // TODO: 按下未弹起时的图片未做
    // TODO: 背景图受圆角切割未做
    // TODO: 禁用鼠标事件当做纯背景图且不受TAB键影响未做
    id: root
    width: parent.width
    height: parent.height
    enabled: true
    acceptedButtons: Qt.LeftButton
    hoverEnabled: true
    cursorShape: this.enabled ? Qt.PointingHandCursor : Qt.ArrowCursor

    property color backgroundColor: "transparent"
    property color backgroundHotColor: "transparent"
    property color backgroundPressedColor: "transparent"
    property color backgroundDisabledColor: "transparent"
    property real radius: 0
    property int backgroundBorderWidth: 0
    property color backgroundBorderColor: "transparent"
    property color backgroundBorderHotColor: "transparent"
    property color backgroundBorderPressedColor: "transparent"
    property color backgroundBorderDisabledColor: "transparent"
    property bool isLeftUpRadius: true
    property bool isLeftDownRadius: true
    property bool isRightUpRadius: true
    property bool isRightDownRadius: true
    property string backgroundImage: ""
    property string backgroundHotImage: ""
    // property string backgroundHoveredImage: ""
    property string backgroundDefaultImage: ""
    property bool isBackgroundImageDesaturated: false
    property bool backgroundHotImageDesaturated: false
    // property bool backgroundHoveredImageDesaturated: false
    property string text: ""
    property real textContentWidth: 0
    property real textContentHeight: 0
    property color textColor: "black"
    property color textHotColor: "transparent"
    property color textPressedColor: "transparent"
    property color textDisabledColor: "transparent"
    property int fontSize: 12
    property bool fontBold: false
    property var foregroundItem: null
    property string imageLoadingDebugOutput: ""

    SACRectangle /* 边框、背景 */ {
        id: background_rect
        anchors.fill: parent
        color: root.get_background_color()
        radius: root.radius
        borderWidth: root.backgroundBorderWidth
        borderColor: root.get_background_border_color()
        isLeftUpRadius: root.isLeftUpRadius
        isLeftDownRadius: root.isLeftDownRadius
        isRightUpRadius: root.isRightUpRadius
        isRightDownRadius: root.isRightDownRadius
    }
    Rectangle /* 灰度+圆角 */ {
        id: background_image
        anchors.fill: parent
        anchors.margins: root.backgroundBorderWidth
        color: "transparent"
        radius: root.radius
        SACImage {
            id: tmp_source
            anchors.fill: parent
            visible: false
            targetSource: get_background_image()
            defaultSource: root.backgroundDefaultImage
            imageLoadingDebugOutput: root.imageLoadingDebugOutput
        }
        Desaturate {
            id: tmp_desaturate
            anchors.fill: parent
            visible: false
            source: tmp_source
            desaturation: root.isBackgroundImageDesaturated ? 1 : 0
        }
        Rectangle {
            id: tmp_mask
            anchors.fill: parent
            visible: false
            radius: parent.radius
        }
        OpacityMask {
            anchors.fill: parent
            visible: (tmp_source.source != "")
            source: tmp_desaturate
            maskSource: tmp_mask
        }
    }
    SACLabel {
        id: label
        anchors.centerIn: parent
        text: root.text
        color: root.get_text_color()
        font.pixelSize: root.fontSize
        font.bold: root.fontBold
        onWidthChanged: {
            root.textContentWidth = width;
        }
        onHeightChanged: {
            root.textContentHeight = height;
        }
    }
    Loader {
        width: parent.width
        height: parent.height
        clip: true
        sourceComponent: root.foregroundItem
    }
    function get_background_color() {
        var normalColor_ = root.backgroundColor;
        var hotColor_ = root.backgroundHotColor;
        var pressedColor_ = root.backgroundPressedColor;
        var disabledColor_ = root.backgroundDisabledColor;
        if (Qt.colorEqual("transparent", hotColor_)) hotColor_ = Qt.darker(normalColor_, 1.2);
        if (Qt.colorEqual("transparent", pressedColor_)) pressedColor_ = Qt.darker(hotColor_, 1.2);
        if (Qt.colorEqual("transparent", disabledColor_)) disabledColor_ = normalColor_;
        if (false) {
        } else if (!root.enabled) {
            return disabledColor_;
        } else if (root.containsPress) {
            return pressedColor_;
        } else if (root.containsMouse) {
            return hotColor_;
        }
        return normalColor_;
    }
    function get_background_image() {
        var backgroundImage_ = root.backgroundImage;
        // if (!Tools.exists(backgroundImage_) && root.backgroundDefaultImage != "") {
        //     backgroundImage_ = root.backgroundDefaultImage;
        // }
        var backgroundHotImage_ = (root.backgroundHotImage == "") ? backgroundImage_ : root.backgroundHotImage;
        // if (!Tools.exists(backgroundHotImage_) && root.backgroundDefaultImage != "") {
        //     backgroundHotImage_ = root.backgroundDefaultImage;
        // }
        if (root.containsMouse) {
            return backgroundHotImage_;
        }
        return backgroundImage_;
    }
    function get_background_border_color() {
        var normalColor_ = root.backgroundBorderColor;
        var hotColor_ = root.backgroundBorderHotColor;
        var pressedColor_ = root.backgroundBorderPressedColor;
        var disabledColor_ = root.backgroundBorderDisabledColor;
        if (Qt.colorEqual("transparent", hotColor_)) hotColor_ = Qt.darker(normalColor_, 1.2);
        if (Qt.colorEqual("transparent", pressedColor_)) pressedColor_ = Qt.darker(hotColor_, 1.2);
        if (Qt.colorEqual("transparent", disabledColor_)) disabledColor_ = normalColor_;
        if (false) {
        } else if (!root.enabled) {
            return disabledColor_;
        } else if (root.containsPress) {
            return pressedColor_;
        } else if (root.containsMouse) {
            return hotColor_;
        }
        return normalColor_;
    }
    function get_text_color() {
        var normalColor_ = root.textColor;
        var hotColor_ = root.textHotColor;
        var pressedColor_ = root.textPressedColor;
        var disabledColor_ = root.textDisabledColor;
        if (Qt.colorEqual("transparent", hotColor_)) hotColor_ = Qt.darker(normalColor_, 1.2);
        if (Qt.colorEqual("transparent", pressedColor_)) pressedColor_ = Qt.darker(hotColor_, 1.2);
        if (Qt.colorEqual("transparent", disabledColor_)) disabledColor_ = normalColor_;
        if (false) {
        } else if (!root.enabled) {
            return disabledColor_;
        } else if (root.containsPress) {
            return pressedColor_;
        } else if (root.containsMouse) {
            return hotColor_;
        }
        return normalColor_;
    }
}