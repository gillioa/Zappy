#ifndef TEXTURE_MANAGER_HPP__
# define TEXTURE_MANAGER_HPP__

#include <SFML/Graphics.hpp>
#include <map>
#include <vector>

typedef enum e_texture {
		LOGIN_SCREEN = 0 ,
        PLAYER_SPRITE    ,
        BIG_PLAYER       ,
        BIG_CASE         ,
        EGG_SMALL        ,
        EGG_SMALL_CRACK  ,
        SUN_SMALL        ,
        BACKGROUND       ,
        ARROW_UP         ,
        ARROW_DOWN       ,
        ARROW_LEFT       ,
        ARROW_RIGHT      ,
        ARROW_UP_SMALL   ,
        ARROW_DOWN_SMALL ,
	 } e_texture;

class TextureManager
{
public:
    static TextureManager& Instance();
    const sf::Texture & getTexture(const e_texture);
    const sf::Font & getFont();
private:
    TextureManager& operator= (const TextureManager&);
    TextureManager(const TextureManager&){}
    TextureManager();
    ~TextureManager();
    static TextureManager m_instance;
private:
	std::map<e_texture, sf::Texture> m_textures;
    sf::Font m_font;
};

const std::string ASSETS_PATH = "./assets/";
const std::map<std::string, e_texture> TEXTURES_PATH =
{
    { ASSETS_PATH + "login_screen.png"       , LOGIN_SCREEN     },
    { ASSETS_PATH + "sprite.png"             , PLAYER_SPRITE    },
    { ASSETS_PATH + "big_player.png"         , BIG_PLAYER       },
    { ASSETS_PATH + "big_case.png"           , BIG_CASE         },
    { ASSETS_PATH + "egg.png"                , EGG_SMALL        },
    { ASSETS_PATH + "egg_crack.png"          , EGG_SMALL_CRACK  },
    { ASSETS_PATH + "sun.png"                , SUN_SMALL        },
    { ASSETS_PATH + "background.png"         , BACKGROUND       },
    { ASSETS_PATH + "arrow_up.png"           , ARROW_UP         },
    { ASSETS_PATH + "arrow_down.png"         , ARROW_DOWN       },
    { ASSETS_PATH + "arrow_left.png"         , ARROW_LEFT       },
    { ASSETS_PATH + "arrow_right.png"        , ARROW_RIGHT      },
    { ASSETS_PATH + "arrow_up_small.png"     , ARROW_UP_SMALL   },
    { ASSETS_PATH + "arrow_down_small.png"   , ARROW_DOWN_SMALL }
};

#endif