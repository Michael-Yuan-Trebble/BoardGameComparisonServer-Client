# BoardGameComparisonServer&Client

This is a server and client program that handles values that should only be seen by the server and client for board games, for instance some rolls must be made privately as to not spoil an event and this program streamlines all rolls into one program.

## Features

Currently there are three applications, the client, the server, and an application that boots both at the same time for testing purposes. The server uses IP 127.0.0.1 and port 54000 for testing purposes, however do have the ability to switch to a certain IP on the client's side. 

### Client Application

The client application can connect to a server through inputting the IP and port, I plan to make port connecting dynamic instead of the user inputting one in the future. Then it prompts the user to either load in a file or create a new file, this will have data about certain dice rolls, values that should be kept between usages, and settings.

### Server Application

The server application immediately opens up a port and starts scanning for incoming clients, then dynamically updates a qtable to show what clients are currently connected and what port they are using. The server scans through a qobject on a different thread through a worker and emits signals telling the main application about updates. When the user rolls a dice, it reaches the server, which then does its own roll and returns true or false based on if it was higher or not.

### Testing Application

Just creates both of the applications on different threads in order to help testing.

## Tech Stack
- C++ 20
  - Winsock2
- Qt6

## Futures Plans
- In the future I plan to flesh out the Client Application more and include more features in order for it to be used in more cases
- Server Application has more screens telling more information and can click buttons to do actions such as requesting something from the client
- Strengthen security and connection
