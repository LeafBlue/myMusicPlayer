#ifndef TOAST_H
#define TOAST_H

#include <QApplication>
#include <QLabel>
#include <QTimer>
#include <QScreen>
#include <QGuiApplication>
#include <QObject>

class Toast : public QLabel
{
    Q_OBJECT
public:
    Toast(const QString& text, QWidget* parent = nullptr);

    void showAutoClose(int milliseconds = 2000);

};

#endif // TOAST_H
