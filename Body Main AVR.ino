/*
 Name:		Shadow_Receiver.ino
 Created:	6/26/2017 9:06:12 PM
 Author:	hoodlum
*/

// =======================================================================================
//        SHADOW_MD:  Small Handheld Arduino Droid Operating Wand + MarcDuino
// =======================================================================================
//                          Last Revised Date: 08/23/2015
//                             Revised By: vint43
//                Inspired by the PADAWAN / KnightShade SHADOW effort
// =======================================================================================
//
//         This program is free software: you can redistribute it and/or modify it for
//         your personal use and the personal use of other astromech club members.  
//
//         This program is distributed in the hope that it will be useful 
//         as a courtesy to fellow astromech club members wanting to develop
//         their own droid control system.
//
//         IT IS OFFERED WITHOUT ANY WARRANTY; without even the implied warranty of
//         MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
//
//         You are using this software at your own risk and, as a fellow club member, it is
//         expected you will have the proper experience / background to handle and manage that 
//         risk appropriately.  It is completely up to you to insure the safe operation of
//         your droid and to validate and test all aspects of your droid control system.
//
// =======================================================================================
//   Note: You will need a Arduino Mega ADK rev3 to run this sketch,
//   as a normal Arduino (Uno, Duemilanove etc.) doesn't have enough SRAM and FLASH
//
//   This is written to be a SPECIFIC Sketch - supporting only one type of controller
//      - PS3 Move Navigation + MarcDuino Dome Controller & Optional Body Panel Controller
//
//   PS3 Bluetooth library - developed by Kristian Lauszus (kristianl@tkjelectronics.com)
//   For more information visit my blog: http://blog.tkjelectronics.dk/ or
//
//   Sabertooth (Foot Drive):
//         Set Sabertooth 2x32 or 2x25 Dip Switches: 1 and 2 Down, All Others Up
//
//   SyRen 10 Dome Drive:
//         For SyRen packetized Serial Set Switches: 1, 2 and 4 Down, All Others Up
//         NOTE:  Support for SyRen Simple Serial has been removed, due to problems.
//         Please contact DimensionEngineering to get an RMA to flash your firmware
//         Some place a 10K ohm resistor between S1 & GND on the SyRen 10 itself
//
// =======================================================================================
//
// ---------------------------------------------------------------------------------------
//                        General User Settings
// ---------------------------------------------------------------------------------------


// local 00:1A:7D:DA:71:14

String PS3ControllerFootMac = "00:07:04:EB:43:DC";  //Set this to your FOOT PS3 controller MAC address
String PS3ControllerDomeMAC = "04:76:6E:98:F7:4B";  //Set to a secondary DOME PS3 controller MAC address (Optional)

													// 00:07:04:EB:43:DC
													// 04:76:6E:98:F7:4B

String PS3ControllerBackupFootMac = "00:07:04:EE:12:B8";  //Set to the MAC Address of your BACKUP FOOT controller (Optional)
String PS3ControllerBackupDomeMAC = "00:07:04:BB:2C:11";  //Set to the MAC Address of your BACKUP DOME controller (Optional)

// 00:1A:7D:DA:71:14


typedef enum _enum_ioPin_Type {
	pinHWSerialRX = 0,
	pinHWSerialTX = 1,

#if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega168__)

	pinOut_DomeEnableRelay = 2,         // relay for dome power
	pinOut_MotorRightEnableRelay = 3,   // relay for right motor
	pinOut_MotorLeftEnableRelay = 4,    // relay for left motor
	pinOut_MotorDomeEnableRelay = 5,    // relay for dome motor

	pinOut_MotorDriveControl = 6, // both left and right - goes to the SaberTooth 2x32 - simple software serial
	pinOut_MotorDomeControl = 7, // dome - goes to the Syren10 - simple software serial or rc servo control

	pinIn_BLE_RX = 8,
	pinOut_BLE_TX = 9,
	pinIn_BLE_State = 10,
	pinOut_BLE_Enable = 11,

	pinOut_StatusLEDs = 12,       // neopixels x 4 : 1 = battery, 2 = CPU, 3 =, 4 =, 5= ,6= ,7= ,8=

	pinOut_MP3SoundTx = 13,
#endif

#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)


#define ESP8266MeshSerial Serial1 
#define DomePanelController Serial1 
#define BodyPanelController Serial3

	//    pinIn_BLE_RX = 15, 
	//    pinOut_BLE_TX = 14,  
	//    pinIn_BLE_State = 38,
	//    pinOut_BLE_Enable = 23,

	pinOut_StatusLED = 13,



	pinHWSerial3TX = 14,  // Mega Serial TX3    // 
	pinHWSerial3RX = 15,  // Mega Serial RX3    // 
	pinHWSerial2TX = 16,  // Mega Serial TX2    // syren/sabertooth
	pinHWSerial2RX = 17,  // Mega Serial RX2    // syren/sabertooth
	pinHWSerial1TX = 18,  // Mega Serial TX1    // 
	pinHWSerial1RX = 19,  // Mega Serial RX1    // 
	pin20 = 20,  // Mega SDA
	pin21 = 21,  // Mega SCL

	pinOut_StatusLEDs = 22,         // neopixels x 8 : 1 = battery, 2 = CPU, 3 = , 4 = , 5= ,6= ,7=FootNav ,8=DomeNav
	pinOut_MP3Sound1Tx = 23,		// R2 Sounds
	pinOut_MP3Sound2Tx = 24,		// background music

	pin25 = 25,

	pinOut_MotorDomeEnableRelay = 26,    // relay for dome
	pinOut_MotorLeftEnableRelay = 27,    // relay for left motor
	pinOut_MotorRightEnableRelay = 28,   // relay for right motor
	pinOut_PowerDomeEnableRelay = 29,   // relay dome power

								   //pinOut_MotorDomeControl = 30, // dome - goes to the Syren10 - simple software serial or rc servo control
								   //pinOut_MotorDriveControl = 31, // both left and right - goes to the SaberTooth 2x32 - simple software serial

								   pin30 = 30,
								   pin31 = 31,

								   pin32 = 32,
								   pin33 = 33,
								   pin34 = 34,
								   pin35 = 35,
								   pin36x = 36, // not currently being passed throught to sensor sheild
								   pin37x = 37, // not currently being passed throught to sensor sheild

								   pin38 = 38,
								   pin39 = 39,
								   pin40 = 40,
								   pin41 = 41,
								   pin42 = 42,
								   pin43 = 43,
								   pin44 = 44,
								   pin45 = 45,
								   pin46 = 46,
								   pin47 = 47,
								   pin48 = 48,
								   pin49 = 49,

								   pin50 = 50,
								   pin51 = 51,
								   pin52 = 52,
								   pin53 = 53,

								   pinA0 = A0,
								   pinA1 = A1,
								   pinA2 = A2,
								   pinA3 = A3,
								   pinA4 = A4,
								   pinA5 = A5,
								   pinA6 = A6,
								   pinA7 = A7,

								   pinA8 = A8,
								   pinA9 = A9,
								   pinA10 = A10,
								   pinA11 = A11,
								   pinA12 = A12,
								   pinA13 = A13,
								   pinA14 = A14,
								   pinA15 = A15,
#endif

								   pinUNOA0 = A0,
								   pinUNOA1 = A1,
								   pinUNOA2 = A2,
								   pinUNOA3 = A3,
								   pinUNOA4 = A4,
								   pinUNOA5 = A5,
								   pinUNOA6 = A6,
								   pinIn_VoltageMonitor = A7,
								   pinEnd = 99
} ioPin_Type;









byte drivespeed1 = 45;   //For Speed Setting (Normal): set this to whatever speeds works for you. 0-stop, 127-full speed.
byte drivespeed2 = 70;  //For Speed Setting (Over Throttle): set this for when needing extra power. 0-stop, 127-full speed.
byte drivespeed3 = 110;  //For Speed Setting (Over Throttle): set this for when needing extra power. 0-stop, 127-full speed.

byte domeTurnSpeed = 75;      // the higher this number the faster it will spin in place, lower - the easier to control.
						  // Recommend beginner: 40 to 50, experienced: 50+, I like 75

byte domespeed = 100;    // If using a speed controller for the dome, sets the top speed
						 // Use a number up to 127

byte ramping = 1;        // Ramping- the lower this number the longer R2 will take to speedup or slow down,
						 // change this by increments of 1

byte joystickFootDeadZoneRange = 35;  // For controllers that centering problems, use the lowest number with no drift
byte joystickDomeDeadZoneRange = 35;  // For controllers that centering problems, use the lowest number with no drift

byte driveDeadBandRange = 10;     // Used to set the Sabertooth DeadZone for foot motors

int invertTurnDirection = 1;   //This may need to be set to 1 for some configurations
int invertSpeedDirection = -1;

byte domeAutoSpeed = 70;     // Speed used when dome automation is active - Valid Values: 50 - 100
int time360DomeTurn = 2500;  // milliseconds for dome to complete 360 turn at domeAutoSpeed - Valid Values: 2000 - 8000 (2000 = 2 seconds)

#define SHADOW_DEBUG       //uncomment this for console DEBUG output
#define SHADOW_VERBOSE     //uncomment this for console VERBOSE output

							 // ---------------------------------------------------------------------------------------
							 //                          MarcDuino Button Settings
							 // ---------------------------------------------------------------------------------------
							 // Std MarcDuino Function Codes:
							 //     1 = Close All Panels
							 //     2 = Scream - all panels open
							 //     3 = Wave, One Panel at a time
							 //     4 = Fast (smirk) back and forth wave
							 //     5 = Wave 2, Open progressively all panels, then close one by one
							 //     6 = Beep cantina - w/ marching ants panel action
							 //     7 = Faint / Short Circuit
							 //     8 = Cantina Dance - orchestral, rhythmic panel dance
							 //     9 = Leia message
							 //    10 = Disco
							 //    11 = Quite mode reset (panel close, stop holos, stop sounds)
							 //    12 = Full Awake mode reset (panel close, rnd sound, holo move,holo lights off)
							 //    13 = Mid Awake mode reset (panel close, rnd sound, stop holos)
							 //    14 = Full Awake+ reset (panel close, rnd sound, holo move, holo lights on)
							 //    15 = Scream, with all panels open (NO SOUND)
							 //    16 = Wave, one panel at a time (NO SOUND)
							 //    17 = Fast (smirk) back and forth (NO SOUND)
							 //    18 = Wave 2 (Open progressively, then close one by one) (NO SOUND)
							 //    19 = Marching Ants (NO SOUND)
							 //    20 = Faint/Short Circuit (NO SOUND)
							 //    21 = Rhythmic cantina dance (NO SOUND)
							 //    22 = Random Holo Movement On (All) - No other actions
							 //    23 = Holo Lights On (All)
							 //    24 = Holo Lights Off (All)
							 //    25 = Holo reset (motion off, lights off)
							 //    26 = Volume Up
							 //    27 = Volume Down
							 //    28 = Volume Max
							 //    29 = Volume Mid
							 //    30 = Open All Dome Panels
							 //    31 = Open Top Dome Panels
							 //    32 = Open Bottom Dome Panels
							 //    33 = Close All Dome Panels
							 //    34 = Open Dome Panel #1
							 //    35 = Close Dome Panel #1
							 //    36 = Open Dome Panel #2
							 //    37 = Close Dome Panel #2
							 //    38 = Open Dome Panel #3
							 //    39 = Close Dome Panel #3
							 //    40 = Open Dome Panel #4
							 //    41 = Close Dome Panel #4
							 //    42 = Open Dome Panel #5
							 //    43 = Close Dome Panel #5
							 //    44 = Open Dome Panel #6
							 //    45 = Close Dome Panel #6
							 //    46 = Open Dome Panel #7
							 //    47 = Close Dome Panel #7
							 //    48 = Open Dome Panel #8
							 //    49 = Close Dome Panel #8
							 //    50 = Open Dome Panel #9
							 //    51 = Close Dome Panel #9
							 //    52 = Open Dome Panel #10
							 //    53 = Close Dome Panel #10
							 //   *** BODY PANEL OPTIONS ASSUME SECOND MARCDUINO MASTER BOARD ON MEGA ADK SERIAL #3 ***
							 //    54 = Open All Body Panels
							 //    55 = Close All Body Panels
							 //    56 = Open Body Panel #1
							 //    57 = Close Body Panel #1
							 //    58 = Open Body Panel #2
							 //    59 = Close Body Panel #2
							 //    60 = Open Body Panel #3
							 //    61 = Close Body Panel #3
							 //    62 = Open Body Panel #4
							 //    63 = Close Body Panel #4
							 //    64 = Open Body Panel #5
							 //    65 = Close Body Panel #5
							 //    66 = Open Body Panel #6
							 //    67 = Close Body Panel #6
							 //    68 = Open Body Panel #7
							 //    69 = Close Body Panel #7
							 //    70 = Open Body Panel #8
							 //    71 = Close Body Panel #8
							 //    72 = Open Body Panel #9
							 //    73 = Close Body Panel #9
							 //    74 = Open Body Panel #10
							 //    75 = Close Body Panel #10
							 //   *** MAGIC PANEL LIGHTING COMMANDS
							 //    76 = Magic Panel ON
							 //    77 = Magic Panel OFF
							 //    78 = Magic Panel Flicker (10 seconds) 
							 //
							 // Std MarcDuino Logic Display Functions (For custom functions)
							 //     1 = Display normal random sequence
							 //     2 = Short circuit (10 second display sequence)
							 //     3 = Scream (flashing light display sequence)
							 //     4 = Leia (34 second light sequence)
							 //     5 = Display “Star Wars”
							 //     6 = March light sequence
							 //     7 = Spectrum, bar graph display sequence
							 //     8 = Display custom text
							 //
							 // Std MarcDuino Panel Functions (For custom functions)
							 //     1 = Panels stay closed (normal position)
							 //     2 = Scream sequence, all panels open
							 //     3 = Wave panel sequence
							 //     4 = Fast (smirk) back and forth panel sequence
							 //     5 = Wave 2 panel sequence, open progressively all panels, then close one by one)
							 //     6 = Marching ants panel sequence
							 //     7 = Faint / short circuit panel sequence
							 //     8 = Rhythmic cantina panel sequence
							 //     9 = Custom Panel Sequence


							 //----------------------------------------------------
							 // CONFIGURE: The FOOT Navigation Controller Buttons
							 //----------------------------------------------------

							 //---------------------------------
							 // CONFIGURE: Arrow Up
							 //---------------------------------
							 //1 = Std MarcDuino Function, 2 = Custom Function
int btnUP_type = 1;

// IF Std MarcDuino Function (type=1) 
// Enter MarcDuino Function Code (1 - 78) (See Above)
int btnUP_MD_func = 12;

// IF Custom Function (type=2)
// CUSTOM SOUND SETTING: Enter the file # prefix on the MP3 trigger card of the sound to play (0 = NO SOUND)
// Valid values: 0 or 182 - 200  
int btnUP_cust_MP3_num = 0;

// CUSTOM LOGIC DISPLAY SETTING: Pick from the Std MD Logic Display Functions (See Above)
// Valid values: 0, 1 to 8  (0 - Not used)
int btnUP_cust_LD_type = 0;

// IF Custom Logic Display = 8 (custom text), enter custom display text here
String btnUP_cust_LD_text = "";

// CUSTOM PANEL SETTING: Pick from the Std MD Panel Functions or Custom (See Above)
// Valid Values: 0, 1 to 9 (0 = Not used)
int btnUP_cust_panel = 0;

// IF Custom Panel Setting = 9 (custom panel sequence)
// Dome Panel #1
boolean btnUP_use_DP1 = false;
int btnUP_DP1_open_start_delay = 1; // in seconds (0 to 30)
int btnUP_DP1_stay_open_time = 5; // in seconds (1 to 30)
								  // Dome Panel #2
boolean btnUP_use_DP2 = false;
int btnUP_DP2_open_start_delay = 1; // in seconds (0 to 30)
int btnUP_DP2_stay_open_time = 5; // in seconds (1 to 30)
								  // Dome Panel #3
boolean btnUP_use_DP3 = false;
int btnUP_DP3_open_start_delay = 1; // in seconds (0 to 30)
int btnUP_DP3_stay_open_time = 5; // in seconds (1 to 30)
								  // Dome Panel #4
boolean btnUP_use_DP4 = false;
int btnUP_DP4_open_start_delay = 1; // in seconds (0 to 30)
int btnUP_DP4_stay_open_time = 5; // in seconds (1 to 30)
								  // Dome Panel #5
boolean btnUP_use_DP5 = false;
int btnUP_DP5_open_start_delay = 1; // in seconds (0 to 30)
int btnUP_DP5_stay_open_time = 5; // in seconds (1 to 30)
								  // Dome Panel #6
boolean btnUP_use_DP6 = false;
int btnUP_DP6_open_start_delay = 1; // in seconds (0 to 30)
int btnUP_DP6_stay_open_time = 5; // in seconds (1 to 30)
								  // Dome Panel #7
boolean btnUP_use_DP7 = false;
int btnUP_DP7_open_start_delay = 1; // in seconds (0 to 30)
int btnUP_DP7_stay_open_time = 5; // in seconds (1 to 30)
								  // Dome Panel #8
boolean btnUP_use_DP8 = false;
int btnUP_DP8_open_start_delay = 1; // in seconds (0 to 30)
int btnUP_DP8_stay_open_time = 5; // in seconds (1 to 30)
								  // Dome Panel #9
boolean btnUP_use_DP9 = false;
int btnUP_DP9_open_start_delay = 1; // in seconds (0 to 30)
int btnUP_DP9_stay_open_time = 5; // in seconds (1 to 30)
								  // Dome Panel #10
boolean btnUP_use_DP10 = false;
int btnUP_DP10_open_start_delay = 1; // in seconds (0 to 30)
int btnUP_DP10_stay_open_time = 5; // in seconds (1 to 30)

								   //---------------------------------
								   // CONFIGURE: Arrow Left
								   //---------------------------------
								   //1 = Std MarcDuino Function, 2 = Custom Function
int btnLeft_type = 1;

// IF Std MarcDuino Function (type=1) 
// Enter MarcDuino Function Code (1 - 78) (See Above)
int btnLeft_MD_func = 13;

// IF Custom Function (type=2)
// CUSTOM SOUND SETTING: Enter the file # prefix on the MP3 trigger card of the sound to play (0 = NO SOUND)
// Valid values: 0 or 182 - 200  
int btnLeft_cust_MP3_num = 0;

// CUSTOM LOGIC DISPLAY SETTING: Pick from the Std MD Logic Display Functions (See Above)
// Valid values: 0, 1 to 8  (0 - Not used)
int btnLeft_cust_LD_type = 0;

// IF Custom Logic Display = 8 (custom text), enter custom display text here
String btnLeft_cust_LD_text = "";

// CUSTOM PANEL SETTING: Pick from the Std MD Panel Functions or Custom (See Above)
// Valid Values: 0, 1 to 9 (0 = Not used)
int btnLeft_cust_panel = 0;

// IF Custom Panel Setting = 9 (custom panel sequence)
// Dome Panel #1
boolean btnLeft_use_DP1 = false;
int btnLeft_DP1_open_start_delay = 1; // in seconds (0 to 30)
int btnLeft_DP1_stay_open_time = 5; // in seconds (1 to 30)
									// Dome Panel #2
boolean btnLeft_use_DP2 = false;
int btnLeft_DP2_open_start_delay = 1; // in seconds (0 to 30)
int btnLeft_DP2_stay_open_time = 5; // in seconds (1 to 30)
									// Dome Panel #3
boolean btnLeft_use_DP3 = false;
int btnLeft_DP3_open_start_delay = 1; // in seconds (0 to 30)
int btnLeft_DP3_stay_open_time = 5; // in seconds (1 to 30)
									// Dome Panel #4
boolean btnLeft_use_DP4 = false;
int btnLeft_DP4_open_start_delay = 1; // in seconds (0 to 30)
int btnLeft_DP4_stay_open_time = 5; // in seconds (1 to 30)
									// Dome Panel #5
boolean btnLeft_use_DP5 = false;
int btnLeft_DP5_open_start_delay = 1; // in seconds (0 to 30)
int btnLeft_DP5_stay_open_time = 5; // in seconds (1 to 30)
									// Dome Panel #6
boolean btnLeft_use_DP6 = false;
int btnLeft_DP6_open_start_delay = 1; // in seconds (0 to 30)
int btnLeft_DP6_stay_open_time = 5; // in seconds (1 to 30)
									// Dome Panel #7
boolean btnLeft_use_DP7 = false;
int btnLeft_DP7_open_start_delay = 1; // in seconds (0 to 30)
int btnLeft_DP7_stay_open_time = 5; // in seconds (1 to 30)
									// Dome Panel #8
boolean btnLeft_use_DP8 = false;
int btnLeft_DP8_open_start_delay = 1; // in seconds (0 to 30)
int btnLeft_DP8_stay_open_time = 5; // in seconds (1 to 30)
									// Dome Panel #9
boolean btnLeft_use_DP9 = false;
int btnLeft_DP9_open_start_delay = 1; // in seconds (0 to 30)
int btnLeft_DP9_stay_open_time = 5; // in seconds (1 to 30)
									// Dome Panel #10
boolean btnLeft_use_DP10 = false;
int btnLeft_DP10_open_start_delay = 1; // in seconds (0 to 30)
int btnLeft_DP10_stay_open_time = 5; // in seconds (1 to 30)

									 //---------------------------------
									 // CONFIGURE: Arrow Right
									 //---------------------------------
									 //1 = Std MarcDuino Function, 2 = Custom Function
int btnRight_type = 1;

// IF Std MarcDuino Function (type=1) 
// Enter MarcDuino Function Code (1 - 78) (See Above)
int btnRight_MD_func = 14;

// IF Custom Function (type=2)
// CUSTOM SOUND SETTING: Enter the file # prefix on the MP3 trigger card of the sound to play (0 = NO SOUND)
// Valid values: 0 or 182 - 200  
int btnRight_cust_MP3_num = 0;

// CUSTOM LOGIC DISPLAY SETTING: Pick from the Std MD Logic Display Functions (See Above)
// Valid values: 0, 1 to 8  (0 - Not used)
int btnRight_cust_LD_type = 0;

// IF Custom Logic Display = 8 (custom text), enter custom display text here
String btnRight_cust_LD_text = "";

// CUSTOM PANEL SETTING: Pick from the Std MD Panel Functions or Custom (See Above)
// Valid Values: 0, 1 to 9 (0 = Not used)
int btnRight_cust_panel = 0;

// IF Custom Panel Setting = 9 (custom panel sequence)
// Dome Panel #1
boolean btnRight_use_DP1 = false;
int btnRight_DP1_open_start_delay = 1; // in seconds (0 to 30)
int btnRight_DP1_stay_open_time = 5; // in seconds (1 to 30)
									 // Dome Panel #2
boolean btnRight_use_DP2 = false;
int btnRight_DP2_open_start_delay = 1; // in seconds (0 to 30)
int btnRight_DP2_stay_open_time = 5; // in seconds (1 to 30)
									 // Dome Panel #3
boolean btnRight_use_DP3 = false;
int btnRight_DP3_open_start_delay = 1; // in seconds (0 to 30)
int btnRight_DP3_stay_open_time = 5; // in seconds (1 to 30)
									 // Dome Panel #4
boolean btnRight_use_DP4 = false;
int btnRight_DP4_open_start_delay = 1; // in seconds (0 to 30)
int btnRight_DP4_stay_open_time = 5; // in seconds (1 to 30)
									 // Dome Panel #5
boolean btnRight_use_DP5 = false;
int btnRight_DP5_open_start_delay = 1; // in seconds (0 to 30)
int btnRight_DP5_stay_open_time = 5; // in seconds (1 to 30)
									 // Dome Panel #6
boolean btnRight_use_DP6 = false;
int btnRight_DP6_open_start_delay = 1; // in seconds (0 to 30)
int btnRight_DP6_stay_open_time = 5; // in seconds (1 to 30)
									 // Dome Panel #7
boolean btnRight_use_DP7 = false;
int btnRight_DP7_open_start_delay = 1; // in seconds (0 to 30)
int btnRight_DP7_stay_open_time = 5; // in seconds (1 to 30)
									 // Dome Panel #8
boolean btnRight_use_DP8 = false;
int btnRight_DP8_open_start_delay = 1; // in seconds (0 to 30)
int btnRight_DP8_stay_open_time = 5; // in seconds (1 to 30)
									 // Dome Panel #9
boolean btnRight_use_DP9 = false;
int btnRight_DP9_open_start_delay = 1; // in seconds (0 to 30)
int btnRight_DP9_stay_open_time = 5; // in seconds (1 to 30)
									 // Dome Panel #10
boolean btnRight_use_DP10 = false;
int btnRight_DP10_open_start_delay = 1; // in seconds (0 to 30)
int btnRight_DP10_stay_open_time = 5; // in seconds (1 to 30)

									  //---------------------------------
									  // CONFIGURE: Arrow Down
									  //---------------------------------
									  //1 = Std MarcDuino Function, 2 = Custom Function
int btnDown_type = 1;

// IF Std MarcDuino Function (type=1) 
// Enter MarcDuino Function Code (1 - 78) (See Above)
int btnDown_MD_func = 11;

// IF Custom Function (type=2)
// CUSTOM SOUND SETTING: Enter the file # prefix on the MP3 trigger card of the sound to play (0 = NO SOUND)
// Valid values: 0 or 182 - 200  
int btnDown_cust_MP3_num = 0;

// CUSTOM LOGIC DISPLAY SETTING: Pick from the Std MD Logic Display Functions (See Above)
// Valid values: 0, 1 to 8  (0 - Not used)
int btnDown_cust_LD_type = 0;

// IF Custom Logic Display = 8 (custom text), enter custom display text here
String btnDown_cust_LD_text = "";

// CUSTOM PANEL SETTING: Pick from the Std MD Panel Functions or Custom (See Above)
// Valid Values: 0, 1 to 9 (0 = Not used)
int btnDown_cust_panel = 0;

// IF Custom Panel Setting = 9 (custom panel sequence)
// Dome Panel #1
boolean btnDown_use_DP1 = false;
int btnDown_DP1_open_start_delay = 1; // in seconds (0 to 30)
int btnDown_DP1_stay_open_time = 5; // in seconds (1 to 30)
									// Dome Panel #2
boolean btnDown_use_DP2 = false;
int btnDown_DP2_open_start_delay = 1; // in seconds (0 to 30)
int btnDown_DP2_stay_open_time = 5; // in seconds (1 to 30)
									// Dome Panel #3
boolean btnDown_use_DP3 = false;
int btnDown_DP3_open_start_delay = 1; // in seconds (0 to 30)
int btnDown_DP3_stay_open_time = 5; // in seconds (1 to 30)
									// Dome Panel #4
boolean btnDown_use_DP4 = false;
int btnDown_DP4_open_start_delay = 1; // in seconds (0 to 30)
int btnDown_DP4_stay_open_time = 5; // in seconds (1 to 30)
									// Dome Panel #5
boolean btnDown_use_DP5 = false;
int btnDown_DP5_open_start_delay = 1; // in seconds (0 to 30)
int btnDown_DP5_stay_open_time = 5; // in seconds (1 to 30)
									// Dome Panel #6
boolean btnDown_use_DP6 = false;
int btnDown_DP6_open_start_delay = 1; // in seconds (0 to 30)
int btnDown_DP6_stay_open_time = 5; // in seconds (1 to 30)
									// Dome Panel #7
boolean btnDown_use_DP7 = false;
int btnDown_DP7_open_start_delay = 1; // in seconds (0 to 30)
int btnDown_DP7_stay_open_time = 5; // in seconds (1 to 30)
									// Dome Panel #8
boolean btnDown_use_DP8 = false;
int btnDown_DP8_open_start_delay = 1; // in seconds (0 to 30)
int btnDown_DP8_stay_open_time = 5; // in seconds (1 to 30)
									// Dome Panel #9
boolean btnDown_use_DP9 = false;
int btnDown_DP9_open_start_delay = 1; // in seconds (0 to 30)
int btnDown_DP9_stay_open_time = 5; // in seconds (1 to 30)
									// Dome Panel #10
boolean btnDown_use_DP10 = false;
int btnDown_DP10_open_start_delay = 1; // in seconds (0 to 30)
int btnDown_DP10_stay_open_time = 5; // in seconds (1 to 30)

									 //---------------------------------
									 // CONFIGURE: Arrow UP + CROSS
									 //---------------------------------
									 //1 = Std MarcDuino Function, 2 = Custom Function
int btnUP_CROSS_type = 1;

// IF Std MarcDuino Function (type=1) 
// Enter MarcDuino Function Code (1 - 78) (See Above)
int btnUP_CROSS_MD_func = 26;

// IF Custom Function (type=2)
// CUSTOM SOUND SETTING: Enter the file # prefix on the MP3 trigger card of the sound to play (0 = NO SOUND)
// Valid values: 0 or 182 - 200  
int btnUP_CROSS_cust_MP3_num = 0;

// CUSTOM LOGIC DISPLAY SETTING: Pick from the Std MD Logic Display Functions (See Above)
// Valid values: 0, 1 to 8  (0 - Not used)
int btnUP_CROSS_cust_LD_type = 0;

// IF Custom Logic Display = 8 (custom text), enter custom display text here
String btnUP_CROSS_cust_LD_text = "";

// CUSTOM PANEL SETTING: Pick from the Std MD Panel Functions or Custom (See Above)
// Valid Values: 0, 1 to 9 (0 = Not used)
int btnUP_CROSS_cust_panel = 0;

// IF Custom Panel Setting = 9 (custom panel sequence)
// Dome Panel #1
boolean btnUP_CROSS_use_DP1 = false;
int btnUP_CROSS_DP1_open_start_delay = 1; // in seconds (0 to 30)
int btnUP_CROSS_DP1_stay_open_time = 5; // in seconds (1 to 30)
										// Dome Panel #2
boolean btnUP_CROSS_use_DP2 = false;
int btnUP_CROSS_DP2_open_start_delay = 1; // in seconds (0 to 30)
int btnUP_CROSS_DP2_stay_open_time = 5; // in seconds (1 to 30)
										// Dome Panel #3
boolean btnUP_CROSS_use_DP3 = false;
int btnUP_CROSS_DP3_open_start_delay = 1; // in seconds (0 to 30)
int btnUP_CROSS_DP3_stay_open_time = 5; // in seconds (1 to 30)
										// Dome Panel #4
boolean btnUP_CROSS_use_DP4 = false;
int btnUP_CROSS_DP4_open_start_delay = 1; // in seconds (0 to 30)
int btnUP_CROSS_DP4_stay_open_time = 5; // in seconds (1 to 30)
										// Dome Panel #5
boolean btnUP_CROSS_use_DP5 = false;
int btnUP_CROSS_DP5_open_start_delay = 1; // in seconds (0 to 30)
int btnUP_CROSS_DP5_stay_open_time = 5; // in seconds (1 to 30)
										// Dome Panel #6
boolean btnUP_CROSS_use_DP6 = false;
int btnUP_CROSS_DP6_open_start_delay = 1; // in seconds (0 to 30)
int btnUP_CROSS_DP6_stay_open_time = 5; // in seconds (1 to 30)
										// Dome Panel #7
boolean btnUP_CROSS_use_DP7 = false;
int btnUP_CROSS_DP7_open_start_delay = 1; // in seconds (0 to 30)
int btnUP_CROSS_DP7_stay_open_time = 5; // in seconds (1 to 30)
										// Dome Panel #8
boolean btnUP_CROSS_use_DP8 = false;
int btnUP_CROSS_DP8_open_start_delay = 1; // in seconds (0 to 30)
int btnUP_CROSS_DP8_stay_open_time = 5; // in seconds (1 to 30)
										// Dome Panel #9
boolean btnUP_CROSS_use_DP9 = false;
int btnUP_CROSS_DP9_open_start_delay = 1; // in seconds (0 to 30)
int btnUP_CROSS_DP9_stay_open_time = 5; // in seconds (1 to 30)
										// Dome Panel #10
boolean btnUP_CROSS_use_DP10 = false;
int btnUP_CROSS_DP10_open_start_delay = 1; // in seconds (0 to 30)
int btnUP_CROSS_DP10_stay_open_time = 5; // in seconds (1 to 30)

										 //---------------------------------
										 // CONFIGURE: Arrow Left + CROSS
										 //---------------------------------
										 //1 = Std MarcDuino Function, 2 = Custom Function
int btnLeft_CROSS_type = 1;

// IF Std MarcDuino Function (type=1) 
// Enter MarcDuino Function Code (1 - 78) (See Above)
int btnLeft_CROSS_MD_func = 23;

// IF Custom Function (type=2)
// CUSTOM SOUND SETTING: Enter the file # prefix on the MP3 trigger card of the sound to play (0 = NO SOUND)
// Valid values: 0 or 182 - 200  
int btnLeft_CROSS_cust_MP3_num = 0;

// CUSTOM LOGIC DISPLAY SETTING: Pick from the Std MD Logic Display Functions (See Above)
// Valid values: 0, 1 to 8  (0 - Not used)
int btnLeft_CROSS_cust_LD_type = 0;

// IF Custom Logic Display = 8 (custom text), enter custom display text here
String btnLeft_CROSS_cust_LD_text = "";

// CUSTOM PANEL SETTING: Pick from the Std MD Panel Functions or Custom (See Above)
// Valid Values: 0, 1 to 9 (0 = Not used)
int btnLeft_CROSS_cust_panel = 0;

// IF Custom Panel Setting = 9 (custom panel sequence)
// Dome Panel #1
boolean btnLeft_CROSS_use_DP1 = false;
int btnLeft_CROSS_DP1_open_start_delay = 1; // in seconds (0 to 30)
int btnLeft_CROSS_DP1_stay_open_time = 5; // in seconds (1 to 30)
										  // Dome Panel #2
boolean btnLeft_CROSS_use_DP2 = false;
int btnLeft_CROSS_DP2_open_start_delay = 1; // in seconds (0 to 30)
int btnLeft_CROSS_DP2_stay_open_time = 5; // in seconds (1 to 30)
										  // Dome Panel #3
boolean btnLeft_CROSS_use_DP3 = false;
int btnLeft_CROSS_DP3_open_start_delay = 1; // in seconds (0 to 30)
int btnLeft_CROSS_DP3_stay_open_time = 5; // in seconds (1 to 30)
										  // Dome Panel #4
boolean btnLeft_CROSS_use_DP4 = false;
int btnLeft_CROSS_DP4_open_start_delay = 1; // in seconds (0 to 30)
int btnLeft_CROSS_DP4_stay_open_time = 5; // in seconds (1 to 30)
										  // Dome Panel #5
boolean btnLeft_CROSS_use_DP5 = false;
int btnLeft_CROSS_DP5_open_start_delay = 1; // in seconds (0 to 30)
int btnLeft_CROSS_DP5_stay_open_time = 5; // in seconds (1 to 30)
										  // Dome Panel #6
boolean btnLeft_CROSS_use_DP6 = false;
int btnLeft_CROSS_DP6_open_start_delay = 1; // in seconds (0 to 30)
int btnLeft_CROSS_DP6_stay_open_time = 5; // in seconds (1 to 30)
										  // Dome Panel #7
boolean btnLeft_CROSS_use_DP7 = false;
int btnLeft_CROSS_DP7_open_start_delay = 1; // in seconds (0 to 30)
int btnLeft_CROSS_DP7_stay_open_time = 5; // in seconds (1 to 30)
										  // Dome Panel #8
boolean btnLeft_CROSS_use_DP8 = false;
int btnLeft_CROSS_DP8_open_start_delay = 1; // in seconds (0 to 30)
int btnLeft_CROSS_DP8_stay_open_time = 5; // in seconds (1 to 30)
										  // Dome Panel #9
boolean btnLeft_CROSS_use_DP9 = false;
int btnLeft_CROSS_DP9_open_start_delay = 1; // in seconds (0 to 30)
int btnLeft_CROSS_DP9_stay_open_time = 5; // in seconds (1 to 30)
										  // Dome Panel #10
boolean btnLeft_CROSS_use_DP10 = false;
int btnLeft_CROSS_DP10_open_start_delay = 1; // in seconds (0 to 30)
int btnLeft_CROSS_DP10_stay_open_time = 5; // in seconds (1 to 30)

										   //---------------------------------
										   // CONFIGURE: Arrow Right + CROSS
										   //---------------------------------
										   //1 = Std MarcDuino Function, 2 = Custom Function
int btnRight_CROSS_type = 1;

// IF Std MarcDuino Function (type=1) 
// Enter MarcDuino Function Code (1 - 78) (See Above)
int btnRight_CROSS_MD_func = 24;

// IF Custom Function (type=2)
// CUSTOM SOUND SETTING: Enter the file # prefix on the MP3 trigger card of the sound to play (0 = NO SOUND)
// Valid values: 0 or 182 - 200  
int btnRight_CROSS_cust_MP3_num = 0;

// CUSTOM LOGIC DISPLAY SETTING: Pick from the Std MD Logic Display Functions (See Above)
// Valid values: 0, 1 to 8  (0 - Not used)
int btnRight_CROSS_cust_LD_type = 0;

// IF Custom Logic Display = 8 (custom text), enter custom display text here
String btnRight_CROSS_cust_LD_text = "";

// CUSTOM PANEL SETTING: Pick from the Std MD Panel Functions or Custom (See Above)
// Valid Values: 0, 1 to 9 (0 = Not used)
int btnRight_CROSS_cust_panel = 0;

// IF Custom Panel Setting = 9 (custom panel sequence)
// Dome Panel #1
boolean btnRight_CROSS_use_DP1 = false;
int btnRight_CROSS_DP1_open_start_delay = 1; // in seconds (0 to 30)
int btnRight_CROSS_DP1_stay_open_time = 5; // in seconds (1 to 30)
										   // Dome Panel #2
boolean btnRight_CROSS_use_DP2 = false;
int btnRight_CROSS_DP2_open_start_delay = 1; // in seconds (0 to 30)
int btnRight_CROSS_DP2_stay_open_time = 5; // in seconds (1 to 30)
										   // Dome Panel #3
boolean btnRight_CROSS_use_DP3 = false;
int btnRight_CROSS_DP3_open_start_delay = 1; // in seconds (0 to 30)
int btnRight_CROSS_DP3_stay_open_time = 5; // in seconds (1 to 30)
										   // Dome Panel #4
boolean btnRight_CROSS_use_DP4 = false;
int btnRight_CROSS_DP4_open_start_delay = 1; // in seconds (0 to 30)
int btnRight_CROSS_DP4_stay_open_time = 5; // in seconds (1 to 30)
										   // Dome Panel #5
boolean btnRight_CROSS_use_DP5 = false;
int btnRight_CROSS_DP5_open_start_delay = 1; // in seconds (0 to 30)
int btnRight_CROSS_DP5_stay_open_time = 5; // in seconds (1 to 30)
										   // Dome Panel #6
boolean btnRight_CROSS_use_DP6 = false;
int btnRight_CROSS_DP6_open_start_delay = 1; // in seconds (0 to 30)
int btnRight_CROSS_DP6_stay_open_time = 5; // in seconds (1 to 30)
										   // Dome Panel #7
boolean btnRight_CROSS_use_DP7 = false;
int btnRight_CROSS_DP7_open_start_delay = 1; // in seconds (0 to 30)
int btnRight_CROSS_DP7_stay_open_time = 5; // in seconds (1 to 30)
										   // Dome Panel #8
boolean btnRight_CROSS_use_DP8 = false;
int btnRight_CROSS_DP8_open_start_delay = 1; // in seconds (0 to 30)
int btnRight_CROSS_DP8_stay_open_time = 5; // in seconds (1 to 30)
										   // Dome Panel #9
boolean btnRight_CROSS_use_DP9 = false;
int btnRight_CROSS_DP9_open_start_delay = 1; // in seconds (0 to 30)
int btnRight_CROSS_DP9_stay_open_time = 5; // in seconds (1 to 30)
										   // Dome Panel #10
boolean btnRight_CROSS_use_DP10 = false;
int btnRight_CROSS_DP10_open_start_delay = 1; // in seconds (0 to 30)
int btnRight_CROSS_DP10_stay_open_time = 5; // in seconds (1 to 30)

											//---------------------------------
											// CONFIGURE: Arrow Down + CROSS
											//---------------------------------
											//1 = Std MarcDuino Function, 2 = Custom Function
int btnDown_CROSS_type = 1;

// IF Std MarcDuino Function (type=1) 
// Enter MarcDuino Function Code (1 - 78) (See Above)
int btnDown_CROSS_MD_func = 27;

// IF Custom Function (type=2)
// CUSTOM SOUND SETTING: Enter the file # prefix on the MP3 trigger card of the sound to play (0 = NO SOUND)
// Valid values: 0 or 182 - 200  
int btnDown_CROSS_cust_MP3_num = 0;

// CUSTOM LOGIC DISPLAY SETTING: Pick from the Std MD Logic Display Functions (See Above)
// Valid values: 0, 1 to 8  (0 - Not used)
int btnDown_CROSS_cust_LD_type = 0;

// IF Custom Logic Display = 8 (custom text), enter custom display text here
String btnDown_CROSS_cust_LD_text = "";

// CUSTOM PANEL SETTING: Pick from the Std MD Panel Functions or Custom (See Above)
// Valid Values: 0, 1 to 9 (0 = Not used)
int btnDown_CROSS_cust_panel = 0;

// IF Custom Panel Setting = 9 (custom panel sequence)
// Dome Panel #1
boolean btnDown_CROSS_use_DP1 = false;
int btnDown_CROSS_DP1_open_start_delay = 1; // in seconds (0 to 30)
int btnDown_CROSS_DP1_stay_open_time = 5; // in seconds (1 to 30)
										  // Dome Panel #2
boolean btnDown_CROSS_use_DP2 = false;
int btnDown_CROSS_DP2_open_start_delay = 1; // in seconds (0 to 30)
int btnDown_CROSS_DP2_stay_open_time = 5; // in seconds (1 to 30)
										  // Dome Panel #3
boolean btnDown_CROSS_use_DP3 = false;
int btnDown_CROSS_DP3_open_start_delay = 1; // in seconds (0 to 30)
int btnDown_CROSS_DP3_stay_open_time = 5; // in seconds (1 to 30)
										  // Dome Panel #4
boolean btnDown_CROSS_use_DP4 = false;
int btnDown_CROSS_DP4_open_start_delay = 1; // in seconds (0 to 30)
int btnDown_CROSS_DP4_stay_open_time = 5; // in seconds (1 to 30)
										  // Dome Panel #5
boolean btnDown_CROSS_use_DP5 = false;
int btnDown_CROSS_DP5_open_start_delay = 1; // in seconds (0 to 30)
int btnDown_CROSS_DP5_stay_open_time = 5; // in seconds (1 to 30)
										  // Dome Panel #6
boolean btnDown_CROSS_use_DP6 = false;
int btnDown_CROSS_DP6_open_start_delay = 1; // in seconds (0 to 30)
int btnDown_CROSS_DP6_stay_open_time = 5; // in seconds (1 to 30)
										  // Dome Panel #7
boolean btnDown_CROSS_use_DP7 = false;
int btnDown_CROSS_DP7_open_start_delay = 1; // in seconds (0 to 30)
int btnDown_CROSS_DP7_stay_open_time = 5; // in seconds (1 to 30)
										  // Dome Panel #8
boolean btnDown_CROSS_use_DP8 = false;
int btnDown_CROSS_DP8_open_start_delay = 1; // in seconds (0 to 30)
int btnDown_CROSS_DP8_stay_open_time = 5; // in seconds (1 to 30)
										  // Dome Panel #9
boolean btnDown_CROSS_use_DP9 = false;
int btnDown_CROSS_DP9_open_start_delay = 1; // in seconds (0 to 30)
int btnDown_CROSS_DP9_stay_open_time = 5; // in seconds (1 to 30)
										  // Dome Panel #10
boolean btnDown_CROSS_use_DP10 = false;
int btnDown_CROSS_DP10_open_start_delay = 1; // in seconds (0 to 30)
int btnDown_CROSS_DP10_stay_open_time = 5; // in seconds (1 to 30)

										   //---------------------------------
										   // CONFIGURE: Arrow UP + CIRCLE
										   //---------------------------------
										   //1 = Std MarcDuino Function, 2 = Custom Function
int btnUP_CIRCLE_type = 1;

// IF Std MarcDuino Function (type=1) 
// Enter MarcDuino Function Code (1 - 78) (See Above)
int btnUP_CIRCLE_MD_func = 2;

// IF Custom Function (type=2)
// CUSTOM SOUND SETTING: Enter the file # prefix on the MP3 trigger card of the sound to play (0 = NO SOUND)
// Valid values: 0 or 182 - 200  
int btnUP_CIRCLE_cust_MP3_num = 0;

// CUSTOM LOGIC DISPLAY SETTING: Pick from the Std MD Logic Display Functions (See Above)
// Valid values: 0, 1 to 8  (0 - Not used)
int btnUP_CIRCLE_cust_LD_type = 0;

// IF Custom Logic Display = 8 (custom text), enter custom display text here
String btnUP_CIRCLE_cust_LD_text = "";

// CUSTOM PANEL SETTING: Pick from the Std MD Panel Functions or Custom (See Above)
// Valid Values: 0, 1 to 9 (0 = Not used)
int btnUP_CIRCLE_cust_panel = 0;

// IF Custom Panel Setting = 9 (custom panel sequence)
// Dome Panel #1
boolean btnUP_CIRCLE_use_DP1 = false;
int btnUP_CIRCLE_DP1_open_start_delay = 1; // in seconds (0 to 30)
int btnUP_CIRCLE_DP1_stay_open_time = 5; // in seconds (1 to 30)
										 // Dome Panel #2
boolean btnUP_CIRCLE_use_DP2 = false;
int btnUP_CIRCLE_DP2_open_start_delay = 1; // in seconds (0 to 30)
int btnUP_CIRCLE_DP2_stay_open_time = 5; // in seconds (1 to 30)
										 // Dome Panel #3
boolean btnUP_CIRCLE_use_DP3 = false;
int btnUP_CIRCLE_DP3_open_start_delay = 1; // in seconds (0 to 30)
int btnUP_CIRCLE_DP3_stay_open_time = 5; // in seconds (1 to 30)
										 // Dome Panel #4
boolean btnUP_CIRCLE_use_DP4 = false;
int btnUP_CIRCLE_DP4_open_start_delay = 1; // in seconds (0 to 30)
int btnUP_CIRCLE_DP4_stay_open_time = 5; // in seconds (1 to 30)
										 // Dome Panel #5
boolean btnUP_CIRCLE_use_DP5 = false;
int btnUP_CIRCLE_DP5_open_start_delay = 1; // in seconds (0 to 30)
int btnUP_CIRCLE_DP5_stay_open_time = 5; // in seconds (1 to 30)
										 // Dome Panel #6
boolean btnUP_CIRCLE_use_DP6 = false;
int btnUP_CIRCLE_DP6_open_start_delay = 1; // in seconds (0 to 30)
int btnUP_CIRCLE_DP6_stay_open_time = 5; // in seconds (1 to 30)
										 // Dome Panel #7
boolean btnUP_CIRCLE_use_DP7 = false;
int btnUP_CIRCLE_DP7_open_start_delay = 1; // in seconds (0 to 30)
int btnUP_CIRCLE_DP7_stay_open_time = 5; // in seconds (1 to 30)
										 // Dome Panel #8
boolean btnUP_CIRCLE_use_DP8 = false;
int btnUP_CIRCLE_DP8_open_start_delay = 1; // in seconds (0 to 30)
int btnUP_CIRCLE_DP8_stay_open_time = 5; // in seconds (1 to 30)
										 // Dome Panel #9
boolean btnUP_CIRCLE_use_DP9 = false;
int btnUP_CIRCLE_DP9_open_start_delay = 1; // in seconds (0 to 30)
int btnUP_CIRCLE_DP9_stay_open_time = 5; // in seconds (1 to 30)
										 // Dome Panel #10
boolean btnUP_CIRCLE_use_DP10 = false;
int btnUP_CIRCLE_DP10_open_start_delay = 1; // in seconds (0 to 30)
int btnUP_CIRCLE_DP10_stay_open_time = 5; // in seconds (1 to 30)

										  //---------------------------------
										  // CONFIGURE: Arrow Left + CIRCLE
										  //---------------------------------
										  //1 = Std MarcDuino Function, 2 = Custom Function
int btnLeft_CIRCLE_type = 1;

// IF Std MarcDuino Function (type=1) 
// Enter MarcDuino Function Code (1 - 78) (See Above)
int btnLeft_CIRCLE_MD_func = 4;

// IF Custom Function (type=2)
// CUSTOM SOUND SETTING: Enter the file # prefix on the MP3 trigger card of the sound to play (0 = NO SOUND)
// Valid values: 0 or 182 - 200  
int btnLeft_CIRCLE_cust_MP3_num = 0;

// CUSTOM LOGIC DISPLAY SETTING: Pick from the Std MD Logic Display Functions (See Above)
// Valid values: 0, 1 to 8  (0 - Not used)
int btnLeft_CIRCLE_cust_LD_type = 0;

// IF Custom Logic Display = 8 (custom text), enter custom display text here
String btnLeft_CIRCLE_cust_LD_text = "";

// CUSTOM PANEL SETTING: Pick from the Std MD Panel Functions or Custom (See Above)
// Valid Values: 0, 1 to 9 (0 = Not used)
int btnLeft_CIRCLE_cust_panel = 0;

// IF Custom Panel Setting = 9 (custom panel sequence)
// Dome Panel #1
boolean btnLeft_CIRCLE_use_DP1 = false;
int btnLeft_CIRCLE_DP1_open_start_delay = 1; // in seconds (0 to 30)
int btnLeft_CIRCLE_DP1_stay_open_time = 5; // in seconds (1 to 30)
										   // Dome Panel #2
boolean btnLeft_CIRCLE_use_DP2 = false;
int btnLeft_CIRCLE_DP2_open_start_delay = 1; // in seconds (0 to 30)
int btnLeft_CIRCLE_DP2_stay_open_time = 5; // in seconds (1 to 30)
										   // Dome Panel #3
boolean btnLeft_CIRCLE_use_DP3 = false;
int btnLeft_CIRCLE_DP3_open_start_delay = 1; // in seconds (0 to 30)
int btnLeft_CIRCLE_DP3_stay_open_time = 5; // in seconds (1 to 30)
										   // Dome Panel #4
boolean btnLeft_CIRCLE_use_DP4 = false;
int btnLeft_CIRCLE_DP4_open_start_delay = 1; // in seconds (0 to 30)
int btnLeft_CIRCLE_DP4_stay_open_time = 5; // in seconds (1 to 30)
										   // Dome Panel #5
boolean btnLeft_CIRCLE_use_DP5 = false;
int btnLeft_CIRCLE_DP5_open_start_delay = 1; // in seconds (0 to 30)
int btnLeft_CIRCLE_DP5_stay_open_time = 5; // in seconds (1 to 30)
										   // Dome Panel #6
boolean btnLeft_CIRCLE_use_DP6 = false;
int btnLeft_CIRCLE_DP6_open_start_delay = 1; // in seconds (0 to 30)
int btnLeft_CIRCLE_DP6_stay_open_time = 5; // in seconds (1 to 30)
										   // Dome Panel #7
boolean btnLeft_CIRCLE_use_DP7 = false;
int btnLeft_CIRCLE_DP7_open_start_delay = 1; // in seconds (0 to 30)
int btnLeft_CIRCLE_DP7_stay_open_time = 5; // in seconds (1 to 30)
										   // Dome Panel #8
boolean btnLeft_CIRCLE_use_DP8 = false;
int btnLeft_CIRCLE_DP8_open_start_delay = 1; // in seconds (0 to 30)
int btnLeft_CIRCLE_DP8_stay_open_time = 5; // in seconds (1 to 30)
										   // Dome Panel #9
boolean btnLeft_CIRCLE_use_DP9 = false;
int btnLeft_CIRCLE_DP9_open_start_delay = 1; // in seconds (0 to 30)
int btnLeft_CIRCLE_DP9_stay_open_time = 5; // in seconds (1 to 30)
										   // Dome Panel #10
boolean btnLeft_CIRCLE_use_DP10 = false;
int btnLeft_CIRCLE_DP10_open_start_delay = 1; // in seconds (0 to 30)
int btnLeft_CIRCLE_DP10_stay_open_time = 5; // in seconds (1 to 30)

											//---------------------------------
											// CONFIGURE: Arrow Right + CIRCLE
											//---------------------------------
											//1 = Std MarcDuino Function, 2 = Custom Function
int btnRight_CIRCLE_type = 1;

// IF Std MarcDuino Function (type=1) 
// Enter MarcDuino Function Code (1 - 78) (See Above)
int btnRight_CIRCLE_MD_func = 7;

// IF Custom Function (type=2)
// CUSTOM SOUND SETTING: Enter the file # prefix on the MP3 trigger card of the sound to play (0 = NO SOUND)
// Valid values: 0 or 182 - 200  
int btnRight_CIRCLE_cust_MP3_num = 0;

// CUSTOM LOGIC DISPLAY SETTING: Pick from the Std MD Logic Display Functions (See Above)
// Valid values: 0, 1 to 8  (0 - Not used)
int btnRight_CIRCLE_cust_LD_type = 0;

// IF Custom Logic Display = 8 (custom text), enter custom display text here
String btnRight_CIRCLE_cust_LD_text = "";

// CUSTOM PANEL SETTING: Pick from the Std MD Panel Functions or Custom (See Above)
// Valid Values: 0, 1 to 9 (0 = Not used)
int btnRight_CIRCLE_cust_panel = 0;

// IF Custom Panel Setting = 9 (custom panel sequence)
// Dome Panel #1
boolean btnRight_CIRCLE_use_DP1 = false;
int btnRight_CIRCLE_DP1_open_start_delay = 1; // in seconds (0 to 30)
int btnRight_CIRCLE_DP1_stay_open_time = 5; // in seconds (1 to 30)
											// Dome Panel #2
boolean btnRight_CIRCLE_use_DP2 = false;
int btnRight_CIRCLE_DP2_open_start_delay = 1; // in seconds (0 to 30)
int btnRight_CIRCLE_DP2_stay_open_time = 5; // in seconds (1 to 30)
											// Dome Panel #3
boolean btnRight_CIRCLE_use_DP3 = false;
int btnRight_CIRCLE_DP3_open_start_delay = 1; // in seconds (0 to 30)
int btnRight_CIRCLE_DP3_stay_open_time = 5; // in seconds (1 to 30)
											// Dome Panel #4
boolean btnRight_CIRCLE_use_DP4 = false;
int btnRight_CIRCLE_DP4_open_start_delay = 1; // in seconds (0 to 30)
int btnRight_CIRCLE_DP4_stay_open_time = 5; // in seconds (1 to 30)
											// Dome Panel #5
boolean btnRight_CIRCLE_use_DP5 = false;
int btnRight_CIRCLE_DP5_open_start_delay = 1; // in seconds (0 to 30)
int btnRight_CIRCLE_DP5_stay_open_time = 5; // in seconds (1 to 30)
											// Dome Panel #6
boolean btnRight_CIRCLE_use_DP6 = false;
int btnRight_CIRCLE_DP6_open_start_delay = 1; // in seconds (0 to 30)
int btnRight_CIRCLE_DP6_stay_open_time = 5; // in seconds (1 to 30)
											// Dome Panel #7
boolean btnRight_CIRCLE_use_DP7 = false;
int btnRight_CIRCLE_DP7_open_start_delay = 1; // in seconds (0 to 30)
int btnRight_CIRCLE_DP7_stay_open_time = 5; // in seconds (1 to 30)
											// Dome Panel #8
boolean btnRight_CIRCLE_use_DP8 = false;
int btnRight_CIRCLE_DP8_open_start_delay = 1; // in seconds (0 to 30)
int btnRight_CIRCLE_DP8_stay_open_time = 5; // in seconds (1 to 30)
											// Dome Panel #9
boolean btnRight_CIRCLE_use_DP9 = false;
int btnRight_CIRCLE_DP9_open_start_delay = 1; // in seconds (0 to 30)
int btnRight_CIRCLE_DP9_stay_open_time = 5; // in seconds (1 to 30)
											// Dome Panel #10
boolean btnRight_CIRCLE_use_DP10 = false;
int btnRight_CIRCLE_DP10_open_start_delay = 1; // in seconds (0 to 30)
int btnRight_CIRCLE_DP10_stay_open_time = 5; // in seconds (1 to 30)

											 //---------------------------------
											 // CONFIGURE: Arrow Down + CIRCLE
											 //---------------------------------
											 //1 = Std MarcDuino Function, 2 = Custom Function
int btnDown_CIRCLE_type = 1;

// IF Std MarcDuino Function (type=1) 
// Enter MarcDuino Function Code (1 - 78) (See Above)
int btnDown_CIRCLE_MD_func = 10;

// IF Custom Function (type=2)
// CUSTOM SOUND SETTING: Enter the file # prefix on the MP3 trigger card of the sound to play (0 = NO SOUND)
// Valid values: 0 or 182 - 200  
int btnDown_CIRCLE_cust_MP3_num = 0;

// CUSTOM LOGIC DISPLAY SETTING: Pick from the Std MD Logic Display Functions (See Above)
// Valid values: 0, 1 to 8  (0 - Not used)
int btnDown_CIRCLE_cust_LD_type = 0;

// IF Custom Logic Display = 8 (custom text), enter custom display text here
String btnDown_CIRCLE_cust_LD_text = "";

// CUSTOM PANEL SETTING: Pick from the Std MD Panel Functions or Custom (See Above)
// Valid Values: 0, 1 to 9 (0 = Not used)
int btnDown_CIRCLE_cust_panel = 0;

// IF Custom Panel Setting = 9 (custom panel sequence)
// Dome Panel #1
boolean btnDown_CIRCLE_use_DP1 = false;
int btnDown_CIRCLE_DP1_open_start_delay = 1; // in seconds (0 to 30)
int btnDown_CIRCLE_DP1_stay_open_time = 5; // in seconds (1 to 30)
										   // Dome Panel #2
boolean btnDown_CIRCLE_use_DP2 = false;
int btnDown_CIRCLE_DP2_open_start_delay = 1; // in seconds (0 to 30)
int btnDown_CIRCLE_DP2_stay_open_time = 5; // in seconds (1 to 30)
										   // Dome Panel #3
boolean btnDown_CIRCLE_use_DP3 = false;
int btnDown_CIRCLE_DP3_open_start_delay = 1; // in seconds (0 to 30)
int btnDown_CIRCLE_DP3_stay_open_time = 5; // in seconds (1 to 30)
										   // Dome Panel #4
boolean btnDown_CIRCLE_use_DP4 = false;
int btnDown_CIRCLE_DP4_open_start_delay = 1; // in seconds (0 to 30)
int btnDown_CIRCLE_DP4_stay_open_time = 5; // in seconds (1 to 30)
										   // Dome Panel #5
boolean btnDown_CIRCLE_use_DP5 = false;
int btnDown_CIRCLE_DP5_open_start_delay = 1; // in seconds (0 to 30)
int btnDown_CIRCLE_DP5_stay_open_time = 5; // in seconds (1 to 30)
										   // Dome Panel #6
boolean btnDown_CIRCLE_use_DP6 = false;
int btnDown_CIRCLE_DP6_open_start_delay = 1; // in seconds (0 to 30)
int btnDown_CIRCLE_DP6_stay_open_time = 5; // in seconds (1 to 30)
										   // Dome Panel #7
boolean btnDown_CIRCLE_use_DP7 = false;
int btnDown_CIRCLE_DP7_open_start_delay = 1; // in seconds (0 to 30)
int btnDown_CIRCLE_DP7_stay_open_time = 5; // in seconds (1 to 30)
										   // Dome Panel #8
boolean btnDown_CIRCLE_use_DP8 = false;
int btnDown_CIRCLE_DP8_open_start_delay = 1; // in seconds (0 to 30)
int btnDown_CIRCLE_DP8_stay_open_time = 5; // in seconds (1 to 30)
										   // Dome Panel #9
boolean btnDown_CIRCLE_use_DP9 = false;
int btnDown_CIRCLE_DP9_open_start_delay = 1; // in seconds (0 to 30)
int btnDown_CIRCLE_DP9_stay_open_time = 5; // in seconds (1 to 30)
										   // Dome Panel #10
boolean btnDown_CIRCLE_use_DP10 = false;
int btnDown_CIRCLE_DP10_open_start_delay = 1; // in seconds (0 to 30)
int btnDown_CIRCLE_DP10_stay_open_time = 5; // in seconds (1 to 30)

											//---------------------------------
											// CONFIGURE: Arrow UP + PS
											//---------------------------------
											//1 = Std MarcDuino Function, 2 = Custom Function
int btnUP_PS_type = 2;

// IF Std MarcDuino Function (type=1) 
// Enter MarcDuino Function Code (1 - 78) (See Above)
int btnUP_PS_MD_func = 0;

// IF Custom Function (type=2)
// CUSTOM SOUND SETTING: Enter the file # prefix on the MP3 trigger card of the sound to play (0 = NO SOUND)
// Valid values: 0 or 182 - 200  
int btnUP_PS_cust_MP3_num = 183;

// CUSTOM LOGIC DISPLAY SETTING: Pick from the Std MD Logic Display Functions (See Above)
// Valid values: 0, 1 to 8  (0 - Not used)
int btnUP_PS_cust_LD_type = 5;

// IF Custom Logic Display = 8 (custom text), enter custom display text here
String btnUP_PS_cust_LD_text = "";

// CUSTOM PANEL SETTING: Pick from the Std MD Panel Functions or Custom (See Above)
// Valid Values: 0, 1 to 9 (0 = Not used)
int btnUP_PS_cust_panel = 0;

// IF Custom Panel Setting = 9 (custom panel sequence)
// Dome Panel #1
boolean btnUP_PS_use_DP1 = false;
int btnUP_PS_DP1_open_start_delay = 1; // in seconds (0 to 30)
int btnUP_PS_DP1_stay_open_time = 5; // in seconds (1 to 30)
									 // Dome Panel #2
boolean btnUP_PS_use_DP2 = false;
int btnUP_PS_DP2_open_start_delay = 1; // in seconds (0 to 30)
int btnUP_PS_DP2_stay_open_time = 5; // in seconds (1 to 30)
									 // Dome Panel #3
boolean btnUP_PS_use_DP3 = false;
int btnUP_PS_DP3_open_start_delay = 1; // in seconds (0 to 30)
int btnUP_PS_DP3_stay_open_time = 5; // in seconds (1 to 30)
									 // Dome Panel #4
boolean btnUP_PS_use_DP4 = false;
int btnUP_PS_DP4_open_start_delay = 1; // in seconds (0 to 30)
int btnUP_PS_DP4_stay_open_time = 5; // in seconds (1 to 30)
									 // Dome Panel #5
boolean btnUP_PS_use_DP5 = false;
int btnUP_PS_DP5_open_start_delay = 1; // in seconds (0 to 30)
int btnUP_PS_DP5_stay_open_time = 5; // in seconds (1 to 30)
									 // Dome Panel #6
boolean btnUP_PS_use_DP6 = false;
int btnUP_PS_DP6_open_start_delay = 1; // in seconds (0 to 30)
int btnUP_PS_DP6_stay_open_time = 5; // in seconds (1 to 30)
									 // Dome Panel #7
boolean btnUP_PS_use_DP7 = false;
int btnUP_PS_DP7_open_start_delay = 1; // in seconds (0 to 30)
int btnUP_PS_DP7_stay_open_time = 5; // in seconds (1 to 30)
									 // Dome Panel #8
boolean btnUP_PS_use_DP8 = false;
int btnUP_PS_DP8_open_start_delay = 1; // in seconds (0 to 30)
int btnUP_PS_DP8_stay_open_time = 5; // in seconds (1 to 30)
									 // Dome Panel #9
boolean btnUP_PS_use_DP9 = false;
int btnUP_PS_DP9_open_start_delay = 1; // in seconds (0 to 30)
int btnUP_PS_DP9_stay_open_time = 5; // in seconds (1 to 30)
									 // Dome Panel #10
boolean btnUP_PS_use_DP10 = false;
int btnUP_PS_DP10_open_start_delay = 1; // in seconds (0 to 30)
int btnUP_PS_DP10_stay_open_time = 5; // in seconds (1 to 30)

									  //---------------------------------
									  // CONFIGURE: Arrow Left + PS
									  //---------------------------------
									  //1 = Std MarcDuino Function, 2 = Custom Function
int btnLeft_PS_type = 2;

// IF Std MarcDuino Function (type=1) 
// Enter MarcDuino Function Code (1 - 78) (See Above)
int btnLeft_PS_MD_func = 0;

// IF Custom Function (type=2)
// CUSTOM SOUND SETTING: Enter the file # prefix on the MP3 trigger card of the sound to play (0 = NO SOUND)
// Valid values: 0 or 182 - 200  
int btnLeft_PS_cust_MP3_num = 186;

// CUSTOM LOGIC DISPLAY SETTING: Pick from the Std MD Logic Display Functions (See Above)
// Valid values: 0, 1 to 8  (0 - Not used)
int btnLeft_PS_cust_LD_type = 1;

// IF Custom Logic Display = 8 (custom text), enter custom display text here
String btnLeft_PS_cust_LD_text = "";

// CUSTOM PANEL SETTING: Pick from the Std MD Panel Functions or Custom (See Above)
// Valid Values: 0, 1 to 9 (0 = Not used)
int btnLeft_PS_cust_panel = 0;

// IF Custom Panel Setting = 9 (custom panel sequence)
// Dome Panel #1
boolean btnLeft_PS_use_DP1 = false;
int btnLeft_PS_DP1_open_start_delay = 1; // in seconds (0 to 30)
int btnLeft_PS_DP1_stay_open_time = 5; // in seconds (1 to 30)
									   // Dome Panel #2
boolean btnLeft_PS_use_DP2 = false;
int btnLeft_PS_DP2_open_start_delay = 1; // in seconds (0 to 30)
int btnLeft_PS_DP2_stay_open_time = 5; // in seconds (1 to 30)
									   // Dome Panel #3
boolean btnLeft_PS_use_DP3 = false;
int btnLeft_PS_DP3_open_start_delay = 1; // in seconds (0 to 30)
int btnLeft_PS_DP3_stay_open_time = 5; // in seconds (1 to 30)
									   // Dome Panel #4
boolean btnLeft_PS_use_DP4 = false;
int btnLeft_PS_DP4_open_start_delay = 1; // in seconds (0 to 30)
int btnLeft_PS_DP4_stay_open_time = 5; // in seconds (1 to 30)
									   // Dome Panel #5
boolean btnLeft_PS_use_DP5 = false;
int btnLeft_PS_DP5_open_start_delay = 1; // in seconds (0 to 30)
int btnLeft_PS_DP5_stay_open_time = 5; // in seconds (1 to 30)
									   // Dome Panel #6
boolean btnLeft_PS_use_DP6 = false;
int btnLeft_PS_DP6_open_start_delay = 1; // in seconds (0 to 30)
int btnLeft_PS_DP6_stay_open_time = 5; // in seconds (1 to 30)
									   // Dome Panel #7
boolean btnLeft_PS_use_DP7 = false;
int btnLeft_PS_DP7_open_start_delay = 1; // in seconds (0 to 30)
int btnLeft_PS_DP7_stay_open_time = 5; // in seconds (1 to 30)
									   // Dome Panel #8
boolean btnLeft_PS_use_DP8 = false;
int btnLeft_PS_DP8_open_start_delay = 1; // in seconds (0 to 30)
int btnLeft_PS_DP8_stay_open_time = 5; // in seconds (1 to 30)
									   // Dome Panel #9
boolean btnLeft_PS_use_DP9 = false;
int btnLeft_PS_DP9_open_start_delay = 1; // in seconds (0 to 30)
int btnLeft_PS_DP9_stay_open_time = 5; // in seconds (1 to 30)
									   // Dome Panel #10
boolean btnLeft_PS_use_DP10 = false;
int btnLeft_PS_DP10_open_start_delay = 1; // in seconds (0 to 30)
int btnLeft_PS_DP10_stay_open_time = 5; // in seconds (1 to 30)

										//---------------------------------
										// CONFIGURE: Arrow Right + PS
										//---------------------------------
										//1 = Std MarcDuino Function, 2 = Custom Function
int btnRight_PS_type = 2;

// IF Std MarcDuino Function (type=1) 
// Enter MarcDuino Function Code (1 - 78) (See Above)
int btnRight_PS_MD_func = 0;

// IF Custom Function (type=2)
// CUSTOM SOUND SETTING: Enter the file # prefix on the MP3 trigger card of the sound to play (0 = NO SOUND)
// Valid values: 0 or 182 - 200  
int btnRight_PS_cust_MP3_num = 185;

// CUSTOM LOGIC DISPLAY SETTING: Pick from the Std MD Logic Display Functions (See Above)
// Valid values: 0, 1 to 8  (0 - Not used)
int btnRight_PS_cust_LD_type = 1;

// IF Custom Logic Display = 8 (custom text), enter custom display text here
String btnRight_PS_cust_LD_text = "";

// CUSTOM PANEL SETTING: Pick from the Std MD Panel Functions or Custom (See Above)
// Valid Values: 0, 1 to 9 (0 = Not used)
int btnRight_PS_cust_panel = 0;

// IF Custom Panel Setting = 9 (custom panel sequence)
// Dome Panel #1
boolean btnRight_PS_use_DP1 = false;
int btnRight_PS_DP1_open_start_delay = 1; // in seconds (0 to 30)
int btnRight_PS_DP1_stay_open_time = 5; // in seconds (1 to 30)
										// Dome Panel #2
boolean btnRight_PS_use_DP2 = false;
int btnRight_PS_DP2_open_start_delay = 1; // in seconds (0 to 30)
int btnRight_PS_DP2_stay_open_time = 5; // in seconds (1 to 30)
										// Dome Panel #3
boolean btnRight_PS_use_DP3 = false;
int btnRight_PS_DP3_open_start_delay = 1; // in seconds (0 to 30)
int btnRight_PS_DP3_stay_open_time = 5; // in seconds (1 to 30)
										// Dome Panel #4
boolean btnRight_PS_use_DP4 = false;
int btnRight_PS_DP4_open_start_delay = 1; // in seconds (0 to 30)
int btnRight_PS_DP4_stay_open_time = 5; // in seconds (1 to 30)
										// Dome Panel #5
boolean btnRight_PS_use_DP5 = false;
int btnRight_PS_DP5_open_start_delay = 1; // in seconds (0 to 30)
int btnRight_PS_DP5_stay_open_time = 5; // in seconds (1 to 30)
										// Dome Panel #6
boolean btnRight_PS_use_DP6 = false;
int btnRight_PS_DP6_open_start_delay = 1; // in seconds (0 to 30)
int btnRight_PS_DP6_stay_open_time = 5; // in seconds (1 to 30)
										// Dome Panel #7
boolean btnRight_PS_use_DP7 = false;
int btnRight_PS_DP7_open_start_delay = 1; // in seconds (0 to 30)
int btnRight_PS_DP7_stay_open_time = 5; // in seconds (1 to 30)
										// Dome Panel #8
boolean btnRight_PS_use_DP8 = false;
int btnRight_PS_DP8_open_start_delay = 1; // in seconds (0 to 30)
int btnRight_PS_DP8_stay_open_time = 5; // in seconds (1 to 30)
										// Dome Panel #9
boolean btnRight_PS_use_DP9 = false;
int btnRight_PS_DP9_open_start_delay = 1; // in seconds (0 to 30)
int btnRight_PS_DP9_stay_open_time = 5; // in seconds (1 to 30)
										// Dome Panel #10
boolean btnRight_PS_use_DP10 = false;
int btnRight_PS_DP10_open_start_delay = 1; // in seconds (0 to 30)
int btnRight_PS_DP10_stay_open_time = 5; // in seconds (1 to 30)

										 //---------------------------------
										 // CONFIGURE: Arrow Down + PS
										 //---------------------------------
										 //1 = Std MarcDuino Function, 2 = Custom Function
int btnDown_PS_type = 2;

// IF Std MarcDuino Function (type=1) 
// Enter MarcDuino Function Code (1 - 78) (See Above)
int btnDown_PS_MD_func = 0;

// IF Custom Function (type=2)
// CUSTOM SOUND SETTING: Enter the file # prefix on the MP3 trigger card of the sound to play (0 = NO SOUND)
// Valid values: 0 or 182 - 200  
int btnDown_PS_cust_MP3_num = 184;

// CUSTOM LOGIC DISPLAY SETTING: Pick from the Std MD Logic Display Functions (See Above)
// Valid values: 0, 1 to 8  (0 - Not used)
int btnDown_PS_cust_LD_type = 1;

// IF Custom Logic Display = 8 (custom text), enter custom display text here
String btnDown_PS_cust_LD_text = "";

// CUSTOM PANEL SETTING: Pick from the Std MD Panel Functions or Custom (See Above)
// Valid Values: 0, 1 to 9 (0 = Not used)
int btnDown_PS_cust_panel = 0;

// IF Custom Panel Setting = 9 (custom panel sequence)
// Dome Panel #1
boolean btnDown_PS_use_DP1 = false;
int btnDown_PS_DP1_open_start_delay = 1; // in seconds (0 to 30)
int btnDown_PS_DP1_stay_open_time = 5; // in seconds (1 to 30)
									   // Dome Panel #2
boolean btnDown_PS_use_DP2 = false;
int btnDown_PS_DP2_open_start_delay = 1; // in seconds (0 to 30)
int btnDown_PS_DP2_stay_open_time = 5; // in seconds (1 to 30)
									   // Dome Panel #3
boolean btnDown_PS_use_DP3 = false;
int btnDown_PS_DP3_open_start_delay = 1; // in seconds (0 to 30)
int btnDown_PS_DP3_stay_open_time = 5; // in seconds (1 to 30)
									   // Dome Panel #4
boolean btnDown_PS_use_DP4 = false;
int btnDown_PS_DP4_open_start_delay = 1; // in seconds (0 to 30)
int btnDown_PS_DP4_stay_open_time = 5; // in seconds (1 to 30)
									   // Dome Panel #5
boolean btnDown_PS_use_DP5 = false;
int btnDown_PS_DP5_open_start_delay = 1; // in seconds (0 to 30)
int btnDown_PS_DP5_stay_open_time = 5; // in seconds (1 to 30)
									   // Dome Panel #6
boolean btnDown_PS_use_DP6 = false;
int btnDown_PS_DP6_open_start_delay = 1; // in seconds (0 to 30)
int btnDown_PS_DP6_stay_open_time = 5; // in seconds (1 to 30)
									   // Dome Panel #7
boolean btnDown_PS_use_DP7 = false;
int btnDown_PS_DP7_open_start_delay = 1; // in seconds (0 to 30)
int btnDown_PS_DP7_stay_open_time = 5; // in seconds (1 to 30)
									   // Dome Panel #8
boolean btnDown_PS_use_DP8 = false;
int btnDown_PS_DP8_open_start_delay = 1; // in seconds (0 to 30)
int btnDown_PS_DP8_stay_open_time = 5; // in seconds (1 to 30)
									   // Dome Panel #9
boolean btnDown_PS_use_DP9 = false;
int btnDown_PS_DP9_open_start_delay = 1; // in seconds (0 to 30)
int btnDown_PS_DP9_stay_open_time = 5; // in seconds (1 to 30)
									   // Dome Panel #10
boolean btnDown_PS_use_DP10 = false;
int btnDown_PS_DP10_open_start_delay = 1; // in seconds (0 to 30)
int btnDown_PS_DP10_stay_open_time = 5; // in seconds (1 to 30)

										//---------------------------------
										// CONFIGURE: Arrow Up + L1
										//---------------------------------
										//1 = Std MarcDuino Function, 2 = Custom Function
int btnUP_L1_type = 1;

// IF Std MarcDuino Function (type=1) 
// Enter MarcDuino Function Code (1 - 78) (See Above)
int btnUP_L1_MD_func = 8;

// IF Custom Function (type=2)
// CUSTOM SOUND SETTING: Enter the file # prefix on the MP3 trigger card of the sound to play (0 = NO SOUND)
// Valid values: 0 or 182 - 200  
int btnUP_L1_cust_MP3_num = 0;

// CUSTOM LOGIC DISPLAY SETTING: Pick from the Std MD Logic Display Functions (See Above)
// Valid values: 0, 1 to 8  (0 - Not used)
int btnUP_L1_cust_LD_type = 0;

// IF Custom Logic Display = 8 (custom text), enter custom display text here
String btnUP_L1_cust_LD_text = "";

// CUSTOM PANEL SETTING: Pick from the Std MD Panel Functions or Custom (See Above)
// Valid Values: 0, 1 to 9 (0 = Not used)
int btnUP_L1_cust_panel = 0;

// IF Custom Panel Setting = 9 (custom panel sequence)
// Dome Panel #1
boolean btnUP_L1_use_DP1 = false;
int btnUP_L1_DP1_open_start_delay = 1; // in seconds (0 to 30)
int btnUP_L1_DP1_stay_open_time = 5; // in seconds (1 to 30)
									 // Dome Panel #2
boolean btnUP_L1_use_DP2 = false;
int btnUP_L1_DP2_open_start_delay = 1; // in seconds (0 to 30)
int btnUP_L1_DP2_stay_open_time = 5; // in seconds (1 to 30)
									 // Dome Panel #3
boolean btnUP_L1_use_DP3 = false;
int btnUP_L1_DP3_open_start_delay = 1; // in seconds (0 to 30)
int btnUP_L1_DP3_stay_open_time = 5; // in seconds (1 to 30)
									 // Dome Panel #4
boolean btnUP_L1_use_DP4 = false;
int btnUP_L1_DP4_open_start_delay = 1; // in seconds (0 to 30)
int btnUP_L1_DP4_stay_open_time = 5; // in seconds (1 to 30)
									 // Dome Panel #5
boolean btnUP_L1_use_DP5 = false;
int btnUP_L1_DP5_open_start_delay = 1; // in seconds (0 to 30)
int btnUP_L1_DP5_stay_open_time = 5; // in seconds (1 to 30)
									 // Dome Panel #6
boolean btnUP_L1_use_DP6 = false;
int btnUP_L1_DP6_open_start_delay = 1; // in seconds (0 to 30)
int btnUP_L1_DP6_stay_open_time = 5; // in seconds (1 to 30)
									 // Dome Panel #7
boolean btnUP_L1_use_DP7 = false;
int btnUP_L1_DP7_open_start_delay = 1; // in seconds (0 to 30)
int btnUP_L1_DP7_stay_open_time = 5; // in seconds (1 to 30)
									 // Dome Panel #8
boolean btnUP_L1_use_DP8 = false;
int btnUP_L1_DP8_open_start_delay = 1; // in seconds (0 to 30)
int btnUP_L1_DP8_stay_open_time = 5; // in seconds (1 to 30)
									 // Dome Panel #9
boolean btnUP_L1_use_DP9 = false;
int btnUP_L1_DP9_open_start_delay = 1; // in seconds (0 to 30)
int btnUP_L1_DP9_stay_open_time = 5; // in seconds (1 to 30)
									 // Dome Panel #10
boolean btnUP_L1_use_DP10 = false;
int btnUP_L1_DP10_open_start_delay = 1; // in seconds (0 to 30)
int btnUP_L1_DP10_stay_open_time = 5; // in seconds (1 to 30)

									  //---------------------------------
									  // CONFIGURE: Arrow Left + L1
									  //---------------------------------
									  //1 = Std MarcDuino Function, 2 = Custom Function
int btnLeft_L1_type = 1;

// IF Std MarcDuino Function (type=1) 
// Enter MarcDuino Function Code (1 - 78) (See Above)
int btnLeft_L1_MD_func = 3;

// IF Custom Function (type=2)
// CUSTOM SOUND SETTING: Enter the file # prefix on the MP3 trigger card of the sound to play (0 = NO SOUND)
// Valid values: 0 or 182 - 200  
int btnLeft_L1_cust_MP3_num = 0;

// CUSTOM LOGIC DISPLAY SETTING: Pick from the Std MD Logic Display Functions (See Above)
// Valid values: 0, 1 to 8  (0 - Not used)
int btnLeft_L1_cust_LD_type = 0;

// IF Custom Logic Display = 8 (custom text), enter custom display text here
String btnLeft_L1_cust_LD_text = "";

// CUSTOM PANEL SETTING: Pick from the Std MD Panel Functions or Custom (See Above)
// Valid Values: 0, 1 to 9 (0 = Not used)
int btnLeft_L1_cust_panel = 0;

// IF Custom Panel Setting = 9 (custom panel sequence)
// Dome Panel #1
boolean btnLeft_L1_use_DP1 = false;
int btnLeft_L1_DP1_open_start_delay = 1; // in seconds (0 to 30)
int btnLeft_L1_DP1_stay_open_time = 5; // in seconds (1 to 30)
									   // Dome Panel #2
boolean btnLeft_L1_use_DP2 = false;
int btnLeft_L1_DP2_open_start_delay = 1; // in seconds (0 to 30)
int btnLeft_L1_DP2_stay_open_time = 5; // in seconds (1 to 30)
									   // Dome Panel #3
boolean btnLeft_L1_use_DP3 = false;
int btnLeft_L1_DP3_open_start_delay = 1; // in seconds (0 to 30)
int btnLeft_L1_DP3_stay_open_time = 5; // in seconds (1 to 30)
									   // Dome Panel #4
boolean btnLeft_L1_use_DP4 = false;
int btnLeft_L1_DP4_open_start_delay = 1; // in seconds (0 to 30)
int btnLeft_L1_DP4_stay_open_time = 5; // in seconds (1 to 30)
									   // Dome Panel #5
boolean btnLeft_L1_use_DP5 = false;
int btnLeft_L1_DP5_open_start_delay = 1; // in seconds (0 to 30)
int btnLeft_L1_DP5_stay_open_time = 5; // in seconds (1 to 30)
									   // Dome Panel #6
boolean btnLeft_L1_use_DP6 = false;
int btnLeft_L1_DP6_open_start_delay = 1; // in seconds (0 to 30)
int btnLeft_L1_DP6_stay_open_time = 5; // in seconds (1 to 30)
									   // Dome Panel #7
boolean btnLeft_L1_use_DP7 = false;
int btnLeft_L1_DP7_open_start_delay = 1; // in seconds (0 to 30)
int btnLeft_L1_DP7_stay_open_time = 5; // in seconds (1 to 30)
									   // Dome Panel #8
boolean btnLeft_L1_use_DP8 = false;
int btnLeft_L1_DP8_open_start_delay = 1; // in seconds (0 to 30)
int btnLeft_L1_DP8_stay_open_time = 5; // in seconds (1 to 30)
									   // Dome Panel #9
boolean btnLeft_L1_use_DP9 = false;
int btnLeft_L1_DP9_open_start_delay = 1; // in seconds (0 to 30)
int btnLeft_L1_DP9_stay_open_time = 5; // in seconds (1 to 30)
									   // Dome Panel #10
boolean btnLeft_L1_use_DP10 = false;
int btnLeft_L1_DP10_open_start_delay = 1; // in seconds (0 to 30)
int btnLeft_L1_DP10_stay_open_time = 5; // in seconds (1 to 30)

										//---------------------------------
										// CONFIGURE: Arrow Right + L1
										//---------------------------------
										//1 = Std MarcDuino Function, 2 = Custom Function
int btnRight_L1_type = 1;

// IF Std MarcDuino Function (type=1) 
// Enter MarcDuino Function Code (1 - 78) (See Above)
int btnRight_L1_MD_func = 5;

// IF Custom Function (type=2)
// CUSTOM SOUND SETTING: Enter the file # prefix on the MP3 trigger card of the sound to play (0 = NO SOUND)
// Valid values: 0 or 182 - 200  
int btnRight_L1_cust_MP3_num = 0;

// CUSTOM LOGIC DISPLAY SETTING: Pick from the Std MD Logic Display Functions (See Above)
// Valid values: 0, 1 to 8  (0 - Not used)
int btnRight_L1_cust_LD_type = 0;

// IF Custom Logic Display = 8 (custom text), enter custom display text here
String btnRight_L1_cust_LD_text = "";

// CUSTOM PANEL SETTING: Pick from the Std MD Panel Functions or Custom (See Above)
// Valid Values: 0, 1 to 9 (0 = Not used)
int btnRight_L1_cust_panel = 0;

// IF Custom Panel Setting = 9 (custom panel sequence)
// Dome Panel #1
boolean btnRight_L1_use_DP1 = false;
int btnRight_L1_DP1_open_start_delay = 1; // in seconds (0 to 30)
int btnRight_L1_DP1_stay_open_time = 5; // in seconds (1 to 30)
										// Dome Panel #2
boolean btnRight_L1_use_DP2 = false;
int btnRight_L1_DP2_open_start_delay = 1; // in seconds (0 to 30)
int btnRight_L1_DP2_stay_open_time = 5; // in seconds (1 to 30)
										// Dome Panel #3
boolean btnRight_L1_use_DP3 = false;
int btnRight_L1_DP3_open_start_delay = 1; // in seconds (0 to 30)
int btnRight_L1_DP3_stay_open_time = 5; // in seconds (1 to 30)
										// Dome Panel #4
boolean btnRight_L1_use_DP4 = false;
int btnRight_L1_DP4_open_start_delay = 1; // in seconds (0 to 30)
int btnRight_L1_DP4_stay_open_time = 5; // in seconds (1 to 30)
										// Dome Panel #5
boolean btnRight_L1_use_DP5 = false;
int btnRight_L1_DP5_open_start_delay = 1; // in seconds (0 to 30)
int btnRight_L1_DP5_stay_open_time = 5; // in seconds (1 to 30)
										// Dome Panel #6
boolean btnRight_L1_use_DP6 = false;
int btnRight_L1_DP6_open_start_delay = 1; // in seconds (0 to 30)
int btnRight_L1_DP6_stay_open_time = 5; // in seconds (1 to 30)
										// Dome Panel #7
boolean btnRight_L1_use_DP7 = false;
int btnRight_L1_DP7_open_start_delay = 1; // in seconds (0 to 30)
int btnRight_L1_DP7_stay_open_time = 5; // in seconds (1 to 30)
										// Dome Panel #8
boolean btnRight_L1_use_DP8 = false;
int btnRight_L1_DP8_open_start_delay = 1; // in seconds (0 to 30)
int btnRight_L1_DP8_stay_open_time = 5; // in seconds (1 to 30)
										// Dome Panel #9
boolean btnRight_L1_use_DP9 = false;
int btnRight_L1_DP9_open_start_delay = 1; // in seconds (0 to 30)
int btnRight_L1_DP9_stay_open_time = 5; // in seconds (1 to 30)
										// Dome Panel #10
boolean btnRight_L1_use_DP10 = false;
int btnRight_L1_DP10_open_start_delay = 1; // in seconds (0 to 30)
int btnRight_L1_DP10_stay_open_time = 5; // in seconds (1 to 30)

										 //---------------------------------
										 // CONFIGURE: Arrow Down + L1
										 //---------------------------------
										 //1 = Std MarcDuino Function, 2 = Custom Function
int btnDown_L1_type = 1;

// IF Std MarcDuino Function (type=1) 
// Enter MarcDuino Function Code (1 - 78) (See Above)
int btnDown_L1_MD_func = 9;

// IF Custom Function (type=2)
// CUSTOM SOUND SETTING: Enter the file # prefix on the MP3 trigger card of the sound to play (0 = NO SOUND)
// Valid values: 0 or 182 - 200  
int btnDown_L1_cust_MP3_num = 0;

// CUSTOM LOGIC DISPLAY SETTING: Pick from the Std MD Logic Display Functions (See Above)
// Valid values: 0, 1 to 8  (0 - Not used)
int btnDown_L1_cust_LD_type = 0;

// IF Custom Logic Display = 8 (custom text), enter custom display text here
String btnDown_L1_cust_LD_text = "";

// CUSTOM PANEL SETTING: Pick from the Std MD Panel Functions or Custom (See Above)
// Valid Values: 0, 1 to 9 (0 = Not used)
int btnDown_L1_cust_panel = 0;

// IF Custom Panel Setting = 9 (custom panel sequence)
// Dome Panel #1
boolean btnDown_L1_use_DP1 = false;
int btnDown_L1_DP1_open_start_delay = 1; // in seconds (0 to 30)
int btnDown_L1_DP1_stay_open_time = 5; // in seconds (1 to 30)
									   // Dome Panel #2
boolean btnDown_L1_use_DP2 = false;
int btnDown_L1_DP2_open_start_delay = 1; // in seconds (0 to 30)
int btnDown_L1_DP2_stay_open_time = 5; // in seconds (1 to 30)
									   // Dome Panel #3
boolean btnDown_L1_use_DP3 = false;
int btnDown_L1_DP3_open_start_delay = 1; // in seconds (0 to 30)
int btnDown_L1_DP3_stay_open_time = 5; // in seconds (1 to 30)
									   // Dome Panel #4
boolean btnDown_L1_use_DP4 = false;
int btnDown_L1_DP4_open_start_delay = 1; // in seconds (0 to 30)
int btnDown_L1_DP4_stay_open_time = 5; // in seconds (1 to 30)
									   // Dome Panel #5
boolean btnDown_L1_use_DP5 = false;
int btnDown_L1_DP5_open_start_delay = 1; // in seconds (0 to 30)
int btnDown_L1_DP5_stay_open_time = 5; // in seconds (1 to 30)
									   // Dome Panel #6
boolean btnDown_L1_use_DP6 = false;
int btnDown_L1_DP6_open_start_delay = 1; // in seconds (0 to 30)
int btnDown_L1_DP6_stay_open_time = 5; // in seconds (1 to 30)
									   // Dome Panel #7
boolean btnDown_L1_use_DP7 = false;
int btnDown_L1_DP7_open_start_delay = 1; // in seconds (0 to 30)
int btnDown_L1_DP7_stay_open_time = 5; // in seconds (1 to 30)
									   // Dome Panel #8
boolean btnDown_L1_use_DP8 = false;
int btnDown_L1_DP8_open_start_delay = 1; // in seconds (0 to 30)
int btnDown_L1_DP8_stay_open_time = 5; // in seconds (1 to 30)
									   // Dome Panel #9
boolean btnDown_L1_use_DP9 = false;
int btnDown_L1_DP9_open_start_delay = 1; // in seconds (0 to 30)
int btnDown_L1_DP9_stay_open_time = 5; // in seconds (1 to 30)
									   // Dome Panel #10
boolean btnDown_L1_use_DP10 = false;
int btnDown_L1_DP10_open_start_delay = 1; // in seconds (0 to 30)
int btnDown_L1_DP10_stay_open_time = 5; // in seconds (1 to 30)

										//----------------------------------------------------
										// CONFIGURE: The DOME Navigation Controller Buttons
										//----------------------------------------------------

										//---------------------------------
										// CONFIGURE: Arrow Up
										//---------------------------------
										// Enter MarcDuino Function Code (1 - 78) (See Above)
int FTbtnUP_MD_func = 58;

//---------------------------------
// CONFIGURE: Arrow Left
//---------------------------------
// Enter MarcDuino Function Code (1 - 78) (See Above)
int FTbtnLeft_MD_func = 56;

//---------------------------------
// CONFIGURE: Arrow Right
//---------------------------------
// Enter MarcDuino Function Code (1 - 78) (See Above)
int FTbtnRight_MD_func = 57;

//---------------------------------
// CONFIGURE: Arrow Down
//---------------------------------
// Enter MarcDuino Function Code (1 - 78) (See Above)
int FTbtnDown_MD_func = 59;

//---------------------------------
// CONFIGURE: Arrow UP + CROSS
//---------------------------------
// Enter MarcDuino Function Code (1 - 78) (See Above)
int FTbtnUP_CROSS_MD_func = 28;

//---------------------------------
// CONFIGURE: Arrow Left + CROSS
//---------------------------------
// Enter MarcDuino Function Code (1 - 78) (See Above)
int FTbtnLeft_CROSS_MD_func = 33;

//---------------------------------
// CONFIGURE: Arrow Right + CROSS
//---------------------------------
// Enter MarcDuino Function Code (1 - 78) (See Above)
int FTbtnRight_CROSS_MD_func = 30;

//---------------------------------
// CONFIGURE: Arrow Down + CROSS
//---------------------------------
// Enter MarcDuino Function Code (1 - 78) (See Above)
int FTbtnDown_CROSS_MD_func = 29;

//---------------------------------
// CONFIGURE: Arrow UP + CIRCLE
//---------------------------------
// Enter MarcDuino Function Code (1 - 78) (See Above)
int FTbtnUP_CIRCLE_MD_func = 22;

//---------------------------------
// CONFIGURE: Arrow Left + CIRCLE
//---------------------------------
// Enter MarcDuino Function Code (1 - 78) (See Above)
int FTbtnLeft_CIRCLE_MD_func = 23;

//---------------------------------
// CONFIGURE: Arrow Right + CIRCLE
//---------------------------------
// Enter MarcDuino Function Code (1 - 78) (See Above)
int FTbtnRight_CIRCLE_MD_func = 24;

//---------------------------------
// CONFIGURE: Arrow Down + CIRCLE
//---------------------------------
// Enter MarcDuino Function Code (1 - 78) (See Above)
int FTbtnDown_CIRCLE_MD_func = 25;

//---------------------------------
// CONFIGURE: Arrow UP + PS
//---------------------------------
// Enter MarcDuino Function Code (1 - 78) (See Above)
int FTbtnUP_PS_MD_func = 38;

//---------------------------------
// CONFIGURE: Arrow Left + PS
//---------------------------------
// Enter MarcDuino Function Code (1 - 78) (See Above)
int FTbtnLeft_PS_MD_func = 40;

//---------------------------------
// CONFIGURE: Arrow Right + PS
//---------------------------------
// Enter MarcDuino Function Code (1 - 78) (See Above)
int FTbtnRight_PS_MD_func = 41;

//---------------------------------
// CONFIGURE: Arrow Down + PS
//---------------------------------
// Enter MarcDuino Function Code (1 - 78) (See Above)
int FTbtnDown_PS_MD_func = 39;

//---------------------------------
// CONFIGURE: Arrow Up + L1
//---------------------------------
// Enter MarcDuino Function Code (1 - 78) (See Above)
int FTbtnUP_L1_MD_func = 34;

//---------------------------------
// CONFIGURE: Arrow Left + L1
//---------------------------------
// Enter MarcDuino Function Code (1 - 78) (See Above)
int FTbtnLeft_L1_MD_func = 36;

//---------------------------------
// CONFIGURE: Arrow Right + L1
//---------------------------------
// Enter MarcDuino Function Code (1 - 78) (See Above)
int FTbtnRight_L1_MD_func = 37;

//---------------------------------
// CONFIGURE: Arrow Down + L1
//---------------------------------
// Enter MarcDuino Function Code (1 - 78) (See Above)
int FTbtnDown_L1_MD_func = 35;

// ---------------------------------------------------------------------------------------
//               SYSTEM VARIABLES - USER CONFIG SECTION COMPLETED
// ---------------------------------------------------------------------------------------

// ---------------------------------------------------------------------------------------
//                          Drive Controller Settings
// ---------------------------------------------------------------------------------------

int motorControllerBaudRate = 9600; // Set the baud rate for the Syren motor controller
									// for packetized options are: 2400, 9600, 19200 and 38400

int marcDuinoBaudRate = 9600; // Set the baud rate for the Syren motor controller

#define SYREN_ADDR         129      // Serial Address for Dome Syren
#define SABERTOOTH_ADDR    128      // Serial Address for Foot Sabertooth

#define ENABLE_UHS_DEBUGGING 1

// ---------------------------------------------------------------------------------------
//                          Sound Settings
// ---------------------------------------------------------------------------------------
//Uncomment one line based on your sound system
//#define SOUND_CFSOUNDIII     //Original system tested with SHADOW
//#define SOUND_MP3TRIGGER   //Code Tested by Dave C. and Marty M.
#define SOUND_WAVTRIGGER   //
//#define SOUND_ROGUE_RMP3   //Support coming soon
//#define SOUND_RASBERRYPI   //Support coming soon


							  // ---------------------------------------------------------------------------------------
							  //                          Libraries
							  // ---------------------------------------------------------------------------------------
#include <avr/wdt.h>
#include <SoftwareSerial.h> 

#include <PS3BT.h>
#include <usbhub.h>

							  // Satisfy IDE, which only needs to see the include statment in the ino.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif

#include <Sabertooth.h>

#define FASTLED_INTERNAL
#include <FastLED.h>

#include <Wire.h>                        //

							  //This is the traditional sound controler that has been used with PADAWAN
#ifdef SOUND_MP3TRIGGER
#include <MP3Trigger.h>
MP3Trigger trigger;
#endif

								// This is the WAVTrigger sound controller 
#ifdef SOUND_WAVTRIGGER
//#include <AltSoftSerial.h>
//#define __WT_USE_ALTSOFTSERIAL__
#include <AltSoftSerial.h>    // Arduino build environment requires this
#include <wavTrigger.h>
wavTrigger trigger;
#endif

#ifdef SOUND_MP3FLASH16P
#include <MP3FLASH16P.h>
MP3FLASH16P mp3Trigger1;
MP3FLASH16P mp3Trigger2;
#endif

							  // ---------------------------------------------------------------------------------------
							  //                          Neopixel LED Management
							  // ---------------------------------------------------------------------------------------

//#define STATUS_LEDCOUNT 8
#define STATUS_LEDTYPE        WS2812B
#define STATUS_LEDCOLORORDER     GRB
#define STATUS_RADIOHOLD        50
typedef enum { statusLED_Power=0, statusLED_Radio, statusLED_Command, statusLED_LED4, statusLED_LED5, statusLED_DomePower, statusLED_DriveNav, statusLED_DomeNav, statusLED_Count } ledStatus_Type;
int statusLedIndex = 0;
CRGB statusLEDs[statusLED_Count]; // = {CHSV( 160, 255, 0), CHSV( 96, 255, 128 ), CHSV( 192, 255, 0 ), CHSV( 224, 255, 0 )};

CHSV colourPowerLED = CHSV(HUE_RED, 255, 192); // green
CHSV colourRadioLED = CHSV(HUE_RED, 255, 192); // green
CHSV colourCommandLED = CHSV(HUE_GREEN, 255, 192); // purple
//CHSV colourFuncLED = CHSV(HUE_BLUE, 0, 0); // blue
//CHSV colourFuncLED = CHSV(HUE_BLUE, 0, 0); // blue
CHSV colourDomePower = CHSV(HUE_RED, 255, 192); // 
CHSV colourDriveNav = CHSV(HUE_RED, 255, 192); // 
CHSV colourDomeNav = CHSV(HUE_RED, 255, 192); // 


							  // ---------------------------------------------------------------------------------------
							  //                    Sound
							  // ---------------------------------------------------------------------------------------
int soundFileNo = 0;
int soundVolume = 1;


							  // ---------------------------------------------------------------------------------------
							  //                    Panel Management Variables
							  // ---------------------------------------------------------------------------------------
boolean runningCustRoutine = false;

int DP1_Status = 0;  // 0 = closed, 1 = waiting to open, 2 = open
unsigned long DP1_start = 0;
int DP1_s_delay = 0;
int DP1_o_time = 0;

int DP2_Status = 0;  // 0 = closed, 1 = waiting to open, 2 = open
unsigned long DP2_start = 0;
int DP2_s_delay = 0;
int DP2_o_time = 0;

int DP3_Status = 0;  // 0 = closed, 1 = waiting to open, 2 = open
unsigned long DP3_start = 0;
int DP3_s_delay = 0;
int DP3_o_time = 0;

int DP4_Status = 0;  // 0 = closed, 1 = waiting to open, 2 = open
unsigned long DP4_start = 0;
int DP4_s_delay = 0;
int DP4_o_time = 0;

int DP5_Status = 0;  // 0 = closed, 1 = waiting to open, 2 = open
unsigned long DP5_start = 0;
int DP5_s_delay = 0;
int DP5_o_time = 0;

int DP6_Status = 0;  // 0 = closed, 1 = waiting to open, 2 = open
unsigned long DP6_start = 0;
int DP6_s_delay = 0;
int DP6_o_time = 0;

int DP7_Status = 0;  // 0 = closed, 1 = waiting to open, 2 = open
unsigned long DP7_start = 0;
int DP7_s_delay = 0;
int DP7_o_time = 0;

int DP8_Status = 0;  // 0 = closed, 1 = waiting to open, 2 = open
unsigned long DP8_start = 0;
int DP8_s_delay = 0;
int DP8_o_time = 0;

int DP9_Status = 0;  // 0 = closed, 1 = waiting to open, 2 = open
unsigned long DP9_start = 0;
int DP9_s_delay = 0;
int DP9_o_time = 0;

int DP10_Status = 0;  // 0 = closed, 1 = waiting to open, 2 = open
unsigned long DP10_start = 0;
int DP10_s_delay = 0;
int DP10_o_time = 0;

// ---------------------------------------------------------------------------------------
//                          Variables
// ---------------------------------------------------------------------------------------

long previousDomeMillis = millis();
long previousFootMillis = millis();
long previousMarcDuinoMillis = millis();
long previousDomeToggleMillis = millis();
long previousSpeedToggleMillis = millis();

//long currentMillis = millis();

int serialLatency = 25;   //This is a delay factor in ms to prevent queueing of the Serial data.
						  //25ms seems approprate for HardwareSerial, values of 50ms or larger are needed for Softare Emulation

int marcDuinoButtonCounter = 0;
int speedToggleButtonCounter = 0;
int domeToggleButtonCounter = 0;

Sabertooth *ST = new Sabertooth(SABERTOOTH_ADDR, Serial2);
Sabertooth *SyR = new Sabertooth(SYREN_ADDR, Serial2);

///////Setup for USB and Bluetooth Devices////////////////////////////
USB Usb;
BTD Btd(&Usb);
PS3BT *PS3NavFoot = new PS3BT(&Btd);
PS3BT *PS3NavDome = new PS3BT(&Btd);

//Used for PS3 Fault Detection
uint32_t msgLagTime = 0;
uint32_t lastMsgTime = 0;
uint32_t currentTime = 0;
uint32_t lastLoopTime = 0;
int badPS3Data = 0;
int badPS3DataDome = 0;

boolean firstMessage = true;
String output = "";

boolean isFootMotorStopped = true;
boolean isDomeMotorStopped = true;

boolean overSpeedSelected = false;

boolean isPrimaryPS3NavigatonInitialized = false;
boolean isSecondaryPS3NavigatonInitialized = false;

boolean isStickEnabled = false;

boolean WaitingforReconnect = false;
boolean WaitingforReconnectDome = false;

boolean mainControllerConnected = false;
boolean domeControllerConnected = false;

// Dome Automation Variables
boolean domeAutomation = false;
int domeTurnDirection = 1;  // 1 = positive turn, -1 negative turn
float domeTargetPosition = 0; // (0 - 359) - degrees in a circle, 0 = home
unsigned long domeStopTurnTime = 0;    // millis() when next turn should stop
unsigned long domeStartTurnTime = 0;  // millis() when next turn should start
int domeStatus = 0;  // 0 = stopped, 1 = prepare to turn, 2 = turning

byte action = 0;
unsigned long DriveMillis = 0;

int footDriveSpeed = 0;

#define INPUTBUFFERLEN 7
#define MAXCOMMANDLENGTH 12
char inputBuffer[INPUTBUFFERLEN];
String inputString = "";                       // a string to hold incoming data
volatile boolean stringComplete = false;       // whether the serial string is complete
















#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

/*
button[10]:0
button[9]:16
button[8]:6
button[7]:8
button[6]:10
button[5]:13
button[4]:14
button[3]:1
button[2]:2
button[1]:0
button[0]:3
*/
//
// define buttons we will use and put its pin pseudonym in the list - BUTTONCOUNT will hold how many buttons in the array
//
//enum { psNav_Left=0, psNav_UP, psNav_DOWN, psNav_RIGHT, psNav_CROSS, psNav_CIRCLE, psNav_L1, psNav_L2, psNav_L3, psNav_PS} idPSNavButtons;
enum { psNav_UP=0, psNav_RIGHT, psNav_DOWN, psNav_Left, psNav_L3, psNav_L2, psNav_L1, psNav_CIRCLE, psNav_CROSS, psNav_PS} idPSNavButtons;

#define BUTTONCOUNT ARRAY_SIZE(buttonIds)
//const uint8_t buttonIds[]{ LEFT=3, UP=0, DOWN=2, RIGHT=1, CROSS=14, CIRCLE=13, L1=10, L2=8, L3=6, PS=16};
#define FOOTSHIFT 64
#define DOMESHIFT 64
enum {
	FOOT_START = UP-1 + FOOTSHIFT, FOOT_UP = UP + FOOTSHIFT, FOOT_RIGHT = RIGHT + FOOTSHIFT, FOOT_DOWN = DOWN + FOOTSHIFT, FOOT_LEFT = LEFT + FOOTSHIFT, FOOT_L3 = L3 + FOOTSHIFT, FOOT_L2 = L2 + FOOTSHIFT, FOOT_L1 = L1 + FOOTSHIFT, FOOT_CIRCLE = CIRCLE + FOOTSHIFT, FOOT_CROSS = CROSS + FOOTSHIFT, FOOT_PS = PS + FOOTSHIFT, FOOT_END,
	DOME_START = UP-1 + DOMESHIFT, DOME_UP = UP + DOMESHIFT, DOME_RIGHT = RIGHT + DOMESHIFT, DOME_DOWN = DOWN + DOMESHIFT, DOME_LEFT = LEFT + DOMESHIFT, DOME_L3 = L3 + DOMESHIFT, DOME_L2 = L2 + DOMESHIFT, DOME_L1 = L1 + DOMESHIFT, DOME_CIRCLE = CIRCLE + DOMESHIFT, DOME_CROSS = CROSS + DOMESHIFT, DOME_PS = PS + DOMESHIFT, DOME_END
} buttonXLATE;
const uint8_t buttonIds[]{ 
	FOOT_UP, FOOT_RIGHT, FOOT_DOWN, FOOT_LEFT, FOOT_L3, FOOT_L2, FOOT_L1, FOOT_CIRCLE, FOOT_CROSS, FOOT_PS,
	DOME_UP, DOME_RIGHT, DOME_DOWN, DOME_LEFT, DOME_L3, DOME_L2, DOME_L1, DOME_CIRCLE, DOME_CROSS, DOME_PS
};

//
// Buttons status
////////////////////////////////////////////////////////////////////////////
#define debounceDelay 20
#define DCgap 150               // max ms between clicks for a double click event
#define holdTime 1000           // ms hold period: how long to wait for press+hold event
#define longHoldTime 3000       // ms long hold period: how long to wait for press+hold event

struct debounceButton {

	int inPin = 2;

	int status = 0;               // status of button, will be one of enum joyButton_Type (check this for button trigger events)
	boolean buttonVal = HIGH;   // value read from button
	boolean buttonLast = HIGH;  // buffered value of the button's previous state
	boolean DCwaiting = false;  // whether we're waiting for a double click (down)
	boolean DConUp = false;     // whether to register a double click on next release, or whether to wait and click
	boolean singleOK = true;    // whether it's OK to do a single click
	long downTime = -1;         // time the button was pressed down
	long upTime = -1;           // time the button was released
	boolean ignoreUp = false;   // whether to ignore the button release because the click+hold was triggered
	boolean waitForUp = false;        // when held, whether to wait for the up event
	boolean holdEventPast = false;    // whether or not the hold event happened already
	boolean longHoldEventPast = false;// whether or not the long hold event happened already

} ;

typedef enum {

	joyButtonNone = 0,
	joyButtonClick,
	joyButtonDoubleClick,
	joyButtonHold,
	joyButtonLongHold

} joyButton_Type;

debounceButton debounceButtons[BUTTONCOUNT];

//
// function : int checkButton(struct debounceButton *butt)
// Keep / update status of button configured within the passed debounceButton structure 
//
// Inputs :
//   an initialised debounceButton structure 
//
// Outputs :
//   status - the checked buttons status.
//
//
int checkButton(struct debounceButton *butt) {
	// ME:found and modified from
	// http://forum.arduino.cc/index.php?topic=14479.0
	//

	//int reading = digitalRead(butt->inPin);
	//
	// figure out
	// button click
	// button double click
	// button hold
	// button long hold
	//
	//
	butt->status = 0;
	//butt->buttonVal = digitalRead(butt->inPin);

	//butt->buttonVal = HIGH;
	if (butt->inPin > FOOT_START && butt->inPin < FOOT_END) {
		if ( PS3NavFoot->getButtonPress((ButtonEnum)(butt->inPin - FOOTSHIFT))) butt->buttonVal = LOW; else butt->buttonVal = HIGH;
	}
	else {
		if ( PS3NavDome->getButtonPress((ButtonEnum)(butt->inPin - DOMESHIFT))) butt->buttonVal = LOW; else butt->buttonVal = HIGH;

	}

	//Serial.println("pin:" + String(butt->inPin) + ":" + butt->buttonVal + ":" + millis());

	// Button pressed down
	if (butt->buttonVal == LOW && butt->buttonLast == HIGH && (millis() - butt->upTime) > debounceDelay)
	{
		butt->downTime = millis();
		butt->ignoreUp = false;
		butt->waitForUp = false;
		butt->singleOK = true;
		butt->holdEventPast = false;
		butt->longHoldEventPast = false;
		if ((millis() - butt->upTime) < DCgap && butt->DConUp == false && butt->DCwaiting == true)  butt->DConUp = true;
		else  butt->DConUp = false;
		butt->DCwaiting = false;
	}
	// Button released
	else {
		if (butt->buttonVal == HIGH && butt->buttonLast == LOW && (millis() - butt->downTime) > debounceDelay) {
			if (not butt->ignoreUp) {
				butt->upTime = millis();
				if (butt->DConUp == false) {
					butt->DCwaiting = true;
				}
				else {
					if ( not butt->holdEventPast ) {
						butt->status = joyButtonDoubleClick;
						butt->DConUp = false;
						butt->DCwaiting = false;
						butt->singleOK = false;
					}
					else {
						if ( butt->longHoldEventPast ) {
							butt->status = joyButtonLongHold;
						}
					}
				}
			}
			else {
				if ( not butt->longHoldEventPast ) {
					butt->status = joyButtonHold;
				}
			}
		}
	}
	// Test for normal click event: DCgap expired
	if ( butt->buttonVal == HIGH && (millis() - butt->upTime) >= DCgap && butt->DCwaiting == true && butt->DConUp == false && butt->singleOK == true && butt->status != joyButtonDoubleClick)
	{
		butt->status = joyButtonClick;
		butt->DCwaiting = false;
	}

	// Test for hold
	if (butt->buttonVal == LOW && (millis() - butt->downTime) >= holdTime) {
		// Trigger "normal" hold
		if (not butt->holdEventPast)
		{
			butt->waitForUp = true;
			butt->ignoreUp = true;
			butt->DConUp = false;
			butt->DCwaiting = false;
			//downTime = millis();
			butt->holdEventPast = true;
		}
		// Trigger "long" hold
		if ((millis() - butt->downTime) >= longHoldTime)
		{
			if (not butt->longHoldEventPast) {
				butt->status = joyButtonLongHold;
				butt->longHoldEventPast = true;
			}

		}
	}

	butt->buttonLast = butt->buttonVal;

	//    Serial.print("event:");
	//    Serial.println(event);

	return butt->status;

}

//#endif














// =======================================================================================
//                          Main Program
// =======================================================================================


// =======================================================================================
//                          Initialize - Setup Function
// =======================================================================================
void setup()
{
	wdt_disable(); //always good to disable it, if it was left 'on' or you need init time

				   //Debug Serial for use with USB Debugging
	Serial.begin(115200);
	while (!Serial);

	Serial.print("Sketch:   ");   Serial.println(__FILE__);
	Serial.print("Uploaded: ");   Serial.println(__DATE__);
	Serial.println(" ");
	
	Serial.println("R2M3-Body-AVR v1.0a");
	Serial.println("Initializing");

	/////////////////////////////////////////////////////////////////////////////////////////////
	Serial.print("- I/O Pins ");

	//
	// disable all motor relays (HIGH)
	// they should already be disabled on powerup
	// wait for sequence from remote to enable
	//

	Serial.print(".");

	pinMode(pinOut_MotorDomeEnableRelay, OUTPUT);
	digitalWrite(pinOut_MotorDomeEnableRelay, LOW);

	Serial.print(".");

	digitalWrite(pinOut_MotorLeftEnableRelay, LOW);
	pinMode(pinOut_MotorLeftEnableRelay, OUTPUT);

	Serial.print(".");

	digitalWrite(pinOut_MotorRightEnableRelay, LOW);
	pinMode(pinOut_MotorRightEnableRelay, OUTPUT);

	Serial.print(".");

	//
	// Disable dome power for a few seconds at least
	//

	digitalWrite(pinOut_PowerDomeEnableRelay, LOW);
	pinMode(pinOut_PowerDomeEnableRelay, OUTPUT);

	//Serial.print(".");

	//digitalWrite(pinOut_BLE_Enable, HIGH);
	//pinMode(pinOut_BLE_Enable, OUTPUT);

	Serial.println(" Done");
	delay(50);


	for (int i = BUTTONCOUNT-1; i >= 0; --i) {
		Serial.println("button["+String(i)+"]:"+String(buttonIds[i]));
		//Serial.print(".");
		debounceButtons[i].inPin = buttonIds[i];
		//pinMode(debounceButtons[i].inPin, INPUT_PULLUP);
		//digitalWrite(debounceButtons[i].inPin, HIGH);
	}


	/////////////////////////////////////////////////////////////////////////////////////////////
	Serial.print("- i2c ");

#define I2CADDRESS 0x19  // 25 in Hexadecmal

	Wire.begin(I2CADDRESS);                  // Connects to I2C Bus and establishes address.
	Wire.onReceive(i2cEvent);                // Register event so when we receive something we jump to i2cEvent();

	Serial.println(" Done");
	delay(50);


	Serial.print("- Status LEDs ");

	FastLED.addLeds<STATUS_LEDTYPE, pinOut_StatusLEDs, STATUS_LEDCOLORORDER>(statusLEDs, statusLED_Count).setCorrection(TypicalLEDStrip);
	FastLED.setBrightness(128);

	for (int i = 0; i < statusLED_Count; i++) {
		// HUE / Saturation / Brightness 
		statusLEDs[i] = CHSV(HUE_BLUE, 255, 128);
		Serial.print(".");
	}
	FastLED.show();
	statusLedIndex = 7;
	Serial.println(" Done");

	delay(50);


	/////////////////////////////////////////////////////////////////////////////////////////////
	Serial.print("- Drive Motor Controller ");

	//Setup for Serial2:: Motor Controllers - Sabertooth (Feet) 
	Serial2.begin(motorControllerBaudRate);
	//ST->autobaud();          // Send the autobaud command to the Sabertooth controller(s).
	ST->setBaudRate(motorControllerBaudRate);
	ST->setTimeout(10);      //DMB:  How low can we go for safety reasons?  multiples of 100ms
	ST->setDeadband(driveDeadBandRange);
	ST->stop();
	Serial.println(" Done");

	statusLEDs[statusLedIndex--] = 0; FastLED.show();
	
	delay(50);

	/////////////////////////////////////////////////////////////////////////////////////////////
	Serial.print("- Dome Motor Controller ");
	//SyR->autobaud()
	SyR->setBaudRate(motorControllerBaudRate);
	SyR->setTimeout(20);      //DMB:  How low can we go for safety reasons?  multiples of 100ms
	SyR->stop();
	Serial.println(" Done");
	statusLEDs[statusLedIndex--] = 0; FastLED.show();
	delay(50);

	/////////////////////////////////////////////////////////////////////////////////////////////
	Serial.print("- Dome Power ");

	//domePowerEnable(false);

	Serial.print(".");

	Serial.println(" Done");
	statusLEDs[statusLedIndex--] = 0; FastLED.show();
	delay(50);


	//
	// mp3Player Init
	//

	/////////////////////////////////////////////////////////////////////////////////////////////
	Serial.print("- Audio ");
	// void MP3FLASH16P::init(int PIN_BUSY, int VOLUME, int rxPin = 10, int txPin = 11)
#ifdef SOUND_MP3FLASH16P

	mp3Trigger1.init(0, mp3Volume, 0, pinOut_MP3Sound1Tx);   // busy pin & volume

	Serial.print(".");

	mp3Trigger2.init(0, mp3Volume, 0, pinOut_MP3Sound2Tx);   // busy pin & volume

	Serial.print(".");
#endif
#ifdef SOUND_WAVTRIGGER
	// WAV Trigger startup at 57600 unless otherwise defined in the sdcard init config file
	trigger.start();
	delay(10);

	// Send a stop-all command and reset the sample-rate offset, in case we have
	//  reset while the WAV Trigger was already playing.
	trigger.stopAllTracks();
	trigger.samplerateOffset(0);

#endif

	Serial.println(" Done");
	delay(50);


	/////////////////////////////////////////////////////////////////////////////////////////////
	Serial.print("- USB Init ");

	if (Usb.Init() == -1)
	{
		Serial.print(F("error"));
		while (1); //halt
	}

	Serial.println(" Done");
	statusLEDs[statusLedIndex--] = 0; FastLED.show();
	delay(50);

	output.reserve(200); // Reserve 200 bytes for the output string

						 /////////////////////////////////////////////////////////////////////////////////////////////
	Serial.print("- Bluetooth Library ");

	//Setup for PS3
	PS3NavFoot->attachOnInit(onInitPS3NavFoot); // onInitPS3NavFoot is called upon a new connection
	PS3NavDome->attachOnInit(onInitPS3NavDome);

	Serial.println(" Done");
	statusLEDs[statusLedIndex--] = 0; FastLED.show();
	delay(50);

	statusLEDs[statusLedIndex--] = 0; FastLED.show();


	//Setup for Serial1:: Sound 
#ifdef SOUND_CFSOUNDIII
	cfSound.setup(&Serial1, 2400);
#endif
#ifdef SOUND_MP3TRIGGER
	trigger.setup(&Serial1);
	trigger.setVolume(vol);
#endif

#ifdef SOUND_WAVTRIGGER
	Serial.println("wav Tringger stuff");

	//trigger.setup(&Serial1);
	//trigger.setAmpPwr(false);
	//trigger.masterGain(soundVolume);
#endif

	//Setup for Serial1:: MarcDuino Dome Control Board
	DomePanelController.begin(marcDuinoBaudRate);

	//Setup for Serial3:: Optional MarcDuino Control Board for Body Panels
	BodyPanelController.begin(marcDuinoBaudRate);


	statusLEDs[statusLedIndex--] = 0; FastLED.show();
	randomSeed(analogRead(0));  // random number seed for dome automation   

	statusLEDs[statusLedIndex--] = 0; FastLED.show();
	

	// WTD is disabled here as the USB shield and bloototh dongle take longer than 500ms to startup
	//////////////////////////////////

	//    wdt_enable(WDTO_500MS); //enable it, and set it to 500ms
	//    wdt_reset();
#ifdef SOUND_MP3FLASH16P
	mp3Trigger1.play(1);
#endif
#ifdef SOUND_WAVTRIGGER
	Serial.println("Playing Track 1");
	trigger.trackPlaySolo(1);
#endif

	Serial.println("Complete");
}

// =======================================================================================
//           Main Program Loop - This is the recurring check loop for entire sketch
// =======================================================================================
uint32_t currentMillis = 0;
uint32_t lastMillis = 0;
uint32_t loopCount;
uint32_t fastLEDMillis = 0;
bool wdt_ok = false;
int buttonStatus = 0;

void loop()
{
	//Serial.println("loop");
	currentMillis = millis();
	loopCount++;

	 

	//Useful to enable with serial console when having controller issues.
#ifdef TEST_CONROLLER
	testPS3Controller();
#endif
	if (currentMillis > 10000 && wdt_ok == false) {
		//wdt_enable(WDTO_500MS); //enable it, and set it to 500ms
		wdt_ok = true;
		Serial.println("WDT Enabled!");
		//
		// enable  Dome power (at same time as enabling watchdog timer)
		//
		digitalWrite(pinOut_PowerDomeEnableRelay, HIGH);

	}

	statusLEDCheck();        // see if the status led should be turned off

	if (stringComplete) {
		inputString.trim();
		Serial.println(inputString + ":" + String(soundFileNo));
		//int mp3fn = atoi(inputString.c_str());
		Serial1.println(inputString.c_str());
#ifdef SOUND_MP3FLASH16P
		mp3Trigger1.play(mp3fn,mp3Volume);
#endif
		//mp3fileno++;



		inputString = "";
		stringComplete = false;
	}


	//LOOP through functions from highest to lowest priority.

	if (!readUSB()) {
		//We have a fault condition that we want to ensure that we do NOT process any controller data!!!
		printOutput();
	}
	else {
		motorRelays();

		footMotorDrive();
		domeMotorDrive();
		
		buttonextrafunc();


		marcDuinoDome();
		marcDuinoFoot();

		toggleSettings();
		printOutput();

		// If running a custom MarcDuino Panel Routine - Call Function
		//if (runningCustRoutine)
		//{
		//	custMarcDuinoPanel();
		//}

		// If dome automation is enabled - Call function
		if (domeAutomation && time360DomeTurn > 1999 && time360DomeTurn < 8001 && domeAutoSpeed > 49 && domeAutoSpeed < 101)
		{
			//Serial.println("autoDome");
			autoDome();
		}
	}

	//fastLEDs();

	if (currentMillis - lastMillis > 1000) {
		Serial.println("Body Main CM:" + String(currentMillis)
			+ " LC:" + String(loopCount)
			//+ " PC:" + String(buttonStatus)
			//+ " P10:" + String(pin10)
			//+ " SM:" + String(stageMillis)
			//+ " SG:" + String(stage)
			//+ " BA:" + String(BLESerial.available())
			//+ " _dome:" + String(transmit_data._dome) + ":" + String(dome)
			//+ " B:" + buttbinary
			//+ " LRC:" + String(colourRadioLED.hue)
			//+ " BS:" + String(buttonStatus)
			//+ " MS:" + String(_motorStatus)

			//+ " MS:" + String(transmit_data._motors)
			//+ " _Z:" + String(actualZone)
			//+ " J0H:" + String(dataOut._joy0HorzValue)
			//+ " J0V:" + String(dataOut._joy0VertValue)
			//+ " J1H:" + String(dataOut._joy1HorzValue)
			//+ " J1V:" + String(dataOut._joy1VertValue)

			//+ " POS:" + pos

		);

		// + ":" + String(transmit_data._buttons) + "("+String(transmit_data._buttons&0x1)+")");
		lastMillis = currentMillis;
		loopCount = 0;
		// packetCount = 0;
	}

	wdt_reset();

}

long buttonMillis = 0;

void buttonextrafunc()
{
	if (currentMillis - buttonMillis > 50) {
		for (int i = 0; i < BUTTONCOUNT; i++) {
			buttonStatus += (checkButton(&debounceButtons[i]) != 0 ? 1 : 0);
		}
		if (buttonStatus != 0) {
			String butString = "LEFT";
			int butStatus0 = debounceButtons[psNav_Left].status;
			if (butStatus0 == joyButtonClick) {
				Serial.println(butString + ":joyButtonClick");
			}
			else
				if (butStatus0 == joyButtonDoubleClick) {
					Serial.println(butString + ":joyButtonDoubleClick");
				}
				else
					if (butStatus0 == joyButtonLongHold) {
						Serial.println(butString + ":joyButtonLongHold");
					}
					else
						if (butStatus0 == joyButtonHold) {
							Serial.println(butString + ":joyButtonHold");
						}

			butString = "UP";
			butStatus0 = debounceButtons[psNav_UP].status;
			if (butStatus0 == joyButtonClick) {
				Serial.println(butString + ":joyButtonClick");
			}
			else
				if (butStatus0 == joyButtonDoubleClick) {
					Serial.println(butString + ":joyButtonDoubleClick");
				}
				else
					if (butStatus0 == joyButtonLongHold) {
						Serial.println(butString + ":joyButtonLongHold");
					}
					else
						if (butStatus0 == joyButtonHold) {
							Serial.println(butString + ":joyButtonHold");
						}

			butString = "DOWN";
			butStatus0 = debounceButtons[psNav_DOWN].status;
			if (butStatus0 == joyButtonClick) {
				Serial.println(butString + ":joyButtonClick");
			}
			else
				if (butStatus0 == joyButtonDoubleClick) {
					Serial.println(butString + ":joyButtonDoubleClick");
				}
				else
					if (butStatus0 == joyButtonLongHold) {
						Serial.println(butString + ":joyButtonLongHold");
					}
					else
						if (butStatus0 == joyButtonHold) {
							Serial.println(butString + ":joyButtonHold");
						}

			butString = "RIGHT";
			butStatus0 = debounceButtons[psNav_RIGHT].status;
			if (butStatus0 == joyButtonClick) {
				Serial.println(butString + ":joyButtonClick");
			}
			else
				if (butStatus0 == joyButtonDoubleClick) {
					Serial.println(butString + ":joyButtonDoubleClick");
				}
				else
					if (butStatus0 == joyButtonLongHold) {
						Serial.println(butString + ":joyButtonLongHold");
					}
					else
						if (butStatus0 == joyButtonHold) {
							Serial.println(butString + ":joyButtonHold");
						}

			butString = "CIRCLE";
			butStatus0 = debounceButtons[psNav_CIRCLE].status;
			if (butStatus0 == joyButtonClick) {
				Serial.println(butString + ":joyButtonClick");
			}
			else
				if (butStatus0 == joyButtonDoubleClick) {
					Serial.println(butString + ":joyButtonDoubleClick");
				}
				else
					if (butStatus0 == joyButtonLongHold) {
						Serial.println(butString + ":joyButtonLongHold");
					}
					else
						if (butStatus0 == joyButtonHold) {
							Serial.println(butString + ":joyButtonHold");
						}

			butString = "CROSS";
			butStatus0 = debounceButtons[psNav_CROSS].status;
			if (butStatus0 == joyButtonClick) {
				Serial.println(butString + ":joyButtonClick");
			}
			else
				if (butStatus0 == joyButtonDoubleClick) {
					Serial.println(butString + ":joyButtonDoubleClick");
				}
				else
					if (butStatus0 == joyButtonLongHold) {
						Serial.println(butString + ":joyButtonLongHold");
					}
					else
						if (butStatus0 == joyButtonHold) {
							Serial.println(butString + ":joyButtonHold");
						}

			butString = "PS";
			butStatus0 = debounceButtons[psNav_PS].status;
			if (butStatus0 == joyButtonClick) {
				Serial.println(butString + ":joyButtonClick");
			}
			else
				if (butStatus0 == joyButtonDoubleClick) {
					Serial.println(butString + ":joyButtonDoubleClick");
				}
				else
					if (butStatus0 == joyButtonLongHold) {
						Serial.println(butString + ":joyButtonLongHold");
					}
					else
						if (butStatus0 == joyButtonHold) {
							Serial.println(butString + ":joyButtonHold");
						}

			butString = "L3";
			butStatus0 = debounceButtons[psNav_L3].status;
			if (butStatus0 == joyButtonClick) {
				Serial.println(butString + ":joyButtonClick");
			}
			else
				if (butStatus0 == joyButtonDoubleClick) {
					Serial.println(butString + ":joyButtonDoubleClick");
				}
				else
					if (butStatus0 == joyButtonLongHold) {
						Serial.println(butString + ":joyButtonLongHold");
					}
					else
						if (butStatus0 == joyButtonHold) {
							Serial.println(butString + ":joyButtonHold");
						}
			butString = "L1";
			butStatus0 = debounceButtons[psNav_L1].status;
			if ( butStatus0 == joyButtonClick ) {
				Serial.println(butString + ":joyButtonClick");
			}
			else
				if ( butStatus0 == joyButtonDoubleClick ) {
					Serial.println(butString + ":joyButtonDoubleClick");
				}
				else
					if ( butStatus0 == joyButtonLongHold ) {
						Serial.println(butString + ":joyButtonLongHold");
					}
					else
						if ( butStatus0 == joyButtonHold ) {
							Serial.println(butString + ":joyButtonHold");
						}
			butString = "L2";
			butStatus0 = debounceButtons[psNav_L2].status;
			if ( butStatus0 == joyButtonClick ) {
				Serial.println(butString + ":joyButtonClick");
			}
			else
				if ( butStatus0 == joyButtonDoubleClick ) {
					Serial.println(butString + ":joyButtonDoubleClick");
				}
				else
					if ( butStatus0 == joyButtonLongHold ) {
						Serial.println(butString + ":joyButtonLongHold");
					}
					else
						if ( butStatus0 == joyButtonHold ) {
							Serial.println(butString + ":joyButtonHold");
						}
			buttonStatus = 0;
		}
		buttonMillis = currentMillis;
	}
}



// =======================================================================================
//           footDrive Motor Control Section
// =======================================================================================

boolean ps3FootMotorDrive(PS3BT* myPS3 = PS3NavFoot)
{
	int stickSpeed = 0;
	int turnnum = 0;

	if (isPrimaryPS3NavigatonInitialized)
	{
		// Additional fault control.  Do NOT send additional commands to Sabertooth if no controllers have initialized.
		if (!isStickEnabled)
		{
#ifdef SHADOW_VERBOSE
			if (abs(myPS3->getAnalogHat(LeftHatY) - 128) > joystickFootDeadZoneRange)
			{
				output += "Drive Stick is disabled\r\n";
			}
#endif

			if (!isFootMotorStopped)
			{
				ST->stop();
				isFootMotorStopped = true;
				footDriveSpeed = 0;

#ifdef SHADOW_VERBOSE      
				output += "\r\n***Foot Motor STOPPED***\r\n";
#endif              
			}

			return false;

		}
		else if (!myPS3->PS3NavigationConnected)
		{

			if (!isFootMotorStopped)
			{
				ST->stop();
				isFootMotorStopped = true;
				footDriveSpeed = 0;

#ifdef SHADOW_VERBOSE      
				output += "\r\n***Foot Motor STOPPED***\r\n";
#endif              
			}

			return false;


		}
		else if (myPS3->getButtonPress(L2) || myPS3->getButtonPress(L1))
		{

			if (!isFootMotorStopped)
			{
				ST->stop();
				isFootMotorStopped = true;
				footDriveSpeed = 0;

#ifdef SHADOW_VERBOSE      
				output += "\r\n***Foot Motor STOPPED***\r\n";
#endif

			}

			return false;

		}
		else
		{
			int joystickPosition = myPS3->getAnalogHat(LeftHatY);

			if (overSpeedSelected) //Over throttle is selected
			{

				stickSpeed = (map(joystickPosition, 0, 255, -drivespeed2, drivespeed2));

			}
			else
			{

				stickSpeed = (map(joystickPosition, 0, 255, -drivespeed1, drivespeed1));

			}

			if (abs(joystickPosition - 128) < joystickFootDeadZoneRange)
			{

				// This is RAMP DOWN code when stick is now at ZERO but prior FootSpeed > 20

				if (abs(footDriveSpeed) > 50)
				{
					if (footDriveSpeed > 0)
					{
						footDriveSpeed -= 3;
					}
					else
					{
						footDriveSpeed += 3;
					}

#ifdef SHADOW_VERBOSE1      
					output += "ZERO FAST RAMP: footSpeed: ";
					output += footDriveSpeed;
					output += "\nStick Speed: ";
					output += stickSpeed;
					output += "\n\r";
#endif

				}
				else if (abs(footDriveSpeed) > 20)
				{
					if (footDriveSpeed > 0)
					{
						footDriveSpeed -= 2;
					}
					else
					{
						footDriveSpeed += 2;
					}

#ifdef SHADOW_VERBOSE1      
					output += "ZERO MID RAMP: footSpeed: ";
					output += footDriveSpeed;
					output += "\nStick Speed: ";
					output += stickSpeed;
					output += "\n\r";
#endif

				}
				else
				{
					footDriveSpeed = 0;
				}

			}
			else
			{

				isFootMotorStopped = false;

				if (footDriveSpeed < stickSpeed)
				{

					if ((stickSpeed - footDriveSpeed)>(ramping + 1))
					{
						footDriveSpeed += ramping;

#ifdef SHADOW_VERBOSE1      
						output += "RAMPING UP: footSpeed: ";
						output += footDriveSpeed;
						output += "\nStick Speed: ";
						output += stickSpeed;
						output += "\n\r";
#endif

					}
					else
						footDriveSpeed = stickSpeed;

				}
				else if (footDriveSpeed > stickSpeed)
				{

					if ((footDriveSpeed - stickSpeed)>(ramping + 1))
					{

						footDriveSpeed -= ramping;

#ifdef SHADOW_VERBOSE1      
						output += "RAMPING DOWN: footSpeed: ";
						output += footDriveSpeed;
						output += "\nStick Speed: ";
						output += stickSpeed;
						output += "\n\r";
#endif

					}
					else
						footDriveSpeed = stickSpeed;
				}
				else
				{
					footDriveSpeed = stickSpeed;
				}
			}

			turnnum = (myPS3->getAnalogHat(LeftHatX));

			//TODO:  Is there a better algorithm here?  
			if (abs(footDriveSpeed) > 50)
				turnnum = (map(myPS3->getAnalogHat(LeftHatX), 54, 200, -(domeTurnSpeed / 4), (domeTurnSpeed / 4)));
			else if (turnnum <= 200 && turnnum >= 54)
				turnnum = (map(myPS3->getAnalogHat(LeftHatX), 54, 200, -(domeTurnSpeed / 3), (domeTurnSpeed / 3)));
			else if (turnnum > 200)
				turnnum = (map(myPS3->getAnalogHat(LeftHatX), 201, 255, domeTurnSpeed / 3, domeTurnSpeed));
			else if (turnnum < 54)
				turnnum = (map(myPS3->getAnalogHat(LeftHatX), 0, 53, -domeTurnSpeed, -(domeTurnSpeed / 3)));

			if (abs(turnnum) > 5)
			{
				isFootMotorStopped = false;
			}

			uint32_t footMillis = millis();

			if ((footMillis - previousFootMillis) > serialLatency)
			{

				if (footDriveSpeed != 0 || abs(turnnum) > 5)
				{

#ifdef SHADOW_VERBOSE      
					output += "Motor: FootSpeed: ";
					output += footDriveSpeed;
					output += "  Turnnum: ";
					output += turnnum;
					output += "  @ ";
					output += millis();
#endif

					ST->turn(turnnum * invertTurnDirection);
					ST->drive(footDriveSpeed* invertSpeedDirection);

				}
				else
				{
					if (!isFootMotorStopped)
					{
						ST->stop();
						isFootMotorStopped = true;
						footDriveSpeed = 0;

#ifdef SHADOW_VERBOSE      
						output += "\r\n***Foot Motor STOPPED***\r\n";
#endif
					}
				}

				// The Sabertooth won't act on mixed mode packet serial commands until
				// it has received power levels for BOTH throttle and turning, since it
				// mixes the two together to get diff-drive power levels for both motors.

				previousFootMillis = footMillis;
				return true; //we sent a foot command   
			}
		}
	}
	return false;
}

uint32_t relayMillis = 0;
void motorRelays()
{
	if (currentMillis - relayMillis > 1000) {
		if (isStickEnabled) {
			digitalWrite(pinOut_MotorLeftEnableRelay, HIGH);
			digitalWrite(pinOut_MotorRightEnableRelay, HIGH);
			digitalWrite(pinOut_MotorDomeEnableRelay, HIGH);
		}
		else {
			digitalWrite(pinOut_MotorLeftEnableRelay, LOW);
			digitalWrite(pinOut_MotorRightEnableRelay, LOW);
			digitalWrite(pinOut_MotorDomeEnableRelay, LOW);
		}
		relayMillis = currentMillis;
	}
}

void footMotorDrive()
{

	//Flood control prevention
	if ((millis() - previousFootMillis) < serialLatency) return;

	if (PS3NavFoot->PS3NavigationConnected) ps3FootMotorDrive(PS3NavFoot);

}


// =======================================================================================
//           domeDrive Motor Control Section
// =======================================================================================

int ps3DomeDrive(PS3BT* myPS3 = PS3NavDome)
{
	int domeRotationSpeed = 0;
	int newDomeRotationSpeed = 0;
	int targetDomeRotationSpeed = 0;
	static long lastDomePrintmillis = 0;
	int joystickPosition = myPS3->getAnalogHat(LeftHatX);

	newDomeRotationSpeed = (map(joystickPosition, 0, 255, -(domespeed+ joystickDomeDeadZoneRange), (domespeed+ joystickDomeDeadZoneRange)));

	if ((newDomeRotationSpeed > -joystickDomeDeadZoneRange && newDomeRotationSpeed < joystickDomeDeadZoneRange))  targetDomeRotationSpeed = 0; else targetDomeRotationSpeed = newDomeRotationSpeed - (joystickDomeDeadZoneRange * (newDomeRotationSpeed < 1 ? -1 : 1));
	if (currentMillis - lastDomePrintmillis > 200) {
		//Serial.println("targetDomeRotationSpeed " + String(targetDomeRotationSpeed) + ":" + String(joystickPosition));
		lastDomePrintmillis = millis();
	}

	domeRotationSpeed = (map(joystickPosition, 0, 255, -domespeed, domespeed));


	if (abs(joystickPosition - 128) < joystickDomeDeadZoneRange)
		domeRotationSpeed = 0;

	domeRotationSpeed = targetDomeRotationSpeed;

	if (domeRotationSpeed != 0 && domeAutomation == true)  // Turn off dome automation if manually moved
	{
		domeAutomation = false;
		domeStatus = 0;
		domeTargetPosition = 0;

#ifdef SHADOW_VERBOSE
		output += "Dome Automation OFF\r\n";
#endif

	}

	return domeRotationSpeed;
}




void rotateDome(int domeRotationSpeed, String mesg)
{
	//Constantly sending commands to the SyRen (Dome) is causing foot motor delay.
	//Lets reduce that chatter by trying 3 things:
	// 1.) Eliminate a constant stream of "don't spin" messages (isDomeMotorStopped flag)
	// 2.) Add a delay between commands sent to the SyRen (previousDomeMillis timer)
	// 3.) Switch to real UART on the MEGA (Likely the *CORE* issue and solution)
	// 4.) Reduce the timout of the SyRen - just better for safety!

	uint32_t domeMillis = millis();
	if ((!isDomeMotorStopped || domeRotationSpeed != 0) && ((domeMillis - previousDomeMillis) > (2 * serialLatency)))
	{

		if (domeRotationSpeed != 0)
		{

			isDomeMotorStopped = false;

#ifdef SHADOW_VERBOSE      
			//output += "Dome rotation speed: ";
			//output += domeRotationSpeed;
#endif

			SyR->motor(domeRotationSpeed);

		}
		else
		{
			isDomeMotorStopped = true;

#ifdef SHADOW_VERBOSE      
			output += "\n\r***Dome motor is STOPPED***\n\r";
#endif

			SyR->stop();
		}

		previousDomeMillis = domeMillis;
	}
}

void domeMotorDrive()
{
	//Flood control prevention
	//This is intentionally set to double the rate of the Dome Motor Latency
	if ((millis() - previousDomeMillis) < (2 * serialLatency)) return;

	int domeRotationSpeed = 0;
	int ps3NavControlSpeed = 0;

	if (PS3NavDome->PS3NavigationConnected)
	{

		ps3NavControlSpeed = ps3DomeDrive(PS3NavDome);

		domeRotationSpeed = ps3NavControlSpeed;

		rotateDome(domeRotationSpeed, "Controller Move");

	}
	else if (PS3NavFoot->PS3NavigationConnected && PS3NavFoot->getButtonPress(L2))
	{

		ps3NavControlSpeed = ps3DomeDrive(PS3NavFoot);

		domeRotationSpeed = ps3NavControlSpeed;

		rotateDome(domeRotationSpeed, "Controller Move");

	}
	else
	{
		if (!isDomeMotorStopped)
		{
			SyR->stop();
			isDomeMotorStopped = true;
		}
	}
}

// =======================================================================================
//                               Toggle Control Section
// =======================================================================================

void ps3ToggleSettings(PS3BT* myPS3 = PS3NavFoot)
{

	// enable / disable drive stick
	if (myPS3->getButtonPress(PS) && myPS3->getButtonClick(CROSS))
	{

#ifdef SHADOW_DEBUG
		output += "Disabling the DriveStick\r\n";
		output += "Stopping Motors";
#endif

		ST->stop();
		isFootMotorStopped = true;
		isStickEnabled = false;
		footDriveSpeed = 0;
	}

	if (myPS3->getButtonPress(PS) && myPS3->getButtonClick(CIRCLE))
	{
#ifdef SHADOW_DEBUG
		output += "Enabling the DriveStick\r\n";
#endif
		isStickEnabled = true;
	}

	// Enable and Disable Overspeed
	if (myPS3->getButtonPress(L3) && myPS3->getButtonPress(L1) && isStickEnabled)
	{

		if ((millis() - previousSpeedToggleMillis) > 1000)
		{
			speedToggleButtonCounter = 0;
			previousSpeedToggleMillis = millis();
		}

		speedToggleButtonCounter += 1;

		if (speedToggleButtonCounter == 1)
		{

			if (!overSpeedSelected)
			{

				overSpeedSelected = true;

#ifdef SHADOW_VERBOSE      
				output += "Over Speed is now: ON";
#endif

			}
			else
			{
				overSpeedSelected = false;

#ifdef SHADOW_VERBOSE      
				output += "Over Speed is now: OFF";
#endif   
			}
		}
	}

	// Enable Disable Dome Automation
	if (myPS3->getButtonPress(L2) && myPS3->getButtonClick(CROSS))
	{
		domeAutomation = false;
		domeStatus = 0;
		domeTargetPosition = 0;
		SyR->stop();
		isDomeMotorStopped = true;

#ifdef SHADOW_DEBUG
		output += "Dome Automation OFF\r\n";
#endif
	}

	if (myPS3->getButtonPress(L2) && myPS3->getButtonClick(CIRCLE))
	{
		domeAutomation = true;

#ifdef SHADOW_DEBUG
		output += "Dome Automation On\r\n";
#endif
	}

}

void toggleSettings()
{
	if (PS3NavFoot->PS3NavigationConnected) ps3ToggleSettings(PS3NavFoot);
}

// =======================================================================================
// This is the main MarcDuino Button Management Function
// =======================================================================================
void marcDuinoButtonPush(int type, int MD_func, int MP3_num, int LD_type, String LD_text, int panel_type,
	boolean use_DP1,
	int DP1_str_delay,
	int DP1_open_time,
	boolean use_DP2,
	int DP2_str_delay,
	int DP2_open_time,
	boolean use_DP3,
	int DP3_str_delay,
	int DP3_open_time,
	boolean use_DP4,
	int DP4_str_delay,
	int DP4_open_time,
	boolean use_DP5,
	int DP5_str_delay,
	int DP5_open_time,
	boolean use_DP6,
	int DP6_str_delay,
	int DP6_open_time,
	boolean use_DP7,
	int DP7_str_delay,
	int DP7_open_time,
	boolean use_DP8,
	int DP8_str_delay,
	int DP8_open_time,
	boolean use_DP9,
	int DP9_str_delay,
	int DP9_open_time,
	boolean use_DP10,
	int DP10_str_delay,
	int DP10_open_time)
{

	if (type == 1)  // Std Marcduino Function Call Configured
	{
		String serial1Cmd = "",serial3Cmd = "";
		switch (MD_func)
		{
		case 1:
			serial1Cmd = (":SE00\r"); // 
			break;

		case 2:
			serial1Cmd = (":SE01\r"); // Scream, with all panels open

			break;

		case 3:
			serial1Cmd = (":SE02\r"); // Wave, one panel at a time

			break;

		case 4:
			serial1Cmd = (":SE03\r"); // Fast (Smirk) back and forth wave

			break;

		case 5:
			serial1Cmd = (":SE04\r"); // Wave 2 (open progressively all panels, then close one by one)

			break;

		case 6:
			serial1Cmd = (":SE05\r"); // Beep Cantina (with marching ants panel action)

			break;

		case 7:
			serial1Cmd = (":SE06\r"); // Faint/Short Circuit

			break;

		case 8:
			serial1Cmd = (":SE07\r"); // Cantina dance (orchestral, rythmic panel dance)
			break;

		case 9:
			serial1Cmd = (":SE08\r"); // Leia
			break;

		case 10:
			serial1Cmd = (":SE09\r"); // Disco
			break;

		case 11:
			serial1Cmd = (":SE10\r"); // Quite Mode reset (panel close, stop holos, stop sounds)

			break;

		case 12:
			serial1Cmd = (":SE11\r"); // Full Awake Mode reset (panel close, random sound, holo movement, no holo lights)

			break;

		case 13:
			serial1Cmd = (":SE13\r"); // Mid Awake Mode reset (panel close, random sound, stop holos)

			break;

		case 14:
			serial1Cmd = (":SE14\r"); // Awake+ Mode reset ((panel close, random sound, holo movement, lights on)

			break;

		case 15:
			serial1Cmd = (":SE51\r"); // Scream, with all panels open

			break;

		case 16:
			serial1Cmd = (":SE52\r"); // Wave, one panel at a time

			break;

		case 17:
			serial1Cmd = (":SE53\r"); // Fast (Smirk) back and forth wave

			break;

		case 18:
			serial1Cmd = (":SE54\r"); // Wave 2 (open progressively all panels, then close one by one)

			break;

		case 19:
			serial1Cmd = (":SE55\r"); // Marching ants

			break;

		case 20:
			serial1Cmd = (":SE56\r"); // Faint/Short Circuit

			break;

		case 21:
			serial1Cmd = (":SE57\r"); // Rythmic panel dance)

			break;

		case 22:
			serial1Cmd = ("*RD00\r"); // all holos to random

			break;

		case 23:
			serial1Cmd = ("*ON00\r"); // holo lights on
			break;

		case 24:
			serial1Cmd = ("*OF00\r"); 
			break;

		case 25:
			serial1Cmd = ("*ST00\r"); // all holos to stop and lights off

			break;

		case 26:
			serial1Cmd = ("$+\r");
			serial1Cmd = ("3V" + String(map(soundVolume,-70,4,0,100) )+ "\r");
			break;

		case 27:
			serial1Cmd = ("$-\r");
			serial1Cmd = ("3V" + String(map(soundVolume,-70,4,0,100) )+ "\r");
			break;

		case 28:
			serial1Cmd = ("$f\r");
			break;

		case 29:
			serial1Cmd = ("$m\r");
			break;

		case 30:
			serial1Cmd = (":OP00\r");
			break;

		case 31:
			serial1Cmd = (":OP11\r");
			break;

		case 32:
			serial1Cmd = (":OP12\r");
			break;

		case 33:
			serial1Cmd = (":CL00\r");
			break;

		case 34:
			serial1Cmd = (":OP01\r");
			break;

		case 35:
			serial1Cmd = (":CL01\r");
			break;

		case 36:
			serial1Cmd = (":OP02\r");
			break;

		case 37:
			serial1Cmd = (":CL02\r");
			break;

		case 38:
			serial1Cmd = (":OP03\r");
			break;

		case 39:
			serial1Cmd = (":CL03\r");
			break;

		case 40:
			serial1Cmd = (":OP04\r");
			break;

		case 41:
			serial1Cmd = (":CL04\r");
			break;

		case 42:
			serial1Cmd = (":OP05\r");
			break;

		case 43:
			serial1Cmd = (":CL05\r");
			break;

		case 44:
			serial1Cmd = (":OP06\r");
			break;

		case 45:
			serial1Cmd = (":CL06\r");
			break;

		case 46:
			serial1Cmd = (":OP07\r");
			break;

		case 47:
			serial1Cmd = (":CL07\r");
			break;

		case 48:
			serial1Cmd = (":OP08\r");
			break;

		case 49:
			serial1Cmd = (":CL08\r");
			break;

		case 50:
			serial1Cmd = (":OP09\r");
			break;

		case 51:
			serial1Cmd = (":CL09\r");
			break;

		case 52:
			serial1Cmd = (":OP10\r");
			break;

		case 53:
			serial1Cmd = (":CL10\r");
			break;

		case 54:
			serial3Cmd = (":OP00\r");
			break;

		case 55:
			serial3Cmd = (":CL00\r");
			break;

		case 56:
			serial3Cmd = (":OP01\r");
			break;

		case 57:
			serial3Cmd = (":CL01\r");
			break;

		case 58:
			serial3Cmd = (":OP02\r");
			break;

		case 59:
			serial3Cmd = (":CL02\r");
			break;

		case 60:
			serial3Cmd = (":OP03\r");
			break;

		case 61:
			serial3Cmd = (":CL03\r");
			break;

		case 62:
			serial3Cmd = (":OP04\r");
			break;

		case 63:
			serial3Cmd = (":CL04\r");
			break;

		case 64:
			serial3Cmd = (":OP05\r");
			break;

		case 65:
			serial3Cmd = (":CL05\r");
			break;

		case 66:
			serial3Cmd = (":OP06\r");
			break;

		case 67:
			serial3Cmd = (":CL06\r");
			break;

		case 68:
			serial3Cmd = (":OP07\r");
			break;

		case 69:
			serial3Cmd = (":CL07\r");
			break;

		case 70:
			serial3Cmd = (":OP08\r");
			break;

		case 71:
			serial3Cmd = (":CL08\r");
			break;

		case 72:
			serial3Cmd = (":OP09\r");
			break;

		case 73:
			serial3Cmd = (":CL09\r");
			break;

		case 74:
			serial3Cmd = (":OP10\r");
			break;

		case 75:
			serial3Cmd = (":CL10\r");
			break;

		case 76:
			serial3Cmd = ("*MO99\r");
			break;

		case 77:
			serial3Cmd = ("*MO00\r");
			break;

		case 78:
			serial3Cmd = ("*MF10\r");
			break;

		}
		if (serial1Cmd.length() > 0 ) {
			DomePanelController.print(serial1Cmd);
			output += "\DomePanelController:" + serial1Cmd;
		}
		if (serial3Cmd.length() > 0) {
			BodyPanelController.print(serial3Cmd);
			output += "\BodyPanelController:" + serial3Cmd;
		}

	}  // End Std Marcduino Function Calls


	if (type == 2) // Custom Button Configuration
	{

		if (MP3_num > 181 && MP3_num < 201) // Valid Custom Sound Range Selected - Play Custom Sound Selection
		{
			String serial1Cmd = "";
			switch (MP3_num)
			{

			case 182:
				serial1Cmd = ("$87\r");
				break;

			case 183:
				serial1Cmd = ("$88\r");
				break;

			case 184:
				serial1Cmd = ("$89\r");
				break;

			case 185:
				serial1Cmd = ("$810\r");
				break;

			case 186:
				serial1Cmd = ("$811\r");
				break;

			case 187:
				serial1Cmd = ("$812\r");
				break;
			case 188:
				serial1Cmd = ("$813\r");
				break;

			case 189:
				serial1Cmd = ("$814\r");
				break;

			case 190:
				serial1Cmd = ("$815\r");
				break;

			case 191:
				serial1Cmd = ("$816\r");
				break;

			case 192:
				serial1Cmd = ("$817\r");
				break;

			case 193:
				serial1Cmd = ("$818\r");
				break;

			case 194:
				serial1Cmd = ("$819\r");
				break;

			case 195:
				serial1Cmd = ("$820\r");
				break;

			case 196:
				serial1Cmd = ("$821\r");
				break;

			case 197:
				serial1Cmd = ("$822\r");
				break;

			case 198:
				serial1Cmd = ("$823\r");
				break;

			case 199:
				serial1Cmd = ("$824\r");
				break;

			case 200:
				serial1Cmd = ("$825\r");
				break;

			}
			
			if (serial1Cmd.length() > 0 ) {
			DomePanelController.print(serial1Cmd);
			output += "\DomePanelController:" + serial1Cmd;
		}

		}

		if (panel_type > 0 && panel_type < 10) // Valid panel type selected - perform custom panel functions
		{

			// Reset the custom panel flags
			DP1_Status = 0;
			DP2_Status = 0;
			DP3_Status = 0;
			DP4_Status = 0;
			DP5_Status = 0;
			DP6_Status = 0;
			DP7_Status = 0;
			DP8_Status = 0;
			DP9_Status = 0;
			DP10_Status = 0;

			String serial1Cmd = "";

			if (panel_type > 1)
			{
				Serial1.print(":CL00\r");  // close all the panels prior to next custom routine
				delay(50); // give panel close command time to process before starting next panel command 
			}
			switch (panel_type)
			{

			case 1:
				serial1Cmd = (":CL00\r");
				break;

			case 2:
				serial1Cmd = (":SE51\r");
				break;

			case 3:
				serial1Cmd = (":SE52\r");
				break;

			case 4:
				serial1Cmd = (":SE53\r");
				break;

			case 5:
				serial1Cmd = (":SE54\r");
				break;

			case 6:
				serial1Cmd = (":SE55\r");
				break;

			case 7:
				serial1Cmd = (":SE56\r");
				break;

			case 8:
				serial1Cmd = (":SE57\r");
				break;

			case 9: // This is the setup section for the custom panel routines

				runningCustRoutine = true;

				// Configure Dome Panel #1
				if (use_DP1)
				{

					DP1_Status = 1;
					DP1_start = millis();

					if (DP1_str_delay < 31)
					{

						DP1_s_delay = DP1_str_delay;

					}
					else
					{
						DP1_Status = 0;
					}

					if (DP1_open_time > 0 && DP1_open_time < 31)
					{

						DP1_o_time = DP1_open_time;

					}
					else
					{
						DP1_Status = 0;
					}

				}

				// Configure Dome Panel #2
				if (use_DP2)
				{

					DP2_Status = 1;
					DP2_start = millis();

					if (DP2_str_delay < 31)
					{

						DP2_s_delay = DP2_str_delay;

					}
					else
					{
						DP2_Status = 0;
					}

					if (DP2_open_time > 0 && DP2_open_time < 31)
					{

						DP2_o_time = DP2_open_time;

					}
					else
					{
						DP2_Status = 0;
					}

				}


				// Configure Dome Panel #3
				if (use_DP3)
				{

					DP3_Status = 1;
					DP3_start = millis();

					if (DP3_str_delay < 31)
					{

						DP3_s_delay = DP3_str_delay;

					}
					else
					{
						DP3_Status = 0;
					}

					if (DP3_open_time > 0 && DP3_open_time < 31)
					{

						DP3_o_time = DP3_open_time;

					}
					else
					{
						DP3_Status = 0;
					}

				}

				// Configure Dome Panel #4
				if (use_DP4)
				{

					DP4_Status = 1;
					DP4_start = millis();

					if (DP4_str_delay < 31)
					{

						DP4_s_delay = DP4_str_delay;

					}
					else
					{
						DP4_Status = 0;
					}

					if (DP4_open_time > 0 && DP4_open_time < 31)
					{

						DP4_o_time = DP4_open_time;

					}
					else
					{
						DP4_Status = 0;
					}

				}

				// Configure Dome Panel #5
				if (use_DP5)
				{

					DP5_Status = 1;
					DP5_start = millis();

					if (DP5_str_delay < 31)
					{

						DP5_s_delay = DP5_str_delay;

					}
					else
					{
						DP5_Status = 0;
					}

					if (DP5_open_time > 0 && DP5_open_time < 31)
					{

						DP5_o_time = DP5_open_time;

					}
					else
					{
						DP5_Status = 0;
					}

				}

				// Configure Dome Panel #6
				if (use_DP6)
				{

					DP6_Status = 1;
					DP6_start = millis();

					if (DP6_str_delay < 31)
					{

						DP6_s_delay = DP6_str_delay;

					}
					else
					{
						DP6_Status = 0;
					}

					if (DP6_open_time > 0 && DP6_open_time < 31)
					{

						DP6_o_time = DP6_open_time;

					}
					else
					{
						DP6_Status = 0;
					}

				}

				// Configure Dome Panel #7
				if (use_DP7)
				{

					DP7_Status = 1;
					DP7_start = millis();

					if (DP7_str_delay < 31)
					{

						DP7_s_delay = DP7_str_delay;

					}
					else
					{
						DP7_Status = 0;
					}

					if (DP7_open_time > 0 && DP7_open_time < 31)
					{

						DP7_o_time = DP7_open_time;

					}
					else
					{
						DP7_Status = 0;
					}

				}

				// Configure Dome Panel #8
				if (use_DP8)
				{

					DP8_Status = 1;
					DP8_start = millis();

					if (DP8_str_delay < 31)
					{

						DP8_s_delay = DP8_str_delay;

					}
					else
					{
						DP8_Status = 0;
					}

					if (DP8_open_time > 0 && DP8_open_time < 31)
					{

						DP8_o_time = DP8_open_time;

					}
					else
					{
						DP8_Status = 0;
					}

				}

				// Configure Dome Panel #9
				if (use_DP9)
				{

					DP9_Status = 1;
					DP9_start = millis();

					if (DP9_str_delay < 31)
					{

						DP9_s_delay = DP9_str_delay;

					}
					else
					{
						DP9_Status = 0;
					}

					if (DP9_open_time > 0 && DP9_open_time < 31)
					{

						DP9_o_time = DP9_open_time;

					}
					else
					{
						DP9_Status = 0;
					}

				}

				// Configure Dome Panel #10
				if (use_DP10)
				{

					DP10_Status = 1;
					DP10_start = millis();

					if (DP10_str_delay < 31)
					{

						DP10_s_delay = DP10_str_delay;

					}
					else
					{
						DP10_Status = 0;
					}

					if (DP10_open_time > 0 && DP10_open_time < 31)
					{

						DP10_o_time = DP10_open_time;

					}
					else
					{
						DP10_Status = 0;
					}

				}

				// If every dome panel config failed to work - reset routine flag to false
				if (DP1_Status + DP2_Status + DP3_Status + DP4_Status + DP5_Status + DP6_Status + DP7_Status + DP8_Status + DP9_Status + DP10_Status == 0)
				{

					runningCustRoutine = false;

				}

				break;
			}
			if (serial1Cmd.length() > 0) {
				DomePanelController.print(serial1Cmd);
				output += "\DomePanelController:" + serial1Cmd;
			}

		}


		if (LD_type > 0 && LD_type < 9) // Valid Logic Display Selected - Display Custom Logic Display
		{

			if (panel_type > 1 && panel_type < 10)  // If a custom panel movement was selected - need to briefly pause before changing light sequence to avoid conflict)
			{
				delay(30);
			}
			String serial1Cmd = "";
			switch (LD_type) {

				case 1:
					serial1Cmd = "@0T1\r";
					break;

				case 2:
					serial1Cmd = "@0T4\r";
					break;

				case 3:
					serial1Cmd = "@0T5\r";
					break;

				case 4:
					serial1Cmd = "@0T6\r";
					break;

				case 5:
					serial1Cmd = "@0T10\r";
					break;

				case 6:
					serial1Cmd = "@0T11\r";
					break;

				case 7:
					serial1Cmd = "@0T92\r";
					break;

				case 8:
					serial1Cmd = "@0T100\r";
					//delay(50);
					String custString = "@0M";
					custString += LD_text;
					custString += "\r";
					serial1Cmd+=custString;

					break;
			}
			if (serial1Cmd.length() > 0) {
				DomePanelController.print(serial1Cmd);
				output += "\DomePanelController:" + serial1Cmd;
			}
		}

	}

}

// ====================================================================================================================
// This function determines if MarcDuino buttons were selected and calls main processing function for FOOT controller
// ====================================================================================================================
void marcDuinoFoot()
{
	if (PS3NavFoot->PS3NavigationConnected && (PS3NavFoot->getButtonPress(UP) || PS3NavFoot->getButtonPress(DOWN) || PS3NavFoot->getButtonPress(LEFT) || PS3NavFoot->getButtonPress(RIGHT)))
	{

		if ((millis() - previousMarcDuinoMillis) > 125)
		{
			marcDuinoButtonCounter = 0;
			previousMarcDuinoMillis = millis();
		}
		else {
			//#ifdef SHADOW_VERBOSE      
			//     output += "marcDuinoFoot:ignore";
			//#endif

		}

		marcDuinoButtonCounter += 1;

	}
	else
	{

		return;
	}

	// Clear inbound buffer of any data sent form the MarcDuino board
	while (Serial1.available()) Serial1.read();
	
	//------------------------------------ 
	// Send triggers for the base buttons 
	//------------------------------------
	if (PS3NavFoot->getButtonPress(UP) && !PS3NavFoot->getButtonPress(CROSS) && !PS3NavFoot->getButtonPress(CIRCLE) && !PS3NavFoot->getButtonPress(L1) && !PS3NavFoot->getButtonPress(PS) && marcDuinoButtonCounter == 1)
	{

		if (PS3NavDome->PS3NavigationConnected && (PS3NavDome->getButtonPress(CROSS) || PS3NavDome->getButtonPress(CIRCLE) || PS3NavDome->getButtonPress(PS)))
		{
			// Skip this section
		}
		else
		{
			marcDuinoButtonPush(btnUP_type, btnUP_MD_func, btnUP_cust_MP3_num, btnUP_cust_LD_type, btnUP_cust_LD_text, btnUP_cust_panel,
				btnUP_use_DP1,
				btnUP_DP1_open_start_delay,
				btnUP_DP1_stay_open_time,
				btnUP_use_DP2,
				btnUP_DP2_open_start_delay,
				btnUP_DP2_stay_open_time,
				btnUP_use_DP3,
				btnUP_DP3_open_start_delay,
				btnUP_DP3_stay_open_time,
				btnUP_use_DP4,
				btnUP_DP4_open_start_delay,
				btnUP_DP4_stay_open_time,
				btnUP_use_DP5,
				btnUP_DP5_open_start_delay,
				btnUP_DP5_stay_open_time,
				btnUP_use_DP6,
				btnUP_DP6_open_start_delay,
				btnUP_DP6_stay_open_time,
				btnUP_use_DP7,
				btnUP_DP7_open_start_delay,
				btnUP_DP7_stay_open_time,
				btnUP_use_DP8,
				btnUP_DP8_open_start_delay,
				btnUP_DP8_stay_open_time,
				btnUP_use_DP9,
				btnUP_DP9_open_start_delay,
				btnUP_DP9_stay_open_time,
				btnUP_use_DP10,
				btnUP_DP10_open_start_delay,
				btnUP_DP10_stay_open_time);

#ifdef SHADOW_VERBOSE      
			output += "\nFOOT: btnUP";
#ifdef SOUND_WAVTRIGGER
			trigger.trackPlaySolo(6);
#endif
#endif

			return;

		}

	}

	if (PS3NavFoot->getButtonPress(DOWN) && !PS3NavFoot->getButtonPress(CROSS) && !PS3NavFoot->getButtonPress(CIRCLE) && !PS3NavFoot->getButtonPress(L1) && !PS3NavFoot->getButtonPress(PS) && marcDuinoButtonCounter == 1)
	{

		if (PS3NavDome->PS3NavigationConnected && (PS3NavDome->getButtonPress(CROSS) || PS3NavDome->getButtonPress(CIRCLE) || PS3NavDome->getButtonPress(PS)))
		{
			// Skip this section
		}
		else
		{
			marcDuinoButtonPush(btnDown_type, btnDown_MD_func, btnDown_cust_MP3_num, btnDown_cust_LD_type, btnDown_cust_LD_text, btnDown_cust_panel,
				btnDown_use_DP1,
				btnDown_DP1_open_start_delay,
				btnDown_DP1_stay_open_time,
				btnDown_use_DP2,
				btnDown_DP2_open_start_delay,
				btnDown_DP2_stay_open_time,
				btnDown_use_DP3,
				btnDown_DP3_open_start_delay,
				btnDown_DP3_stay_open_time,
				btnDown_use_DP4,
				btnDown_DP4_open_start_delay,
				btnDown_DP4_stay_open_time,
				btnDown_use_DP5,
				btnDown_DP5_open_start_delay,
				btnDown_DP5_stay_open_time,
				btnDown_use_DP6,
				btnDown_DP6_open_start_delay,
				btnDown_DP6_stay_open_time,
				btnDown_use_DP7,
				btnDown_DP7_open_start_delay,
				btnDown_DP7_stay_open_time,
				btnDown_use_DP8,
				btnDown_DP8_open_start_delay,
				btnDown_DP8_stay_open_time,
				btnDown_use_DP9,
				btnDown_DP9_open_start_delay,
				btnDown_DP9_stay_open_time,
				btnDown_use_DP10,
				btnDown_DP10_open_start_delay,
				btnDown_DP10_stay_open_time);

#ifdef SHADOW_VERBOSE      
			output += "\nFOOT: btnDown";
#ifdef SOUND_WAVTRIGGER
			trigger.trackPlaySolo(5);
#endif
#endif


			return;
		}
	}

	if (PS3NavFoot->getButtonPress(LEFT) && !PS3NavFoot->getButtonPress(CROSS) && !PS3NavFoot->getButtonPress(CIRCLE) && !PS3NavFoot->getButtonPress(L1) && !PS3NavFoot->getButtonPress(PS) && marcDuinoButtonCounter == 1)
	{
		if (PS3NavDome->PS3NavigationConnected && (PS3NavDome->getButtonPress(CROSS) || PS3NavDome->getButtonPress(CIRCLE) || PS3NavDome->getButtonPress(PS)))
		{
			// Skip this section
		}
		else
		{
			marcDuinoButtonPush(btnLeft_type, btnLeft_MD_func, btnLeft_cust_MP3_num, btnLeft_cust_LD_type, btnLeft_cust_LD_text, btnLeft_cust_panel,
				btnLeft_use_DP1,
				btnLeft_DP1_open_start_delay,
				btnLeft_DP1_stay_open_time,
				btnLeft_use_DP2,
				btnLeft_DP2_open_start_delay,
				btnLeft_DP2_stay_open_time,
				btnLeft_use_DP3,
				btnLeft_DP3_open_start_delay,
				btnLeft_DP3_stay_open_time,
				btnLeft_use_DP4,
				btnLeft_DP4_open_start_delay,
				btnLeft_DP4_stay_open_time,
				btnLeft_use_DP5,
				btnLeft_DP5_open_start_delay,
				btnLeft_DP5_stay_open_time,
				btnLeft_use_DP6,
				btnLeft_DP6_open_start_delay,
				btnLeft_DP6_stay_open_time,
				btnLeft_use_DP7,
				btnLeft_DP7_open_start_delay,
				btnLeft_DP7_stay_open_time,
				btnLeft_use_DP8,
				btnLeft_DP8_open_start_delay,
				btnLeft_DP8_stay_open_time,
				btnLeft_use_DP9,
				btnLeft_DP9_open_start_delay,
				btnLeft_DP9_stay_open_time,
				btnLeft_use_DP10,
				btnLeft_DP10_open_start_delay,
				btnLeft_DP10_stay_open_time);

#ifdef SHADOW_VERBOSE      
			output += "\nFOOT: btnLeft";
#ifdef SOUND_WAVTRIGGER
			trigger.trackPlaySolo(soundFileNo);
#endif // SOUND_WAVTRIGGER


#endif

			return;
		}

	}

	if (PS3NavFoot->getButtonPress(RIGHT) && !PS3NavFoot->getButtonPress(CROSS) && !PS3NavFoot->getButtonPress(CIRCLE) && !PS3NavFoot->getButtonPress(L1) && !PS3NavFoot->getButtonPress(PS) && marcDuinoButtonCounter == 1)
	{

		if (PS3NavDome->PS3NavigationConnected && (PS3NavDome->getButtonPress(CROSS) || PS3NavDome->getButtonPress(CIRCLE) || PS3NavDome->getButtonPress(PS)))
		{
			// Skip this section
		}
		else
		{
			marcDuinoButtonPush(btnRight_type, btnRight_MD_func, btnRight_cust_MP3_num, btnRight_cust_LD_type, btnRight_cust_LD_text, btnRight_cust_panel,
				btnRight_use_DP1,
				btnRight_DP1_open_start_delay,
				btnRight_DP1_stay_open_time,
				btnRight_use_DP2,
				btnRight_DP2_open_start_delay,
				btnRight_DP2_stay_open_time,
				btnRight_use_DP3,
				btnRight_DP3_open_start_delay,
				btnRight_DP3_stay_open_time,
				btnRight_use_DP4,
				btnRight_DP4_open_start_delay,
				btnRight_DP4_stay_open_time,
				btnRight_use_DP5,
				btnRight_DP5_open_start_delay,
				btnRight_DP5_stay_open_time,
				btnRight_use_DP6,
				btnRight_DP6_open_start_delay,
				btnRight_DP6_stay_open_time,
				btnRight_use_DP7,
				btnRight_DP7_open_start_delay,
				btnRight_DP7_stay_open_time,
				btnRight_use_DP8,
				btnRight_DP8_open_start_delay,
				btnRight_DP8_stay_open_time,
				btnRight_use_DP9,
				btnRight_DP9_open_start_delay,
				btnRight_DP9_stay_open_time,
				btnRight_use_DP10,
				btnRight_DP10_open_start_delay,
				btnRight_DP10_stay_open_time);

#ifdef SHADOW_VERBOSE      
			output += "\nFOOT: btnRight";
#ifdef SOUND_WAVTRIGGER
			trigger.trackPlaySolo(3);
#endif
#endif


			return;
		}

	}

	//------------------------------------ 
	// Send triggers for the CROSS + base buttons 
	//------------------------------------
	if (((!PS3NavDome->PS3NavigationConnected && PS3NavFoot->getButtonPress(UP) && PS3NavFoot->getButtonPress(CROSS)) || (PS3NavDome->PS3NavigationConnected && PS3NavFoot->getButtonPress(UP) && PS3NavDome->getButtonPress(CROSS))) && marcDuinoButtonCounter == 1)
	{
		soundVolume+=5;
		soundVolume = min(soundVolume, 4);

		trigger.masterGain(soundVolume);

		marcDuinoButtonPush(btnUP_CROSS_type, btnUP_CROSS_MD_func, btnUP_CROSS_cust_MP3_num, btnUP_CROSS_cust_LD_type, btnUP_CROSS_cust_LD_text, btnUP_CROSS_cust_panel,
			btnUP_CROSS_use_DP1,
			btnUP_CROSS_DP1_open_start_delay,
			btnUP_CROSS_DP1_stay_open_time,
			btnUP_CROSS_use_DP2,
			btnUP_CROSS_DP2_open_start_delay,
			btnUP_CROSS_DP2_stay_open_time,
			btnUP_CROSS_use_DP3,
			btnUP_CROSS_DP3_open_start_delay,
			btnUP_CROSS_DP3_stay_open_time,
			btnUP_CROSS_use_DP4,
			btnUP_CROSS_DP4_open_start_delay,
			btnUP_CROSS_DP4_stay_open_time,
			btnUP_CROSS_use_DP5,
			btnUP_CROSS_DP5_open_start_delay,
			btnUP_CROSS_DP5_stay_open_time,
			btnUP_CROSS_use_DP6,
			btnUP_CROSS_DP6_open_start_delay,
			btnUP_CROSS_DP6_stay_open_time,
			btnUP_CROSS_use_DP7,
			btnUP_CROSS_DP7_open_start_delay,
			btnUP_CROSS_DP7_stay_open_time,
			btnUP_CROSS_use_DP8,
			btnUP_CROSS_DP8_open_start_delay,
			btnUP_CROSS_DP8_stay_open_time,
			btnUP_CROSS_use_DP9,
			btnUP_CROSS_DP9_open_start_delay,
			btnUP_CROSS_DP9_stay_open_time,
			btnUP_CROSS_use_DP10,
			btnUP_CROSS_DP10_open_start_delay,
			btnUP_CROSS_DP10_stay_open_time);

#ifdef SHADOW_VERBOSE
		output += "\nFOOT: btnUP_CROSS + VOL: " + String(soundVolume);
#endif


		return;

	}

	if (((!PS3NavDome->PS3NavigationConnected && PS3NavFoot->getButtonPress(DOWN) && PS3NavFoot->getButtonPress(CROSS)) || (PS3NavDome->PS3NavigationConnected && PS3NavFoot->getButtonPress(DOWN) && PS3NavDome->getButtonPress(CROSS))) && marcDuinoButtonCounter == 1)
	{
		soundVolume-=5;
		soundVolume = max(soundVolume, -70);
		//if (soundVolume < -70) soundVolume = -70;
		trigger.masterGain(soundVolume);

		marcDuinoButtonPush(btnDown_CROSS_type, btnDown_CROSS_MD_func, btnDown_CROSS_cust_MP3_num, btnDown_CROSS_cust_LD_type, btnDown_CROSS_cust_LD_text, btnDown_CROSS_cust_panel,
			btnDown_CROSS_use_DP1,
			btnDown_CROSS_DP1_open_start_delay,
			btnDown_CROSS_DP1_stay_open_time,
			btnDown_CROSS_use_DP2,
			btnDown_CROSS_DP2_open_start_delay,
			btnDown_CROSS_DP2_stay_open_time,
			btnDown_CROSS_use_DP3,
			btnDown_CROSS_DP3_open_start_delay,
			btnDown_CROSS_DP3_stay_open_time,
			btnDown_CROSS_use_DP4,
			btnDown_CROSS_DP4_open_start_delay,
			btnDown_CROSS_DP4_stay_open_time,
			btnDown_CROSS_use_DP5,
			btnDown_CROSS_DP5_open_start_delay,
			btnDown_CROSS_DP5_stay_open_time,
			btnDown_CROSS_use_DP6,
			btnDown_CROSS_DP6_open_start_delay,
			btnDown_CROSS_DP6_stay_open_time,
			btnDown_CROSS_use_DP7,
			btnDown_CROSS_DP7_open_start_delay,
			btnDown_CROSS_DP7_stay_open_time,
			btnDown_CROSS_use_DP8,
			btnDown_CROSS_DP8_open_start_delay,
			btnDown_CROSS_DP8_stay_open_time,
			btnDown_CROSS_use_DP9,
			btnDown_CROSS_DP9_open_start_delay,
			btnDown_CROSS_DP9_stay_open_time,
			btnDown_CROSS_use_DP10,
			btnDown_CROSS_DP10_open_start_delay,
			btnDown_CROSS_DP10_stay_open_time);

#ifdef SHADOW_VERBOSE     

		output += "\nFOOT: btnUP_CROSS + VOL: " + String(soundVolume);

#endif


		return;

	}

	if (((!PS3NavDome->PS3NavigationConnected && PS3NavFoot->getButtonPress(LEFT) && PS3NavFoot->getButtonPress(CROSS)) || (PS3NavDome->PS3NavigationConnected && PS3NavFoot->getButtonPress(LEFT) && PS3NavDome->getButtonPress(CROSS))) && marcDuinoButtonCounter == 1)
	{

		marcDuinoButtonPush(btnLeft_CROSS_type, btnLeft_CROSS_MD_func, btnLeft_CROSS_cust_MP3_num, btnLeft_CROSS_cust_LD_type, btnLeft_CROSS_cust_LD_text, btnLeft_CROSS_cust_panel,
			btnLeft_CROSS_use_DP1,
			btnLeft_CROSS_DP1_open_start_delay,
			btnLeft_CROSS_DP1_stay_open_time,
			btnLeft_CROSS_use_DP2,
			btnLeft_CROSS_DP2_open_start_delay,
			btnLeft_CROSS_DP2_stay_open_time,
			btnLeft_CROSS_use_DP3,
			btnLeft_CROSS_DP3_open_start_delay,
			btnLeft_CROSS_DP3_stay_open_time,
			btnLeft_CROSS_use_DP4,
			btnLeft_CROSS_DP4_open_start_delay,
			btnLeft_CROSS_DP4_stay_open_time,
			btnLeft_CROSS_use_DP5,
			btnLeft_CROSS_DP5_open_start_delay,
			btnLeft_CROSS_DP5_stay_open_time,
			btnLeft_CROSS_use_DP6,
			btnLeft_CROSS_DP6_open_start_delay,
			btnLeft_CROSS_DP6_stay_open_time,
			btnLeft_CROSS_use_DP7,
			btnLeft_CROSS_DP7_open_start_delay,
			btnLeft_CROSS_DP7_stay_open_time,
			btnLeft_CROSS_use_DP8,
			btnLeft_CROSS_DP8_open_start_delay,
			btnLeft_CROSS_DP8_stay_open_time,
			btnLeft_CROSS_use_DP9,
			btnLeft_CROSS_DP9_open_start_delay,
			btnLeft_CROSS_DP9_stay_open_time,
			btnLeft_CROSS_use_DP10,
			btnLeft_CROSS_DP10_open_start_delay,
			btnLeft_CROSS_DP10_stay_open_time);

#ifdef SHADOW_VERBOSE      
		output += "\nFOOT: btnLeft_CROSS";
#endif
#ifdef SOUND_WAVTRIGGER
		if ( soundFileNo > 0 ) soundFileNo--;
		output += "\nmp3: " + String(soundFileNo);

		//trigger.trackPlaySolo(soundFileNo);
#endif

		return;

	}

	if (((!PS3NavDome->PS3NavigationConnected && PS3NavFoot->getButtonPress(RIGHT) && PS3NavFoot->getButtonPress(CROSS)) || (PS3NavDome->PS3NavigationConnected && PS3NavFoot->getButtonPress(RIGHT) && PS3NavDome->getButtonPress(CROSS))) && marcDuinoButtonCounter == 1)
	{

		marcDuinoButtonPush(btnRight_CROSS_type, btnRight_CROSS_MD_func, btnRight_CROSS_cust_MP3_num, btnRight_CROSS_cust_LD_type, btnRight_CROSS_cust_LD_text, btnRight_CROSS_cust_panel,
			btnRight_CROSS_use_DP1,
			btnRight_CROSS_DP1_open_start_delay,
			btnRight_CROSS_DP1_stay_open_time,
			btnRight_CROSS_use_DP2,
			btnRight_CROSS_DP2_open_start_delay,
			btnRight_CROSS_DP2_stay_open_time,
			btnRight_CROSS_use_DP3,
			btnRight_CROSS_DP3_open_start_delay,
			btnRight_CROSS_DP3_stay_open_time,
			btnRight_CROSS_use_DP4,
			btnRight_CROSS_DP4_open_start_delay,
			btnRight_CROSS_DP4_stay_open_time,
			btnRight_CROSS_use_DP5,
			btnRight_CROSS_DP5_open_start_delay,
			btnRight_CROSS_DP5_stay_open_time,
			btnRight_CROSS_use_DP6,
			btnRight_CROSS_DP6_open_start_delay,
			btnRight_CROSS_DP6_stay_open_time,
			btnRight_CROSS_use_DP7,
			btnRight_CROSS_DP7_open_start_delay,
			btnRight_CROSS_DP7_stay_open_time,
			btnRight_CROSS_use_DP8,
			btnRight_CROSS_DP8_open_start_delay,
			btnRight_CROSS_DP8_stay_open_time,
			btnRight_CROSS_use_DP9,
			btnRight_CROSS_DP9_open_start_delay,
			btnRight_CROSS_DP9_stay_open_time,
			btnRight_CROSS_use_DP10,
			btnRight_CROSS_DP10_open_start_delay,
			btnRight_CROSS_DP10_stay_open_time);

#ifdef SHADOW_VERBOSE      
		output += "\nFOOT: btnRight_CROSS";
#ifdef SOUND_WAVTRIGGER
		soundFileNo++;
		output += "\nmp3: " + String(soundFileNo);

		//trigger.trackPlaySolo(soundFileNo);
#endif

#endif


		return;

	}

	//------------------------------------ 
	// Send triggers for the CIRCLE + base buttons 
	//------------------------------------
	if (((!PS3NavDome->PS3NavigationConnected && PS3NavFoot->getButtonPress(UP) && PS3NavFoot->getButtonPress(CIRCLE)) || (PS3NavDome->PS3NavigationConnected && PS3NavFoot->getButtonPress(UP) && PS3NavDome->getButtonPress(CIRCLE))) && marcDuinoButtonCounter == 1)
	{

		marcDuinoButtonPush(btnUP_CIRCLE_type, btnUP_CIRCLE_MD_func, btnUP_CIRCLE_cust_MP3_num, btnUP_CIRCLE_cust_LD_type, btnUP_CIRCLE_cust_LD_text, btnUP_CIRCLE_cust_panel,
			btnUP_CIRCLE_use_DP1,
			btnUP_CIRCLE_DP1_open_start_delay,
			btnUP_CIRCLE_DP1_stay_open_time,
			btnUP_CIRCLE_use_DP2,
			btnUP_CIRCLE_DP2_open_start_delay,
			btnUP_CIRCLE_DP2_stay_open_time,
			btnUP_CIRCLE_use_DP3,
			btnUP_CIRCLE_DP3_open_start_delay,
			btnUP_CIRCLE_DP3_stay_open_time,
			btnUP_CIRCLE_use_DP4,
			btnUP_CIRCLE_DP4_open_start_delay,
			btnUP_CIRCLE_DP4_stay_open_time,
			btnUP_CIRCLE_use_DP5,
			btnUP_CIRCLE_DP5_open_start_delay,
			btnUP_CIRCLE_DP5_stay_open_time,
			btnUP_CIRCLE_use_DP6,
			btnUP_CIRCLE_DP6_open_start_delay,
			btnUP_CIRCLE_DP6_stay_open_time,
			btnUP_CIRCLE_use_DP7,
			btnUP_CIRCLE_DP7_open_start_delay,
			btnUP_CIRCLE_DP7_stay_open_time,
			btnUP_CIRCLE_use_DP8,
			btnUP_CIRCLE_DP8_open_start_delay,
			btnUP_CIRCLE_DP8_stay_open_time,
			btnUP_CIRCLE_use_DP9,
			btnUP_CIRCLE_DP9_open_start_delay,
			btnUP_CIRCLE_DP9_stay_open_time,
			btnUP_CIRCLE_use_DP10,
			btnUP_CIRCLE_DP10_open_start_delay,
			btnUP_CIRCLE_DP10_stay_open_time);

#ifdef SHADOW_VERBOSE      
		output += "\nFOOT: btnUP_CIRCLE";
#endif


		return;

	}

	if (((!PS3NavDome->PS3NavigationConnected && PS3NavFoot->getButtonPress(DOWN) && PS3NavFoot->getButtonPress(CIRCLE)) || (PS3NavDome->PS3NavigationConnected && PS3NavFoot->getButtonPress(DOWN) && PS3NavDome->getButtonPress(CIRCLE))) && marcDuinoButtonCounter == 1)
	{

		marcDuinoButtonPush(btnDown_CIRCLE_type, btnDown_CIRCLE_MD_func, btnDown_CIRCLE_cust_MP3_num, btnDown_CIRCLE_cust_LD_type, btnDown_CIRCLE_cust_LD_text, btnDown_CIRCLE_cust_panel,
			btnDown_CIRCLE_use_DP1,
			btnDown_CIRCLE_DP1_open_start_delay,
			btnDown_CIRCLE_DP1_stay_open_time,
			btnDown_CIRCLE_use_DP2,
			btnDown_CIRCLE_DP2_open_start_delay,
			btnDown_CIRCLE_DP2_stay_open_time,
			btnDown_CIRCLE_use_DP3,
			btnDown_CIRCLE_DP3_open_start_delay,
			btnDown_CIRCLE_DP3_stay_open_time,
			btnDown_CIRCLE_use_DP4,
			btnDown_CIRCLE_DP4_open_start_delay,
			btnDown_CIRCLE_DP4_stay_open_time,
			btnDown_CIRCLE_use_DP5,
			btnDown_CIRCLE_DP5_open_start_delay,
			btnDown_CIRCLE_DP5_stay_open_time,
			btnDown_CIRCLE_use_DP6,
			btnDown_CIRCLE_DP6_open_start_delay,
			btnDown_CIRCLE_DP6_stay_open_time,
			btnDown_CIRCLE_use_DP7,
			btnDown_CIRCLE_DP7_open_start_delay,
			btnDown_CIRCLE_DP7_stay_open_time,
			btnDown_CIRCLE_use_DP8,
			btnDown_CIRCLE_DP8_open_start_delay,
			btnDown_CIRCLE_DP8_stay_open_time,
			btnDown_CIRCLE_use_DP9,
			btnDown_CIRCLE_DP9_open_start_delay,
			btnDown_CIRCLE_DP9_stay_open_time,
			btnDown_CIRCLE_use_DP10,
			btnDown_CIRCLE_DP10_open_start_delay,
			btnDown_CIRCLE_DP10_stay_open_time);

#ifdef SHADOW_VERBOSE      
		output += "\nFOOT: btnDown_CIRCLE";
#endif


		return;

	}

	if (((!PS3NavDome->PS3NavigationConnected && PS3NavFoot->getButtonPress(LEFT) && PS3NavFoot->getButtonPress(CIRCLE)) || (PS3NavDome->PS3NavigationConnected && PS3NavFoot->getButtonPress(LEFT) && PS3NavDome->getButtonPress(CIRCLE))) && marcDuinoButtonCounter == 1)
	{

		marcDuinoButtonPush(btnLeft_CIRCLE_type, btnLeft_CIRCLE_MD_func, btnLeft_CIRCLE_cust_MP3_num, btnLeft_CIRCLE_cust_LD_type, btnLeft_CIRCLE_cust_LD_text, btnLeft_CIRCLE_cust_panel,
			btnLeft_CIRCLE_use_DP1,
			btnLeft_CIRCLE_DP1_open_start_delay,
			btnLeft_CIRCLE_DP1_stay_open_time,
			btnLeft_CIRCLE_use_DP2,
			btnLeft_CIRCLE_DP2_open_start_delay,
			btnLeft_CIRCLE_DP2_stay_open_time,
			btnLeft_CIRCLE_use_DP3,
			btnLeft_CIRCLE_DP3_open_start_delay,
			btnLeft_CIRCLE_DP3_stay_open_time,
			btnLeft_CIRCLE_use_DP4,
			btnLeft_CIRCLE_DP4_open_start_delay,
			btnLeft_CIRCLE_DP4_stay_open_time,
			btnLeft_CIRCLE_use_DP5,
			btnLeft_CIRCLE_DP5_open_start_delay,
			btnLeft_CIRCLE_DP5_stay_open_time,
			btnLeft_CIRCLE_use_DP6,
			btnLeft_CIRCLE_DP6_open_start_delay,
			btnLeft_CIRCLE_DP6_stay_open_time,
			btnLeft_CIRCLE_use_DP7,
			btnLeft_CIRCLE_DP7_open_start_delay,
			btnLeft_CIRCLE_DP7_stay_open_time,
			btnLeft_CIRCLE_use_DP8,
			btnLeft_CIRCLE_DP8_open_start_delay,
			btnLeft_CIRCLE_DP8_stay_open_time,
			btnLeft_CIRCLE_use_DP9,
			btnLeft_CIRCLE_DP9_open_start_delay,
			btnLeft_CIRCLE_DP9_stay_open_time,
			btnLeft_CIRCLE_use_DP10,
			btnLeft_CIRCLE_DP10_open_start_delay,
			btnLeft_CIRCLE_DP10_stay_open_time);

#ifdef SHADOW_VERBOSE      
		output += "\nFOOT: btnLeft_CIRCLE";
#endif


		return;

	}

	if (((!PS3NavDome->PS3NavigationConnected && PS3NavFoot->getButtonPress(RIGHT) && PS3NavFoot->getButtonPress(CIRCLE)) || (PS3NavDome->PS3NavigationConnected && PS3NavFoot->getButtonPress(RIGHT) && PS3NavDome->getButtonPress(CIRCLE))) && marcDuinoButtonCounter == 1)
	{

		marcDuinoButtonPush(btnRight_CIRCLE_type, btnRight_CIRCLE_MD_func, btnRight_CIRCLE_cust_MP3_num, btnRight_CIRCLE_cust_LD_type, btnRight_CIRCLE_cust_LD_text, btnRight_CIRCLE_cust_panel,
			btnRight_CIRCLE_use_DP1,
			btnRight_CIRCLE_DP1_open_start_delay,
			btnRight_CIRCLE_DP1_stay_open_time,
			btnRight_CIRCLE_use_DP2,
			btnRight_CIRCLE_DP2_open_start_delay,
			btnRight_CIRCLE_DP2_stay_open_time,
			btnRight_CIRCLE_use_DP3,
			btnRight_CIRCLE_DP3_open_start_delay,
			btnRight_CIRCLE_DP3_stay_open_time,
			btnRight_CIRCLE_use_DP4,
			btnRight_CIRCLE_DP4_open_start_delay,
			btnRight_CIRCLE_DP4_stay_open_time,
			btnRight_CIRCLE_use_DP5,
			btnRight_CIRCLE_DP5_open_start_delay,
			btnRight_CIRCLE_DP5_stay_open_time,
			btnRight_CIRCLE_use_DP6,
			btnRight_CIRCLE_DP6_open_start_delay,
			btnRight_CIRCLE_DP6_stay_open_time,
			btnRight_CIRCLE_use_DP7,
			btnRight_CIRCLE_DP7_open_start_delay,
			btnRight_CIRCLE_DP7_stay_open_time,
			btnRight_CIRCLE_use_DP8,
			btnRight_CIRCLE_DP8_open_start_delay,
			btnRight_CIRCLE_DP8_stay_open_time,
			btnRight_CIRCLE_use_DP9,
			btnRight_CIRCLE_DP9_open_start_delay,
			btnRight_CIRCLE_DP9_stay_open_time,
			btnRight_CIRCLE_use_DP10,
			btnRight_CIRCLE_DP10_open_start_delay,
			btnRight_CIRCLE_DP10_stay_open_time);


#ifdef SHADOW_VERBOSE      
		output += "\nFOOT: btnRight_CIRCLE";
#endif


		return;

	}

	//------------------------------------ 
	// Send triggers for the L1 + base buttons 
	//------------------------------------
	if (PS3NavFoot->getButtonPress(UP) && PS3NavFoot->getButtonPress(L1) && marcDuinoButtonCounter == 1)
	{

		marcDuinoButtonPush(btnUP_L1_type, btnUP_L1_MD_func, btnUP_L1_cust_MP3_num, btnUP_L1_cust_LD_type, btnUP_L1_cust_LD_text, btnUP_L1_cust_panel,
			btnUP_L1_use_DP1,
			btnUP_L1_DP1_open_start_delay,
			btnUP_L1_DP1_stay_open_time,
			btnUP_L1_use_DP2,
			btnUP_L1_DP2_open_start_delay,
			btnUP_L1_DP2_stay_open_time,
			btnUP_L1_use_DP3,
			btnUP_L1_DP3_open_start_delay,
			btnUP_L1_DP3_stay_open_time,
			btnUP_L1_use_DP4,
			btnUP_L1_DP4_open_start_delay,
			btnUP_L1_DP4_stay_open_time,
			btnUP_L1_use_DP5,
			btnUP_L1_DP5_open_start_delay,
			btnUP_L1_DP5_stay_open_time,
			btnUP_L1_use_DP6,
			btnUP_L1_DP6_open_start_delay,
			btnUP_L1_DP6_stay_open_time,
			btnUP_L1_use_DP7,
			btnUP_L1_DP7_open_start_delay,
			btnUP_L1_DP7_stay_open_time,
			btnUP_L1_use_DP8,
			btnUP_L1_DP8_open_start_delay,
			btnUP_L1_DP8_stay_open_time,
			btnUP_L1_use_DP9,
			btnUP_L1_DP9_open_start_delay,
			btnUP_L1_DP9_stay_open_time,
			btnUP_L1_use_DP10,
			btnUP_L1_DP10_open_start_delay,
			btnUP_L1_DP10_stay_open_time);

#ifdef SHADOW_VERBOSE      
		output += "\nFOOT: btnUP_L1";
#endif


		return;

	}

	if (PS3NavFoot->getButtonPress(DOWN) && PS3NavFoot->getButtonPress(L1) && marcDuinoButtonCounter == 1)
	{

		marcDuinoButtonPush(btnDown_L1_type, btnDown_L1_MD_func, btnDown_L1_cust_MP3_num, btnDown_L1_cust_LD_type, btnDown_L1_cust_LD_text, btnDown_L1_cust_panel,
			btnDown_L1_use_DP1,
			btnDown_L1_DP1_open_start_delay,
			btnDown_L1_DP1_stay_open_time,
			btnDown_L1_use_DP2,
			btnDown_L1_DP2_open_start_delay,
			btnDown_L1_DP2_stay_open_time,
			btnDown_L1_use_DP3,
			btnDown_L1_DP3_open_start_delay,
			btnDown_L1_DP3_stay_open_time,
			btnDown_L1_use_DP4,
			btnDown_L1_DP4_open_start_delay,
			btnDown_L1_DP4_stay_open_time,
			btnDown_L1_use_DP5,
			btnDown_L1_DP5_open_start_delay,
			btnDown_L1_DP5_stay_open_time,
			btnDown_L1_use_DP6,
			btnDown_L1_DP6_open_start_delay,
			btnDown_L1_DP6_stay_open_time,
			btnDown_L1_use_DP7,
			btnDown_L1_DP7_open_start_delay,
			btnDown_L1_DP7_stay_open_time,
			btnDown_L1_use_DP8,
			btnDown_L1_DP8_open_start_delay,
			btnDown_L1_DP8_stay_open_time,
			btnDown_L1_use_DP9,
			btnDown_L1_DP9_open_start_delay,
			btnDown_L1_DP9_stay_open_time,
			btnDown_L1_use_DP10,
			btnDown_L1_DP10_open_start_delay,
			btnDown_L1_DP10_stay_open_time);

#ifdef SHADOW_VERBOSE      
		output += "\nFOOT: btnDown_L1";
#endif


		return;

	}

	if (PS3NavFoot->getButtonPress(LEFT) && PS3NavFoot->getButtonPress(L1) && marcDuinoButtonCounter == 1)
	{

		marcDuinoButtonPush(btnLeft_L1_type, btnLeft_L1_MD_func, btnLeft_L1_cust_MP3_num, btnLeft_L1_cust_LD_type, btnLeft_L1_cust_LD_text, btnLeft_L1_cust_panel,
			btnLeft_L1_use_DP1,
			btnLeft_L1_DP1_open_start_delay,
			btnLeft_L1_DP1_stay_open_time,
			btnLeft_L1_use_DP2,
			btnLeft_L1_DP2_open_start_delay,
			btnLeft_L1_DP2_stay_open_time,
			btnLeft_L1_use_DP3,
			btnLeft_L1_DP3_open_start_delay,
			btnLeft_L1_DP3_stay_open_time,
			btnLeft_L1_use_DP4,
			btnLeft_L1_DP4_open_start_delay,
			btnLeft_L1_DP4_stay_open_time,
			btnLeft_L1_use_DP5,
			btnLeft_L1_DP5_open_start_delay,
			btnLeft_L1_DP5_stay_open_time,
			btnLeft_L1_use_DP6,
			btnLeft_L1_DP6_open_start_delay,
			btnLeft_L1_DP6_stay_open_time,
			btnLeft_L1_use_DP7,
			btnLeft_L1_DP7_open_start_delay,
			btnLeft_L1_DP7_stay_open_time,
			btnLeft_L1_use_DP8,
			btnLeft_L1_DP8_open_start_delay,
			btnLeft_L1_DP8_stay_open_time,
			btnLeft_L1_use_DP9,
			btnLeft_L1_DP9_open_start_delay,
			btnLeft_L1_DP9_stay_open_time,
			btnLeft_L1_use_DP10,
			btnLeft_L1_DP10_open_start_delay,
			btnLeft_L1_DP10_stay_open_time);

#ifdef SHADOW_VERBOSE      
		output += "\nFOOT: btnLeft_L1";
#endif


		return;

	}

	if (PS3NavFoot->getButtonPress(RIGHT) && PS3NavFoot->getButtonPress(L1) && marcDuinoButtonCounter == 1)
	{

		marcDuinoButtonPush(btnRight_L1_type, btnRight_L1_MD_func, btnRight_L1_cust_MP3_num, btnRight_L1_cust_LD_type, btnRight_L1_cust_LD_text, btnRight_L1_cust_panel,
			btnRight_L1_use_DP1,
			btnRight_L1_DP1_open_start_delay,
			btnRight_L1_DP1_stay_open_time,
			btnRight_L1_use_DP2,
			btnRight_L1_DP2_open_start_delay,
			btnRight_L1_DP2_stay_open_time,
			btnRight_L1_use_DP3,
			btnRight_L1_DP3_open_start_delay,
			btnRight_L1_DP3_stay_open_time,
			btnRight_L1_use_DP4,
			btnRight_L1_DP4_open_start_delay,
			btnRight_L1_DP4_stay_open_time,
			btnRight_L1_use_DP5,
			btnRight_L1_DP5_open_start_delay,
			btnRight_L1_DP5_stay_open_time,
			btnRight_L1_use_DP6,
			btnRight_L1_DP6_open_start_delay,
			btnRight_L1_DP6_stay_open_time,
			btnRight_L1_use_DP7,
			btnRight_L1_DP7_open_start_delay,
			btnRight_L1_DP7_stay_open_time,
			btnRight_L1_use_DP8,
			btnRight_L1_DP8_open_start_delay,
			btnRight_L1_DP8_stay_open_time,
			btnRight_L1_use_DP9,
			btnRight_L1_DP9_open_start_delay,
			btnRight_L1_DP9_stay_open_time,
			btnRight_L1_use_DP10,
			btnRight_L1_DP10_open_start_delay,
			btnRight_L1_DP10_stay_open_time);

#ifdef SHADOW_VERBOSE      
		output += "\nFOOT: btnRight_L1";
#endif


		return;

	}

	//------------------------------------ 
	// Send triggers for the PS + base buttons 
	//------------------------------------
	if (((!PS3NavDome->PS3NavigationConnected && PS3NavFoot->getButtonPress(UP) && PS3NavFoot->getButtonPress(PS)) || (PS3NavDome->PS3NavigationConnected && PS3NavFoot->getButtonPress(UP) && PS3NavDome->getButtonPress(PS))) && marcDuinoButtonCounter == 1)
	{

		marcDuinoButtonPush(btnUP_PS_type, btnUP_PS_MD_func, btnUP_PS_cust_MP3_num, btnUP_PS_cust_LD_type, btnUP_PS_cust_LD_text, btnUP_PS_cust_panel,
			btnUP_PS_use_DP1,
			btnUP_PS_DP1_open_start_delay,
			btnUP_PS_DP1_stay_open_time,
			btnUP_PS_use_DP2,
			btnUP_PS_DP2_open_start_delay,
			btnUP_PS_DP2_stay_open_time,
			btnUP_PS_use_DP3,
			btnUP_PS_DP3_open_start_delay,
			btnUP_PS_DP3_stay_open_time,
			btnUP_PS_use_DP4,
			btnUP_PS_DP4_open_start_delay,
			btnUP_PS_DP4_stay_open_time,
			btnUP_PS_use_DP5,
			btnUP_PS_DP5_open_start_delay,
			btnUP_PS_DP5_stay_open_time,
			btnUP_PS_use_DP6,
			btnUP_PS_DP6_open_start_delay,
			btnUP_PS_DP6_stay_open_time,
			btnUP_PS_use_DP7,
			btnUP_PS_DP7_open_start_delay,
			btnUP_PS_DP7_stay_open_time,
			btnUP_PS_use_DP8,
			btnUP_PS_DP8_open_start_delay,
			btnUP_PS_DP8_stay_open_time,
			btnUP_PS_use_DP9,
			btnUP_PS_DP9_open_start_delay,
			btnUP_PS_DP9_stay_open_time,
			btnUP_PS_use_DP10,
			btnUP_PS_DP10_open_start_delay,
			btnUP_PS_DP10_stay_open_time);

#ifdef SHADOW_VERBOSE      
		output += "\nFOOT: btnUP_PS";
#endif


		return;

	}

	if (((!PS3NavDome->PS3NavigationConnected && PS3NavFoot->getButtonPress(DOWN) && PS3NavFoot->getButtonPress(PS)) || (PS3NavDome->PS3NavigationConnected && PS3NavFoot->getButtonPress(DOWN) && PS3NavDome->getButtonPress(PS))) && marcDuinoButtonCounter == 1)
	{

		marcDuinoButtonPush(btnDown_PS_type, btnDown_PS_MD_func, btnDown_PS_cust_MP3_num, btnDown_PS_cust_LD_type, btnDown_PS_cust_LD_text, btnDown_PS_cust_panel,
			btnDown_PS_use_DP1,
			btnDown_PS_DP1_open_start_delay,
			btnDown_PS_DP1_stay_open_time,
			btnDown_PS_use_DP2,
			btnDown_PS_DP2_open_start_delay,
			btnDown_PS_DP2_stay_open_time,
			btnDown_PS_use_DP3,
			btnDown_PS_DP3_open_start_delay,
			btnDown_PS_DP3_stay_open_time,
			btnDown_PS_use_DP4,
			btnDown_PS_DP4_open_start_delay,
			btnDown_PS_DP4_stay_open_time,
			btnDown_PS_use_DP5,
			btnDown_PS_DP5_open_start_delay,
			btnDown_PS_DP5_stay_open_time,
			btnDown_PS_use_DP6,
			btnDown_PS_DP6_open_start_delay,
			btnDown_PS_DP6_stay_open_time,
			btnDown_PS_use_DP7,
			btnDown_PS_DP7_open_start_delay,
			btnDown_PS_DP7_stay_open_time,
			btnDown_PS_use_DP8,
			btnDown_PS_DP8_open_start_delay,
			btnDown_PS_DP8_stay_open_time,
			btnDown_PS_use_DP9,
			btnDown_PS_DP9_open_start_delay,
			btnDown_PS_DP9_stay_open_time,
			btnDown_PS_use_DP10,
			btnDown_PS_DP10_open_start_delay,
			btnDown_PS_DP10_stay_open_time);

#ifdef SHADOW_VERBOSE      
		output += "\nFOOT: btnDown_PS";
#endif


		return;

	}

	if (((!PS3NavDome->PS3NavigationConnected && PS3NavFoot->getButtonPress(LEFT) && PS3NavFoot->getButtonPress(PS)) || (PS3NavDome->PS3NavigationConnected && PS3NavFoot->getButtonPress(LEFT) && PS3NavDome->getButtonPress(PS))) && marcDuinoButtonCounter == 1)
	{

		marcDuinoButtonPush(btnLeft_PS_type, btnLeft_PS_MD_func, btnLeft_PS_cust_MP3_num, btnLeft_PS_cust_LD_type, btnLeft_PS_cust_LD_text, btnLeft_PS_cust_panel,
			btnLeft_PS_use_DP1,
			btnLeft_PS_DP1_open_start_delay,
			btnLeft_PS_DP1_stay_open_time,
			btnLeft_PS_use_DP2,
			btnLeft_PS_DP2_open_start_delay,
			btnLeft_PS_DP2_stay_open_time,
			btnLeft_PS_use_DP3,
			btnLeft_PS_DP3_open_start_delay,
			btnLeft_PS_DP3_stay_open_time,
			btnLeft_PS_use_DP4,
			btnLeft_PS_DP4_open_start_delay,
			btnLeft_PS_DP4_stay_open_time,
			btnLeft_PS_use_DP5,
			btnLeft_PS_DP5_open_start_delay,
			btnLeft_PS_DP5_stay_open_time,
			btnLeft_PS_use_DP6,
			btnLeft_PS_DP6_open_start_delay,
			btnLeft_PS_DP6_stay_open_time,
			btnLeft_PS_use_DP7,
			btnLeft_PS_DP7_open_start_delay,
			btnLeft_PS_DP7_stay_open_time,
			btnLeft_PS_use_DP8,
			btnLeft_PS_DP8_open_start_delay,
			btnLeft_PS_DP8_stay_open_time,
			btnLeft_PS_use_DP9,
			btnLeft_PS_DP9_open_start_delay,
			btnLeft_PS_DP9_stay_open_time,
			btnLeft_PS_use_DP10,
			btnLeft_PS_DP10_open_start_delay,
			btnLeft_PS_DP10_stay_open_time);

#ifdef SHADOW_VERBOSE      
		output += "\nFOOT: btnLeft_PS";
#endif


		return;

	}

	if (((!PS3NavDome->PS3NavigationConnected && PS3NavFoot->getButtonPress(RIGHT) && PS3NavFoot->getButtonPress(PS)) || (PS3NavDome->PS3NavigationConnected && PS3NavFoot->getButtonPress(RIGHT) && PS3NavDome->getButtonPress(PS))) && marcDuinoButtonCounter == 1)
	{

		marcDuinoButtonPush(btnRight_PS_type, btnRight_PS_MD_func, btnRight_PS_cust_MP3_num, btnRight_PS_cust_LD_type, btnRight_PS_cust_LD_text, btnRight_PS_cust_panel,
			btnRight_PS_use_DP1,
			btnRight_PS_DP1_open_start_delay,
			btnRight_PS_DP1_stay_open_time,
			btnRight_PS_use_DP2,
			btnRight_PS_DP2_open_start_delay,
			btnRight_PS_DP2_stay_open_time,
			btnRight_PS_use_DP3,
			btnRight_PS_DP3_open_start_delay,
			btnRight_PS_DP3_stay_open_time,
			btnRight_PS_use_DP4,
			btnRight_PS_DP4_open_start_delay,
			btnRight_PS_DP4_stay_open_time,
			btnRight_PS_use_DP5,
			btnRight_PS_DP5_open_start_delay,
			btnRight_PS_DP5_stay_open_time,
			btnRight_PS_use_DP6,
			btnRight_PS_DP6_open_start_delay,
			btnRight_PS_DP6_stay_open_time,
			btnRight_PS_use_DP7,
			btnRight_PS_DP7_open_start_delay,
			btnRight_PS_DP7_stay_open_time,
			btnRight_PS_use_DP8,
			btnRight_PS_DP8_open_start_delay,
			btnRight_PS_DP8_stay_open_time,
			btnRight_PS_use_DP9,
			btnRight_PS_DP9_open_start_delay,
			btnRight_PS_DP9_stay_open_time,
			btnRight_PS_use_DP10,
			btnRight_PS_DP10_open_start_delay,
			btnRight_PS_DP10_stay_open_time);

#ifdef SHADOW_VERBOSE      
		output += "\nFOOT: btnRight_PS";
#endif


		return;

	}

}

// ===================================================================================================================
// This function determines if MarcDuino buttons were selected and calls main processing function for DOME Controller
// ===================================================================================================================
void marcDuinoDome()
{
	if (PS3NavDome->PS3NavigationConnected && (PS3NavDome->getButtonPress(UP) || PS3NavDome->getButtonPress(DOWN) || PS3NavDome->getButtonPress(LEFT) || PS3NavDome->getButtonPress(RIGHT)))
	{

		if ((millis() - previousMarcDuinoMillis) > 1000)
		{
			marcDuinoButtonCounter = 0;
			previousMarcDuinoMillis = millis();
		}

		marcDuinoButtonCounter += 1;

	}
	else
	{
		return;
	}

	// Clear inbound buffer of any data sent form the MarcDuino board
	while (Serial1.available()) Serial1.read();

	//------------------------------------ 
	// Send triggers for the base buttons 
	//------------------------------------
	if (PS3NavDome->getButtonPress(UP) && !PS3NavDome->getButtonPress(CROSS) && !PS3NavDome->getButtonPress(CIRCLE) && !PS3NavDome->getButtonPress(L1) && !PS3NavDome->getButtonPress(PS) && !PS3NavFoot->getButtonPress(CROSS) && !PS3NavFoot->getButtonPress(CIRCLE) && !PS3NavFoot->getButtonPress(PS) && marcDuinoButtonCounter == 1)
	{

		marcDuinoButtonPush(1, FTbtnUP_MD_func, btnUP_cust_MP3_num, btnUP_cust_LD_type, btnUP_cust_LD_text, btnUP_cust_panel,
			btnUP_use_DP1,
			btnUP_DP1_open_start_delay,
			btnUP_DP1_stay_open_time,
			btnUP_use_DP2,
			btnUP_DP2_open_start_delay,
			btnUP_DP2_stay_open_time,
			btnUP_use_DP3,
			btnUP_DP3_open_start_delay,
			btnUP_DP3_stay_open_time,
			btnUP_use_DP4,
			btnUP_DP4_open_start_delay,
			btnUP_DP4_stay_open_time,
			btnUP_use_DP5,
			btnUP_DP5_open_start_delay,
			btnUP_DP5_stay_open_time,
			btnUP_use_DP6,
			btnUP_DP6_open_start_delay,
			btnUP_DP6_stay_open_time,
			btnUP_use_DP7,
			btnUP_DP7_open_start_delay,
			btnUP_DP7_stay_open_time,
			btnUP_use_DP8,
			btnUP_DP8_open_start_delay,
			btnUP_DP8_stay_open_time,
			btnUP_use_DP9,
			btnUP_DP9_open_start_delay,
			btnUP_DP9_stay_open_time,
			btnUP_use_DP10,
			btnUP_DP10_open_start_delay,
			btnUP_DP10_stay_open_time);

#ifdef SHADOW_VERBOSE      
		output += "\nDOME: btnUP";
#endif

		return;

	}

	if (PS3NavDome->getButtonPress(DOWN) && !PS3NavDome->getButtonPress(CROSS) && !PS3NavDome->getButtonPress(CIRCLE) && !PS3NavDome->getButtonPress(L1) && !PS3NavDome->getButtonPress(PS) && !PS3NavFoot->getButtonPress(CROSS) && !PS3NavFoot->getButtonPress(CIRCLE) && !PS3NavFoot->getButtonPress(PS) && marcDuinoButtonCounter == 1)
	{

		marcDuinoButtonPush(1, FTbtnDown_MD_func, btnDown_cust_MP3_num, btnDown_cust_LD_type, btnDown_cust_LD_text, btnDown_cust_panel,
			btnDown_use_DP1,
			btnDown_DP1_open_start_delay,
			btnDown_DP1_stay_open_time,
			btnDown_use_DP2,
			btnDown_DP2_open_start_delay,
			btnDown_DP2_stay_open_time,
			btnDown_use_DP3,
			btnDown_DP3_open_start_delay,
			btnDown_DP3_stay_open_time,
			btnDown_use_DP4,
			btnDown_DP4_open_start_delay,
			btnDown_DP4_stay_open_time,
			btnDown_use_DP5,
			btnDown_DP5_open_start_delay,
			btnDown_DP5_stay_open_time,
			btnDown_use_DP6,
			btnDown_DP6_open_start_delay,
			btnDown_DP6_stay_open_time,
			btnDown_use_DP7,
			btnDown_DP7_open_start_delay,
			btnDown_DP7_stay_open_time,
			btnDown_use_DP8,
			btnDown_DP8_open_start_delay,
			btnDown_DP8_stay_open_time,
			btnDown_use_DP9,
			btnDown_DP9_open_start_delay,
			btnDown_DP9_stay_open_time,
			btnDown_use_DP10,
			btnDown_DP10_open_start_delay,
			btnDown_DP10_stay_open_time);

#ifdef SHADOW_VERBOSE      
		output += "\nDOME: btnDown";
#endif

		return;
	}

	if (PS3NavDome->getButtonPress(LEFT) && !PS3NavDome->getButtonPress(CROSS) && !PS3NavDome->getButtonPress(CIRCLE) && !PS3NavDome->getButtonPress(L1) && !PS3NavDome->getButtonPress(PS) && !PS3NavFoot->getButtonPress(CROSS) && !PS3NavFoot->getButtonPress(CIRCLE) && !PS3NavFoot->getButtonPress(PS) && marcDuinoButtonCounter == 1)
	{

		marcDuinoButtonPush(1, FTbtnLeft_MD_func, btnLeft_cust_MP3_num, btnLeft_cust_LD_type, btnLeft_cust_LD_text, btnLeft_cust_panel,
			btnLeft_use_DP1,
			btnLeft_DP1_open_start_delay,
			btnLeft_DP1_stay_open_time,
			btnLeft_use_DP2,
			btnLeft_DP2_open_start_delay,
			btnLeft_DP2_stay_open_time,
			btnLeft_use_DP3,
			btnLeft_DP3_open_start_delay,
			btnLeft_DP3_stay_open_time,
			btnLeft_use_DP4,
			btnLeft_DP4_open_start_delay,
			btnLeft_DP4_stay_open_time,
			btnLeft_use_DP5,
			btnLeft_DP5_open_start_delay,
			btnLeft_DP5_stay_open_time,
			btnLeft_use_DP6,
			btnLeft_DP6_open_start_delay,
			btnLeft_DP6_stay_open_time,
			btnLeft_use_DP7,
			btnLeft_DP7_open_start_delay,
			btnLeft_DP7_stay_open_time,
			btnLeft_use_DP8,
			btnLeft_DP8_open_start_delay,
			btnLeft_DP8_stay_open_time,
			btnLeft_use_DP9,
			btnLeft_DP9_open_start_delay,
			btnLeft_DP9_stay_open_time,
			btnLeft_use_DP10,
			btnLeft_DP10_open_start_delay,
			btnLeft_DP10_stay_open_time);

#ifdef SHADOW_VERBOSE      
		output += "\nDOME: btnLeft";
#endif

		return;

	}

	if (PS3NavDome->getButtonPress(RIGHT) && !PS3NavDome->getButtonPress(CROSS) && !PS3NavDome->getButtonPress(CIRCLE) && !PS3NavDome->getButtonPress(L1) && !PS3NavDome->getButtonPress(PS) && !PS3NavFoot->getButtonPress(CROSS) && !PS3NavFoot->getButtonPress(CIRCLE) && !PS3NavFoot->getButtonPress(PS) && marcDuinoButtonCounter == 1)
	{

		marcDuinoButtonPush(1, FTbtnRight_MD_func, btnRight_cust_MP3_num, btnRight_cust_LD_type, btnRight_cust_LD_text, btnRight_cust_panel,
			btnRight_use_DP1,
			btnRight_DP1_open_start_delay,
			btnRight_DP1_stay_open_time,
			btnRight_use_DP2,
			btnRight_DP2_open_start_delay,
			btnRight_DP2_stay_open_time,
			btnRight_use_DP3,
			btnRight_DP3_open_start_delay,
			btnRight_DP3_stay_open_time,
			btnRight_use_DP4,
			btnRight_DP4_open_start_delay,
			btnRight_DP4_stay_open_time,
			btnRight_use_DP5,
			btnRight_DP5_open_start_delay,
			btnRight_DP5_stay_open_time,
			btnRight_use_DP6,
			btnRight_DP6_open_start_delay,
			btnRight_DP6_stay_open_time,
			btnRight_use_DP7,
			btnRight_DP7_open_start_delay,
			btnRight_DP7_stay_open_time,
			btnRight_use_DP8,
			btnRight_DP8_open_start_delay,
			btnRight_DP8_stay_open_time,
			btnRight_use_DP9,
			btnRight_DP9_open_start_delay,
			btnRight_DP9_stay_open_time,
			btnRight_use_DP10,
			btnRight_DP10_open_start_delay,
			btnRight_DP10_stay_open_time);

#ifdef SHADOW_VERBOSE      
		output += "\nDOME: btnRight";
#endif


		return;

	}

	//------------------------------------ 
	// Send triggers for the CROSS + base buttons 
	//------------------------------------
	if (PS3NavDome->getButtonPress(UP) && PS3NavFoot->getButtonPress(CROSS) && marcDuinoButtonCounter == 1)
	{

		marcDuinoButtonPush(1, FTbtnUP_CROSS_MD_func, btnUP_CROSS_cust_MP3_num, btnUP_CROSS_cust_LD_type, btnUP_CROSS_cust_LD_text, btnUP_CROSS_cust_panel,
			btnUP_CROSS_use_DP1,
			btnUP_CROSS_DP1_open_start_delay,
			btnUP_CROSS_DP1_stay_open_time,
			btnUP_CROSS_use_DP2,
			btnUP_CROSS_DP2_open_start_delay,
			btnUP_CROSS_DP2_stay_open_time,
			btnUP_CROSS_use_DP3,
			btnUP_CROSS_DP3_open_start_delay,
			btnUP_CROSS_DP3_stay_open_time,
			btnUP_CROSS_use_DP4,
			btnUP_CROSS_DP4_open_start_delay,
			btnUP_CROSS_DP4_stay_open_time,
			btnUP_CROSS_use_DP5,
			btnUP_CROSS_DP5_open_start_delay,
			btnUP_CROSS_DP5_stay_open_time,
			btnUP_CROSS_use_DP6,
			btnUP_CROSS_DP6_open_start_delay,
			btnUP_CROSS_DP6_stay_open_time,
			btnUP_CROSS_use_DP7,
			btnUP_CROSS_DP7_open_start_delay,
			btnUP_CROSS_DP7_stay_open_time,
			btnUP_CROSS_use_DP8,
			btnUP_CROSS_DP8_open_start_delay,
			btnUP_CROSS_DP8_stay_open_time,
			btnUP_CROSS_use_DP9,
			btnUP_CROSS_DP9_open_start_delay,
			btnUP_CROSS_DP9_stay_open_time,
			btnUP_CROSS_use_DP10,
			btnUP_CROSS_DP10_open_start_delay,
			btnUP_CROSS_DP10_stay_open_time);

#ifdef SHADOW_VERBOSE      
		output += "\nDOME: btnUP_CROSS";
#endif


		return;

	}

	if (PS3NavDome->getButtonPress(DOWN) && PS3NavFoot->getButtonPress(CROSS) && marcDuinoButtonCounter == 1)
	{

		marcDuinoButtonPush(1, FTbtnDown_CROSS_MD_func, btnDown_CROSS_cust_MP3_num, btnDown_CROSS_cust_LD_type, btnDown_CROSS_cust_LD_text, btnDown_CROSS_cust_panel,
			btnDown_CROSS_use_DP1,
			btnDown_CROSS_DP1_open_start_delay,
			btnDown_CROSS_DP1_stay_open_time,
			btnDown_CROSS_use_DP2,
			btnDown_CROSS_DP2_open_start_delay,
			btnDown_CROSS_DP2_stay_open_time,
			btnDown_CROSS_use_DP3,
			btnDown_CROSS_DP3_open_start_delay,
			btnDown_CROSS_DP3_stay_open_time,
			btnDown_CROSS_use_DP4,
			btnDown_CROSS_DP4_open_start_delay,
			btnDown_CROSS_DP4_stay_open_time,
			btnDown_CROSS_use_DP5,
			btnDown_CROSS_DP5_open_start_delay,
			btnDown_CROSS_DP5_stay_open_time,
			btnDown_CROSS_use_DP6,
			btnDown_CROSS_DP6_open_start_delay,
			btnDown_CROSS_DP6_stay_open_time,
			btnDown_CROSS_use_DP7,
			btnDown_CROSS_DP7_open_start_delay,
			btnDown_CROSS_DP7_stay_open_time,
			btnDown_CROSS_use_DP8,
			btnDown_CROSS_DP8_open_start_delay,
			btnDown_CROSS_DP8_stay_open_time,
			btnDown_CROSS_use_DP9,
			btnDown_CROSS_DP9_open_start_delay,
			btnDown_CROSS_DP9_stay_open_time,
			btnDown_CROSS_use_DP10,
			btnDown_CROSS_DP10_open_start_delay,
			btnDown_CROSS_DP10_stay_open_time);

#ifdef SHADOW_VERBOSE      
		output += "\nDOME: btnDown_CROSS";
#endif


		return;

	}

	if (PS3NavDome->getButtonPress(LEFT) && PS3NavFoot->getButtonPress(CROSS) && marcDuinoButtonCounter == 1)
	{

		marcDuinoButtonPush(1, FTbtnLeft_CROSS_MD_func, btnLeft_CROSS_cust_MP3_num, btnLeft_CROSS_cust_LD_type, btnLeft_CROSS_cust_LD_text, btnLeft_CROSS_cust_panel,
			btnLeft_CROSS_use_DP1,
			btnLeft_CROSS_DP1_open_start_delay,
			btnLeft_CROSS_DP1_stay_open_time,
			btnLeft_CROSS_use_DP2,
			btnLeft_CROSS_DP2_open_start_delay,
			btnLeft_CROSS_DP2_stay_open_time,
			btnLeft_CROSS_use_DP3,
			btnLeft_CROSS_DP3_open_start_delay,
			btnLeft_CROSS_DP3_stay_open_time,
			btnLeft_CROSS_use_DP4,
			btnLeft_CROSS_DP4_open_start_delay,
			btnLeft_CROSS_DP4_stay_open_time,
			btnLeft_CROSS_use_DP5,
			btnLeft_CROSS_DP5_open_start_delay,
			btnLeft_CROSS_DP5_stay_open_time,
			btnLeft_CROSS_use_DP6,
			btnLeft_CROSS_DP6_open_start_delay,
			btnLeft_CROSS_DP6_stay_open_time,
			btnLeft_CROSS_use_DP7,
			btnLeft_CROSS_DP7_open_start_delay,
			btnLeft_CROSS_DP7_stay_open_time,
			btnLeft_CROSS_use_DP8,
			btnLeft_CROSS_DP8_open_start_delay,
			btnLeft_CROSS_DP8_stay_open_time,
			btnLeft_CROSS_use_DP9,
			btnLeft_CROSS_DP9_open_start_delay,
			btnLeft_CROSS_DP9_stay_open_time,
			btnLeft_CROSS_use_DP10,
			btnLeft_CROSS_DP10_open_start_delay,
			btnLeft_CROSS_DP10_stay_open_time);

#ifdef SHADOW_VERBOSE      
		output += "\nDOME: btnLeft_CROSS";
#endif


		return;

	}

	if (PS3NavDome->getButtonPress(RIGHT) && PS3NavFoot->getButtonPress(CROSS) && marcDuinoButtonCounter == 1)
	{

		marcDuinoButtonPush(1, FTbtnRight_CROSS_MD_func, btnRight_CROSS_cust_MP3_num, btnRight_CROSS_cust_LD_type, btnRight_CROSS_cust_LD_text, btnRight_CROSS_cust_panel,
			btnRight_CROSS_use_DP1,
			btnRight_CROSS_DP1_open_start_delay,
			btnRight_CROSS_DP1_stay_open_time,
			btnRight_CROSS_use_DP2,
			btnRight_CROSS_DP2_open_start_delay,
			btnRight_CROSS_DP2_stay_open_time,
			btnRight_CROSS_use_DP3,
			btnRight_CROSS_DP3_open_start_delay,
			btnRight_CROSS_DP3_stay_open_time,
			btnRight_CROSS_use_DP4,
			btnRight_CROSS_DP4_open_start_delay,
			btnRight_CROSS_DP4_stay_open_time,
			btnRight_CROSS_use_DP5,
			btnRight_CROSS_DP5_open_start_delay,
			btnRight_CROSS_DP5_stay_open_time,
			btnRight_CROSS_use_DP6,
			btnRight_CROSS_DP6_open_start_delay,
			btnRight_CROSS_DP6_stay_open_time,
			btnRight_CROSS_use_DP7,
			btnRight_CROSS_DP7_open_start_delay,
			btnRight_CROSS_DP7_stay_open_time,
			btnRight_CROSS_use_DP8,
			btnRight_CROSS_DP8_open_start_delay,
			btnRight_CROSS_DP8_stay_open_time,
			btnRight_CROSS_use_DP9,
			btnRight_CROSS_DP9_open_start_delay,
			btnRight_CROSS_DP9_stay_open_time,
			btnRight_CROSS_use_DP10,
			btnRight_CROSS_DP10_open_start_delay,
			btnRight_CROSS_DP10_stay_open_time);

#ifdef SHADOW_VERBOSE      
		output += "\nDOME: btnRight_CROSS";
#endif


		return;

	}

	//------------------------------------ 
	// Send triggers for the CIRCLE + base buttons 
	//------------------------------------
	if (PS3NavDome->getButtonPress(UP) && PS3NavFoot->getButtonPress(CIRCLE) && marcDuinoButtonCounter == 1)
	{

		marcDuinoButtonPush(1, FTbtnUP_CIRCLE_MD_func, btnUP_CIRCLE_cust_MP3_num, btnUP_CIRCLE_cust_LD_type, btnUP_CIRCLE_cust_LD_text, btnUP_CIRCLE_cust_panel,
			btnUP_CIRCLE_use_DP1,
			btnUP_CIRCLE_DP1_open_start_delay,
			btnUP_CIRCLE_DP1_stay_open_time,
			btnUP_CIRCLE_use_DP2,
			btnUP_CIRCLE_DP2_open_start_delay,
			btnUP_CIRCLE_DP2_stay_open_time,
			btnUP_CIRCLE_use_DP3,
			btnUP_CIRCLE_DP3_open_start_delay,
			btnUP_CIRCLE_DP3_stay_open_time,
			btnUP_CIRCLE_use_DP4,
			btnUP_CIRCLE_DP4_open_start_delay,
			btnUP_CIRCLE_DP4_stay_open_time,
			btnUP_CIRCLE_use_DP5,
			btnUP_CIRCLE_DP5_open_start_delay,
			btnUP_CIRCLE_DP5_stay_open_time,
			btnUP_CIRCLE_use_DP6,
			btnUP_CIRCLE_DP6_open_start_delay,
			btnUP_CIRCLE_DP6_stay_open_time,
			btnUP_CIRCLE_use_DP7,
			btnUP_CIRCLE_DP7_open_start_delay,
			btnUP_CIRCLE_DP7_stay_open_time,
			btnUP_CIRCLE_use_DP8,
			btnUP_CIRCLE_DP8_open_start_delay,
			btnUP_CIRCLE_DP8_stay_open_time,
			btnUP_CIRCLE_use_DP9,
			btnUP_CIRCLE_DP9_open_start_delay,
			btnUP_CIRCLE_DP9_stay_open_time,
			btnUP_CIRCLE_use_DP10,
			btnUP_CIRCLE_DP10_open_start_delay,
			btnUP_CIRCLE_DP10_stay_open_time);

#ifdef SHADOW_VERBOSE      
		output += "\nDOME: btnUP_CIRCLE";
#endif


		return;

	}

	if (PS3NavDome->getButtonPress(DOWN) && PS3NavFoot->getButtonPress(CIRCLE) && marcDuinoButtonCounter == 1)
	{

		marcDuinoButtonPush(1, FTbtnDown_CIRCLE_MD_func, btnDown_CIRCLE_cust_MP3_num, btnDown_CIRCLE_cust_LD_type, btnDown_CIRCLE_cust_LD_text, btnDown_CIRCLE_cust_panel,
			btnDown_CIRCLE_use_DP1,
			btnDown_CIRCLE_DP1_open_start_delay,
			btnDown_CIRCLE_DP1_stay_open_time,
			btnDown_CIRCLE_use_DP2,
			btnDown_CIRCLE_DP2_open_start_delay,
			btnDown_CIRCLE_DP2_stay_open_time,
			btnDown_CIRCLE_use_DP3,
			btnDown_CIRCLE_DP3_open_start_delay,
			btnDown_CIRCLE_DP3_stay_open_time,
			btnDown_CIRCLE_use_DP4,
			btnDown_CIRCLE_DP4_open_start_delay,
			btnDown_CIRCLE_DP4_stay_open_time,
			btnDown_CIRCLE_use_DP5,
			btnDown_CIRCLE_DP5_open_start_delay,
			btnDown_CIRCLE_DP5_stay_open_time,
			btnDown_CIRCLE_use_DP6,
			btnDown_CIRCLE_DP6_open_start_delay,
			btnDown_CIRCLE_DP6_stay_open_time,
			btnDown_CIRCLE_use_DP7,
			btnDown_CIRCLE_DP7_open_start_delay,
			btnDown_CIRCLE_DP7_stay_open_time,
			btnDown_CIRCLE_use_DP8,
			btnDown_CIRCLE_DP8_open_start_delay,
			btnDown_CIRCLE_DP8_stay_open_time,
			btnDown_CIRCLE_use_DP9,
			btnDown_CIRCLE_DP9_open_start_delay,
			btnDown_CIRCLE_DP9_stay_open_time,
			btnDown_CIRCLE_use_DP10,
			btnDown_CIRCLE_DP10_open_start_delay,
			btnDown_CIRCLE_DP10_stay_open_time);

#ifdef SHADOW_VERBOSE      
		output += "\nDOME: btnDown_CIRCLE";
#endif


		return;

	}

	if (PS3NavDome->getButtonPress(LEFT) && PS3NavFoot->getButtonPress(CIRCLE) && marcDuinoButtonCounter == 1)
	{

		marcDuinoButtonPush(1, FTbtnLeft_CIRCLE_MD_func, btnLeft_CIRCLE_cust_MP3_num, btnLeft_CIRCLE_cust_LD_type, btnLeft_CIRCLE_cust_LD_text, btnLeft_CIRCLE_cust_panel,
			btnLeft_CIRCLE_use_DP1,
			btnLeft_CIRCLE_DP1_open_start_delay,
			btnLeft_CIRCLE_DP1_stay_open_time,
			btnLeft_CIRCLE_use_DP2,
			btnLeft_CIRCLE_DP2_open_start_delay,
			btnLeft_CIRCLE_DP2_stay_open_time,
			btnLeft_CIRCLE_use_DP3,
			btnLeft_CIRCLE_DP3_open_start_delay,
			btnLeft_CIRCLE_DP3_stay_open_time,
			btnLeft_CIRCLE_use_DP4,
			btnLeft_CIRCLE_DP4_open_start_delay,
			btnLeft_CIRCLE_DP4_stay_open_time,
			btnLeft_CIRCLE_use_DP5,
			btnLeft_CIRCLE_DP5_open_start_delay,
			btnLeft_CIRCLE_DP5_stay_open_time,
			btnLeft_CIRCLE_use_DP6,
			btnLeft_CIRCLE_DP6_open_start_delay,
			btnLeft_CIRCLE_DP6_stay_open_time,
			btnLeft_CIRCLE_use_DP7,
			btnLeft_CIRCLE_DP7_open_start_delay,
			btnLeft_CIRCLE_DP7_stay_open_time,
			btnLeft_CIRCLE_use_DP8,
			btnLeft_CIRCLE_DP8_open_start_delay,
			btnLeft_CIRCLE_DP8_stay_open_time,
			btnLeft_CIRCLE_use_DP9,
			btnLeft_CIRCLE_DP9_open_start_delay,
			btnLeft_CIRCLE_DP9_stay_open_time,
			btnLeft_CIRCLE_use_DP10,
			btnLeft_CIRCLE_DP10_open_start_delay,
			btnLeft_CIRCLE_DP10_stay_open_time);

#ifdef SHADOW_VERBOSE      
		output += "\nDome: btnLeft_CIRCLE";
#endif


		return;

	}

	if (PS3NavDome->getButtonPress(RIGHT) && PS3NavFoot->getButtonPress(CIRCLE) && marcDuinoButtonCounter == 1)
	{

		marcDuinoButtonPush(1, FTbtnRight_CIRCLE_MD_func, btnRight_CIRCLE_cust_MP3_num, btnRight_CIRCLE_cust_LD_type, btnRight_CIRCLE_cust_LD_text, btnRight_CIRCLE_cust_panel,
			btnRight_CIRCLE_use_DP1,
			btnRight_CIRCLE_DP1_open_start_delay,
			btnRight_CIRCLE_DP1_stay_open_time,
			btnRight_CIRCLE_use_DP2,
			btnRight_CIRCLE_DP2_open_start_delay,
			btnRight_CIRCLE_DP2_stay_open_time,
			btnRight_CIRCLE_use_DP3,
			btnRight_CIRCLE_DP3_open_start_delay,
			btnRight_CIRCLE_DP3_stay_open_time,
			btnRight_CIRCLE_use_DP4,
			btnRight_CIRCLE_DP4_open_start_delay,
			btnRight_CIRCLE_DP4_stay_open_time,
			btnRight_CIRCLE_use_DP5,
			btnRight_CIRCLE_DP5_open_start_delay,
			btnRight_CIRCLE_DP5_stay_open_time,
			btnRight_CIRCLE_use_DP6,
			btnRight_CIRCLE_DP6_open_start_delay,
			btnRight_CIRCLE_DP6_stay_open_time,
			btnRight_CIRCLE_use_DP7,
			btnRight_CIRCLE_DP7_open_start_delay,
			btnRight_CIRCLE_DP7_stay_open_time,
			btnRight_CIRCLE_use_DP8,
			btnRight_CIRCLE_DP8_open_start_delay,
			btnRight_CIRCLE_DP8_stay_open_time,
			btnRight_CIRCLE_use_DP9,
			btnRight_CIRCLE_DP9_open_start_delay,
			btnRight_CIRCLE_DP9_stay_open_time,
			btnRight_CIRCLE_use_DP10,
			btnRight_CIRCLE_DP10_open_start_delay,
			btnRight_CIRCLE_DP10_stay_open_time);


#ifdef SHADOW_VERBOSE      
		output += "\nDome: btnRight_CIRCLE";
#endif


		return;

	}

	//------------------------------------ 
	// Send triggers for the L1 + base buttons 
	//------------------------------------
	if (PS3NavDome->getButtonPress(UP) && PS3NavDome->getButtonPress(L1) && marcDuinoButtonCounter == 1)
	{

		marcDuinoButtonPush(1, FTbtnUP_L1_MD_func, btnUP_L1_cust_MP3_num, btnUP_L1_cust_LD_type, btnUP_L1_cust_LD_text, btnUP_L1_cust_panel,
			btnUP_L1_use_DP1,
			btnUP_L1_DP1_open_start_delay,
			btnUP_L1_DP1_stay_open_time,
			btnUP_L1_use_DP2,
			btnUP_L1_DP2_open_start_delay,
			btnUP_L1_DP2_stay_open_time,
			btnUP_L1_use_DP3,
			btnUP_L1_DP3_open_start_delay,
			btnUP_L1_DP3_stay_open_time,
			btnUP_L1_use_DP4,
			btnUP_L1_DP4_open_start_delay,
			btnUP_L1_DP4_stay_open_time,
			btnUP_L1_use_DP5,
			btnUP_L1_DP5_open_start_delay,
			btnUP_L1_DP5_stay_open_time,
			btnUP_L1_use_DP6,
			btnUP_L1_DP6_open_start_delay,
			btnUP_L1_DP6_stay_open_time,
			btnUP_L1_use_DP7,
			btnUP_L1_DP7_open_start_delay,
			btnUP_L1_DP7_stay_open_time,
			btnUP_L1_use_DP8,
			btnUP_L1_DP8_open_start_delay,
			btnUP_L1_DP8_stay_open_time,
			btnUP_L1_use_DP9,
			btnUP_L1_DP9_open_start_delay,
			btnUP_L1_DP9_stay_open_time,
			btnUP_L1_use_DP10,
			btnUP_L1_DP10_open_start_delay,
			btnUP_L1_DP10_stay_open_time);

#ifdef SHADOW_VERBOSE      
		output += "\nDome: btnUP_L1";
#endif


		return;

	}

	if (PS3NavDome->getButtonPress(DOWN) && PS3NavDome->getButtonPress(L1) && marcDuinoButtonCounter == 1)
	{

		marcDuinoButtonPush(1, FTbtnDown_L1_MD_func, btnDown_L1_cust_MP3_num, btnDown_L1_cust_LD_type, btnDown_L1_cust_LD_text, btnDown_L1_cust_panel,
			btnDown_L1_use_DP1,
			btnDown_L1_DP1_open_start_delay,
			btnDown_L1_DP1_stay_open_time,
			btnDown_L1_use_DP2,
			btnDown_L1_DP2_open_start_delay,
			btnDown_L1_DP2_stay_open_time,
			btnDown_L1_use_DP3,
			btnDown_L1_DP3_open_start_delay,
			btnDown_L1_DP3_stay_open_time,
			btnDown_L1_use_DP4,
			btnDown_L1_DP4_open_start_delay,
			btnDown_L1_DP4_stay_open_time,
			btnDown_L1_use_DP5,
			btnDown_L1_DP5_open_start_delay,
			btnDown_L1_DP5_stay_open_time,
			btnDown_L1_use_DP6,
			btnDown_L1_DP6_open_start_delay,
			btnDown_L1_DP6_stay_open_time,
			btnDown_L1_use_DP7,
			btnDown_L1_DP7_open_start_delay,
			btnDown_L1_DP7_stay_open_time,
			btnDown_L1_use_DP8,
			btnDown_L1_DP8_open_start_delay,
			btnDown_L1_DP8_stay_open_time,
			btnDown_L1_use_DP9,
			btnDown_L1_DP9_open_start_delay,
			btnDown_L1_DP9_stay_open_time,
			btnDown_L1_use_DP10,
			btnDown_L1_DP10_open_start_delay,
			btnDown_L1_DP10_stay_open_time);

#ifdef SHADOW_VERBOSE      
		output += "\nDome: btnDown_L1";
#endif


		return;

	}

	if (PS3NavDome->getButtonPress(LEFT) && PS3NavDome->getButtonPress(L1) && marcDuinoButtonCounter == 1)
	{

		marcDuinoButtonPush(1, FTbtnLeft_L1_MD_func, btnLeft_L1_cust_MP3_num, btnLeft_L1_cust_LD_type, btnLeft_L1_cust_LD_text, btnLeft_L1_cust_panel,
			btnLeft_L1_use_DP1,
			btnLeft_L1_DP1_open_start_delay,
			btnLeft_L1_DP1_stay_open_time,
			btnLeft_L1_use_DP2,
			btnLeft_L1_DP2_open_start_delay,
			btnLeft_L1_DP2_stay_open_time,
			btnLeft_L1_use_DP3,
			btnLeft_L1_DP3_open_start_delay,
			btnLeft_L1_DP3_stay_open_time,
			btnLeft_L1_use_DP4,
			btnLeft_L1_DP4_open_start_delay,
			btnLeft_L1_DP4_stay_open_time,
			btnLeft_L1_use_DP5,
			btnLeft_L1_DP5_open_start_delay,
			btnLeft_L1_DP5_stay_open_time,
			btnLeft_L1_use_DP6,
			btnLeft_L1_DP6_open_start_delay,
			btnLeft_L1_DP6_stay_open_time,
			btnLeft_L1_use_DP7,
			btnLeft_L1_DP7_open_start_delay,
			btnLeft_L1_DP7_stay_open_time,
			btnLeft_L1_use_DP8,
			btnLeft_L1_DP8_open_start_delay,
			btnLeft_L1_DP8_stay_open_time,
			btnLeft_L1_use_DP9,
			btnLeft_L1_DP9_open_start_delay,
			btnLeft_L1_DP9_stay_open_time,
			btnLeft_L1_use_DP10,
			btnLeft_L1_DP10_open_start_delay,
			btnLeft_L1_DP10_stay_open_time);

#ifdef SHADOW_VERBOSE      
		output += "\nDome: btnLeft_L1";
#endif


		return;

	}

	if (PS3NavDome->getButtonPress(RIGHT) && PS3NavDome->getButtonPress(L1) && marcDuinoButtonCounter == 1)
	{

		marcDuinoButtonPush(1, FTbtnRight_L1_MD_func, btnRight_L1_cust_MP3_num, btnRight_L1_cust_LD_type, btnRight_L1_cust_LD_text, btnRight_L1_cust_panel,
			btnRight_L1_use_DP1,
			btnRight_L1_DP1_open_start_delay,
			btnRight_L1_DP1_stay_open_time,
			btnRight_L1_use_DP2,
			btnRight_L1_DP2_open_start_delay,
			btnRight_L1_DP2_stay_open_time,
			btnRight_L1_use_DP3,
			btnRight_L1_DP3_open_start_delay,
			btnRight_L1_DP3_stay_open_time,
			btnRight_L1_use_DP4,
			btnRight_L1_DP4_open_start_delay,
			btnRight_L1_DP4_stay_open_time,
			btnRight_L1_use_DP5,
			btnRight_L1_DP5_open_start_delay,
			btnRight_L1_DP5_stay_open_time,
			btnRight_L1_use_DP6,
			btnRight_L1_DP6_open_start_delay,
			btnRight_L1_DP6_stay_open_time,
			btnRight_L1_use_DP7,
			btnRight_L1_DP7_open_start_delay,
			btnRight_L1_DP7_stay_open_time,
			btnRight_L1_use_DP8,
			btnRight_L1_DP8_open_start_delay,
			btnRight_L1_DP8_stay_open_time,
			btnRight_L1_use_DP9,
			btnRight_L1_DP9_open_start_delay,
			btnRight_L1_DP9_stay_open_time,
			btnRight_L1_use_DP10,
			btnRight_L1_DP10_open_start_delay,
			btnRight_L1_DP10_stay_open_time);

#ifdef SHADOW_VERBOSE      
		output += "\nDome: btnRight_L1";
#endif


		return;

	}

	//------------------------------------ 
	// Send triggers for the PS + base buttons 
	//------------------------------------
	if (PS3NavDome->getButtonPress(UP) && PS3NavFoot->getButtonPress(PS) && marcDuinoButtonCounter == 1)
	{

		marcDuinoButtonPush(1, FTbtnUP_PS_MD_func, btnUP_PS_cust_MP3_num, btnUP_PS_cust_LD_type, btnUP_PS_cust_LD_text, btnUP_PS_cust_panel,
			btnUP_PS_use_DP1,
			btnUP_PS_DP1_open_start_delay,
			btnUP_PS_DP1_stay_open_time,
			btnUP_PS_use_DP2,
			btnUP_PS_DP2_open_start_delay,
			btnUP_PS_DP2_stay_open_time,
			btnUP_PS_use_DP3,
			btnUP_PS_DP3_open_start_delay,
			btnUP_PS_DP3_stay_open_time,
			btnUP_PS_use_DP4,
			btnUP_PS_DP4_open_start_delay,
			btnUP_PS_DP4_stay_open_time,
			btnUP_PS_use_DP5,
			btnUP_PS_DP5_open_start_delay,
			btnUP_PS_DP5_stay_open_time,
			btnUP_PS_use_DP6,
			btnUP_PS_DP6_open_start_delay,
			btnUP_PS_DP6_stay_open_time,
			btnUP_PS_use_DP7,
			btnUP_PS_DP7_open_start_delay,
			btnUP_PS_DP7_stay_open_time,
			btnUP_PS_use_DP8,
			btnUP_PS_DP8_open_start_delay,
			btnUP_PS_DP8_stay_open_time,
			btnUP_PS_use_DP9,
			btnUP_PS_DP9_open_start_delay,
			btnUP_PS_DP9_stay_open_time,
			btnUP_PS_use_DP10,
			btnUP_PS_DP10_open_start_delay,
			btnUP_PS_DP10_stay_open_time);

#ifdef SHADOW_VERBOSE      
		output += "\nDome: btnUP_PS";
#endif

		return;

	}

	if (PS3NavDome->getButtonPress(DOWN) && PS3NavFoot->getButtonPress(PS) && marcDuinoButtonCounter == 1)
	{

		marcDuinoButtonPush(1, FTbtnDown_PS_MD_func, btnDown_PS_cust_MP3_num, btnDown_PS_cust_LD_type, btnDown_PS_cust_LD_text, btnDown_PS_cust_panel,
			btnDown_PS_use_DP1,
			btnDown_PS_DP1_open_start_delay,
			btnDown_PS_DP1_stay_open_time,
			btnDown_PS_use_DP2,
			btnDown_PS_DP2_open_start_delay,
			btnDown_PS_DP2_stay_open_time,
			btnDown_PS_use_DP3,
			btnDown_PS_DP3_open_start_delay,
			btnDown_PS_DP3_stay_open_time,
			btnDown_PS_use_DP4,
			btnDown_PS_DP4_open_start_delay,
			btnDown_PS_DP4_stay_open_time,
			btnDown_PS_use_DP5,
			btnDown_PS_DP5_open_start_delay,
			btnDown_PS_DP5_stay_open_time,
			btnDown_PS_use_DP6,
			btnDown_PS_DP6_open_start_delay,
			btnDown_PS_DP6_stay_open_time,
			btnDown_PS_use_DP7,
			btnDown_PS_DP7_open_start_delay,
			btnDown_PS_DP7_stay_open_time,
			btnDown_PS_use_DP8,
			btnDown_PS_DP8_open_start_delay,
			btnDown_PS_DP8_stay_open_time,
			btnDown_PS_use_DP9,
			btnDown_PS_DP9_open_start_delay,
			btnDown_PS_DP9_stay_open_time,
			btnDown_PS_use_DP10,
			btnDown_PS_DP10_open_start_delay,
			btnDown_PS_DP10_stay_open_time);

#ifdef SHADOW_VERBOSE      
		output += "\nDome: btnDown_PS";
#endif


		return;

	}

	if (PS3NavDome->getButtonPress(LEFT) && PS3NavFoot->getButtonPress(PS) && marcDuinoButtonCounter == 1)
	{

		marcDuinoButtonPush(1, FTbtnLeft_PS_MD_func, btnLeft_PS_cust_MP3_num, btnLeft_PS_cust_LD_type, btnLeft_PS_cust_LD_text, btnLeft_PS_cust_panel,
			btnLeft_PS_use_DP1,
			btnLeft_PS_DP1_open_start_delay,
			btnLeft_PS_DP1_stay_open_time,
			btnLeft_PS_use_DP2,
			btnLeft_PS_DP2_open_start_delay,
			btnLeft_PS_DP2_stay_open_time,
			btnLeft_PS_use_DP3,
			btnLeft_PS_DP3_open_start_delay,
			btnLeft_PS_DP3_stay_open_time,
			btnLeft_PS_use_DP4,
			btnLeft_PS_DP4_open_start_delay,
			btnLeft_PS_DP4_stay_open_time,
			btnLeft_PS_use_DP5,
			btnLeft_PS_DP5_open_start_delay,
			btnLeft_PS_DP5_stay_open_time,
			btnLeft_PS_use_DP6,
			btnLeft_PS_DP6_open_start_delay,
			btnLeft_PS_DP6_stay_open_time,
			btnLeft_PS_use_DP7,
			btnLeft_PS_DP7_open_start_delay,
			btnLeft_PS_DP7_stay_open_time,
			btnLeft_PS_use_DP8,
			btnLeft_PS_DP8_open_start_delay,
			btnLeft_PS_DP8_stay_open_time,
			btnLeft_PS_use_DP9,
			btnLeft_PS_DP9_open_start_delay,
			btnLeft_PS_DP9_stay_open_time,
			btnLeft_PS_use_DP10,
			btnLeft_PS_DP10_open_start_delay,
			btnLeft_PS_DP10_stay_open_time);

#ifdef SHADOW_VERBOSE      
		output += "\nDome: btnLeft_PS";
#endif


		return;

	}

	if (PS3NavDome->getButtonPress(RIGHT) && PS3NavFoot->getButtonPress(PS) && marcDuinoButtonCounter == 1)
	{

		marcDuinoButtonPush(1, FTbtnRight_PS_MD_func, btnRight_PS_cust_MP3_num, btnRight_PS_cust_LD_type, btnRight_PS_cust_LD_text, btnRight_PS_cust_panel,
			btnRight_PS_use_DP1,
			btnRight_PS_DP1_open_start_delay,
			btnRight_PS_DP1_stay_open_time,
			btnRight_PS_use_DP2,
			btnRight_PS_DP2_open_start_delay,
			btnRight_PS_DP2_stay_open_time,
			btnRight_PS_use_DP3,
			btnRight_PS_DP3_open_start_delay,
			btnRight_PS_DP3_stay_open_time,
			btnRight_PS_use_DP4,
			btnRight_PS_DP4_open_start_delay,
			btnRight_PS_DP4_stay_open_time,
			btnRight_PS_use_DP5,
			btnRight_PS_DP5_open_start_delay,
			btnRight_PS_DP5_stay_open_time,
			btnRight_PS_use_DP6,
			btnRight_PS_DP6_open_start_delay,
			btnRight_PS_DP6_stay_open_time,
			btnRight_PS_use_DP7,
			btnRight_PS_DP7_open_start_delay,
			btnRight_PS_DP7_stay_open_time,
			btnRight_PS_use_DP8,
			btnRight_PS_DP8_open_start_delay,
			btnRight_PS_DP8_stay_open_time,
			btnRight_PS_use_DP9,
			btnRight_PS_DP9_open_start_delay,
			btnRight_PS_DP9_stay_open_time,
			btnRight_PS_use_DP10,
			btnRight_PS_DP10_open_start_delay,
			btnRight_PS_DP10_stay_open_time);

#ifdef SHADOW_VERBOSE      
		output += "\nDome: btnRight_PS";
#endif


		return;

	}

}


// =======================================================================================
// This function handles the processing of custom MarcDuino panel routines
// =======================================================================================
void custMarcDuinoPanel()
{

	// Open & Close Logic: Dome Panel #1
	if (DP1_Status == 1)
	{

		if ((DP1_start + (DP1_s_delay * 1000)) < millis())
		{

			Serial1.print(":OP01\r");
			DP1_Status = 2;
		}

	}

	if (DP1_Status == 2)
	{

		if ((DP1_start + ((DP1_s_delay + DP1_o_time) * 1000)) < millis())
		{

			Serial1.print(":CL01\r");
			DP1_Status = 0;
		}

	}

	// Open & Close Logic: Dome Panel #2
	if (DP2_Status == 1)
	{

		if ((DP2_start + (DP2_s_delay * 1000)) < millis())
		{

			Serial1.print(":OP02\r");
			DP2_Status = 2;
		}

	}

	if (DP2_Status == 2)
	{

		if ((DP2_start + ((DP2_s_delay + DP2_o_time) * 1000)) < millis())
		{

			Serial1.print(":CL02\r");
			DP2_Status = 0;
		}

	}

	// Open & Close Logic: Dome Panel #3
	if (DP3_Status == 1)
	{

		if ((DP3_start + (DP3_s_delay * 1000)) < millis())
		{

			Serial1.print(":OP03\r");
			DP3_Status = 2;
		}

	}

	if (DP3_Status == 2)
	{

		if ((DP3_start + ((DP3_s_delay + DP3_o_time) * 1000)) < millis())
		{

			Serial1.print(":CL03\r");
			DP3_Status = 0;
		}

	}

	// Open & Close Logic: Dome Panel #4
	if (DP4_Status == 1)
	{

		if ((DP4_start + (DP4_s_delay * 1000)) < millis())
		{

			Serial1.print(":OP04\r");
			DP4_Status = 2;
		}

	}

	if (DP4_Status == 2)
	{

		if ((DP4_start + ((DP4_s_delay + DP4_o_time) * 1000)) < millis())
		{

			Serial1.print(":CL04\r");
			DP4_Status = 0;
		}

	}

	// Open & Close Logic: Dome Panel #5
	if (DP5_Status == 1)
	{

		if ((DP5_start + (DP5_s_delay * 1000)) < millis())
		{

			Serial1.print(":OP05\r");
			DP5_Status = 2;
		}

	}

	if (DP5_Status == 2)
	{

		if ((DP5_start + ((DP5_s_delay + DP5_o_time) * 1000)) < millis())
		{

			Serial1.print(":CL05\r");
			DP5_Status = 0;
		}

	}

	// Open & Close Logic: Dome Panel #6
	if (DP6_Status == 1)
	{

		if ((DP6_start + (DP6_s_delay * 1000)) < millis())
		{

			Serial1.print(":OP06\r");
			DP6_Status = 2;
		}

	}

	if (DP6_Status == 2)
	{

		if ((DP6_start + ((DP6_s_delay + DP6_o_time) * 1000)) < millis())
		{

			Serial1.print(":CL06\r");
			DP6_Status = 0;
		}

	}

	// Open & Close Logic: Dome Panel #7
	if (DP7_Status == 1)
	{

		if ((DP7_start + (DP7_s_delay * 1000)) < millis())
		{

			Serial1.print(":OP07\r");
			DP7_Status = 2;
		}

	}

	if (DP7_Status == 2)
	{

		if ((DP7_start + ((DP7_s_delay + DP7_o_time) * 1000)) < millis())
		{

			Serial1.print(":CL07\r");
			DP7_Status = 0;
		}

	}

	// Open & Close Logic: Dome Panel #8
	if (DP8_Status == 1)
	{

		if ((DP8_start + (DP8_s_delay * 1000)) < millis())
		{

			Serial1.print(":OP08\r");
			DP8_Status = 2;
		}

	}

	if (DP8_Status == 2)
	{

		if ((DP8_start + ((DP8_s_delay + DP8_o_time) * 1000)) < millis())
		{

			Serial1.print(":CL08\r");
			DP8_Status = 0;
		}

	}

	// Open & Close Logic: Dome Panel #9
	if (DP9_Status == 1)
	{

		if ((DP9_start + (DP9_s_delay * 1000)) < millis())
		{

			Serial1.print(":OP09\r");
			DP9_Status = 2;
		}

	}

	if (DP9_Status == 2)
	{

		if ((DP9_start + ((DP9_s_delay + DP9_o_time) * 1000)) < millis())
		{

			Serial1.print(":CL09\r");
			DP9_Status = 0;
		}

	}

	// Open & Close Logic: Dome Panel #10
	if (DP10_Status == 1)
	{

		if ((DP10_start + (DP10_s_delay * 1000)) < millis())
		{

			Serial1.print(":OP10\r");
			DP10_Status = 2;
		}

	}

	if (DP10_Status == 2)
	{

		if ((DP10_start + ((DP10_s_delay + DP10_o_time) * 1000)) < millis())
		{

			Serial1.print(":CL10\r");
			DP10_Status = 0;
		}

	}

	// If all the panels have now closed - close out the custom routine
	if (DP1_Status + DP2_Status + DP3_Status + DP4_Status + DP5_Status + DP6_Status + DP7_Status + DP8_Status + DP9_Status + DP10_Status == 0)
	{

		runningCustRoutine = false;

	}
}

// =======================================================================================
//                             Dome Automation Function
//
//    Features toggles 'on' via L2 + CIRCLE.  'off' via L2 + CROSS.  Default is 'off'.
//
//    This routines randomly turns the dome motor in both directions.  It assumes the 
//    dome is in the 'home' position when the auto dome feature is toggled on.  From
//    there it turns the dome in a random direction.  Stops for a random length of 
//    of time.  Then returns the dome to the home position.  This randomly repeats.
//
//    It is driven off the user variable - time360DomeTurn.  This records how long
//    it takes the dome to do a 360 degree turn at the given auto dome speed.  Tweaking
//    this parameter to be close provides the best results.
//
//    Activating the dome controller manually immediately cancels the auto dome feature
//    or you can toggle the feature off by pressing L2 + CROSS.
// =======================================================================================
void autoDome()
{
	long rndNum;
	int domeSpeed;

	if (domeStatus == 0)  // Dome is currently stopped - prepare for a future turn
	{

		if (domeTargetPosition == 0)  // Dome is currently in the home position - prepare to turn away
		{

			domeStartTurnTime = millis() + (random(3, 10) * 1000);

			rndNum = random(5, 354);

			domeTargetPosition = rndNum;  // set the target position to a random degree of a 360 circle - shaving off the first and last 5 degrees

			if (domeTargetPosition < 180)  // Turn the dome in the positive direction
			{

				domeTurnDirection = 1;

				domeStopTurnTime = domeStartTurnTime + ((domeTargetPosition / 360) * time360DomeTurn);

			}
			else  // Turn the dome in the negative direction
			{

				domeTurnDirection = -1;

				domeStopTurnTime = domeStartTurnTime + (((360 - domeTargetPosition) / 360) * time360DomeTurn);

			}

		}
		else  // Dome is not in the home position - send it back to home
		{

			domeStartTurnTime = millis() + (random(3, 10) * 1000);

			if (domeTargetPosition < 180)
			{

				domeTurnDirection = -1;

				domeStopTurnTime = domeStartTurnTime + ((domeTargetPosition / 360) * time360DomeTurn);

			}
			else
			{

				domeTurnDirection = 1;

				domeStopTurnTime = domeStartTurnTime + (((360 - domeTargetPosition) / 360) * time360DomeTurn);

			}

			domeTargetPosition = 0;

		}

		domeStatus = 1;  // Set dome status to preparing for a future turn

#ifdef SHADOW_DEBUG
		output += "Dome Automation: Initial Turn Set\r\n";
		output += "Current Time: ";
		output += millis();
		output += "\r\n Next Start Time: ";
		output += domeStartTurnTime;
		output += "\r\n";
		output += "Next Stop Time: ";
		output += domeStopTurnTime;
		output += "\r\n";
		output += "Dome Target Position: ";
		output += domeTargetPosition;
		output += "\r\n";
#endif

	}


	if (domeStatus == 1)  // Dome is prepared for a future move - start the turn when ready
	{

		if (domeStartTurnTime < millis())
		{

			domeStatus = 2;

#ifdef SHADOW_DEBUG
			output += "Dome Automation: Ready To Start Turn\r\n";
#endif

		}
	}

	if (domeStatus == 2) // Dome is now actively turning until it reaches its stop time
	{

		if (domeStopTurnTime > millis())
		{

			domeSpeed = domeAutoSpeed * domeTurnDirection;

			SyR->motor(domeSpeed);

#ifdef SHADOW_DEBUG
			output += "Turning Now!!:" + String(domeSpeed) + "\r\n";
#endif


		}
		else  // turn completed - stop the motor
		{
			domeStatus = 0;
			SyR->stop();

#ifdef SHADOW_DEBUG
			output += "STOP TURN!!\r\n";
#endif
		}

	}

}

// =======================================================================================
//           Program Utility Functions - Called from various locations
// =======================================================================================

// =======================================================================================
//           PPS3 Controller Device Mgt Functions
// =======================================================================================

void onInitPS3NavFoot()
{
	String btAddress = getLastConnectedBtMAC();
	PS3NavFoot->setLedOn(LED1);
	//PS3NavFoot->setLedRaw();
	isPrimaryPS3NavigatonInitialized = true;
	badPS3Data = 0;

#ifdef SHADOW_DEBUG
	output += "\r\nBT Address of Last connected Device when FOOT PS3 Connected: ";
	output += btAddress;
#endif

	if (btAddress == PS3ControllerFootMac || btAddress == PS3ControllerBackupFootMac || btAddress == PS3ControllerDomeMAC || btAddress == PS3ControllerBackupDomeMAC) {
		//if (btAddress == PS3ControllerFootMac || btAddress == PS3ControllerBackupFootMac) {

#ifdef SHADOW_DEBUG
			output += "\r\nWe have our FOOT controller connected.\r\n";
#endif
		//}
		//else {
#ifdef SHADOW_DEBUG
		//	output += "\r\nLooks like the Dome Controller is connected first.\r\n";
#endif
		//}
		mainControllerConnected = true;
		WaitingforReconnect = true;
	
	}
	else
	{

		// Prevent connection from anything but the MAIN controllers          
#ifdef SHADOW_DEBUG
		output += "\r\nWe have an invalid controller trying to connect as tha FOOT controller, it will be dropped.\r\n";
#endif

		ST->stop();
		SyR->stop();
		isFootMotorStopped = true;
		footDriveSpeed = 0;
		PS3NavFoot->setLedOff(LED1);
		PS3NavFoot->disconnect();
		printOutput();

		isPrimaryPS3NavigatonInitialized = false;
		mainControllerConnected = false;

	}
}

void onInitPS3NavDome()
{
	String btAddress = getLastConnectedBtMAC();
	PS3NavDome->setLedOn(LED1);
	isSecondaryPS3NavigatonInitialized = true;
	badPS3Data = 0;

	if (btAddress == PS3ControllerFootMac || btAddress == PS3ControllerBackupFootMac || btAddress == PS3ControllerDomeMAC || btAddress == PS3ControllerBackupDomeMAC) {
		//if (btAddress != PS3ControllerDomeMAC && btAddress != PS3ControllerBackupDomeMAC) {
		//	swapPS3NavControllers();
		//}
		
#ifdef SHADOW_DEBUG
			output += "\r\nWe have our DOME controller connected.\r\n";
#endif
		
		domeControllerConnected = true;
		WaitingforReconnectDome = true;

	}
	else
	{

		// Prevent connection from anything but the DOME controllers          
#ifdef SHADOW_DEBUG
		output += "\r\nWe have an invalid controller trying to connect as the DOME controller, it will be dropped.\r\n";
#endif

		ST->stop();
		SyR->stop();
		isFootMotorStopped = true;
		footDriveSpeed = 0;
		PS3NavDome->setLedOff(LED1);
		PS3NavDome->disconnect();
		printOutput();

		isSecondaryPS3NavigatonInitialized = false;
		domeControllerConnected = false;

	}
}

String getLastConnectedBtMAC()
{
	String btAddress = "";
	for (int8_t i = 5; i > 0; i--)
	{
		if (Btd.disc_bdaddr[i]<0x10)
		{
			btAddress += "0";
		}
		btAddress += String(Btd.disc_bdaddr[i], HEX);
		btAddress += (":");
	}
	btAddress += String(Btd.disc_bdaddr[0], HEX);
	btAddress.toUpperCase();
	return btAddress;
}

void swapPS3NavControllers()
{
	PS3BT* temp = PS3NavFoot;
	PS3NavFoot = PS3NavDome;
	PS3NavDome = temp;
	//Correct the status for Initialization
	boolean tempStatus = isPrimaryPS3NavigatonInitialized;
	isPrimaryPS3NavigatonInitialized = isSecondaryPS3NavigatonInitialized;
	isSecondaryPS3NavigatonInitialized = tempStatus;
	//Must relink the correct onInit calls
	//PS3NavFoot->attachOnInit(onInitPS3NavFoot);
	//PS3NavDome->attachOnInit(onInitPS3NavDome);
	
}

boolean criticalFaultDetect()
{
	if (PS3NavFoot->PS3NavigationConnected || PS3NavFoot->PS3Connected)
	{

		currentTime = millis();
		lastMsgTime = PS3NavFoot->getLastMessageTime();
		msgLagTime = currentTime - lastMsgTime;

		if (WaitingforReconnect)
		{

			if (msgLagTime < 200)
			{

				WaitingforReconnect = false;

			}

			lastMsgTime = currentTime;

		}

		if (currentTime >= lastMsgTime)
		{
			msgLagTime = currentTime - lastMsgTime;

		}
		else
		{

			msgLagTime = 0;
		}

		if (msgLagTime > 300 && !isFootMotorStopped)
		{
#ifdef SHADOW_DEBUG
			output += "It has been 300ms since we heard from the PS3 Foot Controller\r\n";
			output += "Shut downing motors, and watching for a new PS3 Foot message\r\n";
#endif
			ST->stop();
			isFootMotorStopped = true;
			footDriveSpeed = 0;
		}

		if (msgLagTime > 10000)
		{
#ifdef SHADOW_DEBUG
			output += "It has been 10s since we heard from the PS3 Foot Controller\r\n";
			output += "msgLagTime:";
			output += msgLagTime;
			output += "  lastMsgTime:";
			output += lastMsgTime;
			output += "  millis:";
			output += millis();
			output += "\r\nDisconnecting the Foot controller.\r\n";
#endif
			ST->stop();
			isFootMotorStopped = true;
			footDriveSpeed = 0;
			PS3NavFoot->disconnect();
			WaitingforReconnect = true;
			return true;
		}

		//Check PS3 Signal Data
		if (!PS3NavFoot->getStatus(Plugged) && !PS3NavFoot->getStatus(Unplugged))
		{
			//We don't have good data from the controller.
			//Wait 15ms if no second controller - 100ms if some controller connected, Update USB, and try again
			if (PS3NavDome->PS3NavigationConnected)
			{
				delay(100);
			}
			else
			{
				delay(15);
			}

			Usb.Task();
			lastMsgTime = PS3NavFoot->getLastMessageTime();

			if (!PS3NavFoot->getStatus(Plugged) && !PS3NavFoot->getStatus(Unplugged))
			{
				badPS3Data++;
#ifdef SHADOW_DEBUG
				output += "\r\n**Invalid data from PS3 FOOT Controller. - Resetting Data**\r\n";
#endif
				return true;
			}
		}
		else if (badPS3Data > 0)
		{

			badPS3Data = 0;
		}

		if (badPS3Data > 10)
		{
#ifdef SHADOW_DEBUG
			output += "Too much bad data coming from the PS3 FOOT Controller\r\n";
			output += "Disconnecting the controller and stop motors.\r\n";
#endif
			ST->stop();
			isFootMotorStopped = true;
			footDriveSpeed = 0;
			PS3NavFoot->disconnect();
			WaitingforReconnect = true;
			return true;
		}
	}
	else if (!isFootMotorStopped)
	{
#ifdef SHADOW_DEBUG      
		output += "No foot controller was found\r\n";
		output += "Shuting down motors and watching for a new PS3 foot message\r\n";
#endif
		ST->stop();
		isFootMotorStopped = true;
		footDriveSpeed = 0;
		WaitingforReconnect = true;
		return true;
	}

	return false;
}

boolean criticalFaultDetectDome()
{
	if (PS3NavDome->PS3NavigationConnected || PS3NavDome->PS3Connected)
	{

		currentTime = millis();
		lastMsgTime = PS3NavDome->getLastMessageTime();
		msgLagTime = currentTime - lastMsgTime;

		if (WaitingforReconnectDome)
		{
			if (msgLagTime < 200)
			{

				WaitingforReconnectDome = false;

			}

			lastMsgTime = currentTime;

		}

		if (currentTime >= lastMsgTime)
		{
			msgLagTime = currentTime - lastMsgTime;

		}
		else
		{
			msgLagTime = 0;
		}

		if (msgLagTime > 10000)
		{
#ifdef SHADOW_DEBUG
			output += "It has been 10s since we heard from the PS3 Dome Controller\r\n";
			output += "msgLagTime:";
			output += msgLagTime;
			output += "  lastMsgTime:";
			output += lastMsgTime;
			output += "  millis:";
			output += millis();
			output += "\r\nDisconnecting the Dome controller.\r\n";
#endif

			SyR->stop();
			PS3NavDome->disconnect();
			WaitingforReconnectDome = true;
			return true;
		}

		//Check PS3 Signal Data
		if (!PS3NavDome->getStatus(Plugged) && !PS3NavDome->getStatus(Unplugged))
		{

			// We don't have good data from the controller.
			//Wait 100ms, Update USB, and try again
			delay(100);

			Usb.Task();
			lastMsgTime = PS3NavDome->getLastMessageTime();

			if (!PS3NavDome->getStatus(Plugged) && !PS3NavDome->getStatus(Unplugged))
			{
				badPS3DataDome++;
#ifdef SHADOW_DEBUG
				output += "\r\n**Invalid data from PS3 Dome Controller. - Resetting Data**\r\n";
#endif
				return true;
			}
		}
		else if (badPS3DataDome > 0)
		{
			badPS3DataDome = 0;
		}

		if (badPS3DataDome > 10)
		{
#ifdef SHADOW_DEBUG
			output += "Too much bad data coming from the PS3 DOME Controller\r\n";
			output += "Disconnecting the controller and stop motors.\r\n";
#endif
			SyR->stop();
			PS3NavDome->disconnect();
			WaitingforReconnectDome = true;
			return true;
		}
	}

	return false;
}

// =======================================================================================
//           USB Read Function - Supports Main Program Loop
// =======================================================================================

boolean readUSB()
{

	Usb.Task();

	//The more devices we have connected to the USB or BlueTooth, the more often Usb.Task need to be called to eliminate latency.
	if (PS3NavFoot->PS3NavigationConnected)
	{
		if (criticalFaultDetect())
		{
			//We have a fault condition that we want to ensure that we do NOT process any controller data!!!
			printOutput();
			return false;
		}

	}
	else if (!isFootMotorStopped)
	{
#ifdef SHADOW_DEBUG      
		output += "No foot controller was found\r\n";
		output += "Shuting down motors, and watching for a new PS3 foot message\r\n";
#endif
		ST->stop();
		isFootMotorStopped = true;
		footDriveSpeed = 0;
		WaitingforReconnect = true;
	}

	if (PS3NavDome->PS3NavigationConnected)
	{

		if (criticalFaultDetectDome())
		{
			//We have a fault condition that we want to ensure that we do NOT process any controller data!!!
			printOutput();
			return false;
		}
	}

	return true;
}

// =======================================================================================
//          Print Output Function
// =======================================================================================

void printOutput()
{
	if (output != "")
	{
		if (Serial) Serial.println(output);
		output = ""; // Reset output string
	}
}

boolean bCommandIn = false;

void fastLEDs()
{

	if (currentMillis - fastLEDMillis > 500) {
		//output += "Leds Update\r\n";
		//statusLED_Power, statusLED_Radio, statusLED_LED3, statusLED_LED4, statusLED_LED5, statusLED_DomePower, statusLED_DriveNav, statusLED_DomeNav, statusLED_Count

		//
		// 1 Power enabled haw haw
		//
		statusLEDs[statusLED_Power] = colourPowerLED;


		//
		// 2 Radio / USB initialized
		//
		colourRadioLED.hue = Usb.Init()==0 ? HUE_GREEN: HUE_RED;
		colourRadioLED.v = colourRadioLED.hue == HUE_RED ? 0 : 128;
		statusLEDs[statusLED_Radio] = colourRadioLED;

		//
		//3
		//
		colourCommandLED.hue = bCommandIn == true ? HUE_GREEN : HUE_RED;
		colourCommandLED.v = colourCommandLED.hue == HUE_RED ? 0 : 128;
		statusLEDs[statusLED_Command] = colourCommandLED;

		//
		//4
		//
		//
		//5
		//
		//
		//6
		//
		//colourDomePower.hue =  ? HUE_GREEN: HUE_RED;
		statusLEDs[statusLED_DomePower] = colourDomePower;

		//
		// 7 Foot controller connected
		//
		colourDriveNav.hue = PS3NavFoot->PS3NavigationConnected ? (isStickEnabled ? HUE_GREEN : HUE_ORANGE): HUE_RED;
		colourDriveNav.v = colourDriveNav.hue == HUE_RED ? 0 : 128;
		statusLEDs[statusLED_DriveNav] = colourDriveNav;

		//
		// 8 Dome Controller connected
		//
		colourDomeNav.hue = PS3NavDome->PS3NavigationConnected ? HUE_GREEN : HUE_RED;
		colourDomeNav.v = colourDomeNav.hue == HUE_RED ? 0 : 128;
		statusLEDs[statusLED_DomeNav] = colourDomeNav;

		FastLED.show();
		fastLEDMillis = millis();
	}

}

#define STATUSLEDMSECS 200                 // Amount of time to flash the led pin
unsigned long ledtimer = 0;


/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////                                                                                               /////
/////                            Onboard LED Communication Status Trigger                           /////
/////                                                                                               /////
///// statusLEDOn - Turn on the LED                                                                 /////
///// statusLEDCheck - Check if enough time has passed and we should turn off the LED               /////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////// 
void statusLEDOn() {
	digitalWrite(pinOut_StatusLED, HIGH);
	//colourCommandLED 
	bCommandIn = true;
	ledtimer = millis();
}

void statusLEDCheck() {
	if (millis() - ledtimer >= STATUSLEDMSECS) {
		digitalWrite(pinOut_StatusLED, LOW);
		bCommandIn = false;

	}
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////                                                                                               /////
/////                             Serial & I2C Communication Functions                              /////
/////                                                                                               /////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////  


/////////////////////////////////////////////////////////
///*****          Serial Event Function          *****///
/////////////////////////////////////////////////////////
/// This routine is run between loop() runs, so using ///
/// delay inside loop can delay response.  Multiple   ///
/// bytes of data may be available.                   ///
/////////////////////////////////////////////////////////

void serialEvent() {
	while (Serial.available()) {                         // Loop through all incoming bytes
		char inChar = (char)Serial.read();                 // Receive each byte as a character        
		if (inChar == '\r' || inChar == '\n') {            // if the incoming character is a carriage return (\r) or newline (\n), it denotes end of command
			if (inputString.length() > 1 && inputString.length() < 128)
				stringComplete = true;                           // Once done, set a flag so the main loop can do something about it.
			else
				inputString = "";								// throwaway any strings that are greater than 128 chars 
		}
		else {
			inputString += inChar;                           // Add each Character to inputString     
		}
		statusLEDOn();
	}
}
/////////////////////////////////////////////////////////
///*****            I2C Event Function           *****///
/////////////////////////////////////////////////////////
///  This routine is run when an onRecieve event is   ///
///     triggered.  Multiple bytes of data may be     ///
///                    available.                     ///
/////////////////////////////////////////////////////////            

void i2cEvent(int howMany)
{
	inputString = "";                                     // Ensures inputString is empty
	int i = 0;
	while (Wire.available()) {                            // loop through all incoming bytes
		char inChar = (char)Wire.read();                    // Receive each byte as a character
		if (i<MAXCOMMANDLENGTH) {
			inputString += inChar;                           // Add each Character to inputString
		}
		i++;
	}
	stringComplete = true;                                // Once done, set a flag so the main loop can do something about it. 
	statusLEDOn();
}

