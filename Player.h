#include <QString>

class Player
{
private:
    char colour;
    QString name;
    int score;

public :
    Player(){}
    Player(QString _name, char _colour) {
        name = _name;
        colour = _colour;
        score = 0;
    }

    void setname(QString x)
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
    QString getname()
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
