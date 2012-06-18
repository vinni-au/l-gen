#include "lemmatizerform.hpp"
#include "ui_lemmatizerform.h"
#include <QKeyEvent>

LemmatizerForm::LemmatizerForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LemmatizerForm)
{
    ui->setupUi(this);
}

LemmatizerForm::~LemmatizerForm()
{
    delete ui;
}

#include <QMessageBox>
#include <QTextCodec>
#include <QTextStream>
#include <3rdparty/MCR/mcr.hpp>

void LemmatizerForm::on_pushButton_clicked()
{
    MCR* mcr = new MCR;
    mcr->LoadVocabulary("./data/zal.mcr");

    QString res;
    QTextCodec* codec = QTextCodec::codecForName("Windows-1251");
    QByteArray encoded = codec->fromUnicode(ui->lineEdit->text());
    const char* text = encoded.constData();
    WordForms *wf = mcr->FindWordForms(text);
    res += "Для слова: " + codec->toUnicode(text) + "\n";
    res += "Найдено форм: " + QString::number(wf->count) + "\n\n";
    for (int i = 0; i < wf->count; ++i) {
        Words *ws = mcr->GetLexemByID(wf->ids[i], true, false);
        res += QString::number(i+1) + "." + codec->toUnicode(text) +
               "\t(" + codec->toUnicode(mcr->ConstGrammarChar(ws->inlex[0].cid)) + ", " +
               codec->toUnicode(mcr->VarGrammarChar(ws->inlex[0].cid, ws->inlex[0].vid)) + ")\n";
        delete ws;
    }
    res += "\n";
    for (int i = 0; i < wf->count; ++i) {
        Words *ws = mcr->GetLexemByID(wf->ids[i], false, true);
        for (int j = 0; j < ws->count; ++j) {
            res += QString::number(j+1) + ") " + codec->toUnicode(ws->inlex[j].wordForm) +
                   "\t(" + codec->toUnicode(mcr->ConstGrammarChar(ws->inlex[j].cid)) + ", " +
                   codec->toUnicode(mcr->VarGrammarChar(ws->inlex[j].cid, ws->inlex[j].vid)) + ")\n";
        }
        res += "\n";
        delete ws;
    }
    ui->textBrowser->setPlainText(res.toAscii());
    delete wf;
}
