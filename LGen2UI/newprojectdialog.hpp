/* Begin of file: newprojectdialog.hpp */
#ifndef NEWPROJECTDIALOG_HPP
#define NEWPROJECTDIALOG_HPP

#include <QDialog>
#include <QFileDialog>

namespace Ui {
    class NewProjectDialog;
}

//FIXME: OS-independent separators
class NewProjectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewProjectDialog(QWidget *parent = 0);
    ~NewProjectDialog();

    QString name() const
    {   return m_projectname;   }
    QString filename() const
    {   return m_filename;  }
    QString templateFilename() const
    {   return m_templateFilename;  }
    QString domainFilename() const
    {   return m_domainFilename;    }
    bool templateFileExists() const
    {   return m_toExists;  }
    bool domainFileExists() const
    {   return m_doExists;  }

private slots:
    void on_btn_file_clicked();
    void on_btn_template_clicked();
    void on_btn_domain_clicked();
    void on_le_name_textEdited(const QString &arg1);
    void on_btn_ok_clicked();
    void on_btn_cancel_clicked();

private:
    Ui::NewProjectDialog *ui;

    void showToolTipAtWidget(QWidget* widget, QString text);

    QString m_projectname;
    QString m_filename;
    QString m_templateFilename;
    QString m_domainFilename;
    bool m_toExists;
    bool m_doExists;

    bool checkData();

};

#endif // NEWPROJECTDIALOG_HPP

/* End of file: newprojectdialog.hpp */
