#ifndef TEXTURE_H
#define TEXTURE_H

#include "const.h"

//texture wrapper class
class Ltexture
{
    public:
        //ham khoi tao
        Ltexture();
        //ham huy
        ~Ltexture();
        //tai anh tu duong dan
        bool loadFromFile(std::string path, SDL_Renderer* gRenderer);
//        //create image from font string
//        bool loadFromRenderedText(std::string textureText, SDL_Color textColor);
        //giai phong bo nho cua texture
        void free();
        //set color modulation
//        void setColor(Uint8 red, Uint8 green, Uint8 blue);
//        //set blending
//        void setBlendMode(SDL_BlendMode blending);
//        //set alpha modulation
//        void setAlpha(Uint8 alpha);
//        //hien thi texture o diem xac dinh
        void render(int x, int y, SDL_Renderer* gRenderer, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
        //lay kich thuoc hinh anh
        int getWidth();
        int getHeight();
    private:
        //the actual hardware texture
        SDL_Texture* mTexture;

        //kich thuoc anh
        int mWidth;
        int mHeight;
};

////character right
//Ltexture Rcharacter;
////character left
//Ltexture Lcharacter;
////character
//Ltexture character;

#endif // TEXTURE_H

void close(SDL_Window* gWindow, SDL_Renderer* gRenderer);

