# Minitalk

The purpose of this project is to code a small data exchange program using UNIX signals. The project consists of creating a client and server that communicate with each other using signals.

## Functionality

The project consists of two binaries, a 'server' and a 'client'. The client sends a message to the server which then prints that message out in the terminal.  
The server is able to handle multiple clients simultaneously by handling only one message at a time. The other clients will wait for 10 seconds and try again. If after a minute there is still no response the client gives up.

## Usage

Clone the project and use make in the repository. This will compile both binaries.  
First run the server, which will display the server PID on the standard output. Then run the client with 2 arguments, the first one being the PID of the server and the second one being the message you want the server to print.  
If you want to test the project just run the tester.sh with the PID of the server as the first argument.

## Implementation

The project allows the usage of only two signals: SIGUSR1 and SIGUSR2. Because of this the message passed through the client needs to be broken down into bit representation (SIGUSR1 for bit 1, SIGUSR2 for bit 0).  
First the client probes the server to see if it's ready to receive a message. If it's not the client will try again in 10 seconds. If it is ready the server will save the clients PID and send a signal back to confirm readiness.  
Next the client will calculate the message length and send that to the server, so the server can allocate enough memory for the incoming message. This is the first 64 bits that the server receives after the initial probing.  
After this the client will send the characters in the message one by one including the null-terminator. Once the server receives the null-terminator it will print the message and set a flag to get ready for the next message.  
The client waits for confirmation from the server after every sent signal. Confirmation is sent through a SIGUSR1 by the server once it is done handling the received signal. If there is no confirmation the client will try sending the same signal again every 3s.  
Whenever the server receives a signal it checks if the signal sent belongs to the client it is currently handling. If it's not it will discard the signal.  
In case of malloc failure on the server side, the server will send a SIGUSR2 to the client telling it to shut down.
