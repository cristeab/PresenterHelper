#ifndef CONFIG_DIALOG_H
#define CONFIG_DIALOG_H

#include <QDialog>
#include <QMap>

namespace Ui {
class Dialog;
}

class PresenterHelper;

class ConfigDialog : public QDialog
{
    Q_OBJECT
    
public:
    ConfigDialog(QWidget *parent, PresenterHelper *p);
    ~ConfigDialog();
	void showCoords(int x, int y);
private slots:
	void onOk();
	void onApply();
	void onCancel();
	void onBrowse();
private:
    Ui::Dialog *ui;
	PresenterHelper *pres;
	QMap<QString,QString> icons;
};

#endif // CONFIG_DIALOG_H
