/*
 * cli_setup.h
 *
 *  Created on: Apr 1, 2025
 *      Author: HTSANG
 */

#ifndef CLI_SETUP_H_
#define CLI_SETUP_H_

#include "embedded_cli.h"
#include "basetypedef.h"
#include "uart.h"
#include "stm32f407xx.h"
#include "board.h"


// Definitions for CLI sizes
#define CLI_BUFFER_SIZE 2048
#define CLI_RX_BUFFER_SIZE		16
#define CLI_CMD_BUFFER_SIZE 	64
#define CLI_HISTORY_SIZE 		128
#define CLI_MAX_BINDING_COUNT 	32
#define CLI_AUTO_COMPLETE 		1
#define CLI_INITATION_EXP_CONSOLE		"EXP_V110:~ $ "
#define CLI_INITATION_EXP_FORWARD		"EXP_V110_FORWARD:~ $ "
/**
 * Definition of the cli_printf() buffer size.
 * Can make smaller to decrease RAM usage,
 * make larger to be able to print longer strings.
 */
#define CLI_PRINT_BUFFER_SIZE	512

// Definitions for CLI UART peripheral
//#define UART_CLI_PERIPH			USART6

/**
 * Char for char is needed for instant char echo, so size 1
 */
#define UART_RX_BUFF_SIZE		1

/**
 * Function to setup the configuration settings for the CLI,
 * based on the definitions from this header file
 */
Std_ReturnType SystemCLI_Init();

/**
 * Function to encapsulate the 'embeddedCliPrint()' call with
 * print formatting arguments (act like printf(), but keeps cursor at correct location).
 * The 'embeddedCliPrint()' function does already add a linebreak ('\r\n')
 * to the end of the print statement, so no need to add it yourself.
 * @param format format string
 * @param ... format arguments
 */
void cli_printf(const char *format, ...);

/**
 * Getter function, to keep only one instance of the EmbeddedCli pointer in this file.
 * @return
 */
//EmbeddedCli *get_EXPForward_CliPointer();
EmbeddedCli *get_EXPConsole_CliPointer();

#endif /* CLI_SETUP_H_ */
