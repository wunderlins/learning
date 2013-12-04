#include <stdio.h>
#include <stdlib.h>
#include <libgen.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
//#include <sys/stat.h> /* struct stat, fchmod (), stat (), S_ISREG, S_ISDIR */

#define DEBUG 1
#define PATH_SEPERATOR "/"

#define NUM_ACTIONS 2
const char* action[NUM_ACTIONS]       = {"apt-get", "apt-cache"};
const char action_root[NUM_ACTIONS]   = {true,      false};
const char action_code[NUM_ACTIONS]   = {'i',       's'};
const char* action_param[NUM_ACTIONS] = {"install", "search"};
#define NUM_SU_EXEC 2
const char* su_exec[NUM_SU_EXEC]      = {"sudo", "su"};

int main(int argc, char **argv, char **envp) { 
	
	// this programm should not be called directly. create a link for every 
	// command. "apt-get install" could be called as pki ("i" for install) whereis
	// the executable is actually pk (sym- or hardlink pointing from pki to pk).
	//
	// the last character in the exec name defines the action,
	// extract last character
	char* file = basename(argv[0]);
	size_t len = strlen(file);
	
	if (len < 2) {
		printf("exec name too short. the name of the executable must be at "
		       "least 2 chars.\n");
		return 1;
	}
	
	char action = file[len-1];
	
	#if DEBUG > 0
		printf("%s %d %c\n", file, (int) len, action);
	#endif
	
	// check if this action is known
	bool found = false;
	int  index_action = 0;
	for (int i=0; i<NUM_ACTIONS; i++) {
		if (action == action_code[i]) {
			found = true;
			index_action = i;
			break;
		}
	}
	
	if (!found) {
		printf("unknown action.\n");
		return 2;
	}
	
	// check if we need super user privileges and if we have it
	char* su_executable = NULL;
	if (action_root[index_action]) {
		//uid_t uid=getuid(), euid=geteuid();
		
		#if DEBUG > 0
			printf("We need usper user rights, maybe?\n");
		#endif
		
		// check for sudo and su, in this order
		const char* PATH = getenv("PATH");
		
		#if DEBUG > 0
			printf("PATH %s\n", PATH);
		#endif
		
		for(int i=0; i<NUM_SU_EXEC; i++) {
			char *ch;
			char p[2000];
			strcpy(p, PATH);
			ch = strtok(p, ":");
			while (ch != NULL) {
				
				char f[2000] = "";
				strcat(f, ch);
				strcat(f, PATH_SEPERATOR);
				strcat(f, su_exec[i]);
				
				// check if file exists and is executable, if so, abort loop and 
				// remeber it
				// FIXME: check if found file is executable
				
				// check if the file exists
				if (access(f, X_OK) == 0) {
					su_executable = f;
					i = NUM_SU_EXEC; // break outer for loop
					break; // break inner while loop
				}
				
				#if DEBUG > 0
					printf("%s %s\n", su_exec[i], f);
				#endif
				
				ch = strtok(NULL, ":");
			}
		}
		
		//printf("a\n");
		//printf("%s\n", su_executable);
		if (!su_executable) {
			printf("Needed elevated privileges, no exec found.\n");
			return 3;
		}
		
		#if DEBUG > 0
			printf("Found su_exec: %s\n", su_executable);
		#endif
	}
	
	// construct command line
	char command[2500] = "";
	if (su_executable != NULL) {
		strcat(command, su_executable);
		strcat(command, " ");
	}
	
	
	

	return EXIT_SUCCESS;
}
