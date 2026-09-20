# Projet C — Mini Job Supervisor

## Objectif

Construire en environ 1 heure un programme C qui combine :

* plusieurs threads ;
* une file de travail partagée ;
* plusieurs processus enfants ;
* des signaux ;
* la récupération correcte des processus terminés.

Le projet doit te permettre de comprendre expérimentalement :

`mutex`, `semaphore`, `signal`, `fork`, `wait/waitpid`, processus zombie.

Tu ne dois pas commencer par chercher leurs définitions. Commence par construire, observer les problèmes, puis cherche uniquement ce qui te manque pour continuer.

---

## Comportement attendu

Ton programme s'appelle :

```text
jobd
```

Au lancement, il doit créer une petite file de jobs.

Un thread produit régulièrement des jobs.

Un ou plusieurs threads récupèrent ces jobs.

Certains jobs doivent provoquer la création d'un processus enfant.

Le processus enfant effectue une tâche triviale pendant quelques secondes puis termine avec un code de retour.

Le programme principal doit continuer à fonctionner pendant ce temps.

Quand un enfant termine, le programme parent doit finir par récupérer correctement son état.

Le programme doit aussi pouvoir être arrêté proprement avec `Ctrl+C`.

---

## Contraintes

La file partagée a une capacité fixe très petite, par exemple 3 éléments.

Plusieurs threads doivent pouvoir y accéder.

Un producteur ne doit pas pouvoir insérer un élément si la file est pleine.

Un consommateur ne doit pas pouvoir retirer un élément si la file est vide.

Deux threads ne doivent jamais modifier simultanément l'état interne de la file.

Tu dois résoudre ces trois problèmes séparément. Si une seule primitive semble résoudre les trois, vérifie soigneusement ton raisonnement.

---

## Phase 1 — File concurrente

Implémente une file circulaire contenant quelques entiers.

Écris au minimum :

```c
queue_init(...)
queue_push(...)
queue_pop(...)
```

Ajoute ensuite :

```text
1 producer
2 consumers
```

Chaque opération doit afficher suffisamment d'informations pour comprendre ce qui se passe :

```text
producer: added job 7
consumer 1: received job 4
consumer 2: received job 5
```

Cherche uniquement ce dont tu as besoin pour répondre à ces problèmes :

> Comment empêcher deux threads de modifier simultanément une structure ?

> Comment bloquer lorsqu'aucun job n'existe ?

> Comment bloquer lorsqu'il n'y a plus de place ?

---

## Phase 2 — Processus enfants

Certains jobs doivent lancer un nouveau processus.

Exemple conceptuel :

```text
job 1
    ↓
worker
    ↓
create child
    ↓
child works
    ↓
child terminates
```

Le parent ne doit pas attendre immédiatement la fin du child de manière bloquante.

L'objectif est que plusieurs enfants puissent exister indépendamment du programme principal.

Cherche :

```text
fork
getpid
getppid
_exit
```

Observe attentivement les valeurs retournées par `fork()` dans le parent et dans l'enfant.

Tu dois être capable d'expliquer pourquoi le même appel produit deux chemins d'exécution différents.

---

## Phase 3 — Créer volontairement un zombie

Modifie temporairement ton programme pour que le parent ne récupère pas immédiatement un enfant terminé.

Laisse le parent vivant suffisamment longtemps pour observer le système.

Utilise des outils système comme :

```bash
ps
```

Trouve ton processus enfant terminé.

Identifie son état.

À partir de cette observation, détermine :

> Le processus exécute-t-il encore du code ?

> Pourquoi apparaît-il encore dans la table des processus ?

> Quelle information le kernel conserve-t-il ?

> Quelle action du parent fait disparaître cet état ?

Ne corrige pas le problème avant de l'avoir observé.

---

## Phase 4 — Récolter les enfants

Le programme doit maintenant récupérer les enfants terminés sans bloquer son activité principale.

Trouve comment demander au système :

```text
"Donne-moi les enfants terminés disponibles,
mais ne bloque pas s'il n'y en a aucun."
```

Ton programme doit pouvoir gérer plusieurs enfants terminant presque simultanément.

Teste spécifiquement ce cas.

---

## Phase 5 — SIGCHLD

Supprime le polling permanent.

Le programme doit maintenant être informé lorsqu'un enfant change d'état.

Cherche :

```text
SIGCHLD
sigaction
signal handler
```

Ne mets pas immédiatement toute la logique de nettoyage dans le handler.

Cherche d'abord :

```text
async-signal-safe
```

Puis décide quelle quantité minimale de travail doit être effectuée dans le handler.

Ton programme principal doit ensuite effectuer le travail restant.

---

## Phase 6 — SIGINT

`Ctrl+C` doit demander un arrêt propre du programme.

Le programme ne doit pas simplement mourir brutalement.

Lors de l'arrêt :

```text
arrêter la production
terminer les threads
récupérer les enfants
détruire les ressources de synchronisation
quitter
```

Cherche quel signal correspond normalement à `Ctrl+C`.

Réutilise le même raisonnement que pour `SIGCHLD` :

```text
notification asynchrone
        ↓
handler minimal
        ↓
programme normal effectue le travail réel
```

---

## Expériences obligatoires

Quand ton programme fonctionne, casse-le volontairement.

Fais les expériences suivantes et note ce que tu observes :

1. Supprimer la protection autour de la structure de la queue.
2. Supprimer le mécanisme empêchant de lire une queue vide.
3. Supprimer le mécanisme empêchant d'écrire dans une queue pleine.
4. Ne jamais récupérer un child terminé.
5. Remettre la récupération des children.
6. Créer plusieurs children qui terminent presque en même temps.
7. Envoyer manuellement `SIGINT` au programme avec `kill`.

Pour chaque expérience, écris :

```text
Hypothèse :
Observation :
Explication :
```

---

## Questions auxquelles tu dois savoir répondre après le projet

Sans regarder Internet ni ton code :

```text
Pourquoi un mutex n'est-il pas simplement un semaphore initialisé à 1 ?

Pourquoi protéger la queue avec un mutex ne suffit-il pas pour attendre qu'un job arrive ?

Pourquoi un semaphore peut-il représenter le nombre de cases libres ?

Qu'est-ce qui déclenche SIGCHLD ?

SIGCHLD supprime-t-il un zombie ?

À quel moment exact un processus devient-il zombie ?

Pourquoi un zombie existe-t-il ?

Quelle différence entre exit(), _exit() et waitpid() ?

Pourquoi un signal peut-il rendre certaines fonctions dangereuses dans un handler ?

Pourquoi waitpid(..., WNOHANG) est-il utile dans ce programme ?
```

Si tu ne peux pas expliquer une réponse avec un exemple provenant de ton propre programme, considère la notion comme non acquise.

---

## Règles

N'utilise pas de code complet trouvé en ligne.

Tu peux chercher :

```text
man pthread_mutex_lock
man sem_wait
man fork
man waitpid
man sigaction
```

Privilégie les pages `man` avant les tutoriels.

Compile toujours avec :

```bash
gcc -Wall -Wextra -Wpedantic -pthread ...
```

Ne masque pas les warnings.

Ajoute temporairement beaucoup de `printf` contenant :

```text
PID
thread
job
événement
```

Le but n'est pas d'obtenir un programme propre rapidement. Le but est de rendre visibles les états concurrents du programme.

---

## Critère de réussite

Le projet est terminé lorsque tu peux dessiner de mémoire ceci et expliquer chaque flèche :

```text
producer threads
       |
       v
   job queue
       |
       v
consumer threads
       |
       +------> fork
                  |
             +----+----+
             |         |
           parent    child
             |         |
             |       terminates
             |         |
             |      SIGCHLD
             |         |
             +---------+
                  |
               waitpid
```

Et lorsque tu peux expliquer précisément pourquoi :

```text
mutex ≠ semaphore
signal ≠ synchronization lock
child terminated ≠ child completely removed
SIGCHLD ≠ waitpid
```
