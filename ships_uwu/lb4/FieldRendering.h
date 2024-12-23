#ifndef FIELDRENDERIND_H
#define FIELDRENDERIND_H

#include "User.h"
#include "Bot.h"

#include <iostream>

// Рисуем поля
class FieldRendering{
public:
    void draw_fields(User& user, Bot& bot);
};

#endif //FIELDRENDERIND_H
