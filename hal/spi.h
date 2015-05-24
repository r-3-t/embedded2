#pragma once

#include "mcu_internal.h"


#pragma once

#include <types.hpp>
#include <type_traits>

namespace spi {


	struct Configuration
	{
		typedef enum {_2Lines_FullDuplex, _2Lines_RxOnly, _1Line_Rx, _1Line_Tx} Direction_t;
		Direction_t direction;           /*!< Specifies the SPI unidirectional or bidirectional data mode.
											This parameter can be a value of @ref SPI_data_direction */

		//typedef enum {_8b, _16b} DataSize_t;
		//DataSize_t dataSize;            /*!< Specifies the SPI data size.
		//									This parameter can be a value of @ref SPI_data_size */

		typedef enum {Low, High} ClockPolarity_t;
		ClockPolarity_t clockPolarity;                /*!< Specifies the serial clock steady state.
											This parameter can be a value of @ref SPI_Clock_Polarity */

		typedef enum {_1_Edge, _2_Edge} ClockPhase_t;
		ClockPhase_t clockPhase;                /*!< Specifies the clock active edge for the bit capture.
											This parameter can be a value of @ref SPI_Clock_Phase */

		typedef enum {Soft, Hard} SlaveSelectManagement_t;
		SlaveSelectManagement_t slaveSelectManagement;                 /*!< Specifies whether the NSS signal is managed by
											hardware (NSS pin) or by software using the SSI bit.
											This parameter can be a value of @ref SPI_Slave_Select_management */

		typedef enum {_2, _4, _8, _16, _32, _64, _128, _256} BaudRatePrescaler_t;
		BaudRatePrescaler_t baudRatePrescaler;   /*!< Specifies the Baud Rate prescaler value which will be
											used to configure the transmit and receive SCK clock.
											This parameter can be a value of @ref SPI_BaudRate_Prescaler
											@note The communication clock is derived from the master
											   clock. The slave clock does not need to be set. */

		typedef enum {LSB, MSB} FirstBitTransmission_t;
		FirstBitTransmission_t firstBitTransmission;            /*!< Specifies whether data transfers start from MSB or LSB bit.
											This parameter can be a value of @ref SPI_MSB_LSB_transmission */

		unsigned long CRCPolynomial;       /*!< Specifies the polynomial used for the CRC calculation. */

		unsigned long DataRate;       /*!< Specifies the data rate. */

		static Configuration _default()
		{
			return {_2Lines_FullDuplex, Low, _1_Edge, Soft, _2, MSB, 8, 1000000};
		}
		
	};
	
	class spi
	{
	public:
		typedef void (*receive_callback)(const uint8_t c);
	
		spi() {}
		spi(unsigned int id);

		void set_as_master(Configuration config, receive_callback callback);

		void set_as_slave(Configuration config, receive_callback callback);

		virtual uint8_t send(uint8_t data);

	private:
		spi_mcu_internal _internal;
		receive_callback _receive_callback;

	};

}
