#include <spi.h>


int main(int argc, char** argv)
{
	spi::spi spi1(1, nullptr, ::spi::config::_default_master());

	spi1.send("SPI TEST");

	return 0;
}

