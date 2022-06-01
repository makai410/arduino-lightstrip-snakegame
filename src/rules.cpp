#include "rules.h"
#include <Arduino.h>
bool Pix::operator==(const Pix &other) const
{
    return x == other.x && y == other.y;
}

Pix::Pix()
{
}
enum Direction
{
    UP = 0,
    LEFT = 1,
    DOWN = 2,
    RIGHT = 3
};

bool SnakeGame::is_food_eaten()
{
    return snake[0] == food;
}

void SnakeGame::move_snake()
{
    for (int i = snake_size - 1; i > 0; i--)
        snake[i] = snake[i - 1];
}

void SnakeGame::move_up()
{
    snake[0].y--;
    cur_move_status = UP;
}

void SnakeGame::move_down()
{
    snake[0].y++;
    cur_move_status = DOWN;
}

void SnakeGame::move_left()
{
    snake[0].x--;
    cur_move_status = LEFT;
}

void SnakeGame::move_right()
{
    snake[0].x++;
    cur_move_status = RIGHT;
}

void SnakeGame::move_snake(int input)
{
    switch (input)
    {
    case UP:
        if (cur_move_status != DOWN) {
            move_up();
            move_snake();
            Serial.print("current move status:");
            Serial.println(cur_move_status);
        }
        break;
    case DOWN:
        if (cur_move_status != UP) {
            move_down();
            move_snake();
            Serial.print("current move status:");
            Serial.println(cur_move_status);
        }
        break;
    case LEFT:
        if (cur_move_status != RIGHT) {
            move_left();
            move_snake();
            Serial.print("current move status:");
            Serial.println(cur_move_status);
        }
        break;
    case RIGHT:
        if (cur_move_status != LEFT) {
            move_right();
            move_snake();
            Serial.print("current move status:");
            Serial.println(cur_move_status);
        }
        break;
    }
}

void SnakeGame::draw_snake()
{
    for(int i = 0; i < snake_size; i++)
    {
        map[snake[i].x][snake[i].y].status = true;
    }
}

void SnakeGame::generate_food()
{
    food.x = 5;
    food.y = 5;
}

void SnakeGame::init_map()
{
    for (int i = 0; i <= X; i++)
    {
        for (int j = 0; j <= Y; j++)
        {
            map[i][j].x = i;
            map[i][j].y = j;
        }
    }
    clear_map();
}

void SnakeGame::clear_map()
{
    for (int i = 0; i <= X; i++)
    {
        for (int j = 0; j <= Y; j++)
        {
            map[i][j].status = false;
        }
    }
}

void SnakeGame::snake_push_back(Pix pix)
{
    snake[snake_size] = pix;
    snake_size++;
}

void SnakeGame::init_snake()
{
    for (int i = 0; i <= 3; i++)
    {
        snake_push_back(Pix(3, i));
    }
}

void SnakeGame::init()
{
    init_map();
    init_snake();
    // generate_food();
}

int SnakeGame::pix_to_digital(int x, int y)
{
    // Serial.println(pix.x + ":" + pix.y);
    if (y % 2 == 0)
        return 8 * y + x;
    else if (y % 2 != 0)
        return 8 * y - x + 7;
    else if (y == 0)
        return 8 * y + x;
}

void SnakeGame::draw_map(CRGB leds[])
{
    for (int i = 0; i <= X; i++)
    {
        for (int j = 0; j <= Y; j++)
        {
            if (map[i][j].status)
            {
                int index = pix_to_digital(i, j);
                leds[index] = CRGB::Red;
                FastLED.show();
            } else {
                int index = pix_to_digital(i, j);
                leds[index] = CRGB::Black;
                FastLED.show();
            }
            // else if(i == food.x && j == food.y)
            // {
            //     int index = pix_to_digital(i, j);
            //     leds[index] = CRGB::Green;
            //     FastLED.show();
            // }
        }
    }
}

void SnakeGame::loop(CRGB leds[])
{

    // if (is_food_eaten())
    // {
    //     // move_snake();
    //     snake_push_back(Pix(snake_tail->x, snake_tail->y));
    //     generate_food();
    // }
    move_snake(get_direction());
    clear_map();
    draw_snake();
    draw_map(leds);
    clear_map();
    // draw_food();
}

SnakeGame::SnakeGame()
{
}
