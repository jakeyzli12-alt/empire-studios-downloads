/* Empire Studios for Mac: the app's main program. Apple only notarizes apps whose main
   executable is a real (signed) program, so this tiny launcher runs the real start-up
   script, Contents/Resources/launcher.sh, with bash. */
#include <limits.h>
#include <mach-o/dyld.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(void) {
    char exe[PATH_MAX], real[PATH_MAX], script[PATH_MAX];
    uint32_t size = sizeof exe;
    if (_NSGetExecutablePath(exe, &size) != 0 || realpath(exe, real) == NULL) return 1;
    char *slash = strrchr(real, '/');            /* .../Contents/MacOS/EmpireStudios */
    if (slash == NULL) return 1;
    *slash = '\0';                               /* .../Contents/MacOS */
    snprintf(script, sizeof script, "%s/../Resources/launcher.sh", real);
    char *args[] = {"/bin/bash", script, NULL};
    execv("/bin/bash", args);
    perror("Empire Studios: couldn't start");
    return 1;
}
