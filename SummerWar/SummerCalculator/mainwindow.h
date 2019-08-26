#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <string>
#include <string.h>
#include "string.h"
using::std::string;
using::std::vector;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    //string Calculate(string expression);
   // QString formatted();
    void on_opB_clicked();
    void on_clB_clicked();

    void on_opmB_clicked();

    void on_clmB_clicked();

    void on_factB_clicked();

    void on_clearB_2_clicked();

    void on_sevenB_clicked();

    void on_eigthB_clicked();

    void on_nineB_clicked();

    void on_plusB_clicked();

    void on_fourB_clicked();

    void on_fiveB_clicked();

    void on_sixB_clicked();

    void on_minusB_clicked();

    void on_oneB_clicked();

    void on_pointB_clicked();

    void on_zeroB_clicked();

    void on_recipB_clicked();

    void on_multB_clicked();

    void on_divisB_clicked();

    void on_sinB_clicked();

    void on_cosB_clicked();

    void on_tgB_clicked();

    void on_ctgB_clicked();

    void on_arcsinB_clicked();

    void on_arccosB_clicked();

    void on_arctgB_clicked();

    void on_arcctgB_clicked();

    void on_piB_clicked();

    void on_eB_clicked();

    void on_copmB_clicked();

    void on_logB_clicked();

    void on_lgB_clicked();

    void on_lnB_clicked();

    void on_powtwoB_clicked();

    void on_powB_clicked();

    void on_radicaltwoB_clicked();

    void on_radicalB_clicked();

    void on_procB_clicked();

    void on_equalB_clicked();

 // void on_exprText_textChanged();

    void on_threeB_clicked();

    void on_twoB_clicked();

private:
    Ui::MainWindow *ui;
protected:

    void keyPressEvent(QKeyEvent *event);

private slots:
 //   void on_exprText_textChanged(const QString &arg1);
    void on_allclearB_clicked();
    void on_Undo_clicked();
    void on_Redo_clicked();
};

#endif // MAINWINDOW_H
