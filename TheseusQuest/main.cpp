/*******************************************************************************************
*
*   raylib [core] example - Basic window
*
*   Welcome to raylib!
*
*   To test examples, just press F6 and execute raylib_compile_execute script
*   Note that compiled executable is placed in the same folder as .c file
*
*   You can find all basic examples on C:\raylib\raylib\examples folder or
*   raylib official webpage: www.raylib.com
*
*   Enjoy using raylib. :)
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2014 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "Headers.h"
#include <iostream>

#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS
using namespace AIForGames;

int main(int argc, char* argv[])
{
	// Initialization
	//--------------------------------------------------------------------------------------
	int screenWidth = 1600;
	int screenHeight = 900;
	InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

	float cur_time = (float)GetTime();
	float deltaTime;
	srand(time(NULL));

#pragma region NavMesh

	NavMesh navMesh(screenWidth, screenHeight);
	navMesh.MakeMaze();
	navMesh.Build();

#pragma endregion

#pragma region Original Positions and Speeds
	glm::vec2 playerStart = { 1550,850 };
	glm::vec2 minotaurStart = { 650, 500 };
	glm::vec2 minotaurPace = { 950, 500 };
	glm::vec2 child1Start = { 650, 600 };
	glm::vec2 child2Start = { 800, 600 };
	glm::vec2 child3Start = { 950, 600 };
	float playerSpeed = 300;
	float childSpeed = 100;
	float minotaurSpeed = 200;
#pragma endregion

#pragma region Forward Declaration

	// Forward declaration of NPC agents
	GoToPointBehaviour* lair1 = new GoToPointBehaviour(minotaurStart);
	Agent Minotaur(&navMesh, lair1, 0, minotaurSpeed, minotaurStart, "Minotaur");
	Agent child1(&navMesh, lair1, 2, childSpeed, child1Start, "child1");
	Agent child2(&navMesh, lair1, 4, childSpeed, child2Start, "child2");
	Agent child3(&navMesh, lair1, 8, childSpeed, child3Start, "child3");
	// Vector for handing all children to behaviours
	std::vector<Agent*> children;
	children.push_back(&child1);
	children.push_back(&child2);
	children.push_back(&child3);

#pragma endregion

#pragma region Player

	WASDBehaviour* input = new WASDBehaviour();
	State* controls = new State(input);
	DeathBehaviour* death = new DeathBehaviour();
	State* reset = new State(death);
	CaughtByMinotaurCondition* playerCaught = new CaughtByMinotaurCondition(5, &Minotaur, children);
	TimeCondition* dead = new TimeCondition(0.00001);
	controls->AddTransition(playerCaught, reset);
	reset->AddTransition(dead, controls);
	FiniteStateMachine* playerFSM = new FiniteStateMachine(controls);
	playerFSM->AddState(reset);
	Agent player(&navMesh, playerFSM, 0, playerSpeed, playerStart, "player");
	player.SetSize(12);
	player.SetColor(RED);

#pragma endregion

#pragma region Minotaur State Machine

	// Pacing State
	GoToPointBehaviour* lair2 = new GoToPointBehaviour(minotaurPace);
	PaceBehaviour* pace = new PaceBehaviour(lair1, lair2);
	State* pacing = new State(pace);

	// Patroling State of the Minotaur
	WanderBehaviour* patrol1 = new WanderBehaviour();
	GoToPointBehaviour* patrol2 = new GoToPointBehaviour(minotaurStart);
	PaceBehaviour* patrol = new PaceBehaviour(patrol1, patrol2);
	State* patrolling = new State(patrol);

	// Pursuing State of the Minotaur
	FollowBehaviour* pursue = new FollowBehaviour(&player, children, 1);

	State* pursuing = new State(pursue);

	// Stunned State of the Minotaur
	DazeBehaviour* dazed = new DazeBehaviour();
	State* stunned = new State(dazed);

	// Returning State of the Minotaur
	GoToPointBehaviour* lair3 = new GoToPointBehaviour(minotaurStart);
	State* returning = new State(lair3);

	// Conditions to leave pacing
	TimeCondition* patrolTime = new TimeCondition(5);
	DistanceCondition* seePlayer = new DistanceCondition(500, &player, true);
	pacing->AddTransition(patrolTime, patrolling);
	pacing->AddTransition(seePlayer, pursuing);

	// Conditions to leave patrolling
	DistanceCondition* seeTarget = new DistanceCondition(500, &player, children, true);
	ReturnedCondition* returnedChild = new ReturnedCondition(children, true);
	patrolling->AddTransition(seeTarget, pursuing);
	patrolling->AddTransition(returnedChild, pacing);

	//Conditions to leave pursuing
	NoLineOfSightCondition* noTargets = new NoLineOfSightCondition(&player, children);
	DistanceCondition* catchTarget = new DistanceCondition(5, &player, children, true);
	pursuing->AddTransition(noTargets, patrolling);
	pursuing->AddTransition(catchTarget, returning);

	//Conditions to leave stunned
	TimeCondition* stunTime = new TimeCondition(3);
	stunned->AddTransition(stunTime, patrolling);

	//Conditions to leave returning
	ReturnedCondition* returnedNoChild = new ReturnedCondition(children, false);
	FreeChildCondition* stoppedByPlayer = new FreeChildCondition(5, &player, children);
	returning->AddTransition(returnedChild, pacing);
	returning->AddTransition(returnedNoChild, patrolling);
	returning->AddTransition(stoppedByPlayer, stunned);

	// Bringing all the states together into a FSM
	FiniteStateMachine* fsm = new FiniteStateMachine(pacing);
	fsm->AddState(patrolling);
	fsm->AddState(pursuing);
	fsm->AddState(returning);
	fsm->AddState(stunned);
#pragma endregion

#pragma region Children Decision Tree

	InLairCondition* childInLair = new InLairCondition();
	SeeMinotaurCondition* seeMinotaur = new SeeMinotaurCondition();
	BraveryCondition* bravery = new BraveryCondition();
	DistanceCondition* childCaught = new DistanceCondition(5, &Minotaur, false);
	LeaveCondition* exitSeen = new LeaveCondition();

	BraveDecision* raiseCourage = new BraveDecision();
	SearchExitDecision* searchExit = new SearchExitDecision();
	ScaredDecision* scared = new ScaredDecision();
	LeaveDecision* leave = new LeaveDecision();
	CaughtDecision* returnLair = new CaughtDecision();

	ABDecision* braveEnough = new ABDecision(bravery, searchExit, raiseCourage);
	ABDecision* captorGone = new ABDecision(seeMinotaur, scared, braveEnough);
	ABDecision* seeExit = new ABDecision(exitSeen, leave, searchExit);
	ABDecision* isCaught = new ABDecision(childCaught, seeExit, returnLair);
	ABDecision* inLair1 = new ABDecision(childInLair, captorGone, isCaught);

	DecisionBehaviour* decisionTree = new DecisionBehaviour(inLair1);

#pragma endregion

#pragma region Children 

	child1.SetBehaviour(decisionTree);
	child1.SetOriginalPosition(child1Start);
	child1.SetPosition(child1Start);
	child1.SetTarget(&Minotaur);
	child1.SetColor(BLUE);
	child1.SetSize(10);

	child2.SetBehaviour(decisionTree);
	child2.SetOriginalPosition(child2Start);
	child2.SetPosition(child2Start);
	child2.SetTarget(&Minotaur);
	child2.SetColor(BLUE);
	child2.SetSize(10);

	child3.SetBehaviour(decisionTree);
	child3.SetOriginalPosition(child3Start);
	child3.SetPosition(child3Start);
	child3.SetTarget(&Minotaur);
	child3.SetColor(BLUE);
	child3.SetSize(10);

#pragma endregion

#pragma region Minotaur

	Minotaur.SetBehaviour(fsm);
	Minotaur.SetTarget(&player);
	Minotaur.SetSize(15);
	Minotaur.SetPosition(minotaurStart);
	Minotaur.SetColor(DARKBROWN);

#pragma endregion


	bool playerDebug = true;
	bool minotaurDebug = true;
	SetTargetFPS(60);
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		float fTime = (float)GetTime();
		deltaTime = fTime - cur_time;
		cur_time = fTime;

		BeginDrawing();
		ClearBackground(BLACK);
		// Set to true to show debug information.
		navMesh.Draw(true);

		// Debug of AStar path and Smoothed Path

		if (playerDebug)
		{
			DrawPath(player.GetPath(), player.GetColor());
			std::vector<glm::vec2> jaggedPath = player.GetJaggedPath();
			DrawPath(jaggedPath, GREEN);
		}
		if (minotaurDebug)
		{
			DrawPath(Minotaur.GetPath(), ORANGE);
			std::vector<glm::vec2> jaggedPath = Minotaur.GetJaggedPath();
			DrawPath(jaggedPath, DARKBLUE);
		}

		player.Update(deltaTime);
		Minotaur.Update(deltaTime);
		child1.Update(deltaTime);
		child2.Update(deltaTime);
		child3.Update(deltaTime);

		player.Draw();
		Minotaur.Draw();
		child1.Draw();
		child2.Draw();
		child3.Draw();

		EndDrawing();
		if (player.GetLives() <= 0)
		{
			CloseWindow();
		}
	}

	CloseWindow();        // Close window and OpenGL context

	return 0;
}