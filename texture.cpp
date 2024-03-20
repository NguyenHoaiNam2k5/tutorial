#include "texture.h"
#include "const.h"

Ltexture :: Ltexture()
{
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
}


Ltexture::~Ltexture()
{
    free();
}

bool Ltexture::loadFromFile(std::string path, SDL_Renderer* gRenderer)
{
    //xoa texture truoc do
    free();
    //final texture
    SDL_Texture* newTexture = NULL;

    //tai anh tu duong dan
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if(loadedSurface == NULL)
    {
        std::cout << "ko the tai hinh anh" << IMG_GetError() << std::endl;
    }
    else{
//        //color key image
//        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface -> format, 0, 0xFF, 0xFF));

        //tao texture tu surface pixels
        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
        if(newTexture == NULL)
        {
            std::cout << "ko the tao texture" <<SDL_GetError() << std::endl;
        }
        else
        {
            //lấy kích thước hình anh
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }
        //xoa loaded surface cux
        SDL_FreeSurface(loadedSurface);
    }
    //return success
    mTexture = newTexture;
    return mTexture != NULL;
}

//bool Ltexture::loadFromRenderedText(std::string textureText, SDL_Color textColor)
//{
//    //get rid of preexisting texture
//    free();
//
//    //render text suface
//    SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);
//    if(textSurface == NULL)
//    {
//        std::cout << "ko tai duoc text surface" << TTF_GetError();
//    }
//    else
//    {
//        //create texture from surface pixels
//        mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
//        if(mTexture == NULL)
//        {
//            std::cout << "ko the tao texture" << SDL_GetError();
//        }
//        else
//        {
//            //get image dimension
//            mWidth = textSurface->w;
//            mHeight = textSurface->h;
//        }
//
//        //get rid of old surface
//        SDL_FreeSurface(textSurface);
//    }
//
//    //return success
//    return mTexture != NULL;
//}

void Ltexture::free()
{
    //free texture if it exists
    if(mTexture != NULL)
    {
        SDL_DestroyTexture(mTexture);
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}

void Ltexture::render(int x, int y, SDL_Renderer* gRenderer, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
    //set rendering space and render to screen
    SDL_Rect renderQuad= {x, y, mWidth, mHeight};

    if(clip != NULL)
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }
    //render to screen
    SDL_RenderCopyEx(gRenderer, mTexture, clip, &renderQuad, angle, center, flip);
}

int Ltexture::getWidth()
{
    return mWidth;
}
int Ltexture::getHeight()
{
    return mHeight;
}






