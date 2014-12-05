#include "stdafx.h"

ReversiGameDoc::ReversiGameDoc()
{
	initiateMap();
	m_state = STATE_NOT_START;
}

void ReversiGameDoc::initiateMap()
{
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			m_map[i][j] = MAP_NULL;
	m_map[3][3] = m_map[4][4] = MAP_WHITE;
	m_map[3][4] = m_map[4][3] = MAP_BLACK;
	m_number[MAP_BLACK] = m_number[MAP_WHITE] = 2;
	m_last_put.x = -1;
	m_last_put.y = -1;
}

bool ReversiGameDoc::ableToPut(const int &x, const int &y, const int &color)
{
	int delta_x[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
	int delta_y[8] = {0, -1, -1, -1, 0, 1, 1, 1};
	int sum;
	int tx, ty;
	bool b;

	if (m_map[x][y] != MAP_NULL)
		return false;
	for (int i = 0; i < 8; i++)
	{
		sum = 0;
		b = false;
		tx = x;
		ty = y;
		while (true)
		{
			tx += delta_x[i];
			ty += delta_y[i];
			if ((tx < 0) || (tx >7) || (ty < 0) || (ty > 7))
				break;
			if (m_map[tx][ty] == MAP_NULL)
				break;
			if (m_map[tx][ty] == color)
			{
				b = true;
				break;
			}
			sum++;
		}
		if (b && (sum > 0))
			return true;
	}
	return false;
}

void ReversiGameDoc::put(const int &x, const int &y, const int &color)
{
	int delta_x[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
	int delta_y[8] = {0, -1, -1, -1, 0, 1, 1, 1};
	int sum;
	int tx, ty;
	bool b;

	m_map[x][y] = color;
	m_number[color]++;
	for (int i = 0; i < 8; i++)
	{
		sum = 0;
		b = false;
		tx = x;
		ty = y;
		while (true)
		{
			tx += delta_x[i];
			ty += delta_y[i];
			if ((tx < 0) || (tx >7) || (ty < 0) || (ty > 7))
				break;
			if (m_map[tx][ty] == MAP_NULL)
				break;
			if (m_map[tx][ty] == color)
			{
				b = true;
				break;
			}
			sum++;
		}
		if (b && (sum > 0))
		{
			tx = x;
			ty = y;
			while (true)
			{
				tx += delta_x[i];
				ty += delta_y[i];
				if (m_map[tx][ty] == color)
					break;
				m_map[tx][ty] = color;
				m_number[color]++;
				m_number[3 - color]--;
			}
		}
	}
}

bool ReversiGameDoc::checkEnd()
{
	if ((m_number[MAP_BLACK] + m_number[MAP_WHITE] == 64) || (m_number[MAP_BLACK] == 0) || (m_number[MAP_WHITE] == 0))
	{
		if (m_number[MAP_BLACK] > m_number[MAP_WHITE])
			m_state = STATE_BLACK_WIN;
		else
			if (m_number[MAP_BLACK] < m_number[MAP_WHITE])
				m_state = STATE_WHITE_WIN;
			else
				m_state = STATE_PEACE;
		return true;
	}
	return false;
}
