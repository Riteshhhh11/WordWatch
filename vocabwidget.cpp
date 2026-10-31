#include "vocabwidget.h"
#include <QPainter>
#include <QJsonArray>
#include <QJsonDocument>
#include <QDebug>
VocabWidget::VocabWidget(QWidget *parent)
    : QWidget(parent)
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_TranslucentBackground);
    resize(300,300);
    QVBoxLayout *layout = new QVBoxLayout(this);
    wordLabel = new QLabel(this);
    wordLabel -> setStyleSheet("color: white; font-size: 24px; font-weight: bold; background: transparent;");
    wordLabel -> setAlignment(Qt::AlignBottom);

    definitonLabel = new QLabel(this);
    definitonLabel -> setStyleSheet("color: #DDDDDD; font-size: 14px; background: transparent;");
    definitonLabel -> setAlignment(Qt::AlignCenter);
    definitonLabel -> setWordWrap(true);

    layout -> addWidget(wordLabel);
    layout -> addWidget(definitonLabel);

    timer = new QTimer(this);
    timer -> setInterval(5000);
    timer -> start();
    QObject::connect(timer, &QTimer::timeout, this, &VocabWidget::fetchNewWord);

    networkManager = new QNetworkAccessManager(this);
    QObject::connect(networkManager, &QNetworkAccessManager::finished, this, &VocabWidget::onWordFetched);


}

VocabWidget::~VocabWidget() = default;

void VocabWidget::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(QColor(0,10,10,200));
    painter.setPen(Qt::NoPen);
    painter.drawRoundedRect(rect(),20,20);
}

void VocabWidget::mousePressEvent(QMouseEvent *event){

    if(event->button() == Qt::LeftButton){
        dragPosition = event->globalPosition().toPoint() - frameGeometry().topLeft();
        event->accept();
    }
}

void VocabWidget::mouseMoveEvent(QMouseEvent *event){
    if(event->buttons() & Qt::LeftButton){
        move(event->globalPosition().toPoint() - dragPosition);
        event->accept();
    }
}
void VocabWidget::fetchNewWord(){
    QNetworkRequest request (QUrl("https://random-word-api.herokuapp.com/word"));
    networkManager -> get(request);
}
void VocabWidget::onWordFetched(QNetworkReply *reply){
    QByteArray bytes = reply->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(bytes);
    QString newWord = doc.array()[0].toString();
    qDebug()<<newWord;
    wordLabel->setText(newWord);
    qDebug()<< "Network Reply Error State:" << reply->error();
    reply->deleteLater();
}
