#include <spi.h>


void spi_slave_callback(uint8_t c)
{
  printf ("spi slave recv : %02X\r\n", c);
}

int main(int argc, char** argv)
{
	spi::spi spi1(1, spi_slave_callback, ::spi::config::_default_slave());

	while (true) {}

	return 0;
}

