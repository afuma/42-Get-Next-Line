# Get Next Line

[![42 School](https://img.shields.io/badge/42-School-000000?style=flat&logo=42&logoColor=white)](https://42.fr/)
[![Language](https://img.shields.io/badge/Language-C-blue.svg)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Standard](https://img.shields.io/badge/Standard-C99-yellow.svg)](https://en.wikipedia.org/wiki/C99)

## 📖 Description

**Get Next Line** est un projet fondamental de l'école 42 qui consiste à programmer une fonction capable de lire un fichier ligne par ligne. Cette fonction est particulièrement utile pour traiter de gros fichiers sans les charger entièrement en mémoire.

La fonction `get_next_line()` lit et retourne une ligne à la fois depuis un descripteur de fichier, en gérant efficacement la mémoire et en optimisant les opérations de lecture grâce à un système de buffer configurable.

## ✨ Fonctionnalités

### 🔧 Fonctionnalités principales
- **Lecture ligne par ligne** : Traitement séquentiel des fichiers texte
- **Gestion mémoire optimisée** : Utilisation d'un buffer configurable (BUFFER_SIZE)
- **Support multi-fichiers** : Gestion simultanée de plusieurs descripteurs (version bonus)
- **Gestion des fins de ligne** : Détection et préservation des caractères `\n`
- **Robustesse** : Gestion complète des cas d'erreur et des fichiers vides

### 🛠️ Aspects techniques
- **Variables statiques** : Persistance des données entre les appels
- **Listes chaînées** : Structure de données pour le stockage temporaire
- **Buffer dynamique** : Taille de lecture configurable à la compilation
- **Gestion des descripteurs** : Support des fichiers, stdin, et autres sources

## 🔧 Prérequis

### Système
- **OS** : Unix/Linux/macOS
- **Compilateur** : GCC ou Clang avec support C99
- **Make** : Pour la compilation (optionnel)

### Bibliothèques système
```c
#include <unistd.h>    // read()
#include <stdlib.h>    // malloc(), free()
#include <fcntl.h>     // open(), close()
```

## 🚀 Installation et compilation

### 1. Clonage du projet
```bash
git clone [URL_DU_REPO]
cd get-next-line
```

### 2. Compilation basique
```bash
# Compilation avec BUFFER_SIZE par défaut (3)
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -o gnl_test
```

### 3. Compilation avec BUFFER_SIZE personnalisé
```bash
# Exemple avec BUFFER_SIZE = 1000
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=1000 get_next_line.c get_next_line_utils.c main.c -o gnl_test

# Exemple avec BUFFER_SIZE = 1 (test extrême)
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=1 get_next_line.c get_next_line_utils.c main.c -o gnl_test
```

### 4. Version bonus (multi-fichiers)
```bash
# Compilation de la version bonus
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line_bonus.c get_next_line_utils_bonus.c main.c -o gnl_bonus
```

## 🎯 Utilisation

### Prototype de la fonction
```c
char *get_next_line(int fd);
```

### Paramètres
- **fd** : Descripteur de fichier à lire

### Valeur de retour
- **Ligne lue** : Chaîne de caractères incluant le `\n` final (si présent)
- **NULL** : Fin de fichier atteinte ou erreur

### Exemple d'utilisation basique
```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int fd;
    char *line;
    
    fd = open("test.txt", O_RDONLY);
    if (fd == -1)
        return (1);
    
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    
    close(fd);
    return (0);
}
```

### Exemple avec stdin
```c
#include "get_next_line.h"
#include <stdio.h>

int main(void)
{
    char *line;
    
    printf("Entrez du texte (Ctrl+D pour terminer):\n");
    while ((line = get_next_line(0)) != NULL)  // 0 = stdin
    {
        printf("Lu: %s", line);
        free(line);
    }
    
    return (0);
}
```

### Exemple multi-fichiers (bonus)
```c
#include "get_next_line_bonus.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int fd1, fd2;
    char *line1, *line2;
    
    fd1 = open("file1.txt", O_RDONLY);
    fd2 = open("file2.txt", O_RDONLY);
    
    // Lecture alternée des deux fichiers
    while ((line1 = get_next_line(fd1)) || (line2 = get_next_line(fd2)))
    {
        if (line1)
        {
            printf("File1: %s", line1);
            free(line1);
        }
        if (line2)
        {
            printf("File2: %s", line2);
            free(line2);
        }
    }
    
    close(fd1);
    close(fd2);
    return (0);
}
```

## 🏗️ Architecture du code

```
get-next-line/
├── get_next_line.c         # Fonction principale
├── get_next_line_utils.c   # Fonctions utilitaires
├── get_next_line.h         # Header principal
├── get_next_line_bonus.c   # Version multi-fichiers
├── get_next_line_utils_bonus.c
├── get_next_line_bonus.h   # Header bonus
└── README.md              # Documentation
```

### Modules détaillés

#### 📚 Fonction principale (`get_next_line.c`)
- **get_next_line()** : Point d'entrée principal
- **read_and_stash()** : Lecture et stockage des données
- **add_to_stash()** : Ajout de données à la liste chaînée
- **found_newline()** : Détection du caractère de fin de ligne

#### 🛠️ Utilitaires (`get_next_line_utils.c`)
- **extract_line()** : Extraction d'une ligne complète
- **generate_line()** : Allocation mémoire pour la ligne
- **clean_stash()** : Nettoyage du buffer après extraction
- **free_stash()** : Libération de la mémoire
- **ft_lstlast()** : Navigation dans la liste chaînée

## 🔍 Fonctionnement interne

### 1. **Structure de données**
```c
typedef struct s_list
{
    char            *content;  // Contenu du buffer
    struct s_list   *next;     // Élément suivant
} t_list;
```

### 2. **Algorithme principal**
```
1. Lecture par chunks de BUFFER_SIZE octets
2. Stockage dans une liste chaînée statique
3. Recherche du caractère '\n'
4. Extraction de la ligne complète
5. Nettoyage du buffer restant
6. Retour de la ligne ou NULL
```

### 3. **Gestion de la mémoire**
```c
static t_list *lst;  // Variable statique persistante

// Cycle de vie :
// Allocation → Utilisation → Nettoyage partiel → Réutilisation
```

### 4. **Optimisation du BUFFER_SIZE**
```c
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 3    // Valeur par défaut
#endif

// Validation :
#if BUFFER_SIZE < 0
# undef BUFFER_SIZE
# define BUFFER_SIZE 0
#endif
```

## 🧪 Tests et validation

### Tests de base
```bash
# Création d'un fichier de test
echo -e "Ligne 1\nLigne 2\nLigne 3" > test.txt

# Test avec différents BUFFER_SIZE
gcc -D BUFFER_SIZE=1 get_next_line.c get_next_line_utils.c main.c -o test1
gcc -D BUFFER_SIZE=10 get_next_line.c get_next_line_utils.c main.c -o test10
gcc -D BUFFER_SIZE=1000 get_next_line.c get_next_line_utils.c main.c -o test1000

./test1 test.txt
./test10 test.txt  
./test1000 test.txt
```

### Tests de cas limites
```bash
# Fichier vide
touch empty.txt
./gnl_test empty.txt

# Fichier sans '\n' final
echo -n "Ligne sans retour" > no_newline.txt
./gnl_test no_newline.txt

# Très gros fichier
seq 1 100000 > big_file.txt
./gnl_test big_file.txt

# Fichier avec lignes très longues
python3 -c "print('A' * 10000)" > long_line.txt
./gnl_test long_line.txt
```

### Tests avec stdin
```bash
# Test interactif
./gnl_test

# Test avec pipe
echo -e "ligne1\nligne2\nligne3" | ./gnl_test

# Test avec redirection
./gnl_test < test.txt
```

### Tests bonus (multi-fichiers)
```bash
# Création de plusieurs fichiers
echo -e "File1-L1\nFile1-L2" > file1.txt
echo -e "File2-L1\nFile2-L2" > file2.txt

# Test de lecture simultanée
./gnl_bonus file1.txt file2.txt
```

## 📝 Gestion des erreurs

### Validation des paramètres
```c
if (BUFFER_SIZE <= 0 || fd < 0 || fd >= 1024)
    return (NULL);
```

### Cas d'erreur gérés
- ❌ **Descripteur invalide** : fd < 0 ou fd >= 1024
- ❌ **BUFFER_SIZE invalide** : Valeur <= 0
- ❌ **Erreur de lecture** : read() retourne -1
- ❌ **Allocation mémoire** : malloc() échoue
- ❌ **Fichier fermé** : Descripteur fermé pendant la lecture

### Gestion mémoire
- ✅ **Pas de fuites** : Toute allocation est libérée
- ✅ **Nettoyage automatique** : Variables statiques nettoyées en fin de fichier
- ✅ **Robustesse** : Gestion des échecs d'allocation

## 🔧 Configuration et optimisation

### BUFFER_SIZE optimal
```c
// Trop petit (1) : Nombreux appels système
#define BUFFER_SIZE 1

// Équilibré (42-1024) : Bon compromis
#define BUFFER_SIZE 42

// Gros (4096+) : Moins d'appels système, plus de mémoire
#define BUFFER_SIZE 4096
```

### Recommandations
- **Fichiers texte normaux** : BUFFER_SIZE = 42-1024
- **Gros fichiers** : BUFFER_SIZE = 4096-8192  
- **Tests/Debug** : BUFFER_SIZE = 1
- **Mémoire limitée** : BUFFER_SIZE = 42

## 🚀 Cas d'usage

### Applications pratiques
- **Parseurs de configuration** : Lecture de fichiers .conf
- **Analyseurs de logs** : Traitement ligne par ligne
- **Lecteurs de CSV** : Parsing de données tabulaires
- **Shells** : Lecture de commandes depuis stdin
- **Éditeurs de texte** : Chargement progressif de fichiers

### Avantages
- **Mémoire constante** : Pas de chargement complet du fichier
- **Performance** : Buffer optimisable selon le contexte
- **Flexibilité** : Fonctionne avec tout descripteur de fichier
- **Simplicité** : Interface claire et intuitive

## 📚 Concepts C appris

Ce projet permet de maîtriser :
- **Variables statiques** : Persistance entre appels de fonction
- **Listes chaînées** : Structure de données dynamique
- **Gestion mémoire** : malloc(), free(), détection de fuites
- **Descripteurs de fichiers** : open(), read(), close()
- **Préprocesseur** : #define, #ifndef, compilation conditionnelle
- **Pointeurs** : Manipulation avancée et double indirection

## 🔍 Différences version standard vs bonus

| Aspect | Standard | Bonus |
|--------|----------|-------|
| **Fichiers simultanés** | 1 seul | Multiples |
| **Variable statique** | `static t_list *lst` | `static t_list *lst[1024]` |
| **Complexité** | Simple | Gestion d'un tableau de listes |
| **Mémoire** | Une liste par programme | Une liste par descripteur |

## 👨‍💻 Auteur

**Etienne** - [edesaint@student.42.fr](mailto:edesaint@student.42.fr)

## 📄 Licence

Ce projet est développé à des fins éducatives dans le cadre de l'école 42.

---

*Lisez ligne par ligne, maîtrisez fichier par fichier ! 📖✨*
