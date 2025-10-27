# 43_minitalk

### Notes

Project works right now. It is pretty much what I did last time around.
I'm using printf since I haven't recoded it yet. Will change.

Message is written to a buffer (in a chained list with CHUNKSIZE macro).
Ran tests on buffer, everything is always properly freed even in case of errors.

Simplified macros so there are less values to modify. Used the lowest values that do not cause errors.
The lower the values, the faster the program, but the more errors creep up. There are 2 types of errors:
	1. Too little delay when sending PID causes bad PID according to server. Bits get mixed up and server can eventually write a "valid" PID that is negative, or much too high.
	   This can theoretically be improved by not accepting 32 bits of PID but 15 instead as I did last time, but depending on the arch of your system, you might have up to 22-bit PIDs apparently, so I'm remiss about changing that.
	2. Too little delay when sending msg causes extra bits to get received. If extra bits are multiple of 8, server might print a bad message, or it might just timeout otherwise. Currently, client has no way of knowing whether this happened.
I could fix these (see ideas below) but choosing proper delay values already makes it virtually impossible for any errors to happen.
I'm moving on to other projects but when I do come back to this one, I might do a complete re-write or think up crazy improvements that could be super fun to implement.



### Quick improvements that I can make

- Make server send a final confirmation signal to indicate that the string is received, and correct.
	- This fixes the client thinking the message was properly sent when the server actually skipped some bits and an "incomplete" message was detected. Client should just usleep for a set delay after receiving last response, and server should just send a last response before printing (or none if not). Client will know whether the server got a full message or not.



### Complete rewrites or fun stuff I could do

- Do the project with 1 signal
	- The absence of a signal is a signal. It should be doable with only 1 signal. But I haven't thought about how to implement a frequency that both programs will use to send/receive. And you need a certain encoding to start a message since the absence of a signal can be 0's.

- Use a different encoding. I'm encoding bits as 0 = SIGUSR1 and 1 = SIGUSR2, but this has limitations. There are other ways to encode, such as 0 = SIGUSR1 SIGUSR1 and 1 = SIGUSR2 SIGUSR2. There can also be rules, such as a 0 preceded by a 0 has a different sequence such as SIGUSR1 SIGUSR2.
  The point of this is to better handle errors and skipped bits. The way I did the project is the most basic naive approach. But there must be better ways to do it that allow for much more robust communication protocols between client and server, with almost no potential for miscommunication.

- It can also be possible for the server to send a byte to the client as a confirmation. If I do this, my communication is already much more robust than what I did, but the speed is halved. And also, errors are still possible if by chance a bad byte sent back to the client becomes good again due to errors.
