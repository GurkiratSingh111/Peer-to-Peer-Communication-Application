S-talk: Short for simple-talk, S-talk is a CLI chat interface for machines connected locally. It is a UDP two-way text chat.

Description: There are 4 threads that handle different tasks and two mutex lockers are applied to two buffers (sendBuff and receiveBuff).

s-talk provides two-way local communication but only if the two users know the other's ip and listening socket information and firewalls don't get in the way (which they often do).

Arguments passed as ./s-talk (local port) (remote ip address) (remote port).

Linux supported and MacOS is supported with make macos.

How to test the code
step 1: complie the code by typing "make"

step 2: open two terminals and within each of them, typing

"s-talk [local port number] [remote machine name] [remote port name]"

for example: terminal 1: s-talk 8080 localhost 8081 terminal 2: s-talk 8081 localhost 8080

To terminate the talking, type "!"

Author

Gurkirat Singh Arora

