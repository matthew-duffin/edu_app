/*
   Name:       Jacob Ormsby, Jonathan Bancroft, Aric Woodliff, Jiedi Mo, Matthew Duffin, Adrian Regalado

   Date:       12/08/2023

   uID:        u1275849, u1300968, u0586534, u1352501, u1227629, u1348610

   GitHub:     21jormsby, JonBancroft, Aric-W, shotpb, matthew-duffin, AdrianRegalado1123

   Assignment: A9: An-Educational-App

   Description: Runs the logic to manipulate soldiers in our animations and free sim.
*/
#include "animationmodel.h"

AnimationModel::AnimationModel(QObject *parent)
    : QObject{parent}, world(b2World(b2Vec2(0.0f, 0.0f)))
{
    // setup timer
    worldTimer = new QTimer(this);
    worldTimer->setInterval(30);

    connect(worldTimer,
            &QTimer::timeout,
            this, &AnimationModel::moveSoldiers);
}
void AnimationModel::ambushAnimation()
{
    isFreeSim = false;
    animationLength = 2400;
    currentRunTime = 0;
    // moves all the soldiers
    for(int i = 0; i < 8; i++)
    {
        if(i < 4) // moves the blue, allied soldiers first
            soldiers[i]->setMoveDirection(0.0f, negativeForce, 800, 190);
        else if(i >= 4 && i < 8) // moves the red, enemy soldiers last
            soldiers[i]->setMoveDirection(0.0f, positiveForce, 800, 100);
    }
}
void AnimationModel::encirclementAnimation()
{
    isFreeSim = false;
    animationLength = 5000;
    currentRunTime = 0;

    QList<int> wings{0, 1, 5, 6}; // moves the blue allies on the left and right wings first
    soldiers[wings[0]]->setMoveDirection(0.0f, negativeForce, 800, 50);
    soldiers[wings[2]]->setMoveDirection(0.0f, negativeForce, 800, 50);
    soldiers[wings[1]]->setMoveDirection(0.0f, negativeForce, 800, 110);
    soldiers[wings[3]]->setMoveDirection(0.0f, negativeForce, 800, 110);

    // second orders for soldiers on bottom of each wing. This is how they change direction
    QTimer::singleShot(2400, this,   [this]{soldiers[1]->setMoveDirection(positiveForce, 0.0f, 350, 800);});
    QTimer::singleShot(2400, this,   [this]{soldiers[6]->setMoveDirection(negativeForce, 0.0f, 525, 800);});

    // second orders for soldiers on top of each wing
    QTimer::singleShot(2400, this,   [this]{soldiers[0]->setMoveDirection(positiveForce, 0.0f, 400, 800);});
    QTimer::singleShot(2400, this,   [this]{soldiers[5]->setMoveDirection(negativeForce, 0.0f, 475, 800);});

    // third orders for soldiers on top of each wing
    QTimer::singleShot(3900, this,   [this]{soldiers[0]->setMoveDirection(0.0f, positiveForce, 800, 90);});
    QTimer::singleShot(3900, this,   [this]{soldiers[5]->setMoveDirection(0.0f, positiveForce, 800, 90);});

    QList<int> centerLine{2, 3, 4}; // moves the 3 soldiers on the center line
    for(int i = 0; i < centerLine.length(); i++)
    {
        soldiers[centerLine[i]]->setMoveDirection(0.0f, negativeForce, 800, 160);
    }
}
void AnimationModel::defeatInDetailAnimation()
{
    isFreeSim = false;
    animationLength = 15000;
    currentRunTime = 0;

    QList<int> boat1{0,1};
    QList<int> boat2{2,3};
    QList<int> boat3{4,5};

    // phase 1 movement, moves all allies out of their boats and onto the beach
    soldiers[boat1[0]]->setMoveDirection(negativeForce, negativeForce, 190, 130);
    soldiers[boat1[1]]->setMoveDirection(0.0f, negativeForce, 800, 130);
    soldiers[boat2[0]]->setMoveDirection(negativeForce, negativeForce, 800, 130);
    soldiers[boat2[1]]->setMoveDirection(0.0f, negativeForce, 800, 130);
    soldiers[boat3[0]]->setMoveDirection(0.5*negativeForce, negativeForce, 800, 120);
    soldiers[boat3[1]]->setMoveDirection(0.2*positiveForce, negativeForce, 800, 120);

    // Part 2 of Phase 1 movement moves two of the allied soldiers left on the beach
    QTimer::singleShot(2000, this,   [this]{soldiers[2]->setMoveDirection(negativeForce, 0.0f, 300, 0);});
    QTimer::singleShot(2000, this,   [this]{soldiers[3]->setMoveDirection(negativeForce, 0.0f, 330, 0);});


    //Phase 2 pushes the left 4 enemy soldiers out of the beach
    QTimer::singleShot(3500, this,   [this]{soldiers[0]->setMoveDirection(0.1*negativeForce, negativeForce, 800,  -15);});
    QTimer::singleShot(3500, this,   [this]{soldiers[1]->setMoveDirection(0.0f, negativeForce, 800,  -15);});
    QTimer::singleShot(3500, this,   [this]{soldiers[2]->setMoveDirection(0, negativeForce, 800,  -15);});
    QTimer::singleShot(3500, this,   [this]{soldiers[3]->setMoveDirection(0.1*negativeForce, negativeForce, 800,  -15);});
    QTimer::singleShot(5800, this,   [this]{soldiers[0]->setMoveDirection(0.1*negativeForce, 0.4*positiveForce, 140,  350);});

    //Phase 3 repositions soldiers on the left side of the beach
    QTimer::singleShot(7000, this,   [this]{soldiers[0]->setMoveDirection(0.5*positiveForce, positiveForce, 800,  120);});
    QTimer::singleShot(7000, this,   [this]{soldiers[1]->setMoveDirection(0.0f, positiveForce, 800,  120);});
    QTimer::singleShot(7000, this,   [this]{soldiers[2]->setMoveDirection(0.0f, positiveForce, 800,  120);});
    QTimer::singleShot(7000, this,   [this]{soldiers[3]->setMoveDirection(0.0f, positiveForce, 800,  120);});

    //Phase 4 concentrates the 4 left side soldiers to the right
    QTimer::singleShot(9000, this,   [this]{soldiers[0]->setMoveDirection(positiveForce, 0.0f, 420,  350);});
    QTimer::singleShot(9000, this,   [this]{soldiers[1]->setMoveDirection(positiveForce, 0.0f, 480,  350);});
    QTimer::singleShot(9000, this,   [this]{soldiers[2]->setMoveDirection(positiveForce, 0.0f, 540,  350);});
    QTimer::singleShot(9000, this,   [this]{soldiers[3]->setMoveDirection(positiveForce, 0.0f, 600,  350);});

    //Phase 4 finishes off the last 6 soldiers
    QTimer::singleShot(12600, this,   [this]{soldiers[0]->setMoveDirection(0.0f, negativeForce, 800,  -20);});
    QTimer::singleShot(12600, this,   [this]{soldiers[1]->setMoveDirection(0.0f, negativeForce, 800,  -20);});
    QTimer::singleShot(12600, this,   [this]{soldiers[2]->setMoveDirection(0.5*positiveForce, negativeForce, 800,  -20);});
    QTimer::singleShot(12600, this,   [this]{soldiers[3]->setMoveDirection(0.5*positiveForce, negativeForce, 800,  -20);});
    QTimer::singleShot(12600, this,   [this]{soldiers[4]->setMoveDirection(0.5*positiveForce, negativeForce, 800,  -20);});
    QTimer::singleShot(12600, this,   [this]{soldiers[5]->setMoveDirection(0.5*positiveForce, negativeForce, 800,  -20);});

}
void AnimationModel::elasticDefenseAnimation()
{
    isFreeSim = false;
    animationLength = 6500;
    currentRunTime = 0;

    QList<int> lures{8, 9, 10};
    // phase 1 movement, moves the blue lures back up the image to the hiding ally forces
    soldiers[lures[0]]->setMoveDirection(0.0f, negativeForce, 800, 20);
    soldiers[lures[1]]->setMoveDirection(negativeForce, negativeForce, 150, 100);
    soldiers[lures[2]]->setMoveDirection(positiveForce, negativeForce, 800, 90);

    QList<int> enemies{11, 12, 13, 14, 15, 16, 17};
    // causes all the enemies to follow the blue lures
    soldiers[enemies[0]]->setMoveDirection(negativeForce, negativeForce, 150, 180);
    soldiers[enemies[1]]->setMoveDirection(negativeForce, negativeForce, 180, 180);
    soldiers[enemies[2]]->setMoveDirection(0.0f, negativeForce, 800, 90);
    soldiers[enemies[3]]->setMoveDirection(0.0f, negativeForce, 800, 80);
    soldiers[enemies[4]]->setMoveDirection(0.0f, negativeForce, 800, 90);
    soldiers[enemies[5]]->setMoveDirection(positiveForce, negativeForce, 700, 170);
    soldiers[enemies[6]]->setMoveDirection(positiveForce, negativeForce, 700, 190);

    // phase 2 movement, causes all allied soldiers to collapse and push enemy soldiers to the bottom of the screen
    QTimer::singleShot(3000, this,   [this]{soldiers[8]->setMoveDirection(0.0f, positiveForce, 800, 200);});
    QTimer::singleShot(3000, this,   [this]{soldiers[9]->setMoveDirection(positiveForce, positiveForce, 330, 281);});
    QTimer::singleShot(3000, this,   [this]{soldiers[10]->setMoveDirection(negativeForce, positiveForce, 280, 220);});

    QTimer::singleShot(3000, this,   [this]{soldiers[0]->setMoveDirection(positiveForce, positiveForce, 330, 280);});
    QTimer::singleShot(3000, this,   [this]{soldiers[1]->setMoveDirection(positiveForce, positiveForce, 280, 200);});
    QTimer::singleShot(3000, this,   [this]{soldiers[2]->setMoveDirection(positiveForce, positiveForce, 290, 210);});

    QTimer::singleShot(3000, this,   [this]{soldiers[3]->setMoveDirection(0.0f, positiveForce, 800, 250);});
    QTimer::singleShot(3000, this,   [this]{soldiers[4]->setMoveDirection(0.0f, positiveForce, 800, 250);});
    QTimer::singleShot(3000, this,   [this]{soldiers[5]->setMoveDirection(negativeForce, positiveForce, 260, 280);});
    QTimer::singleShot(3000, this,   [this]{soldiers[6]->setMoveDirection(negativeForce, positiveForce, 220, 180);});
    QTimer::singleShot(3000, this,   [this]{soldiers[7]->setMoveDirection(negativeForce, positiveForce, 310, 230);});
}

void AnimationModel::infiltrationAnimation()
{
    isFreeSim = false;
    animationLength = 7000;
    currentRunTime = 0;
    //phase 1 troops infiltrate the trench
    soldiers[0]->setMoveDirection(0.8*positiveForce, negativeForce, 800, 50);
    soldiers[1]->setMoveDirection(0.8*positiveForce, negativeForce, 800, 100);
    soldiers[2]->setMoveDirection(0.8*positiveForce, negativeForce, 800, 50);
    soldiers[3]->setMoveDirection(0.8*positiveForce, negativeForce, 800, 100);

    // phase 2 front line moves up with infiltration troops
    QTimer::singleShot(1000, this,   [this]{soldiers[4]->setMoveDirection(0.1*positiveForce, negativeForce, 800, 50);});
    QTimer::singleShot(1000, this,   [this]{soldiers[5]->setMoveDirection(0.1*positiveForce, negativeForce, 800, 50);});
    QTimer::singleShot(1000, this,   [this]{soldiers[6]->setMoveDirection(0.0f, negativeForce, 800, 120);});
    QTimer::singleShot(1000, this,   [this]{soldiers[7]->setMoveDirection(0.0f, negativeForce, 800, 60);});
    QTimer::singleShot(1000, this,   [this]{soldiers[8]->setMoveDirection(0.0f, negativeForce, 800, 10);});
    QTimer::singleShot(1000, this,   [this]{soldiers[9]->setMoveDirection(0.0f, negativeForce, 800, 10);});

    //phase 3 the trench is cleared by the allied soldiers
    QTimer::singleShot(3000, this,   [this]{soldiers[0]->setMoveDirection(negativeForce, negativeForce, 800, 0);});
    QTimer::singleShot(3000, this,   [this]{soldiers[1]->setMoveDirection(negativeForce, negativeForce, 800, 0);});
    QTimer::singleShot(3500, this,   [this]{soldiers[2]->setMoveDirection(positiveForce, 0.6*negativeForce, 600, -10);});
    QTimer::singleShot(3500, this,   [this]{soldiers[3]->setMoveDirection(positiveForce, 0.5*negativeForce, 800, 40);});
    QTimer::singleShot(4500, this,   [this]{soldiers[6]->setMoveDirection(0.0f, negativeForce, 800, 90);});
}

void AnimationModel::feignedRetreatAnimation()
{
    isFreeSim = false;
    animationLength = 7000;
    currentRunTime = 0;

    QList<int> lures{4, 5};
    // phase 1, causes allied lures to lead enemy soldier to allied reinforcements
    soldiers[lures[0]]->setMoveDirection(0.0f, negativeForce, 800, 60);
    soldiers[lures[1]]->setMoveDirection(0.0f, negativeForce, 800, 60);

    QList<int> enemies{6, 7, 8};
    // causes all enemies to follow the lures
    soldiers[enemies[0]]->setMoveDirection(0.0f, negativeForce, 800,110);
    soldiers[enemies[1]]->setMoveDirection(0.0f, negativeForce, 800, 110);
    soldiers[enemies[2]]->setMoveDirection(0.0f, negativeForce, 800, 110);

    // phase 2, causes outside two allied soldiers to begin chasing the enemy first
    QTimer::singleShot(3000, this,   [this]{soldiers[0]->setMoveDirection(0.0, positiveForce, 800, 300);});
    QTimer::singleShot(3000, this,   [this]{soldiers[3]->setMoveDirection(0.0, positiveForce, 800, 300);});

    // phase 3, middle allied troops move down on an offset after the wings
    QTimer::singleShot(3500, this,   [this]{soldiers[1]->setMoveDirection(0.0, positiveForce, 800, 300);});
    QTimer::singleShot(3500, this,   [this]{soldiers[2]->setMoveDirection(0.0, positiveForce, 800, 300);});
    QTimer::singleShot(3500, this,   [this]{soldiers[4]->setMoveDirection(0.0, positiveForce, 800, 300);});
    QTimer::singleShot(3500, this,   [this]{soldiers[5]->setMoveDirection(0.0, positiveForce, 800, 300);});

}
void AnimationModel::freeSimAnimation()
{
    isFreeSim = true;
    animationLength = 3000;
    currentRunTime = 0;
    // moves every single soldier in the soldiers list
    for(Soldier* soldier : soldiers)
    {
        bool invalidLocations = soldier->getTravelLocation().x() == 0 && soldier->getTravelLocation().y() ==  0;

        // if in an invalid location, soldier should not move
        if(invalidLocations)
        {
            soldier->stop();
        }
        else
            soldier->moveSoldierFreeSim(positiveForce, negativeForce);
    }
}

void AnimationModel::resetAnimation()
{
    emit clearLabels();
    for(Soldier* soldier : soldiers)
    {
        soldier->destroySoldier();
    }
    soldiers.clear();
}

int AnimationModel::addSoldier(QPoint soldierPos)
{
    soldiers.append(new Soldier(soldierPos, &world, nullptr));
    return soldiers.length() - 1; // returns the index of the most recently added soldier
}
void AnimationModel::moveSoldiers()
{
    currentRunTime += 30; // increments the run time so we know how long the animation has been playing for
    if(animationLength > currentRunTime)
    {
        world.Step(timeStep, velocityIterations, positionIterations); // move the world
        // get the soldiers position, as soldier was moved in world by world step, then update the label to match this location
        for(int i = 0; i < soldiers.length(); i++)
        {
            b2Vec2 position = soldiers[i]->getPosition();
            emit moveLabel(i, position.x, position.y);
        }
    }
    else // stop everything once we have reached the end of the animations runtime
    {
        worldTimer->stop();

        if(!isFreeSim)
            emit showPlayButton();
        else
            emit soldiersStopped();
        for(int i = 0; i < soldiers.length(); i++)
            soldiers[i]->stop();
    }
}
void AnimationModel::startWorldTimer()
{
    worldTimer->start();
}
Soldier* AnimationModel::getSoldier(int ID)
{
    return soldiers[ID];
}
