#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

/**
 * main - prints pid and parent pid
 *
 * Return: Always 0
 */

int main(void)
{
	pid_t pid, ppid;

	pid = getpid();
	ppid = getppid();

	printf("Process ID is %u\n", pid);
	printf("Parent process ID is %u\n", ppid);

	return (0);
}
