#ifndef VOCABWIDGET_H
#define VOCABWIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QPoint>
#include <QLabel>
#include <QVBoxLayout>
#include <QTimer>

class VocabWidget : public QWidget
{
    Q_OBJECT

public:
    explicit VocabWidget(QWidget *parent = nullptr);
    ~VocabWidget() override;

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private:
    QPoint dragPosition;
    QLabel  *wordLabel;
    QLabel *definitonLabel;
    QTimer *timer;
};
#endif // VOCABWIDGET_H
