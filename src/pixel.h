#ifndef PIXEL_H
#define PIXEL_H

#include <stdint.h>

class Pixel
{
	public:
		Pixel(int r=0, int g=0, int b=0);
		Pixel(const Pixel&);
		Pixel& operator=(const Pixel&);

		uint32_t toInt32() const;

	private:
		char m_R;
		char m_G;
		char m_B;
		char m_A;
};

#endif /* PIXEL_H */
