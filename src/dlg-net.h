#ifndef _DLG_MY_H_
#define _DLG_MY_H_
#include <qt.hpp>


QT_BEGIN_NAMESPACE
class QCheckBox;
class QLabel;
class QErrorMessage;
QT_END_NAMESPACE


class DlgNet : public QDialog
{
	Q_OBJECT    

public:
    DlgNet(QWidget *parent = 0);
private slots:
    void set_net();
private:
    QLabel *integerLabel;
    QLabel *label_ip;
    QLabel *label_mask;
    QLabel *label_gw;
    QLabel *label_dns;

    QLineEdit *edit_ip;
    QLineEdit *edit_mask;
    QLineEdit *edit_gw;
    QLineEdit *edit_dns;
};

#endif
