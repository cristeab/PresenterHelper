#include <QFileDialog>
#include <QMessageBox>
#include "Configdialog.h"
#include "PresenterHelper.h"
#include "ui_ConfigDialog.h"

ConfigDialog::ConfigDialog(QWidget *parent, PresenterHelper *p) :
    QDialog(parent),
    ui(new Ui::Dialog),
	pres(p)
{
    ui->setupUi(this);

	icons["Green Pointer"] = ":/icons/green-pointer.png";
	icons["Hand Pointer"] = ":/icons/hand-pointer.png";
	icons["Tool Pointer"] = ":/icons/tool-pointer.png";

	QList<QString> keys = icons.keys();
	int curIdx = icons.count();
	int i = 0;
	foreach(const QString key, keys)
	{
		QString iconPath = icons.value(key);
		if (iconPath == pres->pointerIconPath)
		{
			curIdx = i;
		}
		++i;
		QIcon iconImage(iconPath);
		if (!iconImage.isNull())
		{
			ui->comboBoxPointerIcon->addItem(iconImage, key);
		}
	}
	if (curIdx >= icons.count())
	{
		QIcon icon(pres->pointerIconPath);
		if (!icon.isNull())
		{
			int nbItems = icons.count();
			ui->comboBoxPointerIcon->insertItem(nbItems, icon, pres->pointerIconPath);
		}
		else
		{
			curIdx = 0;//use default icon
		}
	}
	ui->comboBoxPointerIcon->setCurrentIndex(curIdx);
	ui->spinBoxPointerSize->setValue(pres->pointerSize);
	ui->spinBoxOffsetX->setValue(pres->offsetX);
	ui->spinBoxOffsetY->setValue(pres->offsetY);
	ui->spinBoxScaleFactor->setValue(static_cast<int>(pres->scaleFactor*100));
	ui->spinBoxNbSwipes->setValue(pres->nbSwipes);
	ui->checkBoxTap->setChecked(pres->tapForForwardSwitch);
	ui->checkBoxKalman->setChecked(pres->useKalmanFilter);
	showCoords(pres->scrWidth/2, pres->scrHeight/2);

	connect(ui->pushButtonOk, SIGNAL(clicked(bool)), this, SLOT(onOk()));
	connect(ui->pushButtonApply, SIGNAL(clicked(bool)), this, SLOT(onApply()));
	connect(ui->pushButtonCancel, SIGNAL(clicked(bool)), this, SLOT(onCancel()));
	connect(ui->pushButtonBrowse, SIGNAL(clicked(bool)), this, SLOT(onBrowse()));
}

ConfigDialog::~ConfigDialog()
{
    delete ui;
}

void ConfigDialog::onOk()
{
	onApply();
	onCancel();
}

void ConfigDialog::onCancel()
{
	pres->showCoords = false;
	hide();
}

void ConfigDialog::onApply()
{
	pres->pointerIconPath = ui->comboBoxPointerIcon->currentText();
	int index = ui->comboBoxPointerIcon->currentIndex();
	if (index < icons.count() && 0 <= index)
	{
		pres->pointerIconPath = icons.value(pres->pointerIconPath);
	}
	pres->pointerSize = ui->spinBoxPointerSize->value();
	pres->loadPointer(pres->pointerIconPath, pres->pointerSize);
	pres->update();

	pres->offsetX = ui->spinBoxOffsetX->value();
	pres->offsetY = ui->spinBoxOffsetY->value();
	pres->scaleFactor = ui->spinBoxScaleFactor->value()/100.0;
	pres->nbSwipes = ui->spinBoxNbSwipes->value();
	pres->swipeCounter = 0;
	pres->tapForForwardSwitch = (Qt::Checked == ui->checkBoxTap->checkState());
	pres->useKalmanFilter = (Qt::Checked == ui->checkBoxKalman->checkState());
}

void ConfigDialog::onBrowse()
{
	QFileDialog openFile(NULL, "Select an Image File");
	openFile.setFileMode(QFileDialog::ExistingFile);
	openFile.setViewMode(QFileDialog::Detail);
	openFile.setNameFilter("*.png *.jpg *.jpeg");
	QStringList fileNames;
	if (openFile.exec())
	{
		fileNames = openFile.selectedFiles();
		if (0 < fileNames.size())
		{
			QIcon icon(fileNames[0]);
			if (!icon.isNull())
			{
				int nbItems = icons.count();
				if (nbItems < ui->comboBoxPointerIcon->count()) {
					ui->comboBoxPointerIcon->removeItem(nbItems);
				}
				ui->comboBoxPointerIcon->insertItem(nbItems, icon, fileNames[0]);
				ui->comboBoxPointerIcon->setCurrentIndex(nbItems);
			}
			else
			{
				QMessageBox::warning(this, "Presenter Helper", "Cannot load cursor pixmap");
			}
		}
	}
	activateWindow();
	raise();
}

void ConfigDialog::showCoords(int x, int y)
{
	ui->labelStatus->setText(QString("(x,y) = (%1,%2)").arg(x).arg(y));
}
