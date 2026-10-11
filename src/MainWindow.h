#pragma once
#include <QMainWindow>
#include <QString>
#include "Library.h" 

class QTableWidget;
class QLineEdit;
class QLabel;
class QPlainTextEdit;
class QWidget;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow();

private slots:
    void onAddItem();
    void onAddMember();
    void onBorrow();
    void onReturn();
    void onPayFines();
    void onAdvance(int days);
    void refresh();

private:
    int selectedId(QTableWidget *table); 
    void logMessage(QString msg);
    void showError(string error);
    QString memberName(int memberId);
    QWidget* makeStatCard(QString icon, QString caption, QString color, QLabel *&valueLabel);

    Library library;
    QTableWidget *itemTable;
    QTableWidget *memberTable;
    QLineEdit *searchEdit;
    QLabel *dayLabel;
    QLabel *totalLabel;
    QLabel *availLabel;
    QLabel *borrowedLabel;
    QLabel *lateLabel;
    QLabel *finesLabel;
    QPlainTextEdit *logBox;
};
