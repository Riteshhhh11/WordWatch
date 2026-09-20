#ifndef VOCABWIDGET_H
#define VOCABWIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QPoint>

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
};
#endif // VOCABWIDGET_H
