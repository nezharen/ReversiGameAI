#pragma once

#define STATE_NOT_START 0
#define STATE_BLACK_GO 1
#define STATE_WHITE_GO 2
#define STATE_BLACK_WIN 3
#define STATE_WHITE_WIN 4
#define STATE_PEACE 5

#define MAP_NULL 0
#define MAP_BLACK 1
#define MAP_WHITE 2

class ReversiGameDoc
{
public:
	ReversiGameDoc();
	void initiateMap();
	bool ableToPut(const int &x, const int &y, const int &color);
	void put(const int &x, const int &y, const int &color);
	bool checkEnd();
	int m_map[8][8];
	int m_state;
	int m_number[3];
	CPoint m_last_put;
};
