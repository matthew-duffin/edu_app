/*
   Name:       Jacob Ormsby, Jonathan Bancroft, Aric Woodliff, Jiedi Mo, Matthew Duffin, Adrian Regalado

   Date:       12/08/2023

   uID:        u1275849, u1300968, u0586534, u1352501, u1227629, u1348610

   GitHub:     21jormsby, JonBancroft, Aric-W, shotpb, matthew-duffin, AdrianRegalado1123

   Assignment: A9: An-Educational-App

   Description: Holds the logic and methods for manipulation of a Box2d Body that represents a soldier.
*/
#ifndef SOLDIER_H
#define SOLDIER_H

#include <QObject>
#include <QPixmap>
#include <QTimer>
#include <Box2D/Box2D.h>

class Soldier : public QObject
{
    Q_OBJECT
private:
    int id;
    QPixmap icon;
    b2Body* soldierBody;
    const int INTERVAL = 30;
    QTimer* soldierTimer;
    float forceX = 0.0f;
    float forceY = 0.0f;
    float constraintX = 0.0f; // where a soldier should stop in the x direction
    float constraintY = 0.0f; // where a soldier should stop in the y direction
    b2World* world;
    QPoint travelLocation; // the orders of where a soldier should go in the free sim mode
    bool metX = false, metY = false; // determines if the soldier has reached its constraints in the x or y direction
public:
    Soldier(QPoint pos, b2World *world, QObject *parent = nullptr);
    /**
     * @brief stop stops the soldier by setting linear velocity and force to 0. Also resets the soldiers movement orders
     */
    void stop();
    /**
     * @brief setMoveDirection connects the soldiers unique timer with the executeForce method which causes soldier movement. Causes movement when the soldiers timer timesout
     * @param forceX the force applied in the x direction
     * @param forceY the force applied in the y direction
     * @param constraintX where the soldier should stop in the x direction
     * @param constraintY where the soldier should stop in the y direction
     */
    void setMoveDirection(float forceX, float forceY, float constraintX, float constraintY);
    /**
     * @brief setMoveDirectionFreeSim very similar to the previous method, but connects it to a unique movement method for the free sim
     * @param forceX the force applied in the x direction
     * @param forceY the force applied in the y direction
     * @param constraintX where the soldier should stop in the x direction
     * @param constraintY where the soldier should stop in the y direction
     */
    void setMoveDirectionFreeSim(float forceX, float forceY, float constraintX, float constraintY);
    /**
     * @brief getPosition a getter for the soldiers current position
     * @return returns a b2Vec2 coordinate
     */
    b2Vec2 getPosition();
    /**
     * @brief destroySoldier removes a soldiers body from the world
     */
    void destroySoldier();
    /**
     * @brief getID returns the soldiers unique ID
     * @return
     */
    int getID();
     /**
     * @brief setTravelLocation sets the orders of where the soldier should move to in free sim mode
     * @param coordinate the QPoint that notates where the soldier shoudl travel to
     */
    void setTravelLocation(QPoint coordinate);
    /**
     * @brief moveSoldierFreeSim moves the soldier to the location based on the coordinates supplied
     * @param positiveForce what the force in the x direction should be
     * @param negativeForce what the force in the y direction should be
     */
    void moveSoldierFreeSim(float positiveForce, float negativeForce);
    /**
     * @brief getTravelLocation a getter for what the soldiers move location should be in free sim mode
     * @return a QPoint of the soldiers current movement orders
     */
    QPoint getTravelLocation();

public slots:
    /**
     * @brief executeForce applies the force to the soldier as well as stops the soldier when it reaches its constraints
     */
    void executeForce();
    /**
     * @brief executeForceFreeSim a verys similar method to execute force but with a few modifications for when in free sim mode that better determine when the soldier has reached its travel
     * location
     */
    void executeForceFreeSim();
};

#endif // SOLDIER_H
