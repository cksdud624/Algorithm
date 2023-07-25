#pragma once

class Square
{
private:
	int x;
	int y;
	int len;
	int open;
	int block;
	int G;
	int H;
	int F;
	int beforex;
	int beforey;
public:
	void setX(int x) { this->x = x; }
	void setY(int y) { this->y = y; }
	void setLen(int len) { this->len = len; }
	void setOpen(int open) { this->open = open; }
	void setBlock(int block) { this->block = block; }
	void setG(int G) { this->G = G; }
	void setH(int H) { this->H = H; }
	void setF(int F) { this->F = F; }
	void setBeforeX(int beforex) { this->beforex = beforex; }
	void setBeforeY(int beforey) { this->beforey = beforey; }
	void Clear() { open = 0; G = 0; H = 0; F = 0; beforex = 0; beforey = 0; }

	int getX() { return x; }
	int getY() { return y; }
	int getLen() { return len; }
	int getOpen() { return open; }
	int getBlock() { return block; }
	int getG() { return G; }
	int getH() { return H; }
	int getF() { return F; }
	int getBeforeX() { return beforex; }
	int getBeforeY() { return beforey; }
};