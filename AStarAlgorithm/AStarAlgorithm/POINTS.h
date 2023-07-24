#pragma once

class Square
{
private:
	int x;
	int y;
	int len;
	int open;
	int block;
	double G;
	double H;
	double F;
public:
	void setX(int x) { this->x = x; }
	void setY(int y) { this->y = y; }
	void setLen(int len) { this->len = len; }
	void setOpen(int open) { this->open = open; }
	void setBlock(int block) { this->block = block; }
	void setG(double G) { this->G = G; }
	void setH(double H) { this->H = H; }
	void setF(double F) { this->F = F; }

	int getX() { return x; }
	int getY() { return y; }
	int getLen() { return len; }
	int getOpen() { return open; }
	int getBlock() { return block; }
	double getG() { return G; }
	double getH() { return H; }
	double getF() { return F; }
};