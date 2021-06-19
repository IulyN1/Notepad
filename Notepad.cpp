#include "Notepad.h"
#include <QtWidgets/qfiledialog.h>
#include <QtWidgets/qmessagebox.h>
#include <QtWidgets/qstatusbar.h>

void Notepad::open() {
	QString filename = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Text Files (*.txt)"));
	if (filename != "") {
		QFile file(filename);
		if (!file.open(QIODevice::ReadOnly)) {
			QMessageBox::critical(this, tr("Error"), tr("Could not open file!"));
			return;
		}
		QTextStream in(&file);
		textEdit->setText(in.readAll());
		file.close();
	}
	modified = 0;
}

void Notepad::save() {
	QString filename = QFileDialog::getSaveFileName(this, tr("Save File"), "", tr("Text Files (*.txt)"));
	if (filename != "") {
		QFile file(filename);
		if (!file.open(QFile::WriteOnly | QFile::Truncate)) {
			QMessageBox::critical(this, tr("Error"), tr("Could not save file!"));
			return;
		}
		QTextStream out(&file);
		QString txt = textEdit->document()->toPlainText();
		out << txt;
		file.close();
	}
	modified = 0;
}

void Notepad::exit() {
	this->close();
}

void Notepad::closeEvent(QCloseEvent* ev) {
	ev->ignore();
	if (modified == 1) {
		int ret = QMessageBox::warning(this, "Changes made!",
			"The document has been modified.\nDo you want to save your changes?",
			QMessageBox::Save | QMessageBox::Discard);
		if (ret == QMessageBox::Save) {
			save();
			ev->accept();
		}
		else {
			ev->accept();
		}
	}
	ev->accept();
}

void Notepad::initGUI() {
	setCentralWidget(textEdit);
	menu->addAction(openAct);
	menu->addAction(saveAct);
	menu->addAction(exitAct);
	toolBar->addWidget(font);
	toolBar->addWidget(size);
}

void Notepad::connectSignals() {
	QObject::connect(openAct, &QAction::triggered, this, &Notepad::open);
	QObject::connect(saveAct, &QAction::triggered, this, &Notepad::save);
	QObject::connect(exitAct, &QAction::triggered, this, &Notepad::exit);
	QObject::connect(textEdit, &QTextEdit::textChanged, this, [=]() {
		modified = 1;
		auto nr = get_words();
		wordsNr = "Word Counter: " + QString::number(nr);
		statusBar()->showMessage(wordsNr);
		});
	QObject::connect(size, &QSpinBox::valueChanged, this, [=]() {
		auto val = size->value();
		textEdit->setFontPointSize(val);
		});
}

int Notepad::get_words() {
	int nr{ 0 };
	QString txt = textEdit->document()->toPlainText();
	for (const auto el : txt) {
		if (el == ' ') {
			nr++;
		}
	}
	if (txt.back() == ' ')nr--;
	return nr+1;
}

void Notepad::setInitialState() {
	size->setValue(10);
	resize(600, 300);
	setWindowIcon(QIcon("Notepad.png"));
	statusBar()->showMessage("Word Counter: 0");
}