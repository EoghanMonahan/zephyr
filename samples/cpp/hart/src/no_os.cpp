
#include "no_os.h"
#include <stdlib.h>
#include <zephyr/drivers/spi.h>

void no_os_put_unaligned_be16(uint16_t val, uint8_t *buf)
{
	buf[1] = val & 0xFF;
	buf[0] = val >> 8;
}

uint8_t no_os_crc8(const uint8_t * table, const uint8_t *pdata, size_t nbytes,
		   uint8_t crc)
{
	unsigned int idx;

	while (nbytes--) {
		idx = (crc ^ *pdata);
		crc = (table[idx]) & 0xff;
		pdata++;
	}

	return crc;
}

void no_os_crc8_populate_msb(uint8_t * table, const uint8_t polynomial)
{
	if (!table)
		return;

	for (int16_t n = 0; n < NO_OS_CRC8_TABLE_SIZE; n++) {
		uint8_t currByte = (uint8_t)n;
		for (uint8_t bit = 0; bit < 8; bit++) {
			if ((currByte & 0x80) != 0) {
				currByte <<= 1;
				currByte ^= polynomial;
			} else {
				currByte <<= 1;
			}
		}
		table[n] = currByte;
	}
}

uint16_t no_os_get_unaligned_be16(uint8_t *buf)
{
	return buf[1] | ((uint16_t)buf[0] << 8);
}

uint32_t no_os_find_first_set_bit(uint32_t word)
{
	uint32_t first_set_bit = 0;

	while (word) {
		if (word & 0x1)
			return first_set_bit;
		word >>= 1;
		first_set_bit ++;
	}

	return 32;
}

uint32_t no_os_field_prep(uint32_t mask, uint32_t val)
{
	return (val << no_os_find_first_set_bit(mask)) & mask;
}

uint32_t no_os_field_get(uint32_t mask, uint32_t word)
{
	return (word & mask) >> no_os_find_first_set_bit(mask);
}

int32_t no_os_gpio_direction_output(struct no_os_gpio_desc *desc,
				    uint8_t value)
{
	return 0;
}


int32_t no_os_gpio_get_optional(struct no_os_gpio_desc **desc,
				const struct no_os_gpio_init_param *param)
{
	static const struct gpio_dt_spec ad74416h_reset =
		GPIO_DT_SPEC_GET(DT_NODELABEL(ad74416h_reset), gpios);

	int ret;

	ret = gpio_pin_configure_dt(&ad74416h_reset, GPIO_OUTPUT_LOW);
	if (ret)
		return ret;

	return 0;
}

int32_t no_os_gpio_remove(struct no_os_gpio_desc *desc)
{
	return 0;
}

int32_t no_os_gpio_set_value(struct no_os_gpio_desc *desc,
			     uint8_t value)
{
	return 0;
}

int32_t no_os_spi_init(struct no_os_spi_desc **desc,
		       const struct no_os_spi_init_param *param)
{
	return 0;
}

int32_t no_os_spi_remove(struct no_os_spi_desc *desc)
{
	return 0;
}

int32_t no_os_spi_write_and_read(struct no_os_spi_desc *desc,
				 uint8_t *data,
				 uint16_t bytes_number)
{
	const struct spi_dt_spec dev_spi =
		SPI_DT_SPEC_GET(DT_NODELABEL(ad74416h/*adin1110*/),
					     SPI_OP_MODE_MASTER |
					     SPI_TRANSFER_MSB |
					     SPI_WORD_SET(8) |
					     SPI_MODE_CPOL,
					     0);
	struct spi_buf_set rx_buf_set;
	struct spi_buf_set tx_buf_set;
	struct spi_buf rx_buf;
	struct spi_buf tx_buf;

	tx_buf.len = bytes_number;
	tx_buf.buf = data;
	tx_buf_set.buffers = &tx_buf;
	tx_buf_set.count = 1;

	rx_buf.len = bytes_number;
	rx_buf.buf = data;
	rx_buf_set.buffers = &rx_buf;
	rx_buf_set.count = 1;

	return spi_transceive_dt(&dev_spi, &tx_buf_set, &rx_buf_set);
}

void no_os_udelay(uint32_t usecs)
{
	k_sleep(K_USEC(usecs));
}

void no_os_mdelay(uint32_t msecs)
{
	k_sleep(K_MSEC(msecs));
}

unsigned int no_os_hweight8(uint8_t word)
{
	uint32_t count = 0;

	while (word) {
		if (word & 0x1)
			count++;
		word >>= 1;
	}

	return count;
}

uint64_t no_os_do_div(uint64_t* n,
		      uint64_t base)
{
	uint64_t mod = 0;

	mod = *n % base;
	*n = *n / base;

	return mod;
}

uint64_t no_os_div_u64_rem(uint64_t dividend, uint32_t divisor,
			   uint32_t *remainder)
{
	*remainder = no_os_do_div(&dividend, divisor);

	return dividend;
}

int64_t no_os_div_s64_rem(int64_t dividend, int32_t divisor, int32_t *remainder)
{
	*remainder = dividend % divisor;

	return dividend / divisor;
}


__attribute__((weak)) void *no_os_calloc(size_t nitems, size_t size)
{
	return calloc(nitems, size);
}

__attribute__((weak)) void no_os_free(void *ptr)
{
	free(ptr);
}

