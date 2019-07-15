#ifndef _Calculator_h_
 #define _Calculator_h_
 #include <QWidget>
 #include <QStack>
 #include <QLabel>
 #include <QPushButton>
 #include <QGridLayout>

 class Calculator : public QWidget {
  Q_OBJECT //макрос, нужен в начале всех наших классов
  private:
   QLabel *displaystring;
   QStack <QString> stack;
  public:
   Calculator (QWidget* pwgt = 0);
   QPushButton* createButton (const QString& str);
   void calculate ();
  public slots: //Общедоступные обработчики событий
   void slotButtonClicked ();
 };
#endif
