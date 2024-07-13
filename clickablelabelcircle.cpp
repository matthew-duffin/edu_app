/*
   Name:       Jacob Ormsby, Jonathan Bancroft, Aric Woodliff, Jiedi Mo, Matthew Duffin, Adrian Regalado

   Date:       12/08/2023

   uID:        u1275849, u1300968, u0586534, u1352501, u1227629, u1348610

   GitHub:     21jormsby, JonBancroft, Aric-W, shotpb, matthew-duffin, AdrianRegalado1123

   Assignment: A9: An-Educational-App

   Description: Special QLabel representing a circle that can detect when it is clicked.
*/
#include "clickablelabelcircle.h"

ClickableLabelCircle::ClickableLabelCircle(int radius, int ID,QWidget* parent) : QLabel(parent), radius(radius), id(ID) {}

void ClickableLabelCircle::mousePressEvent(QMouseEvent* event)
{
    sendMouseCoordinate(event);
}
void ClickableLabelCircle::sendMouseCoordinate(QMouseEvent* event)
{
    //tells the view what was soldier was clicked in the free sim
    emit clicked(id);
}
void ClickableLabelCircle::setImage(QImage image)
{
    QPixmap pixmap = QPixmap::fromImage(image); //converts the QImage to QPixmap
    this->setPixmap(pixmap);
    this->setMask(pixmap.mask());
    this->show();
}

