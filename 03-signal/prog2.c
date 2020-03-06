#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

volatile bool done = false;

void onSigAlarm(int sig) {
	done = true;
}

void onSigTerm(int sig) {
	fprintf(stderr, "Can't terminate.\n");
}

void onSigInt(int sig) {
	fprintf(stderr, "Can't be interrupted.\n");
}

int main() {
	struct sigaction actionAlarm;
	memset(&actionAlarm, 0, sizeof (struct sigaction));
	actionAlarm.sa_handler = onSigAlarm;
	
	struct sigaction actionTerm;
	memset(&actionTerm, 0, sizeof (struct sigaction));
	actionTerm.sa_handler = onSigTerm;
	
	struct sigaction actionInt;
	memset(&actionInt, 0, sizeof (struct sigaction));
	actionInt.sa_handler = onSigInt;
	
	sigaction(SIGALRM, &actionAlarm, NULL);
	sigaction(SIGTERM, &actionTerm, NULL);
	sigaction(SIGINT, &actionInt, NULL);
	
	alarm(8);
	
	printf("Running...\n");

	while (!done) {
		sleep(1);
	}

	printf("END\n");
	return 0;
}
