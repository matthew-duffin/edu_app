/*
   Name:       Jacob Ormsby, Jonathan Bancroft, Aric Woodliff, Jiedi Mo, Matthew Duffin, Adrian Regalado

   Date:       12/08/2023

   uID:        u1275849, u1300968, u0586534, u1352501, u1227629, u1348610

   GitHub:     21jormsby, JonBancroft, Aric-W, shotpb, matthew-duffin, AdrianRegalado1123

   Assignment: A9: An-Educational-App

   Description: Special QLabel representing a circle that can detect when it is clicked.
*/
#ifndef CLICKABLELABELCIRCLE_H
#define CLICKABLELABELCIRCLE_H

#include <QMouseEvent>
#include <QLabel>

class ClickableLabelCircle : public QLabel
{
    Q_OBJECT
private:
    int radius;
    int id;

    /**
     * @brief sendMouseCoordinate : Emits the id of circle on event
     * @param event : The triggering event
     */
    void sendMouseCoordinate(QMouseEvent* event);

protected:
    /**
     * @brief mousePressEvent : Sends circle coordinates when mouse is pressed
     * @param event : Event when mouse is pressed
     */
    void mousePressEvent(QMouseEvent* event);

public:
    ClickableLabelCircle(int radius, int ID, QWidget* parent);

public slots:
    /**
     * @brief setImage : sets the image on the QLabel
     * @param image : the image on the label
     */
    void setImage(QImage image);

signals:
    /**
     * @brief clicked: Emits circle ID
     * @param ID: Circle ID
     */
    void clicked(int ID);
};

#endif // CLICKABLELABELCIRCLE_H
