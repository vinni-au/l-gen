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
#include <turglem/lemmatizer.hpp>
#include <turglem/russian/charset_adapters.hpp>

void LemmatizerForm::on_pushButton_clicked()
{
    tl::lemmatizer lem;
    try
    {
        lem.load_lemmatizer("dict_russian.auto",
            "paradigms_russian.bin",
            "prediction_russian.auto"
        );
    }
    catch (const std::logic_error& e)
    {
        QMessageBox::critical(this, "Ошибка!", e.what());
        return;
    }
    catch (const std::exception &e)
    {
        QMessageBox::critical(this, "Ошибка!", e.what());
        return;
    }

    tl::lem_result lr;
    size_t sz_lem = lem.lemmatize<russian_utf8_adapter>(ui->lineEdit->text().toStdString().c_str(), lr);
    std::string str;

    for (size_t i = 0; i < sz_lem; i++) {
        std::string nform = lem.get_text<russian_utf8_adapter>(lr, i, 0);
        str += nform;
    }

    ui->textBrowser->setPlainText(QString(str.c_str()));
}
