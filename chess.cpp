#include "chess.h"

using namespace std;

std::stringstream movebuffer;

void init_chess() {
  cout << engine_info() << endl;

  UCI::init(Options);
  Bitboards::init();
  Position::init();
  Bitbases::init();
  Search::init();
  Eval::init();
  Pawns::init();
  Threads.init();
  Tablebases::init(Options["SyzygyPath"]);
  TT.resize(Options["Hash"]);
  TT.clear();
}

string eval_chess(string hist) {
  Position pos(UCIext::StartFEN, false, Threads.main()); // The root position
  string cmd = "startpos moves " + hist;

  movebuffer.str(std::string()); // clear
  istringstream is(cmd);
  UCIext::position(pos, is); // startpos moves e2e4 e7e5
  UCIext::go(pos, is); // blank | depth 20 | movetime 5000
  Threads.main()->join();
  return movebuffer.str();
}

void finish_chess() {
  Threads.exit();
}
