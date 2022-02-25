/**
 *  @file string.c
 *
 *  @brief String related utility functions.
 *
 *  Author: Krishna Katore
 *  Date: 6 Jun 2021
 */

#include "string.h"

#include <math.h>

#define YEAR		0
#define MONTH		1
#define	DAY			2
#define HOURS		3
#define MINUTES		4
#define SECONDS		5
#define TIME_ZONE	6

#define DAY_OFFSET	86400
#define HOUR_OFFSET	3600
#define MIN_OFFSET	60


#if 0
/**
 * @brief Returns the length of the specified null-terminated string.
 * @return The length of the string, excluding the terminating null character.
 */
uint8_t String_Length(const uint8_t *s) {

	const uint8_t* t = s;

	for (t = s; *t; ++t)
		;

	return t - s;
}
#endif

/**
 * @brief Compares at most n characters of the specified strings.
 * @param s1 the first string
 * @param s2 the second string
 * @return 0 if the strings are equal, -1 if s1 lexicographically precedes s2, 1 otherwise.
 */
int String_N_Compare(const uint8_t *s1, const uint8_t *s2, size_t n) {

	for (; n > 0; s1++, s2++, --n) {
		if (*s1 != *s2)
			return ((*(unsigned char *) s1 < *(unsigned char *) s2) ? -1 : +1);
		else if (*s1 == '\0')
			return n;
	}
	return 0;
}

/**
 * @brief Copies the content of the source string into the specified destination string.
 * @param source the source string, which must be null-terminated
 * @param dest the destination string
 * @return The number of copied characters.
 * @details The destination string is null-terminated. Copying into a destination string with not enough
 * space results in undefined behavior.
 */
uint8_t String_Copy(const uint8_t *source, uint8_t *dest) {

	const uint8_t * const start = source;

	while (*source)
		*(dest++) = *(source++);

	*dest = '\0';

	return source - start;
}

/**
 * @brief Reverses a string in place.
 * @param s the string to reverse
 * @param len the length of the string
 */
void String_Reverse(uint8_t *s, const uint8_t len) {

	uint8_t tmp;
	uint8_t *end = s + len - 1;

	while (s < end) {
		tmp = *s;
		*(s++) = *end;
		*(end--) = tmp;
	}
}


/**
 * @brief Parses a string representing a double-precision floating point number.
 * @param s the null-terminated string to parse
 * @returns The double-precision floating point number represented by the string.
 * In case of error, 0 is returned.
 */
double Atod(const uint8_t *s) {

	if (!s || !*s)
		return 0.0;

	double integerPart = 0;
	double fractionPart = 0;
	int32_t divisorForFraction = 1;
	int8_t sign = 1;
	uint8_t inFraction = 0;

	if (*s == '-') {
		++s;
		sign = -1;
	} else if (*s == '+') {
		++s;
	}

	while (*s != '\0') {
		if (*s >= '0' && *s <= '9') {
			if (inFraction) {
				fractionPart = fractionPart * 10 + (*s - '0');
				divisorForFraction *= 10;
			} else {
				integerPart = integerPart * 10 + (*s - '0');
			}
		} else if (*s == '.') {
			if (inFraction)
				return 0.0;
			else
				inFraction = 1;
		} else {
			return 0.0;
		}
		++s;
	}
	return sign * (integerPart + fractionPart / divisorForFraction);
}

/**
 * @brief Parses a string representing an unsigned integer.
 * @param s the null-terminated string to parse
 * @returns The unsigned integer represented by the string.
 */
uint32_t Atoi(const uint8_t *s) {

	int32_t res = 0;

	if (!s)
		return res;

	while (*s) {
		res *= 10;
		res += (*(s++) - '0') % 10;
	}
	return res;
}

/**
 * @brief check for decimal unsigned  integer or not .
 * @param s the null-terminated string to parse
 * @returns 0x01 on success , 0x00 on error .
 */
uint8_t is_Decimal_UnsignedNumber(const uint8_t *s){
	if(!s)
		return 0x00;
	while(*s){
		if((*s >='0') && (*s <= '9'))
			s++;
		else
			return 0x00;
	}
	return 0x01;
}
/**
 * @brief Parses a string representing a signed integer.
 * @param s the null-terminated string to parse
 * @returns The signed integer represented by the string.
 */
int32_t Atoi_Signed(const uint8_t *s) {

	int32_t res = 0;
	uint8_t negative_flag = 0;

	if (!s)
		return res;

	if (*s == '-') {
		negative_flag = 1;
		s++;
	}

	while (*s) {
		res *= 10;
		res += (*(s++) - '0') % 10;
	}
	return negative_flag ? res * -1 : res;
}

/**
 * @brief Writes the value of an integer into the destination string.
 * @param n the number to write
 * @param dest the destination string
 * @return The number of written characters.
 * @details A null terminator is appended at the end of the string.
 */
uint8_t Itoa(int32_t n, uint8_t *dest) {

	uint8_t *start = dest;
	uint8_t negative_flag = 0;

	if (n < 0) {
		n *= -1;
		negative_flag = 1;
	}

	do {
		*(dest++) = n % 10 + '0';
	} while ((n /= 10) > 0);

	if (negative_flag)
		*(dest++) = '-';

	*dest = '\0';

	String_Reverse(start, dest - start);
	return dest - start;
}

/**
 * @brief Writes a float into the destination string.
 * @param n The number to write
 * @param divider The number of digits after the decimal point
 * @param dest the destination string
 * @return The number of written characters, including the dot separating integer and fractional parts.
 * @details A null terminator is appended at the end of the string.
 */
uint8_t Ftoa(float n, const uint8_t after_point, uint8_t *dest) {

	uint8_t *start = dest;
	int32_t i_part = (int32_t) n;
	float f_part = n - (float) i_part;
	int8_t i;
	int32_t f_part_int, tmp;

	if (f_part < 0) {
		*(dest++) = '-';
		f_part *= -1;
		i_part *= -1;
	}

	dest += Itoa(i_part, dest);

	if (after_point != 0) {

		*(dest++) = '.';

		f_part_int = (int32_t) (f_part * pow(10, after_point));
		tmp = f_part_int;

		i = 0;
		while (tmp) {
			i++;
			tmp /= 10;
		}

		while (i++ < after_point) {
			*(dest++) = '0';
		}

		dest += Itoa(f_part_int, dest);
	}

	return dest - start;
}


void * memcpy(void *dest ,const void *source,const uint16_t count)
{
	char *csrc = (char *)source;
	char *cdest = (char *)dest;

	// Copy contents of src[] to dest[]
	for (uint16_t i=0; i< count; i++)
	    cdest[i] = csrc[i];
	return dest;
}

void * memmove (void *dst, const void *src, uint16_t len)
{
	char *d = dst;
	const char *s = src;
	if (d < s)
		while (len--)
			*d++ = *s++;
	else{
		char *lasts = (char *)(s + (len-1));
		char *lastd = d + (len-1);
		while (len--)
			*lastd-- = *lasts--;
	}
	return dst;
}

uint16_t strlen(const char * str){
	uint16_t i=0;
	for (i = 0;str[i] != '\0'; i++)
			;
	return i;
}


