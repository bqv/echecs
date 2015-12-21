#ifndef CHESS_H
#define CHESS_H

#include <iostream>
#include <sstream>
#include <string>
#include <map>

#include "engine/bitboard.h"
#include "engine/evaluate.h"
#include "engine/movegen.h"
#include "engine/position.h"
#include "engine/search.h"
#include "engine/thread.h"
#include "engine/tt.h"
#include "engine/uci.h"
#include "engine/syzygy/tbprobe.h"

void init_chess(void);
std::string eval_chess(std::string hist);
void finish_chess(void);

#endif
