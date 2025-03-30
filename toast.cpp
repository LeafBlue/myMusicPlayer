#include "toast.h"

Toast::Toast(const QString& text, QWidget* parent): QLabel(text, parent)  {
    // 设置无边框、置顶、透明背景
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::X11BypassWindowManagerHint);
    //setAttribute(Qt::WA_TranslucentBackground);

    // 设置样式
    setStyleSheet(
        "QLabel{"
        "  background-color: black;"  // 深灰色半透明背景
        "  color: white;"                        // 白色文字
        "  padding: 8px 20px;"                  // 内边距
        "  border-radius: 10px;"                 // 圆角
        "  font-size:20px;"
        "}"
    );

    // 自动调整大小
    setMinimumSize(200, 50);
    adjustSize();
}

void Toast::showAutoClose(int milliseconds)
{
    show();

    // 自动关闭定时器
    QTimer::singleShot(milliseconds, this, &Toast::close);

    // 居中显示（相对于主屏幕）
    //QScreen* screen = QGuiApplication::primaryScreen();
    //QRect screenGeometry = screen->availableGeometry();
    //move((screenGeometry.width() - width())/2,
    //     screenGeometry.height() - height() - 50); // 底部向上偏移50px
}
