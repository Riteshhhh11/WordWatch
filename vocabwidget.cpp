#include "vocabwidget.h"
#include <QPainter>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

VocabWidget::VocabWidget(QWidget *parent)
    : QWidget(parent)
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_TranslucentBackground);
    resize(350,250);

    QVBoxLayout *layout = new QVBoxLayout(this);
    wordLabel = new QLabel(this);
    wordLabel -> setStyleSheet("color: #FFFFFF; font-family: 'Segoe UI'; font-size: 26px; font-weight: bold; background: transparent;");
    wordLabel -> setAlignment(Qt::AlignCenter);

    definitonLabel = new QLabel(this);
    definitonLabel -> setStyleSheet("color: #B0B0B0; font-family: 'Segoe UI'; font-size: 15px;font-weight: bold; background: transparent;");
    definitonLabel -> setAlignment(Qt::AlignCenter);
    definitonLabel -> setWordWrap(true);

    layout -> addWidget(wordLabel);
    layout -> addWidget(definitonLabel);
    layout -> setAlignment(Qt::AlignCenter);
    layout -> setContentsMargins(20,20,20,20);
    layout -> setSpacing(8);

    timer = new QTimer(this);
    timer -> setInterval(10000);
    timer -> start();
    QObject::connect(timer, &QTimer::timeout, this, &VocabWidget::fetchNewWord);

    wordManager = new QNetworkAccessManager(this);
    QObject::connect(wordManager, &QNetworkAccessManager::finished, this, &VocabWidget::onWordFetched);

    dictManager = new QNetworkAccessManager(this);
    QObject::connect(dictManager, &QNetworkAccessManager::finished, this, &VocabWidget::onDefinitionFetched);

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
    QString wordUrl = "https://random-word-api.herokuapp.com/word";
    QNetworkRequest wordRequest (wordUrl);
    wordManager -> get(wordRequest);
}

void VocabWidget::onWordFetched(QNetworkReply *reply){
    QByteArray bytes = reply->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(bytes);
    QString newWord = doc.array()[0].toString();
    qDebug()<<newWord;
    wordLabel->setText(newWord);

    QString dictUrl= "https://api.dictionaryapi.dev/api/v2/entries/en/" + newWord;
    QNetworkRequest definitionRequest(dictUrl);
    dictManager->get(definitionRequest);

    qDebug()<< "Network Reply Error State:" << reply->error();
    reply->deleteLater();    
}

void VocabWidget::onDefinitionFetched(QNetworkReply *reply){
    reply->deleteLater();

    QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
    if(!doc.isArray()){
        definitonLabel->setText("Definition Not Found");
        return;
    }

    QString definition = doc.array()[0].toObject()["meanings"].toArray()[0]
                             .toObject()["definitions"].toArray()[0]
                             .toObject()["definition"].toString();

    definitonLabel->setText(definition.isEmpty()?"Definition Not Found" : definition);
}
