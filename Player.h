#include <string>

using namespace std;

class Player
{
private:
    char colour;
	string name;
	int score ;

public :
    Player(){}
    Player(string _name, char _colour) {
        name = _name;
        colour = _colour;
        score = 0;
    }

	void setname(string x)
	{
		name=x;
	}
    void setcolour(char c)
	{
		colour =c;
	}
	void setscore(int s)
	{
		score=s;
	}
	string getname()
	{
		return name;
	}
    char getcolour()
	{
		return colour;
	}
	int getscore()
	{
		return score;
	}
};
