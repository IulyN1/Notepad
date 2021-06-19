#pragma once
#include <QtWidgets/qmainwindow.h>
#include <QtWidgets/qaction.h>
#include <QtWidgets/qtextedit.h>
#include <QtWidgets/qmenubar.h>
#include <qevent.h>
#include <QtWidgets/qtoolbar.h>
#include <QtWidgets/qspinbox.h>
#include <QtWidgets/qlabel.h>

class Notepad: public QMainWindow
{
private:
	int modified = 0;
	QAction* openAct = new QAction(tr("Open"),this);
	QAction* saveAct = new QAction(tr("Save"),this);
	QAction* exitAct = new QAction(tr("Exit"),this);
	QTextEdit* textEdit = new QTextEdit;
	QMenu* menu = menuBar()->addMenu(tr("File"));
	QToolBar* toolBar = addToolBar("&File");
	QSpinBox* size = new QSpinBox;
	QLabel* font = new QLabel{ "Font size: " };
	QString wordsNr;

	// Function that computes the number of words that are in the text edit field
	int get_words();

	// Function that gives the possibility to open a text file from local computer and sets its text
	//into the text edit field
	void open();

	// Function that gives the possibility to save a the text from the text edit field to a text file
	//on the local computer
	void save();

	// Function that enables the user to exit the application
	void exit();

	// Function that initializes the GUI components
	void initGUI();

	// Function that connects the signals of the GUI elements
	void connectSignals();

	// Function that sets the initial state of the GUI application
	void setInitialState();
public:
	// Constructor for the Notepad class
	Notepad() {
		initGUI();
		connectSignals();
		setInitialState();
	}

	// Overriden function for the closeEvent, for manipulating the behaviour of closing the application
	void closeEvent(QCloseEvent* ev) override;
};

