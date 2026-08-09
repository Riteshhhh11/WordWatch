#ifndef VOCABWIDGET_H
#define VOCABWIDGET_H

#include <QWidget>

class VocabWidget : public QWidget
{
    Q_OBJECT

public:
    explicit VocabWidget(QWidget *parent = nullptr);
    ~VocabWidget() override;
};
#endif // VOCABWIDGET_H
