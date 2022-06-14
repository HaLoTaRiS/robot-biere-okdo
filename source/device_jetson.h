/*************************************************************
 * 		PROJET ROBOT BIERE
 *************************************************************
 * file : device_jetson.h
 * Auteurs :
 *   - Baptiste FRITOT
 *   - Leo BOSLAND
 *   - Jeremy VICENTE
 *   - Fabien BILHAUT
 *
 * All rights reserved.
 */


#ifndef INC_DEVICE_JETSON_H
#define INC_DEVICE_JETSON_H

// Address ID : Réception
#define JETSON_ADDR_RX_LEFT				0x4C	// Char : L
#define JETSON_ADDR_RX_RIGHT			0x52	// Char : R
#define JETSON_ADDR_RX_BRAS				0x53	// Char : S

// Address ID :
#define JETSON_ADDR_TX_ULTRASON_1		0x41	// Char : A
#define JETSON_ADDR_TX_ULTRASON_2		0x42	// Char : B
#define JETSON_ADDR_TX_LASER_1			0x43	// Char : C
#define JETSON_ADDR_TX_LASER_2			0x44	// Char : D
#define JETSON_ADDR_TX_LASER_3			0x45	// Char : E
#define JETSON_ADDR_TX_LASER_4			0x46	// Char : F
#define JETSON_ADDR_TX_BRAS_ETAT		0x49	// Char : I
#define JETSON_ADDR_TX_PRECENCE_BEER	0x4A	// Char : J

// Data
#define JETSON_DATA_BRAS_OPEN			0x01
#define JETSON_DATA_BRAS_CLOSE			0x00
#define JETSON_DATA_PRESENCE_BEER		0x01
#define JETSON_DATA_NO_BEER				0x00

#endif
