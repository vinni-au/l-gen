/*
 * Copyright (C) 2011-2012  Anton Storozhev, antonstorozhev@gmail.com
 *
 * This file is a part of L-Gen 2.0
 *
 * L-Gen 2.0 is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation, either version 3
 * of the License, or (at your option) any later version.
 *
 * L-Gen 2.0 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

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
