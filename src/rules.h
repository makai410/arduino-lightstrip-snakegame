#pragma once
#include "input.h"
#include<FastLED.h>
#define X 7
#define Y 7

class Pix
{
public:
    int x, y;
    bool status = false;
    Pix();
    
    Pix(int _x, int _y)
    {
        x = _x;
        y = _y;
    }
    bool operator==(const Pix &other) const;
};

class SnakeGame
{
private:

    int cur_move_status = 1;

    bool is_food_eaten();

    void init_map();

    void move_snake();

    void move_up();

    void move_down();

    void move_left();

    void move_right();

    void move_snake(int input);

    void draw_snake();

    void draw_food();

    void generate_food();

    void init_snake();

    void draw_map(CRGB leds[]);

    void clear_map();

    void snake_push_back(Pix pix);
public:
    int snake_size = 0;

    Pix snake[63];

    Pix food;
    Pix map[X][Y];

    void init();

    void loop(CRGB leds[]);

    int pix_to_digital(int x, int y);

    SnakeGame();
};