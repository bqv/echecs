#ifndef CHESSPLUGIN_H
#define CHESSPLUGIN_H

#include "../plugin.h"

#include "../chess.h"

using namespace std;

namespace {
    map<string,vector<string>> games;

    string play(const string& nick, vector<string>::const_iterator itBegin, vector<string>::const_iterator itEnd)
    {
        size_t size = itEnd - itBegin;
        if(size < 1)
        {
            games[nick].clear();
            return "Game cleared";
        }
        else if(size > 1)
        {
            return "One move at a time.";
        }
        else
        {
            string cmd = *itBegin;
            string history = "";
            for ( vector<string>::const_iterator it = games[nick].begin(); it != games[nick].end(); it++)
            {
                history += *it + " ";
            }
            if(cmd == "newgame")
            {
                games[nick].clear();
                return "Game cleared";
            }
            else if(cmd == "history")
            {
                return history;
            }
            else if(cmd == "undo")
            {
                games[nick].pop_back();
                return "Done";
            }
            else
            {
                history += cmd + " ";
                string move = eval_chess(history);
                history += move + " ";
                cout << nick << "'s game: " << history << endl;
                games[nick].push_back(cmd);
                games[nick].push_back(move);
                return move;
            }
        }
    }
}

class chessPlugin:public plugin
{
	private:
	public:
		//All lines starting with "!" get sent to this command, you can match and act on these.
		//ircNet is defined so you can use ircNet.sendMsg(channel, reply); to reply
		//If you do not match any commands you should return 0;
		//If you match a command but want other plugins to also be allowed to match commands you should return 1;
		//If you match a command and don't want other plugins to be allowed to match commands you should return 2;
		int handleCommand(const string& nick, const string& channel, const vector<string>& words)
		{
			string reply = "";
			if(nick != "")
			{
				reply += nick + ": ";
			}
			if(words.at(0) == "chess")
			{
                reply += play(nick, words.begin()+1, words.end());
                ircNet.sendMsg(channel, reply);
                return 1;
			}
			return 0;
		}
		//All lines not starting with a ! get passed on to this command, you do not have to overwrite it
		//If you wish to use it then use the same return values as in the handleCommand() function
		int handleMessage(const string& nick, const string& channel, const vector<string>& words)
		{
			string reply = "";
			if(nick != "")
			{
				reply += nick + ": ";
			}
			if((words.at(0) == ircNet.getNick() + ":") || (words.at(0) == ircNet.getNick() + ","))
			{
                reply += play(nick, words.begin()+1, words.end());
                ircNet.sendMsg(channel, reply);
                return 1;
			}
			return 0;
		}

		//This function is run every time the program ticks.
		//You can use this to manipulate stored variables etc.
		//Should return 1 if it did anything, otherwise 0.
		int doTick()
		{
			return 0;
		}

		//This function is run at the program startup.
		//the args argument is the command line that is used to start the program.
		//This can be used to set things from the command line at startup.
		//Should return 0.
		int startupOptions(const vector<string>& args)
		{
            init_chess();
			for(int i=0; i<args.size(); ++i)
			{
				if(args.at(i) == "--foo" && args.size() > i+1)
				{
					//do stuff with args.at(i) and args.at(i+1)
					++i;
				}
			}
			return 0;
		}
};

#endif
