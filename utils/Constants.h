#pragma once
#include "raylib.h"

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 800;

const int PLAYER_SPEED = 10;
const Color PLAYER_COLOR = BLUE;

const int CPU_SPEED = 1;
const Color CPU_COLOR = RED;

const Color MIDLINE_COLOR = GRAY;

const Vector2 PADDLE_SIZE = {25, 120};

const Vector2 BALL_INITIAL_POSITION = {SCREEN_WIDTH/2, SCREEN_HEIGHT/2};
const int BALL_RADIUS = 20;
const Vector2 BALL_SPEED = {15, 15};

// scoreboard text
const char scores[8] {'0', '1', '2', '3', '4', '5', '6', '\0'};
const int POINTS_TO_WIN = 3;

struct Line 
{
    Vector2 start;
    Vector2 end;
    Color color;
};