#include <stdlib.h>
#include <stdio.h>

int main() {
    // Remplacez l'URL par celle que vous souhaitez ouvrir
    const char *url = "https://e-campus.enac.fr/moodle/course/view.php?id=15035";
    
    // Commande pour ouvrir l'URL dans le navigateur par défaut
    char command[256];
    snprintf(command, sizeof(command), "start %s", url);
    system(command);
    
    return 0;
}