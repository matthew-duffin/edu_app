/*
   Name:       Jacob Ormsby, Jonathan Bancroft, Aric Woodliff, Jiedi Mo, Matthew Duffin, Adrian Regalado

   Date:       12/08/2023

   uID:        u1275849, u1300968, u0586534, u1352501, u1227629, u1348610

   GitHub:     21jormsby, JonBancroft, Aric-W, shotpb, matthew-duffin, AdrianRegalado1123

   Assignment: A9: An-Educational-App

   Description: Runs the logic to manipulate soldiers in our animations and free sim.
*/
#ifndef ANIMATIONMODEL_H
#define ANIMATIONMODEL_H

#include "soldier.h"
#include <QObject>
#include <QTimer>

class AnimationModel : public QObject
{
    Q_OBJECT

private:
    //constants for forces, to make movement consistent
    const float positiveForce = 72000000.0f;
    const float negativeForce = -72000000.0f;
    // Prepare for simulation. Typically we use a time step of 1/60 of a
    // second (60Hz) and 10 iterations. This provides a high quality simulation
    // in most game scenarios.
    const float32 timeStep = 1.0f / 60.0f;
    const int32 velocityIterations = 6;
    const int32 positionIterations = 10;
    QList<Soldier*> soldiers;
    b2World world;

    QTimer* worldTimer;
    int animationLength;
    int currentRunTime;

    bool isFreeSim = false;

public:
    /**
     * @brief AnimationModel constructs the AnimationModel, initializing its timer and world
     * @param parent none
     */
    explicit AnimationModel(QObject *parent = nullptr);
    /**
     * @brief ambushAnimation runs the logic for the ambush tactic animation
     */
    void ambushAnimation();
    /**
     * @brief encirclementAnimation runs the logic for the encirclement tactic animation
     */
    void encirclementAnimation();
    /**
     * @brief defeatInDetailAnimation runs the logic for the defeat-in-detail tactic animation
     */
    void defeatInDetailAnimation();
    /**
     * @brief elasticDefenseAnimation runs the logic for our elastic defense animation
     */
    void elasticDefenseAnimation();
    /**
     * @brief infiltrationAnimation runs the logic for our infiltration animation
     */
    void infiltrationAnimation();
    /**
     * @brief feignedRetreatAnimation run the logic for our feigned retreat animation
     */
    void feignedRetreatAnimation();
    /**
     * @brief freeSimAnimation handles the logic for how each soldier should move in the free sim animation after the user selects play.
     */
    void freeSimAnimation();
    /**
     * @brief resetAnimation resets the animation for a new animation to be ran or the same one
     */
    void resetAnimation();
    /**
     * @brief addSoldier adds a soldier to the list of soldiers
     * @param soldierPos the starting position of the soldier
     */
    int addSoldier(QPoint soldierPos);
    /**
     * @brief startWorldTimer starts the world timer
     */
    void startWorldTimer();
    /**
     * @brief getSoldier gets a soldier from the soldier QList
     * @param index the location in the list where the soldier is located
     * @return
     */
    Soldier* getSoldier(int index);

public slots:
    /**
     * @brief moveSoldiers moves the soldier bodies by calling a step in the world, then matches up the labels location with bodies location in the world.
     * It also stops the timer and movement of the soldiers when the timer timeouts. Its called on each timeout of the worlds timer.
     */
    void moveSoldiers();

signals:
    /**
     * @brief moveLabel moves the label to its new position
     * @param soldierId the index of the soldier being moved
     * @param x the new horizontal position
     * @param y the new vertical position
     */
    void moveLabel(int soldierId,int x, int y);
    /**
     * @brief showPlayButton displays the play button after the animation finishes
     */
    void showPlayButton();
    /**
     * @brief clearLabels clears the soldier labels from the UI
     */
    void clearLabels();

    /**
     * @brief soldiersStopped a signal emitted after each soldier has stopped. Used primarily during Free sim.
     */
    void soldiersStopped();
};

#endif // ANIMATIONMODEL_H
