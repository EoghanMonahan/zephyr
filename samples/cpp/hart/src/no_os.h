
#ifndef __NO_OS_H__
#define __NO_OS_H__

#include <stdint.h>
#include <errno.h>

struct no_os_spi_init_param {
};

struct no_os_spi_desc {
};

struct no_os_gpio_init_param{
};

struct no_os_gpio_desc {
};

enum no_os_gpio_values {
	/** GPIO logic low */
	NO_OS_GPIO_LOW,
	/** GPIO logic high */
	NO_OS_GPIO_HIGH,
	/** GPIO high impedance */
	NO_OS_GPIO_HIGH_Z
};

#define NO_OS_CRC8_TABLE_SIZE 256

#define NO_OS_DECLARE_CRC8_TABLE(_table) \
	static uint8_t _table[NO_OS_CRC8_TABLE_SIZE]

#define NO_OS_BIT(x)	(1 << (x))
#define NO_OS_BITS_PER_LONG 32

#define NO_OS_GENMASK(h, l) ({ 					\
		uint32_t t = (uint32_t)(~0UL);			\
		t = t << (NO_OS_BITS_PER_LONG - (h - l + 1));	\
		t = t >> (NO_OS_BITS_PER_LONG - (h + 1));	\
		t;						\
})

void no_os_put_unaligned_be16(uint16_t val, uint8_t *buf);
uint16_t no_os_get_unaligned_be16(uint8_t *buf);
uint8_t no_os_crc8(const uint8_t * table, const uint8_t *pdata, size_t nbytes,
		   uint8_t crc);
void no_os_crc8_populate_msb(uint8_t * table, const uint8_t polynomial);
uint32_t no_os_find_first_set_bit(uint32_t word);
uint32_t no_os_field_prep(uint32_t mask, uint32_t val);
uint32_t no_os_field_get(uint32_t mask, uint32_t word);
void no_os_udelay(uint32_t usecs);
void no_os_mdelay(uint32_t msecs);
int32_t no_os_spi_write_and_read(struct no_os_spi_desc *desc,
				 uint8_t *data,
				 uint16_t bytes_number);
unsigned int no_os_hweight8(uint8_t word);
uint64_t no_os_div_u64_rem(uint64_t dividend, uint32_t divisor,
			   uint32_t *remainder);
int64_t no_os_div_s64_rem(int64_t dividend, int32_t divisor, int32_t *remainder);
void *no_os_calloc(size_t nitems, size_t size);
void no_os_free(void *ptr);
int32_t no_os_gpio_direction_output(struct no_os_gpio_desc *desc,
				    uint8_t value);
int32_t no_os_gpio_set_value(struct no_os_gpio_desc *desc,
			     uint8_t value);
int32_t no_os_gpio_get_optional(struct no_os_gpio_desc **desc,
				const struct no_os_gpio_init_param *param);
int32_t no_os_gpio_remove(struct no_os_gpio_desc *desc);
int32_t no_os_spi_init(struct no_os_spi_desc **desc,
		       const struct no_os_spi_init_param *param);
int32_t no_os_spi_remove(struct no_os_spi_desc *desc);
#endif // __NO_OS_H__
