#include <stdio.h>
#include <stdint.h>

__pragma(pack(push, 1))
struct myFloat_s
{
	uint8_t sign : 1;
	uint8_t exponent : 8;
	uint32_t digits : 23;
}
__pragma(pack(pop));

typedef struct myFloat_s Float;

int mylog2(uint32_t n)
{
	uint32_t i = 0;
	while (n > 0)
	{
		n = n / 2;
		i++;
	}
	return i;
}


uint32_t int_digit_count(uint32_t n, uint8_t base)
{
	uint32_t ret = 0;
	while (n > 0)
	{
		n = n / base;
		ret++;
	}
	return ret;
}

uint32_t pow2(uint32_t p)
{
	uint32_t ret = 1;
	return ret << p;
}

uint32_t int_to_mant(uint32_t whole, uint8_t exp)
{

}


int main(void)
{
	// -127..127 -> -63.5, -63 .. 63, 63.5
	/*for (int8_t i = 0xFF; i < 0x7F; i++)
	{
		//int32_t buf = ((i & 0x80) << 0x0FFF) | ((i % 2) << 0x07FF) | (log2(i) & 0x07FF);
		float tmp = i * 0.5f;//*(float*)&buf;
	
	}
	*/
	float tmp = 1234.4567f;
	float tmp2 = 0;
	uint16_t int_part = 1234; // -> exp = 2^10 -> .exp = 137
	uint16_t point_part = 5678; // 12345678 / exp = 12056 ~ 1234.5678 / exp = 1.2056 -> .mant 
	uint32_t whole = int_part << int_digit_count(point_part, 2) | point_part;
	uint8_t sign = 1;

	printf("sizeof(Float)=%zd\n", sizeof(Float));
	Float f = (Float){ .sign = 1, .exponent = 137, .digits = 2056 };
	tmp2 = *(float*)&f;
	printf("%+06.6lf\t%01u\t%03u\t%010u\n", tmp2, f.sign, f.exponent, f.digits);
	printf("%+06.6lf\t%01u\t%03u\t%010u\n", tmp, ((Float*) & tmp)->sign, ((Float*)&tmp)->exponent, ((Float*)&tmp)->digits);
}