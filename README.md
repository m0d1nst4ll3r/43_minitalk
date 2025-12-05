# 43\_minitalk

### Post-grading update

This project went well and is OK *but* it could be way better.

Sigaction allows us to set some flags including siginfo (or something along those lines) which, amongst other things, allows you to get the pid of the signal's *sender*.

Using this would allow us to improve the program by *a lot*. Wouldn't have to send the pid from the client bit by bit (how tedious), and could simultaneously receive messages from *multiple* clients all at once (like get_next_line does multiple fds).

I could definitely, and actually will, redo this entirely with the new info. But the project is turned in now, so we've got no ETA.

### Notes

Project went through a quick rewrite. Before, the server wouldn't verify much (not even if pid was < 0). The message would also be stored in a chained list.

Now, the server verifies the PID, the server and client share a single handshake byte (this catches most errors), the client shares message length with the server (this allows us to skip the chained list and simply malloc), and the server tells the client when it's done filling its string so the client can know if the server desynched. The client and server then share a last handshake byte before the server finally prints everything.

This way of doing things catches 100% of errors even when the server is bombarbed with random data from multiple clients, whereas before the server could catch bad PIDs and write bad messages.

We could skip the handshake parts, especially the first, but in case of errors it will just catch them faster, and the performance hit is trivial for such a simple project.

Note that the handshake can possibly succeed even with jumbled bits (it is only 8 bits after all), in which case the server will read an erroneous message length and possibly try to malloc absurd amounts of memory. It might allocate a very large amount of memory (but not large enough for malloc to fail) and continue writing in there as long as it's receiving bits. However as soon as it stops receiving bits for some milliseconds, it will abort and free the memory.

### Quick improvement ideas

...

### Complete rewrites or fun stuff we could do

- Do the project with 1 signal
	- The absence of a signal is a signal. It should be doable with only 1 signal. But I haven't thought about how to implement a frequency that both programs will use to send/receive. And you need a certain encoding to start a message since the absence of a signal can be 0's.

- Use a different encoding. I'm encoding bits as 0 = SIGUSR1 and 1 = SIGUSR2, but this has limitations. There are other ways to encode, such as 0 = SIGUSR1 SIGUSR1 and 1 = SIGUSR2 SIGUSR2. There can also be rules, such as a 0 preceded by a 0 has a different sequence such as SIGUSR1 SIGUSR2.
  The point of this is to better handle errors and skipped bits. The way I did the project is the most basic naive approach. But there must be better ways to do it that allow for much more robust communication protocols between client and server, with almost no potential for miscommunication.

- It can also be possible for the server to send back the byte it got to the client as a confirmation. If I do this, my communication is already much more robust than what I did, but the speed is halved. And also, errors are still possible if by chance a bad byte sent back to the client becomes good again due to errors. This would also allow the client to backtrack and possibly correct errors. In fact, this could make a server-client communication channel very resilient to noise as long as the server got the client's PID.
