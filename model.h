/*
   Name:       Jacob Ormsby, Jonathan Bancroft, Aric Woodliff, Jiedi Mo, Matthew Duffin, Adrian Regalado

   Date:       12/08/2023

   uID:        u1275849, u1300968, u0586534, u1352501, u1227629, u1348610

   GitHub:     21jormsby, JonBancroft, Aric-W, shotpb, matthew-duffin, AdrianRegalado1123

   Assignment: A9: An-Educational-App

   Description: Header implementation of the model class for the tactics program.
                Handles all the logic and connection for the mainwindow, the quizwindow,
                the animation model, and the free-play mode.
*/

#ifndef MODEL_H
#define MODEL_H

#include "animationmodel.h"
#include <map>
#include <QString>
#include <QObject>
#include <Box2D/Box2D.h>
#include <QTimer>
#include <QMap>
#include <QLabel>
#include <QFile>
#include <QPoint>

using std::map;
using std::string;

class Model : public QObject
{
    Q_OBJECT

private:
    map<int, QString> tacticsDescription;
    map<int, QString> tacticsFunFacts;
    map<int, QString> tacticsHistory;
    int currentTacticID;
    QTimer* timer;
    int animationId = 1;
    const float positiveForce = 72000000.0f;
    const float negativeForce = -72000000.0f;
    bool isFreePlayEnabled;

    /**
     * @brief setUpSingleSoldier : positions a single soldier for free sim mode
     * @param spawnPoint : where the soldier should be located
     * @param isEnemy : determines if the soldier is an ally or an enemy
     */
    void setUpSingleSoldier(QPoint spawnPoint, bool isEnemy);

    /**
     * @brief setUpSoldiers : sets up the soldiers for the animation. Important to note that the allies are set up first
     * @param numberOfAllies : how many friendly soldiers are in a given animation
     * @param totalNumberOfSoldiers : used to determine how many enemies to make, by getting the difference from numberOfAllies
     * @param soldierCoords : the positions of all the soldiers
     */
    void setUpSoldiers(int numberOfAllies, int totalNumberOfSoldiers, QList<QPoint>soldierCoords);

    /**
     * @brief returnCoordinates : returns the starting coordinates of all the soldiers from a file
     * @param fileName : the name of the file
     * @return returns a list of 1 coordinate per soldier.
     */
    QList<QPoint> returnCoordinates(QString fileName);

    /**
     * @brief prepopulateScreen : prepopulates the screen with the soldiers and background when a tactic is selected
     */
    void prepopulateScreen();

    /**
     * @brief questions : QVector of QStrings used to store all the questions for a respective tactic.
     */
    QVector<QString> questions;

    /**
     * @brief choices1 : QVector of QStrings used to store all the first choices for a respective tactic.
     */
    QVector<QString> choices1;

    /**
     * @brief choices2 : QVector of QStrings used to store all the second choices for a respective tactic.
     */
    QVector<QString> choices2;

    /**
     * @brief choices3 : QVector of QStrings used to store all the third choices for a respective tactic.
     */
    QVector<QString> choices3;

    /**
     * @brief choices4 : QVector of QStrings used to store all the fourth choices for a respective tactic.
     */
    QVector<QString> choices4;

    /**
     * @brief choices4 : QVector of Integers used to store all the correct choices for a respective tactic.
     */
    QVector<int> correctAnswers;

    /**
     * @brief unansweredQuestions : QVector of booleans that tracks the status of unanswered questions.
     */
    QVector<bool> unansweredQuestions;

    /**
     * @brief questionIndex : Integer value representing the current question index value.
     */
    int questionIndex;

    /**
     * @brief questionIndex : Integer value representing the quiz score.
     */
    int quizScore;

    /**
     * @brief questionIndex : Integer value representing the quiz corresponding to the current tactic ID.
     */
    int quizSelection;

    /**
     * @brief checkForCompletion : Checks if the current quiz is completed.
     */
    void checkForCompletion();

    /**
     * @brief tacticsQuizCompletion : Array of booleans that tracks the completion status of the quiz for each tactic.
     */
    bool tacticsQuizCompletion[6] = {false, false, false, false, false, false};

public:

    /**
     * Constructor : creates an instance of the Model.
     */
    explicit Model(QObject *parent = nullptr);

    enum tools {placeAlly, placeEnemy, addTrajectoryPoint, noTool};
    tools activeTool;
    AnimationModel animations; // holds the animation methods and fields. Runs underlying box2d logic behind the scenes.

    /**
     * @brief populateQuizQuestions : Reads through several different text files and inserts information into several corresponding QVectors.
     * @param categoryFilePath : QString value that represents the directory to a selected file.
     * @param questions : QVector of QStrings that represent the question being asked.
     * @param choices1 : QVector of QStrings that represent the first choice.
     * @param choices2 : QVector of QStrings that represent the second choice.
     * @param choices3 : QVector of QStrings that represent the third choice.
     * @param choices4 : QVector of QStrings that represent the fourth choice.
     * @param correctAnswers : QVector of integer values that represent the correct choice.
     */
    void populateQuizQuestions(QString categoryFilePath, QVector<QString>& questions,
                                QVector<QString>& choices1, QVector<QString>& choices2,
                                QVector<QString>& choices3, QVector<QString>& choices4,
                                QVector<int>& correctAnswers);

    /**
     * @brief changeQuizSelection : Helper method that cleans and changes quiz UI elements to the current tactic.
     */
    void changeQuizSelection();

    /**
     * @brief populateTacticCategory : populates a tactic category for each tactic with information
     *                                 about that category from a file.
     * @param categoryFilePath : the file path containing the category information.
     * @param tacticsCategory : the data structure holding the tactic category information for each category.
     */
    void populateTacticCategory(QString categoryFilePath, map<int, QString>& tacticsCategory);

private:
    /**
     * @brief setActiveTool : helper method that sets the active tool.
     * @param activeTool : the tool that should be the active tool.
     */
    void setActiveTool(tools tool);

public slots:
    /**
     * @brief choice1 : Called when the user selects the first choice.
     */
    void choice1();

    /**
     * @brief choice2 : Called when the user selects the second choice.
     */
    void choice2();

    /**
     * @brief choice3 : Called when the user selects the third choice.
     */
    void choice3();

    /**
     * @brief choice4 : Called when the user selects the fourth choice.
     */
    void choice4();

    /**
     * @brief changeNextQuestion : Called when the user presses the Next Question button.
     */
    void changeNextQuestion();

    /**
     * @brief changePreviousQuestion : Called when the user presses the Previous Question button.
     */
    void changePreviousQuestion();

    /**
     * @brief getDescription : Emits the description of the current tactic to the view.
     */
    void getDescription();

    /**
     * @brief getHistory : Emits the history of the current tactic to the view.
     */
    void getHistory();

    /**
     * @brief getFunFacts : Emits the fun facts of the current tactic to the view.
     */
    void getFunFacts();

    /**
     * @brief changeTactic : changes the current tactic and resets the animations.
     */
    void changeTactic();

    /**
     * @brief startAnimation : starts the animation on play button click
     */
    void startAnimation();

    /**
     * @brief prepopulateInitialTactic : initial prepopulation for tactic 1 when the program is loaded
     */
    void prepopulateInitialTactic();

    /**
     * @brief enableFreePlay : sets up the free sim mode
     */
    void enableFreePlay();

    /**
     * @brief receiveMouseCoordinates : Gets the mouse coordinates from the view and depending on which
     *                                  tool is active, changes the internal data of the model.
     * @param mouseCoordinates : The mouse coordinates from the view in the animation window.
     * @param ID : The ID of the currently clicked soldier (-1 if there is no currently clicked soldier).
     */
    void receiveMouseCoordinates(QPoint mouseCoordinates, int ID);

    /**
     * @brief setActiveToolTrajectoryPoint : sets the active tool to add trajectory point.
     */
    void setActiveToolTrajectoryPoint();

    /**
     * @brief setActiveToolPlaceAlly : sets the active tool to place ally.
     */
    void setActiveToolPlaceAlly();

    /**
     * @brief setActiveToolPlaceEnemy : sets the active to to place enemy.
     */
    void setActiveToolPlaceEnemy();

    /**
     * @brief simulateFreeSimStep : starts a step of the "Free Play" mode animation and disables the active tool
     *                              while the animation step is playing.
     */
    void simulateFreeSimStep();

    /**
     * @brief receiveSoldiersStopped : a slot that receives a signal from the animation model of when the
     *                                 soldiers of the animation window have stopped moving. Emits a signal
     *                                 to re-enable buttons/tools of the "Free Play" mode after.
     */
    void receiveSoldiersStopped();

    /**
     * @brief receiveSetNoActiveTool : a slot that sets the active tool to nothing.
     */
    void receiveSetNoActiveTool();

    /**
     * @brief receiveResetFreeSim : resets the backing logic of "Free Play" mode, setting the
     *                              active tool to nothing and resetting the animation window.
     */
    void receiveResetFreeSim();

    /**
     * @brief endFreePlay : resets the backing logic of "Free Play" mode, and sets the active tactic
     *                      back to the first tactic. Essentially it changes "Free Play" mode back to
     *                      normal mode.
     */
    void endFreePlay();

signals:
    /**
     * @brief toggleTrajectoryTool : Tells the U.I. that the trajectory tool is the active tool.
     */
    void toggleTrajectoryTool();

    /**
     * @brief togglePlaceEnemyTool : Tells the U.I. that the place enemy tool is the active tool.
     */
    void togglePlaceEnemyTool();

    /**
     * @brief togglePlaceAllyTool : Tells the U.I. that the place ally tool is the active tool.
     */
    void togglePlaceAllyTool();

    /**
     * @brief startFreePlayMode : Tells the U.I. to setup for "Free Play" mode.
     */
    void startFreePlayMode();

    /**
     * @brief sendTrajectoryPoint : Sends the selected trajectory point for a "Free Play" soldier to the U.I.
     * @param trajectoryPoint : The trajectory point the soldier needs to move to.
     */
    void sendTrajectoryPoint(QPoint trajectoryPoint);

    /**
     * @brief toggleToolStatus : Tells the U.I. whether to enable or disable all tools/buttons for "Free Play" mode.
     * @param isEnabled : whether or not to enable the tools/buttons of the "Free Play" mode.
     */
    void toggleToolStatus(bool isEnabled);

    /**
     * @brief endFreePlayMode : Tells the U.I. mode that "Free Play" mode is over and to setup for normal mode.
     */
    void endFreePlayMode();

    /**
     * @brief showCompletedTacticStatus : Tells the U.I. which quiz for which tactic got completed.
     * @param tacticID : The ID of the tactic the quiz was completed for.
     */
    void showCompletedTacticStatus(int tacticID);

    /**
     * @brief makeASoldierLabel : sends the information to the UI to dynamically create a QLabel
     * @param pos : the position of the label
     * @param isEnemy : whether the label represents an allied(blue) or hostile(red) soldier
     * @param isFreePlayEnabled : whether free play mode is enabled or not.
     * @param soldierID : the ID of the soldier to create.
     */
    void makeASoldierLabel(QPoint pos, bool isEnemy, bool isFreePlayEnabled, int soldierID);

    /**
     * @brief setBackground : sets the background image for the tactic
     * @param backgroundImage : the QPixmap holding the image file
     */
    void setBackground(QPixmap backgroundImage);

    /**
     * @brief hidePlayButton : hides the play button
     */
    void hidePlayButton();

    /**
     * @brief incorrectChoice : Signals the main window when the user selects the incorrect choice.
     * @param questionChoice : Integer value representing the question choice.
     */
    void incorrectChoice(int questionChoice);

    /**
     * @brief passQuizUIInfo : Passes the relevant quiz information to the quiz window.
     * @param currentTacticID : Integer value representing the currently selected tactic.
     * @param questonIndex : Integer value representing the current question index.
     * @param question : QString value representing the current question.
     * @param choice1 : QString value representing the first choice.
     * @param choice2 : QString value representing the second choice.
     * @param choice3 : QString value representing the third choice.
     * @param choice4 : QString value representing the fourth choice.
     */
    void passQuizUIInfo(int currentTacticID, int questonIndex, QString question, QString choice1, QString choice2, QString choice3, QString choice4);

    /**
     * @brief enableNextButton : Signals the quiz window to either disable or enable the Next Question button.
     * @param nextActive : Boolean that determines what status the Next Question button should be.
     */
    void enableNextButton(bool nextActive);

    /**
     * @brief enablePreviousButton : Signals the quiz window to either disable or enable the Previous Question button.
     * @param previousActive : Boolean that determines what status the Next Question button should be.
     */
    void enablePreviousButton(bool previousActive);

    /**
     * @brief updateUIScore : Signals the quiz window to update the score label.
     * @param scoreResult : QString that represents the integer score.
     */
    void updateUIScore(QString scoreResult);

    /**
     * @brief reportCompletion : Signals the quiz window that the current quiz has been completed.
     */
    void reportCompletion();

    /**
     * @brief showQuizUIFirstQuestion : Sends information about the first question to the quiz window.
     * @param tacticID : Integer value representing the currently selected tactic.
     * @param questionIndex : Integer value representing the current question index.
     * @param question : QString value representing the current question.
     * @param choice1 : QString value representing the first choice.
     * @param choice2 : QString value representing the second choice.
     * @param choice3 : QString value representing the third choice.
     * @param choice4 : QString value representing the fourth choice.
     */
    void showQuizUIFirstQuestion(int tacticID, int questionIndex, QString question, QString choice1, QString choice2, QString choice3, QString choice4, bool quizCompletion);

    /**
     * @brief updateContent : Tells the U.I. to update the content/textbox with the current tactic information.
     * @param content : The content that should display on the U.I.
     * @param category : The category of the content.
     * @param tacticID : The ID of the tactic to be shown.
     */
    void updateContent(QString content, QString category, int tacticID);

    /**
     * @brief enableFreePlay : Signals the main window to enable the free play function if the user completed all the quizzes.
     * @param completionStatus : Boolean that represents the completion status of all the quizzes.
     */
    void enableFreePlayButton(bool completionStatus);
};

#endif // MODEL_H
