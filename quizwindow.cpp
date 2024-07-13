/*
   Name:       Jacob Ormsby, Jonathan Bancroft, Aric Woodliff, Jiedi Mo, Matthew Duffin, Adrian Regalado

   Date:       12/08/2023

   uID:        u1275849, u1300968, u0586534, u1352501, u1227629, u1348610

   GitHub:     21jormsby, JonBancroft, Aric-W, shotpb, matthew-duffin, AdrianRegalado1123

   Assignment: A9: An-Educational-App

   Description: Body implementation of the quiz window functionality for the tactics program.
                Handles the connection logic between the model and the main window.
                Each tactic has a unique corresponding quiz.
*/

#include "quizwindow.h"
#include "ui_quizwindow.h"

QuizWindow::QuizWindow(Model& model, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QuizWindow),
    tacticID(0)
{
    ui->setupUi(this);
    // Choice button connections
    connect(ui->choice1,
            &QRadioButton::clicked,
            &model,
            &Model::choice1);
    connect(ui->choice2,
            &QRadioButton::clicked,
            &model,
            &Model::choice2);
    connect(ui->choice3,
            &QRadioButton::clicked,
            &model,
            &Model::choice3);
    connect(ui->choice4,
            &QRadioButton::clicked,
            &model,
            &Model::choice4);
    connect(&model,
            &Model::incorrectChoice,
            this,
            &QuizWindow::wrongAnswer);

    // Updating UI elements
    connect(&model,
            &Model::updateUIScore,
            ui->scoreLabel,
            &QLabel::setText);
    connect(ui->nextQuestion,
            &QPushButton::clicked,
            &model,
            &Model::changeNextQuestion);
    connect(ui->previousQuestion,
            &QPushButton::clicked,
            &model,
            &Model::changePreviousQuestion);
    connect(&model,
            &Model::passQuizUIInfo,
            this,
            &QuizWindow::changeQuizUI);
    connect(&model,
            &Model::enableNextButton,
            ui->nextQuestion,
            &QPushButton::setEnabled);
    connect(&model,
            &Model::enablePreviousButton,
            ui->previousQuestion,
            &QPushButton::setEnabled);
    connect(&model,
            &Model::reportCompletion,
            this,
            &QuizWindow::quizCompletion);
    connect(&model,
            &Model::showQuizUIFirstQuestion,
            this,
            &QuizWindow::resetQuizUILabels);

    // Quiz window color themes
    backgroundStyleSheets.append("* {background-color: rgb(150, 172, 135);}");
    backgroundStyleSheets.append("* {background-color: rgb(120, 190, 120);}");
    backgroundStyleSheets.append("* {background-color: rgb(209, 193, 79);}");
    backgroundStyleSheets.append("* {background-color: rgb(230, 230, 230);}");
    backgroundStyleSheets.append("* {background-color: rgb(120, 105, 105);}");
    backgroundStyleSheets.append("* {background-color: rgb(240, 205, 105);}");

    buttonStyleSheets.append("* {background-color: rgb(224, 255, 210);}");
    buttonStyleSheets.append("* {background-color: rgb(224, 255, 210);}");
    buttonStyleSheets.append("* {background-color: rgb(240, 227, 129);}");
    buttonStyleSheets.append("* {background-color: rgb(125, 195, 240);}");
    buttonStyleSheets.append("* {background-color: rgb(169, 69, 45);}");
    buttonStyleSheets.append("* {background-color: rgb(160, 160, 160);}");
}

QuizWindow::~QuizWindow()
{
    delete ui;
}

void QuizWindow::wrongAnswer(int choice)
{
    if(1 == choice )
        ui->choice1->setStyleSheet("QRadioButton {color : red;}");
    else if(2 == choice)
        ui->choice2->setStyleSheet("QRadioButton {color : red;}");
    else if(3 == choice)
        ui->choice3->setStyleSheet("QRadioButton {color : red;}");
    else if(4 == choice)
        ui->choice4->setStyleSheet("QRadioButton {color : red;}");
}

void QuizWindow::changeQuizUI(int currentTacticID, int questionIndex, QString question, QString choice1, QString choice2, QString choice3, QString choice4)
{
    tacticID = currentTacticID;
    ui->questionLabel->setText("Question " + QString::number(questionIndex + 1));
    ui->questionContents->setText(question);
    ui->choice1->setText(choice1);
    ui->choice2->setText(choice2);
    ui->choice3->setText(choice3);
    ui->choice4->setText(choice4);
    ui->choice1->setStyleSheet("QRadioButton {color : black;}");
    ui->choice2->setStyleSheet("QRadioButton {color : black;}");
    ui->choice3->setStyleSheet("QRadioButton {color : black;}");
    ui->choice4->setStyleSheet("QRadioButton {color : black;}");

    ui->choice1->setAutoExclusive(false);
    ui->choice1->setChecked(false);
    ui->choice1->setAutoExclusive(true);

    ui->choice2->setAutoExclusive(false);
    ui->choice2->setChecked(false);
    ui->choice2->setAutoExclusive(true);

    ui->choice3->setAutoExclusive(false);
    ui->choice3->setChecked(false);
    ui->choice3->setAutoExclusive(true);

    ui->choice4->setAutoExclusive(false);
    ui->choice4->setChecked(false);
    ui->choice4->setAutoExclusive(true);

    ui->choice1->setEnabled(true);
    ui->choice2->setEnabled(true);
    ui->choice3->setEnabled(true);
    ui->choice4->setEnabled(true);
}

void QuizWindow::quizCompletion()
{
    ui->completionLabel->setText("Quiz Completed!");
}

void QuizWindow::resetQuizUILabels(int currentTacticID, int questionIndex, QString question, QString choice1, QString choice2, QString choice3, QString choice4, bool quizCompletion)
{
    ui->previousQuestion->setEnabled(false);
    ui->nextQuestion->setEnabled(true);
    ui->scoreLabel->setText("Score: 0/4");

    if(quizCompletion)
        ui->completionLabel->setText("Quiz Completed!");
    else
        ui->completionLabel->setText("");

    changeQuizUI(currentTacticID, questionIndex, question, choice1, choice2, choice3, choice4);

    QuizWindow::setStyleSheet(backgroundStyleSheets[tacticID]);
    ui->nextQuestion->setStyleSheet(buttonStyleSheets[tacticID]);
    ui->previousQuestion->setStyleSheet(buttonStyleSheets[tacticID]);
}
