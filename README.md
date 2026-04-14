# CS Roadmap 

<p align="center">
<img src="./assets/rijksmuseum_claesz_1628.jpg" alt="Rijksmuseum Claesz 1628" width="100%" heigh="50%" />
</p>

```c
##include <stdio.h>

typedef struct {
    const char *dir;
    const char *desc;
} Node;

int main(void) {
    // Princípios de design
    const char *focus[] = {
        "Simple human navigation",
        "Terminal-friendly access",
        "Complete thematic context"
    };

    // Regras de integridade (Standards)
    const char *rules[] = {
        "Folder names: English",
        "Internal notes: PT-BR",
        "Hierarchy: roadmap/tracks",
        "Encapsulation: resources inside themes"
    };

    // Estrutura principal (File System)
    Node filesystem[] = {
        {"roadmap/",   "Trilhas e temas numerados"},
        {"resources/", "Templates e guias de apoio"},
        {"scripts/",   "Automação e manutenção"}
    };

    printf("Repository: CS Roadmap initialized.\n");

    return 0;
}
```
