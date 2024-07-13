/*
   Name:       Jacob Ormsby, Jonathan Bancroft, Aric Woodliff, Jiedi Mo, Matthew Duffin, Adrian Regalado

   Date:       12/08/2023

   uID:        u1275849, u1300968, u0586534, u1352501, u1227629, u1348610

   GitHub:     21jormsby, JonBancroft, Aric-W, shotpb, matthew-duffin, AdrianRegalado1123

   Assignment: A9: An-Educational-App

   Description: Body implementation of the model class for the tactics program.
                Handles all the logic and connection for the mainwindow, the quizwindow,
                the animation model, and the free-play mode.
*/

#include "model.h"
#include <QFile>
#include <QString>
#include <QTextStream>
#include "animationmodel.h"

Model::Model(QObject *parent)
    : QObject{parent}, currentTacticID(0), questionIndex(0), quizScore(0), quizSelection(0)
{
    populateTacticCategory(":/TacticDescriptions.txt", tacticsDescription);
    populateTacticCategory(":/TacticFunFacts.txt", tacticsFunFacts);
    populateTacticCategory(":/TacticHistory.txt", tacticsHistory);
    isFreePlayEnabled = false;
    activeTool = noTool;

    connect(&animations,
            &AnimationModel::soldiersStopped,
            this,
            &Model::receiveSoldiersStopped);
}

void Model::startAnimation()
{
    animations.resetAnimation();
    prepopulateScreen();
    switch (currentTacticID) {
    case 0:
        animations.ambushAnimation();
        break;
    case 1:
        animations.encirclementAnimation();
        break;
    case 2:
        animations.defeatInDetailAnimation();
        break;
    case 3:
        animations.elasticDefenseAnimation();
        break;
    case 4:
        animations.infiltrationAnimation();
        break;
    case 5:
        animations.feignedRetreatAnimation();
        break;
    default:
        break;
    }
    emit hidePlayButton();
    animations.startWorldTimer();
}
QList<QPoint> Model::returnCoordinates(QString fileName)
{
    QList<QPoint> soldierCoords;
    QStringList line;
    QFile* file = new QFile(fileName);

    try
    {
        file->open(QIODevice::ReadOnly);
        file->readLine();

        while(!file->atEnd())
        {
            // grabs the first line of the file, converts it to a QString list, seperated by a ','
            line = QString(file->readLine()).split(',');
            // adds a QPoint made up of the x and y from the file to the soldier coords.
            soldierCoords.append(QPoint(line[0].toInt(), line[1].toInt()));
        }
    }
    catch(_exception e){}

    file->close();
    return soldierCoords;
}
void Model::setUpSoldiers(int numberOfAllies, int totalNumberOfSoldiers, QList<QPoint>soldierCoords)
{
    // add qLabels for allies and soldier objects
    for(int i = 0; i < numberOfAllies; i++)
    {
        int soldierID = animations.addSoldier(soldierCoords[i]);
        emit makeASoldierLabel(soldierCoords[i], false, false, soldierID);
    }

    // add qLabels for enemies and soldier objects
    for(int i = numberOfAllies; i < totalNumberOfSoldiers; i++)
    {
        int soldierID = animations.addSoldier(soldierCoords[i]);
        emit makeASoldierLabel(soldierCoords[i], true, false, soldierID);
    }
}

void Model::setUpSingleSoldier(QPoint spawnPoint, bool isEnemy)
{
    int soldierID = animations.addSoldier(spawnPoint);
    emit makeASoldierLabel(spawnPoint, isEnemy, true, soldierID);
}

void Model::prepopulateInitialTactic()
{
    emit setBackground(QPixmap(":ambushBackground.png"));
    // gets the coordinates of each soldier for the animation
    QList<QPoint> soldierCoords = returnCoordinates(":/ambush.csv");
    setUpSoldiers(8, 14, soldierCoords);
}

void Model::prepopulateScreen()
{
    QList<QPoint> soldierCoords;
    //sets up up the animation according to the tactic id
    switch(currentTacticID)
    {
    case 0:
        emit setBackground(QPixmap(":ambushBackground.png"));
        // gets the coordinates of each soldier for the animation
        soldierCoords = returnCoordinates(":/ambush.csv");
        setUpSoldiers(8, 14, soldierCoords);

        break;
    case 1:
        emit setBackground(QPixmap(":encirclementBackground.png"));

        // gets the coordinates of each soldier for the animation
        soldierCoords = returnCoordinates(":/encirclement.csv");
        setUpSoldiers(7, 10, soldierCoords);

        break;
    case 2:
        emit setBackground(QPixmap(":defeatInDetailBackground.png"));

        // gets the coordinates of each soldier for the animation
        soldierCoords = returnCoordinates(":/defeatInDetail.csv");
        setUpSoldiers(6, 16, soldierCoords);

        break;
    case 3:
        emit setBackground(QPixmap(":elasticDefenseBackground.png"));

        // gets the coordinates of each soldier for the animation
        soldierCoords = returnCoordinates(":/elasticDefense.csv");
        setUpSoldiers(11, 18, soldierCoords);

        break;
    case 4:
        emit setBackground(QPixmap(":infiltrationBackground.png"));

        // gets the coordinates of each soldier for the animation
        soldierCoords = returnCoordinates(":/infiltration.csv");
        setUpSoldiers(10, 16, soldierCoords);

        break;
    case 5:
        emit setBackground(QPixmap(":feignedRetreatBackground.png"));

        // gets the coordinates of each soldier for the animation
        soldierCoords = returnCoordinates(":/feignedRetreat.csv");
        setUpSoldiers(6, 9, soldierCoords);

        break;
    }
}
void Model::choice1()
{
    if(1 == correctAnswers[questionIndex])
    {
        if(unansweredQuestions[questionIndex])
        {
            quizScore++;
            unansweredQuestions[questionIndex] = false;
            checkForCompletion();
        }
    }
    else
        emit incorrectChoice(1);

    emit updateUIScore("Score: " + QString::number(quizScore) + "/" + QString::number(questions.size()));
}

void Model::choice2()
{
    if(2 == correctAnswers[questionIndex])
    {
        if(unansweredQuestions[questionIndex])
        {
            quizScore++;
            unansweredQuestions[questionIndex] = false;
            checkForCompletion();
        }
    }
    else
        emit incorrectChoice(2);

    emit updateUIScore("Score: " + QString::number(quizScore) + "/" + QString::number(questions.size()));
}

void Model::choice3()
{
    if(3 == correctAnswers[questionIndex])
    {
        if(unansweredQuestions[questionIndex])
        {
            quizScore++;
            unansweredQuestions[questionIndex] = false;
            checkForCompletion();
        }
    }
    else
        emit incorrectChoice(3);

    emit updateUIScore("Score: " + QString::number(quizScore) + "/" + QString::number(questions.size()));
}

void Model::choice4()
{
    if(4 == correctAnswers[questionIndex])
    {
        if(unansweredQuestions[questionIndex])
        {
            quizScore++;
            unansweredQuestions[questionIndex] = false;
            checkForCompletion();
        }
    }
    else
        emit incorrectChoice(4);

    emit updateUIScore("Score: " + QString::number(quizScore) + "/" + QString::number(questions.size()));
}

void Model::changeNextQuestion()
{
    if((questions.size() - 1) > questionIndex)
    {
        emit enablePreviousButton(true);
        questionIndex++;
        emit passQuizUIInfo(currentTacticID, questionIndex, questions[questionIndex], choices1[questionIndex],
                            choices2[questionIndex], choices3[questionIndex], choices4[questionIndex]);

        // Check for last question
        if((questions.size() - 1) == questionIndex)
        {
            emit enablePreviousButton(true);
            emit enableNextButton(false);
        }
    }
}

void Model::changePreviousQuestion()
{
    if(0 <= questionIndex)
    {
        emit enableNextButton(true);
        questionIndex--;
        emit passQuizUIInfo(currentTacticID, questionIndex, questions[questionIndex], choices1[questionIndex],
                            choices2[questionIndex], choices3[questionIndex], choices4[questionIndex]);
        if(0 == questionIndex)
        {
            emit enablePreviousButton(false);
            emit enableNextButton(true);
        }
    }
}

void Model::checkForCompletion()
{
    //checks if all 4 questions are right
    if(questions.size() == quizScore)
    {
        tacticsQuizCompletion[currentTacticID] = true;
        emit showCompletedTacticStatus(currentTacticID);
        emit reportCompletion();

        for (bool check : tacticsQuizCompletion)
            if(check == false)
                return;

        emit enableFreePlayButton(true);
    }
}

void Model::populateQuizQuestions(QString categoryFilePath, QVector<QString>& questions,
                                   QVector<QString>& choices1, QVector<QString>& choices2,
                                   QVector<QString>& choices3, QVector<QString>& choices4,
                                   QVector<int>& correctAnswers)
  {
    QFile file(categoryFilePath);
    QString line;

    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream fileReader(&file);
    //reads every line and sorts them into respective QVectors
    //# is the identifier for the line
    while(!fileReader.atEnd())
    {
        QString currentLine = fileReader.readLine();

        if(currentLine == "")
            continue;
        else if(currentLine == "#QuizQuestion")
        {
            questions.append(line);
            line = "";
        }
        else if(currentLine == "#Choice1")
        {
            choices1.append(line);
            line = "";
        }
        else if(currentLine == "#Choice2")
        {
            choices2.append(line);
            line = "";
        }
        else if(currentLine == "#Choice3")
        {
            choices3.append(line);
            line = "";
        }
        else if(currentLine == "#Choice4")
        {
            choices4.append(line);
            line = "";
        }
        else if(currentLine == "#CorrectAnswer")
        {
            correctAnswers.append(line.toInt());
            line = "";
        }
        else
            line.append(currentLine);
    }

    file.close();
}


void Model::populateTacticCategory(QString categoryFilePath, map<int, QString>& tacticsCategory)
{
    QFile file(categoryFilePath);
    QString line;

    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream fileReader(&file);
    int currentTacticID = 0;
    //parses the data in the file into arrays for later displaying
    while(!fileReader.atEnd())
    {
        QString currentLine = fileReader.readLine();

        if(currentLine == "")
            continue;
        else if(currentLine == "###")
        {
            tacticsCategory[currentTacticID] = line;
            currentTacticID++;
            line = "";
        }
        else
            line.append(currentLine);
    }

    file.close();
}

void Model::changeQuizSelection()
{
    questionIndex = 0;
    quizScore = 0;
    questions.clear();
    choices1.clear();
    choices2.clear();
    choices3.clear();
    choices4.clear();
    correctAnswers.clear();
    unansweredQuestions.clear();
    populateQuizQuestions(":/TacticQuiz" + QString::number(currentTacticID + 1) + ".txt", questions, choices1, choices2, choices3, choices4, correctAnswers);

    for (int i = 0; i < questions.size(); i++)
        unansweredQuestions.append(true);

    quizSelection = currentTacticID + 1;

    emit showQuizUIFirstQuestion(currentTacticID, 0, questions[0], choices1[0], choices2[0], choices3[0], choices4[0], tacticsQuizCompletion[currentTacticID]);
}

void Model::getDescription()
{
    emit updateContent(tacticsDescription[currentTacticID], "description", currentTacticID);
}

void Model::getHistory()
{
    emit updateContent(tacticsHistory[currentTacticID], "history", currentTacticID);
}

void Model::getFunFacts()
{
    emit updateContent(tacticsFunFacts[currentTacticID], "funfacts", currentTacticID);
}

void Model::changeTactic()
{
    //gets the button name and converts it to an int to identify the tactic associated
    QString senderName = sender()->objectName();
    int tacticNum = QString(senderName.back()).toInt();

    currentTacticID = tacticNum - 1;
    getDescription();
    animations.resetAnimation();
    prepopulateScreen();
}

void Model::enableFreePlay()
{
    isFreePlayEnabled = true;
    animations.resetAnimation();
    emit startFreePlayMode();
    emit setBackground(QPixmap(":encirclementBackground.png"));
}

void Model::receiveMouseCoordinates(QPoint mouseCoords, int ID)
{
    if(!isFreePlayEnabled || activeTool == noTool)
        return;

    QPoint centeredMouseCoords = QPoint(mouseCoords.x()-25, mouseCoords.y()-25);

    if(activeTool == placeAlly)
        setUpSingleSoldier(centeredMouseCoords, false);
    else if(activeTool == placeEnemy)
        setUpSingleSoldier(centeredMouseCoords, true);
    else
    {
        animations.getSoldier(ID)->setTravelLocation(mouseCoords);
        emit sendTrajectoryPoint(mouseCoords);
    }
}

void Model::setActiveToolTrajectoryPoint()
{
    setActiveTool(addTrajectoryPoint);
    emit toggleTrajectoryTool();
}

void Model::setActiveToolPlaceAlly()
{
    setActiveTool(placeAlly);
    emit togglePlaceAllyTool();
}

void Model::setActiveToolPlaceEnemy()
{
    setActiveTool(placeEnemy);
    emit togglePlaceEnemyTool();
}

void Model::setActiveTool(tools tool)
{
    if(activeTool == tool)
        activeTool = noTool;
    else
        activeTool = tool;
}

void Model::simulateFreeSimStep()
{
    emit toggleToolStatus(false);
    activeTool = noTool;
    animations.freeSimAnimation();
    animations.startWorldTimer();
}

void Model::receiveSoldiersStopped()
{
    emit toggleToolStatus(true);
}

void Model::receiveSetNoActiveTool()
{
    activeTool = noTool;
}

void Model::receiveResetFreeSim()
{
    receiveSetNoActiveTool();
    animations.resetAnimation();
}

void Model::endFreePlay()
{
    // disable all the UI elements.
    receiveSetNoActiveTool();
    isFreePlayEnabled = false;
    animations.resetAnimation();
    currentTacticID = 0;
    prepopulateInitialTactic();
    getDescription();
}
