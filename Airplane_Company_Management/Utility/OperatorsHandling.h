//
// Created by alon on 25/11/18.
//

#ifndef AP1_OPERATORSHANDLING_H
#define AP1_OPERATORSHANDLING_H

#include <string>
#include <cstring>
#include "../interface.h"

using namespace std;

enum OperatorsHandlerResult{ LT, GT, EQUALS };

OperatorsHandlerResult operatorsHandler(Date&, Date&);

#endif //AP1_OPERATORSHANDLING_H
