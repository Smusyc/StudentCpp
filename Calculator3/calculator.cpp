#include "calculator.h"

Calculator::Calculator (QWidget *parent) : QWidget(parent) {
 displaystring = new QLabel("");
 displaystring->setMinimumSize (50, 0);
 QString aButtons[6][7] = {
   {"(", ")", "1/x","x!","=","<-","CE"},
   {"7", "8", "9", "/","sin","x^2","C"},
   {"4", "5", "6", "*","cos","x^y","arcsin"},
   {"1", "2", "3", "-","tg","|x|","arccos"},
   {"0", ".", "+","#","ctg","arcctg","arctg"},
   {"Log", "Ln", "Lg", "e","i","Pi","%"},
  };

 QGridLayout *myLayout = new QGridLayout;
 myLayout->addWidget(displaystring, 0, 0, 1, 4);
 for (int i = 0; i < 6; ++i) {
  for (int j = 0; j < 7; ++j) {
   myLayout->addWidget(createButton(aButtons[i][j]), i + 2, j);
  }
 }
 setLayout(myLayout);
}
