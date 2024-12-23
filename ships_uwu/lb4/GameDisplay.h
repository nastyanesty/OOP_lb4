#ifndef GAMEDISPLAY_H
#define GAMEDISPLAY_H

#include "Game.h"
#include "Observer.h"
#include "FieldRendering.h"


// Шаблонныый класс
template <typename FieldRendering>
// Класс чекер изменений 
class GameDisplay: public Observer{
private:
    Game& game;
    FieldRendering field_render;
public:
    GameDisplay(Game& new_game, FieldRendering& new_fieldrender)
        : game(new_game), field_render(new_fieldrender) {
            game.add_observer(this);
        }
    void update() override{
        field_render.draw_fields(game.GetUser(), game.GetBot());
    }
};

#endif // GAMEDISPLAY_H
