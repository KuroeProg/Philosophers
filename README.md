# Philosophers

Fonctions autorisées dans la partie obligatoire :
🔹 Gestion de la mémoire

    malloc(size_t size)
    ➝ Alloue un bloc de mémoire de size octets et retourne un pointeur vers ce bloc.
    ➝ Utilisation : Pour créer dynamiquement les structures des philosophes, des mutexes, etc.

    free(void *ptr)
    ➝ Libère la mémoire allouée par malloc().
    ➝ Utilisation : Éviter les fuites mémoire à la fin du programme.

🔹 Gestion des chaînes et affichage

    memset(void *s, int c, size_t n)
    ➝ Remplit n octets de s avec l’octet c.
    ➝ Utilisation : Initialiser des structures ou des tableaux à zéro.

    printf(const char *format, ...)
    ➝ Affiche du texte formaté dans la sortie standard.
    ➝ Utilisation : Afficher les logs des philosophes (ex: "X is eating").

    write(int fd, const void *buf, size_t count)
    ➝ Écrit count octets de buf dans fd (file descriptor).
    ➝ Utilisation : Afficher les logs si besoin.

🔹 Gestion du temps

    usleep(useconds_t microseconds)
    ➝ Met le programme en pause pour microseconds microsecondes (1 ms = 1000 µs).
    ➝ Utilisation : Gérer les délais pour manger, dormir, etc.

    gettimeofday(struct timeval *tv, struct timezone *tz)
    ➝ Récupère l'heure actuelle avec une précision en microsecondes.
    ➝ Utilisation : Mesurer les temps entre les événements (ex: vérifier si un philosophe meurt).

🔹 Gestion des threads

    pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg)
    ➝ Crée un thread qui exécute start_routine(arg).
    ➝ Utilisation : Créer un thread pour chaque philosophe.

    pthread_detach(pthread_t thread)
    ➝ Détache un thread pour qu'il se libère tout seul à la fin de son exécution.
    ➝ Utilisation : Éviter d’avoir à pthread_join chaque philosophe manuellement.

    pthread_join(pthread_t thread, void **retval)
    ➝ Attend la fin d'un thread et récupère sa valeur de retour.
    ➝ Utilisation : Synchroniser les threads si besoin.

🔹 Gestion des mutexes (verrous)

    pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr)
    ➝ Initialise un mutex.
    ➝ Utilisation : Protéger les accès aux fourchettes et aux logs.

    pthread_mutex_destroy(pthread_mutex_t *mutex)
    ➝ Détruit un mutex pour libérer les ressources.
    ➝ Utilisation : Nettoyage à la fin du programme.

    pthread_mutex_lock(pthread_mutex_t *mutex)
    ➝ Bloque le mutex (verrouille la ressource pour un seul thread).
    ➝ Utilisation : Empêcher deux philosophes de prendre la même fourchette en même temps.

    pthread_mutex_unlock(pthread_mutex_t *mutex)
    ➝ Débloque le mutex.
    ➝ Utilisation : Libérer la fourchette une fois le philosophe a fini de manger.

📌 Fonctions autorisées dans la partie bonus (processus et sémaphores) :

La partie bonus utilise des processus au lieu de threads, donc certaines fonctions changent :
🔹 Gestion des processus

    fork()
    ➝ Crée un nouveau processus enfant.
    ➝ Utilisation : Chaque philosophe sera un processus distinct.

    kill(pid_t pid, int sig)
    ➝ Envoie un signal à un processus (pid).
    ➝ Utilisation : Arrêter proprement un processus philosophe si besoin.

    exit(int status)
    ➝ Termine un processus.
    ➝ Utilisation : Un philosophe peut quitter quand il meurt.

    waitpid(pid_t pid, int *status, int options)
    ➝ Attend qu’un processus enfant se termine.
    ➝ Utilisation : Synchroniser les processus si nécessaire.

🔹 Gestion des sémaphores

Contrairement aux mutexes, les sémaphores permettent à plusieurs processus d’accéder à une ressource partagée.

    sem_open(const char *name, int oflag, mode_t mode, unsigned int value)
    ➝ Crée ou ouvre un sémaphore nommé.
    ➝ Utilisation : Gérer l’accès aux fourchettes de manière plus efficace.

    sem_close(sem_t *sem)
    ➝ Ferme un sémaphore.
    ➝ Utilisation : Libérer les ressources à la fin du programme.

    sem_post(sem_t *sem)
    ➝ Incrémente le sémaphore (libère une ressource).
    ➝ Utilisation : Un philosophe remet une fourchette sur la table.

    sem_wait(sem_t *sem)
    ➝ Décrémente le sémaphore (attend une ressource).
    ➝ Utilisation : Un philosophe prend une fourchette.

    sem_unlink(const char *name)
    ➝ Supprime un sémaphore nommé.
    ➝ Utilisation : Nettoyage après l’exécution du programme.

