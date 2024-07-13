/*
   Name:       Jacob Ormsby, Jonathan Bancroft, Aric Woodliff, Jiedi Mo, Matthew Duffin, Adrian Regalado

   Date:       12/08/2023

   uID:        u1275849, u1300968, u0586534, u1352501, u1227629, u1348610

   GitHub:     21jormsby, JonBancroft, Aric-W, shotpb, matthew-duffin, AdrianRegalado1123

   Assignment: A9: An-Educational-App

   Description: Holds the logic and methods for manipulation of a Box2d Body that represents a soldier.
*/
#include "soldier.h"
#include <QTimer>

Soldier::Soldier(QPoint pos, b2World* world, QObject *parent)
    : QObject{parent}, world(world), travelLocation(pos)
{
    soldierTimer = new QTimer(this);
    soldierTimer->setInterval(INTERVAL);

    // sets up the soldiers body definition in the world
    b2BodyDef soldierBodyDef;
    soldierBodyDef.type = b2_dynamicBody;
    soldierBodyDef.position.Set(pos.x(), pos.y());
    soldierBodyDef.active = true; // makes sure the body is active.
    soldierBody = world->CreateBody(&soldierBodyDef);

    // Define another box shape for our dynamic body.
    b2CircleShape dynamicCircle;
    dynamicCircle.m_p.Set(1.0f, 1.0f);
    dynamicCircle.m_radius = 20;

    // Define the dynamic body fixture.
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicCircle;

    // Set the box density to be non-zero, so it will be dynamic.
    fixtureDef.density = 100;

    // set the resitution(bounciness)
    fixtureDef.restitution = 0.0f;

    // Add the shape to the body.
    soldierBody->CreateFixture(&fixtureDef);
}
void Soldier::stop()
{
    b2Vec2 position = soldierBody->GetPosition();
    soldierBody->ApplyForce(b2Vec2(0, 0), position, true);
    soldierBody->SetLinearVelocity(b2Vec2(0, 0));
    travelLocation = QPoint(0,0); // resets travel location
    soldierTimer->stop();
}
void Soldier::setMoveDirection(float forceX, float forceY, float constraintX, float constraintY)
{
    // sets the parameter in a way executeForce can access them(globals)
    this->forceX = forceX;
    this->forceY = forceY;
    this->constraintX = constraintX;
    this->constraintY = constraintY;

    connect(soldierTimer,
            &QTimer::timeout,
            this, &Soldier::executeForce);

    soldierTimer->start();

}
void Soldier::setMoveDirectionFreeSim(float forceX, float forceY, float constraintX, float constraintY)
{
    metX = false;
    metY = false;
    // sets the parameter in a way executeForce can access them(globals)
    this->forceX = forceX;
    this->forceY = forceY;
    this->constraintX = constraintX;
    this->constraintY = constraintY;

    connect(soldierTimer,
            &QTimer::timeout,
            this, &Soldier::executeForceFreeSim);

    soldierTimer->start();
}
b2Vec2 Soldier::getPosition()
{
    return soldierBody->GetPosition();
}

void Soldier::executeForce(){
    b2Vec2 position = soldierBody->GetPosition();
    // an if block that determines if the soldiers is in its stopping constraints
    if((       position.x <= (constraintX + 5)
                &&
               position.x >= (constraintX - 5))
            ||
        (      position.y <= (constraintY + 5)
                &&
               position.y >= (constraintY - 5)))
        this->stop();
    else
        soldierBody->ApplyForce(b2Vec2(forceX, forceY), position, true);
}

void Soldier::executeForceFreeSim()
{
    // more complicated checks for if the soldier in free sim mode is in its constraints
    //checks for being within delta and within in window
    bool xCheck =   (getPosition().x <= (constraintX + 5)
                  &&
                    getPosition().x >= (constraintX - 5))
                  ||
                    (getPosition().x >= 815
                  ||
                      getPosition().x <= 135);
    bool yCheck =   (getPosition().y <= (constraintX + 5)
                  &&
                    getPosition().y >= (constraintX - 5))
                  ||
                    (getPosition().y >= 365
                  ||
                    getPosition().y <= -15);
    if(metX && metY)
        this->stop();
    else
    {
        if(xCheck)
        {
            metX = true;
            forceX = 0.0f;
        }
        if(yCheck)
        {
            metY = true;
            forceY = 0.0f;
        }
        soldierBody->ApplyForce(b2Vec2(forceX, forceY), getPosition(), true);
    }
}
void Soldier::destroySoldier()
{
    world->DestroyBody(soldierBody);
}
int Soldier::getID()
{
    return id;
}
void Soldier::setTravelLocation(QPoint coordinate)
{
    travelLocation = coordinate;
}

QPoint Soldier::getTravelLocation()
{
    return travelLocation;
}

void Soldier::moveSoldierFreeSim(float positiveForce, float negativeForce)
{
    float angle = 0.0f;
    float xPos = travelLocation.x();
    float yPos = travelLocation.y();

    angle = abs(qAtan((yPos - this->getPosition().y) / (xPos - this->getPosition().x))); // angle used in math below

    //Make sure xPos and yPos are in window and are not out of bounds. Also determines how the soldier should move based on give coordinates
    if((this->getPosition().x > xPos) && (this->getPosition().y > yPos)) // soldier is to the right and below
        this->setMoveDirectionFreeSim(negativeForce * qCos(angle), negativeForce * qSin(angle), xPos, yPos);

    else if((this->getPosition().x < xPos) && (this->getPosition().y > yPos)) // soldier is to the left and below
        this->setMoveDirectionFreeSim(positiveForce * qCos(angle), negativeForce * qSin(angle), xPos, yPos);

    else if((this->getPosition().x > xPos) && (this->getPosition().y < yPos)) // soldier is to the right and above
        this->setMoveDirectionFreeSim(negativeForce * qCos(angle), positiveForce * qSin(angle), xPos, yPos);

    else if((this->getPosition().x < xPos) && (this->getPosition().y < yPos)) // soldier is to the left and above
        this->setMoveDirectionFreeSim(positiveForce * qCos(angle), positiveForce * qSin(angle), xPos, yPos);
}
