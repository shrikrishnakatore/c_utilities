/**
 * @file string.h
 *
 * @brief String management utilities.
 *
 *  Created on: 30/dic/2013
 *      Author: davide
 */

#ifndef STRING_H_
#define STRING_H_

#define NIBBLE2HEX(c) ((c) > 9 ? (c) + 'A' - 10 : (c) + '0')
#define HEX2NIBBLE(c) ((c) > '9' ? (c) - 'A' + 10 : (c) - '0')

uint8_t AT_Length(const uint8_t * const s);
uint8_t NMEA_Length(const uint8_t * const s);

void NMEA_Append_Checksum(uint8_t * const msg, const uint8_t len);
uint8_t NMEA_Checksum(const uint8_t * const msg);

uint8_t String_Copy(const uint8_t *source, uint8_t *dest);
//uint8_t String_Length(const uint8_t *s);//Krishna
int String_N_Compare(const uint8_t *s1, const uint8_t *s2, size_t n);
void String_Reverse(uint8_t *s, const uint8_t len);

double Deg_To_Double(const uint8_t *s);

double Atod(const uint8_t *s);
uint32_t Atoi(const uint8_t *s);
uint8_t is_Decimal_UnsignedNumber(const uint8_t *s);
int32_t Atoi_Signed(const uint8_t *s);

uint8_t Itoa(int32_t n, uint8_t *dest);
uint8_t Ftoa(float n, const uint8_t after_point, uint8_t *dest);

//krishna//start
void * memcpy(void *dest,const void * source,const uint16_t count);
void * memmove(void *dst, const void *src, uint16_t len);
uint16_t strlen(const char * msg);
//Krishna//end

#endif /* STRING_H_ */
