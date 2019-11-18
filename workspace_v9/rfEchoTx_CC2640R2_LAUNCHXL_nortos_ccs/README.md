# rfEchoTx
---

### SysConfig Notice

All examples will soon be supported by SysConfig, a tool that will help you 
graphically configure your software components. A preview is available today in 
the examples/syscfg_preview directory. Starting in 3Q 2019, with SDK version 
3.30, only SysConfig-enabled versions of examples will be provided. For more 
information, click [here](http://www.ti.com/sysconfignotice).

-------------------------

Project Setup using the System Configuration Tool (SysConfig)
-------------------------
The purpose of SysConfig is to provide an easy to use interface for configuring 
drivers, RF stacks, and more. The .syscfg file provided with each example 
project has been configured and tested for that project. Changes to the .syscfg 
file may alter the behavior of the example away from default. Some parameters 
configured in SysConfig may require the use of specific APIs or additional 
modifications in the application source code. More information can be found in 
SysConfig by hovering over a configurable and clicking the question mark (?) 
next to it's name.

Example Summary
---------------
In this example you will learn how to setup the radio to do bi-directional 
communication. The Echo TX example the radio to transmit a packet and then 
switch over to the receiver mode and wait for its echo. This example is meant 
to be used with the Echo RX example or SmartRF Studio. For every packet echo, 
Board_PIN_LED1 is toggled. The frequency and other RF settings can be modified 
using SmartRF Studio.

Peripherals Exercised
---------------------
* `Board_PIN_LED1` - Blinking indicates a successful transmission and reception
  of a packet (echo)
* `Board_PIN_LED2` - Indicates an abort occurred in packet reception (waiting 
  for the echo)
* `Board_PIN_LED1` & `Board_PIN_LED2` indicate an error condition

Resources & Jumper Settings
---------------------------
> If you're using an IDE (such as CCS or IAR), please refer to Board.html in 
your project directory for resources used and board-specific jumper settings. 
Otherwise, you can find Board.html in the directory 
&lt;SDK_INSTALL_DIR&gt;/source/ti/boards/&lt;BOARD&gt;.

Example Usage
-------------
The user will require two launchpads, one running rfEchoTx (`Board_1`), 
another running rfEchoRx (`Board_2`). Run Board_2 first, followed by 
Board_1. Board_1 is set to transmit a packet every second while Board_2 is 
set to receive the packet and then turnaround and transmit it after a delay of
100ms. Board_PIN_LED1 on Board_1 will toggle when it's able to successfully 
transmits a packet, and when it receives its echo. Board_PIN_LED2 on Board_2 
will toggle when it receives a packet, and then when its able to 
re-transmit it (see [figure 1]).

![perfect_echo_ref][figure 1]

If the receiver (`Board_2`) is turned off and the rfEchoTx (`Board_1`) begins 
transmitting, it switches over to the receiver mode waiting for an echo that 
will never come; in this situation a timeout timer is started and if no 
packet is received within 300ms the receiver operation is aborted. This 
condition is indicated by Board_PIN_LED1 being cleared and Board_PIN_LED2 
being set (see [figure 2]).

![missed_first_ref][figure 2]

If the receiver continues to stay turned off then the rfEchoTx example will 
alternate between transmitting and aborted receiver operations. Board_PIN_LED1
and Board_PIN_LED2 will start alternating, as seen in [figure 3].

![missed_first_few_ref][figure 3]

An error in transmission of a packet, or the reception of its echo, is 
indicated by both LEDs going high (see [figure 4]).

![echo_error_ref][figure 4]

Application Design Details
--------------------------
This examples consists of a single task and the exported SmartRF Studio radio
settings.

The default frequency is 868.0 MHz (433.92 MHz for the 
CC1350-LAUNCHXL-433 board and CC1352P-4-LAUNCHXL boards). In order to change frequency, modify the
smartrf_settings.c file. This can be done using the code export feature in
Smart RF Studio, or directly in the file.

When the task is executed it:

1. Configures the radio for Proprietary mode
2. Gets access to the radio via the RF drivers RF_open
3. Sets up the radio using CMD_PROP_RADIO_DIV_SETUP command
4. Set the output power to 14 dBm (requires that CCFG_FORCE_VDDR_HH = 1 in ccfg.c)
5. Sets the frequency using CMD_FS command
6. Create packet (with increasing sequence number and random content)
7. Set absolute TX time to utilize automatic power management
8. Transmit packet using CMD_PROP_TX command with blocking RF driver call, in
   which case Board_PIN_LED1 is toggled. The transmit command is chained with 
   the receive command, CMD_PROP_RX, which runs immediately after the packet 
   is transmitted
9. The radio waits for the echo and there are three possibilities
   a. echo is successfully received and Board_PIN_LED1 is toggled
   b. receive operation times out and Board_PIN_LED2 is set
   c. unexpected radio event, an error, in which case both LEDs are set
10. Transmit packets forever by repeating step 6-9

Note for IAR users: When using the CC1310DK, the TI XDS110v3 USB Emulator must
be selected. For the CC1310_LAUNCHXL, select TI XDS110 Emulator. In both cases,
select the cJTAG interface.


[figure 1]:rfEcho_PerfectEcho.png "Perfect Echo"
[figure 2]:rfEcho_MissedFirstPacket.png "Missed First Packet"
[figure 3]:rfEcho_MissingFirstCouplePackets.png "Missing First Couple of Packets"
[figure 4]:rfEcho_ErrorTxRx.png "Echo Error"