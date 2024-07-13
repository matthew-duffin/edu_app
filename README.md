**************************************************************************************************************************
Authors:     Jacob Ormsby, Jonathan Bancroft, Aric Woodliff, Jiedi Mo, Matthew Duffin, Adrian Regalado.
Date:       9-Dec-2023,
Course:     CS 3505, University of Utah, School of Computing,
GitHub ID:  21jormsby, JonBancroft, Aric-W, shotpb, matthew-duffin, AdrianRegalado1123
Repo:       https://github.com/University-of-Utah-CS3505/a9-edu-app-AdrianRegalado1123,
Project:    TacticsGame,
Copyright:  CS 3505, Jacob Ormsby, Jonathan Bancroft, Aric Woodliff, Jiedi Mo, Matthew Duffin, Adrian Regalado - This work may not be copied for use in Academic Coursework.
**************************************************************************************************************************

# Overview of the Tactics Game functionality

This project implements a educational game to learn about a handful of military tactics. Within this program users are able to select any of the six available tactics and go through its level. 
Users start off in the "Description" category where a description of the tactic is available, they can then choose the "History" and "Fun Facts" categories where a few historical examples of the tactic 
and some interesting details are presented. Users must visit all three categories at least once before they can attempt the quiz. There is also an animation available above these categories that shows a 
short example of the tactic in action which starts with the "play" button in the top right. If the user re-selects the "play" button after the animation is over then it restarts. The user can then attempt
the quiz for the level. Each tactic quiz has four multiple choice questions. If the user gets the question wrong then the choice they selected is hightlighted in red, but they can then select another
choice until they get the right one. When the user selects a correct answer, their score in the top right is increased. Once all the correct answers have been chosen (score of 4/4), there is an indicator
that the quiz is complete, at that point the user can close the quiz. After quiz completion it can be seen with the tactics button on the left side that the tactic they completed the quiz for has its name
highlighted in bold, signifying that its level is complete. 

After all six tactic levels have been completed, there is a "Free Play" mode unlocked beneath the tactics levels. Within this "Free Play" mode, users can set up their own tactic simulations.
The "Place Ally" and "Place Enemy" tools highlight in dark gray after they are chosen, indicating that they are the active tools. When the tool is active, the user can select a location in the
animation window and a soldier representing an ally or an enemy will show up in that location. All soldiers are clickable, when a soldier appears on the screen, the user can select that soldier
by clicking on it and it will display its ID in the bottom window. The user can then enable the "Select Trajectory Point" tool and click in the animation window to set a trajectory point for where
the soldier will go in the next animation step. Each soldier in the animation window can be given a trajectory point for each animation step. Each animation step is three seconds long, if the user
gives the soldier a trajectory point that is farther than what the soldier can reach in one animation step, the soldier will go as far as it can towards that direction, but then in the next animation
step they will stop. The user must give the trajectory point again for the new animation step if they wish to keep going in that direction. To start the animation step, the user will press the
"Move Soldiers" button and if they set trajectory points for the soldiers, they will see them move. The "Reset Simulation" button clears all soldiers and brings "Free Play" mode to its initial state.
Users can select the "End Freeplay" button if they wish to go back to the normal game mode with the tactic levels re-enabled, but they can go back to free play anytime they wish by clicking the
"Free Play" button again under the tactic levels.

 # Partnership

All work was completed via pair programming with our group of six splitting into three subgroups of two. Each subgroup coding functionality for the project, tested, debugged,
commented, provided new ideas, and polished our code.

# Branching

Subgroup 1 (Aric & Jiedi) and Subgroup 2 (Adrian & Matthew) had associated branches, while Subgroup 3 (Jacob & Jon) worked on the master branch since Subgroup 3 primarily worked on the central U.I.
After all the Subgroup's work was done, each was merged into master.

# Testing

All testing was done manually by targeting specific functionality aspects of the Tactics Game, such as unlocking free play mode while an animation is playing, ensuring that each quiz unlocks
properly after going through each tactic category, making sure the animations play properly, ensuring that soldiers move in the right direction in the "Free Play" mode, and that themes are shown properly.

# References (For the Tactic Research)

1. https://en.wikipedia.org/wiki/Ambush
2. https://www.moore.army.mil/Infantry/DoctrineSupplement/ATP3-21.8/chapter_08/CombatPatrols/ActionsontheObjective_Ambush/index.html#:~:text=An%20ambush%20is%20a%20surprise,or%20to%20harass%20enemy%20forces
3. https://en.wikipedia.org/wiki/Envelopment
4. https://www.nationalww2museum.org/war/articles/battle-midway
5. https://en.wikipedia.org/wiki/Defeat_in_detail
6. https://en.wikipedia.org/wiki/Military_of_the_Mongol_Empire
7. https://en.wikipedia.org/wiki/Withdrawal_(military)
8. https://en.wikipedia.org/wiki/Feigned_retreat
9. https://www.cia.gov/static/5ed7bb5484ea83ad2abea1c690831e6c/lever-of-power.pdf 
10. https://en.wikipedia.org/wiki/Infiltration_tactics
11. https://en.wikipedia.org/wiki/Defence_in_depth 
12. https://www.greece-private.com/salamis-battle
13. https://www.encyclopedia.com/history/encyclopedias-almanacs-transcripts-and-maps/defeat-detail
