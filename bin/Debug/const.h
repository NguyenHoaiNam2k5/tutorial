#ifndef CONST_H
#define CONST_H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <string>
#include <fstream>
#include <cmath>
#include <vector>
#include <utility>
#include <string>
#include <sstream>


const int SCREEN_WIDTH = 840;
const int SCREEN_HEIGHT = 600;

const int NUM_CHAR = 3;

const int Walking_frames = 3;

const int explosion_frames = 3;

const int LEVEL_WIDTH = 1920;
const int LEVEL_HEIGHT = 1440;

//kich thuoc nhan vat
const int CHARACTER_WIDTH = 16;
const int CHARACTER_HEIGHT = 26;

//Tile constants
const int TILE_WIDTH = 32;
const int TILE_HEIGHT = 32;
const int TOTAL_TILES = 2700;
const int TOTAL_TILE_SPRITES = 2;

//level up
const int LEVEL_UP = 40;

//survive time
const int survive_time = 1200000;

const int TILE_background = 00;
const int TILE_wall = 01;
//const int TILE_tree1 = 02;
//const int TILE_tree2 = 03;

enum collision
{
    right,
    left,
    top,
    bottom
};


const int RWEAPON = 0;
const int LWEAPON = 1;
#endif // CONST_H
